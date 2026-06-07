// GANDALFSONRIE - christened by the Architect (D26): Gandalf smiles because he knows the answer before the shot.
// PURPOSE: p-adic elementary-divisor profile of the Fermat-surface line lattice V(2,m),
//   for the GANDALF ring campaign (|disc NS/V| for ALL Fermat surfaces).
// METHOD: line Gram via the SSvL intersection rules with the omega^2-corrected (1,3) rule
//   [even-capable; Rafa's campaign instrument v4 semantics, ported byte-exact to C++];
//   layered p-adic elimination with shrinking modulus (the campaign's self-caught
//   precision fix v2->v3 inherited); int64 modular arithmetic, K chosen so p^K < 2^31.5.
// INNOVATIONS (campaign-owned): the shrinking-modulus layer count IS the elementary-divisor
//   height histogram; checkpointing every CKPT_SEC seconds for window-sliced or abortable runs.
// OUTPUT: rank, p-exponent, full height profile - the GANDALF measurement.
// Heartbeat: progress every ~3s, unbuffered.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <ctime>
using namespace std;
typedef long long ll;
static double t0;
double wall(){ return (double)clock()/CLOCKS_PER_SEC; }
int main(int argc,char**argv){
    setvbuf(stdout,NULL,_IONBF,0);
    t0=wall();
    if(argc<4){ printf("usage: %s m p K [ckptfile]\n",argv[0]); return 1; }
    int m=atoi(argv[1]); ll p=atoll(argv[2]); int K=atoi(argv[3]);
    const char*ck=(argc>4)?argv[4]:0;
    int n=3*m*m;
    ll modr0=1; for(int i=0;i<K;i++) modr0*=p;
    printf("[%6.1fs] GANDALF ELIMINATOR: m=%d (n=%d lines), p=%lld, K=%d (mod %lld)\n",wall()-t0,m,n,p,K,modr0);
    vector<ll> M; M.assign((size_t)n*n,0);
    ll modr=modr0; int r=0, shift=0; vector<ll> counts(64,0);
    FILE*cf = ck? fopen(ck,"rb") : 0;
    if(cf){
        size_t got=0;
        got+=fread(&modr,sizeof(ll),1,cf); got+=fread(&r,sizeof(int),1,cf); got+=fread(&shift,sizeof(int),1,cf);
        got+=fread(counts.data(),sizeof(ll),64,cf); got+=fread(M.data(),sizeof(ll),(size_t)n*n,cf); fclose(cf);
        if(got != 3+64+(size_t)n*n){ printf("CHECKPOINT CORRUPT (read %zu items) - delete %s and restart\n",got,ck); return 1; }
        printf("[%6.1fs] RESUMED from checkpoint: r=%d shift=%d\n",wall()-t0,r,shift);
    } else {
        // build Gram: lines indexed (f,k,l), f in 0..2, k,l in 0..m-1; index = f*m*m + k*m + l
        for(int f1=0;f1<3;f1++)for(int k1=0;k1<m;k1++)for(int l1=0;l1<m;l1++){
            size_t i=(size_t)f1*m*m+(size_t)k1*m+l1;
            for(int f2=0;f2<3;f2++)for(int k2=0;k2<m;k2++)for(int l2=0;l2<m;l2++){
                size_t j=(size_t)f2*m*m+(size_t)k2*m+l2;
                ll v=0;
                if(i==j) v=2-m;
                else if(f1==f2) v=(k1==k2||l1==l2)?1:0;
                else {
                    int fa=f1,fb=f2,ka=k1,la=l1,kb=k2,lb=l2;
                    if(fa>fb){ fa=f2;fb=f1;ka=k2;la=l2;kb=k1;lb=l1; }
                    if(fa==0&&fb==1) v=(((ka-la-kb+lb)%m+m)%m==0)?1:0;
                    else if(fa==1&&fb==2) v=(((ka+la-kb-lb)%m+m)%m==0)?1:0;
                    else v=(((kb-(ka+la+lb+1))%m+m)%m==0)?1:0; // (1,3) omega^2 rule: k' = k+l+l'+1
                }
                M[i*n+j]=((v%modr)+modr)%modr;
            }
        }
        printf("[%6.1fs] Gram built\n",wall()-t0);
    }
    double lasthb=wall(), lastck=wall();
    while(r<n){
        // find unit pivot in M[r:,r:] (mod p)
        ll pr=-1,pc=-1;
        for(ll i=r;i<n&&pr<0;i++){
            const ll*row=&M[(size_t)i*n];
            for(ll j=r;j<n;j++) if(row[j]%p){ pr=i;pc=j;break; }
        }
        if(pr<0){
            // no unit: check all-zero (done) or peel a layer
            bool allz=true;
            for(ll i=r;i<n&&allz;i++){ const ll*row=&M[(size_t)i*n]; for(ll j=r;j<n;j++) if(row[j]%modr){allz=false;break;} }
            if(allz) break;
            if(modr==p){ printf("PRECISION EXHAUSTED - raise K\n"); return 1; }
            modr/=p; shift++;
            for(ll i=r;i<n;i++){ ll*row=&M[(size_t)i*n]; for(ll j=r;j<n;j++) row[j]=(row[j]/p)%modr; }
            continue;
        }
        if(pr!=r) for(ll j=0;j<n;j++) swap(M[(size_t)r*n+j],M[(size_t)pr*n+j]);
        if(pc!=r) for(ll i=0;i<n;i++) swap(M[(size_t)i*n+r],M[(size_t)i*n+pc]);
        // modular inverse of M[r][r] mod modr (extended euclid)
        ll a=M[(size_t)r*n+r]%modr,b=modr,x0=1,x1=0;
        while(b){ ll q=a/b, t=a-q*b; a=b;b=t; t=x0-q*x1; x0=x1; x1=t; }
        ll inv=((x0%modr)+modr)%modr;
        const ll*rowr=&M[(size_t)r*n];
        for(ll i=r+1;i<n;i++){
            ll*rowi=&M[(size_t)i*n];
            ll f=(rowi[r]*inv)%modr;
            if(!f) continue;
            for(ll j=r;j<n;j++){ rowi[j]=(rowi[j]-f*rowr[j])%modr; if(rowi[j]<0) rowi[j]+=modr; }
        }
        // column clear via symmetric structure is NOT assumed (post-pivot rows already cleared below r); clear row r's tail influence on columns implicitly handled by row ops only (row echelon suffices for SNF heights with symmetric start + full row+col in python version; here do explicit column ops):
        for(ll j=r+1;j<n;j++){
            ll f=(M[(size_t)r*n+j]*inv)%modr;
            if(!f) continue;
            for(ll i=r;i<n;i++){ ll &mij=M[(size_t)i*n+j]; mij=(mij-f*M[(size_t)i*n+r])%modr; if(mij<0)mij+=modr; }
        }
        counts[shift]++; r++;
        if(wall()-lasthb>3.0){ printf("[%6.1fs] pivot %d/%d shift=%d\n",wall()-t0,r,n,shift); lasthb=wall(); }
        if(ck && wall()-lastck>240.0){
            FILE*cf2=fopen(ck,"wb");
            fwrite(&modr,sizeof(ll),1,cf2); fwrite(&r,sizeof(int),1,cf2); fwrite(&shift,sizeof(int),1,cf2);
            fwrite(counts.data(),sizeof(ll),64,cf2); fwrite(M.data(),sizeof(ll),(size_t)n*n,cf2); fclose(cf2);
            printf("[%6.1fs] checkpoint written (r=%d)\n",wall()-t0,r); lastck=wall();
        }
    }
    ll rank=0,expo=0;
    printf("RESULT m=%d p=%lld: profile {",m,p);
    for(int h=0;h<64;h++) if(counts[h]){ printf(" %d:%lld",h,counts[h]); rank+=counts[h]; expo+=(ll)h*counts[h]; }
    printf(" } rank %lld exp %lld\n",rank,expo);
    return 0;
}
