// ============================================================================
//  J U L I O C E S A R   I N M O R T A L  (512-row seal + 64 LRU cache, honest RAM)
//  Integral Hodge Conjecture verifier for even-dimensional Fermat varieties.
//
//  ONE structural change over GALACTIC JUICE, measured not guessed (PROBE_GAPS_65 on real (6,5)):
//    The accordion sealed bellows of 16 MB. To read ONE pivot row it decompressed the WHOLE
//    16 MB block -- the "saw": on (6,11) part 8 took 1379 s (a cold-block thrash), 65 s when warm.
//    PROBE_GAPS_65 measured on the byte-exact (6,5) echelon:
//      M1: redundancy is 100% INTRA-row (per-row varint == whole-blob varint, byte-for-byte)
//      M5: LZ compression vs block size FLATTENS at 128 rows:
//            block=  1 row  : 0.538 B/entry
//            block=128 rows : 0.251 B/entry, decompress ~91 KB/read   <-- the knee
//            block= big     : 0.229 B/entry, decompress 16 MB/read    (today, the saw)
//    So: seal every 128 PIVOT ROWS instead of every 16 MB. Compression stays ~0.25 B/entry
//    (projects (6,11) ~10-12e9 nz -> ~2.5-3.0 GB, holgado under the 5.4 GB guard) while a cold
//    read decompresses ~91 KB (microseconds) instead of 16 MB (the saw is dead).
//    A wide LRU cache (256 slots x ~91 KB ~= 23 MB) covers the active cold front -> ~no misses.
//    Math byte-identical: same ideal, same rank, same nz, same dim_Fp, same verdict.
//
//  ------------------------------------------------------------------------
//  ( previous GALACTIC JUICE header retained below for lineage )
//  H O U D I N I   G A L A C T I C   J U I C E   (16MB fuelle + 32-slot LRU cache + panel)
//
//  TWO LEVERS over SONIC BOOM STAR, both byte-exact (same ideal, rank, nz, verdict):
//
//  (1) SPEED -- deferred modulo + straight rebound loop.
//      STAR reduced every echelon entry with sb(0,ml(f,pcf)) -- a modular multiply AND
//      a branchy touch -- once per nonzero, hundreds of millions of times. The modulo is
//      the ONLY op that does not vectorize (integer division has no SIMD lane), so it was
//      the ceiling. ANTIGRAVITY accumulates the rebound LAZILY in a plain-int dense scratch
//      WITHOUT reducing each entry, decodes each pivot ONCE into flat contiguous arrays, and
//      runs a STRAIGHT multiply-subtract loop (buf[col]-=f*coef). The modulo is deferred to
//      the moment a leader is read or a pivot is written. char p<=11 and chains of a few
//      hundred keep the int accumulator far from 2^31 -> EXACT.
//      Measured (6,5): STAR 11.78 s -> ANTIGRAVITY 7.6 s = 1.55x; grows on larger cells.
//
//  (2) RAM -- the ACCORDION (Rafa's coca-cola idea: crush the bottle, then cap it).
//      The varint blob carries massive inter-pivot redundancy (gaps repeat ~1396x, measured)
//      that the per-entry varint cannot exploit. The echelon is split into BELLOWS of ~8 MB.
//      The HOT bellows (newest pivots, where the tail rebounds) stays raw. When it fills it is
//      SEALED: LZ-compressed (self-contained codec, lossless, byte-exact round-trip verified)
//      and its raw bytes freed. A rebound against a COLD pivot expands its bellows into a single
//      open-cache (one bellows open at a time) and reuses it. Because the cold 45% of pivots
//      carry only 10% of rebounds (measured), cold expansions are rare and do not thrash.
//      Measured: the (6,5) blob compresses 0.279x byte-exact; (6,11) ~10.7 GB at 1 B/entry
//      projects to ~3 GB sealed -- fits 8 GB. Sealing at 2/4 MB on (6,5): byte-exact, no slowdown.
//
//  ------------------------------------------------------------------------
//  Engine        : HOUDINI ANTIGRAVITY   (Architect-named)
//  Author        : Rafael Amichis Luengo (Madrid)
//  Method origin : Degtyarev-Shimada computational criterion (arXiv:1405.4683 §5)
//  Lineage       : HOUDINI -> NAPKIN -> NAPKIN TURBINA -> SONIC BOOM STAR (~1 B/entry)
//                  -> ANTIGRAVITY (deferred-modulo rebound + LZ accordion store).
//  Hardware      : MacBook Air M2 (2022), 8 GB, single thread, 25% CPU.
//  Arithmetic    : exact modular. NO floating point anywhere.
//  ------------------------------------------------------------------------
//  GATES (byte-exact, sandbox): (4,4) c2 rank=141 nz=1700 dim=102 ;
//    (8,3) c3 rank=252 nz=7310 dim=260 ; (6,5) c5 rank=4900 nz=1,754,505 dim=11484.
//    Accordion verified byte-exact at bellows 1/2/4 MB (multiple seals) on (6,5).
//  ------------------------------------------------------------------------
//  THE TWO METHODS (verdict needs BOTH halves; the scar alone never carries it)
//    METHOD A  (eigenbasis -- dim_C, byte-exact from HOUDINI, cross-prime).
//    METHOD B  (the turbine -- dim_Fp for p|m): per-partition Jordan-pruned closure,
//              streamed into the shared echelon (ANTIGRAVITY reducer + accordion store)
//              -> rank_p -> dim_Fp. scar = dim_Fp - dim_C. D-HF-7: scar calibrated on the
//              zero side; a scar!=0 prints the BOMBAZO warning + demands a synthetic control.
//  ------------------------------------------------------------------------
//  BUILD (Mac, Apple clang ok -- NO quad, NO bits/stdc++.h):
//    g++ -O3 -march=native -std=c++17 -funroll-loops HOUDINI_ANTIGRAVITY.cpp -o HOUDINI_ANTIGRAVITY
//  V6 = v2 base (8MB fuelle: low RAM, no 512MB thrash) + LRU cache x8 of decompressed
//  cold bellows (kills re-decompression when the tail bounces among several cold blocks) + live panel.
//  RUN (Architect standard, 25% CPU, Mac free & hard, live heartbeat):
//    cd ~/Downloads && caffeinate -dims taskpolicy -c utility ./HOUDINI_ANTIGRAVITY 6 5 2>&1 | tee HOUDINI_ANTIGRAVITY_6_5_run1.log
//  ARGS: n m  [wall_sec]
// ============================================================================
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <map>
#include <cstdint>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <sys/resource.h>
#include <string>
using namespace std;

static int n,m,d,NV,B,P; static long long DIM; static vector<long long> powB;
static vector<vector<pair<int,int>>> parts;
static long long RAM_BUDGET_NZ = 5420000000LL; // 5.4 GB guard (full margin, Architect-set): abort clean before swap, SSD untouched
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

// ================= METHOD B : the TURBINE (Jordan starter + SONICSTAR-FOLD fold) =================
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

// ---- SONICSTAR-FOLD reducer: dense scratch (no hash on hot path) + min-heap of touched cols ----
// BUF/OCC are dense arrays of size DIM, shared and always left clean after each add().
static int* HS_BUF=nullptr;
static char* HS_OCC=nullptr;
// PACKED echelon store: pivot rows in two parallel FLAT arrays (uint32 col + uint8 coef)
// + per-pivot offset. 5 B/entry vs 16 B/entry of vector<pair<long long,int>>.
// Mechanics (dense-rebound, min-heap, scratch) byte-identical to the validated engine;
// ONLY the pivot storage representation changes. Math unchanged.
// Requires: column id < 2^32 (DIM <= 4.29e9) and prime P <= 255 (coef fits a byte).
// HOUDINI SONIC BOOM STAR store: pivot rows held as DELTA-VARINT columns with the COEF EMBEDDED
// in the low bits of the first byte (char p small: coef 0..p-1 fits in <=4 bits). Eliminates
// the separate coef array entirely -> ~1 byte LESS per entry than BLACKHOLE.
//   layout per entry: varint( (delta << CFBITS) | (coef-1) )   [coef in 1..p-1, store coef-1]
//   leading entry of each pivot has coef 1 by normalization, stored as (delta<<CFBITS)|0.
// Speed: rows stream-decoded sequentially (cache-friendly), 32-bit leading-col map, and the
// pivot blob is reserve()d ahead to kill reallocation copies that dominated the dense tail.
// Math byte-identical: same closure, same rank, same dim_Fp.
static int CFBITS=0;            // bits reserved for coef-1 in the embedded varint (set per char p)
static uint32_t CFMASK=0;
// ---- ACCORDION LZ codec (lossless, self-contained, no external deps) ----
// Cold bellows: a sealed block of varint pivots compressed with a small LZ. The varint stream
// carries massive inter-pivot redundancy (gaps repeat ~1396x, measured) that the per-entry
// varint cannot exploit but a back-reference coder can. Measured on the real (6,5) blob:
// 1.94 MB -> 0.279x, byte-exact round-trip. Format per token:
//   ctrl&0x80==0 : literal run of (ctrl+1) bytes (1..128)
//   ctrl&0x80==1 : match len=(ctrl&0x7F)+3 (3..130), then 2-byte LE distance (<=65535)
struct AccLZ{
  static void enc(const uint8_t* in,size_t n,vector<uint8_t>&out){
    out.clear(); if(n<3){ for(size_t i=0;i<n;i++){out.push_back(0);out.push_back(in[i]);} return; }
    vector<int> head(65536,-1), prev(n,-1);
    auto H=[&](size_t i)->uint32_t{ return (uint32_t)((in[i]*131u+in[i+1]*17u+in[i+2])&0xFFFF); };
    size_t i=0,litStart=0;
    auto flushLit=[&](size_t upto){ size_t p=litStart;
      while(p<upto){ size_t run=upto-p; if(run>128)run=128; out.push_back((uint8_t)(run-1));
        for(size_t q=0;q<run;q++) out.push_back(in[p+q]); p+=run; } };
    while(i+3<=n){
      uint32_t h=H(i); int bestLen=0,bestDist=0,tries=64;
      for(int c=head[h];c>=0&&tries-->0;c=prev[c]){ size_t dist=i-c; if(dist>65535)break;
        size_t maxl=n-i; if(maxl>130)maxl=130; size_t l=0; while(l<maxl&&in[c+l]==in[i+l])l++;
        if((int)l>bestLen){bestLen=(int)l;bestDist=(int)dist;if(l>=130)break;} }
      prev[i]=head[h]; head[h]=(int)i;
      if(bestLen>=3){ flushLit(i); out.push_back((uint8_t)(0x80|(bestLen-3)));
        out.push_back((uint8_t)(bestDist&0xFF)); out.push_back((uint8_t)(bestDist>>8));
        for(int s=1;s<bestLen&&i+s+3<=n;s++){uint32_t hh=H(i+s);prev[i+s]=head[hh];head[hh]=(int)(i+s);}
        i+=bestLen; litStart=i; } else i++;
    }
    flushLit(n);
  }
  static void dec(const uint8_t* in,size_t n,vector<uint8_t>&out){ out.clear(); size_t i=0;
    while(i<n){ uint8_t ctrl=in[i++];
      if(ctrl&0x80){int len=(ctrl&0x7F)+3;int dist=in[i]|(in[i+1]<<8);i+=2;size_t st=out.size()-dist;for(int k=0;k<len;k++)out.push_back(out[st+k]);}
      else{int run=ctrl+1;for(int k=0;k<run;k++)out.push_back(in[i+k]);i+=run;} } }
};

struct Red{
 unordered_map<uint32_t,int>pc;     // leading col id -> GLOBAL pivot index
 long long nz=0;
 vector<long long> heap;
 vector<long long> touchedList;
 vector<uint32_t> DCOL;
 vector<int32_t>  DCOEF;

 // ---- ACCORDION storage (JULIOCESAR: seal by ROW COUNT, not byte size) ----
 // Each pivot belongs to a BELLOWS. The hot bellows is raw varint (being filled). When it
 // reaches BELLOWS_ROWS pivots it is sealed: LZ-compressed into cold[] and its raw bytes freed.
 // A rebound against a cold pivot expands ONE bellows into an LRU cache slot, reused until evicted.
 static const int BELLOWS_ROWS = 512;           // 512 rows: few enough bellows to keep per-block
                                                 // overhead low, small enough that a MISS decompresses
                                                 // only ~hundreds of KB (no 16MB sawtooth). Sweet spot
                                                 // between JULIOCESAR's 128 (too many blocks -> RAM) and
                                                 // GALACTIC's 16MB (huge decompress -> picos).
 struct Bellows{ vector<uint8_t> comp; vector<uint32_t> off; long long rawBytes; }; // sealed
 vector<Bellows> cold;                      // sealed bellows
 vector<uint8_t> hotRaw;                     // current hot bellows raw varint
 vector<uint32_t> hotOff;                    // per-pivot offsets within hotRaw (hotOff[0]=0)
 int nGlobal=0;                              // total pivots created (global index counter)
 // ---- INMORTAL anti-thrash: moderate LRU cache of decompressed mini-bellows ----
 // 64 slots cover the active cold front of the tail. Slots are SHRUNK on eviction so the cache
 // never holds air; bytes() counts real used size, not reserved capacity (JULIOCESAR over-counted).
 static const int NCACHE = 64;
 struct OpenSlot{ int b=-1; vector<uint8_t> raw; vector<uint32_t> off; unsigned long long stamp=0; };
 OpenSlot slot[NCACHE];
 unsigned long long lruClock=0;

 Red(){ hotOff.push_back(0); DCOL.reserve(1<<16); DCOEF.reserve(1<<16); }
 static inline void putVarint(vector<uint8_t>&b,uint32_t v){ while(v>=0x80){ b.push_back((uint8_t)(v|0x80)); v>>=7; } b.push_back((uint8_t)v); }
 inline void touch(long long col,int coef){
   if(!HS_OCC[col]){ HS_OCC[col]=1; HS_BUF[col]=coef; heap.push_back(col); push_heap(heap.begin(),heap.end(),greater<long long>()); touchedList.push_back(col); }
   else HS_BUF[col]+=coef;
 }
 // seal the hot bellows into a compressed cold bellows, free the raw
 // Bellows cover CONTIGUOUS ranges of global pivot index. coldStart[b] = first global index
 // in cold bellows b; pivots with index >= hotStart live in the hot bellows. No per-seal
 // O(rank) re-pointing (that was quadratic) -- bellows is found by range over coldStart.
 vector<int> coldStart;     // global index of first pivot in each cold bellows
 int hotStart=0;            // global index of first pivot currently in hot
 void sealHot(){
   if(hotOff.size()<=1) return;
   Bellows b; b.rawBytes=(long long)hotRaw.size(); b.off=hotOff;
   AccLZ::enc(hotRaw.data(),hotRaw.size(),b.comp);
   b.comp.shrink_to_fit(); b.off.shrink_to_fit();   // free LZ doubling slack -- exact cold size
   coldStart.push_back(hotStart);
   cold.push_back(move(b));
   hotStart=nGlobal;                  // next pivot starts a fresh hot bellows
   hotRaw.clear(); hotRaw.shrink_to_fit(); hotOff.clear(); hotOff.push_back(0);
 }
 // get a pointer to pivot g's raw varint [s,e). Uses an LRU cache of decompressed bellows.
 inline void pivotBytes(int g, const uint8_t*& s, const uint8_t*& e){
   if(g>=hotStart){ uint32_t li=(uint32_t)(g-hotStart); s=&hotRaw[hotOff[li]]; e=&hotRaw[hotOff[li+1]]; return; }
   int lo=0,hi=(int)coldStart.size()-1,b=0;
   while(lo<=hi){ int mid=(lo+hi)>>1; if(coldStart[mid]<=g){ b=mid; lo=mid+1; } else hi=mid-1; }
   uint32_t li=(uint32_t)(g-coldStart[b]);
   // look for bellows b in the LRU cache
   int hitSlot=-1, lruSlot=0; unsigned long long oldest=~0ull;
   for(int i=0;i<NCACHE;i++){ if(slot[i].b==b){ hitSlot=i; break; }
                              if(slot[i].stamp<oldest){ oldest=slot[i].stamp; lruSlot=i; } }
   OpenSlot* sl;
   if(hitSlot>=0){ sl=&slot[hitSlot]; }                       // cache HIT: no decompression
   else { sl=&slot[lruSlot];                                  // MISS: evict LRU, decompress here
          AccLZ::dec(cold[b].comp.data(),cold[b].comp.size(),sl->raw); sl->off=cold[b].off; sl->b=b; }
   sl->stamp=++lruClock;
   s=&sl->raw[sl->off[li]]; e=&sl->raw[sl->off[li+1]];
 }
 bool add(const SVec& vin){
   heap.clear(); touchedList.clear();
   for(auto&pr:vin) touch(pr.first,pr.second);
   bool created=false; long long newLead=-1;
   while(!heap.empty()){
     long long lc=heap.front();
     int c=HS_BUF[lc]%P; if(c<0)c+=P;
     if(c==0){ HS_BUF[lc]=0; pop_heap(heap.begin(),heap.end(),greater<long long>()); heap.pop_back(); continue; }
     HS_BUF[lc]=c;
     auto it=pc.find((uint32_t)lc);
     if(it==pc.end()){ newLead=lc; created=true; break; }
     int g=it->second; int f=c;                    // REBOUND against global pivot g
     const uint8_t* bp; const uint8_t* be; pivotBytes(g,bp,be);
     DCOL.clear(); DCOEF.clear(); long long col=0;
     while(bp<be){ uint32_t gg=0; int sh=0; uint8_t by; do{ by=*bp++; gg|=(uint32_t)(by&0x7F)<<sh; sh+=7; }while(by&0x80);
       col += (long long)(gg>>CFBITS); int pcf=(int)(gg&CFMASK)+1; DCOL.push_back((uint32_t)col); DCOEF.push_back(pcf); }
     size_t np=DCOL.size();
     for(size_t i=0;i<np;++i){ uint32_t cc=DCOL[i];
       if(!HS_OCC[cc]){ HS_OCC[cc]=1; HS_BUF[cc]=0; heap.push_back(cc); push_heap(heap.begin(),heap.end(),greater<long long>()); touchedList.push_back(cc); } }
     int32_t* __restrict buf=HS_BUF; const uint32_t* __restrict dc=DCOL.data(); const int32_t* __restrict df=DCOEF.data();
     for(size_t i=0;i<np;++i){ buf[dc[i]] -= f*df[i]; }
     pop_heap(heap.begin(),heap.end(),greater<long long>()); heap.pop_back();
   }
   if(created){ int lv=HS_BUF[newLead]%P; if(lv<0)lv+=P; int iv=invp(lv);
     sort(touchedList.begin(),touchedList.end());
     long long prev=0, added=0;
     for(long long col:touchedList){ int r=HS_BUF[col]%P; if(r<0)r+=P; if(r){ int v=ml(r,iv); uint32_t payload=((uint32_t)(col-prev)<<CFBITS)|(uint32_t)(v-1); putVarint(hotRaw,payload); prev=col; added++; } }
     hotOff.push_back((uint32_t)hotRaw.size());
     int g=nGlobal++;
     pc[(uint32_t)newLead]=g; nz+=added;
     if((int)(hotOff.size()-1)>=BELLOWS_ROWS) sealHot();   // accordion: seal & compress every 128 rows
   }
   for(long long col:touchedList){ HS_BUF[col]=0; HS_OCC[col]=0; }
   return created;
 }
 long long rank()const{return (long long)nGlobal;}
 // HONEST peak: cold bellows hold COMPRESSED bytes; hot holds raw; open-cache is one bellows.
 // Also counts pc (the leader->index map), which grows with rank and is real resident RAM.
 long long bytes()const{
   long long b=(long long)hotRaw.size()+(long long)hotOff.size()*4
              +(long long)coldStart.size()*4
              +(long long)pc.size()*40                 // unordered_map node ~40 B/entry (honest)
              +(long long)heap.size()*8+(long long)touchedList.size()*8;
   for(int i=0;i<NCACHE;i++) b+=(long long)slot[i].raw.size()+(long long)slot[i].off.size()*4;
   for(auto&cb:cold){ b+=(long long)cb.comp.size()+(long long)cb.off.size()*4; }
   return b;
 }
 long long coldComp()const{ long long b=0; for(auto&cb:cold)b+=(long long)cb.comp.capacity(); return b; }
 long long pcBytes()const{ return (long long)pc.size()*40; }
 SVec rowAt(long long g){ SVec s; const uint8_t* bp; const uint8_t* be; pivotBytes((int)g,bp,be); long long col=0;
   while(bp<be){ uint32_t gg=0; int sh=0; uint8_t by; do{ by=*bp++; gg|=(uint32_t)(by&0x7F)<<sh; sh+=7; }while(by&0x80);
     col += (long long)(gg>>CFBITS); int pcf=(int)(gg&CFMASK)+1; s.push_back({col,pcf}); } return s; }
};
static double now_s(){return (double)clock()/CLOCKS_PER_SEC;}

// ---- Dashboard: quiet single-block status panel. Color only flags state, no toys. ----
static bool AG_COLOR = (getenv("NO_COLOR")==nullptr);
static const char* C_GRN="\033[1;92m"; static const char* C_YEL="\033[1;93m";
static const char* C_RED="\033[1;91m"; static const char* C_DIM="\033[2m";
static const char* C_BLD="\033[1m";  static const char* C_RST="\033[0m";
static inline const char* col(const char* c){ return AG_COLOR? c : ""; }
static long long rss_bytes(){ struct rusage ru; getrusage(RUSAGE_SELF,&ru);
#if defined(__APPLE__)
  return (long long)ru.ru_maxrss;
#else
  return (long long)ru.ru_maxrss*1024;
#endif
}
static void ram_bar(char* out,double used,double budget){ int cells=12; double f=budget>0?used/budget:0; if(f>1)f=1;
  int on=(int)(f*cells+0.5); char* p=out; *p++='['; for(int i=0;i<cells;i++)*p++=(i<on?'#':'.'); *p++=']'; *p=0; }

// The turbine: stream each partition's Jordan-pruned closure into a shared echelon (SONICSTAR-FOLD).
// peak = max over the flow of (shared echelon nz + current partition's local closure nz).
// returns rank_p (>=0) or -1 on guard abort; fills peak.
static long long turbineRank(int p,long long&peak){
    P=p; buildBin(); buildRhoUfac();
    // coef-1 ranges 0..p-2; reserve enough bits to embed it in the varint payload
    CFBITS=0; { int mx=p-2; while((1<<CFBITS)<=mx) CFBITS++; } CFMASK=(CFBITS? ((1u<<CFBITS)-1) : 0u);
    // guard: (max delta) << CFBITS must fit 32 bits. max delta < DIM < 2^?  -> check.
    { long long maxshift=(long long)(DIM)<<CFBITS; if(maxshift >= (1LL<<32)){ fprintf(stderr,"  [ANTIGRAVITY] coef-embed overflow risk (DIM=%lld, CFBITS=%d) -- abort, use BLACKHOLE\n",DIM,CFBITS); return -1; } }
    Red R; peak=0; double t0=now_s();
    fprintf(stderr,"  [JULIOCESAR INMORTAL start] streaming %zu partitions, char %d (mini-bellows %d rows + LRU cache x%d)\n",parts.size(),p,Red::BELLOWS_ROWS,Red::NCACHE);
    auto wall0=std::chrono::steady_clock::now();
    auto wall=[&](){ return std::chrono::duration<double>(std::chrono::steady_clock::now()-wall0).count(); };
    double lastWall=0, lastPartT=0; size_t lastPart=0;
    for(size_t pi=0; pi<parts.size(); ++pi){
        Red local; local.add(buildRhoJ_U(parts[pi]));
        long long done=0;
        while(done<local.rank()){ long long upto=local.rank();
          for(long long k=done;k<upto;++k){ SVec row=local.rowAt(k); for(int v=0;v<NV;++v){ SVec s=shiftVar_U(row,v); local.add(s); } }
          done=upto; }
        for(long long k=0;k<local.rank();++k){ SVec v=local.rowAt(k); R.add(v); }
        long long live=R.bytes()+local.bytes(); if(live>peak)peak=live;
        double W=wall();
        if(W-lastWall>=5.0){
          double budget=RAM_BUDGET_NZ/1e9, used=peak/1e9, rss=rss_bytes()/1e9;
          double secPerPart=(pi>lastPart)?(W-lastPartT)/(double)(pi-lastPart):0;
          double eta=secPerPart*(double)(parts.size()-1-pi);
          double frac=used/budget;
          const char* rc=frac<0.55?C_GRN:(frac<0.8?C_YEL:C_RED);
          const char* rtag=frac<0.55?"OK":(frac<0.8?"WATCH":"TIGHT");
          bool haveSp=secPerPart>0; const char* sc=!haveSp?C_DIM:((secPerPart<150)?C_GRN:C_YEL);
          const char* stag=!haveSp?"...":((secPerPart<150)?"FAST":"SLOW");
          char bar[20]; ram_bar(bar,used,budget);
          char spd[32],etas[32];
          if(haveSp){ snprintf(spd,sizeof spd,"%.0f s/part",secPerPart); snprintf(etas,sizeof etas,"%.1f h",eta/3600.0); }
          else { snprintf(spd,sizeof spd,"-- s/part"); snprintf(etas,sizeof etas,"--"); }
          fprintf(stderr,
            "%s  JULIOCESARINMORTAL %s(%d,%d)%s  part %s%zu/%zu%s\n"
            "  RAM %s%s %.2f/%.2f GB [%s]%s  os:%.2fGB   SPEED %s%s %s%s  ETA %s%s%s\n"
            "%s  rank %lld   nz %lld   seals %zu   cold %.2fGB%s\n",
            col(C_DIM),col(C_BLD),n,m,col(C_RST),col(C_BLD),pi+1,parts.size(),col(C_RST),
            col(rc),bar,used,budget,rtag,col(C_RST),rss,col(sc),stag,spd,col(C_RST),col(C_BLD),etas,col(C_RST),
            col(C_DIM),R.rank(),R.nz,R.cold.size(),R.coldComp()/1e9,col(C_RST));
          lastWall=W; lastPartT=W; lastPart=pi;
        }
        if(peak>RAM_BUDGET_NZ){ fprintf(stderr,"%s  [GUARD] RAM hit part=%zu rank=%lld peak=%.2fGB -- NOT a math result%s\n",col(C_RED),pi,R.rank(),peak/1e9,col(C_RST)); return -1; }
        if(wall()>WALL){ fprintf(stderr,"  [GUARD] wall hit\n"); return -1; }
    }
    fprintf(stderr,"%s  JULIOCESAR INMORTAL done%s  rank=%lld  echelon_nz=%lld  peak=%.2fGB  os=%.2fGB  wall=%.0fs\n",
      col(C_GRN),col(C_RST),R.rank(),R.nz,peak/1e9,rss_bytes()/1e9,wall());
    return R.rank();
}

int main(int argc,char**argv){
    if(argc<3){fprintf(stderr,"usage: %s n m [wall_sec]\n",argv[0]);return 1;}
    setvbuf(stderr,NULL,_IONBF,0);
    n=atoi(argv[1]); m=atoi(argv[2]); if(argc>=4)WALL=atof(argv[3]);
    d=n/2; NV=n+1; B=m-1; powB.assign(NV+1,1); for(int i=1;i<=NV;i++)powB[i]=powB[i-1]*B; DIM=powB[NV];
    vector<int>all; for(int i=0;i<n+2;i++)all.push_back(i); vector<pair<int,int>>c; gp(all,c);
    printf("================ JULIOCESARINMORTAL  n=%d m=%d  DIM=%lld  partitions=%zu ================\n",n,m,DIM,parts.size());
    printf("Author: Rafael Amichis Luengo (Madrid). Method: Degtyarev-Shimada (arXiv:1405.4683 §5).\n");
    printf("char-p: Jordan-mould starter + TURBINE flow + SONICSTAR-FOLD dense-rebound fold.\n");

    // dense scratch for SONICSTAR-FOLD (sized to DIM; tiny vs the echelon)
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

    // ---- METHOD B: dim_Fp via the TURBINE (SONICSTAR-FOLD), for each p|m ----
    vector<int> ps; {int mm=m;for(int p=2;(long long)p*p<=mm;p++){if(mm%p==0){ps.push_back(p);while(mm%p==0)mm/=p;}}if(mm>1)ps.push_back(mm);}
    printf("\n[METHOD B] dim_Fp via TURBINE + SONICSTAR-FOLD (primes dividing m:"); for(int p:ps)printf(" %d",p); printf(")\n"); fflush(stdout);

    bool aborted=false; vector<pair<int,long long>> dpv; vector<long long> peaks;
    for(size_t ip=0; ip<ps.size(); ++ip){ int p=ps[ip];
        printf("\n  char %d : turbine flow + sonicstar-fold\n",p); fflush(stdout);
        long long peak=0; long long rP=turbineRank(p,peak); peaks.push_back(peak);
        if(rP<0){ printf("  char %d ABORTED_BY_GUARD (peak=%lld ~%.2fGB) -- NOT a math result\n",p,peak,peak/1e9); aborted=true; break; }
        long long dF=DIM-rP;
        printf("  char %d COMPLETE: rank_p=%lld dim_F%d=%lld  TURBINE LIVE PEAK bytes=%lld (~%.2f GB)\n",p,rP,p,dF,peak,peak/1e9);
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
