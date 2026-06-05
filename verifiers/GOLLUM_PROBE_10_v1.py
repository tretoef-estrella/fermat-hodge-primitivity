# GOLLUM_PROBE_10_v1.py - 5 June 2026 - THE DOUBLE COLLEJA (E2) (cera, full executable)
# COLLEJA 1 [SEALED x3]: B2 on the deep glue = the LINE GRAM mod m on moment-free combos.
#   Pencil chain: affine law + independence => H_top = combos with zero mass / k-moment / l-moment
#   per family (mod m); for such c the fiber identities give <v_c, L> in mZ (constants x zero mass,
#   y_lin x zero moments, axis x zero mass), so v_c/m in L* is a legitimate representative and
#   B2(z,z') = <v_c/m, v_c'> = (c^T G c')/m mod Z, i.e. F_m-value = c^T G c' mod m. Descent to H_top
#   is clean by symmetry (source-kernel combos pair to 0 mod m by the same divisibility).
#   MEASURED: rank(C G C^T mod m) = 8 / 30 / 78 at m = 5 / 7 / 11 = rho2 FIRM, declared first.
#   (Self-caught en route: the naive expectation "c^T G c' divisible by m" was a confusion of
#   (1/m)Z/Z-values with divided integers - logged.)
# COLLEJA 2 [the ladder, FIRM x3]: Q is invariant under a (Z/m)^2-translation action with per-family
#   GL2 twists (equivariance found instrumentally; solution torus nonempty, unimodular reps exist),
#   so Q's symbol lives in R = F_m[u,v]/(u^m,v^m) and moment-free = the submodule m^2=(u,v)^2.
#   THE RANK LADDER over the moment filtration K = 0..4:
#     m=5: 26 20  8  0  0 | m=7: 48 42 30 12 0 | m=11: 96 90 78 60 36
#   *** rank(Q|m^K) = 12(m-3) - 3K(K+1) for m >= 7 (clamped at 0); m=5 carries +2 saturation ***
#   At K=2 this IS rho2 = 12m-54. Drop per step = 6K = 2 x (graded dim 3K): the factor 2 is the rank
#   of the Toeplitz u-block (probe 9) - the two collejas are ONE mechanism ("una doble").
# REMAINING for (E2)-uniform: prove the ladder at K=2 from the symbol in R (route fully specified).
import numpy as np, time
exec(open('GRANSLAP_PROBE_v1.py').read().split("for m in [5,7]:")[0])
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
for m in [5,7,11]:
    N=3*m*m; G=gram(m)
    k=np.arange(m*m)//m; l=np.arange(m*m)%m
    ranks=[]
    for K in range(5):
        mons=[(a,b) for a in range(K) for b in range(K) if a+b<=K-1]
        if K==0:
            Cf=[np.eye(m*m,dtype=np.int64)[i] for i in range(m*m)]
        else:
            Mom=np.array([((k**a)%m)*((l**b)%m)%m for (a,b) in mons],dtype=np.int64).reshape(len(mons),m*m)%m
            Cf=f_null(Mom,m)
        rowsC=[]
        for j in range(3):
            for c in Cf:
                v=np.zeros(N,dtype=np.int64); v[j*m*m:(j+1)*m*m]=c
                rowsC.append(v)
        C=np.array(rowsC,dtype=np.int64)
        ranks.append(rkp((C@G@C.T)%m,m))
    law=[max(12*(m-3)-3*K*(K+1),0) for K in range(5)]
    print(f"[m={m}] ladder {ranks} | law 12(m-3)-3K(K+1): {law} | K=2 = rho2: {ranks[2]}")
