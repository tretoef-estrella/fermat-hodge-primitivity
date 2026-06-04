# LACAZADELOSPELADOS.py - 4 June 2026 (night)
# THE THIRD-CELL DECIDER for the peeling laws of the Watermark campaign.
# Architect: Rafael Amichis Luengo. Engine name is the Architect's (D26).
#
# WHAT IT DOES: computes the fine Galois-isotypic spectrum of the line lattice V of the
# Fermat surface (2,11) under the full translation torus <U,W,Z>, with exact integer
# arithmetic end to end (sympy kernels/discs; int64 hot path with magnitude guards and
# an exact spot-audit). disc V = 11^192 is the published AMV value (in-sample for the
# Watermark law); what is SEALED is the spectrum's internal structure.
#
# INNOVATIONS (campaign, Architect's program): line Z-basis with hard determinant gate;
# Ramanujan-sum integer orbit projectors; saturated kernels with stacked-determinant
# double audit of the global glue; closure-to-the-law checksum per prime.
#
# PROTOCOL: two byte-exact gates (the closed cells (2,5) and (2,7)) MUST pass before the
# sealed shot fires. Heartbeat prints flush at every stage. Zero disk writes. RAM < 1 GB.
#
# SEAL (in acta, findings v70 SS80.3, written before any computation):
#   (2,11) fine spectrum = 27 orbit pieces, rank 10 each, EVERY disc = +-11^17,
#   glue = 11^134, closure to 192.
# KNOWN CLEAN-ABORT: the int64 magnitude guards may trip at m=11; if so the engine
# aborts with an assert BEFORE producing any number (no silent corruption possible).
import numpy as np, random, time
from sympy import Matrix, eye, det, sqrt, Integer
from math import gcd
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
        for x in v: den=lcm(den,x.q)
        cols.append([int(x*den) for x in v])
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
    assert (Mx*sat)==Matrix.zeros(Mx.rows,r), "SATURATION CHECK FAILED"
    return sat

def vp(x,p):
    x=abs(int(x)); v=0
    while x and x%p==0: x//=p; v+=1
    return v

def run_cell(m, disc_target_abs, primes, trials=200):
    t0=time.time(); G=gram(m); N=3*m*m
    rk=rank_mod(G)
    best=None
    for trial in range(trials):
        order=list(range(N)); random.seed(7000+trial); random.shuffle(order)
        chosen=[]
        for i in order:
            if rank_mod(G[:,chosen+[i]])==len(chosen)+1: chosen.append(i)
            if len(chosen)==rk: break
        GramB=Matrix(G[np.ix_(chosen,chosen)].tolist())
        d=det(GramB)
        if abs(d)==disc_target_abs: best=(chosen,GramB,d); break
    assert best, f"no Z-basis of lines found for m={m}"
    chosen,GramB,discV=best
    print(f"[m={m}] rank={rk}, basis trial {trial}, disc V = {discV} (|.|=target: {abs(discV)==disc_target_abs}) [{time.time()-t0:.0f}s]",flush=True)
    GramBinv=GramB.inv()
    GB=Matrix(G[:,chosen].tolist())
    def line_coords(i):
        c=GramBinv*GB[i,:].T
        assert all(x.is_integer for x in c)
        return [int(x) for x in c]
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
        P=np.zeros((N,N),dtype=np.int64); P[sig,np.arange(N)]=1
        assert (P.T@G@P==G).all(), f"{name} not isometry"
        cols=[line_coords(int(sig[i])) for i in chosen]
        A=Matrix(cols).T
        assert A.T*GramB*A==GramB, f"{name} operator gate failed"
        ops[name]=A
    print(f"[m={m}] U,W,Z gated [{time.time()-t0:.0f}s]",flush=True)
    AUo,AWo,AZo=[np.array(ops[n].tolist(),dtype=object) for n in 'UWZ']
    def topow(A):
        out=[np.eye(rk,dtype=object)]
        for _ in range(m-1): out.append(out[-1]@A)
        return out
    PUo,PWo,PZo=topow(AUo),topow(AWo),topow(AZo)
    mx=max(int(abs(x)) for P in (PUo+PWo+PZo) for x in P.flat)
    assert mx < 2**20, f"power magnitude {mx} unsafe"
    PU=[P.astype(np.int64) for P in PUo]; PW=[P.astype(np.int64) for P in PWo]; PZ=[P.astype(np.int64) for P in PZo]
    elems={}
    for s in range(m):
        for t in range(m):
            ST=PU[s]@PW[t]
            for r in range(m):
                elems[(s,t,r)]=ST@PZ[r]
    emax=max(int(np.abs(E).max()) for E in elems.values())
    assert emax < 2**30, f"element magnitude {emax} unsafe"
    s0,t0g,r0=random.choice(list(elems.keys()))
    exact=(PUo[s0]@PWo[t0g])@PZo[r0]
    assert (exact==elems[(s0,t0g,r0)].astype(object)).all(), "INT64 SPOT AUDIT FAILED"
    print(f"[m={m}] {len(elems)} group elements built, int64-guarded + spot-audited [{time.time()-t0:.0f}s]",flush=True)
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
    Mtriv_np=np.zeros((rk,rk),dtype=np.int64)
    for g in elems.values(): Mtriv_np+=g
    print(f"[m={m}] building {len(orbits)} orbit projectors (int64)... [{time.time()-t0:.0f}s]",flush=True)
    Ms=[(O,M_orbit_np(O)) for O in orbits]
    tot=Mtriv_np.copy()
    for _,Mo in Ms: tot+=Mo
    assert (tot==m**3*np.eye(rk,dtype=np.int64)).all(), "PROJECTOR PARTITION FAILED"
    print(f"[m={m}] partition = m^3*I: PASS [{time.time()-t0:.0f}s]",flush=True)
    results=[]; prod=Integer(1)
    Ctriv=sat_kernel(m**3*eye(rk)-Matrix(Mtriv_np.tolist()))
    dtriv=det(Ctriv.T*GramB*Ctriv) if Ctriv.cols else Integer(1)
    results.append(("triv",Ctriv.cols,dtriv)); allB=Ctriv; prod*=dtriv
    I=np.eye(rk,dtype=np.int64)
    for O,Mo in Ms:
        if rank_mod(m**3*I-Mo)==rk: continue
        C=sat_kernel(m**3*eye(rk)-Matrix(Mo.tolist()))
        if C.cols==0: continue
        d=det(C.T*GramB*C)
        results.append((f"O{O[0]}",C.cols,d)); prod*=d
        allB=Matrix.hstack(allB,C)
    print(f"== m={m} FINE SPECTRUM ==",flush=True)
    for name,rkp,d in results:
        pv=" ".join(f"v{p}={vp(d,p)}" for p in primes)
        print(f"  {name}: rank={rkp} disc={d}  {pv}")
    ranksum=sum(r for _,r,_ in results)
    direct=abs(det(allB))
    print(f"rank sum={ranksum}/{rk}; glue={direct}; formula check={sqrt(abs(prod/discV))}")
    for p in primes:
        clos=sum(vp(d,p) for _,_,d in results)-2*vp(int(direct),p)
        print(f"CLOSURE p={p}: {clos}")
    print(f"[m={m}] total {time.time()-t0:.0f}s")
    return results,direct


print("==== GATE 1: (2,5) fine (must reproduce the closed ledger) ====", flush=True)
res5,g5=run_cell(5, 5**12, [5])
nt5=[r for r in res5 if r[0]!="triv"]
assert len(nt5)==9 and all(r==4 for _,r,_ in nt5) and all(abs(d)==5**5 for _,_,d in nt5) and int(g5)==5**17, "GATE 1 FAILED"
print("GATE 1 PASS byte-exact", flush=True)

print("==== GATE 2: (2,7) fine (must reproduce the closed ledger) ====", flush=True)
res7,g7=run_cell(7, 7**48, [7])
nt7=[r for r in res7 if r[0]!="triv"]
assert len(nt7)==15 and all(r==6 for _,r,_ in nt7) and all(abs(d)==7**9 for _,_,d in nt7) and int(g7)==7**44, "GATE 2 FAILED"
print("GATE 2 PASS byte-exact. FIRING THE SEALED SHOT.", flush=True)

print("==== SEALED SHOT: (2,11) FINE SPECTRUM ====", flush=True)
print("SEAL (findings v70 SS80.3): 27 pieces, rank 10, EVERY disc = +-11^17, glue = 11^134, closure 192", flush=True)
res,glue=run_cell(11, 11**192, [11])
nontriv=[r for r in res if r[0]!="triv"]
ok_n=len(nontriv)==27; ok_r=all(r==10 for _,r,_ in nontriv)
flat=all(abs(d)==11**17 for _,_,d in nontriv); ok_g=(int(glue)==11**134)
print(f"SEAL VERDICT: pieces 27: {ok_n} | ranks all 10: {ok_r} | all |disc|=11^17: {flat} | glue=11^134: {ok_g}")
print("OVERALL:", "PASS" if (ok_n and ok_r and flat and ok_g) else "FAIL")
