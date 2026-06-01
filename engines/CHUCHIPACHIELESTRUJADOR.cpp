// ============================================================================
//  C H U C H I P A C H I   E L   E S T R U J A D O R
//  Integral Hodge Conjecture verifier for Fermat varieties, COMPOSITE degree m.
//  The full-cell closer: attacks ONE chosen prime's CRT blocks in isolation, so
//  the second prime of a composite m can be closed after the first is already done.
//
//  ------------------------------------------------------------------------
//  WHAT CHANGED FROM THE PRIOR ENGINE (the mute-segfault fix), and WHY:
//  The prior engine died with a SILENT segmentation fault on (4,15) char 3 at
//  R_rank=17880, peak 4.307 GB -- BELOW the 5.4 GB guard. The cause was not lack of
//  RAM: the per-row blob grew by std::vector's DOUBLING policy, so at ~4.3 GB the
//  next grow asked the OS for ~8.6 GB in a single shot and was refused BEFORE the
//  byte-counter (which only saw already-committed memory) could trip the guard.
//  A reactive guard cannot catch a reserve that dies during the reserve itself.
//  The cell FITS -- the closing curve (~0.27 GB / 1000 rank, 4.307 GB at 17880,
//  closing at 19920) projects ~4.85 GB, under the guard. The engine, not the
//  machine, was the wall.
//
//  THE FIX (two locks, Auditor-ratified):
//   (1) PREDICTIVE GUARD: before every blob grow, project (grown blob + B_off +
//       all other live structures) and compare to the HARD 5.4 GB guard. If it
//       would cross, abort CLEAN via a flag -- never call the reserve, never
//       segfault mute. The guard now sees what is ABOUT to be asked, not only
//       what is already held.
//   (2) CONTROLLED GROWTH: the blob grows in a linear +1 GB increment over real
//       need, never doubling. No speculative giant malloc, no mid-block 2x spike.
//  Together: the cell closes if it fits (it does), and if a future cell does NOT
//  fit, the engine reports the exact RAM it would have needed and stops clean.
//
//  ------------------------------------------------------------------------
//  Engine        : CHUCHIPACHI
//  Author        : Rafael Amichis Luengo (Madrid)
//  Method origin : Degtyarev-Shimada computational criterion (arXiv:1405.4683 S5)
//  Hardware      : MacBook Air M2 (2022), 8 GB, single thread, 25% CPU.
//  Arithmetic    : exact modular over F_p. NO floating point. NO extension-field
//                  arithmetic (CRT idempotents have F_p coefficients).
//  ------------------------------------------------------------------------
//  WHY THIS ENGINE EXISTS (honest framing):
//
//  For composite m = p*q, a full (n,m) verdict needs BOTH primes to agree with
//  dim_C. The two primes have DIFFERENT all-B block sizes (dimB differs per prime),
//  so one prime can fit on 8 GB while the other is heavier. The prior probe engine
//  attacked the LARGEST prime and STOPPED by design, leaving the second prime
//  uncomputed -- which is why the smaller-prime half of some composite cells was
//  recorded as "not run", NOT "RAM-bound". CHUCHIPACHI closes that gap: a --char=P
//  selector attacks exactly one prime's blocks, so the remaining prime of a
//  composite cell can be run in its own job, with the full RAM budget to itself.
//
//  For (4,15) = 3*5 specifically: char 5 is ALREADY closed PRIMITIVE (dim_F5 =
//  dim_C = 504,924). The only thing missing for a COMPLETE verdict is char 3.
//  The char-3 all-B block is dimB^(NV) = 12^5 = 248,832 -- the SAME size as the
//  all-B block (4,14) closed clean at peak ~2.22 GB. So char 3 of (4,15) is
//  (4,14)-class work: the block FITS. The earlier "char 3 RAM-bound" line came
//  from attacking the monolith / iterating ascending and dying on the wrong block,
//  not from this CRT-split all-B block. CHUCHIPACHI runs `--char=3` directly.
//
//  THE LEVER (the CRT block split -- Rafa's LETHAL DUAL mechanism):
//    phi(t) = 1 + ... + t^{m-1} = (t-1)^a * g(t)^b  over F_p, the two factors
//    coprime, so F_p[t]/phi = A x B by CRT. The shift respects the split; the
//    (n+1)-fold tensor space breaks into 2^{n+1} independent blocks, reduced ONE
//    AT A TIME and released. RAM peak = the largest single block, not the whole
//    closure. The all-B block (mask = all ones) is the RAM-determining monster and
//    is a LOCAL ring (g irreducible -> no further idempotents), so it does not
//    split further: dimB^(NV) is the floor, attacked directly with the inside-block
//    RAM guard + heartbeat.
//
//  Note on char-3 layout for m=15: dimA = p^e - 1 = 3 - 1 = 2 (NOT 1), dimB = 12.
//  The dimA=2 only enlarges the blocks that CONTAIN an A-factor (which are small);
//  the all-B block is dimB^(NV) = 12^5 regardless of dimA. So the RAM-driving block
//  is identical in size to (4,14) char 2's all-B block. The CRT idempotent solver
//  computes a and reports it; no special-casing of dimA is needed.
//
//  CORRECTNESS GATE (every run): the per-block ranks sum to the cell's closing
//  rank. The --gate mode checks known cells byte-exact before any real target.
//
//  ------------------------------------------------------------------------
//  BUILD (Mac, Apple clang ok -- NO quad, NO bits/stdc++.h):
//    g++ -O3 -march=native -std=c++17 -funroll-loops CHUCHIPACHI.cpp -o CHUCHIPACHI
//  GATES (run these FIRST, must match byte-exact before trusting any real cell):
//    ./CHUCHIPACHI 4 4 --char=2      -> char 2 rank 141  dim 102   PRIMITIVE
//    ./CHUCHIPACHI 4 6 --char=3      -> char 3 rank 1001 dim 2124  (the char-3 gate)
//    ./CHUCHIPACHI 8 3 --char=3      -> char 3 rank 252  dim 260
//  RUN (the target):
//    cd ~/Downloads && caffeinate -dims taskpolicy -c utility ./CHUCHIPACHI 4 15 --char=3 2>&1 | tee CHUCHIPACHI_4_15_char3_run1.log
//  ARGS: n m [--char=P] [--wall=SEC]
//    --char=P : attack ONLY prime P (must divide m). If omitted, attacks all primes
//               of m (largest first), each in turn -- a full cell in one job.
// ============================================================================
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <algorithm>
#include <ctime>
#include <string>
#include <cstring>
using namespace std;

static int n,m,d,NV,B,P; static long long DIM; static vector<long long> powB;
static vector<vector<pair<int,int>>> parts;
static long long RAM_BUDGET_BYTES = 5400000000LL; // 5.4 GB hard guard (no swap, ever)
static long long RAM_SOFT_BYTES   = 5000000000LL; // 5.0 GB soft guard: abort CLEAN with a
                                                  // 400 MB margin so we stop BEFORE the OS
                                                  // can segfault us mid-allocation. The guard
                                                  // lives INSIDE the turbine, line by line.
static double WALL = 1000000.0;
// CHUCHIPACHIELESTRUJADOR predictive-guard globals:
//  GUARD_OTHER_LIVE = bytes live OUTSIDE the Red currently being grown (the block echelon R
//                     plus the local turbine), set by dualRank before each add() so the guard
//                     check inside add() accounts for ALL live RAM, not just this one blob.
//  GUARD_TRIPPED    = >0 if the predictive guard refused a reserve (clean-abort signal).
static long long GUARD_OTHER_LIVE = 0;
static long long GUARD_TRIPPED = 0;

static inline int ad(int a,int b){a+=b;if(a>=P)a-=P;return a;}
static inline int sb(int a,int b){a-=b;if(a<0)a+=P;return a;}
static inline int ml(long long a,long long b){return(int)((a*b)%P);}
static int pw(int a,long long e){int r=1;a%=P;if(a<0)a+=P;while(e){if(e&1)r=ml(r,a);a=ml(a,a);e>>=1;}return r;}
static int invp(int a){return pw(a,P-2);}

// ---------- partition generator: perfect matchings of {0..n+1} ----------
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

// ---------- ideal construction (byte-exact monomial lineage) ----------
struct TTerm{int ea,eb,cf;};
static vector<TTerm> rhoTfac;
static void buildRhoTfac(){
    rhoTfac.clear();
    for(int a=0;a<=m-2;a++) for(int b=0;b<=a;b++) rhoTfac.push_back({a,b,1});
}
static SVec buildRhoJ_T(const vector<pair<int,int>>& Pj){
    vector<pair<int,int>> ap;
    for(auto&pr:Pj){if(pr.first==0||pr.second==0)continue;ap.push_back({pr.first-1,pr.second-1});}
    SVec cur; cur.push_back({0LL,1});
    for(auto&a:ap){
        long long wA=powB[a.first],wB=powB[a.second];
        SVec nx; nx.reserve(cur.size()*rhoTfac.size());
        for(auto&t:cur){long long bid=t.first;int cf=t.second;
            for(auto&f:rhoTfac) nx.push_back({bid+(long long)f.ea*wA+(long long)f.eb*wB,ml(cf,f.cf)});}
        cur.swap(nx);
    }
    if(ap.empty()){cur.clear();cur.push_back({0LL,1});}
    svClean(cur); return cur;
}
static SVec shiftVar_T(const SVec&v,int var){
    long long w=powB[var]; SVec o; o.reserve(v.size()*2);
    for(auto&pr:v){long long id=pr.first;int cf=pr.second;int e=(int)((id/w)%B);
        if(e+1<B){o.push_back({id+w,cf});}
        else{long long base=id-(long long)e*w;int negcf=sb(0,cf);
            for(int ee=0;ee<B;ee++)o.push_back({base+(long long)ee*w,negcf});}}
    svClean(o); return o;
}

// ---------- polynomial arithmetic over F_p (for CRT idempotents) ----------
typedef vector<int> Poly;
static void ptrim(Poly&a){while(a.size()>1&&a.back()==0)a.pop_back();}
static Poly pmul(const Poly&a,const Poly&b){
    Poly r(a.size()+b.size()-1,0);
    for(size_t i=0;i<a.size();i++)if(a[i])for(size_t j=0;j<b.size();j++)if(b[j])r[i+j]=ad(r[i+j],ml(a[i],b[j]));
    ptrim(r);return r;
}
static void pdivmod(Poly a,const Poly&b,Poly&q,Poly&r){
    int db=(int)b.size()-1; int lb=invp(b[db]);
    q.assign(a.size()>=b.size()?a.size()-b.size()+1:1,0);
    for(int i=(int)a.size()-1;i>=db;--i){
        if(a[i]==0)continue; int coef=ml(a[i],lb); q[i-db]=coef;
        for(int j=0;j<=db;j++) a[i-db+j]=sb(a[i-db+j],ml(coef,b[j]));
    }
    a.resize(db>0?db:1); ptrim(a); r=a; ptrim(q);
}
static Poly pmod(const Poly&a,const Poly&b){Poly q,r;pdivmod(a,b,q,r);return r;}
static Poly pegcd(Poly a,Poly b,Poly&u,Poly&v){
    Poly u0={1},u1={0},v0={0},v1={1};
    while(!(b.size()==1&&b[0]==0)){
        Poly q,r; pdivmod(a,b,q,r); a=b;b=r;
        Poly nu=u0;{Poly t=pmul(q,u1);if(t.size()<nu.size())t.resize(nu.size(),0);else nu.resize(t.size(),0);for(size_t i=0;i<nu.size();i++)nu[i]=sb(nu[i],t[i]);}
        u0=u1;u1=nu;ptrim(u1);
        Poly nv=v0;{Poly t=pmul(q,v1);if(t.size()<nv.size())t.resize(nv.size(),0);else nv.resize(t.size(),0);for(size_t i=0;i<nv.size();i++)nv[i]=sb(nv[i],t[i]);}
        v0=v1;v1=nv;ptrim(v1);
    }
    u=u0;v=v0;return a;
}
// e_A (=1 mod (t-1)^a, =0 mod g^b) and e_B, as length-B coef vectors in F_p.
// Returns dimA (= a) for reporting. Aborts if idempotent identities fail.
static int crt_idempotents(vector<int>&eA,vector<int>&eB){
    Poly Phi(m,1);                                  // 1 + t + ... + t^{m-1}
    long long pk=1; {int mm=m; while(mm%P==0){pk*=P;mm/=P;}}
    int a=(int)pk-1;                                // multiplicity of (t-1) in phi over F_p
    Poly tm1={sb(0,1),1};                           // (t-1)
    Poly MA={1}; for(int i=0;i<a;i++)MA=pmul(MA,tm1);
    Poly q,r; pdivmod(Phi,MA,q,r); Poly MB=q;        // MB = phi / (t-1)^a  (exact)
    Poly u,v; Poly g=pegcd(MA,MB,u,v);
    int gi=invp(g[0]); for(auto&x:u)x=ml(x,gi); for(auto&x:v)x=ml(x,gi);
    Poly EA=pmod(pmul(v,MB),Phi), EB=pmod(pmul(u,MA),Phi);
    eA.assign(B,0); eB.assign(B,0);
    for(size_t i=0;i<EA.size()&&i<(size_t)B;i++)eA[i]=EA[i];
    for(size_t i=0;i<EB.size()&&i<(size_t)B;i++)eB[i]=EB[i];
    Poly sum(B,0); for(int i=0;i<B;i++)sum[i]=ad(eA[i],eB[i]);
    bool ok=(sum[0]==1); for(int i=1;i<B;i++) if(sum[i]!=0) ok=false;
    Poly prod=pmod(pmul(EA,EB),Phi); for(int x:prod) if(x!=0) ok=false;
    Poly sq=pmod(pmul(EA,EA),Phi); for(int i=0;i<B;i++){int s=(i<(int)sq.size()?sq[i]:0); if(sb(s,eA[i])!=0)ok=false;}
    fprintf(stderr,"  [CRT] char %d : phi splits  dimA=%d  dimB=%d  idempotents %s\n",P,a,B-a,ok?"VALID":"FAILED");
    if(!ok){fprintf(stderr,"  [CRT] idempotent identities failed -- run VOID\n");exit(2);}
    return a;
}
// multiply tensor vector by polynomial 'poly' (length B) in variable var
static SVec mulPolyVar(const SVec&V,const vector<int>&poly,int var){
    SVec acc; SVec cur=V;
    for(int j=0;j<B;j++){
        if(poly[j]){ for(auto&pr:cur) acc.push_back({pr.first, ml(pr.second,poly[j])}); }
        if(j+1<B) cur=shiftVar_T(cur,var);
    }
    svClean(acc); return acc;
}
// project vector onto block 'mask' (bit v: 0=A, 1=B) by applying e_{s_v} per variable
static SVec projectBlock(const SVec&V,int mask,const vector<int>&eA,const vector<int>&eB){
    SVec cur=V;
    for(int v=0;v<NV;v++){ cur=mulPolyVar(cur,((mask>>v)&1)?eB:eA,v); if(cur.empty())break; }
    return cur;
}

// ================= METHOD A : eigenbasis dim_C (byte-exact lineage) =================
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

// ---------- SONICSTAR-FOLD varint reducer (byte-identical monomial lineage) ----------
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
            if((long long)P_blob.capacity()<need){
                // PREDICTIVE GUARD (CHUCHIPACHIELESTRUJADOR fix): std::vector::reserve grows by
                // DOUBLING -- at 4.3 GB it would ask the OS for ~8.6 GB in one shot and segfault
                // mute before the byte-counter saw it. Two fixes together:
                //  (1) grow in a CONTROLLED 1 GB increment over the real 'need', never doubling;
                //  (2) check projected live RAM (this blob grown + B_off + everything else live)
                //      against the HARD guard BEFORE calling reserve; if it would cross, abort
                //      CLEAN via GUARD_TRIPPED instead of dying.
                // grow proportionally but CAP the increment so the monster never doubles in one
                // shot (the doubling is what segfaulted) and small blocks are not inflated by a
                // flat +1 GB. Increment = clamp(need/4, 64 MB, 1 GB) over real need.
                long long inc = need/4; if(inc < (64LL<<20)) inc = (64LL<<20); if(inc > (1LL<<30)) inc = (1LL<<30);
                long long grow = need + inc;
                long long projected_live = grow + (long long)B_off.capacity()*4 + GUARD_OTHER_LIVE;
                if(projected_live > RAM_BUDGET_BYTES){
                    GUARD_TRIPPED = projected_live;   // signal clean abort to dualRank
                    return false;
                }
                P_blob.reserve((size_t)grow);
            }
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

// Per-prime char-p rank via CRT block split. Each block reduced alone & released.
// Returns total rank (sum over blocks) or -1 on guard/wall abort.
static long long dualRank(int p, long long& peak, long long closingTarget){
    P=p; buildRhoTfac();
    CFBITS=0;{int mx=p-2;while((1<<CFBITS)<=mx)CFBITS++;}CFMASK=(CFBITS?((1u<<CFBITS)-1):0u);
    {long long maxshift=(long long)(DIM)<<CFBITS;if(maxshift>=(1LL<<32)){fprintf(stderr,"  [LDE] coef-embed overflow (DIM=%lld, CFBITS=%d)\n",DIM,CFBITS);return -1;}}
    vector<int> eA,eB; crt_idempotents(eA,eB);

    int nblk = 1<<NV;
    long long rank_total=0; peak=0;
    long long biggest_block_bytes=0; int biggest_mask=-1; long long biggest_block_rank=0;
    double t0=now_s(), lastP=t0;
    fprintf(stderr,"  [LDE start] char %d : %d CRT blocks, sequential (peak = largest single block)\n",p,nblk);

    for(int mask=0; mask<nblk; ++mask){
        // build projected seeds for this block (one per partition)
        vector<SVec> seeds; seeds.reserve(parts.size());
        for(auto&Pj:parts){ SVec gseed=projectBlock(buildRhoJ_T(Pj),mask,eA,eB); if(!gseed.empty())seeds.push_back(gseed); }
        if(seeds.empty()) continue;

        Red R; // echelon for THIS block only
        // CHUCHIPACHIELESTRUJADOR candado 1B (corrected, self-audited): do NOT speculatively
        // reserve ~5 GB up front for the monster block -- a single giant malloc with no data yet
        // can itself fail. Instead the blob grows in CONTROLLED 1 GB increments (see add(): the
        // grow step is capped, not a blind doubling), each one screened by the predictive guard
        // BEFORE the reserve. That kills both the mute segfault AND the speculative-giant risk.
        // turbine flow within the block: per-seed local closure, fold into block echelon.
        // The guard lives INSIDE the turbine (line-by-line), not just between seeds, so the
        // monster all-B block (one heavy seed whose internal closure grows large) is checked
        // against a SOFT budget (margin below the hard 5.4 GB) and aborts CLEAN before macOS
        // can kill us. The heartbeat also beats INSIDE the monster block so it is never silent.
        for(auto&seed:seeds){
            Red local; local.add(seed);
            long long done=0;
            while(done<local.rank()){
                long long upto=local.rank();
                for(long long k=done;k<upto;++k){
                    SVec row=local.rowAt(k);
                    for(int v=0;v<NV;++v){
                        GUARD_OTHER_LIVE = R.bytes();           // live RAM outside 'local'
                        SVec s=shiftVar_T(row,v); local.add(s);
                        if(GUARD_TRIPPED){
                            fprintf(stderr,"  [GUARD] PREDICTIVE abort inside block #%d/%d (turbine): a P_blob grow would reach "
                                "~%.3fGB > hard 5.4GB. rank_so_far=%lld. ABORT CLEAN before reserve (NOT a math result, NOT a segfault).\n",
                                mask+1,nblk,GUARD_TRIPPED/1e9,rank_total+R.rank());
                            return -1;
                        }
                        long long live=R.bytes()+local.bytes(); if(live>peak)peak=live;
                        if(peak>RAM_SOFT_BYTES){
                            fprintf(stderr,"  [GUARD] RAM soft-limit inside block #%d/%d : peak=%lld(~%.3fGB) "
                                "margin below hard 5.4GB. rank_so_far=%lld. ABORT CLEAN (NOT a math result).\n",
                                mask+1,nblk,peak,peak/1e9,rank_total+R.rank());
                            return -1;
                        }
                        if(now_s()-t0>WALL){fprintf(stderr,"  [GUARD] wall hit inside block #%d\n",mask+1);return -1;}
                    }
                }
                done=upto;
                // live heartbeat INSIDE the monster block
                if(now_s()-lastP>=5.0){
                    lastP=now_s();
                    long long live=R.bytes()+local.bytes();
                    fprintf(stderr,"  [LDE flow] block=%d/%d (turbine) local_rank=%lld R_rank=%lld rank_total=%lld/%lld live=%lld(~%.3fGB) peak=%lld(~%.3fGB) t=%.0fs\n",
                        mask+1,nblk,local.rank(),R.rank(),rank_total,closingTarget,live,live/1e9,peak,peak/1e9,now_s()-t0);
                }
            }
            for(long long k=0;k<local.rank();++k){
                SVec vv=local.rowAt(k);
                GUARD_OTHER_LIVE = local.bytes();       // live RAM outside 'R'
                R.add(vv);
                if(GUARD_TRIPPED){
                    fprintf(stderr,"  [GUARD] PREDICTIVE abort folding block #%d/%d : a P_blob grow would reach "
                        "~%.3fGB > hard 5.4GB. ABORT CLEAN before reserve (NOT a math result, NOT a segfault).\n",
                        mask+1,nblk,GUARD_TRIPPED/1e9);
                    return -1;
                }
                long long live=R.bytes()+local.bytes(); if(live>peak)peak=live;
                if(peak>RAM_SOFT_BYTES){
                    fprintf(stderr,"  [GUARD] RAM soft-limit folding block #%d/%d : peak=%lld(~%.3fGB). ABORT CLEAN (NOT a math result).\n",
                        mask+1,nblk,peak,peak/1e9);
                    return -1;
                }
            }
            long long live=R.bytes()+local.bytes(); if(live>peak)peak=live;
            if(now_s()-t0>WALL){fprintf(stderr,"  [GUARD] wall hit\n");return -1;}
        }
        long long rb=R.bytes();
        if(rb>biggest_block_bytes){biggest_block_bytes=rb;biggest_mask=mask;biggest_block_rank=R.rank();}
        rank_total+=R.rank();
        if(now_s()-lastP>=5.0){
            lastP=now_s();
            fprintf(stderr,"  [LDE flow] block=%d/%d rank(block)=%lld rank_total=%lld/%lld block_bytes=%lld(~%.3fGB) peak=%lld(~%.3fGB) t=%.0fs\n",
                mask+1,nblk,R.rank(),rank_total,closingTarget,rb,rb/1e9,peak,peak/1e9,now_s()-t0);
        }
        // R destroyed here -> block memory released before next block
    }
    fprintf(stderr,"  [LDE done] char %d rank_total=%lld peak=%lld(~%.3fGB) biggest_block=#%d rank=%lld (~%.3fGB) t=%.0fs\n",
        p,rank_total,peak,peak/1e9,biggest_mask,biggest_block_rank,biggest_block_bytes/1e9,now_s()-t0);
    return rank_total;
}

// ---------- shared setup: dims, partitions ----------
static void setupCell(int nn,int mm){
    n=nn;m=mm;NV=n+1;B=m-1;d=m-1;
    DIM=1;for(int i=0;i<NV;i++)DIM*= (long long)B;
    powB.assign(NV,1);for(int i=1;i<NV;i++)powB[i]=powB[i-1]*B;
    parts.clear();{vector<int>av;for(int i=0;i<=n+1;i++)av.push_back(i);vector<pair<int,int>>c0;gp(av,c0);}
    long long need=(DIM+16);
    HS_BUF=(int*)malloc(sizeof(int)*need); HS_OCC=(char*)malloc(sizeof(char)*need);
    memset(HS_OCC,0,sizeof(char)*need);
}

// ---------- prime list of m (largest first) ----------
static vector<int> primesOf(int mm){
    vector<int> ps;int x=mm;for(int p=2;(long long)p*p<=x;p++){if(x%p==0){ps.push_back(p);while(x%p==0)x/=p;}}if(x>1)ps.push_back(x);
    sort(ps.rbegin(),ps.rend());return ps;
}

// ---------- known gate table: (n,m,char) -> (closing rank, dim_Fp) ----------
static bool gateExpect(int nn,int mm,int p,long long&erank,long long&edim){
    struct G{int n,m,p;long long r,d;};
    static const G T[]={
        {4,4,2, 141, 102},
        {4,6,3, 1001, 2124},
        {4,6,2, 1001, 2124},
        {8,3,3, 252, 260},
        {6,5,5, 4900, 11484},
        {6,6,2, 18733, 59392},
        {6,6,3, 18733, 59392},
    };
    for(auto&g:T) if(g.n==nn&&g.m==mm&&g.p==p){erank=g.r;edim=g.d;return true;}
    return false;
}

int main(int argc,char**argv){
    if(argc<3){fprintf(stderr,"usage: %s n m [--char=P] [--wall=SEC] [--gate]\n",argv[0]);return 1;}
    int nn=atoi(argv[1]), mm=atoi(argv[2]);
    int onlyChar=0; bool gateMode=false;
    for(int i=3;i<argc;i++){
        if(!strncmp(argv[i],"--char=",7)) onlyChar=atoi(argv[i]+7);
        else if(!strncmp(argv[i],"--wall=",7)) WALL=atof(argv[i]+7);
        else if(!strcmp(argv[i],"--gate")) gateMode=true;
        else if(argv[i][0]!='-') WALL=atof(argv[i]); // legacy positional wall_sec
    }
    setupCell(nn,mm);

    printf("================ CHUCHIPACHI  n=%d m=%d  DIM=%lld  partitions=%zu ================\n",n,m,DIM,parts.size());
    fflush(stdout);

    // ---- which primes to attack ----
    vector<int> allp=primesOf(m);
    vector<int> ps;
    if(onlyChar){
        bool divides=false; for(int p:allp) if(p==onlyChar) divides=true;
        if(!divides){printf("ERROR: --char=%d does not divide m=%d. primes of m:",onlyChar,m);for(int p:allp)printf(" %d",p);printf("\n");free(HS_BUF);free(HS_OCC);return 1;}
        ps.push_back(onlyChar);
        printf("[CHAR SELECTOR] attacking ONLY char %d (of m=%d). Other primes need their own run for a full verdict.\n",onlyChar,m);
    } else {
        ps=allp;
        printf("[CHAR SELECTOR] no --char given: attacking ALL primes of m (largest first):");for(int p:ps)printf(" %d",p);printf("\n");
    }
    fflush(stdout);

    // ---- METHOD A: dim_C via eigenbasis, cross-prime ----
    double tA0=now_s();
    long long dC=-1; int found=0; int Ps[8]; long long dCs[8]; long long base=1;
    for(int k=0;k<5;k++){int Pk,zk;if(!findPrimeRoot(m,base,Pk,zk)){printf("   (no more primes)\n");break;}base=(Pk-1)/m+1;long long dk=eigen_dimC(Pk,zk);Ps[found]=Pk;dCs[found]=dk;found++;printf("   P=%d -> dim_C = %lld\n",Pk,dk);if(dC<0)dC=dk;}
    bool crossOK=true;for(int k=1;k<found;k++)if(dCs[k]!=dCs[0])crossOK=false;
    printf("   cross-prime: %s   dim_C = %lld   [%.2f s over %d primes]\n",crossOK?"CONSISTENT":"!!! DISAGREE !!!",dC,now_s()-tA0,found);
    fflush(stdout);

    // ---- METHOD B: dim_Fp via CRT block split, for each selected prime ----
    printf("\n[METHOD B] dim_Fp via CRT block split (LETHAL DUAL lever), primes:");for(int p:ps)printf(" %d",p);printf("\n");fflush(stdout);

    bool aborted=false; vector<pair<int,long long>> dpv;
    long long closingTarget = DIM - dC;
    for(int p:ps){
        printf("\n  char %d : CRT block split\n",p);
        printf("  [TARGET] dim_C = %lld  ->  closing rank to hit = %lld  (= DIM - dim_C). char %d PRIMITIVE-half iff rank_total == this.\n",dC,closingTarget,p);
        fflush(stdout);
        long long peak=0; long long rP=dualRank(p,peak,closingTarget);
        if(rP<0){printf("  char %d ABORTED_BY_GUARD (peak=%lld ~%.2fGB) -- NOT a math result\n",p,peak,peak/1e9);aborted=true;break;}
        long long dF=DIM-rP;
        // gate check if known
        long long erank,edim; bool known=gateExpect(n,m,p,erank,edim);
        if(known){
            bool pass=(rP==erank && dF==edim);
            printf("  char %d COMPLETE: rank_p=%lld dim_F%d=%lld  PEAK ~%.3f GB  [GATE %s vs rank=%lld dim=%lld]\n",
                p,rP,p,dF,peak/1e9,pass?"PASS":"FAIL <<<",erank,edim);
            if(!pass && gateMode){printf("  GATE FAILED -- run VOID, nothing trustworthy.\n");free(HS_BUF);free(HS_OCC);return 3;}
        } else {
            printf("  char %d COMPLETE: rank_p=%lld dim_F%d=%lld  PEAK ~%.3f GB\n",p,rP,p,dF,peak/1e9);
        }
        dpv.push_back({p,dF});
        fflush(stdout);
    }

    // ---- VERDICT ----
    printf("\n================ VERDICT ================\n");
    if(aborted){
        printf("dim_C = %lld (Method A, cross-prime %s).\n",dC,crossOK?"consistent":"DISAGREE");
        printf("dim_Fp INCOMPLETE: hit guard. NOT a math result. VERDICT=ABORTED_BY_GUARD\n");
        free(HS_BUF);free(HS_OCC);return 2;
    }
    printf("dim_C  = %lld   (Method A eigenbasis, cross-prime)\n",dC);
    string verdict="PRIMITIVE";for(auto&pr:dpv)if(pr.second!=dC)verdict="TORSION";
    for(auto&pr:dpv)printf("dim_F%d = %lld%s\n",pr.first,pr.second,(pr.second!=dC?"   <-- DIFFERS":""));

    bool partial = (ps.size() < allp.size());
    if(partial){
        int probed = dpv.empty()?-1:dpv[0].first;
        printf("VERDICT (char %d HALF) = %s\n", probed, verdict.c_str());
        if(verdict=="PRIMITIVE"){
            printf("=> char %d half: dim_F%d == dim_C. This characteristic is PRIMITIVE and FITS on 8 GB.\n",probed,probed);
            printf("=> (n=%d,m=%d) full verdict needs the remaining prime(s):",n,m);
            for(int p:allp){bool done=false;for(auto&pr:dpv)if(pr.first==p)done=true;if(!done)printf(" %d",p);}printf("\n");
        } else {
            printf("=> char %d half DIFFERS from dim_C. CANDIDATE chuchipachi (torsion) -- re-verify before any claim (D-HF-7):\n",probed);
            printf("   (a) re-run byte-exact (rule out transient); (b) independent reduction order; (c) synthetic positive-torsion control.\n");
        }
    } else {
        printf("VERDICT = %s\n",verdict.c_str());
        if(verdict=="PRIMITIVE")printf("=> L(X) primitive. Standard linear cycles GENERATE the integral Hodge lattice.\n");
        else{printf("=> TORSION (scar!=0). *** CANDIDATE CHUCHIPACHI -- counterexample to DS Conjecture 1.2 ***\n");
             printf("   WARNING (D-HF-7): before trusting, re-verify with an independent method + synthetic positive-torsion control.\n");}
    }
    free(HS_BUF);free(HS_OCC);
    return 0;
}
