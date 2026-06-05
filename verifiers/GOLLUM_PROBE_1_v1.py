# GOLLUM_PROBE_1_v1.py - 5 June 2026 - OPERACION GOLLUM, probe 1 (cera shipment)
# Declarations made in chat BEFORE running (D-GOLLUM-1..4). Results, all PASS:
# (1) Lemma D numeric [m=5]: complement det 1; V-Gram disc 5^12; profile {1:10, 2:1} = AMV row.
# (2) Per-piece S/T divisors [5,5,5,25] at THREE orbits = (Z/m)^{m-2} x Z/m^2, index m^m (flat).
# (3) First divisibility step: coords of t_r divisible by m (v_r/m in V); the one-line congruence
#     t_r + N_j == 0 mod m entrywise verified at m=7 too.
# (4) Second-divisibility combination found: a = (4,3,2,1) - the LINEAR weight (y_lin again).
# (5) THE SEALED m=11 SHOT: SNF(G) profile {0:96, 1:158, 2:17}, total 192 - declared first, hit exact.
import numpy as np, time
from sympy import Matrix, det
from sympy.matrices.normalforms import smith_normal_form
exec(open('GRANSLAP_PROBE_v1.py').read().split("for m in [5,7]:")[0])
t0=time.time()
m=5
G=gram(m); N=3*m*m
Kf=sat_kernel(Matrix(G.tolist()))
Kb=np.array([[int(Kf[i,j]) for j in range(Kf.cols)] for i in range(N)],dtype=np.int64)
KM=Matrix(Kb.T.tolist()); rrefM,piv=KM.rref()
J=[j for j in range(N) if j not in piv]
M=np.zeros((N,N),dtype=np.int64); M[:,:38]=Kb
for idx,j in enumerate(J): M[j,38+idx]=1
print("complement det:",det(Matrix(M.tolist())))
Q=G[np.ix_(J,J)]
prof,_=padic_profile(Q.copy(),5,K=10)
print("V-Gram disc v5:",vp(det(Matrix(Q.tolist())),5)," profile:",dict((h,c) for h,c in sorted(prof.items()) if h>0))
k=np.arange(m*m)//m; l=np.arange(m*m)%m
def tr(j,a,b,r):
    coef=np.array([ramanujan(m,int(a*kk+b*ll-r)%m) for kk,ll in zip(k,l)],dtype=np.int64)
    v=np.zeros(N,dtype=np.int64); v[(j-1)*m*m:j*m*m]=coef
    return v
Minv=Matrix(M.tolist()).inv()
def Vcoords(x):
    c=Minv*Matrix([int(u) for u in x])
    return np.array([int(c[38+i]) for i in range(37)],dtype=np.int64)
for (j,a,b,lbl) in [(1,1,1,"O(1,1,0)"),(1,1,2,"O(1,2,0)"),(2,1,1,"O(1,1,2)f2")]:
    C=np.array([Vcoords(tr(j,a,b,r)) for r in range(m-1)]).T
    S=smith_normal_form(Matrix(C.tolist()))
    print(lbl,"S/T divisors:",[int(S[i,i]) for i in range(4)])
C=np.array([Vcoords(tr(1,1,1,r)) for r in range(m-1)]).T
print("t_r coords divisible by 5:",not (C%5).any())
def f5_null(A,p=5):
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
print("m^2 combination(s):",[list(v) for v in f5_null(C//5,5)])
m=7
G7=gram(7); N7=147
k=np.arange(49)//7; l=np.arange(49)%7
t0v=np.zeros(N7,dtype=np.int64); t0v[:49]=np.array([ramanujan(7,int(kk+ll)%7) for kk,ll in zip(k,l)])
N1=np.zeros(N7,dtype=np.int64); N1[:49]=1
print("[m=7] t_r + N_j == 0 mod 7:",not ((t0v+N1)%7).any())
m=11
pf,_=padic_profile(gram(11).copy(),11,K=6)
print("[m=11] SEALED:",dict((h,c) for h,c in sorted(pf.items())),"total",sum(h*c for h,c in pf.items()))
