# GRANSLAP_PROBE_v1.py - 4 June 2026 (night) - THE GRAND GAME OF THE PELADOS
# CERA: this file reproduces ALL measurements of skeleton v4 SS17-18 (previously transcript-only)
# and executes the Auditor's G-B-2 attack order (b)+(a):
#   LEFT HAND (K and friends): (b) elementary-divisor profile of G, hypothesis-free;
#       disc_std(K) at m=5 (independent); block-saturation ledger.
#   RIGHT HAND (m and friends): reproduce det[K0|F|N1] = m^((9m^2-3m-6)/2), per-family 5^16.
#   BOTH HANDS: [K:K0] = m^(9m-6) split as 9 blocks x m^(m-2) + CONSTANT residual m^12 [DECLARED].
import numpy as np, random, time
from sympy import Matrix, det, eye
from math import gcd as g_
from sympy import totient, mobius

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

def ramanujan(m,a):
    d=g_(a,m); kk=m//d
    return int(mobius(kk))*int(totient(m))//int(totient(kk))

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

def padic_profile(Anp,p,K=12):
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

def sat_kernel(Mx):
    ns=Mx.nullspace()
    if not ns: return Matrix.zeros(Mx.cols,0)
    from sympy import lcm
    cols=[]
    for v in ns:
        den=1
        for q in v: den=lcm(den,q.q)
        cols.append([int(q*den) for q in v])
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

def vp(x,p):
    x=abs(int(x)); v=0
    while x and x%p==0: x//=p; v+=1
    return v

def build_K0_F(m):
    G=gram(m); N=3*m*m
    k=np.arange(m*m)//m; l=np.arange(m*m)%m
    def tr(j,a,b,r):
        coef=np.array([ramanujan(m,int(a*kk+b*ll-r)%m) for kk,ll in zip(k,l)],dtype=np.int64)
        v=np.zeros(N,dtype=np.int64); v[(j-1)*m*m:j*m*m]=coef
        return v
    K0blocks=[]
    for j in [1,2,3]:
        for (aa,bb) in [(1,0),(0,1)]:
            K0blocks.append(("axis",np.array([tr(j,aa,bb,r) for r in range(m-1)]).T))
    for name,(j1,a1,b1),(j2,a2,b2),s0 in [("ov12",(1,1,m-1),(2,1,m-1),0),("ov23",(2,1,1),(3,1,1),0),("ov13",(1,1,1),(3,1,m-1),1)]:
        K0blocks.append((name,np.array([tr(j1,a1,b1,r)+tr(j2,a2,b2,(r+s0)%m) for r in range(m-1)]).T))
    Nv=[]
    for j in [1,2,3]:
        v=np.zeros(N,dtype=np.int64); v[(j-1)*m*m:j*m*m]=1; Nv.append(v)
    K0blocks.append(("triv",np.array([Nv[0]-Nv[1],Nv[1]-Nv[2]]).T))
    K0=np.hstack([b for _,b in K0blocks])
    units=[t for t in range(1,m) if g_(t,m)==1]
    chars=[(a,b,c) for a in range(m) for b in range(m) for c in range(m) if (a,b,c)!=(0,0,0)]
    orbits=[]; seen=set()
    for ch in chars:
        if ch in seen: continue
        O=sorted(set(((t*ch[0])%m,(t*ch[1])%m,(t*ch[2])%m) for t in units))
        orbits.append(O); seen|=set(O)
    F=[]
    for O in orbits:
        a,b,c0=O[0]
        sup=None
        if c0==0 and a%m and b%m: sup=(1,a,b)
        elif c0==(a+b)%m and a%m and b%m: sup=(2,a,b)
        elif a==b and a%m and (c0-a)%m: sup=(3,a,(c0-a)%m)
        if not sup: continue
        j,ap,bp=sup
        for r in range(m-1): F.append(tr(j,ap,bp,r))
    F.append(Nv[0])
    return G,N,K0,K0blocks,np.array(F).T,tr

for m in [5,7]:
    t0=time.time(); target=(9*m*m-21*m+4)//2
    G,N,K0,K0blocks,F,tr=build_K0_F(m)
    assert not (G@K0).any() and rank_mod(K0)==9*m-7
    # RIGHT HAND: reproduce SS17 measurements (cera shipment)
    Stack=np.hstack([K0,F])
    dS=det(Matrix(Stack.tolist()))
    bigdet_v=vp(dS,m); other=abs(int(dS))//(m**bigdet_v)
    print(f"[m={m}] RIGHT: |det[K0|F|N1]| v_{m}={bigdet_v} (pred (9m^2-3m-6)/2={(9*m*m-3*m-6)//2}); non-{m} part={other}")
    print(f"[m={m}]        => [K:K0] = m^{bigdet_v-target-1} (pred 9m-6={9*m-6})")
    # LEFT HAND (b): elementary divisor profile of G itself, hypothesis-free, at p=m,2,3
    for p in [m,2,3]:
        prof,flag=padic_profile(G.copy(),p,K=12)
        nz={h:c for h,c in sorted(prof.items()) if h>0}
        tot=sum(h*c for h,c in prof.items())
        print(f"[m={m}] LEFT(b): SNF profile of G at p={p}: nonzero-height {nz}, rank {sum(prof.values())}, total v={tot}, flag={flag}")
    # LEFT HAND (a): block saturation ledger via disc ratios
    # axis block saturation in A: pullback(Z0): disc = m^m; trace block disc = m^(3m-4) -> index m^((2m-4)/2)=m^(m-2)
    blocksat=0
    for name,B in K0blocks:
        if name=="triv": continue
        Gr=Matrix((B.T@B).tolist()); dB=det(Gr)
        if name=="axis":
            idx2=vp(dB,m)-m   # disc(sat)=m^m
        else:
            idx2=vp(dB,m)-m   # overlap saturation: paired pullback, disc m^m * 2-part
        blocksat+=idx2//2
        print(f"[m={m}] LEFT(a): block {name}: disc v_{m}={vp(dB,m)}, 2-part v2={vp(dB,2)} -> per-block sat index v_{m}={idx2//2}")
    print(f"[m={m}] LEFT(a): blockwise saturation total = m^{blocksat} (pred 9(m-2)={9*(m-2)}) => residual = m^{(bigdet_v-target-1)-blocksat} (DECLARED constant 12)")
    if m==5:
        Kfull=sat_kernel(Matrix(G.tolist()))
        Kb=np.array([[int(Kfull[i,j]) for j in range(Kfull.cols)] for i in range(N)],dtype=np.int64)
        dK=det(Matrix((Kb.T@Kb).tolist())); dK0=det(Matrix((K0.T@K0).tolist()))
        import sympy
        ratio=sympy.Rational(int(dK0),int(dK))
        idx=sympy.sqrt(ratio)
        print(f"[m=5] INDEPENDENT: disc(K0)/disc(K) -> [K:K0] = {idx} (pred 5^39 = {5**39})")
    print(f"[m={m}] done {time.time()-t0:.0f}s")
