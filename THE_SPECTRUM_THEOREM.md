# THE SPECTRUM THEOREM
### A complete, byte-exact diagonalisation of the Fermat-fourfold plane intersection form, by `K₆` symmetry

**Author:** Third Auditor, Operación Glotón / King Pin · **Architect:** Rafael Amichis Luengo (Madrid) · 14 June 2026

---

## Scope and honesty (read first)

This is a **theorem about the intersection form on the plane span of `V(4,4)-prim`**. It rests on the **Sweet Lie** family/support structure and the **Movasati–Villaflor** torus-character description of the primitive cohomology (cited, not re-derived). **It is not the King Pin theorem.** It *maps the form* — it gives the exact spectrum and a structural law for it — which is the scaffold any equivariant cut construction stands on; but a spectrum is a **tool**, not a record-beating lattice. Every numeric claim is byte-exact (exact integer / Gaussian-integer arithmetic) and reproduced by `spectrum_parity_exact_v1.py`.

---

## 1. Setup

`V(4,4)-prim` carries **960 planes** `P_{M,b}`: 15 perfect matchings `M` of `K₆`, and for each, **64 phases** `b ∈ (Z/4)³` (one `Z/4` per edge). They span a **142-dimensional** lattice `Λ` with intersection form `G` (the 960×960 plane Gram). The torus `T = (Z/4)⁶ / Δ` acts on the planes by phase shift: a torus element `s = (s₀,…,s₅)` sends `P_{M,b} ↦ P_{M, b+δ(s)}`, where on edge `(x,y)` the shift is `δ_e(s) = s_y − s_x (mod 4)`.

`T` diagonalises `G ⊗ C`. Its characters are `a ∈ {1,2,3}⁶`, `Σ aᵢ ≡ 0 (mod 4)` (183 of them), with `a(s) = i^{Σ aᵢ sᵢ}`. For a matching `M` carrying `a` (i.e. `a ∈ supp(M)`), the **isotypic vector**
```
v_a^M  =  Σ_{s ∈ T}  i^{−Σ aᵢ sᵢ} · P_{M, δ(s)}
```
is the projection of a plane onto the `a`-eigenline of `T`.

---

## 2. The realisation lemma

> **Lemma (which characters the planes carry).** *A character `a` is carried by some plane family iff `#{i : aᵢ = 1} = #{i : aᵢ = 3}`. Writing `k` for this common count, the four realised value-types are*
> ```
> k=0 : 2⁶            k=1 : 1·2⁴·3        k=2 : 1²2²3²        k=3 : 1³3³.
> ```
> *Exactly `1 + 30 + 90 + 20 = 141` of the 183 characters are realised; the remaining 42 are carried by no plane.*

**Proof.** `a ∈ supp(M)` requires every edge of `M` to pair two entries summing to `0 (mod 4)`; the only such pairs from `{1,2,3}` are `(1,3)` and `(2,2)`. A perfect matching pairing all six entries this way exists iff the multiset of entries partitions into `(1,3)`- and `(2,2)`-pairs, i.e. iff `#1 = #3` (then `#2 = 6 − 2k` is automatically even). The congruence `Σaᵢ ≡ 0` is then automatic: `Σ = k + 2(6−2k) + 3k = 12 ≡ 0`. Counting types with `#1 = #3`: `k=0` gives `1`, `k=1` gives `6·5 = 30`, `k=2` gives `6!/(2!2!2!) = 90`, `k=3` gives `C(6,3) = 20`. ∎

The 141 realised characters together with the **universal class `h`** (the family-sum, equal for all 15 matchings) span the full 142-dimensional `Λ`.

---

## 3. The eigenvalue law

For a realised character `a`, let `N_a` be the **number of matchings whose support contains `a`** (equivalently, the number of perfect matchings of `K₆` consistent with the forced `(1,3)`/`(2,2)` pairing of `a`'s entries).

> **Eigenvalue Law.** *The intersection-form eigenvalue of the character direction `a` is*
> ```
>            λ(a)  =  16 · N_a ,
> ```
> *where 16 is the (uniform) eigenvalue of the within-matching block. Concretely:*

| type | `k` | `N_a` (supporting matchings) | `λ = 16·N_a` |
|---|---|---|---|
| `2⁶` (impostor) | 0 | 15 (every matching pairs 2's with 2's) | **240** |
| `1³3³` | 3 | 6 (bijections from the three 1's to the three 3's) | **96** |
| `1·2⁴·3` | 1 | 3 (the 1–3 edge forced × 3 matchings of the four 2's) | **48** |
| `1²2²3²` | 2 | 2 (2 pairings of 1's↔3's × the forced 2–2 edge) | **32** |

**Why `16·N_a`.** Within a single matching the 64 planes form a `(Z/4)³`-torus orbit; the block Gram is the corresponding circulant, whose nonzero eigenvalue is **16 uniformly** (Fourier-diagonalised: eigenvalue 16 on the 28 characters with `m(k) ∈ {0,3}`, `0` on the other 36). The character `a` is carried by exactly `N_a` of the 15 matchings; its isotypic vectors across those blocks **add coherently** under `G`. The image `w := G·v_a` is therefore an eigenvector supported on those `N_a` blocks (`64·N_a` planes), with eigenvalue `16·N_a`. ∎ (proof completed byte-exact in §5.)

---

## 4. The theorem

> **Spectrum Theorem.** *The intersection form on the 142-dimensional plane span of `V(4,4)-prim` has exactly **four** nonzero eigenvalues,*
> ```
>     16 · {15, 6, 3, 2}  =  {240, 96, 48, 32},
> ```
> *with multiplicities*
> ```
>     {2, 20, 30, 90}  =  2 · {1, 10, 15, 45},
> ```
> *the four integers `{1, 10, 15, 45}` being the `K₆` strata — the trivial class, the **10 bipartitions** `(3+3 splits)`, the **15 edges**, and the **45 pencil-pairs** — and the factor 2 the conjugate pairing `{a, ā}` (with the two self-conjugate directions `χ*` and `h` filling the eigenvalue-240 plane).*

**Proof.** The intersection form is `S₆ × T`-equivariant: `S₆` permutes the six coordinates and `T` is the torus of §1. The `T`-isotypic decomposition (§1) splits `Λ ⊗ C` into the character lines plus `⟨h⟩`. The eigenvalue is constant on `S₆`-orbits (the form is `S₆`-invariant), and the `S₆`-orbit of a character is exactly its **value-type** (since `S₆` realises every permutation of coordinates, two characters share an orbit iff they share the multiset of entries). By the Realisation Lemma there are exactly four realised value-types; by the Eigenvalue Law (verified byte-exact in §5) their eigenvalues are `{240, 96, 48, 32}`. Counting: `k=0` contributes the single direction `χ*` (eigenvalue 240); the family-sum `h` is the second eigenvalue-240 direction (§5); `k=3` contributes 20 directions = 10 conjugate pairs at 96; `k=1` contributes 30 = 15 pairs at 48; `k=2` contributes 90 = 45 pairs at 32. Total `2 + 20 + 30 + 90 = 142 = dim Λ`. ∎

**The strata, concretely.** `k=3` (`1³3³`) is the character `r(1_A − 1_B)` of a 3+3 **bipartition** `(A,B)`; its conjugate pair `{r=1, r=3}` is the **chorus** of Sweet Lie. The 10 bipartitions give the 20-dimensional eigenvalue-96 space. `k=1` (`1·2⁴·3`) is parametrised by the unordered **edge** `{position of 1, position of 3}` of `K₆` (15 of them). `k=2` (`1²2²3²`) is parametrised by a **pencil-pair** (the pair of 2-positions, plus a 1/3-bipartition of the remaining four: `15 × 3 = 45`).

---

## 5. Byte-exact verification

Because each isotypic vector `v_a` carries a large kernel component (its within-block Rayleigh quotient is the block value 16, **not** the form eigenvalue), the eigenvalue is certified on the *image* `w := G·v_a`, the genuine eigenvector. With exact integer (Gaussian) arithmetic:

```
type 2⁶  :   G(G·v) = 240·(G·v)   holds exactly,  G·v nonzero on 960 = 64·15 planes
type 1³3³:   G(G·v) =  96·(G·v)   holds exactly,  G·v nonzero on 384 = 64·6  planes
type 1·2⁴·3: G(G·v) =  48·(G·v)   holds exactly,  G·v nonzero on 192 = 64·3  planes
type 1²2²3²: G(G·v) =  32·(G·v)   holds exactly,  G·v nonzero on 128 = 64·2  planes
h (note) :   G(G·h) = 240·(G·h)   holds exactly
```

The nonzero-support counts `64·N_a` confirm the structural mechanism: `G·v_a` lives on precisely the `N_a` supporting blocks. The eigenvalue `16·N_a` is thus proven, not merely observed (`16 = 240/15 = 96/6 = 48/3 = 32/2`).

---

## 6. Consequence for King Pin (where the danger lives)

Decomposing each short vector's length² across the four `Q`-orthogonal eigenspaces gives a hard localisation:

| vector | e32 | e48 | e96 | e240 |
|---|---|---|---|---|
| squirrel (norm 12, point-pair) | 6 | 2 | 4 | **0** |
| witness `w` (norm 12, k=4) | 4 | **0** | 8 | **0** |
| disjoint (norm 14) | 6 | 3 | 4 | 1 |
| line (norm 18) | 8 | 5 | 4 | 1 |

**Byte-exact facts with teeth.** Norm-12 vectors carry **zero** energy in `e240` (the `χ* + h` plane): so `e240` is a *refuge* for the section (no short vector there) but **useless for the cut** (a functional in `e240` separates no norm-12 vector). The cut must draw from `e32 ⊕ e48 ⊕ e96`. The witness `w` lives **two-thirds in `e96`** — the 10-bipartition (chorus) stratum — which is exactly where 13 genuine steels (which reach the 162 non-chorus characters) can catch the very vectors the chorus lens was blind to. The Spectrum Theorem thus points the cut at `e32 ⊕ e96`, and pins the trivial-but-tempting `e240` as off-target.

---

*Spectrum sealed byte-exact in full 142 dimensions; the eigenvalue is `16 × (number of supporting matchings)`, with realisation governed by `#1 = #3`; the danger localised to `e32 ⊕ e96`. Rests on Sweet Lie and Movasati–Villaflor; it maps the form — a tool, not King Pin. PMC.*

---

## ADDENDUM — 15 June 2026 · the norm-12 vectors are SEVEN orbits, not one (byte-exact correction)

**What this corrects.** The squirrel (norm-12 point-pair) energy elsewhere in the project was stated as a single profile `[e32:6, e48:2, e96:4, e240:0]`. That is **incomplete**: it is only ONE of seven `S₆×T` orbits, and not even the modal one. Verified byte-exact by the 3rd Auditor (reproducer `squirrel_covariance_probe_v1.py`, census `squirrel_orbit_energy_census_v1.txt`; energies = `λ·|Π_λ c|²` with exact rational projectors; e240 in closed form on the 2-dim plane `⟨G·v(2⁶), G·h⟩`).

**The seven orbits `[e32, e48, e96, e240]` : count** (each sums to 12 = norm):

| profile | count | note |
|---|---|---|
| `[6,3,3,0]` | 61 440 | **MODAL**; e240=0 |
| `[6,2,4,0]` | 28 800 | the one the old table called "generic"; e240=0 |
| `[5,3,4,0]` | 23 040 | e240=0 |
| `[5,4,2,1]` | 11 520 | e240=1 |
| `[7,2,2,1]` | 11 520 | e240=1 |
| `[4,3,4,1]` | 5 760 | e240=1 |
| `[8,4,0,0]` | 1 440 | **e96=0 → chorus-blind** = the 1 440 `δ=(2,2,0)` of diario v50 (96×15), re-derived by energy alone |
| **total** | **143 520** | |

- **e240 split (exact):** e240=0 in 114 720 squirrels, e240=1 in 28 800. Aggregate e240 energy = 28 800 = **1.6722%** of the total 1 722 240. This confirms the handoff §2d byte-exact and shows the single-profile table was incomplete.
- **Aggregate per eigenspace:** e32 = 829 440 (48.2%), e96 = 460 800 (26.8%), e48 = 403 200 (23.4%), e240 = 28 800 (1.7%). The norm-12 vectors live in the **3-tone chamber e32⊕e48⊕e96 (140-dim)**; only the k=4 core `w = [4,0,8,0]` is 2-tone.
- **CAUTION on the kissing covariance.** `K = Σ_sq c cᵀ` is **NOT block-scalar**: the seven orbits weight the eigenspaces differently (e32 ranges 4..8). The clean guess `K = 9568·(Π₃₂+Π₄₈+3·Π₉₆)` (which assumed all squirrels `[6,2,4,0]`) is **FALSE** — killed by this census. The trace-average scalars `c₃₂=288, c₄₈=280, c₉₆=240, c₂₄₀=60` are trace-correct only. **Any chamber-LP / Rankin bound must use the seven-orbit fingerprint, not an averaged covariance.**

*This addendum is a byte-exact correction to the energy table. It does not change the Eigenvalue Law (§3) — the spectrum {240:2, 96:20, 48:30, 32:90} stands. PMC.*
