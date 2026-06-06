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
    R[(u64)a*n+a]=(int8_t)val[3];
    for(int b=a+1;b<n;b++){
      int dim=inter_dim(Ps[a],Ps[b],twod);
      int8_t v=(int8_t)val[dim+1];
      R[(u64)a*n+b]=v; R[(u64)b*n+a]=v;
    }
    if(el()-last>2){ hb("  Gram %s rows %d/%d",tag,a+1,n); last=el(); }
  }
  hb("Gram %s built",tag);
}
static void materialize(const int8_t*R,u64 nn,u32*buf,u64 mod){
  for(u64 i=0;i<nn;i++){ i64 v=R[i]; buf[i]=(u32)((v>=0)?(u64)v:(u64)((i64)mod+v)); }
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

// =====================================================================================
// legolaselpeloterov3 - THE ARCHITECT'S ORDER: BOTH. ALL OF IT. (5 June 2026, night run)
// One engine, sequence: gates -> (4,11) triple-blind -> (4,10) both towers -> confirms.
//
// MANIFEST:
//  GATES (abort on fail):
//   G1 [SEALED-ANCHOR campaign]:  (4,3) p=3  -> {19,1,1}
//   G2 [SEALED-ANCHOR published]: (4,4) p=2  -> rank 142, {100,2,4,30,4,2} (AMV Table 1)
//   G3 [SEALED-ANCHOR acta v78 s88]: (4,5) p=5 -> rank 401, {166,174,54,7}
//  SEAL TESTS (no abort, out-of-sample flat law):
//   fam d=11 p=11 -> rank 1001, {0:29, 1:243, 2:729}   (ninth degree)
//   fam d=10 p=2  -> rank 730,  {0:26, 1:192, 2:512}   (eighth degree, tower 1)
//   fam d=10 p=5  -> rank 730,  {0:26, 1:192, 2:512}   (eighth degree, tower 2)
//  CELL A [NEW, TRIPLE-BLIND]: (4,11) p=11 mod 11^8, 8 levels.
//   SEALED (acta v78 s88, before any run): rank 10901, h_max 6, E 20211.
//   One miss kills the prime ladder = maximum information. NO per-height commitments.
//   Precision note, honest: 11^8 = 214358881 is the u32 ceiling for p=11
//   (11^16 products = 4.6e16 < 2^63 OK); margin over the sealed top = 2 levels;
//   'unaccounted' is the honesty meter - nonzero means deeper precision needed.
//  CELL B [NEW, two-prime front]: (4,10), raw Gram built ONCE, rank ONCE (mod QB),
//   then both towers: p=2 mod 2^30 (20 levels), p=5 mod 5^13 (10 levels).
//   SEALED: rank 7762; G(10) = 15*730 - 7762 = 3188 (conditional on fam seal). Profiles: ZERO commitments.
//  CONFIRMATION PASSES [campaign standard, compare vs acta v78 s88, no abort]:
//   (4,8) p=2 -> rank 3302, {428,252,42,1240,298,336,190,252,136,128}
//   (4,9) p=3 -> rank 5121, {763,246,1866,411,1383,191,202,56,3}
//  RAM (measured ledger printed live): PEAK OF THE NIGHT = (4,11) two u32 buffers
//   = 2 x 19965^2 x 4 B = 3.19 GB (raw int8 0.40 GB freed before bufB). Guard 5.4 intact.
//  No argv: every modulus is a literal at its call site (the runner-footgun dies here).
//
// EXPECTED OUTPUT (diff template; bracketed unknown):
//  3x GATE ... -> PASS ; 3x SEAL TEST ... -> [HIT/MISS], continuing
//  VERDICT (4,11): rank [10901?] | hmax [6?] | E [20211?]  -> TRIPLE [HIT/MISS]
//  VERDICT (4,10): rank [7762?] ; p=2 profile [...] ; p=5 profile [...]
//  CONFIRM (4,8): [CONFIRMED/DIVERGED] ; CONFIRM (4,9): [CONFIRMED/DIVERGED]
//
// Compile: g++-15 -O3 -march=native -std=c++17 -funroll-loops -o legolaselpeloterov3 legolaselpeloterov3.cpp
// Run:     cd ~/Downloads && time caffeinate -dims taskpolicy -c utility ./legolaselpeloterov3 2>&1 | tee legolaselpeloterov3_night_run1.log
// =====================================================================================
struct CellOut{ int rank; long long E; int hmax; long long unacc; std::vector<long long> c; };
static CellOut run_peel_phase(const int8_t*raw,int n,u64 P,int levels,const char*tag,u32*bufA,u32*bufB,u64 modp_banner){
  CellOut o; o.c.assign(levels,0);
  materialize(raw,(u64)n*n,bufA,modp_banner);
  int deep=0;
  if(P==2)       peel<1073741824ULL,2ULL>(bufA,bufB,n,levels,tag,o.c.data(),deep);
  else if(P==3)  peel<129140163ULL,3ULL>(bufA,bufB,n,levels,tag,o.c.data(),deep);
  else if(P==5)  peel<1220703125ULL,5ULL>(bufA,bufB,n,levels,tag,o.c.data(),deep);
  else if(P==11) peel<214358881ULL,11ULL>(bufA,bufB,n,levels,tag,o.c.data(),deep);
  else { hb("unsupported prime"); exit(1); }
  o.E=0; long long tot=0; o.hmax=0;
  for(int v=0;v<levels;v++){ tot+=o.c[v]; o.E+=(long long)v*o.c[v]; if(o.c[v])o.hmax=v; }
  o.rank=(int)tot; o.unacc=0; return o;
}
static void print_prof(const char*pre,const std::vector<long long>&c){
  printf("%s{",pre); for(size_t v=0;v<c.size();v++)printf("%d: %lld%s",(int)v,c[v],v+1<c.size()?", ":""); printf("}\n"); fflush(stdout);
}
int main(){
  T0=chrono::steady_clock::now(); setvbuf(stdout,NULL,_IONBF,0);
  hb("legolaselpeloterov3 - BOTH. ALL OF IT. Gates first.");
  { // G1 (4,3) p=3
    auto Ps=build_planes(3,-1); int n=(int)Ps.size();
    vector<int8_t> raw((u64)n*n); build_gram_raw(Ps,3,raw.data(),"(4,3)");
    vector<u32> A((u64)n*n),B((u64)n*n);
    long long c[4]; int dp; materialize(raw.data(),(u64)n*n,A.data(),129140163ULL);
    peel<129140163ULL,3ULL>(A.data(),B.data(),n,4,"g1",c,dp);
    bool ok=(c[0]==19&&c[1]==1&&c[2]==1&&c[3]==0);
    printf("GATE (4,3) p=3: {0: %lld, 1: %lld, 2: %lld, 3: %lld}\n",c[0],c[1],c[2],c[3]);
    hb("GATE (4,3) -> %s",ok?"PASS":"FAIL - ABORT"); if(!ok)return 1;
  }
  { // G2 (4,4) p=2 vs AMV
    auto Ps=build_planes(4,-1); int n=(int)Ps.size();
    vector<int8_t> raw((u64)n*n); build_gram_raw(Ps,4,raw.data(),"(4,4)");
    vector<u32> A((u64)n*n),B((u64)n*n);
    materialize(raw.data(),(u64)n*n,A.data(),QB); int rk=rank_modq(A.data(),n,"g2");
    long long c[8]; int dp; materialize(raw.data(),(u64)n*n,A.data(),1073741824ULL);
    peel<1073741824ULL,2ULL>(A.data(),B.data(),n,8,"g2",c,dp);
    bool ok=(rk==142&&c[0]==100&&c[1]==2&&c[2]==4&&c[3]==30&&c[4]==4&&c[5]==2&&c[6]==0&&c[7]==0);
    printf("GATE (4,4) p=2: rank %d heights {0: %lld, 1: %lld, 2: %lld, 3: %lld, 4: %lld, 5: %lld}\n",rk,c[0],c[1],c[2],c[3],c[4],c[5]);
    hb("GATE (4,4) vs AMV Table 1 -> %s",ok?"PASS":"FAIL - ABORT"); if(!ok)return 1;
  }
  { // G3 (4,5) p=5 vs acta v78 s88
    auto Ps=build_planes(5,-1); int n=(int)Ps.size();
    vector<int8_t> raw((u64)n*n); build_gram_raw(Ps,5,raw.data(),"(4,5)");
    vector<u32> A((u64)n*n),B((u64)n*n);
    materialize(raw.data(),(u64)n*n,A.data(),QB); int rk=rank_modq(A.data(),n,"g3");
    long long c[8]; int dp; materialize(raw.data(),(u64)n*n,A.data(),1220703125ULL);
    peel<1220703125ULL,5ULL>(A.data(),B.data(),n,8,"g3",c,dp);
    bool ok=(rk==401&&c[0]==166&&c[1]==174&&c[2]==54&&c[3]==7&&c[4]==0);
    printf("GATE (4,5) p=5: rank %d heights {0: %lld, 1: %lld, 2: %lld, 3: %lld}\n",rk,c[0],c[1],c[2],c[3]);
    hb("GATE (4,5) vs acta v78 s88 -> %s",ok?"PASS":"FAIL - ABORT"); if(!ok)return 1;
  }
  { // SEAL TEST fam d=11 (ninth degree, flat law out-of-sample)
    auto Ps=build_planes(11,0); int n=(int)Ps.size();
    vector<int8_t> raw((u64)n*n); build_gram_raw(Ps,11,raw.data(),"fam d=11");
    vector<u32> A((u64)n*n),B((u64)n*n);
    materialize(raw.data(),(u64)n*n,A.data(),QB); int rk=rank_modq(A.data(),n,"sf11");
    long long c[5]; int dp; materialize(raw.data(),(u64)n*n,A.data(),214358881ULL);
    peel<214358881ULL,11ULL>(A.data(),B.data(),n,5,"sf11",c,dp);
    bool hit=(rk==1001&&c[0]==29&&c[1]==243&&c[2]==729&&c[3]==0&&c[4]==0);
    printf("SEAL TEST fam d=11: rank %d heights {0: %lld, 1: %lld, 2: %lld, 3: %lld}\n",rk,c[0],c[1],c[2],c[3]);
    hb("SEAL TEST flat law 9th degree -> %s, continuing",hit?"HIT":"MISS (high information)");
  }
  // ================= CELL A: (4,11) THE TRIPLE-BLIND TRIAL =================
  hb("CELL A: (4,11), 19965 planes. SEALED: rank 10901, h_max 6, E 20211. One miss kills the ladder.");
  {
    auto Ps=build_planes(11,-1); int n=(int)Ps.size();
    hb("RAM ledger: raw int8 %.2f GB + bufA %.2f GB; PEAK OF THE NIGHT after bufB = %.2f GB (guard 5.4)",
       (double)n*n/1073741824.0,(double)n*n*4/1073741824.0,(double)n*n*8/1073741824.0);
    int8_t*raw=(int8_t*)malloc((u64)n*n); if(!raw){hb("FATAL alloc");return 3;}
    build_gram_raw(Ps,11,raw,"(4,11)");
    u32*A=(u32*)malloc((u64)n*n*4); if(!A){hb("FATAL alloc");return 3;}
    materialize(raw,(u64)n*n,A,QB);
    int rk=rank_modq(A,n,"4,11");
    hb("rank = %d | SEAL 10901: %s",rk,rk==10901?"HIT":"MISS - high information");
    u32*B=(u32*)malloc((u64)n*n*4); if(!B){hb("FATAL alloc");return 3;}
    CellOut o; o.c.assign(8,0); int dp;
    materialize(raw,(u64)n*n,A,214358881ULL); free(raw);
    peel<214358881ULL,11ULL>(A,B,n,8,"4,11",o.c.data(),dp);
    long long tot=0,E=0; int hm=0; for(int v=0;v<8;v++){tot+=o.c[v];E+=(long long)v*o.c[v];if(o.c[v])hm=v;}
    printf("======================================================================\n");
    printf("VERDICT (4,11): rank = %d (seal 10901: %s) | h_max = %d (seal 6: %s) | E = %lld (seal 20211: %s)\n",
       rk,rk==10901?"HIT":"MISS",hm,hm==6?"HIT":"MISS",E,E==20211?"HIT":"MISS");
    printf("  TRIPLE SEAL: %s\n",(rk==10901&&hm==6&&E==20211)?"ALL THREE HIT - the prime ladder stands":"AT LEAST ONE MISS - maximum information");
    print_prof("  11-adic height counts: ",o.c);
    printf("  unaccounted: %lld (honesty meter; nonzero = precision ceiling touched)\n",(long long)rk-tot);
    fflush(stdout); free(A); free(B);
  }
  { // SEAL TESTS fam d=10, both towers
    auto Ps=build_planes(10,0); int n=(int)Ps.size();
    vector<int8_t> raw((u64)n*n); build_gram_raw(Ps,10,raw.data(),"fam d=10");
    vector<u32> A((u64)n*n),B((u64)n*n);
    materialize(raw.data(),(u64)n*n,A.data(),QB); int rk=rank_modq(A.data(),n,"sf10");
    long long c2[6],c5[6]; int dp;
    materialize(raw.data(),(u64)n*n,A.data(),1073741824ULL);
    peel<1073741824ULL,2ULL>(A.data(),B.data(),n,6,"sf10p2",c2,dp);
    materialize(raw.data(),(u64)n*n,A.data(),1220703125ULL);
    peel<1220703125ULL,5ULL>(A.data(),B.data(),n,6,"sf10p5",c5,dp);
    bool h2=(rk==730&&c2[0]==26&&c2[1]==192&&c2[2]==512&&c2[3]==0);
    bool h5=(c5[0]==26&&c5[1]==192&&c5[2]==512&&c5[3]==0);
    printf("SEAL TEST fam d=10: rank %d | p=2 {0: %lld, 1: %lld, 2: %lld} | p=5 {0: %lld, 1: %lld, 2: %lld}\n",rk,c2[0],c2[1],c2[2],c5[0],c5[1],c5[2]);
    hb("SEAL TEST flat law 8th degree -> p2 %s, p5 %s, continuing",h2?"HIT":"MISS",h5?"HIT":"MISS");
  }
  // ================= CELL B: (4,10) THE TWO-PRIME FRONT =================
  hb("CELL B: (4,10), 15000 planes, raw built ONCE, both towers. SEALED: rank 7762, G 3188. Profiles: zero commitments.");
  {
    auto Ps=build_planes(10,-1); int n=(int)Ps.size();
    hb("RAM ledger: raw %.2f GB + two u32 buffers %.2f GB = %.2f GB",(double)n*n/1073741824.0,(double)n*n*8/1073741824.0,(double)n*n*9/1073741824.0);
    int8_t*raw=(int8_t*)malloc((u64)n*n); if(!raw){hb("FATAL alloc");return 3;}
    build_gram_raw(Ps,10,raw,"(4,10)");
    u32*A=(u32*)malloc((u64)n*n*4),*B=(u32*)malloc((u64)n*n*4); if(!A||!B){hb("FATAL alloc");return 3;}
    materialize(raw,(u64)n*n,A,QB);
    int rk=rank_modq(A,n,"4,10");
    hb("rank = %d | SEAL 7762: %s | G = 15*730-rank = %d (seal 3188: %s, conditional on fam seal)",
       rk,rk==7762?"HIT":"MISS",15*730-rk,(15*730-rk)==3188?"HIT":"MISS");
    long long ca[20],cb[10]; int dp;
    materialize(raw,(u64)n*n,A,1073741824ULL);
    peel<1073741824ULL,2ULL>(A,B,n,20,"4,10p2",ca,dp);
    long long t2=0,E2=0; for(int v=0;v<20;v++){t2+=ca[v];E2+=(long long)v*ca[v];}
    materialize(raw,(u64)n*n,A,1220703125ULL); free(raw);
    peel<1220703125ULL,5ULL>(A,B,n,10,"4,10p5",cb,dp);
    long long t5=0,E5=0; for(int v=0;v<10;v++){t5+=cb[v];E5+=(long long)v*cb[v];}
    printf("======================================================================\n");
    printf("VERDICT (4,10): rank = %d (seal 7762: %s)\n",rk,rk==7762?"HIT":"MISS");
    printf("  2-adic: "); for(int v=0;v<20;v++)printf("%lld%s",ca[v],v<19?",":""); printf("  | sum %lld unacc %lld E2 = %lld\n",t2,rk-t2,E2);
    printf("  5-adic: "); for(int v=0;v<10;v++)printf("%lld%s",cb[v],v<9?",":""); printf("  | sum %lld unacc %lld E5 = %lld\n",t5,rk-t5,E5);
    fflush(stdout); free(A); free(B);
  }
  // ================= CONFIRMATION PASSES (campaign standard) =================
  {
    auto Ps=build_planes(8,-1); int n=(int)Ps.size();
    vector<int8_t> raw((u64)n*n); build_gram_raw(Ps,8,raw.data(),"(4,8) confirm");
    vector<u32> A((u64)n*n),B((u64)n*n);
    materialize(raw.data(),(u64)n*n,A.data(),QB); int rk=rank_modq(A.data(),n,"c48");
    long long c[20]; int dp; materialize(raw.data(),(u64)n*n,A.data(),1073741824ULL);
    peel<1073741824ULL,2ULL>(A.data(),B.data(),n,20,"c48",c,dp);
    long long exp8[10]={428,252,42,1240,298,336,190,252,136,128}; bool ok=(rk==3302);
    for(int v=0;v<10;v++)ok=ok&&(c[v]==exp8[v]); for(int v=10;v<20;v++)ok=ok&&(c[v]==0);
    printf("CONFIRM (4,8): rank %d, profile vs acta v78 s88 -> %s\n",rk,ok?"CONFIRMED":"DIVERGED - flag the Auditor");
  }
  {
    auto Ps=build_planes(9,-1); int n=(int)Ps.size();
    vector<int8_t> raw((u64)n*n); build_gram_raw(Ps,9,raw.data(),"(4,9) confirm");
    vector<u32> A((u64)n*n),B((u64)n*n);
    materialize(raw.data(),(u64)n*n,A.data(),QB); int rk=rank_modq(A.data(),n,"c49");
    long long c[12]; int dp; materialize(raw.data(),(u64)n*n,A.data(),129140163ULL);
    peel<129140163ULL,3ULL>(A.data(),B.data(),n,12,"c49",c,dp);
    long long exp9[9]={763,246,1866,411,1383,191,202,56,3}; bool ok=(rk==5121);
    for(int v=0;v<9;v++)ok=ok&&(c[v]==exp9[v]); for(int v=9;v<12;v++)ok=ok&&(c[v]==0);
    printf("CONFIRM (4,9): rank %d, profile vs acta v78 s88 -> %s\n",rk,ok?"CONFIRMED":"DIVERGED - flag the Auditor");
  }
  printf("Night complete. PMC.\n");
  return 0;
}
