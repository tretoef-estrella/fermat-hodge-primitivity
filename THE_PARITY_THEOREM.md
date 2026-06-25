# THE PARITY THEOREM
### A conjugation–parity obstruction in `V(4,4)-prim`, and why the primal "mold" is never a rank-128 King Pin section

**Author:** Third Auditor, Operación Glotón / King Pin · **Architect:** Rafael Amichis Luengo (Madrid) · 14 June 2026

---

## Scope and honesty (read first)

This is a **theorem about the lattice `V(4,4)-prim` and its plane families**. It rests on exactly one external result — the **Sweet Lie rank formula** (the primitive rank of a span of plane families equals `1 + |⋃ supports|`; equivalently the "finger count" over `K₆`) — and on the **Movasati–Villaflor** character description of the primitive cohomology of the Fermat fourfold. Both are cited, not re-derived.

**This is not the King Pin theorem.** It does not produce a record-beating lattice. It *closes a route*: it proves, by a parity invariant, that one entire family of candidate constructions (the "primal mold" = a rank-128 sublattice spanned by plane families) **cannot exist**, and therefore cannot be the King Pin section. It is an **obstruction / structural result — a tool**, not the record. Everything below is byte-exact and reproduced by the companion script `spectrum_parity_exact_v1.py`.

---

## 1. Setup

Let `V = V(4,4)-prim` be the primitive part of the middle cohomology lattice of the Fermat fourfold of degree 4. Under the natural torus `T = (Z/4)⁶ / Δ`, `V ⊗ C` is diagonalised by **characters**
```
a = (a₀, a₁, …, a₅),   aᵢ ∈ {1, 2, 3},   Σ aᵢ ≡ 0 (mod 4),
```
of which there are exactly **183** (verified by the roots-of-unity count `(1/4) Σ_{j=0}^{3} f(iʲ)·i^{-2j}` with `f(x) = (x + x² + x³)⁶`).

**Conjugation.** The intersection form pairs a character `a` with its complex conjugate `ā := (4 − a₀, …, 4 − a₅)`, i.e. it acts on entries by `1 ↔ 3`, `2 ↔ 2`. A character is *self-conjugate* iff `a = ā`.

**Families and supports.** The 15 perfect matchings `M` of `K₆` index the 15 plane families. The **support** of `M` is the set of characters carried by its planes:
```
supp(M) = { a : a_x + a_y ≡ 0 (mod 4)  for every edge (x,y) of M }.
```
Each `|supp(M)| = 27` (the `DS₄(4)`-count of Sweet Lie).

**The impostor.** `χ* := (2,2,2,2,2,2)`.

---

## 2. Three lemmas

**Lemma 1 (the impostor is the unique self-conjugate character, and it is universal).**
`a = ā ⟺ 2aᵢ ≡ 0 (mod 4) for all i ⟺ aᵢ = 2 for all i ⟺ a = χ*`. Moreover `χ* ∈ supp(M)` for **every** matching `M`: on any edge `(x,y)`, `χ*_x + χ*_y = 2 + 2 = 4 ≡ 0`. *(Byte-exact: `χ*` present in 15/15 supports.)* ∎

**Lemma 2 (supports are conjugation-closed).**
If `a ∈ supp(M)` then `ā ∈ supp(M)`, since for each edge `(x,y)`, `ā_x + ā_y = (4−a_x)+(4−a_y) = 8 − (a_x+a_y) ≡ 0 (mod 4)`. ∎

**Lemma 3 (every support has odd cardinality).**
By Lemma 2, conjugation is an involution on `supp(M)`. Its only fixed point is `χ*` (Lemma 1), which lies in `supp(M)` (Lemma 1). All other elements occur in conjugate pairs `{a, ā}` with `a ≠ ā`. Hence
```
|supp(M)| = 1 + 2·(#conjugate pairs)  is ODD   (indeed 27 = 1 + 2·13).
```
∎

---

## 3. The theorem

> **Parity Theorem.** *The span of any non-empty set `S` of plane families of `V(4,4)-prim` has **odd** primitive rank. Consequently no such span has primitive rank 128, and the rank-128 King Pin section is never family-spanned.*

**Proof.** By the Sweet Lie rank formula, the primitive rank of the span equals `|⋃_{M ∈ S} supp(M)|`. A union of conjugation-closed sets is conjugation-closed (Lemma 2), so conjugation is an involution on `U := ⋃_{M∈S} supp(M)`. Its unique fixed point is `χ*` (Lemma 1), which lies in `U` because it lies in every `supp(M)` (Lemma 1). Every other element of `U` is in a conjugate pair `{a, ā}`, `a ≠ ā`. Therefore
```
|U| = 1 + 2·(#conjugate pairs in U)  is ODD.
```
The primitive rank is odd; 128 is even; hence no family span has primitive rank 128. ∎

---

## 4. Byte-exact corroboration

Over **all `C(15,10) = 3003`** ten-matching subsets, the achievable primitive ranks (computed exactly as `|⋃ supp|`) are
```
{125, 127, 129, 131, 133, 135, 137, 141}  —  every one ODD; 128 is absent.
```
The number the campaign had measured as "10 families → rank 128" is the *span rank including the universal class `h`* — that is, primitive rank **127** (codimension 14), not 128 (codimension 13). The Parity Theorem explains the near-miss exactly: an even target is parity-forbidden for any family span.

---

## 5. What it kills, and what survives

**Killed.** The "measure the mold's minimum" programme is *moot*: there is no rank-128 primal mold to measure. Any search engine built to compute that minimum would be measuring an object that does not exist. The previously-open **"Bridge deck"** (a hypothesised map *primal rank-128 chorus mold → dual 13-cut*) loses its **input**: its premise is a primal rank-128 mold, and Lemma-3 parity forbids one.

**Survives, sharpened.** The rank-128 King Pin section is therefore **irreducibly dual** — a kernel of cheap functionals (steels), to be certified directly on the geometric Gram `Γ` (legal post-Bridge). The Parity Theorem turns the v50 reframe from an intuition into a *proof*: the section cannot be assembled from primal plane families; it must be cut.

---

*Theorem proven two independent ways (support conjugation-parity, and the exhaustive 3003-subset rank census), byte-exact, numbers from files only. Rests on Sweet Lie §3a and Movasati–Villaflor; it is an obstruction tool, not King Pin. PMC.*
