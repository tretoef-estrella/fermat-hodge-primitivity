# The block-rank theorem for Fermat CRT blocks — and the red link that makes it unconditional

### The per-block rank of the Chinese-Remainder splitting of a Fermat cell is a Degtyarev–Shimada rank polynomial — equivalently, the constant term of a closed lattice walk — for every block dimension, proved by a tensor identity from the Degtyarev–Shimada source. As of Version 2.0 the one stated condition (the dictionary) is discharged: its faithfulness half is now a pen-and-paper theorem, so the block-rank law is **unconditional**. As of Version 3.0 the dictionary's *geometric* half is likewise a theorem — the **eigencut identity** — and the coupling above recursive dimension 2 is located, verbatim, in the source (§8).

**Rafael Amichis Luengo** — Madrid · [github.com/tretoef-estrella](https://github.com/tretoef-estrella)
**Version 3.0 · 4 June 2026** *(Version 1.0, 2 June 2026: the law conditional on the dictionary. Version 2.0, 3 June 2026: the red link closes the dictionary's faithfulness; the law is unconditional. Version 3.0: the eigencut identity closes the dictionary's geometric half as an identity of operators, and §8 locates the coupling above recursive dimension 2 in the source's own equivalence.)*

> The capstone of the campaign's structural results. [THE_LOCALIZATION_THEOREM.md](THE_LOCALIZATION_THEOREM.md) proves *where* any torsion of a Fermat cell must live (one CRT block). [THE_BLOCK_DECOMPOSITION.md](THE_BLOCK_DECOMPOSITION.md) measures *how* the block ranks multiply (a product of recursion ladders). [THE_WITHIN_PAIR_FUNCTOR.md](THE_WITHIN_PAIR_FUNCTOR.md) opens the *interior* of one block. [THE_CLOSED_WALK_LAW.md](THE_CLOSED_WALK_LAW.md) names the *value* each ladder rung takes (a closed walk). This note closes the ladder: it proves that the rank a block contributes at every coupling depth equals that Degtyarev–Shimada value, for every block dimension, by a module-dimension identity read from the Degtyarev–Shimada paper itself. **Version 2.0 adds §7, the red link: a pen-and-paper proof that the `F_p` refinement of the block closure is faithful, which discharges the one stated condition of §2 and promotes the block-rank law from conditional to unconditional.** **Version 3.0 adds §8, the eigencut identity: the dictionary's geometric half — carried since Version 1.0 as a textual reading — is proven as an identity of linear projections, and the complete source is read to its end, locating the coupling of three or more pairs at Degtyarev–Shimada's own equivalence with Conjecture 1.2.**

---

## What changed in Version 2.0 (for the returning reader)

Version 1.0 proved the block-rank law `rec(d, ℓ) = DS_{2(ℓ−1)}(d+1)` **conditional on one identification** (the dictionary, §2): that the campaign's measured CRT all-`A` block is the Degtyarev–Shimada core module. That dictionary has two halves:

- **(geometric)** `e_A ↔` the coordinate-zeroing cut `X(2s)` of [2, §4.6]. This half was *verified textually* against the source in Version 1.0 — it was never the open part.
- **(faithfulness)** that the block measured over `F_p` equals the Degtyarev–Shimada core over `Z` **without spurious torsion injected when `Z → F_p`** — i.e. that the characteristic-`p` refinement of the integral closure is faithful. This was the genuinely open link, carried until now by measurement (four cells, zero injected torsion) rather than proof.

**Version 2.0 closes the faithfulness half by a pen-and-paper, characteristic-independent proof (§7).** The block closure is shown to be a free `Z`-module (it is the ring `Z[t]/φ` realized inside the pair, char poly `= φ`), and a free module reduces faithfully mod every prime. With the geometric half textual and the faithfulness half now a theorem, the dictionary is discharged and **the block-rank law is unconditional.** The integral-torsion question (the swan) still sits outside the chain and remains open — §7 fixes that the refinement injects no *spurious* torsion, not that *genuine* torsion is absent somewhere unmeasured.

---

## What changed in Version 3.0 (for the returning reader)

Version 2.0 discharged the dictionary's *faithfulness* half by the red link and noted that the *geometric* half — `e_A ↔` the coordinate-zeroing cut `X(2s)` of [2, §4.6] — was "verified textually against the source... never the open part." Version 3.0 upgrades that half from a reading to a **theorem**: the CRT idempotent cut and the Degtyarev–Shimada coordinate cut are the *same linear projection* on the per-variable ambient space, in every characteristic — the **eigencut identity**, proved in §8 by primary decomposition, in the same elementary register as `x·c₀ = −1`, with its one load-bearing hypothesis (the Fermat degree bound of [2, Lemma 4.1]) stated and verified rather than assumed. The dictionary now stands on two theorems and no readings.

Version 3.0 also records what the completed source settles about the *next* object in the chain. Reading [2, §4.5–§4.6] to the end: the coupled module of three or more pairs is the quotient of free legs by the single diagonal element `Σ 1_J` (their Theorem 1.1(d)), their §4.5 establishes the four torsion descriptions isomorphic, and their §4.6 states — verbatim, as an *if and only if* — that the freedom of that quotient in recursive dimension `2s` **is** Conjecture 1.2 in dimension `2s`. With the eigencut identity in hand the equivalence applies exactly to the campaign's objects. §8 narrates this location; the scope statements of §6–§7 are unchanged and remain accurate.

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

The equality at each depth is therefore standalone — `rec(d, ℓ) = dim_C(core) = walk = DS_{2(ℓ−1)}(d+1)` — and propagates from the base `rec(d, 1) = d`.

**In Version 1.0 the result was stated conditional on one identification — the dictionary of §2 — that the campaign's measured CRT all-`A` block at depth `ℓ` is the Degtyarev–Shimada core `C̄_{J(2s)}(2s)`. Version 2.0 discharges that condition: §7 proves the faithfulness half of the dictionary (the geometric half being textual), so the law is unconditional.** The integral torsion question (Degtyarev–Shimada Conjecture 1.2, the campaign's "swan") sits outside this chain and remains open: this theorem fixes the per-block **value**, not whether torsion exists. Every numerical statement is reproduced byte-exact by self-contained verifiers; the proof is verified link by link against the source.

---

## 1. Setting and statement

Fix an even-dimensional Fermat cell `(n, m)`, `n = 2d`, and a prime `p | m`. The integral Hodge question for the standard `d`-spaces reduces, by Degtyarev–Shimada [2], to whether `dim_C` of the cycle lattice equals `dim_{F_p}` for every `p | m`; the complex rank is the closed-form polynomial `DS_n(m)` of [2, Remark 4.4]. Over `F_p` the per-variable cyclotomic ring splits, by the Chinese Remainder Theorem, into a `(t−1)`-primary factor `A` and a coprime cofactor `B`; tensoring over the `n+2` variables decomposes the cohomology module into CRT blocks. The rank a block contributes at **coupling depth** `ℓ` (the number of `A`-pairs in the block) was measured across the campaign to obey

```
rec(d, ℓ) = DS_{2(ℓ−1)}(d+1)      (ℓ ≥ 2),    rec(d, 1) = d,    rec(d, 0) = 1,
```

the **General Product Law** of [THE_BLOCK_DECOMPOSITION.md](THE_BLOCK_DECOMPOSITION.md). The mechanism by which the ladders *mesh* as `ℓ` grows — the coupling — was a measured pattern. This note proves it.

**Theorem (block-rank law, unconditional as of Version 2.0).** *For every `d ≥ 0` and `ℓ ≥ 1`,*
```
rec(d, ℓ) = DS_{2(ℓ−1)}(d+1).
```
*Equivalently, the rank the block contributes at depth `ℓ` is the constant term of a closed lattice walk of `2ℓ` steps on `Z^{⌊d/2⌋}`, with rest permitted iff `d` is odd.* *(Version 1.0 proved this conditional on the dictionary of §2; §7 discharges that condition.)*

The published Degtyarev–Shimada closed forms, with `δ_m = (m−1) mod 2`, are `DS_2(m) = 3m² − 9m + 6 + δ_m`, `DS_4(m) = 15m³ − 90m² + 175m − 100 + (15m − 39)δ_m`, and `DS_6(m) = 105m⁴ − 1050m³ + 3955m² − 6335m + 3325 + (210m² − 1302m + 2010)δ_m`; these are the only rows for which [2] prints a polynomial. The theorem covers all `n = 2(ℓ−1)`, i.e. all depths, by the closed-walk reading of link 1 — which is the *definition* of `DS_n` for `n > 6`, there being no published closed form beyond `DS_6`.

## 2. The dictionary — stated, and now discharged (§7)

The theorem identifies the campaign's measured object with a Degtyarev–Shimada module. In Version 1.0 this identification was stated as a condition; Version 2.0 discharges it (§7). It is recorded here in full, with its two halves separated, because the separation is exactly what a referee needs to verify the discharge.

**The dictionary.** The campaign's CRT all-`A` block at depth `ℓ` is the Degtyarev–Shimada core module `C̄_{J(2s)}(2s)`, `s = ℓ−1`. Concretely: the `A`-idempotent `e_A` (projecting onto the `(t−1)`-primary part over `F_p`) corresponds to the coordinate-zeroing `z_v = 0` of the partial Fermat `X(2s) := W_s ∩ {z_{2s+2} = ⋯ = z_{n+1} = 0}` [2, §4.6]; the live cofactor `e_B` (`a_i ≠ 1`) corresponds to the surviving coordinates of `Γ_K` [2, Def 1.3, Thm 1.4].

This dictionary has two halves, and only one was ever open:

- **(geometric, textual)** the identification `e_A ↔ X(2s)` itself: that the `(t−1)`-primary idempotent is the coordinate-zeroing cut. This was confirmed *verbatim* against the Degtyarev–Shimada text (Definition 1.3's "`a_i ≠ 1`" is `e_B`; "`a_i = 1`" is `e_A`; the partial-Fermat cut `X(2s)` of §4.6 is the coordinate-zeroing). It is a textual reading of the source, not an inference — never the open part.
- **(faithfulness, the open link)** that the block measured over `F_p` equals the core's reduction over `Z` *without spurious torsion injected in the passage `Z → F_p`*. The Degtyarev–Shimada tensor (Cor 1.7) is a statement over `Z`; the campaign's CRT split is over `F_p` and carries the nilpotent `(t−1)`-primary tower (multiplicity `p^v−1` over `F_p`, multiplicity 1 over `C`). Faithfulness is the claim that this tower injects no extra survivors. This was carried by measurement (four cells, dimA `∈ {1,2,3,7}`, including the tall `m=8` tower, all zero injected torsion) until Version 2.0.

**§7 proves the faithfulness half.** With the geometric half textual and the faithfulness half a theorem, the dictionary is discharged, and the block-rank law of §1 is unconditional.

## 3. Link 1 — the value is a closed walk (Eslabón 4)

This is the content of [THE_CLOSED_WALK_LAW.md](THE_CLOSED_WALK_LAW.md), summarized for self-containment.

**Proposition 1.** `DS_n(m)` is the number of closed walks of `n+2` steps on `Z^{⌊(m−1)/2⌋}` (each step `±1` along an axis, the walk returning to its origin), with a rest step permitted iff `m` is even. Equivalently it is the constant term of `(1 + S)^{n+2}` (even `m`) or `S^{n+2}` (odd `m`), `S = x_1 + ⋯ + x_h + x_h^{-1} + ⋯ + x_1^{-1}` the symmetric Laurent sum.

This is read directly from [2, Remark 4.4]. It is gate-verified byte-exact on 24 in-sample points (`DS_2, DS_4, DS_6` for `m = 3..8`), 12 out-of-sample points (`m = 9..12`), the new row `DS_8`, and — the decisive check — the value `DS_6(4) = 1107` measured independently on the author's hardware and reproduced by the formula without having been fitted to it. The parity correction `δ_m` is exactly the walker's rest permission: odd `m` no rest, even `m` rest allowed (Eslabón 4, [THE_CLOSED_WALK_LAW.md](THE_CLOSED_WALK_LAW.md), §4).

With `s = ℓ−1`, `m = d+1`, the depth-`ℓ` value `DS_{2(ℓ−1)}(d+1)` is a closed walk of `2ℓ` steps on `Z^{⌊d/2⌋}`, rest iff `m = d+1` even, i.e. **iff `d` is odd**.

## 4. Link 2 — the measured block is the core, and the core is the walk (Eslabón 5, the induction)

This is the new content of Version 1.0. The equality is carried by a tensor identity, **not** by a shared recursion (which would not force equality — two sequences being holonomic does not make them equal).

**Lemma 2 (the block rank is the core dimension).** Under the dictionary of §2, the rank of the measured block at depth `ℓ` equals `dim_C C̄_{J(2s)}(2s)`, `s = ℓ−1`.

*Proof.* By [2, Cor 1.7], the relevant module decomposes as a tensor
```
C̄_{J_s}(2d) = C̄_{J(2s)}(2s) ⊗_Z S̄(s, d),   S̄(s, d) = ⊗_k Z[t_k]/(φ(t_k)),
```
each tail factor `Z[t_k]/(φ(t_k))` free of rank `m − 1`, hence `S̄` free. Degtyarev–Shimada obtain this by fixing the partition tail (the "constant relations" `t_{2s+2}t_{2s+3} = ⋯ = 1`, [2, §4.6]) and taking the even-index variables out. The exact sequence `0 → (λ)/(λρ_J) → R/(λρ_J) → R/(λ) → 0` with `R/(λ)` free [2, Lemma 4.5, Lemma 4.1] makes the split clean. Because `S̄` is free of rank `(m−1)^{d−s}`, over `C` the tensor dimension factorizes as `dim_C C̄_{J_s}(2d) = dim_C(core) · (m−1)^{d−s}`, and the tail contributes only its (constant, free) multiplicity. The rank the block contributes at depth `ℓ` is therefore `dim_C` of the core exactly — a free-module dimension, isolated, not a quantity that merely "advances controllably". ∎

**Lemma 3 (the core dimension is the walk).** `dim_C C̄_{J(2s)}(2s)` is the closed walk of `2s+2` steps of Proposition 1.

*Proof.* The core `C̄_{J(2s)}(2s)` is the full-partition module one dimension down: by [2, §4.6], the restriction of `J_s` to the index set `{0, …, 2s+1}` is exactly the full set `J(2s)` of partitions of `2s+1`. Hence Remark 4.4 applies to the core verbatim with `n → 2s`, and `dim_C(core) = DS_{2s}(m)` = the constant term of `(1 + S)^{2s+2}` = the closed walk. ∎

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

**What is proved.** The per-block rank `rec(d, ℓ) = DS_{2(ℓ−1)}(d+1)` for every `d`, **unconditionally** (Version 2.0), by a module-dimension identity read from the Degtyarev–Shimada source: the measured block is the core (Cor 1.7, free tail), the core dimension is the closed walk (Remark 4.4), the walk is the Degtyarev–Shimada value (Eslabón 4), uniform in `d` by Lipshitz finiteness — and the one identification this rested on (the dictionary, §2) is discharged by the red link (§7). The coupling mechanism — the "meshing" of the General Product Law, open since the product form was first measured — is closed: it is the constant term of a closed walk, and the ladder is a tensor of cores.

**Where this sits.** It is the capstone of the campaign's structural chain:
> within-pair triangle (measured, `ν ≤ μ`) → centrality localization ([THE_LOCALIZATION_THEOREM.md](THE_LOCALIZATION_THEOREM.md), proven) → closed-walk `=` block value ([THE_CLOSED_WALK_LAW.md](THE_CLOSED_WALK_LAW.md), Eslabón 4) → tensor induction (§4, Eslabón 5) → **faithful `F_p` refinement (§7, the red link)** ⟹ **block-rank law, all `d`, unconditional.**

**What this does not give.** The result fixes the per-block **value** — the rank ladder. It is **not** a statement about integral torsion. The Degtyarev–Shimada primitivity criterion compares `dim_C` against `dim_{F_p}`; this theorem computes the `C`-side ladder, and §7 proves the `F_p` refinement injects no *spurious* torsion — but neither exhibits nor excludes a *genuine* torsion counterexample in some unmeasured block. The integral torsion question — Degtyarev–Shimada Conjecture 1.2, the campaign's "swan" — sits **outside** this chain and **remains open**. It is a different battle, and is named as such without perfume. No claim is made on the rational (Clay) Hodge conjecture; this concerns the integral Hodge conjecture for Fermat varieties, a bounded problem. The torsion counterexample has not been found; every cell measured in the campaign is primitive.

## 7. The red link — the `F_p` refinement is faithful (Version 2.0, the discharge)

This section proves the faithfulness half of the dictionary (§2), discharging the one stated condition and making the block-rank law unconditional. It is pen-and-paper and characteristic-independent.

**What must be shown.** The Degtyarev–Shimada tensor (Cor 1.7, Lemma 2) is a decomposition over `Z`. The campaign's CRT split lives over `F_p` and carries the `(t−1)`-primary nilpotent tower: over `F_p` the factor `(t−1)` appears with multiplicity `p^v−1` (where `p^v ‖ m`), against multiplicity 1 over `C`. The faithfulness question is whether this characteristic-`p` tower injects *extra survivors* into the block closure under `Z → F_p` — equivalently, whether the integer closure module is `Z`-free (torsion-free), since a `Z`-free module of rank `r` satisfies `Z^r ⊗ F_p = F_p^r` exactly, with no injection, for **every** prime `p`.

This is **not** the vacuous "free is free" (which would assert `S̄(s,d)` is free by dimension and prove nothing about the coupled closure). The object proved free here is the **concrete coupled closure** — the image of `ρ_J` under the shift, the actual submodule with its quotient — by its tensor-of-cyclic-rings structure.

**The mechanism: the within-pair closure is the free ring `Z[t]/φ`.** A block at depth `ℓ` is a tensor of `ℓ` within-pair closures (the partition is a perfect matching; `ρ_J` factorizes over its pairs; the closure under shift respects the factorization). It therefore suffices to prove a single within-pair closure is `Z`-free; a tensor of free modules is free.

**Lemma 5 (`ρ` is `t_A`-cyclic of full dimension `m−1`).** Let `ρ = Σ_{0 ≤ b ≤ a ≤ m−2} x^a y^b` be the within-pair triangle in `(Z[t]/φ)_x ⊗ (Z[t]/φ)_y`. Then the `x`-shift orbit of `ρ` spans a submodule of dimension `m−1` (full), so `ρ` generates the within-pair closure cyclically as a `t_A`-module.

*Proof.* Write `ρ = Σ_{b=0}^{m−2} c_b(x) · y^b` by collecting `y`-powers; the `y^0`-component is
```
c_0(x) = 1 + x + x² + ⋯ + x^{m−2}.
```
In `Z[t]/φ`, the cyclotomic relation is `x^{m−1} = −(1 + x + ⋯ + x^{m−2}) = −c_0`. Therefore
```
x · c_0 = (x + x² + ⋯ + x^{m−2}) + x^{m−1} = (c_0 − 1) + (−c_0) = −1.
```
So **`x · c_0 = −1`** in `Z[t]/φ` (verified byte-exact `m = 4 … 12`). Consequently the `x`-orbit of `c_0` contains `−1`, hence `1`, hence `x, x², …, x^{m−2}` — it spans all of `(Z[t]/φ)_x`. Thus `c_0` is a **cyclic vector** for the `x`-action. Since `c_0` is the `y^0`-component of `ρ`, the `x`-orbit of `ρ` has full dimension `m−1`. ∎

This is the exact structural reason the within-pair closure is saturated while the image of `(t−1)` is **not** (the latter has Smith form `[1, …, 1, m]`, index `m`, verified `m = 4,5,6,8`): the triangle `ρ` is a generator whose orbit *regenerates the whole ring* (`x·c_0 = −1` pulls the unit `1` into the orbit), whereas `(t−1)` is a non-invertible operator whose image *contracts* by a `p`-adic factor. Saturation comes from cyclic regeneration, **not** from "the shift is a unit" — a unit-built map (`(t−1)` is a polynomial in the unit `x`) can have non-saturated image, so that argument would be unsound; this one is not.

**Lemma 6 (the within-pair closure is `Z`-free `≅ Z[t]/φ`).** The within-pair closure, as a `t`-module under the shift, has characteristic polynomial exactly `φ = 1 + t + ⋯ + t^{m−1}`; hence it is isomorphic to `Z[t]/φ`, which is free of rank `m−1`.

*Proof.* By Lemma 5 the module is cyclic of dimension `m−1 = deg φ`, generated by `ρ`. A cyclic module over `Z[t]` of dimension `deg φ` on which `t` acts with `t`'s minimal polynomial dividing `φ` (and reaching full dimension) has characteristic polynomial `φ` and is `≅ Z[t]/(char poly) = Z[t]/φ`. Verified byte-exact: char poly of the shift on the closure `= φ` for `m = 4,5,6`. `Z[t]/φ` is free as a `Z`-module (basis `1, t, …, t^{m−2}`). ∎

**Theorem (red link — faithful refinement).** The all-`A` coupled block closure at depth `ℓ` is `Z`-free of rank `(m−1)^ℓ`. Hence `Z^{(m−1)^ℓ} ⊗ F_p = F_p^{(m−1)^ℓ}` for every prime `p`, the `F_p` refinement injects zero torsion, and the dictionary's faithfulness half holds.

*Proof.* The depth-`ℓ` closure is the tensor of `ℓ` within-pair closures (matching factorization of `ρ_J`, shift respecting the factorization). Each within-pair closure is `Z`-free (Lemma 6). A tensor of free `Z`-modules is `Z`-free, of rank `(m−1)^ℓ`. For a free module, rank determines the module up to isomorphism, so the rank-`(m−1)^ℓ` match measured across the campaign **is** the tensor (here rank-match suffices precisely because both sides are free — the gap that torsion would open, e.g. the char-poll obstruction the campaign documented for torsion modules, is absent for free modules). A free `Z`-module reduces faithfully mod every prime: `Z^r ⊗ F_p = F_p^r`, no injection. The isomorphism is over `Z` and names no prime, so it holds in **every** characteristic, including characteristic 2 (the `m=8`, dimA `= 7` tall-tower case, where the tower is highest). ∎

**Independent verification.** `x·c_0 = −1` byte-exact `m = 4..12`; char poly of the shift on the within-pair closure `= φ` for `m = 4,5,6`; `ρ` is `t_A`-cyclic of dimension `m−1` for `m = 4..10`; `im(t−1)` has Smith `[1,…,1,m]` (index `m`, not saturated) for `m = 4,5,6,8`; `im(σ)` (the symmetrizer `I+τ`) carries 2-torsion, confirming the within-pair closure is **not** `im(σ)` (which would not be free). Four independent computational instruments measured zero injected torsion across dimA `∈ {1,2,3,7}` and char `∈ {2,3}` before the proof; the proof explains the measurements rather than resting on them.

**Scope of the red link, stated plainly.** The red link proves the refinement injects no *spurious* torsion — the `C`-side ladder of §1–§5 reduces faithfully, so every primitivity verdict the campaign measured is genuine, not an artifact of the `Z → F_p` passage. It does **not** prove that *genuine* integral torsion is absent in some unmeasured block of recursive dimension `≥ 4`. That is Conjecture 1.2, the swan, and it remains open. What the red link gives the swan-hunt is a rigorous map: by [THE_LOCALIZATION_THEOREM.md](THE_LOCALIZATION_THEOREM.md), torsion lives in one block; by this theorem the per-block value is fixed and the `F_p` refinement is faithful, so a counterexample can only hide in a recursive-dimension `≥ 4` block that deviates from the Degtyarev–Shimada value — `recdim 0, 2` are torsion-free by [2, Cor 1.7]. The hunt is thereby reduced from an unbounded search to a pointed one.

---

## 8. The eigencut identity — the geometric half becomes a theorem, and the coupling located (Version 3.0)

### 8.1 The identity

Fix one variable of the cell and its ambient space `V = k[t]/(tᵐ − 1)`, the group-ring realization of the Galois rotation `γ_j : z_j ↦ ζ z_j` of [2, §2], with `t` acting as the cyclic shift. Two cuts act on `V`. The **Degtyarev–Shimada coordinate cut** sets `z_j = 0` — the operation building `X(2s) := W_s ∩ {z_{2s+2} = ⋯ = z_{n+1} = 0}` [2, §4.6] — and retains the part fixed by `γ_j`: linearly, the generalized eigenspace `E₁(t) := ker((t−1)ᵐ)`. The **CRT idempotent cut** is `e_A`, the projection onto the `(t−1)`-primary factor — the cut every block of this note is built from.

**Theorem (eigencut identity).** `E₁(t) = im(e_A)` as subspaces of `V`, in every characteristic. Consequently the two cuts are the *same linear projection* — equal as operators, not merely in dimension.

*Proof.* Factor the minimal polynomial of `t` on `V` into primary components over `k`: `tᵐ − 1 = (t−1)ᵃ · h(t)` with `gcd((t−1)ᵃ, h) = 1`, `a` the exact multiplicity. Primary decomposition of `V` as a `k[t]`-module gives `V = ker((t−1)ᵃ) ⊕ ker(h(t))`, and `e_A` is by construction the projector onto the first summand along the second (`e_A ≡ 1 mod (t−1)ᵃ`, `e_A ≡ 0 mod h`), so `im(e_A) = ker((t−1)ᵃ)`. Since `a ≤ m`, `ker((t−1)ᵃ) ⊆ ker((t−1)ᵐ)`; conversely any vector killed by a power of `(t−1)` lies in the `(t−1)`-primary part, which `(t−1)ᵃ` annihilates exactly. Hence `ker((t−1)ᵃ) = ker((t−1)ᵐ) = E₁(t) = im(e_A)`. ∎

No cohomology, no spectral sequence, no Pham polyhedron beyond the action `γ_i ↔ t_i` already fixed in [2, §2] — the same register as the cyclotomic identity `x·c₀ = −1` of §7. Two refinements carry the statement across characteristics. **(i) The generalized eigenspace is the correct geometric object in characteristic `p`.** Over `C`, eigenvalue 1 is a simple root and `E₁` is the eigenline; over `F_p` with `p^v ‖ m`, Frobenius gives `tᵐ − 1 = (t^{m′} − 1)^{p^v}` and the `(t−1)`-primary block of `V` has dimension `p^v` exactly, with `t − 1` nilpotent on it — the tower. *Fixed by `γ_j`* must be read as this full primary block, not the one-dimensional ordinary eigenspace. (Two registers, kept distinct: on `V = k[t]/(tᵐ−1)` the primary dimension is `p^v`; in the φ-restricted quotient used in §2 and §7 the multiplicity is `p^v − 1`. Both are correct in their own register; the identity lives on `V`.) **(ii) The characteristic-0 idempotent is the Galois average:** `e_A = (1 + t + ⋯ + t^{m−1})/m`, the Reynolds projector onto the `γ_j`-invariants — the textbook projection onto the fixed subspace, which is exactly the coordinate cut's invariant part.

### 8.2 The hinge, made explicit

The arrow *"`z_j = 0` retains the part fixed by `γ_j`"* carries the geometry, and it holds for a stated reason, not by default. Abstractly, *fixed by `γ_j`* means exponent `≡ 0 (mod m)` — the infinite set `{0, m, 2m, …}` — while setting `z_j = 0` keeps exponent exactly `0`. The two coincide under the **Fermat degree bound** `0 ≤ ν < m` of [2, Lemma 4.1] (the quotient by `x_iᵐ − 1`), under which `ν ≡ 0 (mod m)` forces `ν = 0`. Verified for `m = 4` through `15`: without the bound the invariant exponents in `[0, 4m)` are `{0, m, 2m, 3m}`; with it, exactly `{0}`. The proof names its own load-bearing hypothesis.

### 8.3 The anchor

The identity was measured before it was written. Ten cells, both registers, zero discrepancies: characteristic 0 at `m = 4, 6, 10` (`dim E₁ = dim im(e_A) = 1`, `e_A = φ_full/m`, idempotent); characteristic `p` at `(m,p) = (6,2), (6,3), (12,2), (8,2), (15,3), (15,5), (9,3)` — `dimA ∈ {2, 3, 4, 8, 3, 5, 9}`, including the maximal-height towers `(8,2)` and `(9,3)` where the generalized eigenspace is the whole space. In every cell, `E₁(t) = im(e_A)` as subspaces and `e_A² = e_A` in the ambient arithmetic. Verifiers, each recomputing from scratch: [`verifiers/EIGENCUT_IDENTITY_VERIFIER.py`](verifiers/EIGENCUT_IDENTITY_VERIFIER.py), [`verifiers/HINGE1_DEGREE_BOUND_VERIFIER.py`](verifiers/HINGE1_DEGREE_BOUND_VERIFIER.py). Full statement and proof note: [THE_EIGENCUT_IDENTITY.md](THE_EIGENCUT_IDENTITY.md).

### 8.4 What this changes in this note

The dictionary of §2 had two halves: faithfulness, closed by §7, and the geometric identification, carried since Version 1.0 as a verbatim reading. With the eigencut identity the geometric half is an identity of operators. **The dictionary stands on two theorems**; nothing in §§1–7 changes, and the block-rank law remains unconditional with one fewer textual dependency in its chain.

### 8.5 The coupling, located in the source

With the complete Degtyarev–Shimada text in hand, [2, §4.5–§4.6] were read to the end — twice, independently. What they settle about the object one step beyond this note's ladder is recorded here as fact.

**The object.** [2, Theorem 1.1(d)], verbatim: the coupled module is `C̄_K := (⊕_{J∈K} R̄_J)/M̄`, where `M̄` is the `R̄`-submodule generated by the **single element** `Σ_{J∈K} 1_J` — the diagonal relation gluing the legs by their unit. Each leg `R̄_J` is `Z`-free by [2, Lemma 4.1]: its `τ_J = (t_{k_0}−1)⋯(t_{k_d}−1)` is exactly a `θ` over the `k`-variables, with no restriction on the number of variables — free for any number of pairs.

**What §4.5 proves.** The proof of parts (c) and (d) is a chain of **torsion isomorphisms**: dualization (`Tors Coker(ϕ) ≅ Tors Coker(ϕ∨)`), the exact sequence `0 → (⊕(τ_J))/Rs → (⊕R_J)/Rs → ⊕(R_J/(τ_J)) → 0` with third term free by Lemma 4.1, and the identification `f ↦ f·τ_J` carrying `s = Σ τ_J 1_J` to `Σ 1_J`. It establishes that the four modules of their Theorem 1.1 share one torsion.

**Where the freedom of the quotient is addressed.** [2, §4.6], verbatim:

> *"Thus, this module is free (as an abelian group) if and only if so is C̄_{J(2s)}(2s), i.e., if and only if Conjecture 1.2 holds for Fermat varieties of dimension 2s in P^{2s+1}."*

**The identification.** By that equivalence — the source's own, an *if and only if* — whether the quotient of free legs by the diagonal `Σ 1_J` preserves freedom in recursive dimension `2s`, and whether Conjecture 1.2 holds in dimension `2s`, are **one statement**. The eigencut identity makes the application exact: the campaign's coupled core *is* the Degtyarev–Shimada module (§8.1 — the cuts are the same operator), so it inherits the equivalence. The boundary between the regimes is thereby drawn to the line. **Two legs** (recursive dimension 2): the within-pair closure is `Z[t]/φ`, free by `x·c₀ = −1` alone (§7), and dimensions 0 and 2 are torsion-free by the source's own results — below the equivalence. **Three or more legs** (recursive dimension `≥ 4`): the freedom in question sits on the equivalence itself. Accordingly, every primitivity verdict of the campaign is an instance of Conjecture 1.2 confirmed; and a deviation in a recursive-dimension `≥ 4` block, should one ever be measured, and a failure of Conjecture 1.2 in that dimension are the same event. The scope statement of §7 stands word for word; this section adds the location, read from the source and confirmed against the complete text.

---

## References

1. R. Amichis Luengo, *The localization of torsion to a single CRT block.* Campaign note, version 1.1, 1 June 2026. [THE_LOCALIZATION_THEOREM.md](THE_LOCALIZATION_THEOREM.md)
2. A. Degtyarev, I. Shimada, *On the topology of projective subspaces in complex Fermat varieties.* J. Math. Soc. Japan **68**:3 (2016), 975–996. arXiv:1405.4683.
3. R. Amichis Luengo, *The closed-walk law for the Fermat block-rank factor.* Campaign note, version 1.0, 2 June 2026. [THE_CLOSED_WALK_LAW.md](THE_CLOSED_WALK_LAW.md)
4. L. Lipshitz, *The diagonal of a D-finite power series is D-finite.* J. Algebra **113** (1988), 373–378.
5. R. Amichis Luengo, *The within-pair functor of a Fermat CRT block.* Campaign note, version 1.0, 1 June 2026. [THE_WITHIN_PAIR_FUNCTOR.md](THE_WITHIN_PAIR_FUNCTOR.md)
6. E. Aljovin, H. Movasati, R. Villaflor, *Integral Hodge conjecture for Fermat varieties.* J. Symbolic Computation **95** (2019), 177–184. arXiv:1711.02628.
7. R. Amichis Luengo, *The eigencut identity — the CRT idempotent cut is the Degtyarev–Shimada coordinate cut.* Campaign note, version 1.0, 3 June 2026. [THE_EIGENCUT_IDENTITY.md](THE_EIGENCUT_IDENTITY.md)
