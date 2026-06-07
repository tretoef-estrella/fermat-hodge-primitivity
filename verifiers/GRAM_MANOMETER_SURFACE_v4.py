# GRAM_MANOMETER_SURFACE_v4.py - 4 June 2026 (night)
# EVEN-CAPABLE instrument. vs v3: rule (1,3) now carries omega^2 explicitly.
# With gamma := omega^2 (primitive m-th root, any m), SSvL (5) reads:
#   same family: k=k' or l=l' | (1,2): k-l == k'-l' | (2,3): k+l == k'+l'
#   (1,3): zeta' = omega^2*zeta*eta*eta'  ->  k' == k+l+l'+1  (the +1 is gamma^1 = omega^2)
# For odd m this is a relabeling of v3 (omega=-1) -> odd gates double as invariance tests.
# GATES (byte-exact, AMV Table 1): O1 (2,5) r37 5^10*25 | O2 (2,7) r91 7^38*49^5
#   E1 (2,6) r62 p2:{2:12} p3:{1:21,2:3,3:1} | E2 (2,8) r128 p2:{1:12,3:48,4:2,5:8,6:4}
# SEALED EVEN SHOTS (4 June 2026, before computation):
#   (2,16) 2^2034 | (2,18) 2^672 * 3^1356 | (2,20) 2^1734 * 5^870
import numpy as np, time

def gram(m):
    k = np.arange(m*m) // m; l = np.arange(m*m) % m
    kml = (k - l) % m; kpl = (k + l) % m; kpl1 = (k + l + 1) % m
    n = 3*m*m; A = np.zeros((n, n), dtype=np.int64)
    eq = lambda u, v: (u[:, None] == v[None, :]).astype(np.int64)
    same = (eq(k, k) | eq(l, l)).astype(np.int64); np.fill_diagonal(same, 0)
    B12 = eq(kml, kml); B13 = eq(kpl1, kml); B23 = eq(kpl, kpl)
    s = m*m
    A[0:s,0:s]=same; A[s:2*s,s:2*s]=same; A[2*s:,2*s:]=same
    A[0:s,s:2*s]=B12; A[s:2*s,0:s]=B12.T
    A[0:s,2*s:]=B13; A[2*s:,0:s]=B13.T
    A[s:2*s,2*s:]=B23; A[2*s:,s:2*s]=B23.T
    np.fill_diagonal(A, 2 - m)
    return A

def padic_eldiv(A, p, K):
    modr = p**K
    M = (A % modr).astype(np.int64)
    n = M.shape[0]; r = 0; shift = 0; counts = {}
    while r < n:
        sub = M[r:, r:]
        if not (sub % modr).any():
            return counts, False
        units = (sub % p) != 0
        if not units.any():
            if modr == p:
                return counts, True
            modr //= p; shift += 1
            M[r:, r:] = (sub // p) % modr
            continue
        i, j = np.unravel_index(np.argmax(units), units.shape)
        i += r; j += r
        if i != r: M[[r, i], :] = M[[i, r], :]
        if j != r: M[:, [r, j]] = M[:, [j, r]]
        inv = pow(int(M[r, r]) % modr, -1, modr)
        colf = (M[r+1:, r] * inv) % modr
        M[r+1:, r:] = (M[r+1:, r:] - colf[:, None] * M[r, r:][None, :]) % modr
        rowf = (M[r, r+1:] * inv) % modr
        M[r:, r+1:] = (M[r:, r+1:] - M[r:, r][:, None] * rowf[None, :]) % modr
        counts[shift] = counts.get(shift, 0) + 1
        r += 1
    return counts, False

KP = {2: 24, 3: 16, 5: 12, 7: 10, 17: 7, 19: 7}

def run(m, primes):
    A = gram(m); out = {}
    for p in primes:
        t0 = time.time()
        counts, flag = padic_eldiv(A, p, KP[p])
        rank = sum(counts.values()); exp = sum(h*c for h, c in counts.items())
        prof = {h: c for h, c in sorted(counts.items()) if h > 0}
        out[p] = (rank, exp, prof, flag)
        print(f"(2,{m}) p={p}: rank={rank} exp={exp} profile={prof} flag={flag} t={time.time()-t0:.1f}s", flush=True)
    return out

print("== GATES ==")
g5 = run(5, [5]);  assert g5[5]  == (37, 12, {1:10, 2:1}, False),  "O1 FAILED"
g7 = run(7, [7]);  assert g7[7]  == (91, 48, {1:38, 2:5}, False),  "O2 FAILED"
g6 = run(6, [2, 3])
assert g6[2] == (62, 24, {2:12}, False), "E1 p=2 FAILED"
assert g6[3] == (62, 30, {1:21, 2:3, 3:1}, False), "E1 p=3 FAILED"
g8 = run(8, [2]); assert g8[2] == (128, 228, {1:12, 3:48, 4:2, 5:8, 6:4}, False), "E2 FAILED"
print("ALL FOUR GATES PASS byte-exact (odd invariance + even capability). FIRING EVEN SHOTS.")
print("== SEALED: (2,16) 2^2034 | (2,18) 2^672*3^1356 | (2,20) 2^1734*5^870 ==")
s16 = run(16, [2])
print("  (2,16):", "PASS" if (s16[2][1] == 2034 and not s16[2][3]) else f"FAIL (exp {s16[2][1]})", flush=True)
s18 = run(18, [2, 3])
ok18 = s18[2][1] == 672 and s18[3][1] == 1356 and not s18[2][3] and not s18[3][3] and s18[2][0] == s18[3][0]
print("  (2,18):", "PASS" if ok18 else f"FAIL (exp2 {s18[2][1]}, exp3 {s18[3][1]})", flush=True)
s20 = run(20, [2, 5])
ok20 = s20[2][1] == 1734 and s20[5][1] == 870 and not s20[2][3] and not s20[5][3] and s20[2][0] == s20[5][0]
print("  (2,20):", "PASS" if ok20 else f"FAIL (exp2 {s20[2][1]}, exp5 {s20[5][1]})", flush=True)
print(f"rank targets (3(m-1)(m-2)+2): 16->{3*15*14+2} 18->{3*17*16+2} 20->{3*19*18+2}")
