// DOBERMAN_v2 : family-wide sweep. Auto-enumerates EVERY Fermat cell up to a DIM ceiling,
// sorts cheapest-first (carne early), computes eigenbasis dim_C per cell, writes each line LIVE.
// Core eigen_dimC is BYTE-EXACT from SELLO_A.cpp (extracted byte-exact from HOUDINI.cpp).
// NO real reduction, NO floating point. dim_C only (char-LARGE half, DS Thm 1.4). Flat RAM, no swap.
// CLI:  ./doberman_v2 <DIM_ceiling>     (default 50,000,000)
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
static int n,m,d,NV,B,P; static long long DIM; static vector<long long> powB;
static vector<vector<pair<int,int>>> parts;
static inline int ad(int a,int b){a+=b;if(a>=P)a-=P;return a;}
static inline int ml(long long a,long long b){return(int)((a*b)%P);}
static int pw(int a,long long e){int r=1;a%=P;if(a<0)a+=P;while(e){if(e&1)r=ml(r,a);a=ml(a,a);e>>=1;}return r;}
static void gp(vector<int>&av,vector<pair<int,int>>&c){if(av.empty()){parts.push_back(c);return;}int a=av[0];for(size_t bi=1;bi<av.size();++bi){int b=av[bi];vector<int>nx;for(size_t i=1;i<av.size();++i)if((int)i!=(int)bi)nx.push_back(av[i]);c.push_back({a,b});gp(nx,c);c.pop_back();}}
// ---- METHOD A byte-exact from HOUDINI (via SELLO_A) ----
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
static bool isPrime(int x){ if(x<2)return false; for(int i=2;(long long)i*i<=x;i++) if(x%i==0)return false; return true; }
static long long dfact(int k){ long long r=1; while(k>0){r*=k;k-=2;} return r; }

static bool setupCell(int nn,int mm){
    n=nn; m=mm; d=n/2; NV=n+1; B=m-1;
    powB.assign(NV+1,1); for(int i=1;i<=NV;i++) powB[i]=powB[i-1]*B; DIM=powB[NV];
    parts.clear();
    vector<int> all; for(int i=0;i<n+2;i++) all.push_back(i);
    vector<pair<int,int>> c; gp(all,c);
    return true;
}

struct Cell{ int n,m; long long DIM, parts_count, cost; };

int main(int argc,char**argv){
    long long CEIL = (argc>=2)? atoll(argv[1]) : 50000000LL;

    // ---- enumerate the whole family up to CEIL, sort cheapest first ----
    vector<Cell> fam;
    for(int nn=4; nn<=16; nn+=2){
        for(int mm=3; mm<=15; mm++){
            int dd=nn/2;
            long long dimv=1; bool ovf=false;
            for(int i=0;i<nn+1;i++){ dimv*=(mm-1); if(dimv>(long long)4e18){ovf=true;break;} }
            if(ovf || dimv>CEIL) continue;
            long long pc = dfact(2*dd+1);
            fam.push_back({nn,mm,dimv,pc,dimv*pc});
        }
    }
    sort(fam.begin(),fam.end(),[](const Cell&a,const Cell&b){return a.cost<b.cost;});

    setvbuf(stdout,nullptr,_IONBF,0); // unbuffered: live heartbeat per cell
    printf("DOBERMAN_v2 family sweep  DIM_ceiling=%lld  cells=%zu\n",CEIL,fam.size());
    printf("%-8s %-12s %-9s %-13s %-7s %-7s %-8s %-10s\n",
           "cell","DIM","parts","dim_C","off346","mprime","suspect","wall_s");
    printf("--------------------------------------------------------------------------------\n");

    for(size_t i=0;i<fam.size();++i){
        int nn=fam[i].n, mm=fam[i].m, dd=nn/2;
        bool off=(mm!=3&&mm!=4&&mm!=6), mp=isPrime(mm);
        bool susp=(dd>=3)&&(off||mp);
        char cn[16]; snprintf(cn,sizeof(cn),"(%d,%d)",nn,mm);

        setupCell(nn,mm);
        clock_t t0=clock();
        long long base=(1000000/mm)+1; int Pk,zk; long long dC=-1;
        if(findPrimeRoot(mm,base,Pk,zk)) dC=eigen_dimC(Pk,zk);
        double wall=double(clock()-t0)/CLOCKS_PER_SEC;

        printf("%-8s %-12lld %-9lld %-13lld %-7s %-7s %-8s %-10.3f\n",
               cn,DIM,fam[i].parts_count,dC,off?"yes":"no",mp?"yes":"no",susp?"yes":"no",wall);
    }
    printf("--------------------------------------------------------------------------------\n");
    printf("done. dim_C = char-LARGE half (DS Thm 1.4). scar (char-p) is a separate run.\n");
    return 0;
}
