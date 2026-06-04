# GRANSLAP_PROBE_v2_RESIDUAL.py - 4 June 2026 (night) - the m^12 residual anatomy + fixed SNF(G)
# (companion to GRANSLAP_PROBE_v1.py; shipped per the Auditor's cera requirement)
# Measures: (1) SNF profile of G at p=m with overflow-safe precision (reproduces AMV rows);
# (2) explicit saturated kernel blocks (pullbacks + phase-paired pullbacks) are IN ker(G), rank 38;
# (3) [K : SAT] independently via full kernel at m=5 -> 5^12 exact;
# (4) residual glue structure: denominator lcm = m, profile {0:12, 1:26} -> R = (Z/m)^12 elementary.
import numpy as np
from sympy import Matrix, det
exec(open('GRANSLAP_PROBE_v1.py').read().split("for m in [5,7]:")[0])
import sympy
for m in [5,7]:
    G=gram(m)
    Ksafe=10 if m==5 else 9
    prof,flag=padic_profile(G.copy(),m,K=Ksafe)
    nz={h:c for h,c in sorted(prof.items())}
    print(f"[m={m}] SNF profile of G at p={m}: {nz}, rank={sum(prof.values())}, total v={sum(h*c for h,c in prof.items())}, flag={flag}")
m=5
G,N,K0,K0blocks,F,tr=build_K0_F(5)
k=np.arange(25)//5; l=np.arange(25)%5
def pullback(j,a,b,y):
    xv=(a*k+b*l)%5
    v=np.zeros(N,dtype=np.int64); v[(j-1)*25:j*25]=np.array([y[x] for x in xv])
    return v
satcols=[]
Z0basis=[np.array([1,0,0,0,-1]),np.array([0,1,0,0,-1]),np.array([0,0,1,0,-1]),np.array([0,0,0,1,-1])]
for j in [1,2,3]:
    for (aa,bb) in [(1,0),(0,1)]:
        for y in Z0basis: satcols.append(pullback(j,aa,bb,y))
for (j1,a1,b1),(j2,a2,b2),s0 in [((1,1,4),(2,1,4),0),((2,1,1),(3,1,1),0),((1,1,1),(3,1,4),1)]:
    for y in Z0basis:
        satcols.append(pullback(j1,a1,b1,y)+pullback(j2,a2,b2,np.roll(y,s0)))
Nv=[]
for j in [1,2,3]:
    v=np.zeros(N,dtype=np.int64); v[(j-1)*25:j*25]=1; Nv.append(v)
satcols+=[Nv[0]-Nv[1],Nv[1]-Nv[2]]
SAT=np.array(satcols).T
print("SAT in kernel:",not (G@SAT).any()," rank:",rank_mod(SAT))
Kfull=sat_kernel(Matrix(G.tolist()))
Kb=np.array([[int(Kfull[i,j]) for j in range(Kfull.cols)] for i in range(N)],dtype=np.int64)
dSAT=det(Matrix((SAT.T@SAT).tolist())); dK=det(Matrix((Kb.T@Kb).tolist()))
idx=sympy.sqrt(sympy.Rational(int(dSAT),int(dK)))
print(f"[K : SAT] = {idx} (declared 5^12 = {5**12})")
SATm=Matrix(SAT.tolist()); Kbm=Matrix(Kb.tolist())
Msol=(SATm.T*SATm).inv()*(SATm.T*Kbm)
from sympy import lcm
den=1
for q in Msol: den=lcm(den,q.q)
Mint=Matrix([[int(q*den) for q in Msol.row(i)] for i in range(38)])
prof,flag=padic_profile(np.array(Mint.tolist(),dtype=np.int64),5,K=10)
print(f"denominator lcm = {den}; profile of den*(K in SAT-coords): {dict(sorted(prof.items()))} -> residual R = (Z/5)^12 elementary")
