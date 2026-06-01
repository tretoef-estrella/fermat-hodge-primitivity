#!/usr/bin/env python3
# ============================================================================
#  CHUCHI1_TRIANGLE_VERIFIER  — independent check of ADDENDUM §29 (Chuchi 1, step b)
#
#  This verifier COMPUTES the within-pair match (it does not assert it), per the Auditor's rule
#  "a verifier must verify, not assert." Two independent constructions, compared as SETS:
#   - MEASURED: the (t4,t5) within-pair A-survivor pairs from the real engine dump
#     BANGBANG_4_12_c2_mask7_basis.log (hard-coded here from Rafa's grep output, 54 pairs).
#   - PREDICTED: DS's triangular relation ρ = Σ_μ x^μ Σ_{ν≤μ} y^ν, reduced mod p^v: survivor (a,b)
#     iff both single-survivors (k ≢ -1 mod p^v) and (b mod p^v) ≤ (a mod p^v).
#  PASS iff the two SETS are equal (presentation-to-presentation, NOT by count alone).
#
#  RESULT on (4,12)c2 (p^v=4): set equality, 54=54. This is per-pair I=J on real block data.
#  HONEST LIMIT: ONE cell. One out-of-sample confirmation (different p or p^v) is owed before
#  φ iso over F_p is a theorem. The verifier prints this limit; it does not overclaim.
#
#  USAGE:  python3 CHUCHI1_TRIANGLE_VERIFIER.py
# ============================================================================

# MEASURED within-pair (t4,t5) survivors from BANGBANG_4_12_c2_mask7_basis.log (Rafa's grep, 54 pairs)
MEASURED = {
 (0,0),(0,4),(0,8),(1,0),(1,1),(1,4),(1,5),(1,8),(1,9),
 (2,0),(2,1),(2,10),(2,2),(2,4),(2,5),(2,6),(2,8),(2,9),
 (4,0),(4,4),(4,8),(5,0),(5,1),(5,4),(5,5),(5,8),(5,9),
 (6,0),(6,1),(6,10),(6,2),(6,4),(6,5),(6,6),(6,8),(6,9),
 (8,0),(8,4),(8,8),(9,0),(9,1),(9,4),(9,5),(9,8),(9,9),
 (10,0),(10,1),(10,10),(10,2),(10,4),(10,5),(10,6),(10,8),(10,9),
}

def predicted(m, pv):
    """DS triangular relation, reduced mod p^v: survivor (a,b) iff both single-survivors and
    (b mod pv) <= (a mod pv). Single-survivor: k ≢ -1 mod pv."""
    def single(k): return k % pv != pv - 1
    return {(a, b) for a in range(m) for b in range(m)
            if single(a) and single(b) and (b % pv) <= (a % pv)}

def verify(m, pv, measured):
    pred = predicted(m, pv)
    eq = (measured == pred)
    print(f"(4,12) char 2, m={m}, p^v={pv}:")
    print(f"  measured within-pair survivors : {len(measured)}")
    print(f"  DS-triangle predicted survivors: {len(pred)}")
    print(f"  SET EQUALITY (presentation, not just count)? {eq}")
    if not eq:
        print(f"    measured not predicted: {sorted(measured-pred)}")
        print(f"    predicted not measured: {sorted(pred-measured)}")
    free = len([k for k in range(m) if k % pv != pv-1])**2
    print(f"  (free-tensor would be {free}; coupling reduces to {len(pred)} — the triangle is real)")
    return eq

if __name__ == "__main__":
    print("="*70)
    print("CHUCHI 1 step (b): within-pair coupling = DS triangle ν≤μ mod p^v ? (REAL engine data)")
    print("="*70)
    ok = verify(12, 4, MEASURED)
    print()
    print("="*70)
    print(f"RESULT: per-pair I=J on real block data (presentation-to-presentation) = {ok}")
    print("="*70)
    print("HONEST LIMIT: ONE cell (p^v=4, dimA=3, char 2). Strong — real data, set equality, NOT")
    print("counting — but a single point. ONE out-of-sample confirmation (different p or p^v) is owed")
    print("before φ iso over F_p is a theorem. With it: per-pair I=J (out of sample) + tensor-over-pairs")
    print("(§27.2) + Frobenius single-variable (§26.3) => φ iso over F_p, the campaign's first theorem.")
    print("UNCHANGED OPEN: the Z-lift = DS Conjecture 1.2; the n=4 monster block stays conditional.")
