# GRAM PRESSURE-TEST SNIFF v1 (sandbox probe, <5 min)
# Instrument: Gram matrix of the DS linear cycles (d-planes), Smith form
#   -> rank (gate vs DS rank) + elementary divisors of L*/L (the disc group).
# Exact arithmetic: roots of -1 encoded as odd exponents mod 2m; intersection
#   dimension via union-graph components with potential consistency (Z/2m).
# Intersection values (d=2, fourfold X_m in P^5, all derived, see notes):
#   self  = m^2-3m+3   (deg c_2(N), N from 0->N->O(1)^3->O(m)->0)
#   line  = 2-m        (excess: c1(N_{S/X})|_C - c1(N_C/S') = (3-m)-1)
#   point = 1          (transverse in X)
# d=1 (surface in P^3): self = 2-m, point = 1.
import itertools, sys, time
from sympy import Matrix, ZZ
from sympy.matrices.normalforms import smith_normal_form

def matchings(verts):
    if not verts: yield []; return
    a = verts[0]
    for i in range(1, len(verts)):
        b = verts[i]; rest = verts[1:i]+verts[i+1:]
        for m_ in matchings(rest): yield [(a,b)]+m_

def planes(n, m):
    d = n//2; V = list(range(n+2)); out=[]
    roots = [2*k+1 for k in range(m)]            # odd exponents mod 2m: w^e, e odd => (w^e)^m = -1
    for M in matchings(V):
        for es in itertools.product(roots, repeat=d+1):
            out.append(tuple(zip(M, es)))        # edge (i,j) means x_j = w^e x_i
    return out

def inter_dim(P, Q, mod):
    # union graph potentials; returns projective dim of P∩Q (-1 empty)
    par = list(range(max(max(i,j) for (i,j),_ in P)+1)); pot=[0]*len(par); alive=[True]*len(par)
    def find(x):
        path=[]
        while par[x]!=x: path.append(x); x=par[x]
        s=0
        for v in reversed(path):
            s=(s+pot[v]); # accumulate? need root-relative; do two-pass
        # simpler: iterative find with potential compression
        return x
    # implement union-find with potentials properly
    par = {}; pot = {}
    def root(x):
        if x not in par: par[x]=x; pot[x]=0
        if par[x]==x: return x,0
        r,p = root(par[x]); par[x]=r; pot[x]=(pot[x]+p)%mod
        return r, pot[x]
    bad=set()
    for (i,j),e in list(P)+list(Q):
        ri,pi = root(i); rj,pj = root(j)
        if ri!=rj:
            # x_j = w^e x_i ; x_i = w^pi x_ri ; x_j = w^pj x_rj => x_rj = w^{pi+e-pj} x_ri
            par[rj]=ri; pot[rj]=(pi+e-pj)%mod
        else:
            if (pi+e-pj)%mod != 0: bad.add(ri)
    comps={}
    for v in list(par):
        r,_=root(v); comps.setdefault(r,0)
    good = sum(1 for r in comps if root(r)[0] not in {root(b)[0] for b in bad})
    return good-1

def gram(n, m):
    d=n//2; mod=2*m; Ps=planes(n,m); N=len(Ps)
    if d==1: val={1:2-m, 0:1, -1:0}
    elif d==2: val={2:m*m-3*m+3, 1:2-m, 0:1, -1:0}
    G=[[0]*N for _ in range(N)]
    for a in range(N):
        G[a][a]=val[d]
        for b in range(a+1,N):
            k=inter_dim(Ps[a],Ps[b],mod)
            if k==d: print("WARNING duplicate planes",a,b)
            G[a][b]=G[b][a]=val[k]
    return Matrix(G), N

def report(tag, n, m, expect_rank=None):
    t0=time.time(); G,N=gram(n,m)
    r=G.rank()
    print(f"[{tag}] ({n},{m}): N={N} planes, Gram rank={r}", "GATE OK" if expect_rank in (None,r) else f"GATE FAIL expect {expect_rank}", flush=True)
    t1=time.time()
    S=smith_normal_form(G, domain=ZZ)
    divs=[S[i,i] for i in range(min(S.shape)) if S[i,i]!=0]
    nz=[abs(int(x)) for x in divs]
    disc=1
    for x in nz: disc*=x
    nontriv=[x for x in nz if x!=1]
    print(f"   nonzero Smith divisors: {len(nz)} total, nontrivial: {nontriv}, disc={disc}  (build {t1-t0:.1f}s, SNF {time.time()-t1:.1f}s)", flush=True)
    return r, nontriv, disc

# GATE 1: cubic surface (2,3): 27 lines, NS unimodular rank 7, disc 1
report("GATE", 2, 3, expect_rank=7)
# GATE 2: quartic surface (2,4): 48 lines, NS rank 20, disc 64 (E8^2+U+<-8>^2), lines generate (Degtyarev Thm 1.2)
report("GATE", 2, 4, expect_rank=20)

# GATE 3: quintic surface (2,5): 75 lines, rank must be DS_2(5)+1 = 37 (lines generate, m prime to 6)
report("GATE", 2, 5, expect_rank=37)
# THE JUMP: Fermat cubic fourfold (4,3): 405 planes, rank must be DS_4(3)+1 = 21
report("FOURFOLD", 4, 3, expect_rank=21)

# GATE 3: quintic surface (2,5): 75 lines, rank must be DS_2(5)+1 = 37 (lines generate, m prime to 6)
report("GATE", 2, 5, expect_rank=37)
# THE JUMP: Fermat cubic fourfold (4,3): 405 planes, rank must be DS_4(3)+1 = 21
report("FOURFOLD", 4, 3, expect_rank=21)

# =====================================================================
# RESULTS LOG (sandbox, 4 June 2026) — all gates byte-exact:
#   (2,3): rank 7,  divisors trivial, disc 1        [classical I_{1,6}]
#   (2,4): rank 20, divisors [8,8], disc 64         [E8^2+U+<-8>^2, literature]
#   (2,5): rank 37 = DS_2(5)+1                      [rank gate]
#   (4,3): rank 21, PSD, divisors [3,9], disc 27    [405 planes; Voisin rules 0/1/-1]
#   (4,4): rank 142 = DS_4(4)+1, PSD, 2-primary only (p scanned to 31):
#          (Z/2)^2 (Z/4)^4 (Z/8)^30 (Z/16)^4 (Z/32)^2, disc 2^126
#          l(G) = 42 = rank(T) exactly (theoretical ceiling met).
# p-adic SNF (padic_divisor_valuations) gated on (4,3) -> [3,9] OK.
# Caveat: line-excess value 2-m literature-confirmed only at m=3.
# =====================================================================
