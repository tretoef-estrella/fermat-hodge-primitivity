# GOLLUM_PROBE_4_v2.py - 5 June 2026 - THE ELEVATOR instrument (full executable; supersedes _v1 whose
# body was a placeholder - self-caught cera violation, documented here).
# Lemma E [PROVEN]: #m^2(V*/V) = t - 2*alpha + rho2. This file measures, at m = 5, 7, 11:
#   rank(full glue coordinates) = g (integrity), elementarity of every line class,
#   rank_B (the glue's B-projection) -> alpha = g - rank_B, and rho2 back-solved via Lemma E.
# Results of record: rank(full) = 17/44/134 = g; rank_B = 9 CONSTANT; alpha = 8/35/125;
#   rho2 = 8/30/78 (= 12m-54 for m>=7; = alpha at m=5: rank saturation).
import numpy as np, time
from sympy import Matrix, det
exec(open('GRANSLAP_PROBE_v1.py').read().split("for m in [5,7]:")[0])
from math import gcd as g_
def smith_transforms(Ain):
    A=[[int(x) for x in row] for row in Ain]; n=len(A)
    U=[[1 if i==j else 0 for j in range(n)] for i in range(n)]
    for t in range(n):
        while True:
            piv=None; best=None
            for i in range(t,n):
                for j in range(t,n):
                    if A[i][j]!=0 and (best is None or abs(A[i][j])<best): best=abs(A[i][j]); piv=(i,j)
            if piv is None: break
            pi,pj=piv
            if pi!=t: A[t],A[pi]=A[pi],A[t]; U[t],U[pi]=U[pi],U[t]
            if pj!=t:
                for r in range(n): A[r][t],A[r][pj]=A[r][pj],A[r][t]
            done=True
            for i in range(t+1,n):
                if A[i][t]:
                    q=A[i][t]//A[t][t]
                    for j2 in range(n): A[i][j2]-=q*A[t][j2]
                    for j2 in range(n): U[i][j2]-=q*U[t][j2]
                    if A[i][t]: done=False
            for j2 in range(t+1,n):
                if A[t][j2]:
                    q=A[t][j2]//A[t][t]
                    for r in range(n): A[r][j2]-=q*A[r][t]
                    if A[t][j2]: done=False
            if done: break
    return A,U
def rkp(A,p):
    A=(A%p).astype(np.int64).copy(); n,c=A.shape; r=0
    for jj in range(c):
        nz=np.nonzero(A[r:,jj]%p)[0]
        if len(nz)==0: continue
        i=nz[0]+r
        if i!=r: A[[r,i],:]=A[[i,r],:]
        inv=pow(int(A[r,jj]),-1,p)
        f=(A[r+1:,jj]*inv)%p
        A[r+1:,jj:]=(A[r+1:,jj:]-f[:,None]*A[r,jj:][None,:])%p
        r+=1
        if r==n: break
    return r
for m in [5,7,11]:
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
    pieces=[]
    for (j,a,b) in orbits:
        Nj=np.zeros(N,dtype=np.int64); Nj[(j-1)*m*m:j*m*m]=1
        ylin=np.array([x-(m-1)//2 for x in range(m)],dtype=np.int64)
        gam=((m-1)//2)*(a+b-1)
        a0=(pb(j,a,b,ylin)-a*pb(j,1,0,ylin)-b*pb(j,0,1,ylin)-gam*Nj)//m
        lifts=[pb(j,a,b,np.eye(m,dtype=np.int64)[r]) for r in range(m-2)]+[a0]
        B=np.array(lifts).T
        D,U=smith_transforms((B.T@G@B).tolist())
        Brows=[i for i in range(m-1) if vp(D[i][i],m)==1]
        Trows=[i for i in range(m-1) if vp(D[i][i],m)==2]
        pieces.append((B,np.array(U,dtype=np.int64),Brows,Trows))
    a_e=np.zeros(N,dtype=np.int64); a_e[:m*m]=(k==m-1).astype(np.int64)
    elem=True; FB=[]; FA=[]
    for ell in range(N):
        gcol=G[:,ell]; bco=[]; aco=[]
        for (B,U,Brows,Trows) in pieces:
            pp=U@(B.T@gcol)
            for i in Brows: bco.append(int(pp[i])%m)
            for i in Trows:
                val=int(pp[i])%(m*m)
                if val%m: elem=False
                aco.append((val//m)%m)
        bco.append(int(gcol@a_e)%m)
        FB.append(bco); FA.append(aco)
    RB=np.array(FB,dtype=np.int64); full=np.hstack([RB,np.array(FA,dtype=np.int64)])
    g_glue=(3*m*m-9*m+4)//2
    rB=rkp(RB,m); rf=rkp(full,m); tt=3*(m-2)*(m-4); alpha=g_glue-rB
    rho2=(1 if m==5 else 3*m-16)-tt+2*alpha
    print(f"[m={m}] elementary {elem}; rank(full)={rf} (g={g_glue}); rank_B={rB}; alpha={alpha}; rho2={rho2}")
