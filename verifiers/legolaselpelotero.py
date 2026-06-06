#!/usr/bin/env python3
# =====================================================================================
# legolaselpelotero.py - 5 June 2026 - THE BEETLE'S BALL: the (4,9) full-lattice shot
# Engine named by the Architect (D26). Operacion LEGOLAS, second leg.
#
# MANIFEST (per the new audit protocol):
#   GATE 1 [SEALED-ANCHOR]: (4,3) full cell at mod 3^17 -> rank 21, heights {0:19, 1:1, 2:1}
#       (campaign gate, SAME prime as the target; output line "GATE (4,3) ... PASS")
#   GATE 2 [SEALED-ANCHOR]: single family d=9 -> rank 513, 3-adic {0:23, 2:147, 4:343}
#       (sealed this session, certifies the d=9 plane/Gram machinery; line "GATE fam d=9 ... PASS")
#   THE SHOT [NEW]: full (4,9), 10935 planes. SEALED PREDICTION (written before this run):
#       rank = 8001 (character counter 8000 + 1; the counter is gated HIT at every prime power
#       tested and MISS only at two-distinct-prime d=6). NO height-profile counts committed
#       (the (4,7) graveyard lesson). Output: "VERDICT (4,9): rank = R (SEAL 8001: HIT/MISS)"
#       plus the full 3-adic height profile (12 explicit levels) and E_3.
#
# EXPECTED OUTPUT (for the Auditor's diff; bracketed numbers are the only unknowns):
#   GATE (4,3) at mod 3^17: {0: 19, 1: 1, 2: 1, 3: 0} -> PASS
#   GATE fam d=9: rank 513 heights {0: 23, 1: 0, 2: 147, 3: 0, 4: 343, 5: 0, ...} -> PASS
#   VERDICT (4,9): rank = [R] (SEAL 8001: [HIT/MISS])
#     3-adic height counts: {0: [..], 1: [..], ..., 11: [..]}; unaccounted beyond 11: [0?]
#     3-adic exponent E = [..]
#
# Innovations credited to the Architect (Rafael Amichis Luengo): the sealed-rank discipline;
# the prime-power signature finding (family heights even-only; odd heights are pure coupling)
# that this run tests at full assembly; the demand that no profile be guessed in advance.
# Technique: valuation peeling at mod 3^17 (int64-safe: (3^17)^2 = 1.7e16 << 9.2e18; margin
# 5 powers after 12 levels) with column-dropping elimination (exact: full clearing above+below).
# RAM ledger: Gram 956 MB int64 + one working copy ~= 2.1 GB peak, inside the 5.4 GB guard.
# Heartbeat ~2 s, unbuffered. ETA at 25% single-thread: ~60-90 min wall.
# Mac form (byte-exact):
#   cd ~/Downloads && time caffeinate -dims taskpolicy -c utility python3 legolaselpelotero.py 2>&1 | tee legolaselpelotero_4_9_run1.log
# =====================================================================================
import sys, time, itertools
import numpy as np
T0=time.time()
def hb(msg): print(f"[{time.time()-T0:8.1f}s] {msg}", flush=True)
def matchings(verts):
    if not verts: yield []; return
    a=verts[0]
    for i in range(1,len(verts)):
        b=verts[i]; rest=verts[1:i]+verts[i+1:]
        for m_ in matchings(rest): yield [(a,b)]+m_
def inter_dim(P,Q,mod):
    par={}; pot={}
    def root(x):
        if x not in par: par[x]=x; pot[x]=0
        if par[x]==x: return x,0
        r,p=root(par[x]); par[x]=r; pot[x]=(pot[x]+p)%mod
        return r,pot[x]
    bad=set()
    for (i,j),e in list(P)+list(Q):
        ri,pi=root(i); rj,pj=root(j)
        if ri!=rj: par[rj]=ri; pot[rj]=(pi+e-pj)%mod
        elif (pi+e-pj)%mod: bad.add(ri)
    comps=set(); badroots={root(b)[0] for b in bad}
    for v in list(par): comps.add(root(v)[0])
    return sum(1 for r in comps if r not in badroots)-1
def build_gram(d,subset=None):
    Ms=list(matchings(list(range(6))))
    if subset is not None: Ms=[Ms[i] for i in subset]
    roots=[2*k+1 for k in range(d)]
    Ps=[]
    for M in Ms:
        Ps+=[tuple(zip(M,es)) for es in itertools.product(roots,repeat=3)]
    val={2:d*d-3*d+3,1:2-d,0:1,-1:0}
    n=len(Ps)
    hb(f"building Gram d={d}{' (subset)' if subset else ''}: {n} planes")
    G=np.zeros((n,n),dtype=np.int64); last=time.time()
    for a in range(n):
        G[a,a]=val[2]
        Pa=Ps[a]
        for b in range(a+1,n):
            G[a,b]=G[b,a]=val[inter_dim(Pa,Ps[b],2*d)]
        if time.time()-last>2: hb(f"  Gram rows {a+1}/{n}"); last=time.time()
    hb(f"Gram built: {n}x{n}, {G.nbytes>>20} MB")
    return G
def rank_modp(A,q):
    A=(A%q).astype(np.int64).copy(); n,c=A.shape; r=0; last=time.time()
    for jj in range(c):
        nz=np.nonzero(A[r:,jj]%q)[0]
        if len(nz)==0: continue
        i=nz[0]+r
        if i!=r: A[[r,i],:]=A[[i,r],:]
        inv=pow(int(A[r,jj]),-1,q)
        f=(A[r+1:,jj]*inv)%q
        A[r+1:,jj:]=(A[r+1:,jj:]-f[:,None]*A[r,jj:][None,:])%q
        r+=1
        if time.time()-last>2: hb(f"  rank pass: {r} pivots"); last=time.time()
        if r==n: break
    return r
P=3; MOD=P**17
def peel(Acur,levels,tag):
    counts={}
    for v in range(levels):
        if not Acur.size:
            counts[v]=0; continue
        Ar=(Acur%MOD).copy(); nloc,ncol=Ar.shape
        rr=0; piv=[]; last=time.time()
        for c in range(ncol):
            nz=np.nonzero(Ar[rr:,c]%P)[0]
            if len(nz)==0: continue
            i=nz[0]+rr
            if i!=rr: Ar[[rr,i],:]=Ar[[i,rr],:]
            inv=pow(int(Ar[rr,c])%MOD,-1,MOD)
            f=(Ar[rr+1:,c]*inv)%MOD
            Ar[rr+1:,:]=(Ar[rr+1:,:]-f[:,None]*Ar[rr,:][None,:])%MOD
            f2=(Ar[:rr,c]*inv)%MOD
            Ar[:rr,:]=(Ar[:rr,:]-f2[:,None]*Ar[rr,:][None,:])%MOD
            piv.append(c); rr+=1
            if time.time()-last>2: hb(f"  [{tag}] level {v}: {rr} pivots"); last=time.time()
            if rr==nloc: break
        counts[v]=rr
        keep=[c for c in range(ncol) if c not in set(piv)]
        rem=Ar[rr:,:][:,keep]
        assert (rem%P==0).all(), f"peel violation level {v} - ABORT"
        Acur=rem//P
        hb(f"  [{tag}] level {v} done: {rr} divisors; residual {Acur.shape}")
    return counts
# ---- GATE 1 [SEALED-ANCHOR]: (4,3) full cell, same prime as the target
hb("legolaselpelotero - THE BEETLE'S BALL (4,9). Gates first.")
G3=build_gram(3)
c3=peel(G3,4,"gate1")
g1=(c3.get(0)==19 and c3.get(1)==1 and c3.get(2)==1 and c3.get(3,0)==0)
hb(f"GATE (4,3) at mod 3^17: {c3} -> {'PASS' if g1 else 'FAIL - ABORT'}")
if not g1: sys.exit(1)
del G3
# ---- GATE 2 [SEALED-ANCHOR]: single family d=9 (flat law, sealed this session)
Gf=build_gram(9,subset=[0])
rkf=rank_modp(Gf,1000003)
cf=peel(Gf,6,"gate2")
g2=(rkf==513 and cf.get(0)==23 and cf.get(2)==147 and cf.get(4)==343 and cf.get(1,0)==0 and cf.get(3,0)==0)
hb(f"GATE fam d=9: rank {rkf} heights {cf} -> {'PASS' if g2 else 'FAIL - ABORT'}")
if not g2: sys.exit(1)
del Gf
# ---- THE SHOT [NEW]: full (4,9)
hb("THE SHOT: (4,9), 10935 planes. SEAL ON THE TABLE: rank 8001. No profile committed.")
G=build_gram(9)
rk=rank_modp(G,1000003)
hb(f"rank = {rk} (SEAL 8001: {'HIT' if rk==8001 else 'MISS - high information, do not dismiss'})")
counts=peel(G,12,"4,9")
E=sum(k*v for k,v in counts.items())
deep=rk-sum(counts.values())
hb("="*70)
hb(f"VERDICT (4,9): rank = {rk} (SEAL 8001: {'HIT' if rk==8001 else 'MISS'})")
hb(f"  3-adic height counts: {counts}")
hb(f"  unaccounted beyond height 11: {deep}")
hb(f"  3-adic exponent E = {E}")
hb("Done. PMC.")
