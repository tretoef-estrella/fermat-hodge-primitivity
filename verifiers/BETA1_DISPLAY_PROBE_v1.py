# BETA1_DISPLAY_PROBE_v1.py - 4 June 2026 (night) - cera shipment of the verified display identities
# Verifies entrywise, for EVERY t and c and both primes m=5,7, the four identities displayed in
# THE_LEMMA_R_TEXT_v1.md (Lemma R.2), plus integrality+kernel membership of the three pure generators.
# Result of record: PASS on all counts (both primes).
import numpy as np
exec(open('GRANSLAP_PROBE_v1.py').read().split("for m in [5,7]:")[0])
for m in [5,7]:
    G=gram(m); N=3*m*m
    k=np.arange(m*m)//m; l=np.arange(m*m)%m
    ones=np.zeros((3,N),dtype=np.int64)
    for j in range(3): ones[j,j*m*m:(j+1)*m*m]=1
    ok=True
    for c in range(m):
        for t in range(m):
            y=np.zeros(N,dtype=np.int64); y[0:m*m]=((k+t*l)%m==c).astype(np.int64)
            Gy=G@y
            if t==0:
                pred=ones[0]+ones[1]+ones[2]
            elif t==1:
                z3=np.zeros(N,dtype=np.int64); z3[2*m*m:]=((k-l)%m==(c+1)%m).astype(np.int64)
                pred=2*ones[0]+ones[1]+m*z3-m*y
            elif t==m-1:
                z2=np.zeros(N,dtype=np.int64); z2[m*m:2*m*m]=((k-l)%m==c).astype(np.int64)
                pred=2*ones[0]+m*z2+ones[2]-m*y
            else:
                pred=2*ones[0]+ones[1]+ones[2]-m*y
            if not (Gy==pred).all(): ok=False; print(f"m={m} t={t} c={c} MISMATCH")
    for j in range(3):
        if not (G@ones[j]==m*np.ones(N,dtype=np.int64)).all(): ok=False; print(f"m={m} GN{j+1} fail")
    print(f"[m={m}] all displayed fiber identities (every t, every c) + G*N_j = m*1_A: {'PASS' if ok else 'FAIL'}")
    for j in [1,2,3]:
        yv=np.ones(m,dtype=np.int64); yv[m-1]=1-m
        v1=np.zeros(N,dtype=np.int64); v1[(j-1)*m*m:j*m*m]=np.array([yv[x] for x in k])
        v2=np.zeros(N,dtype=np.int64); v2[(j-1)*m*m:j*m*m]=np.array([yv[x] for x in l])
        g=v1-v2
        gm=g//m if not (g%m).any() else None
        inK = gm is not None and not (G@gm).any()
        print(f"   pure generator family {j}: (pb_a(1-me)-pb_b(1-me))/m integral and in K: {inK}")
