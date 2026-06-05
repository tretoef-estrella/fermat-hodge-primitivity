# GOLLUM_PROBE_8_v1.py - 5 June 2026 - THE BUG NAMED AND THE FREE NUGGET (cera, full executable)
# THE MIXED-FRAME PACHI: probe 5 normalized COORDINATES to the m-primary generators (val * c^-1)
# but left the FORM in the old frame (no c_i*c_j factor). The scaling acts INSIDE Xi^T M Xi,
# moving the subspace: "unit rescalings preserve rank" was FALSE reasoning - logged. With one top
# per piece (m=5) it did not bite; with 3x3 top blocks (m>=7) it inflated rho2 to full rank.
# Side-by-side demonstration + THE NUGGET: corrected DIRECT rho2 = 8 / 30 / 78 at m = 5 / 7 / 11
# (all declared before running), Lemma E closing 1 / 5 / 17 = the FIRM profiles incl. the SEALED m=11.
# (E2) upgraded: rho2 = 12m-54 (m>=7) now DIRECTLY MEASURED x2 with a gate-validated instrument.
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
def f_null(Aa,p):
    Aa=(Aa%p).astype(np.int64).copy(); n2,c2=Aa.shape; piv=[]; r2=0
    for j in range(c2):
        nz=np.nonzero(Aa[r2:,j]%p)[0]
        if len(nz)==0: continue
        i=nz[0]+r2
        if i!=r2: Aa[[r2,i],:]=Aa[[i,r2],:]
        inv=pow(int(Aa[r2,j]),-1,p)
        Aa[r2,:]=(Aa[r2,:]*inv)%p
        for ii in range(n2):
            if ii!=r2 and Aa[ii,j]%p: Aa[ii,:]=(Aa[ii,:]-Aa[ii,j]*Aa[r2,:])%p
        piv.append(j); r2+=1
    free=[j for j in range(c2) if j not in piv]
    out=[]
    for f in free:
        v=np.zeros(c2,dtype=np.int64); v[f]=1
        for ri,j in enumerate(piv): v[j]=(-Aa[ri,f])%p
        out.append(v%p)
    return out
def madic(q,m,power):
    a=int(q.p); c=int(q.q)
    while c%m==0 and a%m==0: a//=m; c//=m
    return (a*pow(c,-1,m**power))%(m**power)
t0=time.time()
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
        Gs=B.T@G@B
        D,U=smith_u(Gs.tolist())
        Um=Matrix(U); F=(Um.inv().T*Matrix(Gs.tolist()).inv()*Um.inv())
        Brows=[i for i in range(m-1) if vp(D[i][i],m)==1]
        Trows=[i for i in range(m-1) if vp(D[i][i],m)==2]
        cofB=[abs(D[i][i])//m for i in Brows]
        cofT=[abs(D[i][i])//(m*m) for i in Trows]
        nt=len(Trows)
        M2old=np.zeros((nt,nt),dtype=np.int64); M2new=np.zeros((nt,nt),dtype=np.int64)
        for ii,i in enumerate(Trows):
            for jj2,j2 in enumerate(Trows):
                M2old[ii,jj2]=madic(Rational(F[i,j2])*m*m,m,1)
                M2new[ii,jj2]=madic(Rational(F[i,j2])*cofT[ii]*cofT[jj2]*m*m,m,1)
        pieces.append((B,np.array(U,dtype=np.int64),Brows,Trows,cofB,cofT,M2old,M2new))
    a_e=np.zeros(N,dtype=np.int64); a_e[:m*m]=(k==m-1).astype(np.int64)
    FB=[]; FT=[]
    for ell in range(N):
        gcol=G[:,ell]; bco=[]; tco=[]
        for (B,U,Brows,Trows,cofB,cofT,M2o,M2n) in pieces:
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
    def assemble(idx):
        Ms=[pc[idx] for pc in pieces]
        T=sum(M.shape[0] for M in Ms)
        Mf=np.zeros((T,T),dtype=np.int64); off=0
        for M in Ms:
            s=M.shape[0]; Mf[off:off+s,off:off+s]=M; off+=s
        return Mf
    Pold=(Htop@assemble(6)@Htop.T)%m
    Pnew=(Htop@assemble(7)@Htop.T)%m
    alpha=rkp(Htop,m); tt=3*(m-2)*(m-4)
    r_old=rkp(Pold,m); r_new=rkp(Pnew,m)
    firm={5:1,7:5,11:17}[m]
    print(f"[m={m}] alpha={alpha}; rho2 mixed-frame(BUG)={r_old}; rho2 CORRECTED={r_new}; LemmaE={tt-2*alpha+r_new} (FIRM {firm}) [{time.time()-t0:.0f}s]")
