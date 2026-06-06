# LEGOLAS_PROBE_3_v1.py - 5 June 2026 - THE FAMILY COLLEJADA: the d=7 coupling ladder (cera, executable)
# Requires GRAM_MANOMETER_PROBE_v1.py on path. Fixed matching enumeration (first K of the 15).
# DECLARED before running: h3 > 0 at K=2 (pairwise, like d=5) [HIT]; h4 first born at K=3 [MISS - autopsy:
# the naive "rung r needs (r-1)-wise coupling" pattern is DEAD; declared, measured, killed].
# THE LADDER OF RECORD (d=7, ranks and height profiles):
#   K=1: 217  {17, 75, 125}                      (flat law)
#   K=2: 397  {35, 174, 173, 15}                 (height 3 born pairwise - HIT)
#   K=3: 541  {53, 268, 195, 25}
#   K=4: 721  {89, 325, 273, 34}
#   K=5: 871  {124, 395, 304, 47, 1}   <- *** HEIGHT 4 BORN AT K=5 ***
#   K=6: 991  {153, 467, 313, 57, 1}
#   K=15 (full): 1861 {443, 854, 504, 59, 1}     (the record cell)
# FINDINGS: (F4) the lone height-4 class is born in 5-family coupling and is UNIQUE AND STABLE
# from birth to the full assembly. (F5) d-dependence of the top rung: d=5 never reaches height 4
# (even 15-wise); d=7 reaches it 5-wise; (4,6) 3-adic carries 16 such classes. (F6) the birth-K
# is an observable of this enumeration; subset-type dependence is an open refinement (the pair
# symmetry suggested type-blindness, but >=4-subsets have richer matching-overlap types).
import itertools, time
import numpy as np
src=open('GRAM_MANOMETER_PROBE_v1.py').read()
exec(src.split('def report(')[0])
def rank_modp(A,q):
    A=(A%q).astype(np.int64).copy(); nn,c=A.shape; r=0
    for jj in range(c):
        nz=np.nonzero(A[r:,jj]%q)[0]
        if len(nz)==0: continue
        i=nz[0]+r
        if i!=r: A[[r,i],:]=A[[i,r],:]
        inv=pow(int(A[r,jj]),-1,q)
        f=(A[r+1:,jj]*inv)%q
        A[r+1:,jj:]=(A[r+1:,jj:]-f[:,None]*A[r,jj:][None,:])%q
        r+=1
        if r==nn: break
    return r
def peel(Acur,P,M,levels):
    counts={}
    for v in range(levels):
        if not Acur.size: counts[v]=0; continue
        Ar=(Acur%M).copy(); nloc,ncol=Ar.shape
        rr=0; piv=[]
        for c in range(ncol):
            nz=np.nonzero(Ar[rr:,c]%P)[0]
            if len(nz)==0: continue
            i=nz[0]+rr
            if i!=rr: Ar[[rr,i],:]=Ar[[i,rr],:]
            inv=pow(int(Ar[rr,c])%M,-1,M)
            f=(Ar[rr+1:,c]*inv)%M
            Ar[rr+1:,:]=(Ar[rr+1:,:]-f[:,None]*Ar[rr,:][None,:])%M
            f2=(Ar[:rr,c]*inv)%M
            Ar[:rr,:]=(Ar[:rr,:]-f2[:,None]*Ar[rr,:][None,:])%M
            piv.append(c); rr+=1
            if rr==nloc: break
        counts[v]=rr
        keep=[c for c in range(ncol) if c not in set(piv)]
        rem=Ar[rr:,:][:,keep]
        assert (rem%P==0).all()
        Acur=rem//P
    return counts
def kfam_gram(d,K):
    Ms=list(matchings(list(range(6))))[:K]
    roots=[2*k+1 for k in range(d)]
    Ps=[]
    for M in Ms:
        Ps+=[tuple(zip(M,es)) for es in itertools.product(roots,repeat=3)]
    val={2:d*d-3*d+3,1:2-d,0:1,-1:0}
    n=len(Ps); G=np.zeros((n,n),dtype=np.int64)
    for a in range(n):
        G[a,a]=val[2]
        Pa=Ps[a]
        for b in range(a+1,n):
            G[a,b]=G[b,a]=val[inter_dim(Pa,Ps[b],2*d)]
    return G
for K in [2,3,4,5]:
    G=kfam_gram(7,K)
    print(f"d=7 K={K}: rank {rank_modp(G,1000003)} heights {peel(G,7,7**8,6)}",flush=True)
