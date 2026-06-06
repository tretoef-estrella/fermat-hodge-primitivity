// =====================================================================================
// legolaselpelotero.cpp - 5 June 2026 - THE BEETLE'S BALL, REFORGED IN STEEL (C++)
// Engine named by the Architect (D26). Operacion LEGOLAS, second leg. The (4,9) shot.
// The Python ball was retired pre-flight by the Architect's order: same ball, same seal,
// forged to fly. This forge is also the exact machinery the (4,11) cell will need.
//
// MANIFEST (per the new audit protocol):
//   GATE 1 [SEALED-ANCHOR]: (4,3) full cell at mod 3^17 -> rank 21, heights {0:19, 1:1, 2:1}
//       (campaign gate, SAME prime as the target; line "GATE (4,3) ... PASS")
//   GATE 2 [SEALED-ANCHOR]: single family d=9 -> rank 513, 3-adic {0:23, 2:147, 4:343}
//       (sealed this session; certifies the d=9 plane/Gram machinery; line "GATE fam d=9 ... PASS")
//   BENCH [NEW, instrument-only]: (a) plain % with runtime modulus vs constexpr modulus
//       (compiler magic-number reduction = Barrett baked in at compile time) -- the faster is
//       committed (constexpr, used throughout); (b) synthetic mid-size elimination mod QB,
//       measured updates/s, honest n^3 extrapolation printed as PROJECTION (assuming seal
//       rank 8001) BEFORE the shot. D-HF-27: wall time is measured, never promised.
//   THE SHOT [NEW]: full (4,9), 10935 planes. SEALED PREDICTION (written before this run):
//       rank = 8001. NO height-profile counts committed (the (4,7) graveyard lesson).
//       Seal-MISS prints high-information and CONTINUES to the full profile.
//       Output: "VERDICT (4,9): rank = R (SEAL 8001: HIT/MISS)" + 12-level 3-adic profile + E_3.
//
// EXPECTED OUTPUT (for the Auditor's diff; bracketed values are the only unknowns):
//   GATE (4,3) at mod 3^17: {0: 19, 1: 1, 2: 1, 3: 0} -> PASS
//   GATE fam d=9: rank 513 heights {0: 23, 1: 0, 2: 147, 3: 0, 4: 343, 5: 0} -> PASS
//   PROJECTION ... (machine-dependent, informational only)
//   VERDICT (4,9): rank = [R] (SEAL 8001: [HIT/MISS])
//     3-adic height counts: {0: [..], ..., 11: [..]}
//     unaccounted beyond height 11: [..]
//     3-adic exponent E = [..]
//
// Innovations credited to the Architect (Rafael Amichis Luengo): the sealed-rank discipline;
// the prime-power signature finding (family heights even-only, odd heights pure coupling),
// tested here at full assembly; the order "steel, not wood" that forged this engine.
// Technique: valuation peeling at mod 3^17, int64-safe ((3^17)^2 = 1.7e16 << 1.8e19 of u64),
// below-clearing-only echelon (pivot rows are discarded into the level count, so clearing
// above is provably wasted work -- removed), column-dropping with physical compaction into a
// ping-pong buffer (cache-contiguous inner loops), raw Gram held once as int8 (120 MB) and
// materialized per modulus (no second Gram build); matrices stored as uint32 (both moduli
// < 2^32, products computed in u64) -- halves memory bandwidth, the measured bottleneck.
// Divisibility assert with HARD ABORT (exit 2).
// RAM ledger printed at every allocation; declared peak ~1.07 GB, inside the 5.4 GB guard.
// Heartbeat ~2 s, unbuffered.
//
// Compile (byte-exact):
//   g++-15 -O3 -march=native -std=c++17 -funroll-loops -o legolaselpelotero legolaselpelotero.cpp
// Mac run (byte-exact):
//   cd ~/Downloads && time caffeinate -dims taskpolicy -c utility ./legolaselpelotero 2>&1 | tee legolaselpelotero_4_9_steel_run1.log
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

constexpr u64 MODP = 129140163ULL;  // 3^17  (peeling modulus; 12 levels + 5 powers of margin)
constexpr u64 QB   = 1000003ULL;    // separable reference prime (rank over Q proxy)

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
// raw Gram: int8 (values for d=9: 57,-7,1,0; d=3: 3,-1,1,0)
static void build_gram_raw(const vector<Plane>&Ps,int d,int8_t*R,const char*tag){
  int n=(int)Ps.size(), twod=2*d;
  i64 val[4]={0,1,2-(i64)d,(i64)d*d-3*d+3}; // index dim+1
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
// peeling: below-clearing only; residual compacted /3 into the ping-pong buffer
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
      int pi=-1; for(int i=rr;i<nr;i++) if(Rp[i][c]%3ULL){pi=i;break;}
      if(pi<0)continue;
      swap(Rp[rr],Rp[pi]);
      u64 inv=inv_mod(Rp[rr][c],MODP);
      const u32*s=Rp[rr];
      for(int i=rr+1;i<nr;i++){
        u64 f=(u64)Rp[i][c]*inv%MODP; if(!f)continue;
        u32*t=Rp[i];
        // FULL-ROW update: skipped (non-pivot) columns left of c hold nonzero multiples of 3
        // that the residual reads -- starting at j=c is valid for rank, WRONG for peeling.
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
        if(x%3ULL){ hb("FATAL: divisibility violation at level %d (residual row %d col %d val %llu) - ABORT",v,i,j,(unsigned long long)x); exit(2); }
        t[jj++]=x/3ULL;
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
  hb("legolaselpelotero (STEEL) - THE BEETLE'S BALL (4,9). Gates first.");

  // ---- BENCH (a): runtime-% vs constexpr-% (compile-time Barrett). Committed: constexpr.
  {
    volatile u64 mr=QB; u64 x=123456789ULL,acc=0; int N=20000000;
    double t1=el(); for(int i=0;i<N;i++){ x=x*2862933555ULL%mr; acc+=x; } double rt=el()-t1;
    x=123456789ULL; double t2=el(); for(int i=0;i<N;i++){ x=x*2862933555ULL%QB; acc+=x; } double ct=el()-t2;
    hb("BENCH modmul: runtime-%% %.0f Mops/s vs constexpr-%% %.0f Mops/s -> constexpr COMMITTED (acc %llu)",
       N/rt/1e6, N/ct/1e6,(unsigned long long)(acc&1));
  }

  // ---- GATE 1 [SEALED-ANCHOR]: (4,3) full cell, same prime as the target
  {
    auto Ps=build_planes(3,-1); int n=(int)Ps.size();
    vector<int8_t> raw((u64)n*n);
    build_gram_raw(Ps,3,raw.data(),"(4,3)");
    vector<u32> A((u64)n*n),B((u64)n*n);
    materialize(raw.data(),(u64)n*n,A.data(),MODP);
    long long c3[4]; int deep;
    peel(A.data(),B.data(),n,4,"gate1",c3,deep);
    bool g1=(c3[0]==19&&c3[1]==1&&c3[2]==1&&c3[3]==0);
    print_counts("GATE (4,3) at mod 3^17: ",c3,4);
    hb("GATE (4,3) -> %s",g1?"PASS":"FAIL - ABORT");
    if(!g1) return 1;
  }
  // ---- GATE 2 [SEALED-ANCHOR]: single family d=9 (flat law, sealed this session)
  double gate2_elim_secs=0;
  {
    auto Ps=build_planes(9,0); int n=(int)Ps.size();
    vector<int8_t> raw((u64)n*n);
    build_gram_raw(Ps,9,raw.data(),"fam d=9");
    vector<u32> A((u64)n*n),B((u64)n*n);
    materialize(raw.data(),(u64)n*n,A.data(),QB);
    double te=el();
    int rk=rank_modq(A.data(),n,"gate2");
    gate2_elim_secs=el()-te;
    materialize(raw.data(),(u64)n*n,A.data(),MODP);
    long long cf[6]; int deep;
    peel(A.data(),B.data(),n,6,"gate2",cf,deep);
    bool g2=(rk==513&&cf[0]==23&&cf[1]==0&&cf[2]==147&&cf[3]==0&&cf[4]==343&&cf[5]==0);
    printf("GATE fam d=9: rank %d heights ",rk); print_counts("",cf,6);
    hb("GATE fam d=9 -> %s",g2?"PASS":"FAIL - ABORT");
    if(!g2) return 1;
  }
  // ---- BENCH (b): synthetic mid-size elimination -> honest projection (D-HF-27)
  {
    int n=1500; vector<u32> A((u64)n*n); u64 x=88172645463325252ULL;
    for(u64 i=0;i<(u64)n*n;i++){ x^=x<<13; x^=x>>7; x^=x<<17; A[i]=(u32)(x%QB); }
    double t1=el(); rank_modq(A.data(),n,"bench"); double secs=el()-t1;
    double updates=(double)n*n*n/3.0, ups=updates/secs;
    double N=10935.0, rhat=8001.0;
    auto S=[&](double m){ return m*(m+1)*(2*m+1)/6.0; };
    double rank_up=S(N)-S(N-rhat);
    double proj_rank=rank_up/ups;
    hb("BENCH elimination: %.0f Mupd/s (n=1500 in %.1fs; gate2 729-elim %.2fs)",ups/1e6,secs,gate2_elim_secs);
    hb("PROJECTION (this machine, full speed, ASSUMING seal rank 8001): rank pass ~%.0f s (~%.0f min);",proj_rank,proj_rank/60);
    hb("PROJECTION peel: comparable order (distribution unknown, below-clearing only). 25%% throttle scales up. Measured, not promised.");
  }
  // ---- THE SHOT [NEW]: full (4,9)
  hb("THE SHOT: (4,9), 10935 planes. SEAL ON THE TABLE: rank 8001. No profile committed.");
  auto Ps=build_planes(9,-1); int n=(int)Ps.size();
  hb("RAM ledger: raw Gram int8 = %.2f GB",(double)n*n/1073741824.0);
  int8_t* raw=(int8_t*)malloc((u64)n*n);
  if(!raw){hb("FATAL: raw alloc failed");return 3;}
  build_gram_raw(Ps,9,raw,"(4,9)");
  hb("RAM ledger: bufA u32 = %.2f GB (running total %.2f GB)",(double)n*n*4/1073741824.0,(double)n*n*5/1073741824.0);
  u32* bufA=(u32*)malloc((u64)n*n*4);
  if(!bufA){hb("FATAL: bufA alloc failed");return 3;}
  materialize(raw,(u64)n*n,bufA,QB);
  int rk=rank_modq(bufA,n,"4,9");
  hb("rank = %d (SEAL 8001: %s)",rk,rk==8001?"HIT":"MISS - high information, do not dismiss; continuing to profile");
  materialize(raw,(u64)n*n,bufA,MODP);
  free(raw);
  hb("RAM ledger: raw freed; bufB u32 = %.2f GB (DECLARED PEAK %.2f GB, guard 5.4)",(double)n*n*4/1073741824.0,(double)n*n*8/1073741824.0);
  u32* bufB=(u32*)malloc((u64)n*n*4);
  if(!bufB){hb("FATAL: bufB alloc failed");return 3;}
  long long counts[12]; int deep_rows;
  peel(bufA,bufB,n,12,"4,9",counts,deep_rows);
  long long tot=0,E=0; for(int v=0;v<12;v++){tot+=counts[v];E+=(long long)v*counts[v];}
  printf("======================================================================\n");
  printf("VERDICT (4,9): rank = %d (SEAL 8001: %s)\n",rk,rk==8001?"HIT":"MISS");
  print_counts("  3-adic height counts: ",counts,12);
  printf("  unaccounted beyond height 11: %lld (residual rows %d)\n",(long long)rk-tot,deep_rows);
  printf("  3-adic exponent E = %lld\n",E);
  printf("Done. PMC.\n"); fflush(stdout);
  free(bufA); free(bufB);
  return 0;
}
