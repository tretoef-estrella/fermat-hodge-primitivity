# GOLLUM_PROBE_5_v2.py - 5 June 2026 - THE TOWER instrument, FULL EXECUTABLE (supersedes _v1 stub,
# a self-caught cera violation - second of its kind tonight, both caught before Auditor contact).
# Direct alpha and rho2 via the discriminant form in Smith coordinates (U-frame form, m-adic-clean
# coordinate extraction). Results of record: m=5 alpha=8, DIRECT rho2=8, Lemma E -> 1 = FIRM;
# m=7 alpha=35 double-routed, direct rho2 reads 35 vs forced 30: OPEN INSTRUMENT BUG (multi-top
# normalization suspected; resolution gate: reproduce the full m=7 profile {1:38,2:5} via H-perp/H).
import numpy as np, time
from sympy import Matrix, Rational
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
def f_null(A,p):
    A=(A%p).astype(np.int64).copy(); n,c=A.shape; piv=[]; r=0
    for j in range(c):
        nz=np.nonzero(A[r:,j]%p)[0]
        if len(nz)==0: continue
        i=nz[0]+r
        if i!=r: A[[r,i],:]=A[[i,r],:]
        inv=pow(int(A[r,j]),-1,p)
        A[r,:]=(A[r,:]*inv)%p
        for ii in range(n):
            if ii!=r and A[ii,j]%p: A[ii,:]=(A[ii,:]-A[ii,j]*A[r,:])%p
        piv.append(j); r+=1
    free=[j for j in range(c) if j not in piv]
    out=[]
    for f in free:
        v=np.zeros(c,dtype=np.int64); v[f]=1
        for ri,j in enumerate(piv): v[j]=(-A[ri,f])%p
        out.append(v%p)
    return out
def madic_mod(q,m,power):
    a=int(q.p); c=int(q.q)
    while c%m==0 and a%m==0: a//=m; c//=m
    assert c%m!=0
    return (a*pow(c,-1,m**power))%(m**power)
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
        Gs=B.T@G@B
        D,U=smith_u(Gs.tolist())
        Um=Matrix(U); F=(Um.inv().T*Matrix(Gs.tolist()).inv()*Um.inv())
        Brows=[i for i in range(m-1) if vp(D[i][i],m)==1]
        Trows=[i for i in range(m-1) if vp(D[i][i],m)==2]
        cofB=[abs(D[i][i])//m for i in Brows]
        cofT=[abs(D[i][i])//(m*m) for i in Trows]
        M2=np.zeros((len(Trows),len(Trows)),dtype=np.int64)
        for ii,i in enumerate(Trows):
            for jj2,j2 in enumerate(Trows):
                M2[ii,jj2]=madic_mod(Rational(F[i,j2])*m*m,m,1)
        pieces.append((B,np.array(U,dtype=np.int64),Brows,Trows,cofB,cofT,M2))
    a_e=np.zeros(N,dtype=np.int64); a_e[:m*m]=(k==m-1).astype(np.int64)
    FB=[]; FT=[]
    for ell in range(N):
        gcol=G[:,ell]; bco=[]; tco=[]
        for (B,U,Brows,Trows,cofB,cofT,M2) in pieces:
            pp=U@(B.T@gcol)
            for i,cf in zip(Brows,cofB):
                bco.append((int(pp[i])*pow(cf%m,-1,m))%m if cf%m else int(pp[i])%m)
            for i,cf in zip(Trows,cofT):
                xi=(int(pp[i])*pow(cf%(m*m),-1,m*m))%(m*m)
                tco.append((xi//m)%m)
        bco.append(int(gcol@a_e)%m)
        FB.append(bco); FT.append(tco)
    RB=np.array(FB,dtype=np.int64); RT=np.array(FT,dtype=np.int64)
    nulls=f_null(RB.T,m)
    Htop=np.array([(c@RT)%m for c in nulls],dtype=np.int64)
    M2blocks=[pc[6] for pc in pieces]
    T=sum(M.shape[0] for M in M2blocks)
    M2full=np.zeros((T,T),dtype=np.int64); off=0
    for M in M2blocks:
        s=M.shape[0]; M2full[off:off+s,off:off+s]=M; off+=s
    P=(Htop@M2full@Htop.T)%m
    rho2=rkp(P,m); alpha=rkp(Htop,m); tt=3*(m-2)*(m-4)
    print(f"[m={m}] alpha={alpha}; direct rho2={rho2}; LemmaE={tt-2*alpha+rho2} (FIRM {1 if m==5 else 5})")
