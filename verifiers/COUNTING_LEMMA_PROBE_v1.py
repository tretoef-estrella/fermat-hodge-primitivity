# COUNTING_LEMMA_PROBE_v1.py - 4 June 2026 (night) - Lemma C verification (cera shipment)
# (1) rank_{F_m}(SAT mod m) = 9m-19 at m=5,7 (direct, parametrization-free) => d = dim K/SAT = 12.
# (2) The 12-parameter polynomial relation family of Lemma C, explicitly encoded
#     (y-basis encoding c_i = f(i), using sum_i y_i = 1 mod m), is valid and has rank 12 (both primes).
# Self-caught and documented: a first harness encoded functions as c_i = f(i)-f(m-1), which drops
# the constant part mod m; 6 of 12 relations failed until the encoding was corrected. The direct
# rank measurement (1) was never affected.
import numpy as np
exec(open('GRANSLAP_PROBE_v1.py').read().split("for m in [5,7]:")[0])
def satblocks(m):
    G,N,K0,K0blocks,F,tr=build_K0_F(m)
    k=np.arange(m*m)//m; l=np.arange(m*m)%m
    def pullback(j,a,b,y):
        xv=(a*k+b*l)%m
        v=np.zeros(N,dtype=np.int64); v[(j-1)*m*m:j*m*m]=np.array([y[x] for x in xv])
        return v
    Z0=[np.eye(m,dtype=np.int64)[i]-np.eye(m,dtype=np.int64)[m-1] for i in range(m-1)]
    cols=[]
    for j in [1,2,3]:
        for (aa,bb) in [(1,0),(0,1)]:
            for y in Z0: cols.append(pullback(j,aa,bb,y))
    for nm,(j1,a1,b1),(j2,a2,b2),s0 in [("ov12",(1,1,m-1),(2,1,m-1),0),("ov23",(2,1,1),(3,1,1),0),("ov13",(1,1,1),(3,1,m-1),1)]:
        for y in Z0: cols.append(pullback(j1,a1,b1,y)+pullback(j2,a2,b2,np.roll(y,s0)))
    Nv=[]
    for j in [1,2,3]:
        v=np.zeros(N,dtype=np.int64); v[(j-1)*m*m:j*m*m]=1; Nv.append(v)
    cols+=[Nv[0]-Nv[1],Nv[1]-Nv[2]]
    return G,N,np.array(cols).T
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
    G,N,SAT=satblocks(m)
    enc=lambda f: np.array([f[i]%m for i in range(m-1)],dtype=np.int64)
    X=np.arange(m,dtype=np.int64); Zf=np.zeros(m,dtype=np.int64); On=np.ones(m,dtype=np.int64)
    def relvec(u1k,u1l,u2k,u2l,u3k,u3l,w12,w23,w13,e1,e2):
        c=[enc(f) for f in [u1k,u1l,u2k,u2l,u3k,u3l,w12,w23,w13]]
        c.append(np.array([e1,e2],dtype=np.int64))
        return np.concatenate(c)%m
    rels=[]
    rels.append(relvec(On,-On,Zf,Zf,Zf,Zf,Zf,Zf,Zf,0,0))
    rels.append(relvec(Zf,Zf,On,-On,Zf,Zf,Zf,Zf,Zf,0,0))
    rels.append(relvec(Zf,Zf,Zf,Zf,On,-On,Zf,Zf,Zf,0,0))
    rels.append(relvec(-On,Zf,Zf,Zf,On,Zf,Zf,Zf,Zf,1,1))
    rels.append(relvec(Zf,Zf,-On,Zf,On,Zf,Zf,Zf,Zf,0,1))
    rels.append(relvec(-On,Zf,-On,Zf,Zf,Zf,On,Zf,Zf,0,0))
    rels.append(relvec(Zf,Zf,-On,Zf,-On,Zf,Zf,On,Zf,0,0))
    rels.append(relvec(-On,Zf,Zf,Zf,-On,Zf,Zf,Zf,On,0,0))
    rels.append(relvec(-X,X,-X,X,Zf,Zf,X,Zf,Zf,0,0))
    rels.append(relvec(Zf,Zf,-X,-X,-X,-X,Zf,X,Zf,0,0))
    rels.append(relvec(-X,-X,Zf,Zf,(-X+On)%m,X,Zf,Zf,X,0,0))
    X2=(X*X)%m
    rels.append(relvec((-2*X2)%m,(-2*X2)%m,(-2*X2)%m,(-2*X2)%m,(-2*X2+2*X)%m,(-2*X2-2*X-On)%m,X2,X2,X2,0,0))
    R=np.array(rels).T
    ok=all(not (SAT@R[:,i]%m).any() for i in range(12))
    print(f"[m={m}] rank(SAT mod {m}) = {rank_modp(SAT,m)} (pred {9*m-19}); 12 relations valid: {ok}, rank {rank_modp(R,m)} (pred 12)")
