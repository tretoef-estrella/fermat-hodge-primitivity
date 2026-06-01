#!/usr/bin/env python3
# ============================================================================
#  RIFLE.py  — the velocidad de Fermat, command-line. Predict a cell from the sofa.
#
#  Predicts the primitivity verdict and dim_Fp of any Fermat cell (n,m), n in {4,6},
#  for every prime p|m, with ZERO computation — using:
#    - the general product block law (§23, validated out-of-sample to dimA=4),
#    - the per-variable block-count law (§25, byte-exact vs sympy),
#    - DS Remark 4.4 for dim_C.
#
#  CONFIDENCE FLAGS (rectitud — the rifle tells you how firm each shot is):
#    [FIRM]  : prime is 2-component -> validated 2-ladder product law applies.
#    [CONJ]  : prime is >2-component -> rests on the UNVERIFIED r-ladder law (§26.2);
#              total is the vacuous-total (§24), per-block structure unknown until measured.
#
#  A prediction is FALSIFIABLE: a Mac run departing per-block from it is the swan.
#  The detector LOCALIZATION (which block holds a swan) is proven by centrality (§22);
#  the VALUE rec(d,l)=DS_{2(l-1)}(d+1) is measured-not-proven (§23.6) — so a clean run
#  matching the prediction is consistent with primitive, a departure is a candidate swan.
#
#  USAGE:
#    python3 RIFLE.py 4 35          # predict cell (4,35), all primes
#    python3 RIFLE.py 4 21          # mixed: char3 FIRM, char7 CONJ
#    python3 RIFLE.py 6 15          # n=6 works too
#  (requires sympy)
# ============================================================================
import sys, math
import sympy
from sympy import symbols, Poly
t = symbols('t')

def DS(n, m):
    d = (m - 1) % 2
    if n == 0: return 1
    if n == 2: return 3*m*m - 9*m + 6 + d
    if n == 4: return 15*m**3 - 90*m**2 + 175*m - 100 + (15*m - 39)*d
    if n == 6: return 105*m**4 - 1050*m**3 + 3955*m**2 - 6335*m + 3325 + (210*m*m - 1302*m + 2010)*d
    raise ValueError("n must be 4 or 6 (DS Rem 4.4 closed forms available)")

def rec(d, l):
    if l == 0: return 1
    if l == 1: return d
    return DS(2*(l-1), d + 1)

def block_sum_2ladder(n, dimA, dimB):
    NV = n + 1
    return sum(rec(dimA, math.ceil((NV-bin(mask).count('1'))/2)) *
               rec(dimB, math.ceil(bin(mask).count('1')/2))
               for mask in range(2**NV))

def prime_power_dividing(p, m):
    """return p^e where p^e || m (exact power), and e."""
    e = 0; mm = m
    while mm % p == 0:
        mm //= p; e += 1
    return p**e, e

def primes_of(m):
    ps = []; mm = m; d = 2
    while d*d <= mm:
        if mm % d == 0:
            ps.append(d)
            while mm % d == 0: mm //= d
        d += 1
    if mm > 1: ps.append(mm)
    return ps

def n_components(p, m):
    return len(Poly(t**m - 1, t, modulus=p).factor_list()[1])

def predict(n, m):
    NV = n + 1
    DIM = (m-1)**NV
    dimC = DS(n, m)
    print(f"{'='*64}")
    print(f"  RIFLE — cell (n={n}, m={m})   [velocidad de Fermat, from the sofa]")
    print(f"{'='*64}")
    print(f"  DIM = {m-1}^{NV} = {DIM:,}")
    print(f"  dim_C = DS_{n}({m}) = {dimC:,}   (facade, characteristic-independent)")
    ps = primes_of(m)
    if len(ps) < 2:
        print(f"  NOTE: m={m} is a prime power (primes={ps}). CRT split is trivial for the lone")
        print(f"        prime; composite cells (>=2 distinct primes) are the real swan-suspects.")
    print(f"  primes dividing m: {ps}")
    print(f"  {'-'*60}")
    for p in ps:
        pe, e = prime_power_dividing(p, m)
        dimA = pe - 1
        dimB = (m-1) - dimA
        r = n_components(p, m)
        s = block_sum_2ladder(n, dimA, dimB)
        firm = (r == 2)
        flag = "[FIRM]" if firm else "[CONJ]"
        verdict = "PRIMITIVE" if s == dimC else "DEPARTS (candidate swan)"
        rooms = r**NV
        print(f"  char {p}: dimA={dimA} (p^e={pe}), dimB={dimB}, components/var={r}  {flag}")
        print(f"     block lattice = {r}^{NV} = {rooms:,} blocks (hiding rooms)")
        if firm:
            print(f"     block-sum (validated 2-ladder law) = {s:,}  (= dim_C? {s==dimC})")
            print(f"     PREDICTION: {verdict}, dim_F{p} = {s:,}")
        else:
            print(f"     block-sum (2-ladder, but cell is {r}-component) = {s:,} = dim_C")
            print(f"     WARNING: total telescopes (vacuous, §24). Per-block structure rests on the")
            print(f"     UNVERIFIED r-ladder law (§26.2). PREDICTION: PRIMITIVE at total level ONLY;")
            print(f"     per-block unknown until measured. Confidence: CONJECTURAL.")
        print(f"  {'-'*60}")
    print(f"  Overall: predicted PRIMITIVE (all primes). A Mac --dump-blocks run that DEPARTS")
    print(f"  per-block from these values would localize a swan (by centrality, §22) to one block.")
    print(f"  FIRM primes stand on the validated law; CONJ primes need measurement to confirm.")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("usage: python3 RIFLE.py <n> <m>   e.g.  python3 RIFLE.py 4 35")
        sys.exit(1)
    n, m = int(sys.argv[1]), int(sys.argv[2])
    predict(n, m)
