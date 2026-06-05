# GOLLUM_PROBE_11_v1.py - 5 June 2026 - THE OFFERINGS AT RUNG 2 (cera, full executable)
# (E2) derivation skeleton, all byte-verified at m = 5, 7, 11:
# (1) DIAGONAL BLOCKS: G_jj = 1(k=k') + 1(l=l') mod m EXACTLY (the self-intersection -(m-2) merges
#     with the doubled origin and vanishes mod m). Cross blocks: single affine lines: (1,2): {k-l},
#     (2,3): {k+l}, (1,3): the twisted line. => Q = sum of NINE affine-line channel pairings, no more.
# (2) THE TWELVE SHADOWS: each family casts 4 one-variable pushforwards along the PENCIL DIRECTIONS
#     {k, l, k-l, k+l}; 4 x 3 = 12. Q FACTORS THROUGH THE SHADOWS EXACTLY (Q on shadow-kernel = 0,
#     every K, every prime).
# (3) SHADOW-SPACE DIMS: 12m-18-3K(K+1)/2 measured exactly. The 18 = 6 relations per family =
#     3 (mass equality) + 2 (linear: m(k-l)=m(k)-m(l), m(k+l)=m(k)+m(l)) + 1 (THE POLARIZATION
#     (k-l)^2+(k+l)^2 = 2k^2+2l^2 - Lemma C's quadratic survivor, returning as a shadow relation).
# (4) THE CLOSE: the channel form is perfect on the full 12-shadow space (axis self-pairings = standard
#     1-var inner products; cross channels = hyperbolic pairs); rank(Q|m^K) = dim(image_K) - dim(radical)
#     = (12m-18-3K(K+1)/2) - (18+3K(K+1)/2) = 12(m-3) - 3K(K+1). At K=2: rho2 = 12m-54.
#     m=5's uniform +2 = relation collision at the boundary (the same structural frontier).
# Named finite checks for the line-by-line: (i) perfectness of the assembled channel form;
# (ii) W-perp inside W (deficit = relation count, instrumentally exact x3); (iii) relation completeness.
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
    kk=np.arange(m*m)//m; ll=np.arange(m*m)%m
    ok=True
    for j in range(3):
        blk=(G[j*m*m:(j+1)*m*m, j*m*m:(j+1)*m*m])%m
        pred=((kk[:,None]==kk[None,:]).astype(np.int64)+(ll[:,None]==ll[None,:]).astype(np.int64))%m
        if not (blk==pred).all(): ok=False
    dirs=[lambda K,L:(K)%m, lambda K,L:(L)%m, lambda K,L:(K-L)%m, lambda K,L:(K+L)%m]
    def shadow(c,j,d):
        out=np.zeros(m,dtype=np.int64)
        np.add.at(out, dirs[d](kk,ll), c[j*m*m:(j+1)*m*m])
        return out%m
    res=[]
    for K in [0,1,2]:
        mons=[(a,b) for a in range(K) for b in range(K) if a+b<=K-1]
        if K==0:
            Cf=[np.eye(m*m,dtype=np.int64)[i] for i in range(m*m)]
        else:
            Mom=np.array([((kk**a)%m)*((ll**b)%m)%m for (a,b) in mons],dtype=np.int64).reshape(len(mons),m*m)%m
            Cf=f_null(Mom,m)
        rowsC=[]
        for j in range(3):
            for c in Cf:
                v=np.zeros(N,dtype=np.int64); v[j*m*m:(j+1)*m*m]=c
                rowsC.append(v)
        C=np.array(rowsC,dtype=np.int64)
        S=np.zeros((C.shape[0],12*m),dtype=np.int64)
        for i,c in enumerate(C):
            col=0
            for j in range(3):
                for d in range(4):
                    S[i,col*m:(col+1)*m]=shadow(c,j,d); col+=1
        rS=rkp(S,m); rQ=rkp((C@G@C.T)%m,m)
        ker=f_null(S.T,m)
        rkk=rkp(((np.array(ker,dtype=np.int64)@C)%m@G@C.T)%m,m) if len(ker) else 0
        res.append((K,rQ,rS,rkk))
    print(f"[m={m}] diag=axes: {ok} | (K, rankQ, shadowdim, Q-on-kernel): {res} | laws: rank=12(m-3)-3K(K+1){' +2sat' if m==5 else ''}, dim=12m-18-3K(K+1)/2")
