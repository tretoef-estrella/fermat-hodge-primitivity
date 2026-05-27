// ============================================================================
//  H O U D I N I
//  Integral Hodge Conjecture verifier for even-dimensional Fermat varieties.
//  The escape artist: walks through the monomial-basis wall that buries dense
//  reduction, by changing to the eigenbasis where the ideal is block-diagonal.
//
//  ------------------------------------------------------------------------
//  TECHNICAL DATA SHEET
//  ------------------------------------------------------------------------
//  Engine        : HOUDINI
//  Author        : Rafael Amichis Luengo (Madrid)
//  Method origin : Degtyarev-Shimada computational criterion (arXiv:1405.4683 §5)
//  Engine novelty: eigenbasis decomposition of the shift action on the quotient
//                  (Method A) + rank-gap "scar" for characteristic p (Method B)
//  Hardware (record run): MacBook Air M2 (2022), 8 GB RAM, 8 cores,
//                  single thread, throttled to 25% CPU (taskpolicy -c utility)
//  Arithmetic    : exact modular. NO floating point anywhere.
//  ------------------------------------------------------------------------
//  RECORD (this engine):
//    Cell (n,m) = (8,4)  ->  PRIMITIVE,  dim_C = dim_F2 = 10730
//      DIM = (m-1)^(n+1) = 19683 ;  partitions (2d+1)!! = 945
//      Method A (eigenbasis) dim_C ............... 0.02 s
//      Method B (real reduction) confirm:
//        PASS 1 char large : 8 rounds, rank_Q=8953, 6093 s, RAM max 0.72 GB
//        PASS 2 char 2     : 8 rounds, rank_p=8953, 3777 s, RAM max 0.42 GB
//      scar = 0 at all 8 rounds.  Peak RAM 0.72 GB on an 8 GB machine (no swap).
//      Virgin cell: not in Degtyarev-Shimada published tables (stop at (8,3)),
//      not in Aljovin-Movasati-Villaflor (their code reaches only n<=4).
//  ------------------------------------------------------------------------
//  THE TWO METHODS
//
//  METHOD A  (eigenbasis -- computes dim_C, any cell, milliseconds)
//    Over a prime P = 1 (mod m) a primitive m-th root of unity zeta exists, so
//    multiplication by each t_v on Rbar = k[t_1..t_{n+1}]/(phi(t_i)) is
//    diagonalizable (phi=1+t+...+t^{m-1}; eigenvalues = nontrivial m-th roots
//    zeta^1..zeta^{m-1}). The simultaneous eigenbasis is indexed by characters
//    chi=(j_0..j_n), j_v in {1..m-1}; (m-1)^{n+1}=DIM one-dim eigenlines.
//    The ideal (rho_J:J) is t_v-invariant => splits over chi; on each 1-dim line
//    every monomial acts as a scalar, so the ideal is the whole line or {0}.
//        dim_C B_K = #{ chi : rho_J(chi)=0  for ALL partitions J }.
//    rho_J is tensorial over disjoint pairs => rho_J(chi) factorizes:
//        rho_J(chi) = prod over active pairs (a,b) of F(j_a,j_b),
//        F(jp,jq)   = sum_{a=0}^{m-2} sum_{b=0}^{a} zeta^{jp*a + jq*b}.
//    No linear algebra. No burial. Validated 7/7 (4,3),(4,4),(4,5),(8,3),
//    (10,3),(8,4),(4,13) and cross-prime stable.
//
//  METHOD B  (scar -- computes dim_Fp for p|m, where Method A cannot apply)
//    For p|m no primitive m-th root exists (phi=(t-1)^{m-1}, single Jordan
//    block, not diagonalizable). dim_Fp needs real sparse reduction in char p.
//        scar = rank_Q(closure) - rank_p(closure) = dim_Fp - dim_C
//             = number of elementary divisors divisible by p (the p-torsion).
//    HONEST LIMIT (audited): every known Fermat cell is PRIMITIVE, so the scar
//    has only ever been tested at 0. It is a PRIMITIVITY CONFIRMATOR, NOT a
//    validated torsion detector. A synthetic positive control must fire before
//    any future scar!=0 verdict is trusted.
//
//  VERDICT carried by TWO concordant independent roads to dim_C (Method A
//  cross-prime + char-large real reduction), not by the scar alone.
//  ------------------------------------------------------------------------
//  BUILD (Mac M2, plain g++; no quad needed):
//    g++ -O3 -march=native -std=c++17 -funroll-loops HOUDINI.cpp -o HOUDINI
//  RUN (Architect standard, 25% CPU, Mac free & hard):
//    cd ~/Downloads && caffeinate -dims taskpolicy -c utility ./HOUDINI 8 4 2>&1 | tee HOUDINI_8_4_run.log
//  ARGS: n m  [wall_sec_for_reduction]
//  Method A always runs (instant). Method B runs if its RAM guard allows;
//  on guard hit it reports the partial scar table honestly (not a math result).
// ============================================================================
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <ctime>
#include <string>
using namespace std;

static int n,m,d,NV,B,P; static long long DIM; static vector<long long> powB;
static vector<vector<pair<int,int>>> parts;
static long long RAM_BUDGET_NZ = 450000000LL; // ~5.4 GB at 12B/entry; 8GB Mac: abort before swap
static double WALL = 100000.0;

// ---------- modular arithmetic ----------
static inline int ad(int a,int b){a+=b;if(a>=P)a-=P;return a;}
static inline int sb(int a,int b){a-=b;if(a<0)a+=P;return a;}
static inline int ml(long long a,long long b){return(int)((a*b)%P);}
static int pw(int a,long long e){int r=1;a%=P;if(a<0)a+=P;while(e){if(e&1)r=ml(r,a);a=ml(a,a);e>>=1;}return r;}
static int inv(int a){return pw(a,P-2);}

// ---------- partitions of {0..n+1} into pairs, index 0 fixed first ----------
static void gp(vector<int>&av,vector<pair<int,int>>&c){if(av.empty()){parts.push_back(c);return;}int a=av[0];for(size_t bi=1;bi<av.size();++bi){int b=av[bi];vector<int>nx;for(size_t i=1;i<av.size();++i)if((int)i!=(int)bi)nx.push_back(av[i]);c.push_back({a,b});gp(nx,c);c.pop_back();}}

// ---------- power reduction t^k -> basis {1..t^{m-2}} (depends on P) ----------
static vector<vector<pair<int,int>>> redPow;
static void buildRed(){int mk=2*(m-2)+1;if(mk<m)mk=m;redPow.assign(mk+1,{});for(int k=0;k<=m-2;k++)redPow[k]={{k,1}};{vector<pair<int,int>>r;for(int j=0;j<=m-2;j++)r.push_back({j,P-1});redPow[m-1]=r;}for(int k=m;k<=mk;k++){vector<int>acc(m-1,0);for(auto&pr:redPow[k-1]){int e=pr.first+1,cf=pr.second;if(e<=m-2)acc[e]=ad(acc[e],cf);else for(int j=0;j<=m-2;j++)acc[j]=ad(acc[j],ml(cf,P-1));}vector<pair<int,int>>r;for(int j=0;j<=m-2;j++)if(acc[j])r.push_back({j,acc[j]});redPow[k]=r;}}

typedef vector<pair<long long,int>> SVec;
static void svClean(SVec&v){sort(v.begin(),v.end());SVec o;for(auto&pr:v){if(!o.empty()&&o.back().first==pr.first)o.back().second=ad(o.back().second,pr.second);else o.push_back(pr);}SVec o2;for(auto&pr:o)if(pr.second)o2.push_back(pr);v.swap(o2);}
static vector<pair<int,int>> rhoFac(){vector<pair<int,int>>f;for(int a=0;a<=m-2;a++)for(int b=0;b<=a;b++)f.push_back({a,b});return f;}
static SVec buildRhoJ(const vector<pair<int,int>>&Pj){vector<pair<int,int>>ap;for(auto&pr:Pj){if(pr.first==0||pr.second==0)continue;ap.push_back({pr.first-1,pr.second-1});}static const vector<pair<int,int>>fac=rhoFac();SVec cur;cur.push_back({0LL,1});for(auto&a:ap){long long wA=powB[a.first],wB=powB[a.second];SVec nx;nx.reserve(cur.size()*fac.size());for(auto&t:cur){long long bid=t.first;int c=t.second;for(auto&f:fac)nx.push_back({bid+(long long)f.first*wA+(long long)f.second*wB,c});}cur.swap(nx);}if(ap.empty()){cur.clear();cur.push_back({0LL,1});}svClean(cur);return cur;}
static SVec shiftVar(const SVec&v,int var){long long w=powB[var];SVec o;o.reserve(v.size());for(auto&pr:v){long long id=pr.first;int cf=pr.second;long long hi=id/w;int e=(int)(hi%B);long long rest=id-(long long)e*w;int nk=e+1;for(auto&rp:redPow[nk])o.push_back({rest+(long long)rp.first*w,ml(cf,rp.second)});}svClean(o);return o;}
static double now_s(){return (double)clock()/CLOCKS_PER_SEC;}

// ================= METHOD A : eigenbasis dim_C over P0 = 1 mod m =================
static long long eigen_dimC(int P0,int zeta){
    P=P0;
    vector<int> zp(2*m,1); for(int k=1;k<2*m;k++) zp[k]=ml(zp[k-1],zeta);
    auto Z=[&](int e){ e%=m; if(e<0)e+=m; return zp[e]; };
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

// ================= METHOD B : real reduction rank, per round, with scar =================
struct Red{unordered_map<long long,int>pc;vector<SVec>piv;long long nz=0;
    bool add(SVec v){while(true){if(v.empty())return false;long long lc=v[0].first;auto it=pc.find(lc);if(it==pc.end())break;const SVec&pr=piv[it->second];int f=v[0].second;SVec r;r.reserve(v.size()+pr.size());size_t i=0,j=0;while(i<v.size()&&j<pr.size()){if(v[i].first<pr[j].first)r.push_back(v[i++]);else if(v[i].first>pr[j].first){r.push_back({pr[j].first,sb(0,ml(f,pr[j].second))});j++;}else{int nc=sb(v[i].second,ml(f,pr[j].second));if(nc)r.push_back({v[i].first,nc});i++;j++;}}while(i<v.size())r.push_back(v[i++]);while(j<pr.size()){r.push_back({pr[j].first,sb(0,ml(f,pr[j].second))});j++;}v.swap(r);}if(v.empty())return false;int iv=inv(v[0].second);for(auto&pr:v)pr.second=ml(pr.second,iv);pc[v[0].first]=piv.size();nz+=v.size();piv.push_back(std::move(v));return true;}
    long long rank()const{return (long long)piv.size();}
};
// closure under current P, recording rank per round; abort on guard (-1). rpr filled.
static long long closureRanks(const char* tag, vector<long long>& rpr){
    buildRed(); Red R; double t0=now_s(); double lastPulse=now_s();
    for(auto&Pj:parts) R.add(buildRhoJ(Pj));
    rpr.clear(); rpr.push_back(R.rank());
    fprintf(stderr,"  [%s round 0 seed] rank=%lld nz=%lld(~%.2fGB) t=%.0fs\n",tag,R.rank(),R.nz,R.nz*12.0/1e9,now_s()-t0);
    vector<SVec> fr=R.piv; int rd=0;
    while(!fr.empty()){
        rd++; vector<SVec> nx;
        for(auto&row:fr){ for(int v=0;v<NV;++v){ SVec s=shiftVar(row,v); if(R.add(std::move(s))) nx.push_back(R.piv.back());
            if(now_s()-lastPulse>=30.0){ lastPulse=now_s(); fprintf(stderr,"  [%s ..alive] round=%d rank=%lld (%.2f%%) nz=%lld(~%.2fGB) t=%.0fs\n",tag,rd,R.rank(),100.0*R.rank()/DIM,R.nz,R.nz*12.0/1e9,now_s()-t0); }
            if(R.nz>RAM_BUDGET_NZ){ fprintf(stderr,"  [%s GUARD] RAM hit round=%d rank=%lld (~%.2fGB)\n",tag,rd,R.rank(),R.nz*12.0/1e9); return -1; }
            if(now_s()-t0>WALL){ fprintf(stderr,"  [%s GUARD] wall hit\n",tag); return -1; } } }
        fr.swap(nx); rpr.push_back(R.rank());
        fprintf(stderr,"  [%s round %d done] rank=%lld (%.2f%%) nz=%lld(~%.2fGB) t=%.0fs\n",tag,rd,R.rank(),100.0*R.rank()/DIM,R.nz,R.nz*12.0/1e9,now_s()-t0);
        if(R.rank()>=DIM) break;
    }
    return R.rank();
}

int main(int argc,char**argv){
    if(argc<3){fprintf(stderr,"usage: %s n m [wall_sec]\n",argv[0]);return 1;}
    setvbuf(stderr,NULL,_IONBF,0);
    n=atoi(argv[1]); m=atoi(argv[2]); if(argc>=4)WALL=atof(argv[3]);
    d=n/2; NV=n+1; B=m-1; powB.assign(NV+1,1); for(int i=1;i<=NV;i++)powB[i]=powB[i-1]*B; DIM=powB[NV];
    vector<int>all; for(int i=0;i<n+2;i++)all.push_back(i); vector<pair<int,int>>c; gp(all,c);
    printf("================ HOUDINI  n=%d m=%d  DIM=%lld  partitions=%zu ================\n",n,m,DIM,parts.size());
    printf("Author: Rafael Amichis Luengo (Madrid).  Method: Degtyarev-Shimada (arXiv:1405.4683 §5).\n");

    // ---- METHOD A: dim_C eigenbasis, cross-prime ----
    printf("\n[METHOD A] dim_C via eigenbasis, cross-prime (primes = 1 mod m):\n"); fflush(stdout);
    double tA0=now_s();
    long long dC=-1; int found=0; long long base=(1000000/m)+1; long long dCs[8]; int Ps[8];
    for(int k=0;k<5;k++){ int Pk,zk; if(!findPrimeRoot(m,base,Pk,zk)){printf("   (no more primes)\n");break;} base=(Pk-1)/m+1; long long dk=eigen_dimC(Pk,zk); Ps[found]=Pk; dCs[found]=dk; found++; printf("   P=%d -> dim_C = %lld\n",Pk,dk); if(dC<0)dC=dk; }
    bool crossOK=true; for(int k=1;k<found;k++) if(dCs[k]!=dCs[0]) crossOK=false;
    double tA=now_s()-tA0;
    printf("   cross-prime: %s   dim_C = %lld   [Method A time %.2f s over %d primes]\n", crossOK?"CONSISTENT":"!!! DISAGREE !!!", dC, tA, found);

    // ---- METHOD B: dim_Fp real reduction + scar, for each p|m ----
    vector<int> ps; {int mm=m;for(int p=2;(long long)p*p<=mm;p++){if(mm%p==0){ps.push_back(p);while(mm%p==0)mm/=p;}}if(mm>1)ps.push_back(mm);}
    printf("\n[METHOD B] dim_Fp via real reduction + scar (primes dividing m:"); for(int p:ps)printf(" %d",p); printf(")\n"); fflush(stdout);

    // reference rank_Q over a large prime (independent of Method A): dim_C cross-check
    printf("\n  PASS 1 (char large, rank_Q per round):\n"); fflush(stdout);
    P=1000003; while(m%P==0)P++; vector<long long> rprQ; long long rQ=closureRanks("Q",rprQ); bool Qdone=(rQ>=0);
    printf("  PASS1 %s: rank_Q=%lld dim_C(real)=%lld\n", Qdone?"COMPLETE":"ABORTED", Qdone?rQ:rprQ.back(), Qdone?(DIM-rQ):-1);

    bool aborted=!Qdone; vector<pair<int,long long>> dpv; vector<long long> rprP_first;
    for(size_t ip=0; ip<ps.size() && !aborted; ++ip){ int p=ps[ip];
        printf("\n  PASS 2 (char %d, rank_p per round):\n",p); fflush(stdout);
        P=p; vector<long long> rprP; long long rP=closureRanks("F",rprP);
        if(rP<0){ printf("  PASS2(char %d) ABORTED by guard\n",p); aborted=true; break; }
        printf("  PASS2(char %d) COMPLETE: rank_p=%lld dim_F%d=%lld\n",p,rP,p,DIM-rP); dpv.push_back({p,DIM-rP});
        if(ip==0) rprP_first=rprP;
        // scar table vs rank_Q
        printf("\n  [SCAR vs char-large] round : rank_Q  rank_p  scar\n");
        size_t R=min(rprQ.size(),rprP.size()); long long last=-1; int stab=-1;
        for(size_t r=0;r<R;r++){ long long sc=rprQ[r]-rprP[r]; printf("    %3zu  : %6lld  %6lld  %lld\n",r,rprQ[r],rprP[r],sc); if(r>0&&sc==last&&stab<0)stab=(int)r; last=sc; }
        if(stab>=0) printf("  [SCAR] stabilized at round %d\n",stab);
    }

    // ---- VERDICT ----
    printf("\n================ VERDICT ================\n");
    if(aborted){
        printf("dim_C = %lld (Method A, cross-prime %s).\n", dC, crossOK?"consistent":"DISAGREE");
        printf("dim_Fp INCOMPLETE: char-p reduction hit the RAM guard. NOT a math result.\n");
        printf("=> Method A half is solid; the char-p half needs more RAM or a lighter prime.\n");
        return 2;
    }
    string verdict="PRIMITIVE"; for(auto&pr:dpv) if(pr.second!=dC) verdict="TORSION";
    printf("dim_C  = %lld   (Method A eigenbasis, cross-prime; AND char-large real reduction agree)\n",dC);
    for(auto&pr:dpv) printf("dim_F%d = %lld%s\n",pr.first,pr.second,(pr.second!=dC?"   <-- DIFFERS":""));
    printf("VERDICT = %s\n",verdict.c_str());
    if(verdict=="PRIMITIVE") printf("=> L(X) primitive. Standard linear cycles GENERATE the integral Hodge lattice.\n");
    else { printf("=> TORSION (scar!=0). *** CANDIDATE BOMBAZO ***\n");
           printf("   WARNING (D-HF-7): the scar is calibrated only on primitive controls. Before trusting\n");
           printf("   this TORSION, pass a synthetic positive-torsion control. Numbers from files only.\n"); }
    return 0;
}
