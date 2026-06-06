// =====================================================================================
// legolaselpeloterov4 - THE CANNON: (4,13), THE LAST PRIME BULLET (6 June 2026)
// Single-buffer IN-PLACE peel for the tightest run of the campaign.
//
// MANIFEST:
//  FORGE CAZA (cera carnauba): the fam d=13 seal gate caught an int8 DIAGONAL OVERFLOW
//   (d^2-3d+3 = 133 > 127) in the forge smoke - 16 Mac-hours saved. All prior degrees fit
//   (d=12 -> 111); no previous result affected. Fix: the diagonal is never stored, it is
//   synthesized at materialize time; off-diagonals {0, 1, 2-d} remain int8-safe.
//  THE TRICK (new): in-place residual compaction. After each level's elimination, the
//   residual row pointers are SORTED BY ADDRESS; row k (sorted) is compacted to base+k*nc2.
//   Safety: r_k >= k (k smaller-address residual rows precede it), so source start r_k*nc
//   >= k*nc >= k*nc2 = its destination start, and for k' > k the source start >= (k+1)*nc
//   >= dest end of row k. No write ever lands on an unread source. Within a row, the
//   destination index jj <= j always, ascending scan is safe. ONE buffer instead of two.
//  MANDATORY DUAL-PATH GATE (Auditor condition): (4,5) p=5 is peeled by BOTH the two-buffer
//   path (v3 machinery, untouched) and the in-place path; profiles must be BYTE-IDENTICAL
//   and equal the acta anchor {166,174,54,7} - else ABORT. 0.34 GiB of margin demands the
//   trick be certified, not trusted.
//  GATES (abort on fail): (4,3) p=3 {19,1,1}; (4,4) p=2 vs AMV Table 1 (rank 142 + profile);
//   the dual-path certification above.
//  SEAL TEST (no abort): family d=13 flat law, ELEVENTH degree: rank 1729 (the taxicab
//   number, (13-1)^3+1), heights {0: 35, 1: 363, 2: 1331}.
//  THE SHOT [NEW]: (4,13), 32955 planes, p=13 mod 13^8 = 815730721 (u32 ceiling; products
//   6.7e17, u64-safe), 8 levels. RIDING THE RUN, ALL SEALED ON THE ACTA BEFORE FORGING:
//    - sofa rank law, TENTH trial: rank = 19921
//    - Hypothesis H [CONJ-posthoc]: c0 = 1319, c2 = 7516, c4 = 50 (even floors are the cubics)
//    - bookkeeping complement (automatic, not evidence): c1+c3 = 11036
//    - registered guess (weakest label): h_max = 4
//   This is plausibly the LAST reachable prime kingdom on this hardware ((4,17) needs ~22 GB).
//  CONFIRMATION PASSES (campaign standard, end of run, no abort): (4,11) p=11 and (4,10)
//   both towers vs acta v79 night values.
//  RAM (ledger printed at every allocation): peak = raw int8 1.01 GiB + single u32 buffer
//   4.05 GiB = 5.06 GiB sustained through the rank pass; raw freed before the peel.
//   TIGHTEST RUN OF THE CAMPAIGN: guard 5.4, margin 0.34 GiB. Swap is the red line.
//  WALL (honest, scaled from measured (4,11) phases x4.49): shot ~16 h; confirms ~5 h more;
//   total ~21 h at 25%. The Architect holds the launch.
//
// EXPECTED OUTPUT (diff template; bracketed unknown):
//  GATE (4,3) PASS; GATE (4,4) PASS; DUAL-PATH (4,5): two-buffer == in-place == acta -> CERTIFIED
//  SEAL TEST fam d=13: rank [1729?] {35,363,1331}? -> [HIT/MISS], continuing
//  VERDICT (4,13): rank [19921?] | c0 [1319?] c2 [7516?] c4 [50?] | hmax [4?] | profile [...]
//  CONFIRM (4,11) [CONFIRMED?]; CONFIRM (4,10) [CONFIRMED?]
//
// Compile: g++-15 -O3 -march=native -std=c++17 -funroll-loops -o legolaselpeloterov4 legolaselpeloterov4.cpp
// Run:     cd ~/Downloads && time caffeinate -dims taskpolicy -c utility ./legolaselpeloterov4 2>&1 | tee legolaselpeloterov4_4_13_run1.log
// =====================================================================================
// =====================================================================================
// legolaselpeloterov2.cpp - 5 June 2026 - THE BALL, GENERALIZED TO ANY PRIME. The (4,8) trial.
// Engine lineage: legolaselpelotero (the (4,9) kill, 32.5 min). v2 per fix-naming rule.
// Operacion LEGOLAS. Mission: put the fourfold Amichis boundary's true shape ON TRIAL.
//
// MANIFEST (per audit protocol):
//   GATE 1 [SEALED-ANCHOR, campaign]: (4,3) at p=3 mod 3^17 -> heights {0:19, 1:1, 2:1}
//   GATE 2 [SEALED-ANCHOR, PUBLISHED]: (4,4) at p=2 mod 2^30 -> rank 142,
//       2-adic heights {0:100, 1:2, 2:4, 3:30, 4:4, 5:2}  (AMV arXiv:1711.02628 Table 1,
//       row (4,4): 1^100 2^2 4^4 8^30 16^4 32^2 - the published anchor; reproducing it
//       certifies the NEW p=2 peel path against independent published data)
//   SEAL TEST [NEW, no abort]: single family d=8, flat-law OUT-OF-SAMPLE prediction:
//       rank 344 = (d-1)^3+1, heights {0:20, 3:108, 6:216}. Hit extends the law to a
//       2-power degree; miss informs and the shot CONTINUES.
//   THE SHOT [NEW]: full (4,8), 7680 planes. THE TRIAL - three predictions SEALED IN
//       WRITING BEFORE this engine was compiled (sandbox session of 5 June 2026):
//       (a) character counter (gated 6/6 on d=3,4,5,7 hits + d=6,9 misses): 5881 -> rank 5882
//       (b) DS Remark 4.4: DS_4(8) = 3301 -> rank 3302  (NB: 3301 = the (4,8)c2 tower of
//           chuchipachi007, sec.68 of the findings master - independent campaign resonance)
//       (c) AMV-guarantee boundary conjecture [CONJ]: hit set = {d prime, or d=4, or
//           gcd(d,120)=1}; d=8 fails all three -> predicts counter MISS, i.e. rank = 3302.
//       rank = 3302 -> boundary conjecture SURVIVES (7/7). rank = 5882 -> conjecture DEAD.
//       Anything else -> maximum information. NO height-profile commitments (graveyard).
//
// EXPECTED OUTPUT (diff template; bracketed = unknown):
//   GATE (4,3) p=3: {0: 19, 1: 1, 2: 1, 3: 0} -> PASS
//   GATE (4,4) p=2: rank 142 heights {0: 100, 1: 2, 2: 4, 3: 30, 4: 4, 5: 2} -> PASS
//   SEAL TEST fam d=8: rank [344?] heights [{0:20, 3:108, 6:216}?] -> [HIT/MISS], continuing
//   VERDICT (4,8): rank = [R]  | counter 5882: [HIT/MISS] | DS 3302: [HIT/MISS]
//     2-adic height counts: {0..19}; unaccounted; E_2
//
// Technique (inherited + new): raw int8 Gram materialized per modulus; u32 storage
// (MODP <= 2^30, products in u64); below-clearing FULL-ROW peeling (the v1 smoke caza:
// skipped columns left of the pivot hold nonzero multiples of P that the residual reads);
// peel TEMPLATED on <MODP,P> so the compiler bakes magic-number reduction per prime -
// for p=2 the mod is a mask and the division a shift (the 2-adic peel flies).
// 20 levels at mod 2^30 = 10 powers of margin. Divisibility assert, HARD ABORT exit 2.
// Heartbeat ~2 s unbuffered. RAM: (4,8) buffers 2x236 MB, declared peak ~0.6 GB, guard 5.4.
//
// Compile (byte-exact):
//   g++-15 -O3 -march=native -std=c++17 -funroll-loops -o legolaselpeloterov2 legolaselpeloterov2.cpp
// Mac run (byte-exact):
//   cd ~/Downloads && time caffeinate -dims taskpolicy -c utility ./legolaselpeloterov2 2>&1 | tee legolaselpeloterov2_4_8_run1.log
// =====================================================================================
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstdarg>
#include <cstring>
#include <vector>
#include <array>
#include <utility>
#include <algorithm>
#include <chrono>
using namespace std;
typedef uint64_t u64; typedef uint32_t u32; typedef int64_t i64;

static chrono::steady_clock::time_point T0;
static double el(){ return chrono::duration<double>(chrono::steady_clock::now()-T0).count(); }
static void hb(const char*fmt,...){ printf("[%8.1fs] ", el()); va_list ap; va_start(ap,fmt); vprintf(fmt,ap); va_end(ap); printf("\n"); fflush(stdout); }

constexpr u64 QB = 1000003ULL; // separable reference prime (odd, !=3): valid for both towers

static i64 egcd(i64 a,i64 b,i64&x,i64&y){ if(!b){x=1;y=0;return a;} i64 x1,y1,g=egcd(b,a%b,x1,y1); x=y1; y=x1-(a/b)*y1; return g; }
static u64 inv_mod(u64 a,u64 m){ i64 x,y; egcd((i64)(a%m),(i64)m,x,y); x%=(i64)m; if(x<0)x+=(i64)m; return (u64)x; }

struct Edge{ int a,b,e; };
struct Plane{ Edge ed[3]; };

static void gen_matchings(vector<int> v, vector<array<pair<int,int>,3>>&out, array<pair<int,int>,3>&cur, int depth){
  if(v.empty()){ out.push_back(cur); return; }
  int a=v[0];
  for(size_t i=1;i<v.size();i++){
    vector<int> rest; rest.reserve(v.size()-2);
    for(size_t k=1;k<v.size();k++) if(k!=i) rest.push_back(v[k]);
    cur[depth]={a,(int)v[i]};
    gen_matchings(rest,out,cur,depth+1);
  }
}
static vector<Plane> build_planes(int d,int family_only){
  vector<array<pair<int,int>,3>> Ms; array<pair<int,int>,3> cur{};
  gen_matchings({0,1,2,3,4,5},Ms,cur,0);
  if(family_only>=0) Ms=vector<array<pair<int,int>,3>>{Ms[family_only]};
  vector<Plane> Ps; Ps.reserve(Ms.size()*(size_t)d*d*d);
  for(auto&M:Ms) for(int k0=0;k0<d;k0++)for(int k1=0;k1<d;k1++)for(int k2=0;k2<d;k2++){
    Plane p;
    p.ed[0]={M[0].first,M[0].second,2*k0+1};
    p.ed[1]={M[1].first,M[1].second,2*k1+1};
    p.ed[2]={M[2].first,M[2].second,2*k2+1};
    Ps.push_back(p);
  }
  return Ps;
}
static inline int inter_dim(const Plane&P,const Plane&Q,int mod){
  int par[6],pot[6]; bool bad[6];
  for(int i=0;i<6;i++){par[i]=i;pot[i]=0;bad[i]=false;}
  auto root=[&](int x,int&pp)->int{ int p=0; while(par[x]!=x){p+=pot[x]; x=par[x];} pp=((p%mod)+mod)%mod; return x; };
  const Plane* PQ[2]={&P,&Q};
  for(int s=0;s<2;s++)for(int k=0;k<3;k++){
    const Edge&E=PQ[s]->ed[k];
    int pa,pb,ra=root(E.a,pa),rb=root(E.b,pb);
    int w=((pa+E.e-pb)%mod+mod)%mod;
    if(ra!=rb){ par[rb]=ra; pot[rb]=w; bad[ra]=bad[ra]||bad[rb]; }
    else if(w) bad[ra]=true;
  }
  int good=0;
  for(int v2=0;v2<6;v2++) if(par[v2]==v2 && !bad[v2]) good++;
  return good-1;
}
static void build_gram_raw(const vector<Plane>&Ps,int d,int8_t*R,const char*tag){
  int n=(int)Ps.size(), twod=2*d;
  i64 val[4]={0,1,2-(i64)d,(i64)d*d-3*d+3};
  hb("building Gram %s: %d planes (raw int8 %.0f MB)",tag,n,n*(double)n/1048576.0);
  double last=el();
  for(int a=0;a<n;a++){
    R[(u64)a*n+a]=0; // diagonal synthesized at materialize time (int8 overflow at d>=13: 133>127)
    for(int b=a+1;b<n;b++){
      int dim=inter_dim(Ps[a],Ps[b],twod);
      int8_t v=(int8_t)val[dim+1];
      R[(u64)a*n+b]=v; R[(u64)b*n+a]=v;
    }
    if(el()-last>2){ hb("  Gram %s rows %d/%d",tag,a+1,n); last=el(); }
  }
  hb("Gram %s built",tag);
}
static void materialize(const int8_t*R,int n,u32*buf,u64 mod,i64 diag){
  u64 nn=(u64)n*n;
  for(u64 i=0;i<nn;i++){ i64 v=R[i]; buf[i]=(u32)((v>=0)?(u64)v:(u64)((i64)mod+v)); }
  u64 dm=(u64)(((diag%(i64)mod)+(i64)mod)%(i64)mod);
  for(int i=0;i<n;i++) buf[(u64)i*n+i]=(u32)dm;
}
static int rank_modq(u32*A,int n,const char*tag){
  vector<u32*> Rp(n); for(int i=0;i<n;i++)Rp[i]=A+(u64)i*n;
  int r=0; double last=el();
  for(int c=0;c<n;c++){
    int pi=-1; for(int i=r;i<n;i++) if(Rp[i][c]){pi=i;break;}
    if(pi<0)continue;
    swap(Rp[r],Rp[pi]);
    u64 inv=inv_mod(Rp[r][c],QB);
    const u32*s=Rp[r];
    for(int i=r+1;i<n;i++){
      u64 f=(u64)Rp[i][c]*inv%QB; if(!f)continue;
      u32*t=Rp[i];
      for(int j=c;j<n;j++){ u64 v=f*s[j]%QB; u32 dd=t[j]; t[j]=dd>=(u32)v?dd-(u32)v:dd+(u32)QB-(u32)v; }
    }
    r++;
    if(el()-last>2){ hb("  [%s] rank pass: %d pivots (col %d/%d)",tag,r,c+1,n); last=el(); }
    if(r==n)break;
  }
  return r;
}
// peeling TEMPLATED on <MODP,P>: compiler bakes magic-mod per prime (p=2 -> mask & shift)
template<u64 MODP, u64 P>
static void peel(u32*bufA,u32*bufB,int n,int levels,const char*tag,long long counts[],int&deep_rows){
  int nr=n,nc=n; u32*A=bufA,*B=bufB;
  vector<u32*> Rp; vector<char> ispiv;
  for(int v=0;v<levels;v++){
    counts[v]=0;
    if(nr==0||nc==0) continue;
    Rp.resize(nr); for(int i=0;i<nr;i++)Rp[i]=A+(u64)i*nc;
    ispiv.assign(nc,0);
    int rr=0; double last=el();
    for(int c=0;c<nc;c++){
      int pi=-1; for(int i=rr;i<nr;i++) if(Rp[i][c]%P){pi=i;break;}
      if(pi<0)continue;
      swap(Rp[rr],Rp[pi]);
      u64 inv=inv_mod(Rp[rr][c],MODP);
      const u32*s=Rp[rr];
      for(int i=rr+1;i<nr;i++){
        u64 f=(u64)Rp[i][c]*inv%MODP; if(!f)continue;
        u32*t=Rp[i];
        // FULL-ROW update: skipped columns left of c hold nonzero multiples of P that the
        // residual reads (the v1 smoke caza) -- j=c start is valid for rank, WRONG here.
        for(int j=0;j<nc;j++){ u64 vv=f*s[j]%MODP; u32 dd=t[j]; t[j]=dd>=(u32)vv?dd-(u32)vv:dd+(u32)MODP-(u32)vv; }
      }
      ispiv[c]=1; rr++;
      if(el()-last>2){ hb("  [%s] level %d: %d pivots (col %d/%d, rows %d)",tag,v,rr,c+1,nc,nr); last=el(); }
      if(rr==nr)break;
    }
    counts[v]=rr;
    int nr2=nr-rr, nc2=nc-rr;
    for(int i=0;i<nr2;i++){
      const u32*s=Rp[rr+i]; u32*t=B+(u64)i*nc2; int jj=0;
      for(int j=0;j<nc;j++){
        if(ispiv[j])continue;
        u32 x=s[j];
        if(x%P){ hb("FATAL: divisibility violation at level %d (residual row %d col %d val %u) - ABORT",v,i,j,x); exit(2); }
        t[jj++]=x/(u32)P;
      }
    }
    hb("  [%s] level %d done: %lld divisors; residual %dx%d",tag,v,counts[v],nr2,nc2);
    swap(A,B); nr=nr2; nc=nc2;
  }
  deep_rows=nr;
}
static void print_counts(const char*pre,const long long*c,int levels){
  printf("%s{",pre);
  for(int v=0;v<levels;v++) printf("%d: %lld%s",v,c[v],v+1<levels?", ":"");
  printf("}\n"); fflush(stdout);
}


// IN-PLACE peel: single buffer, residual compacted to the base after each level.
template<u64 MODP, u64 P>
static void peel_inplace(u32*A,int n,int levels,const char*tag,long long counts[],int&deep_rows){
  int nr=n,nc=n;
  vector<u32*> Rp; vector<char> ispiv;
  for(int v=0;v<levels;v++){
    counts[v]=0;
    if(nr==0||nc==0) continue;
    Rp.resize(nr); for(int i=0;i<nr;i++)Rp[i]=A+(u64)i*nc;
    ispiv.assign(nc,0);
    int rr=0; double last=el();
    for(int c=0;c<nc;c++){
      int pi=-1; for(int i=rr;i<nr;i++) if(Rp[i][c]%P){pi=i;break;}
      if(pi<0)continue;
      swap(Rp[rr],Rp[pi]);
      u64 inv=inv_mod(Rp[rr][c],MODP);
      const u32*s=Rp[rr];
      for(int i=rr+1;i<nr;i++){
        u64 f=(u64)Rp[i][c]*inv%MODP; if(!f)continue;
        u32*t=Rp[i];
        for(int j=0;j<nc;j++){ u64 vv=f*s[j]%MODP; u32 dd=t[j]; t[j]=dd>=(u32)vv?dd-(u32)vv:dd+(u32)MODP-(u32)vv; }
      }
      ispiv[c]=1; rr++;
      if(el()-last>2){ hb("  [%s] level %d: %d pivots (col %d/%d, rows %d)",tag,v,rr,c+1,nc,nr); last=el(); }
      if(rr==nr)break;
    }
    counts[v]=rr;
    int nr2=nr-rr, nc2=nc-rr;
    // sort residual row pointers by address: guarantees collision-free in-place compaction
    sort(Rp.begin()+rr,Rp.end());
    for(int k=0;k<nr2;k++){
      const u32*s=Rp[rr+k]; u32*t=A+(u64)k*nc2; int jj=0;
      for(int j=0;j<nc;j++){
        if(ispiv[j])continue;
        u32 x=s[j];
        if(x%P){ hb("FATAL: divisibility violation at level %d (residual row %d col %d val %u) - ABORT",v,k,j,x); exit(2); }
        t[jj++]=x/(u32)P;
      }
    }
    hb("  [%s] level %d done: %lld divisors; residual %dx%d (in-place)",tag,v,counts[v],nr2,nc2);
    nr=nr2; nc=nc2;
  }
  deep_rows=nr;
}
// (v3's run_peel_phase helper removed: dead code in v4 - main calls peel/peel_inplace directly)
static void print_prof(const char*pre,const std::vector<long long>&c){
  printf("%s{",pre); for(size_t v=0;v<c.size();v++)printf("%d: %lld%s",(int)v,c[v],v+1<c.size()?", ":""); printf("}\n"); fflush(stdout);
}
int main(){
  T0=chrono::steady_clock::now(); setvbuf(stdout,NULL,_IONBF,0);
  hb("legolaselpeloterov4 - THE CANNON. Gates, then the dual-path certification, then (4,13).");
  { // G1 (4,3) p=3 (in-place path from the start: it must carry the whole night)
    auto Ps=build_planes(3,-1); int n=(int)Ps.size();
    vector<int8_t> raw((u64)n*n); build_gram_raw(Ps,3,raw.data(),"(4,3)");
    vector<u32> A((u64)n*n);
    long long c[4]; int dp; materialize(raw.data(),n,A.data(),129140163ULL,(i64)3*3-3*3+3);
    peel_inplace<129140163ULL,3ULL>(A.data(),n,4,"g1",c,dp);
    bool ok=(c[0]==19&&c[1]==1&&c[2]==1&&c[3]==0);
    printf("GATE (4,3) p=3 in-place: {0: %lld, 1: %lld, 2: %lld, 3: %lld}\n",c[0],c[1],c[2],c[3]);
    hb("GATE (4,3) -> %s",ok?"PASS":"FAIL - ABORT"); if(!ok)return 1;
  }
  { // G2 (4,4) p=2 vs AMV (in-place)
    auto Ps=build_planes(4,-1); int n=(int)Ps.size();
    vector<int8_t> raw((u64)n*n); build_gram_raw(Ps,4,raw.data(),"(4,4)");
    vector<u32> A((u64)n*n);
    materialize(raw.data(),n,A.data(),QB,(i64)4*4-3*4+3); int rk=rank_modq(A.data(),n,"g2");
    long long c[8]; int dp; materialize(raw.data(),n,A.data(),1073741824ULL,(i64)4*4-3*4+3);
    peel_inplace<1073741824ULL,2ULL>(A.data(),n,8,"g2",c,dp);
    bool ok=(rk==142&&c[0]==100&&c[1]==2&&c[2]==4&&c[3]==30&&c[4]==4&&c[5]==2&&c[6]==0&&c[7]==0);
    printf("GATE (4,4) p=2 in-place: rank %d heights {0: %lld, 1: %lld, 2: %lld, 3: %lld, 4: %lld, 5: %lld}\n",rk,c[0],c[1],c[2],c[3],c[4],c[5]);
    hb("GATE (4,4) vs AMV Table 1 -> %s",ok?"PASS":"FAIL - ABORT"); if(!ok)return 1;
  }
  { // DUAL-PATH CERTIFICATION on (4,5): two-buffer vs in-place, byte-identical, vs acta
    auto Ps=build_planes(5,-1); int n=(int)Ps.size();
    vector<int8_t> raw((u64)n*n); build_gram_raw(Ps,5,raw.data(),"(4,5)");
    vector<u32> A((u64)n*n),B((u64)n*n);
    long long c2b[8],cip[8]; int dp;
    materialize(raw.data(),n,A.data(),1220703125ULL,(i64)5*5-3*5+3);
    peel<1220703125ULL,5ULL>(A.data(),B.data(),n,8,"dual-2buf",c2b,dp);
    materialize(raw.data(),n,A.data(),1220703125ULL,(i64)5*5-3*5+3);
    peel_inplace<1220703125ULL,5ULL>(A.data(),n,8,"dual-inpl",cip,dp);
    bool same=true; for(int v=0;v<8;v++) same=same&&(c2b[v]==cip[v]);
    bool acta=(cip[0]==166&&cip[1]==174&&cip[2]==54&&cip[3]==7&&cip[4]==0);
    printf("DUAL-PATH (4,5): two-buffer {%lld,%lld,%lld,%lld} | in-place {%lld,%lld,%lld,%lld}\n",
      c2b[0],c2b[1],c2b[2],c2b[3],cip[0],cip[1],cip[2],cip[3]);
    hb("DUAL-PATH CERTIFICATION -> %s",(same&&acta)?"CERTIFIED (byte-identical, equals acta)":"FAIL - ABORT");
    if(!(same&&acta))return 1;
  }
  { // SEAL TEST fam d=13: flat law, ELEVENTH degree (taxicab rank 1729)
    auto Ps=build_planes(13,0); int n=(int)Ps.size();
    vector<int8_t> raw((u64)n*n); build_gram_raw(Ps,13,raw.data(),"fam d=13");
    vector<u32> A((u64)n*n);
    materialize(raw.data(),n,A.data(),QB,(i64)13*13-3*13+3); int rk=rank_modq(A.data(),n,"sf13");
    long long c[5]; int dp; materialize(raw.data(),n,A.data(),815730721ULL,(i64)13*13-3*13+3);
    peel_inplace<815730721ULL,13ULL>(A.data(),n,5,"sf13",c,dp);
    bool hit=(rk==1729&&c[0]==35&&c[1]==363&&c[2]==1331&&c[3]==0&&c[4]==0);
    printf("SEAL TEST fam d=13: rank %d heights {0: %lld, 1: %lld, 2: %lld}\n",rk,c[0],c[1],c[2]);
    hb("SEAL TEST flat law 11th degree -> %s, continuing",hit?"HIT":"MISS (high information)");
  }
  // ================= THE SHOT: (4,13) - THE LAST PRIME BULLET =================
  hb("THE SHOT: (4,13), 32955 planes. SEALED ON THE ACTA: rank 19921 | H: c0 1319, c2 7516, c4 50 | guess hmax 4.");
  {
    auto Ps=build_planes(13,-1); int n=(int)Ps.size();
    hb("RAM ledger: raw int8 %.2f GiB; single u32 buffer %.2f GiB; SUSTAINED PEAK %.2f GiB (guard 5.4, margin %.2f)",
       (double)n*n/1073741824.0,(double)n*n*4/1073741824.0,(double)n*n*5/1073741824.0,5.4-(double)n*n*5/1073741824.0);
    int8_t*raw=(int8_t*)malloc((u64)n*n); if(!raw){hb("FATAL alloc raw");return 3;}
    build_gram_raw(Ps,13,raw,"(4,13)");
    u32*A=(u32*)malloc((u64)n*n*4); if(!A){hb("FATAL alloc buf");return 3;}
    materialize(raw,n,A,QB,(i64)13*13-3*13+3);
    int rk=rank_modq(A,n,"4,13");
    hb("rank = %d | SOFA SEAL 19921 (tenth trial): %s",rk,rk==19921?"HIT":"MISS - high information");
    materialize(raw,n,A,815730721ULL,(i64)13*13-3*13+3); free(raw);
    hb("RAM ledger: raw freed; peel runs IN-PLACE on the single %.2f GiB buffer",(double)n*n*4/1073741824.0);
    long long c[8]; int dp;
    peel_inplace<815730721ULL,13ULL>(A,n,8,"4,13",c,dp);
    long long tot=0,E=0; int hm=0; for(int v=0;v<8;v++){tot+=c[v];E+=(long long)v*c[v];if(c[v])hm=v;}
    printf("======================================================================\n");
    printf("VERDICT (4,13): rank = %d (seal 19921: %s)\n",rk,rk==19921?"HIT":"MISS");
    printf("  HYPOTHESIS H: c0 = %lld (seal 1319: %s) | c2 = %lld (seal 7516: %s) | c4 = %lld (seal 50: %s)\n",
      c[0],c[0]==1319?"HIT":"MISS",c[2],c[2]==7516?"HIT":"MISS",c[4],c[4]==50?"HIT":"MISS");
    printf("  bookkeeping c1+c3 = %lld (complement 11036) | h_max = %d (guess 4: %s) | E = %lld\n",
      c[1]+c[3],hm,hm==4?"HIT":"MISS",E);
    printf("  13-adic height counts: {0: %lld, 1: %lld, 2: %lld, 3: %lld, 4: %lld, 5: %lld, 6: %lld, 7: %lld}\n",
      c[0],c[1],c[2],c[3],c[4],c[5],c[6],c[7]);
    printf("  unaccounted: %lld (honesty meter)\n",(long long)rk-tot);
    fflush(stdout); free(A);
  }
  // ================= CONFIRMATION PASSES (campaign standard) =================
  {
    auto Ps=build_planes(11,-1); int n=(int)Ps.size();
    int8_t*raw=(int8_t*)malloc((u64)n*n); if(!raw){hb("FATAL");return 3;}
    build_gram_raw(Ps,11,raw,"(4,11) confirm");
    u32*A=(u32*)malloc((u64)n*n*4); if(!A){hb("FATAL");return 3;}
    materialize(raw,n,A,QB,(i64)11*11-3*11+3); int rk=rank_modq(A,n,"c411");
    long long c[8]; int dp; materialize(raw,n,A,214358881ULL,(i64)11*11-3*11+3); free(raw);
    peel_inplace<214358881ULL,11ULL>(A,n,8,"c411",c,dp);
    long long e11[5]={1093,4968,3907,911,22}; bool ok=(rk==10901);
    for(int v=0;v<5;v++)ok=ok&&(c[v]==e11[v]); for(int v=5;v<8;v++)ok=ok&&(c[v]==0);
    printf("CONFIRM (4,11): rank %d -> %s\n",rk,ok?"CONFIRMED":"DIVERGED - flag the Auditor");
    free(A);
  }
  {
    auto Ps=build_planes(10,-1); int n=(int)Ps.size();
    int8_t*raw=(int8_t*)malloc((u64)n*n); if(!raw){hb("FATAL");return 3;}
    build_gram_raw(Ps,10,raw,"(4,10) confirm");
    u32*A=(u32*)malloc((u64)n*n*4); if(!A){hb("FATAL");return 3;}
    materialize(raw,n,A,QB,(i64)10*10-3*10+3); int rk=rank_modq(A,n,"c410");
    long long ca[20],cb[10]; int dp;
    materialize(raw,n,A,1073741824ULL,(i64)10*10-3*10+3);
    peel_inplace<1073741824ULL,2ULL>(A,n,20,"c410p2",ca,dp);
    materialize(raw,n,A,1220703125ULL,(i64)10*10-3*10+3); free(raw);
    peel_inplace<1220703125ULL,5ULL>(A,n,10,"c410p5",cb,dp);
    long long ea[4]={1162,4400,680,1520}, eb[6]={781,3864,2412,643,61,1};
    bool ok=(rk==7762);
    for(int v=0;v<4;v++)ok=ok&&(ca[v]==ea[v]); for(int v=4;v<20;v++)ok=ok&&(ca[v]==0);
    for(int v=0;v<6;v++)ok=ok&&(cb[v]==eb[v]); for(int v=6;v<10;v++)ok=ok&&(cb[v]==0);
    printf("CONFIRM (4,10): rank %d both towers -> %s\n",rk,ok?"CONFIRMED":"DIVERGED - flag the Auditor");
    free(A);
  }
  printf("The last prime bullet is spent. PMC.\n");
  return 0;
}
