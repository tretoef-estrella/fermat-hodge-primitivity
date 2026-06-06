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
int main(){
  T0=chrono::steady_clock::now();
  setvbuf(stdout,NULL,_IONBF,0);
  hb("legolaselpeloterov2 - ANY-PRIME BALL. The (4,8) trial. Gates first.");
  // ---- GATE 1 [SEALED-ANCHOR]: (4,3), p=3 (certifies the inherited 3-adic path)
  {
    auto Ps=build_planes(3,-1); int n=(int)Ps.size();
    vector<int8_t> raw((u64)n*n); build_gram_raw(Ps,3,raw.data(),"(4,3)");
    vector<u32> A((u64)n*n),B((u64)n*n);
    materialize(raw.data(),(u64)n*n,A.data(),129140163ULL);
    long long c3[4]; int deep;
    peel<129140163ULL,3ULL>(A.data(),B.data(),n,4,"gate1",c3,deep);
    bool g1=(c3[0]==19&&c3[1]==1&&c3[2]==1&&c3[3]==0);
    print_counts("GATE (4,3) p=3: ",c3,4);
    hb("GATE (4,3) -> %s",g1?"PASS":"FAIL - ABORT");
    if(!g1) return 1;
  }
  // ---- GATE 2 [SEALED-ANCHOR, PUBLISHED]: (4,4), p=2 (AMV Table 1: rank 142, 1^100 2^2 4^4 8^30 16^4 32^2)
  {
    auto Ps=build_planes(4,-1); int n=(int)Ps.size();
    vector<int8_t> raw((u64)n*n); build_gram_raw(Ps,4,raw.data(),"(4,4)");
    vector<u32> A((u64)n*n),B((u64)n*n);
    materialize(raw.data(),(u64)n*n,A.data(),QB);
    int rk=rank_modq(A.data(),n,"gate2");
    materialize(raw.data(),(u64)n*n,A.data(),1073741824ULL);
    long long c4[8]; int deep;
    peel<1073741824ULL,2ULL>(A.data(),B.data(),n,8,"gate2",c4,deep);
    bool g2=(rk==142&&c4[0]==100&&c4[1]==2&&c4[2]==4&&c4[3]==30&&c4[4]==4&&c4[5]==2&&c4[6]==0&&c4[7]==0);
    printf("GATE (4,4) p=2: rank %d heights ",rk); print_counts("",c4,8);
    hb("GATE (4,4) vs AMV Table 1 -> %s",g2?"PASS":"FAIL - ABORT");
    if(!g2) return 1;
  }
  // ---- SEAL TEST [no abort]: family d=8, flat law OUT-OF-SAMPLE (rank 344, {0:20, 3:108, 6:216})
  {
    auto Ps=build_planes(8,0); int n=(int)Ps.size();
    vector<int8_t> raw((u64)n*n); build_gram_raw(Ps,8,raw.data(),"fam d=8");
    vector<u32> A((u64)n*n),B((u64)n*n);
    materialize(raw.data(),(u64)n*n,A.data(),QB);
    int rk=rank_modq(A.data(),n,"sealfam");
    materialize(raw.data(),(u64)n*n,A.data(),1073741824ULL);
    long long cf[8]; int deep;
    peel<1073741824ULL,2ULL>(A.data(),B.data(),n,8,"sealfam",cf,deep);
    bool hit=(rk==344&&cf[0]==20&&cf[3]==108&&cf[6]==216&&cf[1]==0&&cf[2]==0&&cf[4]==0&&cf[5]==0&&cf[7]==0);
    printf("SEAL TEST fam d=8: rank %d heights ",rk); print_counts("",cf,8);
    hb("SEAL TEST flat law at 2-power degree -> %s, continuing",hit?"HIT (law extends to d=8)":"MISS (high information)");
  }
  // ---- THE SHOT [NEW]: full (4,8) -- THE TRIAL
  hb("THE SHOT: (4,8), 7680 planes. SEALED: counter says 5882, DS says 3302, boundary conjecture says DS.");
  auto Ps=build_planes(8,-1); int n=(int)Ps.size();
  hb("RAM ledger: raw Gram int8 = %.2f GB",(double)n*n/1073741824.0);
  int8_t* raw=(int8_t*)malloc((u64)n*n);
  if(!raw){hb("FATAL: raw alloc failed");return 3;}
  build_gram_raw(Ps,8,raw,"(4,8)");
  hb("RAM ledger: bufA u32 = %.2f GB",(double)n*n*4/1073741824.0);
  u32* bufA=(u32*)malloc((u64)n*n*4);
  if(!bufA){hb("FATAL: bufA alloc failed");return 3;}
  materialize(raw,(u64)n*n,bufA,QB);
  int rk=rank_modq(bufA,n,"4,8");
  hb("rank = %d | counter 5882: %s | DS 3302: %s",rk, rk==5882?"HIT":"MISS", rk==3302?"HIT":"MISS");
  materialize(raw,(u64)n*n,bufA,1073741824ULL);
  free(raw);
  hb("RAM ledger: raw freed; bufB u32 = %.2f GB (DECLARED PEAK %.2f GB, guard 5.4)",(double)n*n*4/1073741824.0,(double)n*n*8/1073741824.0);
  u32* bufB=(u32*)malloc((u64)n*n*4);
  if(!bufB){hb("FATAL: bufB alloc failed");return 3;}
  long long counts[20]; int deep_rows;
  peel<1073741824ULL,2ULL>(bufA,bufB,n,20,"4,8",counts,deep_rows);
  long long tot=0,E=0; for(int v=0;v<20;v++){tot+=counts[v];E+=(long long)v*counts[v];}
  printf("======================================================================\n");
  printf("VERDICT (4,8): rank = %d  | counter 5882: %s | DS 3302: %s\n",rk, rk==5882?"HIT":"MISS", rk==3302?"HIT":"MISS");
  printf("  boundary conjecture (hit set = prime, d=4, or gcd(d,120)=1): %s\n",
         rk==3302?"SURVIVES 7/7":(rk==5882?"DEAD (counter right where it predicted miss)":"NEITHER - maximum information"));
  print_counts("  2-adic height counts: ",counts,20);
  printf("  unaccounted beyond height 19: %lld (residual rows %d)\n",(long long)rk-tot,deep_rows);
  printf("  2-adic exponent E = %lld\n",E);
  printf("Done. PMC.\n"); fflush(stdout);
  free(bufA); free(bufB);
  return 0;
}
