// ============================================================================
//  LETHAL_DUAL_PROBE  --  measurement probe (NOT an engine)
//
//  Question (sub-veta 1 from the (4,15) handoff): when phi factors over F_p
//  (p | m, m composite), the quotient ring R = F_p[t]/phi splits by CRT into
//  R = A x B  (A = F_p[t]/(t-1)^a  nilpotent local ; B = F_p[t]/g^b , g the
//  cyclotomic-type irreducible). The shift (mult by t) respects this split, so
//  the (n+1)-variable space splits into 2^(n+1) tensor blocks, each invariant
//  under ALL variable-shifts. The ideal closure therefore splits as a DIRECT
//  SUM over blocks:  rank_total = sum_blocks rank(block).
//
//  If true, the blocks can be reduced ONE AT A TIME and released, so the RAM
//  PEAK becomes  max_block(peak)  instead of the whole closure. That is the
//  only lever with theoretical leverage left for (4,15) (storage refuted 4x).
//
//  This probe measures, on small cells (dense, sandbox-cheap), with the SAME
//  sparse reducer for both paths and identical nz accounting:
//    MONO : full monomial closure (one echelon)   -> rank_mono, peak_mono
//    CRT  : per-block closure (32 echelons, seq)  -> sum rank_s (GATE),
//             sum nz_s, max peak_s
//  Decision metric:  ratio = max_peak_s / peak_mono.  ratio << 1  => lever real.
//
//  Everything is done over F_p (CRT idempotents have F_p coefficients), so NO
//  extension-field arithmetic is needed and the result is exact.
//  GATE (self-validation): sum_s rank_s MUST equal rank_mono. If it does not,
//  the CRT split is implemented wrong and the probe is void.
//
//  Ideal construction (buildRhoJ_T, shiftVar_T, rhoTfac, svClean, indexing)
//  is cloned BYTE-EXACT from ROSETTA_STAR.cpp.
//
//  Build:  g++ -O3 -march=native -std=c++17 LETHAL_DUAL_PROBE.cpp -o LDP
//  Run:    ./LDP n m p     (p must divide m)
// ============================================================================
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <algorithm>
#include <ctime>
using namespace std;

static int n,m,NV,B,P; static long long DIM; static vector<long long> powB;
static vector<vector<pair<int,int>>> parts;

static inline int ad(int a,int b){a+=b;if(a>=P)a-=P;return a;}
static inline int sb(int a,int b){a-=b;if(a<0)a+=P;return a;}
static inline int ml(long long a,long long b){return(int)((a*b)%P);}
static int pw(int a,long long e){int r=1;a%=P;if(a<0)a+=P;while(e){if(e&1)r=ml(r,a);a=ml(a,a);e>>=1;}return r;}
static int invp(int a){return pw(a,P-2);}

// ---- partition generator: perfect matchings of {0..n+1} (byte-exact ROSETTA) ----
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

// ---- ideal construction, byte-exact from ROSETTA_STAR ----
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

// ---- polynomial arithmetic over F_p (coef ascending), for CRT idempotents ----
typedef vector<int> Poly;
static void ptrim(Poly&a){while(a.size()>1&&a.back()==0)a.pop_back();}
static Poly pmul(const Poly&a,const Poly&b){
    Poly r(a.size()+b.size()-1,0);
    for(size_t i=0;i<a.size();i++)if(a[i])for(size_t j=0;j<b.size();j++)if(b[j])r[i+j]=ad(r[i+j],ml(a[i],b[j]));
    ptrim(r);return r;
}
// divmod: a = q*b + r, deg r < deg b
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
// extended gcd: returns g, sets u,v with u*a+v*b=g
static Poly pegcd(Poly a,Poly b,Poly&u,Poly&v){
    Poly u0={1},u1={0},v0={0},v1={1};
    while(!(b.size()==1&&b[0]==0)){
        Poly q,r; pdivmod(a,b,q,r);
        a=b;b=r;
        Poly nu=u0;{Poly t=pmul(q,u1);if(t.size()<nu.size())t.resize(nu.size(),0);else nu.resize(t.size(),0);for(size_t i=0;i<nu.size();i++)nu[i]=sb(nu[i],t[i]);}
        u0=u1;u1=nu;ptrim(u1);
        Poly nv=v0;{Poly t=pmul(q,v1);if(t.size()<nv.size())t.resize(nv.size(),0);else nv.resize(t.size(),0);for(size_t i=0;i<nv.size();i++)nv[i]=sb(nv[i],t[i]);}
        v0=v1;v1=nv;ptrim(v1);
    }
    u=u0;v=v0;return a;
}

// CRT idempotent e_A (=1 mod M_A, =0 mod M_B), as a vector of B coefs in F_p.
// Returns e_A and e_B as length-B coefficient vectors (the basis of R = F_p[t]/Phi).
static void crt_idempotents(vector<int>&eA,vector<int>&eB){
    // Phi = (t^m - 1)/(t-1) = 1 + t + ... + t^{m-1}, degree m-1 = B
    Poly Phi(m,1); // 1,t,...,t^{m-1}
    // M_A = (t-1)^a, a = p-adic part exponent: largest p^k | m, minus 1
    long long pk=1; {int mm=m; while(mm%P==0){pk*=P;mm/=P;} }
    int a=(int)pk-1;
    Poly tm1={sb(0,1),1}; // -1 + t  == (t-1)
    Poly MA={1}; for(int i=0;i<a;i++)MA=pmul(MA,tm1);
    Poly q,r; pdivmod(Phi,MA,q,r); Poly MB=q; // MB = Phi / MA (exact)
    // u*MA + v*MB = 1
    Poly u,v; Poly g=pegcd(MA,MB,u,v);
    // normalize g to 1 (should be constant)
    int gi=invp(g[0]);
    for(auto&x:u)x=ml(x,gi); for(auto&x:v)x=ml(x,gi);
    // e_A = v*MB mod Phi  (=1 mod MA, 0 mod MB) ; e_B = u*MA mod Phi
    Poly EA=pmod(pmul(v,MB),Phi);
    Poly EB=pmod(pmul(u,MA),Phi);
    eA.assign(B,0); eB.assign(B,0);
    for(size_t i=0;i<EA.size()&&i<(size_t)B;i++)eA[i]=EA[i];
    for(size_t i=0;i<EB.size()&&i<(size_t)B;i++)eB[i]=EB[i];
    // sanity: e_A + e_B == 1, e_A*e_B == 0 mod Phi, e_A^2 == e_A
    Poly sum(B,0); for(int i=0;i<B;i++)sum[i]=ad(eA[i],eB[i]);
    bool ok_sum=(sum[0]==1); for(int i=1;i<B;i++) if(sum[i]!=0) ok_sum=false;
    Poly prod=pmod(pmul(EA,EB),Phi);
    bool ok_prod=true; for(int x:prod) if(x!=0) ok_prod=false;
    Poly sq=pmod(pmul(EA,EA),Phi); Poly diff(B,0);
    for(int i=0;i<B;i++){int s=(i<(int)sq.size()?sq[i]:0); diff[i]=sb(s,eA[i]);}
    bool ok_idem=true; for(int x:diff) if(x!=0) ok_idem=false;
    fprintf(stderr,"  [CRT] a=%d  dimA=%d dimB=%d  e_A+e_B=1:%s  e_A*e_B=0:%s  e_A^2=e_A:%s\n",
        a,a,B-a,ok_sum?"OK":"FAIL",ok_prod?"OK":"FAIL",ok_idem?"OK":"FAIL");
    if(!ok_sum||!ok_prod||!ok_idem){fprintf(stderr,"  [CRT] idempotent construction FAILED -- probe void\n");exit(2);}
}

// multiply a tensor vector by polynomial 'poly' (length B, F_p coefs) in variable var:
//   result = sum_j poly[j] * shift^j (V)
static SVec mulPolyVar(const SVec&V,const vector<int>&poly,int var){
    SVec acc; SVec cur=V; // cur = shift^0(V)
    for(int j=0;j<B;j++){
        if(poly[j]){ for(auto&pr:cur) acc.push_back({pr.first, ml(pr.second,poly[j])}); }
        if(j+1<B) cur=shiftVar_T(cur,var);
    }
    svClean(acc); return acc;
}
// project vector to block s: apply e_{s_v} in every variable v (s_v: 0=A,1=B)
static SVec project(const SVec&V,const vector<int>&s,const vector<int>&eA,const vector<int>&eB){
    SVec cur=V;
    for(int v=0;v<NV;v++){ cur=mulPolyVar(cur, s[v]? eB:eA, v); if(cur.empty())break; }
    return cur;
}

// ---- sparse reducer with nz + peak accounting (same for both paths) ----
struct Red{
    unordered_map<long long,SVec> piv; // lead-col -> normalized row (lead coef 1)
    long long nz=0, peak=0;
    void note(){ if(nz>peak)peak=nz; }
    bool add(SVec v){
        svClean(v);
        while(!v.empty()){
            long long lc=v.front().first; // smallest col = lead (rows sorted asc)
            auto it=piv.find(lc);
            if(it==piv.end()){
                int iv=invp(v.front().second);
                for(auto&pr:v)pr.second=ml(pr.second,iv);
                nz+=(long long)v.size(); note();
                piv.emplace(lc,move(v));
                return true;
            }
            int f=v.front().second; const SVec&row=it->second;
            // v = v - f*row
            SVec nx; nx.reserve(v.size()+row.size());
            size_t i=0,j=0;
            while(i<v.size()&&j<row.size()){
                if(v[i].first<row[j].first){nx.push_back(v[i]);i++;}
                else if(v[i].first>row[j].first){nx.push_back({row[j].first,sb(0,ml(f,row[j].second))});j++;}
                else{int c=sb(v[i].second,ml(f,row[j].second));if(c)nx.push_back({v[i].first,c});i++;j++;}
            }
            while(i<v.size()){nx.push_back(v[i]);i++;}
            while(j<row.size()){nx.push_back({row[j].first,sb(0,ml(f,row[j].second))});j++;}
            v.swap(nx);
        }
        return false;
    }
    long long rank()const{return(long long)piv.size();}
};

// closure of a set of seed vectors under all variable-shifts, reduced. counts peak.
static void closeInto(Red&R, vector<SVec> seeds){
    // BFS closure: maintain list of accepted rows, shift each, add.
    vector<SVec> frontier;
    for(auto&s:seeds){ if(s.empty())continue; SVec c=s; if(R.add(c)) frontier.push_back(s); }
    // re-extract accepted rows to shift (use the seeds that created pivots + their reductions)
    // Simpler & correct: iterate to fixpoint over current pivot rows.
    bool changed=true;
    // snapshot rows to shift; new pivots get shifted in next sweep
    vector<SVec> toShift;
    for(auto&kv:R.piv) toShift.push_back(kv.second);
    while(changed){
        changed=false;
        vector<SVec> next;
        for(auto&row:toShift){
            for(int v=0;v<NV;v++){
                SVec s=shiftVar_T(row,v);
                long long before=R.rank();
                if(R.add(s)){ changed=true; }
                long long after=R.rank();
                if(after>before){ /* new pivot(s) created; capture for next sweep */
                }
            }
        }
        if(changed){ // rebuild shift set from ALL current pivots (cheap on small cells)
            toShift.clear();
            for(auto&kv:R.piv) toShift.push_back(kv.second);
        }
    }
}

int main(int argc,char**argv){
    if(argc<4){fprintf(stderr,"usage: %s n m p   (p|m)\n",argv[0]);return 1;}
    setvbuf(stderr,NULL,_IONBF,0);
    n=atoi(argv[1]);m=atoi(argv[2]);P=atoi(argv[3]);
    if(m%P!=0){fprintf(stderr,"p must divide m\n");return 1;}
    NV=n+1;B=m-1;powB.assign(NV+1,1);for(int i=1;i<=NV;i++)powB[i]=powB[i-1]*B;DIM=powB[NV];
    vector<int>all;for(int i=0;i<n+2;i++)all.push_back(i);vector<pair<int,int>>c;gp(all,c);
    buildRhoTfac();
    fprintf(stderr,"==== LETHAL_DUAL_PROBE  n=%d m=%d p=%d  DIM=%lld  parts=%zu ====\n",n,m,P,DIM,parts.size());

    // ---------- MONO path: full monomial closure, one echelon ----------
    double t0=(double)clock()/CLOCKS_PER_SEC;
    Red Rmono;
    {
        vector<SVec> seeds;
        for(auto&Pj:parts) seeds.push_back(buildRhoJ_T(Pj));
        closeInto(Rmono,seeds);
    }
    long long rank_mono=Rmono.rank(), nz_mono=Rmono.nz, peak_mono=Rmono.peak;
    double t1=(double)clock()/CLOCKS_PER_SEC;
    fprintf(stderr,"[MONO] rank=%lld  dim_Fp=%lld  echelon_nz=%lld  peak_nz=%lld  t=%.2fs\n",
        rank_mono,DIM-rank_mono,nz_mono,peak_mono,t1-t0);

    // ---------- CRT path: per-block closure, sequential ----------
    vector<int> eA,eB; crt_idempotents(eA,eB);
    long long sum_rank=0,sum_nz=0,max_peak=0; int nblk=1<<NV; int nonempty=0;
    long long biggest_block=-1; int biggest_s=-1;
    for(int mask=0;mask<nblk;mask++){
        vector<int> s(NV); for(int v=0;v<NV;v++)s[v]=(mask>>v)&1;
        // project all partition generators to this block
        vector<SVec> seeds; seeds.reserve(parts.size());
        for(auto&Pj:parts){ SVec g=project(buildRhoJ_T(Pj),s,eA,eB); if(!g.empty())seeds.push_back(g); }
        if(seeds.empty()) continue;
        Red Rb; closeInto(Rb,seeds);
        if(Rb.rank()>0)nonempty++;
        sum_rank+=Rb.rank(); sum_nz+=Rb.nz;
        if(Rb.peak>max_peak){max_peak=Rb.peak; biggest_block=Rb.peak; biggest_s=mask;}
    }
    double t2=(double)clock()/CLOCKS_PER_SEC;
    fprintf(stderr,"[CRT ] sum_rank=%lld  blocks_nonempty=%d/%d  sum_nz=%lld  max_block_peak_nz=%lld  t=%.2fs\n",
        sum_rank,nonempty,nblk,sum_nz,max_peak,t2-t1);

    // ---------- GATE + DECISION ----------
    fprintf(stderr,"\n================ RESULT ================\n");
    fprintf(stderr,"GATE  sum_rank(CRT)=%lld  vs  rank(MONO)=%lld  : %s\n",
        sum_rank,rank_mono,(sum_rank==rank_mono)?"MATCH (CRT split valid)":"MISMATCH (PROBE VOID)");
    if(sum_rank!=rank_mono){fprintf(stderr,"  -> CRT split implemented wrong; numbers below are meaningless.\n");return 3;}
    double ratio_peak = peak_mono? (double)max_peak/(double)peak_mono : 0;
    double ratio_nz   = nz_mono?   (double)sum_nz/(double)nz_mono     : 0;
    fprintf(stderr,"PEAK  mono=%lld  CRT(max single block)=%lld  ratio=%.4f\n",peak_mono,max_peak,ratio_peak);
    fprintf(stderr,"NZ    mono=%lld  CRT(sum all blocks)=%lld  ratio=%.4f\n",nz_mono,sum_nz,ratio_nz);
    fprintf(stderr,"VERDICT: %s\n", ratio_peak<0.6 ? "LEVER LOOKS REAL (peak<0.6x) -- worth an engine" :
                                   (ratio_peak<0.9 ? "MARGINAL (0.6-0.9x) -- weigh CPU cost" :
                                                     "NO LEVER (>=0.9x) -- veta refuted, ship exhibitor-only"));
    return 0;
}
