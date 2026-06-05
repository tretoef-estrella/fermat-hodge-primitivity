# GOLLUM_PROBE_3_v1.py - 5 June 2026 - A-side piece anatomy + the rho falsifier (cera shipment)
# Part A (PASS, three primes): the jewel identity t_r + N_j = m*pb_L(e_r) exact; piece bases
#   [pb(e_0..e_{m-3}), a0] built purely in A (a0 from the proven Lemma-R congruence); piece disc
#   m^{2m-5} (flat: 5^5, 7^9, 11^17 instantly, no kernels); dual SNF {1:3, 2:m-4} at m=5,7,11
#   = the O/lambda^{2m-5} prediction (confirming the v2 self-catch: tops/piece = m-4, not 1).
# Part B (the falsifier FIRING): rank of ALL line classes' top-socle projections (proper Smith
#   transforms) = 9 (m=5, FULL) and 43 (m=7): the v2 "demote = 2*rho" heuristic is DEAD by its
#   own falsifier. Autopsy in GOLLUM_REPORT_v3.md; the mechanism returns to open hunt with the
#   correct object named (full m-adic discriminant-form computation of H-perp/H heights).
# [Code: parts of GOLLUM probe runs 3 and 3b, merged; see report for the run outputs of record.]
import numpy as np
from sympy import Matrix, det
from sympy.matrices.normalforms import smith_normal_form
exec(open('GRANSLAP_PROBE_v1.py').read().split("for m in [5,7]:")[0])
from math import gcd as g_
for m in [5,7,11]:
    N=3*m*m; G=gram(m)
    k=np.arange(m*m)//m; l=np.arange(m*m)%m
    def pb(j,a,b,f):
        xv=(a*k+b*l)%m
        v=np.zeros(N,dtype=np.int64); v[(j-1)*m*m:j*m*m]=np.array([f[x] for x in xv])
        return v
    j,a,b=1,1,1
    Nj=np.zeros(N,dtype=np.int64); Nj[:m*m]=1
    e0=np.eye(m,dtype=np.int64)[0]
    t0v=np.array([ramanujan(m,int(kk+ll)%m) for kk,ll in zip(k,l)],dtype=np.int64)
    T0=np.zeros(N,dtype=np.int64); T0[:m*m]=t0v
    ylin=np.array([x-(m-1)//2 for x in range(m)],dtype=np.int64)
    a0=(pb(j,a,b,ylin)-pb(j,1,0,ylin)-pb(j,0,1,ylin)-((m-1)//2)*Nj)//m
    lifts=[pb(j,a,b,np.eye(m,dtype=np.int64)[r]) for r in range(m-2)]+[a0]
    B=np.array(lifts).T
    Gs=Matrix((B.T@G@B).tolist())
    S=smith_normal_form(Gs)
    prof={}
    for i in range(m-1):
        d=vp(int(S[i,i]),m); prof[d]=prof.get(d,0)+1
    print(f"[m={m}] jewel: {(T0+Nj==m*pb(1,1,1,e0)).all()}; disc m^{vp(det(Gs),m)}; dual SNF {dict(sorted(prof.items()))}")
