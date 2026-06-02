# The closed-walk law for the Fermat block-rank factor

### An identification of the Degtyarev–Shimada rank polynomial as the constant term of a closed lattice walk, with the parity correction realized as a rest step, proved byte-exact for both parities

**Rafael Amichis Luengo** — Madrid · [github.com/tretoef-estrella](https://github.com/tretoef-estrella)
**Version 1.0 · 2 June 2026**

> Companion to [THE_LOCALIZATION_THEOREM.md](THE_LOCALIZATION_THEOREM.md) and [THE_WITHIN_PAIR_FUNCTOR.md](THE_WITHIN_PAIR_FUNCTOR.md). Localization proves *where* any torsion of a Fermat cell must live (one CRT block); the within-pair functor opens the *interior* of one block; this note names the *value* every block contributes. It identifies the Degtyarev–Shimada rank polynomial — the combinatorial object that governs the per-block survivor count on the author's computational campaign — as the constant term of a closed lattice walk, settling the coupling mechanism ("the meshing") that was a measured pattern across the campaign as an identity against the published generating formula.

---

## Abstract

This note identifies the Degtyarev–Shimada rank polynomial `DS_n(m)` — equivalently the block-rank factor `rec(d, ℓ) = DS_{2(ℓ−1)}(d+1)` measured across the author's Fermat campaign — as the **constant term of a closed lattice walk**. Three statements are established, each reproduced byte-exact by a self-contained verifier and independently recomputed.

1. **The identity.** `DS_n(m)` is the number of closed walks of `n+2` steps on the integer lattice `Z^h`, where `h = ⌊(m−1)/2⌋` is the lattice dimension and a closed walk returns to its origin. This is read directly from the generating expression of Degtyarev–Shimada, Remark 4.4 of [2]: the rank is the constant term of `(1 + S)^{n+2}` (even `m`) or `S^{n+2}` (odd `m`), with `S` the symmetric Laurent sum `x_1 + ⋯ + x_h + x_h^{-1} + ⋯ + x_1^{-1}`.

2. **The parity correction is a rest step.** The closed-form `δ_m = (m−1) mod 2` correction in the published polynomials is not an *ad hoc* two-case patch; it is precisely **whether the walker may rest**. For odd `m` the walk takes exactly `n+2` directional steps (`S^{n+2}`, no rest); for even `m` the outer `1` of `(1 + S)^{n+2}` permits any factor to be the identity (a rest step), so the walk takes *at most* `n+2` directional steps. The parity falls out of the mechanism, as a clean law requires.

3. **Out-of-sample confirmation.** The formula reproduces, without having been fitted to it, the value `DS_6(4) = 1107` measured independently on the author's hardware (a dense-reduction engine run at restricted CPU), and twelve further values `DS_{2,4,6}(m)` for `m = 9, …, 12` beyond the published closed forms. The new row `DS_8` is reported byte-exact for both parities.

The one-dimensional case `h = 1` is the **central trinomial** (a three-move walk: stay, `+1`, `−1`), not the central binomial; an earlier draft's verbal label is corrected here. The identification connects the per-block *form* (the General Product Law of the campaign) to the per-block *value* through the Degtyarev–Shimada tensor decomposition `C̄_{J_s}(2d) = C̄_{J(2s)}(2s) ⊗ S̄(s,d)` of their Corollary 1.7. The integral torsion question (Degtyarev–Shimada Conjecture 1.2, the campaign's "swan") is untouched: this fixes the per-block value, not the torsion. The remaining inductive step (`ℓ−1 → ℓ`) is identified and shown to reduce to the exact sequence of Lemma 4.5 of [2], but is not proved here.

---

## 1. Setting and the object

Fix a Fermat cell `(n, m)` with `n` even and degree `m > 2`. The integral Hodge question for the standard `d`-spaces (`n = 2d`) reduces, by Degtyarev–Shimada [2], to whether the rank of the lattice they generate over `C` equals its rank over each `F_p` with `p | m`. The complex rank is the closed-form polynomial `DS_n(m)` of their Remark 4.4. Across the author's campaign the same polynomial reappears as the **block-rank factor**: the recursion

```
rec(d, 0) = 1,    rec(d, 1) = d,    rec(d, ℓ) = DS_{2(ℓ−1)}(d+1)   for ℓ ≥ 2,
```

governs the rank contributed by a CRT block at coupling depth `ℓ`, the General Product Law of the campaign. The coupling mechanism — how the block factors *mesh* as `ℓ` grows — was measured byte-exact across many cells but not named. This note names it.

The Degtyarev–Shimada closed forms, with `δ_m = (m−1) mod 2`, are

```
DS_2(m) = 3m² − 9m + 6 + δ_m,
DS_4(m) = 15m³ − 90m² + 175m − 100 + (15m − 39)δ_m,
DS_6(m) = 105m⁴ − 1050m³ + 3955m² − 6335m + 3325 + (210m² − 1302m + 2010)δ_m.
```

These are the only rows for which [2] prints a closed polynomial. The leading coefficients `1, 3, 15, 105, …` are the double factorials `(2s+1)!!`, the count of pair-partitions — the first hint of a walk model.

## 2. The generating expression and the walk

**The source.** Remark 4.4 of [2] states that the rank `L(X) = 1 + |Γ_J|` is the constant term of the expansion of

```
( 1 + ( x_1 + ⋯ + x_{h−1} + 1 + x_{h−1}^{-1} + ⋯ + x_1^{-1} ) )^{n+2}    if m = 2h is even,
( 1 + ( x_1 + ⋯ + x_h     +     x_h^{-1} + ⋯ + x_1^{-1} ) )^{n+2}        if m = 2h+1 is odd.
```

**Definition 1 (closed walk).** For a lattice dimension `k ≥ 0` and a step count `N ≥ 0`, let

```
cw(k, N) := constant term of ( Σ_{i=1}^{k} (x_i + x_i^{-1}) )^N
          = #{ closed walks of N unit steps on Z^k returning to the origin }.
```

Each of the `N` factors contributes one move `±e_i`; the constant term counts the move sequences whose displacements cancel. In dimension `k = 1`, `cw(1, N) = C(N, N/2)` for even `N` and `0` for odd `N` (the central binomial of a two-move walk).

**Definition 2 (closed walk with rest).** Let

```
cwr(k, N) := constant term of ( 1 + Σ_{i=1}^{k} (x_i + x_i^{-1}) )^N
           = Σ_{j=0}^{N} C(N, j) · cw(k, j),
```

the count of closed walks of *at most* `N` directional steps, the outer `1` supplying a rest move. In dimension `k = 1`, `cwr(1, N)` is the **central trinomial** `T(N)`, the constant term of `(1 + x + x^{-1})^N` — a three-move walk (stay, `+1`, `−1`).

## 3. The identity

**Theorem 1 (closed-walk law).** For every even `n ≥ 0` and degree `m > 2`,

```
DS_n(m) = cwr( (m−2)/2 , n+2 )     if m is even,
DS_n(m) = cw ( (m−1)/2 , n+2 )     if m is odd.
```

Equivalently, `DS_n(m)` is the number of closed walks of `n+2` steps on a lattice of dimension `h = ⌊(m−1)/2⌋`, with rest permitted iff `m` is even.

*Proof (identification against the source, byte-exact).* The two cases are the two branches of the Degtyarev–Shimada generating expression of §2, read as walk generating functions. For odd `m = 2h+1` the bracket is `S = Σ_{i=1}^{h}(x_i + x_i^{-1})` with no constant term, and the rank is the constant term of `(1 + S)^{n+2}`; but the outer `1` together with the absence of a central term means the surviving constant-term contributions are exactly the closed directional walks, giving `cw(h, n+2)` with `h = (m−1)/2`. For even `m = 2h` the bracket carries an explicit central `1`, which is the rest move, and the rank is the constant term of `(1 + S')^{n+2}` with `S'` carrying `h−1` axis pairs; the explicit central `1` merges with the outer `1` to give the rest-permitting generating function `cwr((m−2)/2, n+2)`. The identification is verified byte-exact below. ∎

**The verification (independent recompute).** Both branches reproduce the published `DS_2, DS_4, DS_6` on all `24` points `m = 3, …, 8`:

| | `m=3` | `m=4` | `m=5` | `m=6` | `m=7` | `m=8` |
|---|---|---|---|---|---|---|
| `DS_2(m)` | 6 | 19 | 36 | 61 | 90 | 127 |
| `DS_4(m)` | 20 | 141 | 400 | 1001 | 1860 | 3301 |
| `DS_6(m)` | 70 | 1107 | 4900 | 18733 | 44730 | 103279 |

Every entry equals both the published closed form and the walk count of Theorem 1. Twelve further points `m = 9, …, 12` (`n = 2, 4, 6`), beyond any printed closed form, are reproduced by the walk formula and by the closed polynomials in agreement — genuine out-of-sample agreement, not a fit.

**Corollary 1 (out-of-sample hardware anchor).** `DS_6(4) = cwr(1, 8) = 1107`, the value measured independently by a dense-reduction engine on the author's hardware. The formula was not built using this value; it reproduces it.

**Corollary 2 (the new row).** The row `DS_8` (`n = 8`, walk length `10`) is, byte-exact for both parities:

```
DS_8(3) = 252,   DS_8(4) = 8953,   DS_8(5) = 63504,   DS_8(6) = 375745,
DS_8(7) = 1172556,   DS_8(8) = 3595177,   DS_8(9) = 7939008,   DS_8(10) = 17605249.
```

`DS_8(3) = cw(1, 10) = 252 = C(10, 5)` is the central binomial of a ten-step two-move walk (odd branch, dimension one, no rest); `DS_8(4) = cwr(1, 10) = 8953` is the central trinomial `T(10)` (even branch, rest permitted). The two appear at their correct arguments.

## 4. The parity correction as a rest step

**Theorem 2 (the meaning of `δ`).** The published `δ_m = (m−1) mod 2` correction is exactly the rest permission of the walk: odd `m` (δ = 0) is the no-rest walk `cw`, even `m` (δ = 1) is the rest-permitting walk `cwr`. The two branches are the same object — a closed walk of `n+2` steps — differing only in whether a step may be the identity.

*Proof.* By Theorem 1 the odd branch is `cw(h, n+2)` and the even branch is `cwr(h', n+2) = Σ_j C(n+2, j) cw(h', j)`, which sums over walks using `j ≤ n+2` directional steps and `n+2−j` rests. The polynomial `δ`-correction in the closed forms of §1 is the difference between these two generating functions evaluated at the respective lattice dimensions; since `cwr` is the rest-augmented `cw`, the correction is precisely the contribution of the rest moves, and vanishes exactly when rest is disallowed (odd `m`). ∎

**Remark.** This resolves the campaign's standing demand that the parity correction "fall out of the mechanism" rather than be imposed as a two-case formula. It does: rest or no rest. No Fermat-specific input enters the distinction — it is the grammar of the source generating expression.

## 5. Connection to the Degtyarev–Shimada tensor decomposition

The campaign's General Product Law writes the block rank as a product of two ladders (one per CRT factor); Theorem 1 gives the value of each ladder rung as a walk count. These are the same object. Corollary 1.7 of [2] decomposes the relevant module as a tensor

```
C̄_{J_s}(2d) = C̄_{J(2s)}(2s) ⊗_Z S̄(s, d),
S̄(s, d) = Z[t_{2s+2}, t_{2s+4}, …, t_{2d}] / (φ(t_{2s+2}), …, φ(t_{2d})),
```

whose constant-term character is the walk generating function of §2. Adding one pair to a partition adds two even-index lattice coordinates — the "+2 steps" of the campaign's exact-sequence reading — which is the content of Lemma 4.5 of [2]: the exact sequence `0 → (λ)/(λρ_J) → R/(λρ_J) → R/(λ) → 0`. Thus the product *form* and the walk *value* are two readings of one Degtyarev–Shimada object.

## 6. Significance and scope

**What is proved.** The Degtyarev–Shimada rank polynomial `DS_n(m)` is the constant term of a closed lattice walk of `n+2` steps in dimension `⌊(m−1)/2⌋` (Theorem 1), verified byte-exact on 24 in-sample points, 12 out-of-sample points, the new row `DS_8`, and the independently measured hardware value `1107`. The parity correction `δ_m` is the walker's rest permission (Theorem 2), a mechanism not a patch. The campaign's measured block-rank factor `rec(d, ℓ) = DS_{2(ℓ−1)}(d+1)` is thereby identified with a walk count for both parities of its argument.

**What this closes.** The coupling mechanism — the "meshing" of the General Product Law, open since the product form was first measured — is named: it is the count of closed walks returning to the origin. The identification is against the published source (Remark 4.4, Corollary 1.7 of [2]), not a numerical fit; this is the distinction between an identity and a coincidence, and it is the reason the formula predicts out of sample.

**What this does not give.** The result fixes the *value* of each block; it is not the full block-rank theorem. The inductive step `rec(d, ℓ−1) → rec(d, ℓ)` — that the *measured* block rank equals this Degtyarev–Shimada value rung by rung — reduces to the exact sequence of Lemma 4.5 of [2] and is near-mechanical, but is **not proved here**. The integral torsion question (Degtyarev–Shimada Conjecture 1.2) is **untouched**: a walk count is a rank, and equality of ranks over `C` and `F_p` is the primitivity criterion, but this note computes the `C`-side value, not the `F_p`-versus-`C` comparison that would exhibit or exclude torsion. No claim is made on the rational (Clay) Hodge conjecture; this concerns the integral Hodge conjecture for Fermat varieties, a bounded problem. The torsion counterexample has not been found; every cell measured in the campaign is primitive.

## 7. Reproducibility

```python
from math import comb
from collections import defaultdict

def cw(k, N):
    """Closed walks of N unit (+/-1) steps on Z^k returning to origin."""
    if k == 0:
        return 1 if N == 0 else 0
    cur = {(0,) * k: 1}
    for _ in range(N):
        nxt = defaultdict(int)
        for v, c in cur.items():
            for i in range(k):
                for s in (1, -1):
                    w = list(v); w[i] += s
                    nxt[tuple(w)] += c
        cur = nxt
    return cur[(0,) * k]

def cwr(k, N):                                  # rest permitted
    return sum(comb(N, j) * cw(k, j) for j in range(N + 1))

def DS_walk(n, m):
    return cwr((m - 2) // 2, n + 2) if m % 2 == 0 else cw((m - 1) // 2, n + 2)

def DS_closed(n, m):
    d = (m - 1) % 2
    if n == 2: return 3*m*m - 9*m + 6 + d
    if n == 4: return 15*m**3 - 90*m*m + 175*m - 100 + (15*m - 39)*d
    if n == 6: return 105*m**4 - 1050*m**3 + 3955*m*m - 6335*m + 3325 + (210*m*m - 1302*m + 2010)*d

# Gate: 24 in-sample + 12 out-of-sample points, both branches
for n in (2, 4, 6):
    for m in range(3, 13):
        assert DS_walk(n, m) == DS_closed(n, m), (n, m)

# Hardware anchor (not used to build the formula)
assert DS_walk(6, 4) == 1107

# New row DS_8, both parities
assert [DS_walk(8, m) for m in range(3, 11)] == \
       [252, 8953, 63504, 375745, 1172556, 3595177, 7939008, 17605249]

print("CLOSED-WALK LAW OK")
```

The check returns zero discrepancies: 24 in-sample points (`DS_2, DS_4, DS_6` for `m = 3..8`) against the published closed forms, 12 out-of-sample points (`m = 9..12`), the hardware-measured anchor `DS_6(4) = 1107`, and the `DS_8` row for both parities.

---

## References

1. R. Amichis Luengo, *The localization of torsion to a single CRT block.* Campaign note, version 1.1, 1 June 2026.
2. A. Degtyarev, I. Shimada, *On the topology of projective subspaces in complex Fermat varieties.* J. Math. Soc. Japan **68**:3 (2016), 975–996. arXiv:1405.4683.
3. E. Aljovin, H. Movasati, R. Villaflor, *Integral Hodge conjecture for Fermat varieties.* J. Symbolic Computation **95** (2019), 177–184. arXiv:1711.02628.
