# LEGOLAS_PROBE_4_v1.py - 5 June 2026 - THE F6 TYPE SWEEP (cera, full executable)
# The Auditor's demanded falsifier, run BEFORE any "magic number" language could harden.
# Classifies ALL k-subsets of the 15 matchings into S6-orbit types (canonical form over the
# 720 permutations) and peels one representative per type at d=7 (mod 7^8).
# RESULTS OF RECORD:
#  - 4-subsets: 9 types (orbits 30,45,60,60,90,180,180,360,360; sum 1365 = C(15,4)).
#    h4 = 1 in SIX types; h4 = 0 in THREE ({0,1,2,3}, {0,1,3,11}, {0,1,3,14}).
#  - 3-subsets: 5 types (orbits 15,20,60,180,180; sum 455 = C(15,3)).
#    h4 = 1 in THREE types ({0,1,5}, {0,4,8}, {0,4,13}); h4 = 0 in TWO ({0,1,2}, {0,1,3}).
#  - 2-subsets: type-complete from Probe 1 (2 types, identical profile, h4 = 0).
#  => "BORN AT K=5" IS DEAD (its falsifier: this sweep). The statement of record:
#     THE HEIGHT-4 CLASS NEEDS A MINIMUM OF THREE FAMILIES, AND ITS PRESENCE IS A
#     SUBSET-TYPE INVARIANT, NOT A COUNT. The fixed enumeration (0,1,2,...) happens to
#     walk through h4-blind types until K=5 - the earlier ladder was measuring one path
#     up the mountain, not the mountain.
#  - UNIQUENESS UNIVERSAL: h4 = 1 in EVERY positive subset of every size tested (3,4,5,6,15):
#    the class saturates at ONE from first appearance, in every type that carries it.
#  - d=5 mid-ladder (fixed enumeration): K=4..8 ranks 193/229/253/285/313,
#    h3 = 4,7,7,7,7 (saturates at the full-assembly value 7 from K=5); h4 = 0 throughout.
import itertools, time
import numpy as np
src=open('GRAM_MANOMETER_PROBE_v1.py').read()
exec(src.split('def report(')[0])
Ms=list(matchings(list(range(6))))
def mkey(M): return tuple(sorted(tuple(sorted(p)) for p in M))
idx={mkey(M):i for i,M in enumerate(Ms)}
perms=list(itertools.permutations(range(6)))
act=[]
for s in perms:
    act.append(tuple(idx[mkey([tuple(sorted((s[a],s[b]))) for (a,b) in [tuple(sorted(p)) for p in M]])] for M in Ms))
def classify(k):
    types={}
    for sub in itertools.combinations(range(15),k):
        best=min(tuple(sorted(row[i] for i in sub)) for row in act)
        types.setdefault(best,[]).append(sub)
    return types
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
def subset_gram(d,sub):
    roots=[2*k+1 for k in range(d)]
    Ps=[]
    for i in sub:
        Ps+=[tuple(zip(Ms[i],es)) for es in itertools.product(roots,repeat=3)]
    val={2:d*d-3*d+3,1:2-d,0:1,-1:0}
    n=len(Ps); G=np.zeros((n,n),dtype=np.int64)
    for a in range(n):
        G[a,a]=val[2]
        Pa=Ps[a]
        for b in range(a+1,n):
            G[a,b]=G[b,a]=val[inter_dim(Pa,Ps[b],2*d)]
    return G
for k in [3,4]:
    tps=classify(k)
    print(f"{k}-subset types: {len(tps)}")
    for rep in sorted(tps.keys()):
        G=subset_gram(7,rep)
        c=peel(G,7,7**8,6)
        print(f"  type {rep} (orbit {len(tps[rep])}): rank {rank_modp(G,1000003)} heights {c}",flush=True)
for K in [4,5,6,7,8]:
    G=subset_gram(5,list(range(K)))
    print(f"d=5 K={K}: rank {rank_modp(G,1000003)} heights {peel(G,5,5**8,6)}",flush=True)
