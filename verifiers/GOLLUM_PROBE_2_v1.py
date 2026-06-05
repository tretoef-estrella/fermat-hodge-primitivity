# GOLLUM_PROBE_2_v1.py - 5 June 2026 - OPERACION GOLLUM probe 2 (cera shipment)
# (B) The second-step proof's displayed identities, entrywise:
#     - EXACT: sum_r r*t_r = m*pb_L(y_lin) in A (Ramanujan telescoping)  [m=5,7: PASS]
#     - CONGRUENCE: pb_L(y_lin) == a*pb_ax1(y_lin) + b*pb_ax2(y_lin) + ((m-1)/2)(a+b-1)*N_j (mod m)
#       for ALL live (a,b), all families [m=5,7: PASS]
#     => sum_r r*v_r in m^2 V (the second saturation step) is PROVEN.
# (C) Demotion anatomy at m=5: the order-25 dual generator (Lemma D dictionary) restricts to
#     order 25 on EVERY one of the nine pieces; explicit piece bases [s0,s1,s2,sigma] all have
#     disc 5^5 = m^{2m-5} (the flat value, exhibited).
#     => #m^2(V*/V) = (3m-6) - 2*rho with rho = rank of the glue projection onto the piece-top
#        socles: measured rho = 4, 5, 5 at m = 5, 7, 11 (from profiles 1, 5, 17). [CONJ law: rho=5, m>=7]
import numpy as np, time
from sympy import Matrix, det, lcm
exec(open('GRANSLAP_PROBE_v1.py').read().split("for m in [5,7]:")[0])
for m in [5,7]:
    N=3*m*m
    k=np.arange(m*m)//m; l=np.arange(m*m)%m
    ylin=np.array([x-(m-1)//2 for x in range(m)],dtype=np.int64)
    def pb(j,a,b,f):
        xv=(a*k+b*l)%m
        v=np.zeros(N,dtype=np.int64); v[(j-1)*m*m:j*m*m]=np.array([f[x] for x in xv])
        return v
    ok=True
    for j in [1,2,3]:
        Nj=np.zeros(N,dtype=np.int64); Nj[(j-1)*m*m:j*m*m]=1
        for a in range(1,m):
            for b in range(1,m):
                if ((pb(j,a,b,ylin)-a*pb(j,1,0,ylin)-b*pb(j,0,1,ylin)-((m-1)//2)*(a+b-1)*Nj)%m).any(): ok=False
    T=np.zeros(N,dtype=np.int64)
    for r in range(m):
        T+=r*np.concatenate([np.array([ramanujan(m,int(kk+ll-r)%m) for kk,ll in zip(k,l)]),np.zeros(2*m*m,dtype=np.int64)])
    print(f"[m={m}] congruence: {ok}; exact sum r*t_r = m*pb(ylin): {(T==m*pb(1,1,1,ylin)).all()}")
m=5; N=75
G=gram(m)
Kf=sat_kernel(Matrix(G.tolist()))
Kb=np.array([[int(Kf[i,j]) for j in range(Kf.cols)] for i in range(N)],dtype=np.int64)
KM=Matrix(Kb.T.tolist()); rrefM,piv=KM.rref()
J=[j for j in range(N) if j not in piv]
M=np.zeros((N,N),dtype=np.int64); M[:,:38]=Kb
for idx,j in enumerate(J): M[j,38+idx]=1
Minv=Matrix(M.tolist()).inv()
Q=Matrix(G[np.ix_(J,J)].tolist()); Qinv=Q.inv()
gen=None
for i in range(37):
    col=Qinv[:,i]; d=1
    for q in col: d=lcm(d,q.q)
    if d==25: gen=col; break
k5=np.arange(25)//5; l5=np.arange(25)%5
def tr5(j,a,b,r):
    coef=np.array([ramanujan(5,int(a*kk+b*ll-r)%5) for kk,ll in zip(k5,l5)],dtype=np.int64)
    v=np.zeros(N,dtype=np.int64); v[(j-1)*25:j*25]=coef
    return v
def Vc(x):
    c=Minv*Matrix([int(u) for u in x])
    return np.array([int(c[38+i]) for i in range(37)],dtype=np.int64)
for (j,a,b,lbl) in [(1,1,1,"f1(1,1)"),(1,1,2,"f1(1,2)"),(1,1,3,"f1(1,3)"),(1,1,4,"f1(1,4)"),
                    (2,1,1,"f2(1,1)"),(2,1,2,"f2(1,2)"),(2,1,3,"f2(1,3)"),(2,1,4,"f2(1,4)"),(3,1,1,"f3(1,1)")]:
    C=np.array([Vc(tr5(j,a,b,r)) for r in range(4)]).T
    Csig=np.zeros(37,dtype=np.int64)
    for r in range(4): Csig+=r*(C[:,r]//5)
    Csig=Csig-4*((C[:,0]+C[:,1]+C[:,2]+C[:,3])//5)
    Bs=np.column_stack([C[:,0]//5,C[:,1]//5,C[:,2]//5,Csig//5])
    Gs=Matrix((Bs.T@G[np.ix_(J,J)]@Bs).tolist())
    p=(Matrix(Bs.tolist()).T)*Q*gen
    ordv=None
    for n in [1,5,25]:
        sol=Gs.solve(p*n); dd=1
        for q in sol: dd=lcm(dd,q.q)
        if dd==1: ordv=n; break
    print(f"   {lbl}: piece disc 5^{vp(det(Gs),5)}, 25-generator restriction order {ordv}")
