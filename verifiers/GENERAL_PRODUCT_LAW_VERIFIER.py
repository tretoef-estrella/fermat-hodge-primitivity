#!/usr/bin/env python3
# ============================================================================
#  GENERAL_PRODUCT_LAW_VERIFIER  — independent check of ADDENDUM §23
#
#  The general block law (all dimA):
#     rank(block) = rec(dimA, ceil(A_vars/2)) * rec(dimB, ceil(B_vars/2))
#  with rec(d, l) = 1 (l=0); d (l=1); DS_{2(l-1)}(d+1) (l>=2).
#
#  Three attacks, each recomputed from scratch (DS Rem 4.4 coded independently):
#   ATTACK 1 — consistency: reproduces the dimA=1 cells byte-exact.
#   ATTACK 2 — total: sum over masks = DS_4(m) for all measured cells.
#   ATTACK 3 — BLIND prediction of (4,15) char5 (dimA=4), a cell NOT used to build the law;
#              must match v11 measured values AND total = DS_4(15).
#
#  HONEST LIMIT: confirms the FORM of the law (product of two rec-ladders) on all available
#  data incl. out-of-sample. Does NOT prove the factor VALUE rec(d,l)=DS_{2(l-1)}(d+1) in
#  general (the self-similarity nail, §22.3/§23.6) — that is the single residual pen-and-paper
#  item, and the detector (localization by centrality, §22.2) does not need it.
#
#  USAGE:  python3 GENERAL_PRODUCT_LAW_VERIFIER.py
# ============================================================================
import math

def DS(n, m):
    d = (m - 1) % 2
    if n == 0: return 1
    if n == 2: return 3*m*m - 9*m + 6 + d
    if n == 4: return 15*m**3 - 90*m**2 + 175*m - 100 + (15*m - 39)*d
    if n == 6: return 105*m**4 - 1050*m**3 + 3955*m**2 - 6335*m + 3325 + (210*m*m - 1302*m + 2010)*d
    raise ValueError

def rec(d, l):
    if l == 0: return 1
    if l == 1: return d
    return DS(2*(l-1), d + 1)

def block_value(dimA, dimB, k, NV):
    """rank of the block with k B-variables (popcount), NV-k A-variables."""
    a = NV - k
    return rec(dimA, math.ceil(a/2)) * rec(dimB, math.ceil(k/2))

# measured cells (popcount -> rank), byte-exact from logs
MEASURED = {
    "(4,6)c2  dimA1 dimB4": (4, 1, 4, {0:1,1:4,2:4,3:36,4:36,5:400}),
    "(4,10)c2 dimA1 dimB8": (4, 1, 8, {0:1,1:8,2:8,3:168,4:168,5:5120}),
    "(4,6)c3  dimA2 dimB3": (4, 2, 3, {0:20,1:18,2:18,3:38,4:38,5:141}),
    "(4,12)c3 dimA2 dimB9": (4, 2, 9, {0:20,1:54,2:54,3:434,4:434,5:7761}),
}

def attack_1_consistency():
    print("="*70)
    print("ATTACK 1 — product law reproduces measured cells byte-exact (incl. dimA=1)")
    print("="*70)
    allok = True
    for lab, (n, dimA, dimB, blocks) in MEASURED.items():
        NV = n + 1
        ok = all(block_value(dimA, dimB, k, NV) == blocks[k] for k in blocks)
        allok = allok and ok
        detail = ", ".join(f"k{k}:{block_value(dimA,dimB,k,NV)}={blocks[k]}" for k in sorted(blocks))
        print(f"  {lab}: {'OK' if ok else 'FAIL<<'}")
        print(f"      {detail}")
    print("ATTACK 1:", "PASSED" if allok else "FAILED")
    return allok

def attack_2_total():
    print("\n" + "="*70)
    print("ATTACK 2 — total over all masks = DS_4(m), dimA+dimB = m-1")
    print("="*70)
    allok = True
    for lab, (n, dimA, dimB, blocks) in MEASURED.items():
        NV = n + 1; m = dimA + dimB + 1
        tot = sum(block_value(dimA, dimB, bin(mask).count('1'), NV) for mask in range(2**NV))
        direct = DS(n, m); ok = (tot == direct); allok = allok and ok
        print(f"  {lab}: Σ={tot}  DS_{n}({m})={direct}  {'OK' if ok else 'FAIL<<'}")
    print("ATTACK 2:", "PASSED" if allok else "FAILED")
    return allok

def attack_3_blind():
    print("\n" + "="*70)
    print("ATTACK 3 — BLIND prediction of (4,15) char5 (dimA=4, NOT used to build the law)")
    print("="*70)
    n, dimA, dimB = 4, 4, 10; NV = 5; m = 15
    pred = {k: block_value(dimA, dimB, k, NV) for k in range(NV+1)}
    print(f"  predicted by popcount: {pred}")
    v11_measured = {360, 1080, 10900}  # the non-trivial distinct values listed in v11 §3.2
    pred_nontrivial = {pred[k] for k in (1,2,3,4,5)}
    match = v11_measured.issubset(pred_nontrivial)
    print(f"  v11 measured distinct values {sorted(v11_measured)} ⊆ predicted {sorted(pred_nontrivial)}? {match}")
    tot = sum(block_value(dimA, dimB, bin(mask).count('1'), NV) for mask in range(2**NV)); direct = DS(n, m)
    print(f"  predicted total Σ={tot}  DS_4(15)={direct}  {'OK' if tot==direct else 'FAIL<<'}")
    print(f"  k0 corner = {pred[0]} = DS_4(dimA+1)=DS_4(5)={DS(4,5)} (all-A, structurally forced)")
    ok = match and (tot == direct)
    print("ATTACK 3:", "PASSED (out-of-sample dimA=4 prediction correct)" if ok else "FAILED")
    return ok

if __name__ == "__main__":
    a1 = attack_1_consistency()
    a2 = attack_2_total()
    a3 = attack_3_blind()
    print("\n" + "="*70)
    print(f"GENERAL PRODUCT LAW: attack1={a1}  attack2={a2}  attack3(blind)={a3}")
    print("="*70)
    print("HONEST LIMIT: confirms the FORM (product of two rec-ladders = DS §17 tensor explicit)")
    print("on all data incl. the out-of-sample dimA=4 cell. Does NOT prove the factor VALUE")
    print("rec(d,l)=DS_{2(l-1)}(d+1) in general (self-similarity, §23.6) — the single residual")
    print("pen-and-paper item. The detector (localization by centrality, §22.2) does not need it.")
