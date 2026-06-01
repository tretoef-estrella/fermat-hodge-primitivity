#!/usr/bin/env python3
# ============================================================================
#  BLOCK_COUNT_LAW_VERIFIER  — independent check of ADDENDUM §25
#
#  For the Auditor Jefe to attack the closed form for the per-variable CRT block count:
#     # coprime primary components of t^m-1 over F_p
#        = 1 + sum_{d | m', d>1} phi(d)/ord_d(p),   m' = prime-to-p part of m.
#  Checked against sympy's ACTUAL factorization of t^m-1 over F_p (the ground truth).
#
#  Also reports the cells where the count exceeds 2 (where the A×B LETHAL DUAL picture
#  is a simplification and the block lattice is finer).
#
#  HONEST LIMIT: this verifies the COUNT (a number-theoretic fact). It does not by itself
#  recompute the per-block ranks; it tells you HOW MANY blocks per variable a cell has,
#  which refines the detector's granularity (§25.3). The measured cells are all
#  2-component, so prior block tables are unaffected.
#
#  USAGE:  python3 BLOCK_COUNT_LAW_VERIFIER.py   (requires sympy)
# ============================================================================
import sympy
from sympy import symbols, Poly, divisors, totient, n_order

t = symbols('t')

def predicted_count(p, m):
    """1 + sum_{d|m', d>1} phi(d)/ord_d(p), m' = prime-to-p part of m."""
    mp = m
    while mp % p == 0:
        mp //= p
    total = 1  # the (t-1) primary part
    for d in divisors(mp):
        if d > 1:
            total += totient(d) // n_order(p, d)
    return int(total)

def actual_count(p, m):
    """ground truth: number of distinct irreducible factors of t^m-1 over F_p."""
    f = Poly(t**m - 1, t, modulus=p)
    return int(len(f.factor_list()[1]))

if __name__ == "__main__":
    print("Verifying the per-variable block-count closed form vs sympy factorization.\n")
    print(f"{'p':>2} {'m':>3} {'actual':>7} {'predicted':>10}  match   note")
    print("-"*50)
    allok = True
    over2 = []
    for p in (2, 3, 5, 7, 11):
        for m in range(3, 30):
            if m % p != 0:
                continue
            a = actual_count(p, m)
            q = predicted_count(p, m)
            ok = (a == q); allok = allok and ok
            note = "" if a == 2 else (f"<-- {a} blocks (A×B is simplification)" if a > 2 else "")
            if a > 2:
                over2.append((p, m, a))
            mark = "OK" if ok else "FAIL<<"
            print(f"{p:>2} {m:>3} {a:>7} {q:>10}  {mark:>5}   {note}")
    print("-"*50)
    print(f"closed form matches sympy factorization in ALL cases: {allok}")
    print()
    print("Cells with >2 per-variable components (finer block lattice than A×B):")
    for p, m, a in over2:
        print(f"  (n,*)/char {p}, m={m}: {a} components per variable")
    print()
    print("HONEST LIMIT: verifies the COUNT (number theory). The detector's localization")
    print("(centrality, §22) holds for any number of components; this just tells you how many")
    print("hiding rooms per variable, from the sofa. Measured cells are all 2-component, so")
    print("prior block tables stand; the general detector uses this count.")
