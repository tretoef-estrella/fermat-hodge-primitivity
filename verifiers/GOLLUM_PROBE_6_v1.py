# GOLLUM_PROBE_6_v1.py - 5 June 2026 - THE NINE PACHIS: the affine shadow law (cera, full executable)
# DECLARED before running: B(line at (k,l)) = u_j + k*v_j + l*w_j entrywise mod m; per-family rank 3;
# rank of the nine {u_j,v_j,w_j} = 9. RESULT: PASS on every count, every line, both primes (m=5,7).
# This closes (E1)'s architecture: the glue's B-shadow = the affine span, dim exactly 9 = "las nueve
# sombras afines" (proof: cross-family constants + sigma-row y_lin values are affine in position;
# the m*delta parts are deep; affine maps in 2 variables x 3 families cap at 9; the nine reach 9).
import numpy as np, time
from sympy import Matrix
exec(open('GRANSLAP_PROBE_v1.py').read().split("for m in [5,7]:")[0])
from math import gcd as g_
def smith_u(Ain):
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
for m in [5,7]:
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
        D,U=smith_u((B.T@G@B).tolist())
        Brows=[i for i in range(m-1) if vp(D[i][i],m)==1]
        cofB=[abs(D[i][i])//m for i in Brows]
        pieces.append((B,np.array(U,dtype=np.int64),Brows,cofB))
    a_e=np.zeros(N,dtype=np.int64); a_e[:m*m]=(k==m-1).astype(np.int64)
    def Bco(ell):
        gcol=G[:,ell]; bco=[]
        for (B,U,Brows,cofB) in pieces:
            pp=U@(B.T@gcol)
            for i,cf in zip(Brows,cofB):
                bco.append((int(pp[i])*pow(cf%m,-1,m))%m if cf%m else int(pp[i])%m)
        bco.append(int(gcol@a_e)%m)
        return np.array(bco,dtype=np.int64)
    nine=[]; okall=True
    for j in [1,2,3]:
        base=(j-1)*m*m
        u=Bco(base); v=(Bco(base+m)-u)%m; w=(Bco(base+1)-u)%m
        ok=all((Bco(base+kk*m+ll)%m==(u+kk*v+ll*w)%m).all() for kk in range(m) for ll in range(m))
        okall&=ok; nine+=[u,v,w]
        print(f"[m={m}] family {j}: affine law: {ok}")
    print(f"[m={m}] rank of the nine = {rkp(np.array(nine),m)} (pred 9); all-affine: {okall}")
