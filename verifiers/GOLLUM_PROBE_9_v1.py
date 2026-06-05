# GOLLUM_PROBE_9_v1.py - 5 June 2026 - THE AUTOGRAPH SESSION (cera, full executable)
# Phase A finding (shirt-shake): the induced bar-b Gram of the nine shadows is SINGULAR with structure:
# the six increments v_j,w_j are TOTALLY ISOTROPIC within the shadow; the u-block is the arithmetic
# Toeplitz u_i.u_j = (m-7)/2 - (i+j) mod m, rank exactly 2 (fits at m=5,7,11,13: corners -1/0/2/3).
# => the Gram route cannot seal independence (degenerate restriction != dependence) - logged.
# Phase B (THE AUTOGRAPH): canonical B-readers exist because the piece Gram is = 0 mod m (from the
# fiber identities: entries 2m - m^2 delta), so pb(e_r)/m and a0/m are explicit order-m dual classes:
# e-reader = family-pair constants (2/1/0), sigma-reader = pencil-slope linear position. The 9x9
# evaluation is block-triangular (e-readers kill all increments exactly) and
#   *** det = 6 mod m at ALL FOUR PRIMES (1=6 mod 5; 6,6,6) ***
# a UNIFORM integer constant, unit for every prime m>=5 since gcd(6,m)=1 - the SSvL condition itself.
# (E1) INDEPENDENCE SEALED UNIFORMLY. Declared-then-measured at m = 5,7,11,13.
import numpy as np, time
from sympy import Matrix
exec(open('GRANSLAP_PROBE_v1.py').read().split("for m in [5,7]:")[0])
from math import gcd as g_
for m in [5,7,11,13]:
    N=3*m*m; G=gram(m)
    k=np.arange(m*m)//m; l=np.arange(m*m)%m
    def pb(j,a,b,f):
        xv=(a*k+b*l)%m
        v=np.zeros(N,dtype=np.int64); v[(j-1)*m*m:j*m*m]=np.array([f[x] for x in xv])
        return v
    units=[t for t in range(1,m) if g_(t,m)==1]
    chars=[(aa,bb,cc) for aa in range(m) for bb in range(m) for cc in range(m) if (aa,bb,cc)!=(0,0,0)]
    orbits=[]; seen=set()
    for ch in chars:
        if ch in seen: continue
        O=sorted(set(((t*ch[0])%m,(t*ch[1])%m,(t*ch[2])%m) for t in units))
        aa,bb,cc=O[0]; sup=None
        if cc==0 and aa%m and bb%m: sup=(1,aa,bb)
        elif cc==(aa+bb)%m and aa%m and bb%m: sup=(2,aa,bb)
        elif aa==bb and aa%m and (cc-aa)%m: sup=(3,aa,(cc-aa)%m)
        seen|=set(O)
        if sup: orbits.append(sup)
    ylin=np.array([x-(m-1)//2 for x in range(m)],dtype=np.int64)
    def reader_const(j,a,b):
        return (G@pb(j,a,b,np.eye(m,dtype=np.int64)[0]))%m
    def reader_sigma(j,a,b):
        Nj=np.zeros(N,dtype=np.int64); Nj[(j-1)*m*m:j*m*m]=1
        gam=((m-1)//2)*(a+b-1)
        a0=(pb(j,a,b,ylin)-a*pb(j,1,0,ylin)-b*pb(j,0,1,ylin)-gam*Nj)//m
        return (G@a0)%m
    fams={1:[],2:[],3:[]}
    for (j,a,b) in orbits: fams[j].append((a,b))
    readers=[]
    for j in [1,2,3]:
        a,b=fams[j][0]; readers.append(reader_const(j,a,b))
    for j in [1,2,3]:
        a1,b1=fams[j][0]; sec=None
        for (a2,b2) in fams[j][1:]:
            if (a1*b2-a2*b1)%m: sec=(a2,b2); break
        a2,b2=sec
        readers.append(reader_sigma(j,a1,b1)); readers.append(reader_sigma(j,a2,b2))
    R=np.array(readers,dtype=np.int64)
    cols=[]
    for j in [1,2,3]:
        base=(j-1)*m*m
        cu=np.zeros(N,dtype=np.int64); cu[base]=1
        cv=np.zeros(N,dtype=np.int64); cv[base+m]=1; cv[base]-=1
        cw=np.zeros(N,dtype=np.int64); cw[base+1]=1; cw[base]-=1
        cols+=[cu,cv,cw]
    M=(R@np.array(cols,dtype=np.int64).T)%m
    A=M.copy()%m; det=1
    for c in range(9):
        piv=None
        for r in range(c,9):
            if A[r,c]%m: piv=r; break
        if piv is None: det=0; break
        if piv!=c: A[[c,piv]]=A[[piv,c]]; det=(-det)%m
        det=(det*int(A[c,c]))%m
        inv=pow(int(A[c,c]),-1,m)
        for r in range(c+1,9):
            A[r]=(A[r]-A[r,c]*inv*A[c])%m
    print(f"[m={m}] AUTOGRAPH det = {det} (6 mod {m} = {6%m}) -> {'SEALED' if det==6%m else 'CHECK'}")
