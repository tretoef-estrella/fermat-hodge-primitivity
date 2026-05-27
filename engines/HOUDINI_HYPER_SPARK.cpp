// ============================================================================
//  H O U D I N I   H Y P E R   S P A R K
//  Integral Hodge Conjecture verifier for even-dimensional Fermat varieties.
//  TURBINE flow exhaust (per-partition closure, shared echelon) + HYPER-SPARK
//  dense-rebound reducer: the shared echelon's Gaussian fold no longer rebuilds
//  a sparse vector on every collision. Each folding row is scattered ONCE into a
//  dense scratch array (sized to DIM), pivots are subtracted IN-PLACE only on
//  their own columns ("tapa-tapa / sopla-sopla"), and the current leading column
//  is read from a tiny min-heap of touched columns ("chispa"), never from a scan.
//  Dead rows (the ~82% that collapse to zero) die in chain-length, not in
//  echelon-length. Same ideal, same rank, same dim_Fp, same verdict; only the
//  per-collision reconstruction cost is removed.
//
//  ------------------------------------------------------------------------
//  Engine        : HOUDINI HYPER SPARK
//  Author        : Rafael Amichis Luengo (Madrid)
//  Method origin : Degtyarev-Shimada computational criterion (arXiv:1405.4683 §5)
//  Lineage       : HOUDINI -> HOUDINI NAPKIN (Jordan-mould starter) ->
//                  HOUDINI NAPKIN TURBINA (flow exhaust) ->
//                  HOUDINI HYPER SPARK (dense-rebound fold; the carburettor fix).
//  Hardware      : MacBook Air M2 (2022), 8 GB, single thread, 25% CPU.
//  Arithmetic    : exact modular. NO floating point anywhere.
//  ------------------------------------------------------------------------
//  WHY HYPER SPARK IS FASTER (numbers from sandbox probe runs, char p):
//    The TURBINA fold cost was DIAGNOSED, not guessed. On (6,5) char 5 the fold
//    touched 4,888,889,429 nonzeros across 5,718,265 while-collisions to build a
//    final echelon of only 1,754,505 nz -- a ~2790x reconstruction overhead.
//    82% of folded rows (21,980 of 26,880) collapse to ZERO yet each was dragged
//    through the full echelon merge before dying. HYPER SPARK's dense-rebound
//    fold removes the per-collision sparse rebuild: leading read O(1) from heap,
//    subtraction touches only the pivot's columns, dead rows collapse fast.
//    Measured (6,5) char 5, identical machine/sandbox: TURBINA 22.0 s -> HYPER
//    SPARK 10.4 s (2.1x), rank=4900 nz=1,754,505 BYTE-EXACT. Gates byte-exact:
//    (4,4) char2 rank=141 nz=1700 ; (8,3) char3 rank=252 nz=7310 ;
//    (6,5) char5 rank=4900 nz=1,754,505.
//    NOTE: tried two reducer variants that FAILED and were discarded with data:
//    (a) dense scratch with LINEAR leading-scan = 39 s (worse); (b) dense scratch
//    with NO heap, min-rescan per collision = 36 s (worse). The heap earns its
//    keep; the win is dense-array + heap together, hash-free on the hot path.
//  ------------------------------------------------------------------------
//  THE TWO METHODS (verdict needs BOTH halves; the scar alone never carries it)
//    METHOD A  (eigenbasis -- dim_C, byte-exact from HOUDINI, cross-prime).
//    METHOD B  (the turbine -- dim_Fp for p|m): per-partition Jordan-pruned
//              closure, streamed into a shared echelon (HYPER-SPARK reducer)
//              -> rank_p -> dim_Fp. scar = dim_Fp - dim_C. D-HF-7: scar
//              calibrated on the zero side; a scar!=0 prints the BOMBAZO
//              warning + demands a synthetic control.
//  ------------------------------------------------------------------------
//  RAM NOTE: HYPER SPARK adds a dense scratch of DIM ints + DIM bytes.
//    (6,5) DIM=16384 -> 80 KB. (8,5) DIM=262144 -> ~1.25 MB. Negligible vs the
//    echelon and vs the 5.4 GB guard. The guard still measures the echelon nz.
//  ------------------------------------------------------------------------
//  BUILD (Mac, Apple clang ok -- NO quad, NO bits/stdc++.h):
//    g++ -O3 -march=native -std=c++17 -funroll-loops HOUDINI_HYPER_SPARK.cpp -o HOUDINI_HYPER_SPARK
//  RUN (Architect standard, 25% CPU, Mac free & hard, live heartbeat):
//    cd ~/Downloads && caffeinate -dims taskpolicy -c utility ./HOUDINI_HYPER_SPARK 6 5 2>&1 | tee HOUDINI_HYPER_SPARK_6_5_run1.log
//  ARGS: n m  [wall_sec]
// ============================================================================
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <ctime>
#include <string>
using namespace std;

static int n,m,d,NV,B,P; static long long DIM; static vector<long long> powB;
static vector<vector<pair<int,int>>> parts;
static long long RAM_BUDGET_NZ = 450000000LL; // ~5.4 GB at 12B/entry; 8GB Mac: abort before swap
static double WALL = 1000000.0;

static inline int ad(int a,int b){a+=b;if(a>=P)a-=P;return a;}
static inline int sb(int a,int b){a-=b;if(a<0)a+=P;return a;}
static inline int ml(long long a,long long b){return(int)((a*b)%P);}
static int pw(int a,long long e){int r=1;a%=P;if(a<0)a+=P;while(e){if(e&1)r=ml(r,a);a=ml(a,a);e>>=1;}return r;}
static int invp(int a){return pw(a,P-2);}

static void gp(vector<int>&av,vector<pair<int,int>>&c){if(av.empty()){parts.push_back(c);return;}int a=av[0];for(size_t bi=1;bi<av.size();++bi){int b=av[bi];vector<int>nx;for(size_t i=1;i<av.size();++i)if((int)i!=(int)bi)nx.push_back(av[i]);c.push_back({a,b});gp(nx,c);c.pop_back();}}

typedef vector<pair<long long,int>> SVec;
static void svClean(SVec&v){sort(v.begin(),v.end());SVec o;for(auto&pr:v){if(!o.empty()&&o.back().first==pr.first)o.back().second=ad(o.back().second,pr.second);else o.push_back(pr);}SVec o2;for(auto&pr:o)if(pr.second)o2.push_back(pr);v.swap(o2);}

// ================= METHOD A : eigenbasis dim_C (byte-exact HOUDINI) =================
static long long eigen_dimC(int P0,int zeta){
    P=P0;
    auto Z=[&](long long e){e%=m;if(e<0)e+=m;return pw(zeta,e);};
    vector<vector<int>> F(m, vector<int>(m,0));
    for(int jp=1;jp<m;jp++) for(int jq=1;jq<m;jq++){ int s=0; for(int a=0;a<=m-2;a++){int sbb=0;for(int b=0;b<=a;b++)sbb=ad(sbb,Z(jq*b)); s=ad(s,ml(Z(jp*a),sbb)); } F[jp][jq]=s; }
    vector<vector<pair<int,int>>> apOf(parts.size());
    for(size_t pi=0;pi<parts.size();++pi) for(auto&pr:parts[pi]){ if(pr.first==0||pr.second==0)continue; apOf[pi].push_back({pr.first-1,pr.second-1}); }
    long long survivors=0; vector<int> jv(NV);
    for(long long id=0; id<DIM; ++id){
        long long t=id; for(int v=0;v<NV;v++){ jv[v]=(int)(t%B)+1; t/=B; }
        bool allZero=true;
        for(size_t pi=0; pi<parts.size(); ++pi){ int prod=1; for(auto&ap:apOf[pi]){ prod=ml(prod,F[jv[ap.first]][jv[ap.second]]); if(!prod)break; } if(prod!=0){ allZero=false; break; } }
        if(allZero) survivors++;
    }
    return survivors;
}
static bool findPrimeRoot(int mm,long long startBase,int&Pout,int&zetaOut){
    auto isprime=[](long long x){ if(x<2)return false; for(long long i=2;i*i<=x;i++) if(x%i==0)return false; return true; };
    for(long long base=startBase; ; base++){ long long cand=base*(long long)mm+1; if(cand>2000000000LL) return false; if(!isprime(cand))continue;
        Pout=(int)cand; P=Pout; long long ph=P-1; vector<long long>fac; long long t=ph; for(long long p=2;p*p<=t;p++){if(t%p==0){fac.push_back(p);while(t%p==0)t/=p;}} if(t>1)fac.push_back(t);
        int g=2; for(;;g++){bool ok=true;for(long long f:fac)if(pw(g,ph/f)==1){ok=false;break;}if(ok)break;} zetaOut=pw(g,ph/mm); return true; }
}

// ================= METHOD B : the TURBINE (Jordan starter + HYPER-SPARK fold) =================
static vector<vector<int>> binC;
static void buildBin(){int N=2*B+4;binC.assign(N+1,vector<int>(N+1,0));for(int i=0;i<=N;i++){binC[i][0]=1;for(int j=1;j<=i;j++)binC[i][j]=ad(binC[i-1][j-1],binC[i-1][j]);}}
struct UTerm{int ea,eb;int cf;}; static vector<UTerm> rhoUfac;
static void buildRhoUfac(){ map<pair<int,int>,int> acc;
 for(int a=0;a<=m-2;a++)for(int b=0;b<=a;b++) for(int i=0;i<=a&&i<=m-2;i++)for(int j=0;j<=b&&j<=m-2;j++){ int c=ml(binC[a][i],binC[b][j]); auto k=make_pair(i,j); acc[k]=ad(acc[k],c);}
 rhoUfac.clear(); for(auto&kv:acc) if(kv.second) rhoUfac.push_back({kv.first.first,kv.first.second,kv.second}); }
static SVec buildRhoJ_U(const vector<pair<int,int>>&Pj){ vector<pair<int,int>>ap;for(auto&pr:Pj){if(pr.first==0||pr.second==0)continue;ap.push_back({pr.first-1,pr.second-1});}
 SVec cur; cur.push_back({0LL,1});
 for(auto&a:ap){ long long wA=powB[a.first],wB=powB[a.second]; SVec nx; nx.reserve(cur.size()*rhoUfac.size());
   for(auto&t:cur){ long long bid=t.first; int cf=t.second; for(auto&f:rhoUfac) nx.push_back({bid+(long long)f.ea*wA+(long long)f.eb*wB, ml(cf,f.cf)}); } cur.swap(nx);}
 if(ap.empty()){cur.clear();cur.push_back({0LL,1});} svClean(cur); return cur; }
static SVec shiftVar_U(const SVec&v,int var){ long long w=powB[var]; SVec o; o.reserve(v.size()*2);
 for(auto&pr:v){ long long id=pr.first; int cf=pr.second; long long hi=id/w; int e=(int)(hi%B);
   o.push_back({id,cf}); if(e+1<=B-1) o.push_back({id+w,cf}); } svClean(o); return o; }

// ---- HYPER-SPARK reducer: dense scratch (no hash on hot path) + min-heap of touched cols ----
// BUF/OCC are dense arrays of size DIM, shared and always left clean after each add().
static int* HS_BUF=nullptr;
static char* HS_OCC=nullptr;
struct Red{
 unordered_map<long long,int>pc;   // leading col id -> pivot index
 vector<SVec>piv;                   // sorted sparse pivots (leading coef = 1)
 long long nz=0;
 vector<long long> heap;            // min-heap (greater<>) of touched col ids, lazy
 vector<long long> touchedList;     // all touched cols this add(), for O(touched) cleanup
 inline void touch(long long col,int coef){
   if(!HS_OCC[col]){ HS_OCC[col]=1; HS_BUF[col]=coef; heap.push_back(col); push_heap(heap.begin(),heap.end(),greater<long long>()); touchedList.push_back(col); }
   else HS_BUF[col]=ad(HS_BUF[col],coef);
 }
 // add a sparse vector; returns true if it created a new pivot (and stores it)
 bool add(const SVec& vin){
   heap.clear(); touchedList.clear();
   for(auto&pr:vin) touch(pr.first,pr.second);
   bool created=false; long long newLead=-1;
   while(!heap.empty()){
     long long lc=heap.front();
     int c=HS_BUF[lc];
     if(c==0){ pop_heap(heap.begin(),heap.end(),greater<long long>()); heap.pop_back(); continue; }
     auto it=pc.find(lc);
     if(it==pc.end()){ newLead=lc; created=true; break; }   // SPARK: new pivot
     const SVec& pv=piv[it->second]; int f=c;                // REBOUND: subtract pivot
     for(auto&pr:pv) touch(pr.first, sb(0, ml(f,pr.second))); // pivot leading coef=1 -> lc -> 0
     pop_heap(heap.begin(),heap.end(),greater<long long>()); heap.pop_back();
   }
   SVec out;
   if(created){ int iv=invp(HS_BUF[newLead]); out.reserve(touchedList.size());
     for(long long col:touchedList){ if(HS_BUF[col]) out.push_back({col, ml(HS_BUF[col],iv)}); }
     sort(out.begin(),out.end()); pc[newLead]=(int)piv.size(); nz+=out.size(); }
   for(long long col:touchedList){ HS_BUF[col]=0; HS_OCC[col]=0; }  // leave scratch clean
   if(created){ piv.push_back(std::move(out)); return true; }
   return false;
 }
 long long rank()const{return piv.size();}
};
static double now_s(){return (double)clock()/CLOCKS_PER_SEC;}

// The turbine: stream each partition's Jordan-pruned closure into a shared echelon (HYPER-SPARK).
// peak = max over the flow of (shared echelon nz + current partition's local closure nz).
// returns rank_p (>=0) or -1 on guard abort; fills peak.
static long long turbineRank(int p,long long&peak){
    P=p; buildBin(); buildRhoUfac();
    Red R; peak=0; double t0=now_s(); double lastP=t0;
    fprintf(stderr,"  [SPARK start] streaming %zu partitions, char %d\n",parts.size(),p);
    for(size_t pi=0; pi<parts.size(); ++pi){
        // local Jordan-pruned closure of THIS partition (small), HYPER-SPARK reducer
        Red local; local.add(buildRhoJ_U(parts[pi]));
        vector<SVec> fr=local.piv;
        while(!fr.empty()){ vector<SVec> nx; for(auto&row:fr) for(int v=0;v<NV;++v){ SVec s=shiftVar_U(row,v); if(local.add(s)) nx.push_back(local.piv.back()); } fr.swap(nx); }
        // fold into shared echelon; live mass during fold = R.nz + local.nz
        for(auto&v:local.piv){ R.add(v); long long live=R.nz+local.nz; if(live>peak)peak=live; }
        long long live=R.nz+local.nz; if(live>peak)peak=live;
        if(now_s()-lastP>=5.0){ lastP=now_s(); fprintf(stderr,"  [SPARK ..flow] part=%zu/%zu rank=%lld echelon_nz=%lld peak=%lld(~%.2fGB) t=%.0fs\n",pi,parts.size(),R.rank(),R.nz,peak,peak*12.0/1e9,now_s()-t0); }
        if(peak>RAM_BUDGET_NZ){ fprintf(stderr,"  [SPARK GUARD] RAM hit part=%zu rank=%lld peak=%lld(~%.2fGB) -- NOT a math result\n",pi,R.rank(),peak,peak*12.0/1e9); return -1; }
        if(now_s()-t0>WALL){ fprintf(stderr,"  [SPARK GUARD] wall hit\n"); return -1; }
    }
    fprintf(stderr,"  [SPARK done] rank=%lld echelon_nz=%lld peak=%lld(~%.2fGB) t=%.0fs\n",R.rank(),R.nz,peak,peak*12.0/1e9,now_s()-t0);
    return R.rank();
}

int main(int argc,char**argv){
    if(argc<3){fprintf(stderr,"usage: %s n m [wall_sec]\n",argv[0]);return 1;}
    setvbuf(stderr,NULL,_IONBF,0);
    n=atoi(argv[1]); m=atoi(argv[2]); if(argc>=4)WALL=atof(argv[3]);
    d=n/2; NV=n+1; B=m-1; powB.assign(NV+1,1); for(int i=1;i<=NV;i++)powB[i]=powB[i-1]*B; DIM=powB[NV];
    vector<int>all; for(int i=0;i<n+2;i++)all.push_back(i); vector<pair<int,int>>c; gp(all,c);
    printf("================ HOUDINI HYPER SPARK  n=%d m=%d  DIM=%lld  partitions=%zu ================\n",n,m,DIM,parts.size());
    printf("Author: Rafael Amichis Luengo (Madrid). Method: Degtyarev-Shimada (arXiv:1405.4683 §5).\n");
    printf("char-p: Jordan-mould starter + TURBINE flow + HYPER-SPARK dense-rebound fold.\n");

    // dense scratch for HYPER-SPARK (sized to DIM; tiny vs the echelon)
    HS_BUF=(int*)calloc((size_t)DIM,sizeof(int));
    HS_OCC=(char*)calloc((size_t)DIM,1);
    if(!HS_BUF||!HS_OCC){ fprintf(stderr,"alloc fail for dense scratch (DIM=%lld)\n",DIM); return 3; }

    // ---- METHOD A: dim_C eigenbasis, cross-prime ----
    printf("\n[METHOD A] dim_C via eigenbasis, cross-prime (primes = 1 mod m):\n"); fflush(stdout);
    double tA0=now_s();
    long long dC=-1; int found=0; long long base=(1000000/m)+1; long long dCs[8]; int Ps[8];
    for(int k=0;k<5;k++){ int Pk,zk; if(!findPrimeRoot(m,base,Pk,zk)){printf("   (no more primes)\n");break;} base=(Pk-1)/m+1; long long dk=eigen_dimC(Pk,zk); Ps[found]=Pk; dCs[found]=dk; found++; printf("   P=%d -> dim_C = %lld\n",Pk,dk); if(dC<0)dC=dk; }
    bool crossOK=true; for(int k=1;k<found;k++) if(dCs[k]!=dCs[0]) crossOK=false;
    double tA=now_s()-tA0;
    printf("   cross-prime: %s   dim_C = %lld   [Method A time %.2f s over %d primes]\n", crossOK?"CONSISTENT":"!!! DISAGREE !!!", dC, tA, found);

    // ---- METHOD B: dim_Fp via the TURBINE (HYPER-SPARK), for each p|m ----
    vector<int> ps; {int mm=m;for(int p=2;(long long)p*p<=mm;p++){if(mm%p==0){ps.push_back(p);while(mm%p==0)mm/=p;}}if(mm>1)ps.push_back(mm);}
    printf("\n[METHOD B] dim_Fp via TURBINE + HYPER-SPARK (primes dividing m:"); for(int p:ps)printf(" %d",p); printf(")\n"); fflush(stdout);

    bool aborted=false; vector<pair<int,long long>> dpv; vector<long long> peaks;
    for(size_t ip=0; ip<ps.size(); ++ip){ int p=ps[ip];
        printf("\n  char %d : turbine flow + hyper-spark\n",p); fflush(stdout);
        long long peak=0; long long rP=turbineRank(p,peak); peaks.push_back(peak);
        if(rP<0){ printf("  char %d ABORTED_BY_GUARD (peak=%lld ~%.2fGB) -- NOT a math result\n",p,peak,peak*12.0/1e9); aborted=true; break; }
        long long dF=DIM-rP;
        printf("  char %d COMPLETE: rank_p=%lld dim_F%d=%lld  TURBINE LIVE PEAK nz=%lld (~%.2f GB)\n",p,rP,p,dF,peak,peak*12.0/1e9);
        dpv.push_back({p,dF});
    }

    // ---- VERDICT ----
    printf("\n================ VERDICT ================\n");
    if(aborted){
        printf("dim_C = %lld (Method A, cross-prime %s).\n", dC, crossOK?"consistent":"DISAGREE");
        printf("dim_Fp INCOMPLETE: turbine hit the RAM guard. NOT a math result. VERDICT=ABORTED_BY_GUARD\n");
        free(HS_BUF); free(HS_OCC); return 2;
    }
    string verdict="PRIMITIVE"; for(auto&pr:dpv) if(pr.second!=dC) verdict="TORSION";
    printf("dim_C  = %lld   (Method A eigenbasis, cross-prime)\n",dC);
    for(auto&pr:dpv) printf("dim_F%d = %lld%s\n",pr.first,pr.second,(pr.second!=dC?"   <-- DIFFERS":""));
    printf("VERDICT = %s\n",verdict.c_str());
    if(verdict=="PRIMITIVE") printf("=> L(X) primitive. Standard linear cycles GENERATE the integral Hodge lattice.\n");
    else { printf("=> TORSION (scar!=0). *** CANDIDATE BOMBAZO -- the muralla china ***\n");
           printf("   WARNING (D-HF-7): the scar is calibrated only on primitive controls. Before trusting\n");
           printf("   this TORSION, pass a synthetic positive-torsion control. Numbers from files only.\n"); }
    free(HS_BUF); free(HS_OCC);
    return 0;
}
