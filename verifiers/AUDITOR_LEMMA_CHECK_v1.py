# LEMMA_PROBE_v1.py - 4 June 2026 (night) - THE WATERMARK THEOREM commission
# LEMMA A(b): for every orbit piece of (2,5) and (2,7): O_K-structure (Phi_m minimal poly),
#   free generator v, integral hermitian content h(v,v) = sum_j B(v, X^j v) zeta^{-j}.
#   DECLARED: N(h(v,v)) = m^{2m-4} exactly, all pieces (<=> delta = h/m ~ lambda^{m-3}).
# LEMMA B(a): hypothesis-free MEASUREMENT of the glue group V/(+)pieces: p-adic SNF profile
#   of the stacked basis matrix at p=m. Sealed totals only: v5=17, v7=44.
import numpy as np, random, time
from sympy import Matrix, eye, det, Integer, Poly, symbols, resultant, cyclotomic_poly
from math import gcd
from sympy import totient, mobius

x=symbols('x')

def gram(m):
    k=np.arange(m*m)//m; l=np.arange(m*m)%m
    kml=(k-l)%m; kpl=(k+l)%m; kpl1=(k+l+1)%m
    n=3*m*m; A=np.zeros((n,n),dtype=np.int64)
    eq=lambda u,v:(u[:,None]==v[None,:]).astype(np.int64)
    same=(eq(k,k)|eq(l,l)).astype(np.int64); np.fill_diagonal(same,0)
    B12=eq(kml,kml); B13=eq(kpl1,kml); B23=eq(kpl,kpl)
    s=m*m
    A[0:s,0:s]=same; A[s:2*s,s:2*s]=same; A[2*s:,2*s:]=same
    A[0:s,s:2*s]=B12; A[s:2*s,0:s]=B12.T
    A[0:s,2*s:]=B13; A[2*s:,0:s]=B13.T
    A[s:2*s,2*s:]=B23; A[2*s:,s:2*s]=B23.T
    np.fill_diagonal(A,2-m)
    return A

def rank_mod(M,q=1000003):
    A=(M%q).astype(np.int64); n,c=A.shape; r=0
    for j in range(c):
        nz=np.nonzero(A[r:,j]%q)[0]
        if len(nz)==0: continue
        i=nz[0]+r
        if i!=r: A[[r,i],:]=A[[i,r],:]
        inv=pow(int(A[r,j]),-1,q)
        f=(A[r+1:,j]*inv)%q
        A[r+1:,j:]=(A[r+1:,j:]-f[:,None]*A[r,j:][None,:])%q
        r+=1
        if r==n: break
    return r

def ramanujan(m,a):
    d=gcd(a,m); k=m//d
    return int(mobius(k))*int(totient(m))//int(totient(k))

def sat_kernel(Mx):
    ns=Mx.nullspace()
    if not ns: return Matrix.zeros(Mx.cols,0)
    from sympy import lcm
    cols=[]
    for v in ns:
        den=1
        for xq in v: den=lcm(den,xq.q)
        cols.append([int(xq*den) for xq in v])
    B=[list(r) for r in zip(*cols)]
    n=len(B); r=len(B[0])
    Q=[[1 if i==j else 0 for j in range(n)] for i in range(n)]
    top=0
    for c in range(r):
        while True:
            piv=None; best=None
            for i in range(top,n):
                if B[i][c]!=0 and (best is None or abs(B[i][c])<best):
                    best=abs(B[i][c]); piv=i
            if piv is None: break
            if piv!=top:
                B[top],B[piv]=B[piv],B[top]; Q[top],Q[piv]=Q[piv],Q[top]
            done=True
            for i in range(top+1,n):
                if B[i][c]!=0:
                    qq=B[i][c]//B[top][c]
                    for j in range(r): B[i][j]-=qq*B[top][j]
                    for j in range(n): Q[i][j]-=qq*Q[top][j]
                    if B[i][c]!=0: done=False
            if done: break
        top+=1
    Qm=Matrix(Q); sat=Qm.inv()[:,:r]
    assert (Mx*sat)==Matrix.zeros(Mx.rows,r)
    return sat

def padic_profile(Anp,p,K=10):
    modr=p**K
    M=(Anp%modr).astype(np.int64); n=M.shape[0]; r=0; shift=0; counts={}
    while r<n:
        sub=M[r:,r:]
        if not (sub%modr).any(): break
        units=(sub%p)!=0
        if not units.any():
            if modr==p: return counts,True
            modr//=p; shift+=1
            M[r:,r:]=(sub//p)%modr
            continue
        i,j=np.unravel_index(np.argmax(units),units.shape)
        i+=r; j+=r
        if i!=r: M[[r,i],:]=M[[i,r],:]
        if j!=r: M[:,[r,j]]=M[:,[j,r]]
        inv=pow(int(M[r,r])%modr,-1,modr)
        colf=(M[r+1:,r]*inv)%modr
        M[r+1:,r:]=(M[r+1:,r:]-colf[:,None]*M[r,r:][None,:])%modr
        rowf=(M[r,r+1:]*inv)%modr
        M[r:,r+1:]=(M[r:,r+1:]-M[r:,r][:,None]*rowf[None,:])%modr
        counts[shift]=counts.get(shift,0)+1
        r+=1
    return counts,False

def vp(xv,p):
    xv=abs(int(xv)); v=0
    while xv and xv%p==0: xv//=p; v+=1
    return v

def analyze(m, disc_target_abs):
    t0=time.time(); G=gram(m); N=3*m*m
    rk=rank_mod(G)
    best=None
    for trial in range(200):
        order=list(range(N)); random.seed(7000+trial); random.shuffle(order)
        chosen=[]
        for i in order:
            if rank_mod(G[:,chosen+[i]])==len(chosen)+1: chosen.append(i)
            if len(chosen)==rk: break
        GramB=Matrix(G[np.ix_(chosen,chosen)].tolist())
        d=det(GramB)
        if abs(d)==disc_target_abs: best=(chosen,GramB,d); break
    chosen,GramB,discV=best
    GramBinv=GramB.inv()
    GB=Matrix(G[:,chosen].tolist())
    def line_coords(i):
        c=GramBinv*GB[i,:].T
        return [int(xq) for xq in c]
    def permidx(shifts):
        sig=np.zeros(N,dtype=np.int64)
        for j in range(3):
            sk,sl=shifts[j]
            for k in range(m):
                for l in range(m):
                    sig[j*m*m+k*m+l]=j*m*m+((k+sk)%m)*m+((l+sl)%m)
        return sig
    gens={'U':permidx([(1,0),(1,0),(1,0)]),'W':permidx([(0,1),(0,1),(1,0)]),'Z':permidx([(0,0),(1,1),(1,1)])}
    ops={}
    for name,sig in gens.items():
        cols=[line_coords(int(sig[i])) for i in chosen]
        A=Matrix(cols).T
        assert A.T*GramB*A==GramB
        ops[name]=np.array(A.tolist(),dtype=np.int64)
    def topow(A):
        out=[np.eye(rk,dtype=np.int64)]
        for _ in range(m-1): out.append(out[-1]@A)
        return out
    PU,PW,PZ=topow(ops['U']),topow(ops['W']),topow(ops['Z'])
    elems={}
    for s in range(m):
        for t in range(m):
            ST=PU[s]@PW[t]
            for r in range(m):
                elems[(s,t,r)]=ST@PZ[r]
    units=[t for t in range(1,m) if gcd(t,m)==1]; phi=len(units)
    chars=[(a,b,c) for a in range(m) for b in range(m) for c in range(m) if (a,b,c)!=(0,0,0)]
    orbits=[]; seen=set()
    for ch in chars:
        if ch in seen: continue
        O=sorted(set(((t*ch[0])%m,(t*ch[1])%m,(t*ch[2])%m) for t in units))
        orbits.append(O); seen|=set(O)
    def M_orbit_np(O):
        a,b,c0=O[0]; size=len(O)
        Mo=np.zeros((rk,rk),dtype=np.int64)
        for (s,t,r),g in elems.items():
            cc=ramanujan(m,(a*s+b*t+c0*r)%m)*size//phi
            if cc: Mo+=cc*g
        return Mo
    Mtriv=np.zeros((rk,rk),dtype=np.int64)
    for g in elems.values(): Mtriv+=g
    I=np.eye(rk,dtype=np.int64)
    Ctriv=sat_kernel(m**3*eye(rk)-Matrix(Mtriv.tolist()))
    allB=Ctriv
    Phim=Poly(cyclotomic_poly(m,x),x)
    print(f"== m={m}: LEMMA A — hermitian contents per piece (declared N = m^(2m-4) = {m**(2*m-4)}) ==",flush=True)
    okA=True; npieces=0
    for O in orbits:
        Mo=M_orbit_np(O)
        if rank_mod(m**3*I-Mo)==rk: continue
        C=sat_kernel(m**3*eye(rk)-Matrix(Mo.tolist()))
        if C.cols==0: continue
        npieces+=1
        allB=Matrix.hstack(allB,C)
        a,b,c0=O[0]
        g0=None
        for s in range(m):
            for t in range(m):
                for r in range(m):
                    if (a*s+b*t+c0*r)%m==1: g0=(s,t,r); break
                if g0: break
            if g0: break
        E=Matrix(elems[g0].tolist())
        Xop=(C.T*C).inv()*C.T*(E*C)
        assert all(xq.is_integer for xq in Xop), "X not integer"
        Xop=Matrix([[int(xq) for xq in Xop.row(i)] for i in range(Xop.rows)])
        # minimal polynomial = Phi_m
        Pm=Matrix.zeros(Xop.rows)
        coeffs=Phim.all_coeffs()
        Acc=eye(Xop.rows)
        for cf in reversed(coeffs):
            Pm+=int(cf)*Acc; Acc=Acc*Xop
        assert Pm==Matrix.zeros(Xop.rows), "min poly not Phi_m"
        P=C.T*GramB*C
        # AUDITOR ideal-form check: any v with O_K v of finite index k; identity N(h)=k^2*m^(2m-4)
        gen=None; kidx=None
        dim=Xop.rows
        for j in range(dim):
            v=Matrix([1 if i==j else 0 for i in range(dim)])
            cols=[v]
            for _ in range(dim-1): cols.append(Xop*cols[-1])
            Mgen=Matrix.hstack(*cols)
            dd=det(Mgen)
            if dd!=0: gen=v; kidx=abs(int(dd)); break
        assert gen is not None, "no finite-index vector found"
        # hermitian content
        cj=[]
        Xj=eye(dim)
        for j in range(m):
            cj.append(int((gen.T*P*(Xj*gen))[0,0])); Xj=Xj*Xop
        H=sum(cj[j]*x**((m-j)%m) for j in range(m))
        Nh=resultant(Phim.as_expr(),H,x)
        ok = abs(int(Nh))==kidx*kidx*m**(2*m-4)
        okA = okA and ok
        print(f"  O{O[0]}: index k={kidx}  N(h) = k^2*m^(2m-4)? {ok}",flush=True)
    print(f"LEMMA A m={m}: {npieces} pieces, ideal-form identity all: {'PASS' if okA else 'FAIL'}")
    print(f"== m={m}: LEMMA B — glue group SNF profile (hypothesis-free) ==")
    Ball=np.array([[int(allB[i,j]) for j in range(allB.cols)] for i in range(allB.rows)],dtype=np.int64)
    prof,flag=padic_profile(Ball,m,K=10)
    nz={h:c for h,c in sorted(prof.items()) if h>0}
    tot=sum(h*c for h,c in prof.items())
    print(f"  glue p-adic divisor profile (p^h: count): {nz}; total v_{m} = {tot}; flag={flag}")
    print(f"[m={m}] done {time.time()-t0:.0f}s")

analyze(5, 5**12)
analyze(7, 7**48)
