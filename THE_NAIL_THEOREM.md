# The block-rank theorem for Fermat CRT blocks

### The per-block rank of the Chinese-Remainder splitting of a Fermat cell is a Degtyarev–Shimada rank polynomial — equivalently, the constant term of a closed lattice walk — for every block dimension, proved by a tensor identity from the Degtyarev–Shimada source

**Rafael Amichis Luengo** — Madrid · [github.com/tretoef-estrella](https://github.com/tretoef-estrella)
**Version 1.0 · 2 June 2026**

> The capstone of the campaign's structural results. [THE_LOCALIZATION_THEOREM.md](THE_LOCALIZATION_THEOREM.md) proves *where* any torsion of a Fermat cell must live (one CRT block). [THE_BLOCK_DECOMPOSITION.md](THE_BLOCK_DECOMPOSITION.md) measures *how* the block ranks multiply (a product of recursion ladders). [THE_WITHIN_PAIR_FUNCTOR.md](THE_WITHIN_PAIR_FUNCTOR.md) opens the *interior* of one block. [THE_CLOSED_WALK_LAW.md](THE_CLOSED_WALK_LAW.md) names the *value* each ladder rung takes (a closed walk). **This note closes the ladder: it proves that the rank a block contributes at every coupling depth equals that Degtyarev–Shimada value, for every block dimension, by a module-dimension identity read from the Degtyarev–Shimada paper itself.** With it, the block-rank structure of the splitting is a theorem rather than a measured pattern.

---

## Abstract

Let `(n, m)` be an even-dimensional Fermat cell and `p | m` a prime. Over `F_p` the cyclotomic quotient splits, by the Chinese Remainder Theorem, into blocks; the rank a block contributes is governed by the recursion

```
rec(d, 0) = 1,    rec(d, 1) = d,    rec(d, ℓ) = DS_{2(ℓ−1)}(d+1)   for ℓ ≥ 2,
```

measured byte-exact across the campaign (the General Product Law, [THE_BLOCK_DECOMPOSITION.md](THE_BLOCK_DECOMPOSITION.md)), where `DS_n(m)` is the Degtyarev–Shimada complex rank polynomial [2, Remark 4.4]. This note proves the identity `rec(d, ℓ) = DS_{2(ℓ−1)}(d+1)` holds **for every `d`**, not only the cases measured. The proof is a chain of module-dimension identities read from the Degtyarev–Shimada source, in three links:

1. **The value is a closed walk.** `DS_{2s}(m)` is the constant term of a closed lattice walk of `2s+2` steps on `Z^{⌊(m−1)/2⌋}` — directional steps with rest permitted iff `m` is even, the rest permission being exactly the published parity correction `δ_m`. Proved and gate-verified byte-exact in [THE_CLOSED_WALK_LAW.md](THE_CLOSED_WALK_LAW.md) (Eslabón 4).

2. **The measured block is a Degtyarev–Shimada core module.** By the Degtyarev–Shimada tensor decomposition `C̄_{J_s}(2d) = C̄_{J(2s)}(2s) ⊗_Z S̄(s,d)` [2, Cor 1.7], with the tail `S̄(s,d)` a free `Z`-module, the rank of the block at depth `ℓ = s+1` equals `dim_C` of the core `C̄_{J(2s)}(2s)` exactly — a free-module dimension, isolated by the clean tensor split. And `dim_C` of that core is the closed walk of link 1, by Remark 4.4 applied one dimension down (Eslabón 5).

3. **The step is uniform.** The depth step `ℓ−1 → ℓ` adds two lattice coordinates and is a finite-order holonomic operator for every block dimension (Lipshitz 1988 [4]); this is the structural reason the induction does not blow up as the lattice dimension grows, and it carries the *uniformity* in `d`, not the equality.

The equality at each depth is therefore standalone — `rec(d, ℓ) = dim_C(\text{core}) = \text{walk} = DS_{2(ℓ−1)}(d+1)` — and propagates from the base `rec(d, 1) = d`. **The result is conditional on one identification, named explicitly: that the campaign's measured CRT all-`A` block at depth `ℓ` is the Degtyarev–Shimada core `C̄_{J(2s)}(2s)`** (the dictionary `e_A ↔` coordinate-zeroing, established earlier in the campaign and confirmed verbatim against [2, Def 1.3, Thm 1.4, §4.6]). The integral torsion question (Degtyarev–Shimada Conjecture 1.2, the campaign's "swan") sits outside this chain and remains open: this theorem fixes the per-block **value**, not whether torsion exists. Every numerical statement is reproduced byte-exact by self-contained verifiers; the proof is verified link by link against the source.

---

## 1. Setting and statement

Fix an even-dimensional Fermat cell `(n, m)`, `n = 2d`, and a prime `p | m`. The integral Hodge question for the standard `d`-spaces reduces, by Degtyarev–Shimada [2], to whether `dim_C` of the cycle lattice equals `dim_{F_p}` for every `p | m`; the complex rank is the closed-form polynomial `DS_n(m)` of [2, Remark 4.4]. Over `F_p` the per-variable cyclotomic ring splits, by the Chinese Remainder Theorem, into a `(t−1)`-primary factor `A` and a coprime cofactor `B`; tensoring over the `n+2` variables decomposes the cohomology module into CRT blocks. The rank a block contributes at **coupling depth** `ℓ` (the number of `A`-pairs in the block) was measured across the campaign to obey

```
rec(d, ℓ) = DS_{2(ℓ−1)}(d+1)      (ℓ ≥ 2),    rec(d, 1) = d,    rec(d, 0) = 1,
```

the **General Product Law** of [THE_BLOCK_DECOMPOSITION.md](THE_BLOCK_DECOMPOSITION.md). The mechanism by which the ladders *mesh* as `ℓ` grows — the coupling — was a measured pattern. This note proves it.

**Theorem (block-rank law).** *For every `d ≥ 0` and `ℓ ≥ 1`, conditional on the dictionary of §2,*
```
rec(d, ℓ) = DS_{2(ℓ−1)}(d+1).
```
*Equivalently, the rank the block contributes at depth `ℓ` is the constant term of a closed lattice walk of `2ℓ` steps on `Z^{⌊d/2⌋}`, with rest permitted iff `d` is odd.*

The published Degtyarev–Shimada closed forms, with `δ_m = (m−1) mod 2`, are `DS_2(m) = 3m² − 9m + 6 + δ_m`, `DS_4(m) = 15m³ − 90m² + 175m − 100 + (15m − 39)δ_m`, and `DS_6(m) = 105m⁴ − 1050m³ + 3955m² − 6335m + 3325 + (210m² − 1302m + 2010)δ_m`; these are the only rows for which [2] prints a polynomial. The theorem covers all `n = 2(ℓ−1)`, i.e. all depths, by the closed-walk reading of link 1 — which is the *definition* of `DS_n` for `n > 6`, there being no published closed form beyond `DS_6`.

## 2. The one stated condition: the dictionary

The theorem identifies the campaign's measured object with a Degtyarev–Shimada module, and this identification is the single place the campaign's own construction meets the published one. It is stated as a condition, not hidden.

**The dictionary.** The campaign's CRT all-`A` block at depth `ℓ` is the Degtyarev–Shimada core module `C̄_{J(2s)}(2s)`, `s = ℓ−1`. Concretely: the `A`-idempotent `e_A` (projecting onto the `(t−1)`-primary part over `F_p`) corresponds to the coordinate-zeroing `z_v = 0` of the partial Fermat `X(2s) := W_s ∩ {z_{2s+2} = ⋯ = z_{n+1} = 0}` [2, §4.6]; the live cofactor `e_B` (`a_i ≠ 1`) corresponds to the surviving coordinates of `Γ_K` [2, Def 1.3, Thm 1.4].

This was established earlier in the campaign and confirmed verbatim against the Degtyarev–Shimada text (Definition 1.3's "`a_i ≠ 1`" is `e_B`; "`a_i = 1`" is `e_A`; the partial-Fermat cut `X(2s)` of §4.6 is the coordinate-zeroing). The theorem holds **given** this dictionary. A referee will examine exactly this link; the paper names it rather than assuming it.

## 3. Link 1 — the value is a closed walk (Eslabón 4)

This is the content of [THE_CLOSED_WALK_LAW.md](THE_CLOSED_WALK_LAW.md), summarized for self-containment.

**Proposition 1.** `DS_n(m)` is the number of closed walks of `n+2` steps on `Z^{⌊(m−1)/2⌋}` (each step `±1` along an axis, the walk returning to its origin), with a rest step permitted iff `m` is even. Equivalently it is the constant term of `(1 + S)^{n+2}` (even `m`) or `S^{n+2}` (odd `m`), `S = x_1 + ⋯ + x_h + x_h^{-1} + ⋯ + x_1^{-1}` the symmetric Laurent sum.

This is read directly from [2, Remark 4.4]. It is gate-verified byte-exact on 24 in-sample points (`DS_2, DS_4, DS_6` for `m = 3..8`), 12 out-of-sample points (`m = 9..12`), the new row `DS_8`, and — the decisive check — the value `DS_6(4) = 1107` measured independently on the author's hardware and reproduced by the formula without having been fitted to it. The parity correction `δ_m` is exactly the walker's rest permission: odd `m` no rest, even `m` rest allowed (Eslabón 4, [THE_CLOSED_WALK_LAW.md](THE_CLOSED_WALK_LAW.md), §4).

With `s = ℓ−1`, `m = d+1`, the depth-`ℓ` value `DS_{2(ℓ−1)}(d+1)` is a closed walk of `2ℓ` steps on `Z^{⌊d/2⌋}`, rest iff `m = d+1` even, i.e. **iff `d` is odd**.

## 4. Link 2 — the measured block is the core, and the core is the walk (Eslabón 5, the induction)

This is the new content. The equality is carried by a tensor identity, **not** by a shared recursion (which would not force equality — two sequences being holonomic does not make them equal).

**Lemma 2 (the block rank is the core dimension).** Under the dictionary of §2, the rank of the measured block at depth `ℓ` equals `dim_C C̄_{J(2s)}(2s)`, `s = ℓ−1`.

*Proof.* By [2, Cor 1.7], the relevant module decomposes as a tensor
```
C̄_{J_s}(2d) = C̄_{J(2s)}(2s) ⊗_Z S̄(s, d),   S̄(s, d) = ⊗_k Z[t_k]/(φ(t_k)),
```
each tail factor `Z[t_k]/(φ(t_k))` free of rank `m − 1`, hence `S̄` free. Degtyarev–Shimada obtain this by fixing the partition tail (the "constant relations" `t_{2s+2}t_{2s+3} = ⋯ = 1`, [2, §4.6]) and taking the even-index variables out. The exact sequence `0 → (λ)/(λρ_J) → R/(λρ_J) → R/(λ) → 0` with `R/(λ)` free [2, Lemma 4.5, Lemma 4.1] makes the split clean. Because `S̄` is free of rank `(m−1)^{d−s}`, over `C` the tensor dimension factorizes as `dim_C C̄_{J_s}(2d) = dim_C(\text{core}) · (m−1)^{d−s}`, and the tail contributes only its (constant, free) multiplicity. The rank the block contributes at depth `ℓ` is therefore `dim_C` of the core exactly — a free-module dimension, isolated, not a quantity that merely "advances controllably". ∎

**Lemma 3 (the core dimension is the walk).** `dim_C C̄_{J(2s)}(2s)` is the closed walk of `2s+2` steps of Proposition 1.

*Proof.* The core `C̄_{J(2s)}(2s)` is the full-partition module one dimension down: by [2, §4.6], the restriction of `J_s` to the index set `{0, …, 2s+1}` is exactly the full set `J(2s)` of partitions of `2s+1`. Hence Remark 4.4 applies to the core verbatim with `n → 2s`, and `dim_C(\text{core}) = DS_{2s}(m)` = the constant term of `(1 + S)^{2s+2}` = the closed walk. ∎

**Lemma 4 (the step is uniform in `d`).** The depth step `ℓ−1 → ℓ` adds two lattice coordinates (Cor 1.7's tail growth, the "`+2` steps") and is a finite-order holonomic operator on the walk count for every lattice dimension `h`.

*Proof.* By [4, Lipshitz 1988], the constant term of the `N`-th power of a fixed Laurent polynomial is P-recursive (holonomic) in `N`. The walk counts `cw(h, N)` and `cwr(h, N)` are exactly such constant terms with `S` the fixed symmetric Laurent polynomial of `Z^h`; hence for each fixed `h` the sequence in `N` satisfies a finite-order linear recursion with polynomial coefficients. The depth step advances `N → N+2`. The order is `1` for `h = 1` (no rest), `2` for `h = 1` (rest) and `h = 2`, and grows with `h`, but Lipshitz guarantees finiteness for every `h` — the uniformity of the step. This carries the *uniformity in `d`*; it does **not** carry the equality, which is Lemmas 2–3. ∎

**Proof of the Theorem.** Fix `d, ℓ`. By Lemma 2, `rec(d, ℓ) = dim_C C̄_{J(2s)}(2s)`, `s = ℓ−1`. By Lemma 3, `dim_C C̄_{J(2s)}(2s) = ` the closed walk of `2ℓ` steps on `Z^{⌊d/2⌋}`. By Proposition 1 (link 1), that walk is `DS_{2(ℓ−1)}(d+1)`. Hence `rec(d, ℓ) = DS_{2(ℓ−1)}(d+1)`, standalone at each depth. The base `rec(d, 1) = d` [Eslabón 1: the single-`B`-leg block rank is `dim_B`, verified byte-exact for `d = 3, 4, 8`] anchors the ladder; Lemma 4 makes the depth step a finite uniform holonomic operator, so the identity propagates to all depths. ∎

The equality rests on the tensor (Cor 1.7) and the generating count (Remark 4.4) — module-dimension identities from the source — with Lipshitz supplying only the finiteness of the step. No appeal to "two sequences share a recursion" is made or needed.

## 5. Verification

Every numeric instance is recomputed from scratch (see [chuchipachielconquistador.py](verifiers/chuchipachielconquistador.py) for link 1 and the block-rank ladders below).

| `d` | derived ladder (base + the law) | target (measured) | status |
|---|---|---|---|
| 2 | `rec(2,2)=6, rec(2,3)=20, rec(2,4)=70` | 6, 20, 70 | byte-exact ✓ |
| 3 | `rec(3,2)=19, rec(3,3)=141, rec(3,4)=1107` | 19, 141, 1107 | byte-exact ✓ (1107 = hardware-measured) |
| 4 | `rec(4,3)=400, rec(4,4)=4900` | 400, 4900 | byte-exact ✓ |
| 6 | `rec(6,4)=44730` | `DS_6(7)=44730` | byte-exact ✓ (dim-3 lattice) |
| 7 | `rec(7,4)=103279` | `DS_6(8)=103279` | byte-exact ✓ (dim-3 lattice) |

The `d = 6, 7` rows verify the law beyond the one- and two-dimensional lattice cases, in dimension three, against the published `DS_6`. Beyond the published closed forms (e.g. `rec(6,5) = 1172556`) the closed walk *is* the definition (link 1), there being no published `DS_8` polynomial.

```python
from math import comb
from collections import defaultdict

def cw(k, N):                                       # closed walk, no rest
    if k == 0: return 1 if N == 0 else 0
    cur = {(0,) * k: 1}
    for _ in range(N):
        nxt = defaultdict(int)
        for v, c in cur.items():
            for i in range(k):
                for s in (1, -1):
                    w = list(v); w[i] += s; nxt[tuple(w)] += c
        cur = nxt
    return cur[(0,) * k]

def cwr(k, N):                                      # rest permitted
    return sum(comb(N, j) * cw(k, j) for j in range(N + 1))

def rec(d, l):                                      # the block-rank law
    h = d // 2                                      # lattice dimension
    return cwr(h, 2 * l) if (d + 1) % 2 == 0 else cw(h, 2 * l)

def DS_closed(n, m):
    e = (m - 1) % 2
    if n == 2: return 3*m*m - 9*m + 6 + e
    if n == 4: return 15*m**3 - 90*m*m + 175*m - 100 + (15*m - 39)*e
    if n == 6: return 105*m**4 - 1050*m**3 + 3955*m*m - 6335*m + 3325 + (210*m*m - 1302*m + 2010)*e

# the law against the published closed form, all d=2..7, depths l=2..4
for d in range(2, 8):
    for l in range(2, 5):
        n = 2 * (l - 1)
        if n in (2, 4, 6):
            assert rec(d, l) == DS_closed(n, d + 1), (d, l)
assert rec(3, 4) == 1107            # the hardware-measured anchor
print("BLOCK-RANK LAW OK")
```

The check returns zero discrepancies across `d = 2..7`, depths `ℓ = 2..4`, including the hardware-measured `rec(3,4) = 1107`.

## 6. Significance and scope

**What is proved.** The per-block rank `rec(d, ℓ) = DS_{2(ℓ−1)}(d+1)` for every `d`, conditional on the dictionary of §2, by a module-dimension identity read from the Degtyarev–Shimada source: the measured block is the core (Cor 1.7, free tail), the core dimension is the closed walk (Remark 4.4), the walk is the Degtyarev–Shimada value (Eslabón 4), uniform in `d` by Lipshitz finiteness. The coupling mechanism — the "meshing" of the General Product Law, open since the product form was first measured — is closed: it is the constant term of a closed walk, and the ladder is a tensor of cores.

**Where this sits.** It is the capstone of the campaign's structural chain:
> within-pair triangle (measured, `ν ≤ μ`) → centrality localization ([THE_LOCALIZATION_THEOREM.md](THE_LOCALIZATION_THEOREM.md), proven) → closed-walk `=` block value ([THE_CLOSED_WALK_LAW.md](THE_CLOSED_WALK_LAW.md), Eslabón 4) → tensor induction (this note, Eslabón 5) ⟹ **block-rank law, all `d`.**

**What this does not give.** The result fixes the per-block **value** — the rank ladder. It is **not** a statement about integral torsion. The Degtyarev–Shimada primitivity criterion compares `dim_C` against `dim_{F_p}`; this theorem computes the `C`-side ladder, not the `F_p`-versus-`C` comparison that would exhibit or exclude a counterexample. The integral torsion question — Degtyarev–Shimada Conjecture 1.2, the campaign's "swan" — sits **outside** this chain and **remains open**. It is a different battle, and is named as such without perfume. No claim is made on the rational (Clay) Hodge conjecture; this concerns the integral Hodge conjecture for Fermat varieties, a bounded problem. The torsion counterexample has not been found; every cell measured in the campaign is primitive.

**The stated condition, once more.** The theorem is conditional on the dictionary (§2): the measured CRT block is the Degtyarev–Shimada core. This is sealed in the campaign findings and confirmed verbatim against the source, but it is the campaign's own identification, and a referee should weigh it as such.

---

## References

1. R. Amichis Luengo, *The localization of torsion to a single CRT block.* Campaign note, version 1.1, 1 June 2026. [THE_LOCALIZATION_THEOREM.md](THE_LOCALIZATION_THEOREM.md)
2. A. Degtyarev, I. Shimada, *On the topology of projective subspaces in complex Fermat varieties.* J. Math. Soc. Japan **68**:3 (2016), 975–996. arXiv:1405.4683.
3. R. Amichis Luengo, *The closed-walk law for the Fermat block-rank factor.* Campaign note, version 1.0, 2 June 2026. [THE_CLOSED_WALK_LAW.md](THE_CLOSED_WALK_LAW.md)
4. L. Lipshitz, *The diagonal of a D-finite power series is D-finite.* J. Algebra **113** (1988), 373–378.
5. R. Amichis Luengo, *The within-pair functor of a Fermat CRT block.* Campaign note, version 1.0, 1 June 2026. [THE_WITHIN_PAIR_FUNCTOR.md](THE_WITHIN_PAIR_FUNCTOR.md)
6. E. Aljovin, H. Movasati, R. Villaflor, *Integral Hodge conjecture for Fermat varieties.* J. Symbolic Computation **95** (2019), 177–184. arXiv:1711.02628.
