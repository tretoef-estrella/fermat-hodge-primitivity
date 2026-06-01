// ============================================================================
//  C H U C H I P A C H I B A N G B A N G
//  Integral Hodge Conjecture verifier for Fermat varieties, COMPOSITE degree m,
//  with a BLOCK-BASIS DUMP for the DS eq. 4.5 isomorphism check (Frente 1).
//
//  ------------------------------------------------------------------------
//  Engine        : CHUCHIPACHIBANGBANG
//  Author        : Rafael Amichis Luengo (Madrid)
//  Method origin : Degtyarev-Shimada computational criterion (arXiv:1405.4683 S5)
//  Hardware      : MacBook Air M2 (2022), 8 GB, single thread, 25% CPU.
//  Arithmetic    : exact modular over F_p. NO floating point. NO extension-field
//                  arithmetic (CRT idempotents have F_p coefficients).
//  ------------------------------------------------------------------------
//  THE LEVER  (the CRT block split -- Rafa's LETHAL DUAL mechanism):
//    phi(t) = 1 + ... + t^{m-1} = (t-1)^a * g(t)^b  over F_p, the two factors
//    coprime, so F_p[t]/phi = A x B by CRT. The shift respects the split; the
//    (n+1)-fold tensor space breaks into 2^{n+1} independent blocks, reduced ONE
//    AT A TIME and released. RAM peak = the largest single block, not the whole
//    closure. Each block carries a CRT mask (bit v: 0 = variable v in the (t-1)
//    factor A, 1 = variable v in the g(t) factor B).
//
//  THE NEW INSTRUMENT  (this engine's reason to exist -- the basis dump):
//    The recursive block decomposition (THE_BLOCK_DECOMPOSITION) validated, out
//    of sample, that each block's rank is a product of two DS recursion ladders.
//    The open residual is to PROVE the per-block value law -- specifically that
//    the CRT idempotent cut equals the DS sec.17 coordinate-zeroing cut, i.e.
//    that our block is DS's tensor factor C_{J(2s)}(2s) (x) S(s,d), not merely an
//    object of equal rank. To attack that with pen and paper one needs the actual
//    BASIS of a single block -- the generators the engine materializes inside it,
//    decoded to monomial exponents -- to map against DS's R_J in eq. 4.5.
//
//    --dump-basis-mask=N  prints, for the one chosen CRT block N: a header
//    (rank, dimA, dimB, the head/tail variable split), and every echelon row as
//    a list of monomials (e_1,...,e_NV)*coef. The exponents are RAW tensor
//    indices in base B (0..B-1) -- the engine's own materialized basis, NOT
//    pre-massaged by any DS relation. The DS variable identification
//    t_{j_nu} = t_{k_nu}^{m-1} (eq. 4.5) is applied BY HAND in the proof, in the
//    open, so the comparison against DS is not circular: the engine emits the raw
//    truth; the theorem does the work of identifying the spaces. Contaminating
//    the dump with the DS relation would make "block matches DS" a tautology.
//
//    The dump is read-only on the reduced echelon R (rowAt is const; no mutation
//    of R, peak, or seeds), inserted only after the block is closed and counted.
//    With --dump-basis-mask=-1 (default) the engine is byte-identical to the
//    plain closer: same per-block ranks, same verdict, same gate values.
//  ------------------------------------------------------------------------
//  CORRECTNESS GATE (every run): per-block ranks sum to the cell's closing rank.
//  The --gate mode checks known cells byte-exact before any real target.
//
//  BUILD (Mac):
//    g++-15 -O3 -march=native -std=c++17 -funroll-loops CHUCHIPACHIBANGBANG.cpp -o CHUCHIPACHIBANGBANG
//  GATES (run FIRST, must match byte-exact before trusting any dump):
//    ./CHUCHIPACHIBANGBANG 4 4 --char=2   -> char 2 rank 141  dim 102   PRIMITIVE
//    ./CHUCHIPACHIBANGBANG 4 6 --char=2   -> char 2 rank 1001 dim 2124
//  BASIS DUMP (the Frente 1 instrument; tiny -- (4,6) char 2 closes in seconds):
//    head/tail block (popcount 3, head AND tail coexist -- the meat of the iso):
//      ./CHUCHIPACHIBANGBANG 4 6 --char=2 --dump-basis-mask=7  2>&1 | tee BANGBANG_4_6_c2_mask7_basis.log
//    all-B block (popcount 5, format gate, pure tail):
//      ./CHUCHIPACHIBANGBANG 4 6 --char=2 --dump-basis-mask=31 2>&1 | tee BANGBANG_4_6_c2_mask31_basis.log
//  ARGS: n m [--char=P] [--wall=SEC] [--gate] [--dump-blocks] [--dump-basis-mask=N]
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
static bool DUMP_BLOCKS = false; // print one line per CRT block (mask, popcount, rank) for the popcount-law test
static long long DUMP_BASIS_MASK = -1; // dump the full echelon basis of ONE block (the CRT mask N) for the DS eq.4.5 iso check; -1 = off

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

// Per-prime char-p rank via CRT block split. Each block reduced alone & released.
// Returns total rank (sum over blocks) or -1 on guard/wall abort.
static long long dualRank(int p, long long& peak, long long closingTarget){
    P=p; buildRhoTfac();
    CFBITS=0;{int mx=p-2;while((1<<CFBITS)<=mx)CFBITS++;}CFMASK=(CFBITS?((1u<<CFBITS)-1):0u);
    {long long maxshift=(long long)(DIM)<<CFBITS;if(maxshift>=(1LL<<32)){fprintf(stderr,"  [LDE] coef-embed overflow (DIM=%lld, CFBITS=%d)\n",DIM,CFBITS);return -1;}}
    vector<int> eA,eB; int dimA=crt_idempotents(eA,eB);

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
                        SVec s=shiftVar_T(row,v); local.add(s);
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
                SVec vv=local.rowAt(k); R.add(vv);
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
        if(DUMP_BLOCKS){
            int pc=__builtin_popcount((unsigned)mask);
            fprintf(stderr,"  [BLOCK] mask=%d popcount=%d rank=%lld\n",mask,pc,R.rank());
        }
        if(DUMP_BASIS_MASK>=0 && mask==(int)DUMP_BASIS_MASK){
            // ---- BLOCK BASIS DUMP (Frente 1: the DS eq.4.5 isomorphism check) ----
            // Each echelon row R.rowAt(k) is ONE generator of this block, in reduced
            // form. rowAt is const: read-only, no mutation of R/peak/seeds. We decode
            // each column index to its monomial exponents in the FULL tensor space,
            // base B over the NV variables -- the engine's RAW basis, exponents 0..B-1
            // (NO +1: that offset belongs to eigen_dimC's survivor count, not here).
            // The dump is deliberately UN-massaged: the DS variable identification
            // t_{j_nu}=t_{k_nu}^{m-1} (eq.4.5) is applied by hand in the proof, in the
            // open, NOT inside the engine -- otherwise "block matches DS" is circular.
            int pc=__builtin_popcount((unsigned)mask);
            fprintf(stderr,"  [BASIS-HEADER] mask=%d popcount=%d rank=%lld dimA=%d dimB=%d NV=%d m=%d char=%d\n",
                mask,pc,R.rank(),dimA,B-dimA,NV,m,p);
            fprintf(stderr,"  [BASIS-SPLIT]");
            for(int v=0;v<NV;v++) fprintf(stderr," t%d=%s",v+1,((mask>>v)&1)?"B":"A");
            fprintf(stderr,"\n");
            for(long long k=0;k<R.rank();++k){
                SVec row=R.rowAt(k);
                fprintf(stderr,"  [BASIS-GEN] k=%lld nterms=%zu :",k,row.size());
                for(auto&pr:row){
                    long long t=pr.first; int e[16];
                    for(int v=0;v<NV;v++){ e[v]=(int)(t%B); t/=B; }
                    fprintf(stderr," (");
                    for(int v=0;v<NV;v++) fprintf(stderr,"%s%d",v?",":"",e[v]);
                    fprintf(stderr,")*%d",pr.second);
                }
                fprintf(stderr,"\n");
            }
            fflush(stderr);
        }
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
        else if(!strcmp(argv[i],"--dump-blocks")) DUMP_BLOCKS=true;
        else if(!strncmp(argv[i],"--dump-basis-mask=",18)) DUMP_BASIS_MASK=atoll(argv[i]+18);
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
