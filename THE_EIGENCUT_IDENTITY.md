# The eigencut identity — the CRT idempotent cut is the Degtyarev–Shimada coordinate cut

### A pen-and-paper proof that the Chinese-Remainder idempotent projection `e_A` and the Degtyarev–Shimada coordinate-zeroing cut `z_j = 0` are the *same linear projection* on the per-variable ambient space — the geometric half of Link A — anchored byte-exact across ten cells in both characteristics

**Rafael Amichis Luengo** — Madrid · [github.com/tretoef-estrella](https://github.com/tretoef-estrella)
**Version 1.0 · 3 June 2026**

> Companion to [THE_NAIL_THEOREM.md](THE_NAIL_THEOREM.md) and [THE_BLOCK_DECOMPOSITION.md](THE_BLOCK_DECOMPOSITION.md). The Nail proves the block-rank law `rec(d,ℓ) = DS_{2(ℓ−1)}(d+1)` is unconditional *given* one identification — the dictionary of §2 there — whose geometric half (`e_A ↔` the coordinate-zeroing cut `X(2s)`) was carried as a textual reading, never proved as an identity of operators. This note proves that geometric half: the CRT idempotent cut and the Degtyarev–Shimada coordinate cut are not merely the same dimension count, they are the **same projection on the same ambient space**. It is the handle the campaign's standing residual (Link A) turned on — and it falls to linear algebra, in the register of `x·c₀ = −1`, not to the cohomology of [2, §4].

---

## What this closes, in one paragraph

Degtyarev–Shimada build their recursion factor geometrically: a sub-Fermat `X(2s) := W_s ∩ {z_{2s+2} = ⋯ = z_{n+1} = 0}` obtained by **setting coordinates to zero** [2, §4.6]. The campaign's block-rank law instead splits the cohomology by a **Chinese-Remainder idempotent** `e_A` projecting onto the `(t−1)`-primary factor. The two constructions return the same numbers (e.g. `(4,6)c2` all-`B` `= 400 = DS_4(5)`, grade `m−1`), but "same number" is not "same object", and the residual was exactly to show they coincide as objects. This note shows they do, via the Galois action: setting `z_j = 0` keeps the part **fixed by `γ_j`** (the eigenvalue-1 part of `t_j`); `e_A` projects onto the **`(t−1)`-primary** part; and these two subspaces are **equal**, proved below and anchored byte-exact in ten cells. The geometric half of Link A is therefore a theorem. Link B (that the iterated cut realizes the full sub-Fermat *as a variety*, and Corollary 1.7 transfers) is **not** closed here; it is stated precisely in §5. The swan (Conjecture 1.2) is untouched.

---

## 1. Setting and the two cuts

Fix an even-dimensional Fermat cell `(n, m)`, `n = 2d`, in `P^{n+1}` with coordinates `z_0, …, z_{n+1}`. Degtyarev–Shimada [2, §2] present `X` as a Galois covering `π : X → Π` with group `G = (Z/m)^{n+1}`, the generator `γ_i` acting by

```
γ_i : z_i ↦ ζ z_i,    ζ = e^{2πi/m},
```

and identify `γ_i` with the ring variable `t_i` (so `R = Z[G]`, `γ_i ↔ t_i`). On a single variable the relevant ambient space is the group-ring quotient `V = k[t]/(t^m − 1)` over the coefficient field `k` (`k = C` over the rationals, `k = F_p` for the prime-field reduction), with `t` acting as the cyclic shift — the linear realization of `γ`.

There are two cuts on `V`.

**The Degtyarev–Shimada coordinate cut.** Setting `z_j = 0` (the operation defining `X(2s)` in [2, §4.6]) retains, on the `j`-th variable, the part **invariant under `γ_j`** — the monomials the rotation `z_j ↦ ζ z_j` does not move. Linearly: the (generalized) eigenspace of `t` at eigenvalue `1`,

```
E₁(t) := { v ∈ V : (t − 1)^N v = 0 for some N }   = ker((t − 1)^m).
```

Over `C` this is the simple eigenline (eigenvalue `1` is a simple root of `t^m − 1`); over `F_p` it is the **`(t−1)`-primary block**, on which `t − 1` is nilpotent — the tower.

**The CRT idempotent cut.** Over `k` the polynomial `t^m − 1` factors with the `(t−1)`-primary part `A` and a coprime cofactor `B`, and the Chinese Remainder Theorem gives `k[t]/(t^m−1) ≅ A × B` with central idempotents `e_A, e_B`. The cut is the projection

```
e_A : V ↠ im(e_A) = the (t−1)-primary factor A.
```

**The claim (geometric half of Link A).** These are the *same* projection:

```
E₁(t) = im(e_A)    as subspaces of V,   in every characteristic.
```

## 2. The proof

**Lemma 1 (the two subspaces coincide).** Let `V = k[t]/(t^m − 1)`, `t` the shift. Then the generalized eigenspace `E₁(t) = ker((t−1)^m)` equals `im(e_A)`, the image of the CRT idempotent onto the `(t−1)`-primary factor.

*Proof.* Factor the minimal polynomial of `t` on `V`, which is `t^m − 1`, into its primary components over `k`:

```
t^m − 1 = (t − 1)^a · h(t),    gcd((t−1)^a, h) = 1,
```

where `(t−1)^a` is the full `(t−1)`-primary part (`a` its multiplicity in `t^m − 1`) and `h` collects the coprime cofactor. By the primary decomposition of a module over a PID applied to `V` as a `k[t]`-module (equivalently, the Chinese Remainder Theorem for the coprime factors `(t−1)^a` and `h`),

```
V = ker((t−1)^a) ⊕ ker(h(t)),
```

and the CRT idempotent `e_A` is, by construction, the projection onto the first summand along the second: `e_A ≡ 1 mod (t−1)^a`, `e_A ≡ 0 mod h`. Hence `im(e_A) = ker((t−1)^a)`.

It remains that `ker((t−1)^a) = ker((t−1)^m) = E₁(t)`. Since `(t−1)^a` divides `(t−1)^m` (as `a ≤ m`), `ker((t−1)^a) ⊆ ker((t−1)^m)`. Conversely the `(t−1)`-primary part of `V` is annihilated by `(t−1)^a` exactly (that is the meaning of `a` being the multiplicity), and any vector killed by some power of `(t−1)` lies in that primary part; so `ker((t−1)^m) ⊆ ker((t−1)^a)`. The two are equal, and both equal `im(e_A)`. ∎

**Corollary 1 (the cuts are the same operator).** The Degtyarev–Shimada coordinate cut `z_j = 0` and the CRT idempotent cut `e_A` are the *same linear projection* on the per-variable ambient space `V`: each is the projection onto `E₁(t) = im(e_A)` along the coprime complement. They agree not as dimension counts but **as operators** — `e_A` is the unique idempotent with image `E₁(t)` and kernel the `γ_j`-non-invariant part, which is precisely the projector the coordinate cut realizes. ∎

**The fine point (the generalized eigenspace is the correct geometric object).** In characteristic `p` "fixed by `γ_j`" must be read as the **generalized** eigenspace `ker((t−1)^m)`, not the ordinary one `ker(t−1)`. The ordinary eigenspace is one-dimensional (the constant line) regardless of the tower; the part the coordinate cut keeps is the entire `(t−1)`-primary block of dimension `p^v`, on which `t−1` is nilpotent. The two agree over `C` (eigenvalue `1` simple) but diverge over `F_p` with a tower — and it is the generalized/primary one that equals `im(e_A)`, confirmed byte-exact in §3 (e.g. `(8,2)`: both are 8, not 1). A referee should check this reading; it is the one point where the char-`p` statement is not the verbatim char-0 one, and it is the hinge on which Link B's tower behaviour will turn.

**Why this is the right register.** The proof uses only the primary decomposition of `V` as a `k[t]`-module — the same elementary linear-algebra register as the cyclotomic identity `x·c₀ = −1` that closed the red link [THE_NAIL_THEOREM.md, §7]. No appeal to the Aoki–Shioda cohomology of [2, §4], no spectral sequence, no Pham polyhedron beyond the action `γ_i ↔ t_i` already fixed in [2, §2]. The handle turns.

**The char-0 idempotent is the Galois average.** Over `C`, the verifier returns

```
e_A(t) = (1 + t + t² + ⋯ + t^{m−1}) / m = φ_full(t) / m,
```

the normalized sum over the cyclic group — i.e. the **averaging projector** `(1/|⟨γ_j⟩|) Σ_g g` onto the `γ_j`-invariants. This is the textbook projection onto the fixed subspace of a finite group action, and it is exactly the coordinate cut's invariant part. The idempotent *is* the Reynolds operator of the Galois rotation; that it equals the coordinate cut is then immediate, and the char-`p` case is the same statement with the simple eigenline thickened into the nilpotent tower.

## 3. The anchor — byte-exact, ten cells, both registers

The identity is proved in §2; this section records that it was *measured* first, across both characteristics and a range of tower heights, before being written — including the tall char-2 towers where an integral counterexample could hide. Each row recomputes `t^m − 1` over `k`, builds the shift `t`, the generalized eigenspace `E₁(t)`, and the idempotent `e_A` from a Bézout relation, and checks `E₁(t) = im(e_A)` as subspaces (equal ranks of `E₁`, `im(e_A)`, and their join) and `e_A² = e_A`.

**Char 0 (simple eigenvalue 1; `e_A = φ_full/m`, the Galois average):**

| `m` | `dim E₁` | `dim im(e_A)` | `E₁ = im(e_A)` | `e_A` idempotent |
|---|---|---|---|---|
| 4 | 1 | 1 | ✓ | ✓ |
| 6 | 1 | 1 | ✓ | ✓ |
| 10 | 1 | 1 | ✓ | ✓ |

**Char `p` (generalized eigenspace = `(t−1)`-primary, WITH the tower):**

| `(m, p)` | `dimA` | `dimB` | `dim genEig₁` | `dim im(e_A)` | `genEig₁ = im(e_A)` | `e_A` idem mod `p` |
|---|---|---|---|---|---|---|
| (6, 2) | 2 | 4 | 2 | 2 | ✓ | ✓ |
| (6, 3) | 3 | 3 | 3 | 3 | ✓ | ✓ |
| (12, 2) | 4 | 8 | 4 | 4 | ✓ | ✓ |
| (8, 2) | 8 | 0 | 8 | 8 | ✓ | ✓ |
| (15, 3) | 3 | 12 | 3 | 3 | ✓ | ✓ |
| (15, 5) | 5 | 10 | 5 | 5 | ✓ | ✓ |
| (9, 3) | 9 | 0 | 9 | 9 | ✓ | ✓ |

Ten cells, char `∈ {0, 2, 3, 5}`, `dimA ∈ {1, 2, 3, 4, 5, 8}`, including the maximal-height towers `(8,2)` and `(9,3)`. Zero discrepancies. The verifier is [`verifiers/EIGENCUT_IDENTITY_VERIFIER.py`](verifiers/EIGENCUT_IDENTITY_VERIFIER.py); it recomputes every number from scratch with no stored values.

## 4. Two corrections this note carries (cera carnauba)

Recorded plainly, because they were wrong in earlier campaign notes and the source settles them.

1. **The construction `X(2s)` lives in Degtyarev–Shimada §4.6, not "§17".** The paper [2] has five sections; the recurring "§17" in prior handoffs is a mislabel. The coordinate-zeroing cut `X(2s) := W_s ∩ {z_{2s+2} = ⋯ = z_{n+1} = 0}` is stated in §4.6 (verified verbatim against the source transcription). The object is correct; the section number was wrong.

2. **The `(t−1)`-primary dimension is `p^v`, not `p^v − 1`.** By Frobenius over `F_p`, `t^m − 1 = (t^{m'} − 1)^{p^v}` with `m = p^v m'`, `p ∤ m'`; for `m = p^v` the `(t−1)` factor appears with multiplicity `p^v` exactly. The measured `dimA` confirms: `(6,2)` gives `dimA = 2` (not 1), `(8,2)` gives `8` (not 7). The "`p^v − 1`" of earlier notes was the degree of the φ-restricted factor, a different quantity; it does not enter this identity.

## 5. Scope — what is closed, what is not

**Closed (this note).** The *geometric half* of Link A: the CRT idempotent cut `e_A` and the Degtyarev–Shimada coordinate cut `z_j = 0` are the same linear projection on the per-variable ambient space, in every characteristic (Lemma 1, Corollary 1), anchored byte-exact in ten cells (§3). With this, the geometric half of the dictionary of [THE_NAIL_THEOREM.md, §2] — carried there as a textual reading — is upgraded to a proved identity of operators.

**Not closed (named, not perfumed).**

- **Link B (the variety-level realization, ~15%).** This note proves the *single-variable* cut identity. Promoting it to the full sub-Fermat requires showing that zeroing the `n+1−(2s+1)` coordinates *simultaneously* realizes `X(2s)` as a variety — i.e. the tensor `C̄_{J_s}(2d) = C̄_{J(2s)}(2s) ⊗ S̄(s,d)` of [2, §4.6] is the multi-variable image of the iterated `e_A`-cut, and Corollary 1.7 (torsion-free in recursive dim 0, 2 ⇒ primitive higher) transfers to the CRT decomposition. The single-variable identity is the load-bearing piece and the tensor splits per variable (the idempotents are central, [THE_LOCALIZATION_THEOREM.md]), so the inheritance is plausibly near-free — **but it is stated, not proved here.** It is the remaining work for Link A to be a complete theorem.

- **The swan (Conjecture 1.2).** Untouched. This note fixes that the CRT cut *is* the DS cut; combined with the Nail it makes `rec = DS` (the block value equals the DS number) a theorem on the geometric side. It does **not** decide whether genuine integral torsion exists in some unmeasured recursive-dim ≥ 4 block. That remains open, and is a different battle.

**Not the Clay (rational) Hodge conjecture.** This concerns the integral Hodge conjecture for Fermat varieties, a bounded problem. The torsion counterexample has not been found; every measured cell is primitive.

## 6. Reproducibility

```
python3 verifiers/EIGENCUT_IDENTITY_VERIFIER.py
```

Recomputes both registers from scratch: char 0 (`m = 4, 6, 10`, simple eigenvalue, `e_A = φ_full/m`) and char `p` (`(m,p)` across the seven tower cells of §3), checking `E₁(t) = im(e_A)` as subspaces and `e_A² = e_A` in each characteristic. Returns `EIGENCUT IDENTITY OK` with zero discrepancies.

## References

1. R. Amichis Luengo, *The block-rank theorem for Fermat CRT blocks — and the red link.* Campaign note, version 2.0, 3 June 2026. [THE_NAIL_THEOREM.md](THE_NAIL_THEOREM.md)
2. A. Degtyarev, I. Shimada, *On the topology of projective subspaces in complex Fermat varieties.* J. Math. Soc. Japan **68**:3 (2016), 975–996. arXiv:1405.4683. — §2 (the Galois action `γ_i ↔ t_i`); §4.6 (the coordinate-zeroing cut `X(2s)`, the tensor `C̄_{J_s}(2d) = C̄_{J(2s)}(2s) ⊗ S̄(s,d)`); Remark 4.4 (the closed-form rank).
3. R. Amichis Luengo, *The localization of torsion to a single CRT block.* Campaign note, version 1.1, 1 June 2026. [THE_LOCALIZATION_THEOREM.md](THE_LOCALIZATION_THEOREM.md)
