#!/usr/bin/env python3
# ============================================================================
#  BLOCK_RANK_THEOREM_RIFLE.py
#    — the command-line demonstrator of the block-rank theorem.
#
#  WHAT THIS IS
#  ------------
#  A play-with-it proof of the campaign's capstone theorem (THE_NAIL_THEOREM.md):
#
#      rec(d, l) = DS_{2(l-1)}(d+1)   for every block dimension d and depth l,
#
#  where rec(d,l) is the rank a CRT block of the Fermat splitting contributes at
#  coupling depth l. The theorem identifies this rank as the CONSTANT TERM OF A
#  CLOSED LATTICE WALK (Degtyarev-Shimada, Remark 4.4, read as a walk count).
#
#  Give it d and l; it shows you the walk, computes the rank two independent ways
#  (the closed-walk count AND the published DS closed form, when one exists), and
#  confirms they agree byte-exact. It is a demonstrator, not a search engine: it
#  lets a reader SEE the mechanism the theorem names.
#
#  THE MECHANISM, IN ONE BREATH
#  ----------------------------
#  Picture a walker on an integer grid of dimension  h = floor(d/2).  It takes
#  exactly  N = 2l  steps; each step moves +1 or -1 along one axis. The rank is
#  the number of step-sequences that bring the walker back to where it started
#  — closed walks, "return to home". One twist, and it is the whole story of the
#  parity correction delta_m that the published formula carries as an unexplained
#  patch:
#
#      d ODD  (m=d+1 EVEN) : the walker MAY REST  -> count (1+S)^N constant term
#      d EVEN (m=d+1 ODD)  : the walker may NOT rest -> count  S^N  constant term
#
#  So delta is not a patch bolted onto a formula. It is a single bit of the walk:
#  whether a step may be "stay put". That is the discovery, in one line.
#
#  WHY TWO WAYS
#  ------------
#  For depths l=2,3,4 (i.e. DS_2, DS_4, DS_6) Degtyarev-Shimada printed a closed
#  polynomial. The rifle evaluates BOTH the walk and that polynomial and checks
#  they match — the gate. For deeper l (DS_8 and beyond) NO closed form was ever
#  published; there the closed walk IS the definition (this is the new content),
#  and the rifle reports the walk value as firm, flagged accordingly.
#
#  SCOPE — STATED HONESTLY (rectitud)
#  ----------------------------------
#  This rifle computes the per-block VALUE (the complex-side rank ladder). The
#  theorem it demonstrates fixes that value; it does NOT touch the integral
#  torsion question — the SWAN, Degtyarev-Shimada Conjecture 1.2 — which compares
#  the value against the prime-field rank and remains OPEN. A walk count is a
#  rank, not a torsion verdict. The theorem is also conditional on the campaign
#  dictionary (the measured CRT block = the DS core module); see THE_NAIL_THEOREM.md.
#
#  USAGE
#  -----
#    python3 BLOCK_RANK_THEOREM_RIFLE.py            # the gate: d=2..7, l=2..4
#    python3 BLOCK_RANK_THEOREM_RIFLE.py 3 4        # one shot: rec(3,4)=1107 (the Mac value)
#    python3 BLOCK_RANK_THEOREM_RIFLE.py 2 5        # a depth beyond any closed form
#  Pure standard library. No dependencies. No disk. Self-contained.
# ============================================================================

import sys
from math import comb
from collections import defaultdict


# --- the walk counts --------------------------------------------------------

def closed_walk(h, N):
    """Constant term of S^N, S = sum_{i=1..h} (x_i + x_i^-1).
    = number of closed walks of N unit (+/-1) steps on Z^h returning to origin
      (the NO-REST walk; d even / m odd branch)."""
    if h == 0:
        return 1 if N == 0 else 0
    cur = {(0,) * h: 1}
    for _ in range(N):
        nxt = defaultdict(int)
        for v, c in cur.items():
            for i in range(h):
                for s in (1, -1):
                    w = list(v); w[i] += s
                    nxt[tuple(w)] += c
        cur = nxt
    return cur[(0,) * h]


def closed_walk_with_rest(h, N):
    """Constant term of (1+S)^N: closed walks of AT MOST N directional steps,
    the outer 1 supplying a REST step (the d odd / m even branch).
    = sum_k C(N,k) * closed_walk(h, k)."""
    return sum(comb(N, k) * closed_walk(h, k) for k in range(N + 1))


def block_rank(d, l):
    """The block-rank theorem: rec(d,l) as a closed-walk constant term.
       lattice dimension h = floor(d/2), walk length N = 2l,
       rest permitted iff d is ODD (m = d+1 even)."""
    h = d // 2
    N = 2 * l
    return closed_walk_with_rest(h, N) if (d % 2 == 1) else closed_walk(h, N)


# --- the published DS closed forms (the gate, depths l=2,3,4 only) ----------

def DS_closed(n, m):
    """Degtyarev-Shimada Remark 4.4 closed polynomials. n=2,4,6 only published."""
    e = (m - 1) % 2
    if n == 2: return 3*m*m - 9*m + 6 + e
    if n == 4: return 15*m**3 - 90*m*m + 175*m - 100 + (15*m - 39)*e
    if n == 6: return 105*m**4 - 1050*m**3 + 3955*m*m - 6335*m + 3325 + (210*m*m - 1302*m + 2010)*e
    return None   # no published closed form beyond DS_6


# --- one shot ---------------------------------------------------------------

def shot(d, l):
    h = d // 2
    N = 2 * l
    rest = (d % 2 == 1)
    rank = block_rank(d, l)
    n = 2 * (l - 1)            # DS index: rec(d,l) = DS_{2(l-1)}(d+1)
    m = d + 1
    ds = DS_closed(n, m)

    print(f"  rec(d={d}, l={l})  =  DS_{n}({m})")
    print(f"    walk: {N} steps on Z^{h}   |   rest {'ALLOWED (d odd, m even)' if rest else 'FORBIDDEN (d even, m odd)'}")
    print(f"    closed-walk count      = {rank}")
    if ds is not None:
        ok = (rank == ds)
        print(f"    DS Remark 4.4 closed   = {ds}   [{'MATCH' if ok else 'MISMATCH'}]   <- the gate")
        if d == 3 and l == 4:
            print(f"    (this is 1107, the value the 8 GB Mac measured directly — reproduced from the sofa)")
        return ok
    else:
        print(f"    DS Remark 4.4 closed   = (none published for n={n}) — here the WALK is the definition  [FIRM]")
        return True


def gate():
    print("=" * 70)
    print("BLOCK-RANK THEOREM RIFLE — the gate (d=2..7, depths l=2..4)")
    print("  rec(d,l) = DS_{2(l-1)}(d+1) = constant term of a closed lattice walk")
    print("=" * 70)
    allok = True
    for d in range(2, 8):
        for l in range(2, 5):
            print()
            allok &= shot(d, l)
    print()
    print("=" * 70)
    print(f"GATE: {'ALL SHOTS ON TARGET — walk = DS, byte-exact' if allok else 'MISMATCH FOUND'}")
    print("Mechanism: the block rank is a return-to-home count; delta = may the walker rest.")
    print("Scope: this is the per-block VALUE. The swan (DS Conjecture 1.2, integral")
    print("torsion) is a different question and remains OPEN. See THE_NAIL_THEOREM.md.")
    print("=" * 70)
    return allok


if __name__ == "__main__":
    if len(sys.argv) == 3:
        d, l = int(sys.argv[1]), int(sys.argv[2])
        if d < 0 or l < 1:
            print("d >= 0, l >= 1 required"); sys.exit(1)
        print("=" * 70)
        print(f"BLOCK-RANK THEOREM RIFLE — one shot")
        print("=" * 70)
        print()
        shot(d, l)
        print()
        print("Mechanism: closed lattice walk, return to home; rest iff d odd.")
        print("Scope: per-block VALUE only; the swan (integral torsion) is open.")
    else:
        gate()
