# LEMAR_SHAKE_PROBE_v1.py - 4 June 2026 (night) - insurance (m=7 residual) + the 12 generators (m=5)
# Companion to GRANSLAP_PROBE_v1.py (helpers loaded from it). Reproduces LEMMA_R_REPORT_v1 numbers.
import numpy as np, time
from sympy import Matrix, det
exec(open('GRANSLAP_PROBE_v1.py').read().split("for m in [5,7]:")[0])
import sympy
from sympy import lcm

def satblocks(m):
    G,N,K0,K0blocks,F,tr=build_K0_F(m)
    k=np.arange(m*m)//m; l=np.arange(m*m)%m
    def pullback(j,a,b,y):
        xv=(a*k+b*l)%m
        v=np.zeros(N,dtype=np.int64); v[(j-1)*m*m:j*m*m]=np.array([y[x] for x in xv])
        return v
    Z0=[np.eye(m,dtype=np.int64)[i]-np.eye(m,dtype=np.int64)[m-1] for i in range(m-1)]
    cols=[]; labels=[]
    for j in [1,2,3]:
        for (aa,bb) in [(1,0),(0,1)]:
            for i,y in enumerate(Z0):
                cols.append(pullback(j,aa,bb,y)); labels.append(f"ax{j}({aa}{bb}){i}")
    for nm,(j1,a1,b1),(j2,a2,b2),s0 in [("ov12",(1,1,m-1),(2,1,m-1),0),("ov23",(2,1,1),(3,1,1),0),("ov13",(1,1,1),(3,1,m-1),1)]:
        for i,y in enumerate(Z0):
            cols.append(pullback(j1,a1,b1,y)+pullback(j2,a2,b2,np.roll(y,s0))); labels.append(f"{nm}{i}")
    Nv=[]
    for j in [1,2,3]:
        v=np.zeros(N,dtype=np.int64); v[(j-1)*m*m:j*m*m]=1; Nv.append(v)
    cols+=[Nv[0]-Nv[1],Nv[1]-Nv[2]]; labels+=["N1-N2","N2-N3"]
    return G,N,np.array(cols).T,labels

def rank_modp(M,p):
    A=(M%p).astype(np.int64); n,c=A.shape; r=0
    for j in range(c):
        nz=np.nonzero(A[r:,j]%p)[0]
        if len(nz)==0: continue
        i=nz[0]+r
        if i!=r: A[[r,i],:]=A[[i,r],:]
        inv=pow(int(A[r,j]),-1,p)
        f=(A[r+1:,j]*inv)%p
        A[r+1:,j:]=(A[r+1:,j:]-f[:,None]*A[r,j:][None,:])%p
        r+=1
        if r==n: break
    return r

for m in [5,7]:
    G,N,SAT,labels=satblocks(m)
    assert not (G@SAT).any() and rank_mod(SAT)==9*m-7
    Kf=sat_kernel(Matrix(G.tolist()))
    Kb=np.array([[int(Kf[i,j]) for j in range(Kf.cols)] for i in range(N)],dtype=np.int64)
    dS=det(Matrix((SAT.T@SAT).tolist())); dK=det(Matrix((Kb.T@Kb).tolist()))
    idx=sympy.sqrt(sympy.Rational(int(dS),int(dK)))
    print(f"[m={m}] [K:SAT] = {idx} (pred m^12 = {m**12})")
    SATm=Matrix(SAT.tolist())
    Ms=(SATm.T*SATm).inv()*(SATm.T*Matrix(Kb.tolist()))
    den=1
    for q in Ms: den=lcm(den,q.q)
    print(f"[m={m}] denominator lcm = {den} (elementary iff = m)")
    if m==5:
        C=np.array([[int(q*5) for q in Ms.row(i)] for i in range(9*m-7)],dtype=np.int64)%5
        sel=[]
        for j in range(C.shape[1]):
            if rank_modp(C[:,sel+[j]],5)==len(sel)+1: sel.append(j)
            if len(sel)==12: break
        print(f"[m=5] independent denominator directions: {len(sel)}")
        for j in sel:
            summ={}
            for i in range(9*m-7):
                if C[i,j]%5:
                    t=labels[i].split('(')[0][:4] if labels[i].startswith('ax') else labels[i][:4]
                    summ[t]=summ.get(t,0)+1
            print(f"   gen {j}: {summ}")
