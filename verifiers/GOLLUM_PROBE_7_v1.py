# GOLLUM_PROBE_7_v1.py - 5 June 2026 - THE STOPWATCH GATE (cera, full executable)
# End-to-end #m^2 computation via H-perp/H: full discriminant form Phi in g-hat normalization
# (cofactor products c_i*c_j included), kernel mod m^2 by PURE elimination (no integer Smith -
# the integer-Smith route overflowed; that catch is in the acta). GATE RESULT OF RECORD:
# #m^2 = 1 (m=5) and 5 (m=7), matching FIRM profiles: the abstract Lemma-E chain is validated
# end to end and the probe-5 defect is localized to the B2 sub-instrument (see PROBE_8: mixed frame).
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
def kernel_m2(Cons,m):
    M2=m*m; Mdim=Cons.shape[1]
    gens=[np.eye(Mdim,dtype=np.int64)[i] for i in range(Mdim)]
    for crow in Cons:
        vals=[int(crow@g)%M2 for g in gens]
        if not any(vals): continue
        def valm(x): return 2 if x==0 else (1 if x%m==0 else 0)
        vmin=min(valm(v) for v in vals)
        if vmin==2: continue
        pi=[i for i,v in enumerate(vals) if valm(v)==vmin][0]
        unit=vals[pi]//(m**vmin); uin=pow(unit%M2,-1,M2)
        newg=[]
        for i,g in enumerate(gens):
            if i==pi: continue
            q=(vals[i]//(m**vmin))*uin%M2
            newg.append((g-q*gens[pi])%M2)
        if vmin>0: newg.append((m*gens[pi])%M2)
        gens=newg
    return np.array(gens,dtype=np.int64)
t0=time.time()
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
    blocks=[]; horders=[]; Phi_blocks=[]
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
        rows=[i for i in range(m-1) if vp(D[i][i],m)>=1]
        hs=[vp(D[i][i],m) for i in rows]
        cofs=[abs(D[i][i])//(m**h) for h,i in zip(hs,rows)]
        Phi=np.zeros((len(rows),len(rows)),dtype=np.int64)
        for ii,i in enumerate(rows):
            for jj2,j2 in enumerate(rows):
                Phi[ii,jj2]=madic(Rational(F[i,j2])*cofs[ii]*cofs[jj2]*m*m,m,2)
        blocks.append((B,np.array(U,dtype=np.int64),rows,hs,cofs))
        Phi_blocks.append(Phi); horders+=hs
    horders.append(1)
    Mdim=len(horders)
    Phi=np.zeros((Mdim,Mdim),dtype=np.int64); off=0
    for Pb in Phi_blocks:
        s=Pb.shape[0]; Phi[off:off+s,off:off+s]=Pb; off+=s
    Phi[off,off]=m%(m*m)
    a_e=np.zeros(N,dtype=np.int64); a_e[:m*m]=(k==m-1).astype(np.int64)
    Hg=[]
    for ell in range(N):
        gcol=G[:,ell]; co=[]
        for (B,U,rows,hs,cofs) in blocks:
            pp=U@(B.T@gcol)
            for i,h,cf in zip(rows,hs,cofs):
                co.append((int(pp[i])*pow(cf%(m**h),-1,m**h))%(m**h))
        co.append(int(gcol@a_e)%m)
        Hg.append(co)
    Hg=np.array(Hg,dtype=np.int64)
    Cons=(Hg@Phi.T)%(m*m)
    K2=kernel_m2(Cons,m)
    extra=[]
    for i,h in enumerate(horders):
        v=np.zeros(Mdim,dtype=np.int64); v[i]=m**h
        extra.append(v)
    Hperp=np.vstack([K2,np.array(extra,dtype=np.int64)])
    mH=(Hperp*m)%(m*m)
    Tpos=[i for i,h in enumerate(horders) if h==2]
    Bpos=[i for i,h in enumerate(horders) if h==1]
    def topF(v):
        return [((int(v[i])%(m*m))//m)%m if int(v[i])%m==0 else -77 for i in Tpos]
    mtop=np.array([topF(v) for v in mH],dtype=np.int64)
    assert (mtop>=0).all()
    HTm=np.array([[((int(Hg[r,i])%(m*m))//m)%m if int(Hg[r,i])%m==0 else -77 for i in Tpos] for r in range(N)],dtype=np.int64)
    nulls=f_null((Hg[:,Bpos]%m).T,m)
    Hdeep=np.array([(c@HTm)%m for c in nulls],dtype=np.int64)
    num=rkp(np.vstack([mtop,Hdeep]),m); den=rkp(Hdeep,m)
    print(f"[m={m}] GATE end-to-end: #m^2 = {num-den} (FIRM {1 if m==5 else 5}) [{time.time()-t0:.0f}s]")
