// ============================================================================
//  R O S E T T A   S T A R
//  Integral Hodge Conjecture verifier for even-dimensional Fermat varieties.
//  The engine that translates the MONOMIAL basis correctly for ALL m, including
//  m with multiple distinct prime factors (m=6,10,12,...) where the Jordan-mould
//  starter (u^{m-1}=0) is WRONG because phi(u+1) != u^{m-1}.
//
//  ------------------------------------------------------------------------
//  Engine        : ROSETTA STAR
//  Author        : Rafael Amichis Luengo (Madrid)
//  Method origin : Degtyarev-Shimada computational criterion (arXiv:1405.4683 S5)
//  Lineage       : HOUDINI SONIC BOOM STAR (TURBINE flow + SONICSTAR-FOLD
//                  dense-rebound fold + delta-varint embedded-coef store)
//                  with the Jordan-mould starter REPLACED by the correct
//                  MONOMIAL-basis construction + phi-reduction shift.
//  Hardware      : MacBook Air M2 (2022), 8 GB, single thread, 25% CPU.
//  Arithmetic    : exact modular. NO floating point anywhere.
//  ------------------------------------------------------------------------
//  THE FIX (why this engine exists):
//    STAR's Jordan-mould uses u=t-1 and prunes by u^{m-1}=0. That is
//    equivalent to phi(u+1) = u^{m-1}, which holds IFF m is a prime power.
//    For m=6=2*3:
//      phi(u+1) mod 2 = u*(u^2+u+1)^2  != u^5     [WRONG pruning]
//      phi(u+1) mod 3 = u^2*(u-1)^3    != u^5     [WRONG pruning]
//    ROSETTA works in the MONOMIAL basis (t, not u). The shift by t_v
//    reduces t_v^{m-1} via phi(t_v) = 0, i.e. t_v^{m-1} = -(1+t_v+...+t_v^{m-2}).
//    This is correct for ALL m, ALL char. The quotient ring
//    Rbar = F_p[t_1..t_{n+1}]/(phi(t_i)) has basis {t^a : 0<=a_i<=m-2},
//    dim = (m-1)^{n+1} = DIM. No Jordan, no binomial, no pruning.
//    The TURBINE flow, SONICSTAR-FOLD reducer, delta-varint store, RAM guard,
//    Method A eigenbasis -- all byte-identical from STAR.
//  GATES: (4,4) char 2 rank=141 dim=102; (6,5) char 5 rank=4900 dim=11484;
//         (8,3) char 3 rank=252 dim=260. All must match STAR byte-exact.
//  TARGET: (6,6) char 2 and char 3 -- the cell where Jordan fails.
//  ------------------------------------------------------------------------
//  BUILD (Mac, Apple clang ok -- NO quad, NO bits/stdc++.h):
//    g++ -O3 -march=native -std=c++17 -funroll-loops ROSETTA_STAR.cpp -o ROSETTA_STAR
//  RUN:
//    cd ~/Downloads && caffeinate -dims taskpolicy -c utility ./ROSETTA_STAR 6 6 2>&1 | tee ROSETTA_STAR_6_6_run1.log
//  ARGS: n m [wall_sec]
// ============================================================================
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <algorithm>
#include <ctime>
#include <string>
using namespace std;

static int n,m,d,NV,B,P; static long long DIM; static vector<long long> powB;
static vector<vector<pair<int,int>>> parts;
static long long RAM_BUDGET_BYTES = 5400000000LL; // 5.4 GB guard
static double WALL = 1000000.0;

static inline int ad(int a,int b){a+=b;if(a>=P)a-=P;return a;}
static inline int sb(int a,int b){a-=b;if(a<0)a+=P;return a;}
static inline int ml(long long a,long long b){return(int)((a*b)%P);}
static int pw(int a,long long e){int r=1;a%=P;if(a<0)a+=P;while(e){if(e&1)r=ml(r,a);a=ml(a,a);e>>=1;}return r;}
static int invp(int a){return pw(a,P-2);}

// partition generator: perfect matchings of {0..n+1}
static void gp(vector<int>&av,vector<pair<int,int>>&c){
    if(av.empty()){parts.push_back(c);return;}
    int a=av[0];
    for(size_t bi=1;bi<av.size();++bi){
        int b=av[bi]; vector<int>nx;
        for(size_t i=1;i<av.size();++i) if((int)i!=(int)bi) nx.push_back(av[i]);
        c.push_back({a,b}); gp(nx,c); c.pop_back();
    }
}

typedef vector<pair<long long,int>> SVec;
static void svClean(SVec&v){
    sort(v.begin(),v.end()); SVec o;
    for(auto&pr:v){
        if(!o.empty()&&o.back().first==pr.first) o.back().second=ad(o.back().second,pr.second);
        else o.push_back(pr);
    }
    SVec o2; for(auto&pr:o) if(pr.second) o2.push_back(pr); v.swap(o2);
}

// ================= METHOD A : eigenbasis dim_C (byte-exact HOUDINI) =================
static long long eigen_dimC(int P0,int zeta){
    P=P0;
    auto Z=[&](long long e)->int{e%=m;if(e<0)e+=m;return pw(zeta,e);};
    vector<vector<int>> F(m, vector<int>(m,0));
    for(int jp=1;jp<m;jp++) for(int jq=1;jq<m;jq++){
        int s=0; for(int a=0;a<=m-2;a++){int sbb=0;for(int b=0;b<=a;b++)sbb=ad(sbb,Z(jq*b)); s=ad(s,ml(Z(jp*a),sbb));} F[jp][jq]=s;
    }
    vector<vector<pair<int,int>>> apOf(parts.size());
    for(size_t pi=0;pi<parts.size();++pi) for(auto&pr:parts[pi]){ if(pr.first==0||pr.second==0)continue; apOf[pi].push_back({pr.first-1,pr.second-1}); }
    long long survivors=0; vector<int> jv(NV);
    for(long long id=0; id<DIM; ++id){
        long long t=id; for(int v=0;v<NV;v++){ jv[v]=(int)(t%B)+1; t/=B; }
        bool allZero=true;
        for(size_t pi=0; pi<parts.size(); ++pi){ int prod=1; for(auto&ap:apOf[pi]){ prod=ml(prod,F[jv[ap.first]][jv[ap.second]]); if(!prod)break; } if(prod!=0){allZero=false;break;} }
        if(allZero) survivors++;
    }
    return survivors;
}
static bool findPrimeRoot(int mm,long long startBase,int&Pout,int&zetaOut){
    auto isprime=[](long long x){if(x<2)return false;for(long long i=2;i*i<=x;i++)if(x%i==0)return false;return true;};
    for(long long base=startBase;;base++){long long cand=base*(long long)mm+1;if(cand>2000000000LL)return false;if(!isprime(cand))continue;
        Pout=(int)cand;P=Pout;long long ph=P-1;vector<long long>fac;long long t=ph;for(long long p=2;p*p<=t;p++){if(t%p==0){fac.push_back(p);while(t%p==0)t/=p;}}if(t>1)fac.push_back(t);
        int g=2;for(;;g++){bool ok=true;for(long long f:fac)if(pw(g,ph/f)==1){ok=false;break;}if(ok)break;}zetaOut=pw(g,ph/mm);return true;}
}

// ================= METHOD B : MONOMIAL-basis TURBINE + SONICSTAR-FOLD =================
// rho(x,y) as a table of (exp_x, exp_y, coef) terms.  These are already in the
// monomial basis: rho(x,y) = sum_{a=0}^{m-2} x^a * sum_{b=0}^{a} y^b.
// Each term has exp_x = a, exp_y = b, coef = 1.  All exponents < B = m-1.
struct TTerm { int ea, eb; int cf; };
static vector<TTerm> rhoTfac;

static void buildRhoTfac(){
    rhoTfac.clear();
    for(int a=0; a<=m-2; a++)
        for(int b=0; b<=a; b++)
            rhoTfac.push_back({a, b, 1});
}

// Build rho_J in MONOMIAL basis via tensor product (disjoint variable pairs).
// Identical logic to STAR's buildRhoJ_U but using rhoTfac (no binomial change of basis).
static SVec buildRhoJ_T(const vector<pair<int,int>>& Pj){
    vector<pair<int,int>> ap;
    for(auto&pr:Pj){ if(pr.first==0||pr.second==0) continue; ap.push_back({pr.first-1,pr.second-1}); }
    SVec cur; cur.push_back({0LL,1});
    for(auto&a:ap){
        long long wA=powB[a.first], wB=powB[a.second];
        SVec nx; nx.reserve(cur.size()*rhoTfac.size());
        for(auto&t:cur){
            long long bid=t.first; int cf=t.second;
            for(auto&f:rhoTfac)
                nx.push_back({bid + (long long)f.ea*wA + (long long)f.eb*wB, ml(cf,f.cf)});
        }
        cur.swap(nx);
    }
    if(ap.empty()){cur.clear();cur.push_back({0LL,1});}
    svClean(cur); return cur;
}

// Shift by t_var in MONOMIAL basis with EXPLICIT PHI REDUCTION.
// t_v * (monomial with exp[var]=e):
//   if e+1 < B:  just increment exp[var] by 1.
//   if e+1 == B: t_v^B needs reduction. phi(t_v)=0 means
//     t_v^{m-1} = -(1 + t_v + ... + t_v^{m-2})  in any char p.
//     So the monomial with exp[var]=B-1 shifts to:
//       -(coef) * sum_{e=0}^{B-1} (monomial with exp[var]=e).
// NOTE: this is the ONLY difference from STAR. Everything else is byte-identical.
static SVec shiftVar_T(const SVec&v, int var){
    long long w = powB[var];
    SVec o; o.reserve(v.size() * 2);
    for(auto&pr : v){
        long long id = pr.first; int cf = pr.second;
        int e = (int)((id / w) % B);
        if(e + 1 < B){
            // simple shift: exp[var] increments by 1
            o.push_back({id + w, cf});
        } else {
            // e = B-1: t_v^B = -(1 + t_v + ... + t_v^{B-1})
            // base = id with exp[var] zeroed out
            long long base = id - (long long)e * w;
            int negcf = sb(0, cf);  // -cf mod P
            for(int ee = 0; ee < B; ee++)
                o.push_back({base + (long long)ee * w, negcf});
        }
    }
    svClean(o); return o;
}

// ---- SONICSTAR-FOLD reducer: BYTE-IDENTICAL from STAR ----
static int* HS_BUF=nullptr;
static char* HS_OCC=nullptr;
static int CFBITS=0;
static uint32_t CFMASK=0;

struct Red{
    unordered_map<uint32_t,int> pc;
    vector<uint8_t>  P_blob;
    vector<uint32_t> B_off;
    long long nz=0;
    vector<long long> heap;
    vector<long long> touchedList;
    Red(){ B_off.push_back(0); }
    static inline void putVarint(vector<uint8_t>&b,uint32_t v){
        while(v>=0x80){b.push_back((uint8_t)(v|0x80));v>>=7;} b.push_back((uint8_t)v);
    }
    inline void touch(long long col,int coef){
        if(!HS_OCC[col]){HS_OCC[col]=1;HS_BUF[col]=coef;heap.push_back(col);push_heap(heap.begin(),heap.end(),greater<long long>());touchedList.push_back(col);}
        else HS_BUF[col]=ad(HS_BUF[col],coef);
    }
    bool add(const SVec& vin){
        heap.clear(); touchedList.clear();
        for(auto&pr:vin) touch(pr.first,pr.second);
        bool created=false; long long newLead=-1;
        while(!heap.empty()){
            long long lc=heap.front();
            int c=HS_BUF[lc];
            if(c==0){pop_heap(heap.begin(),heap.end(),greater<long long>());heap.pop_back();continue;}
            auto it=pc.find((uint32_t)lc);
            if(it==pc.end()){newLead=lc;created=true;break;}
            int k=it->second; int f=c;
            const uint8_t* bp=&P_blob[B_off[k]]; const uint8_t* be=&P_blob[B_off[k+1]];
            long long col=0;
            while(bp<be){uint32_t g=0;int sh=0;uint8_t by;do{by=*bp++;g|=(uint32_t)(by&0x7F)<<sh;sh+=7;}while(by&0x80);
                col+=(long long)(g>>CFBITS);int pcf=(int)(g&CFMASK)+1;touch(col,sb(0,ml(f,pcf)));}
            pop_heap(heap.begin(),heap.end(),greater<long long>());heap.pop_back();
        }
        if(created){int iv=invp(HS_BUF[newLead]);
            sort(touchedList.begin(),touchedList.end());
            long long need=(long long)P_blob.size()+(long long)touchedList.size()*5;
            if((long long)P_blob.capacity()<need) P_blob.reserve(need+(64LL<<20));
            long long added=0,prev=0;
            for(long long col:touchedList){if(HS_BUF[col]){int v=ml(HS_BUF[col],iv);uint32_t payload=((uint32_t)(col-prev)<<CFBITS)|(uint32_t)(v-1);putVarint(P_blob,payload);prev=col;added++;}}
            B_off.push_back((uint32_t)P_blob.size());
            pc[(uint32_t)newLead]=(int)(B_off.size()-2); nz+=added;
        }
        for(long long col:touchedList){HS_BUF[col]=0;HS_OCC[col]=0;}
        return created;
    }
    long long rank()const{return(long long)B_off.size()-1;}
    long long bytes()const{return(long long)P_blob.capacity()+(long long)B_off.capacity()*4;}
    SVec rowAt(long long k)const{
        SVec s;const uint8_t*bp=&P_blob[B_off[k]];const uint8_t*be=&P_blob[B_off[k+1]];long long col=0;
        while(bp<be){uint32_t g=0;int sh=0;uint8_t by;do{by=*bp++;g|=(uint32_t)(by&0x7F)<<sh;sh+=7;}while(by&0x80);
            col+=(long long)(g>>CFBITS);int pcf=(int)(g&CFMASK)+1;s.push_back({col,pcf});}return s;
    }
};

static double now_s(){return(double)clock()/CLOCKS_PER_SEC;}

// TURBINE: per-partition monomial-basis closure -> shared echelon (SONICSTAR-FOLD).
static long long turbineRank(int p, long long& peak){
    P = p; buildRhoTfac();
    CFBITS=0;{int mx=p-2;while((1<<CFBITS)<=mx)CFBITS++;}CFMASK=(CFBITS?((1u<<CFBITS)-1):0u);
    {long long maxshift=(long long)(DIM)<<CFBITS;if(maxshift>=(1LL<<32)){fprintf(stderr,"  [ROSETTA] coef-embed overflow (DIM=%lld, CFBITS=%d) -- abort\n",DIM,CFBITS);return -1;}}
    Red R; peak=0; double t0=now_s(); double lastP=t0;
    fprintf(stderr,"  [ROSETTA start] streaming %zu partitions, char %d\n",parts.size(),p);
    for(size_t pi=0; pi<parts.size(); ++pi){
        // local monomial-basis closure of THIS partition
        Red local; local.add(buildRhoJ_T(parts[pi]));
        long long done=0;
        while(done < local.rank()){
            long long upto=local.rank();
            for(long long k=done; k<upto; ++k){
                SVec row=local.rowAt(k);
                for(int v=0; v<NV; ++v){
                    SVec s=shiftVar_T(row,v);
                    local.add(s);
                }
            }
            done=upto;
        }
        // fold local closure into shared echelon
        for(long long k=0; k<local.rank(); ++k){
            SVec v=local.rowAt(k); R.add(v);
            long long live=R.bytes()+local.bytes(); if(live>peak)peak=live;
        }
        long long live=R.bytes()+local.bytes(); if(live>peak)peak=live;
        if(now_s()-lastP>=5.0){
            lastP=now_s();
            fprintf(stderr,"  [ROSETTA flow] part=%zu/%zu rank=%lld echelon_nz=%lld peak_bytes=%lld(~%.2fGB) t=%.0fs\n",
                pi+1,parts.size(),R.rank(),R.nz,peak,peak/1e9,now_s()-t0);
        }
        if(peak>RAM_BUDGET_BYTES){fprintf(stderr,"  [ROSETTA GUARD] RAM hit part=%zu rank=%lld peak_bytes=%lld(~%.2fGB) -- NOT a math result\n",pi+1,R.rank(),peak,peak/1e9);return -1;}
        if(now_s()-t0>WALL){fprintf(stderr,"  [ROSETTA GUARD] wall hit\n");return -1;}
    }
    fprintf(stderr,"  [ROSETTA done] rank=%lld echelon_nz=%lld peak_bytes=%lld(~%.2fGB) t=%.0fs\n",R.rank(),R.nz,peak,peak/1e9,now_s()-t0);
    return R.rank();
}

int main(int argc,char**argv){
    if(argc<3){fprintf(stderr,"usage: %s n m [wall_sec]\n",argv[0]);return 1;}
    setvbuf(stderr,NULL,_IONBF,0);
    n=atoi(argv[1]); m=atoi(argv[2]); if(argc>=4)WALL=atof(argv[3]);
    d=n/2; NV=n+1; B=m-1; powB.assign(NV+1,1); for(int i=1;i<=NV;i++)powB[i]=powB[i-1]*B; DIM=powB[NV];
    vector<int>all;for(int i=0;i<n+2;i++)all.push_back(i);vector<pair<int,int>>c;gp(all,c);
    printf("================ ROSETTA STAR  n=%d m=%d  DIM=%lld  partitions=%zu ================\n",n,m,DIM,parts.size());
    printf("Author: Rafael Amichis Luengo (Madrid). Method: Degtyarev-Shimada (arXiv:1405.4683 S5).\n");
    printf("char-p: MONOMIAL-basis phi-reduction + TURBINE flow + SONICSTAR-FOLD dense-rebound fold.\n");
    printf("FIX: replaces Jordan-mould (u^{m-1}=0) with correct phi-reduction (t^{m-1}=-(1+...+t^{m-2})).\n");
    printf("     Jordan = correct when m=prime power. Phi-reduction = correct for ALL m.\n");
    fflush(stdout);

    HS_BUF=(int*)calloc((size_t)DIM,sizeof(int));
    HS_OCC=(char*)calloc((size_t)DIM,1);
    if(!HS_BUF||!HS_OCC){fprintf(stderr,"alloc fail for dense scratch (DIM=%lld)\n",DIM);return 3;}

    // ---- METHOD A: dim_C eigenbasis, cross-prime ----
    printf("\n[METHOD A] dim_C via eigenbasis, cross-prime (primes = 1 mod m):\n"); fflush(stdout);
    double tA0=now_s();
    long long dC=-1; int found=0; long long base=(1000000/m)+1; long long dCs[8]; int Ps[8];
    for(int k=0;k<5;k++){int Pk,zk;if(!findPrimeRoot(m,base,Pk,zk)){printf("   (no more primes)\n");break;}base=(Pk-1)/m+1;long long dk=eigen_dimC(Pk,zk);Ps[found]=Pk;dCs[found]=dk;found++;printf("   P=%d -> dim_C = %lld\n",Pk,dk);if(dC<0)dC=dk;}
    bool crossOK=true;for(int k=1;k<found;k++)if(dCs[k]!=dCs[0])crossOK=false;
    double tA=now_s()-tA0;
    printf("   cross-prime: %s   dim_C = %lld   [Method A time %.2f s over %d primes]\n",crossOK?"CONSISTENT":"!!! DISAGREE !!!",dC,tA,found);

    // ---- METHOD B: dim_Fp via TURBINE (MONOMIAL phi-reduction) ----
    vector<int> ps;{int mm=m;for(int p=2;(long long)p*p<=mm;p++){if(mm%p==0){ps.push_back(p);while(mm%p==0)mm/=p;}}if(mm>1)ps.push_back(mm);}
    printf("\n[METHOD B] dim_Fp via ROSETTA TURBINE (phi-reduction, primes dividing m:");for(int p:ps)printf(" %d",p);printf(")\n");fflush(stdout);

    bool aborted=false; vector<pair<int,long long>> dpv; vector<long long> peaks;
    for(size_t ip=0;ip<ps.size();++ip){int p=ps[ip];
        printf("\n  char %d : ROSETTA turbine + sonicstar-fold\n",p);fflush(stdout);
        long long peak=0;long long rP=turbineRank(p,peak);peaks.push_back(peak);
        if(rP<0){printf("  char %d ABORTED_BY_GUARD (peak=%lld ~%.2fGB) -- NOT a math result\n",p,peak,peak/1e9);aborted=true;break;}
        long long dF=DIM-rP;
        printf("  char %d COMPLETE: rank_p=%lld dim_F%d=%lld  PEAK bytes=%lld (~%.2f GB)\n",p,rP,p,dF,peak,peak/1e9);
        dpv.push_back({p,dF});
    }

    // ---- VERDICT ----
    printf("\n================ VERDICT ================\n");
    if(aborted){
        printf("dim_C = %lld (Method A, cross-prime %s).\n",dC,crossOK?"consistent":"DISAGREE");
        printf("dim_Fp INCOMPLETE: turbine hit guard. NOT a math result. VERDICT=ABORTED_BY_GUARD\n");
        free(HS_BUF);free(HS_OCC);return 2;
    }
    string verdict="PRIMITIVE";for(auto&pr:dpv)if(pr.second!=dC)verdict="TORSION";
    printf("dim_C  = %lld   (Method A eigenbasis, cross-prime)\n",dC);
    for(auto&pr:dpv)printf("dim_F%d = %lld%s\n",pr.first,pr.second,(pr.second!=dC?"   <-- DIFFERS":""));
    printf("VERDICT = %s\n",verdict.c_str());
    if(verdict=="PRIMITIVE")printf("=> L(X) primitive. Standard linear cycles GENERATE the integral Hodge lattice.\n");
    else{printf("=> TORSION (scar!=0). *** CANDIDATE BOMBAZO -- the muralla china ***\n");
         printf("   WARNING (D-HF-7): the scar is calibrated only on primitive controls. Before trusting\n");
         printf("   this TORSION, pass a synthetic positive-torsion control. Numbers from files only.\n");}
    free(HS_BUF);free(HS_OCC);
    return 0;
}
