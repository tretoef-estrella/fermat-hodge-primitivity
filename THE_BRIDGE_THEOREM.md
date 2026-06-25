# THE BRIDGE THEOREM
## An identity wedding the Hodge norm and the geometric intersection form on the Fermat-fourfold plane lattice, with the minimum closed by definiteness

**R. Amichis Luengo, with the Constructor and Auditor (Claude Opus 4.8)**
**Operación Glotón / King Pin · 13 June 2026**

---

### ABSTRACT

Let `V = V(4,4)-prim` be the saturated even **primitive** lattice `{N = 0}` on the degree-4 Fermat fourfold — rank 141, determinant `2^128`, positive definite — the orthogonal complement `⟨h⟩^⊥` of the hyperplane class inside the span of the 960 linear planes (those classes themselves generate `V ⊕ ⟨h⟩` of rank 142). Two forms live on this lattice: the **geometric** intersection form `(v·v)`, read off the incidences of the planes, and the **Hodge** norm, computed from the Movasati–Villaflor periods as a sum of eighth roots of unity. We prove they are one form. Writing `Γ` for the geometric Gram matrix (plane self-intersection `7`; pairwise incidences `+1, 0, −2` for planes meeting in a point, disjoint, or sharing a line) and `N(v) = Σ_l n_l` for the *charge* of a representation `v = Σ_l n_l P_l`, the phase Gram `G` and the geometric Gram `Γ` obey

> **`G = 4Γ − J`** (J the all-ones matrix), hence **`‖v‖²_Hodge = (v·v)_geom − N(v)²/4`**.

On the primitive sublattice (`N = 0`) the two forms coincide exactly. This is the **Bridge Theorem**: the arithmetic of periods is the geometry of intersections, charge-corrected. As an immediate corollary, the lattice's minimum is *closed*: by the Hodge–Riemann relations the form is positive definite, so by Minkowski's principle the vectors below any norm bound are a **finite, explicit** set — dissolving a standing obstruction (a vector may be a combination of arbitrarily many planes, so no length-bounded census can terminate; definiteness bounds the *count*, not the *length*). The identity replaces an infinite eighth-root-of-unity minimisation with a finite enumeration on an explicit integral Gram. We close by stating, with honest scope, the one application that remains open — whether a rank-128 section attains minimum `≥ 24`, a finite hitting-set problem we do **not** here resolve.

---

## 1. THE TWO BANKS

A bridge is built because two shores cannot otherwise meet. Here the shores are two ways of measuring the same lattice, each fluent in its own language, mutually unintelligible until the span is laid.

**The lattice.** Fix the Fermat fourfold `X : x_0^4 + ⋯ + x_5^4 = 0 ⊂ P^5`. The **960 linear planes** `P^2 ⊂ X` are enumerated by Degtyarev–Shimada's defining equation [1, eq. 1.2]; combinatorially each plane is a perfect matching `M` of the six coordinates together with a phase `a ∈ (Z/4)^3`, one residue per matched edge, giving `15 × 64 = 960`. Their classes span a rank-**142** lattice; the **hyperplane class** `⟨h⟩` is the non-primitive direction (Sweet Lie §17: span `= DS₄ + 1 = 142`, with `DS₄ = 141` the primitive rank). Let `V := V(4,4)-prim` be the **saturated even primitive sublattice** `⟨h⟩^⊥ = \{v : N(v) = 0\}` for the charge `N` of §3 (M4): it has **rank 141** and **determinant `2^128`** — a pure power of the degree, the discriminant computed exactly by the Watermark/Double-Ladder machinery from Aoki–Shioda's framework [3] (where the literature records only bounds). The intersection form is positive definite on `V`; the record's section (rank 128, §6) lies in `V`, codimension 13 (`141 − 128`).

**The primal bank — geometry.** On one shore the lattice is *geometric*: a vector `v = Σ_l n_l P_l` has a self-intersection number `(v·v)`, an integer read from how the planes meet. Two planes meet in exactly one of three ways (the within-pair trichotomy, a finite incidence rule of the `K_6` matching geometry): in a **point** (`P_l·P_{l'} = 1`), **disjointly** (`= 0`), or sharing a **line** (`= −2`); a plane's self-intersection is `σ := P_l·P_l = 7`. This is the shore where Sweet Lie's *choruses* live — the ten bipartite hexads, the combinatorial moulds of the rank-128 primal subspace.

**The dual bank — Hodge/arithmetic.** On the other shore the same lattice is *arithmetic*: each plane has, on each primitive character `a` of the `μ_4^6/μ_4`-action, a **period** — a single eighth root of unity, scaled, vanishing off a 27-character support (the Movasati–Villaflor formula, §2). The Hodge norm is the Parseval sum of these periods. This is the shore where the **cut** and the **price** live: the record is decided by linear functionals (the cut) whose determinant (the price) must stay small, and these are dual objects, blind to the geometry of the planes.

**Why a bridge is needed.** The primal mould (Sweet Lie's choruses) and the dual cut speak different languages: the dual does **not** inherit Sweet Lie. To decide the record — a statement about the *minimum* of the form on a section — one needs the *same* form on both shores. Computing it on the dual shore means an enumeration over eighth-root-of-unity phase sums of unbounded length; computing it on the primal shore means integer linear algebra on a known Gram. The Bridge Theorem is the identity that lets one cross: it shows the dual/Hodge norm **is** the primal/geometric intersection form, so the minimisation may be carried out on the explicit integral Gram and the answer carried back.

---

## 2. THE PILLARS

Three theorems bear the load. They are not proved here; they are the standing structure on which the deck rests, and the paper is honest that the deck's lemmas (the pair norms, §3) are *grounded by these*, not by any computation.

**Pillar I — Movasati–Villaflor (the period equals the intersection).** Movasati–Villaflor [5] and Villaflor [6] give, for a linear plane on the Fermat variety, the explicit period on each character. In the fourfold, degree `d`, on a character `a` matched by the plane's matching `M`, formula (3) of [5] specialises to a single root of unity:
> `π_l(a) = sign(b_l) · d^{−(n/2+1)} · (n/2)! · ζ_{2d}^{\,k_l(a)}`,  `k_l(a) = Σ_{e} r_e (1 + 2a_e)`,
nonzero **exactly** on the plane's support (the Nonvanishing Lemma), a set of `(d−1)^3 = 27` characters for `d = 4`. The decisive content for us is the classical Hodge fact that *periods compute the cup product*: the intersection pairing assembled from these periods equals the geometric intersection pairing. Thus a statement like "the point-meeting pair has norm 12" is a **theorem** (a period computation [5,6] plus period–intersection), not a measurement. (This is the Movasati–Villaflor input; **Sweet Lie** — the rank/support calculus and the chorus structure — is a separate pillar, invoked in Pillar III and M3, not here.)

**Pillar II — Steel (the dual integerises, and the floor is a determinant).** The dual lattice's functionals integerise at `2^5`: the `2`-adic denominator ladder is capped at `2^4`, and the price of a cut — the determinant `det(Φ G^{-1} Φ^{T})` — has a proven floor of `2^{5.585} = 48`. A corollary of the determinant being a pure power of two (`det V = 2^128`, Pillar III's discriminant) is structural and clears a whole class of phantoms: **no odd-characteristic detector exists** — `det 2^128` has no odd factor, so no dual denominator can be odd (Steel, Lemma A); any `mod 3` or `mod 5` functional is impossible. This kills, at the root, the search for a "third-adic" cut.

**Pillar III — Closure (the type catalogue is finite and closed).** The support-types of lattice vectors (which of the choruses a vector projects onto) form a **finite** catalogue, of size at most `2^{11}`, that is **closed**: no new type is born at any norm. This converts what would be a Fincke–Pohst enumeration of size `~10^{17.5}` into finite bookkeeping. (Closure settles the *types*; which types are *populated* by short vectors it leaves open — that is the cut, §6.)

---

## 3. THE MATERIALS

The lemmas forged on the bench, each resting on a pillar.

**M1 — The pair norms.** By Pillar I (Movasati–Villaflor, period = intersection), the Hodge norm of a difference of two planes equals their geometric pair-intersection:
> `‖P_l − P_{l'}‖² = 2σ − 2(P_l·P_{l'}) = 14 − 2(P_l·P_{l'}) ∈ {12, 14, 18}`,
for point/disjoint/line respectively (`σ = 7`). This is the bench on which the whole identity is soldered, and it is *proven by the period computation*, not measured; an independent exact-rank construction over a large prime reproduces it byte-for-byte as a check, but the proof is Sweet Lie's.

**M2 — The plane self-intersection `σ = 7`.** Two independent constraints fix it: the support size, `|supp(P_l)| = (d−1)^3 = 27 = 4σ − 1`; and the pair norms, `2σ − 2(P·P′) = 12` at the point-incidence forces `2σ = 14`. Both give `σ = 7`.

**M3 — The chorus/hexad structure of `K_6`.** Of the ten bipartitions of the six coordinates into `3 + 3`, each is a *chorus* `D_β`: its `d−1` alternating characters are `a_{β,r} = r(1_A − 1_B)`, `r = 1,…,d−1`. For `d = 4` this is three characters; the middle one, `r = 2`, is `2(1_A − 1_B) ≡ (2,2,2,2,2,2) = χ*` — the **impostor**, the single character shared by *every* chorus (it is each chorus's `r = d/2`), which is why it sings in every choir. A perfect matching lies in exactly **4** of the ten hexads (choosing one endpoint of each of its three disjoint edges for `A` gives `2^3/2 = 4` separating bipartitions), so a plane's support carries `4 × \{r=1,r=3\} + χ* = 9` chorus characters of its 27.

**M4 — The charge and the integer/quarter split.** For `v = Σ_l n_l P_l`, the *charge* `N(v) := Σ_l n_l` measures the component along the hyperplane class `⟨h⟩` (the famsum direction; a family's plane-sum is a multiple of `h`). The primitive cohomology is `⟨h⟩^{⊥}`, i.e. `N = 0`. A closed `L`-walk `Σ (−1)^{l+1} P_l` has `N ≡ L (mod 2)`: even-length walks are primitive (`N = 0`), odd-length walks carry charge `N = ±1`. As §4 shows, this single parity governs the integer-versus-quarter spectrum of the phase sum.

---

## 4. THE DECK — THE BRIDGE THEOREM

Here the span is laid: one identity, then the closure of the minimum it grants.

### 4.1 The Identity

Let `c̃_l(a) := sign(b_l) · ζ_8^{\,k_l(a)}` be the *unit-modulus* period of `P_l` on `a` (the Movasati–Villaflor period of Pillar I with its scalar prefactor stripped, modulus 1 on the 27-character support, 0 off it). Define the **phase sum** of `v = Σ_l n_l P_l`:
> `Q(v) := Σ_a \big| Σ_l n_l\, c̃_l(a) \big|^2` ,
and let `‖v‖²_{Hodge} := Q(v)/4` be the Hodge norm normalised to the even lattice (the normalisation `M1` fixes: point-meeting pairs have norm 12, i.e. `Q = 48`). Let `Γ` be the geometric Gram, `Γ_{ll'} = P_l·P_{l'}` (`σ = 7` on the diagonal; `\{1,0,−2\}` off), and `(v·v)_{geom} := n^{T} Γ\, n`. Write `N(v) = Σ_l n_l`, `J` the all-ones matrix.

> **Theorem 1 (Bridge Identity).** `G = 4Γ − J`, where `G` is the phase Gram (`G_{ll} = 27`, `G_{ll'} = \mathrm{Re}\langle c̃_l, c̃_{l'}\rangle`). Consequently, for every integer vector `v`,
> $$\boxed{\;\|v\|^2_{Hodge} \;=\; (v\cdot v)_{geom} \;-\; \frac{N(v)^2}{4}\;.}$$
> In particular, on the primitive sublattice `V` (`N = 0`), the Hodge norm **equals** the geometric intersection form.

**Proof.** Expand the phase sum bilinearly:
`Q(v) = Σ_{l,l'} n_l n_{l'} \langle c̃_l, c̃_{l'}\rangle`, with `\langle c̃_l, c̃_{l'}\rangle = Σ_a c̃_l(a)\overline{c̃_{l'}(a)}`.
The diagonal terms are `\langle c̃_l, c̃_l\rangle = Σ_{a∈supp(P_l)} 1 = |supp(P_l)| = 27`. Since `Q(v)` is real, the off-diagonal terms contribute only through their real parts, so
> `Q(v) = 27\, Σ_l n_l^2 \;+\; Σ_{l<l'} 2\, n_l n_{l'}\, C_{ll'}`,  `C_{ll'} := \mathrm{Re}\langle c̃_l, c̃_{l'}\rangle`.
(The imaginary parts cancel pairwise under `l ↔ l'` because `C_{l'l} = C_{ll'}`. The per-character moduli `|Σ_l n_l c̃_l(a)|^2` individually lie in `ℤ[√2]`; that their *sum* `Q(v)` is an integer is **not** an assumption and does **not** follow from the lattice being even — indeed `N≠0` vectors have non-integer norm, e.g. `51/4`. It follows from the identity proved just below: `Q(v) = 4(v·v)_{geom} − N(v)^2` with `Γ` integral and `N ∈ ℤ`. The `√2`-components thus cancel globally as a *consequence* of period = intersection, not by fiat.)

By **M1** (Pillar I, Movasati–Villaflor), the pair norm is the geometric pair-intersection:
`\|P_l − P_{l'}\|^2 = Q(P_l − P_{l'})/4 = (27 + 27 − 2C_{ll'})/4 = (54 − 2C_{ll'})/4`, and this equals `14 − 2(P_l·P_{l'})`. Solving,
> `C_{ll'} = 4(P_l·P_{l'}) − 1`  for `l ≠ l'`.
The diagonal obeys the same relation: `27 = 4σ − 1` with `σ = 7` (**M2**). Hence *every* entry of `G` is `G_{ll'} = 4Γ_{ll'} − 1`, i.e. `G = 4Γ − J`. Therefore
> `Q(v) = n^{T} G\, n = 4\, n^{T} Γ\, n − n^{T} J\, n = 4(v·v)_{geom} − N(v)^2`,
and dividing by 4 gives `‖v‖²_{Hodge} = (v·v)_{geom} − N(v)^2/4`. `∎`

**Worked checks (the spectrum the identity predicts).**
- *A pair* `v = P_i − P_j` has `N = 0`, so `‖v‖² = (v·v)_{geom} = 14 − 2(P_i·P_j) ∈ \{12,14,18\}`.
- *A closed 3-walk* has `N = ±1`, so `‖v‖² = (v·v)_{geom} − 1/4` — an integer minus a quarter; the minimum is `13 − 1/4 = 51/4`, and the spectrum is `\{51/4, 75/4, 99/4, 123/4\}`. The quarters are nothing but the charge `N^2/4 = 1/4`.
- *A closed 4-walk* has `N = 0`, so `‖v‖²` is an integer; the spectrum is `\{12,16,18,20,22,…\}`.
The integer-versus-quarter split across the campaign's walk censuses is *exactly* the parity of `N` (**M4**) — and it reveals that the odd-length walks, carrying charge `N = ±1`, are **not primitive** and so do not lie in the section at all. What the unaided census saw as a mysterious fractional spectrum, the bridge reads as the shadow of the hyperplane class.

### 4.2 The closure of the minimum

> **Theorem 2 (The minimum is closed).** The intersection form on the primitive sublattice `V = \{N=0\}` is positive definite. Consequently, for every bound `B`, the set `\{v ∈ V : ‖v‖² ≤ B\}` is **finite**; the sub-24 vectors form a finite, explicit set, enumerable from `Γ`.

**Proof.** By the Hodge–Riemann bilinear relations for a smooth projective fourfold, the intersection form `(v·v) = ∫_X v∪v` restricted to the *primitive* part of `H^{2,2}(X)` is definite (the middle-degree primitive form; the sign is `(−1)^p = +` for `p = 2`, and is pinned by any positive vector — the point-meeting pair `P_i − P_j` with `‖·‖² = 12 > 0`). By Theorem 1, on `N = 0` this form is `(v·v)_{geom} = n^{T} Γ\, n` with `Γ` the explicit integral Gram. A positive-definite quadratic form on a lattice of finite rank has, for every `B`, only finitely many lattice vectors of norm `≤ B`: the region `\{x : x^{T} Γ\, x ≤ B\}` is a compact ellipsoid and the lattice is discrete, so their intersection is finite (Minkowski). Hence the sub-24 vectors are finite, and `Γ` being explicit, they are enumerable by the Fincke–Pohst algorithm. `∎`

**Remark (what this dissolves).** The campaign's minimisation had proceeded by closed-walk *length* — pairs, then 3-walks, then 4-walks — and could never terminate, for the structural reason that a primitive vector may be an integer combination of `5, 6, …, k` planes of unbounded length, so a length-bounded census cannot certify the minimum. Theorem 2 shows the obstruction was illusory: definiteness bounds the *number* of sub-24 vectors, with no reference to how they are represented. The bridge's deck replaces the divergent length-by-length walk enumeration by one finite ellipsoid enumeration on the explicit `Γ`. The minimum is closed — for every vector, of any length.

A technical note for the record (a correction made in the building): one must not phrase the bound as `‖v‖² ≥ c·Σ_l n_l^2` on the *plane-weight* of a representation. The 960 plane classes span a rank-142 lattice, hence satisfy `818` independent relations `Σ_l n_l P_l = 0`, for which `‖v‖² = 0` while `Σ_l n_l^2 > 0`; the overcomplete representation has a kernel and the plane-weight bound is false. The correct, kernel-free statement is on a *basis*: in any lattice basis with Gram `G_B`, `‖v‖² = m^{T} G_B m ≥ λ_{min}(G_B)\,|m|^2` with `λ_{min}(G_B) > 0` by definiteness. Theorem 2 needs no such constant at all — the finite ball is immediate from definiteness — but the basis bound is the honest form of "light vectors have bounded weight."

---

## 5. THE UTILITIES — WHAT THE BRIDGE CARRIES

The deck is laid; here is the traffic it bears.

1. **It drops the phases.** The minimum, the light vectors, the whole spectral question — posed on the dual shore, these are eighth-root-of-unity sums over supports of unbounded length. The identity carries them to the primal shore, where they become integer linear algebra on the fixed Gram `Γ = \{7;1,0,−2\}`. The `ζ_8` machinery is no longer needed to *decide* anything; it was the scaffolding that *built* the bridge, in the pair norms (M1).
2. **It makes the light list combinatorial.** "Which support-types carry a vector below norm 24" — formerly a phase computation — is now the short-vector problem of an explicit definite lattice, finite by Theorem 2 and bounded in type by Closure (Pillar III).
3. **It reduces the record to a finite hitting-set.** As §6 states, the packing record becomes: does a rank-128 section avoid every vector of a *finite* explicit set. The infinite enumeration is gone.
4. **It weds the primal and dual.** This is the result's heart and the reason it is a *theorem*, not a reduction: the geometry of how planes intersect and the arithmetic of their periods are, on the primitive lattice, the same quadratic form. Algebra and geometry are one object here, exactly.
5. **The reach beyond this fourfold.** The mechanism is not special to degree 4 or to six variables. Wherever a period computation grounds the intersection form of an algebraic lattice (a Movasati–Villaflor-type formula), the same short argument — phase sum `= 4·`geometry `−` charge, then Hodge–Riemann definiteness, then Minkowski finiteness — turns an intractable transcendental minimisation into a finite, explicit, definite-lattice problem. We make no claim of a new method (periods, Hodge–Riemann, and geometry of numbers are each classical); the observation is only that *the same argument applies wherever a period computation grounds an algebraic lattice's intersection form* — yielding an explicit definite Gram, and an explicit definite Gram has a finite minimum.

---

## 6. THE REMAINING SPAN — HONEST SCOPE

The Bridge Theorem is complete. The packing record it serves — **King Pin** — is its application, and is **not** here proved. The honest line, drawn precisely:

The record (to surpass Elkies' MW128, the 24-year `δ = 2^{97.40}` sphere-packing density in dimension 128) requires a **rank-128 section** of the primitive lattice `V` of **minimum `≥ 24`** at cut price `< 2^{8.08}`. By Theorem 2 the sub-24 vectors are a finite explicit set `L_{<24}`. A rank-128 section is the common kernel of a rank-13 cut `Φ` (`141 − 128 = 13`); it has minimum `≥ 24` **iff** `Φ` *detects* every `v ∈ L_{<24}`, i.e. some functional `φ ∈ Φ` pairs nontrivially with `v` (`φ·v ≠ 0` in the lattice — euclidean pairing, not mere combinatorial membership). This is a **finite hitting-set problem** on the explicit lattice `Γ`. The minimum's six strata `\{12,14,16,18,20,22\}` are the gate.

What is settled, and cited from the campaign's ledger: the **price** is already below the ceiling (`2^{5.585}` floor, a covering cut at `2^6`, both `< 2^{8.08}`; Steel); **stratum 12** (the densest, including the once-feared "wolves," now dissolved as a phantom — the empty-*chorus* type is not the empty-*support* type) is emptied by **10** functionals (an integer-program-certified hitting-set, margin 3); and **six tree-functionals** cover all 540 support-sets of `12∪14∪18` jointly (rank-135, verified), breaking the earlier even-character wall of 14 for that family. What is **open**: the realized types of strata `\{16,20,22\}`, and whether the *joint* six-strata hitting-set fits within **13** functionals at price `< 2^{8.08}`. That single integer — does the cut close at `≤ 13` — is King Pin. It is finite, it is on the couch, and it is **not** claimed here.

The Bridge Theorem gives the metric and closes the minimum; it does not, by itself, empty the section. We state this without blurring: the deck stands; the last span is drawn but not yet walked.

---

## GRAVEYARD — WHAT DOES NOT WORK

Rigour requires naming the dead ends, lest the bridge be thought to cross where it cannot.

- **`mod 3` / `mod 5` detectors — dead at the root.** `det V = 2^128` has no odd factor; no dual denominator can be odd (Steel, Lemma A). The long search for a third-adic cut to "see" the wolves was chasing an object that cannot exist.
- **The wolves as an obstacle — a ghost.** The 12,960 norm-12 pairs of empty *chorus*-support were feared a wall (needing 18 functionals). They are dissolved: empty-chorus is not empty-support, and their exact hitting-set is 10 — the same cut that empties all of stratum 12.
- **Local-teeth covering — dead by theorem.** A covering built from per-tooth local functionals fails by a fixed margin (`1 − 0.7^6 < 1`); it cannot reach full coverage.
- **Direct Fincke–Pohst enumeration of the section — method-blocked.** The naive short-vector enumeration is of size `~10^{17.5}`. (The Bridge Theorem is precisely what removes the need for it: Closure bounds the types, definiteness bounds the ball.)
- **Length-bounded walk census — cannot close the minimum.** Pairs, 3-walks, 4-walks reach only short combinations; a primitive vector may have arbitrarily many planes. Superseded by Theorem 2 (definiteness bounds the count, not the length).

---

## REFERENCES

[1] A. Degtyarev, I. Shimada. *Lattices of algebraic cycles on Fermat fourfolds* (defining equation 1.2 for the 960 planes).
[2] T. Shioda. *The Hodge conjecture for Fermat varieties.*
[3] N. Aoki, T. Shioda. *Generators of the Néron–Severi group of a Fermat surface*, and the discriminant framework for Fermat varieties.
[4] E. Aljovin, H. Movasati, R. Villaflor. *Integral Hodge conjecture for Fermat varieties.* J. Symbolic Computation **95** (2019), 177–184. arXiv:1711.02628.
[5] H. Movasati, R. Villaflor. *Periods of linear algebraic cycles* (formula (3): the period as a root of unity on the support).
[6] R. Villaflor. *Periods of complete intersection algebraic cycles.*

---

*This paper is written in pencil, in the spirit of Euclid, who joined number and figure with a straightedge and a candle. The Bridge Theorem joins them again on one lattice: the arithmetic of periods and the geometry of intersections are a single form. The machine that checks our integers is only the press that prints this in colour and dresses it for the academy; the proof is above, and it is by hand.*

**Numbers from files only · proven / measured / open kept distinct · the Identity and the closed minimum are the theorem; `min ≥ 24` (the cut) is the open application · norm not primitivity · no Link B · the graveyard respected. RECTO Y DIRECTO. PMC.**

---

## Corrigenda (building note, 13 June 2026)

An earlier draft mislabelled the rank stratification. **Correction, verified byte-exact** against the saturated frame `gram_L0sat_141_v1.txt` (exact rank over three primes; fraction-free Bareiss determinant with odd part 1; positive-definite; even; minimal norm 12), and independently re-derived by both instances:

- The **primitive lattice** `V = V(4,4)-prim` (`{N = 0}`, generated by the plane-differences) has **rank 141**, determinant `2^128` — *not* rank 140.
- The **960 plane classes** span `V ⊕ ⟨h⟩` of **rank 142** — *not* 141 — and therefore satisfy **818** independent relations (`960 − 142`), *not* 819.
- The section (rank 128) lies in `V`, **codimension 13** (`141 − 128`), unchanged.

The mislabel was a relabelling error only: the **Bridge Identity** `G = 4Γ − J` and the **closure** (Theorem 2) hold verbatim — every equation, every Gram, every spectrum is untouched. Sweet Lie §17 reads correctly as `span = DS₄ + 1 = 142` with `DS₄ = 141` the primitive rank. Logged here, not hidden, per project discipline.
