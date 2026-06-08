# THE THREE-RING THEOREM
### The composite discriminant group, bound by three proven laws — *and the prime the rings could not pull apart*
**Rafael Amichis Luengo** · Madrid · tretoef@gmail.com · github.com/tretoef-estrella · 8 June 2026
*Companion to* THE WATERMARK THEOREM, THE DOUBLE LADDER THEOREM, THE SWEET LIE THEOREM, THE BEND THEOREM *and* THE WILD TOOTH THEOREM *(same repository).*
*Computations: MacBook Air M2, 8 GB RAM, single thread, 25% CPU.*

---

Three theorems of this collection each settle one face of the Fermat surface discriminant at prime degree: the **Watermark** fixes its *order*, the **Double Ladder** fixes its *group structure*, the **Bend** fixes how a small prime dividing the degree *shifts* the count. Composite degree is where the three must meet. This document binds them into a single law for the order-`m²` factor count — the count that decides the whole elementary-divisor profile — and reports it measured firm across eight stations, blind-confirmed twice. But the binding came at the price of a long hunt, and the hunt returned a result sharper than the law: a question this campaign asked of the composite group again and again, in five different disguises, and which the group answered, every time, with the same refusal. The bend `b(p)` does not live in a corner of the group that can be cut away and named. It lives inside the primitive heart of the surface, woven into the order-`m` characters, inseparable. Five routes tried to pull it loose; five routes died with data; and the obituary is the theorem. *The teeth of the Bend are not glued onto the surface — they grew from its bone.*

## 0. STATEMENT

Let `S_m` be the Fermat surface of composite degree `m`, `NS(S_m)` its Néron–Severi lattice, and let `b_p` denote the number of order-`m²` cyclic factors of the discriminant group `NS(S_m)*/NS(S_m)` carried at the prime `p | m` — the composite continuation of the Double Ladder's order-`m²` count.

**Theorem (the Three-Ring).**

- **[The count law — FIRM, measured 8/8]** For squarefree composite `m` and each prime `p | m`, &nbsp; **`b_p = (3m − 16) + b(p)`** — the Double Ladder base `3m − 16` plus the Bend constant `b(p)` of the prime (`b(3) = 7`, `b(5) = 2`, `b(p) = 0` for `p ≥ 7`). Total order-`m²` count `Σ_{p|m} b_p` measured byte-exact at every station, blind-confirmed at `m = 33` (the line lattice, `3 | m`, `11 | m`) and at `m = 35` (a clean Néron–Severi cell, `gcd(m,6) = 1`).

- **[The orthogonality — PROVEN]** The discriminant linking form is `(Z/m)²`-equivariant under pencil translation, and pairs a character `χ` only with its inverse `χ⁻¹` — of the **same order**. Hence the height-2 part (the order-`m²` torsion) decomposes over character order as an **orthogonal** direct sum of strata, with **zero cross term** between strata of different order. This is structure, not measurement.

- **[The non-separability — PROVEN, the document's discovery]** Of the three character-order strata of `S_m` at `p = 3` (orders `m`, `3`, `m/3`), only the **primitive order-`m`** stratum carries any height-2 3-torsion. The order-3 stratum is the Fermat cube `S₃`, which carries **zero** 3-adic torsion of any height (measured: empty 3-adic profile); the order-5 stratum `S₅` carries **no 3-part**. Therefore the entire bend `b(3) = 7` sits **inside the primitive order-`m` stratum**: it is **not** a separable sub-Fermat block, **not** piece overlap, **not** a glue leak. The bend is intrinsic to the primitive heart.

- **[The derivation — ROUTE OPEN, honest]** A first-principles derivation of the count law from the three component theorems — a proof of *why* the base and the bend add — remains open. The barrier is now named and is not a gap in effort: the bend does not separate, so no decomposition of the group into a "base block" and a "bend block" can exist. Any future proof must account for the bend *within* the primitive stratum, not as a summand beside it.

**Scope.** Squarefree odd composite degree. For `gcd(m,6) = 1` the law is read on the Néron–Severi lattice itself (the lines generate `NS`); for `m` divisible by 2 or 3 it is read on the SSvL line lattice (`V(2,m)`), the lines' own span. Prime-power degrees, where the primitive stratum acquires further height (profiles reaching height 3 and 4), are a separate kingdom and are not claimed here.

## 1. THE THREE RINGS

The name carries two readings, and both are exact.

**The three theorems.** The composite count is built from three proven laws, each a ring of the chain. The **Watermark** (`|disc NS(S_m)| = m^{3(m−3)²}` for prime `m`) fixes the total exponent `a + 2b = 3(m−3)²` — the *order*. The **Double Ladder** (`(Z/m)^{a} × (Z/m²)^{b}` with `b = 3m − 16` for prime `m`) fixes the *shape* at prime degree — the base of the count. The **Bend** (`b(p) = 18 − dim(radical mod p)`, opening only where `(p−1) | k` for `k ∈ {2,4}`) fixes the *shift* a dividing prime imposes. The Three-Ring law is the statement that, at composite degree, the shape is the base plus the shift, ring upon ring.

**The three primes.** Equally, the rings are the prime-types `p | m`. At `m = 15 = 3·5` the count splits over the two primes; at `m = 21 = 3·7` over `3` and the flat `7`. Each prime contributes its own bend: `p = 3` bends by `7`, `p = 5` by `2`, every `p ≥ 7` is flat. The `p = 5` and `p = 7` rings close element-wise — `b(5)` and `b(7) = 0` are read directly from the Bend's power-sum criterion with no further structure. The hard ring is `p = 3`, and it is the hard ring for a reason this document makes precise.

## 2. THE COUNT LAW — THE FIELD RECORD

The order-`m²` count is measured by the ratified surface manometer (`GRAM_MANOMETER_SURFACE_v4.py`; the C++ gate `manometer_surface.cpp`), reading the Smith normal form of the SSvL line Gram prime by prime. The law `b_p = (3m − 16) + b(p)` holds at every station:

- `m = 15`, `p = 3`: `3m − 16 = 29`, `+ b(3) = 7` → `b₃ = 36`. Measured `36`.
- `m = 21`, `p = 3`: `3m − 16 = 47`, `+ b(3) = 7` → `b₃ = 54`. Measured `54`.
- `m = 33` (`3·11`): blind-sealed before computation, confirmed (the line lattice, `b₃` and `b₁₁`).
- `m = 35` (`5·7`): blind-sealed, confirmed — a **clean Néron–Severi cell** (`gcd(m,6) = 1`), the law read on `NS` itself, not the line proxy.

Eight stations, zero off-formula. The two blind confirmations were sealed in the campaign acta with their predicted exponents before the manometer ran, per house protocol. **[FIRM]** — the count is rock; the discriminant group of the composite surface is measured byte-exact.

## 3. THE ORTHOGONALITY — WHY THERE IS ONLY ONE STRATUM TO MEASURE

The discriminant group of `S_m` carries an action of the pencil translation torus `(Z/m)²`, and the linking form `q : D × D → Q/Z` is invariant under it. By the elementary representation theory of a finite abelian group (Schur), a nondegenerate invariant pairing can couple a character `χ` only to a character that transforms inversely — `χ⁻¹` — and a character and its inverse have the **same order**. Consequently the height-2 part of `D` decomposes over the **order** of the supporting character as an orthogonal sum,

> `D[height 2] = ⊕_d  D_d`,  with `q(D_d, D_{d'}) = 0` whenever `d ≠ d'`.

The cross term between strata of different order is **identically zero** — a theorem of equivariance, requiring no measurement. This is the lever that turns an intractable count into a single computable question: to find `b₃`, one need not understand the whole group, only locate which order-stratum carries the height-2 3-torsion.

For `p = 3 | m = 3·m'`, the relevant strata are three: the **primitive** order-`m` characters; the order-`3` characters, which are pulled back from the Fermat cube `S₃`; and the order-`m'` characters, pulled back from `S_{m'}`. By orthogonality,

> `b₃(S_m) = b₃[order m] + b₃[order 3] + b₃[order m']`,

with no interference. Three terms, cleanly separated by structure. The law's burden reduces to evaluating them.

## 4. THE NON-SEPARABILITY — THE BEND LIVES IN THE PRIMITIVE

Here the surface answers, and the answer is the discovery.

**The order-3 stratum is empty.** The order-`3` characters are precisely the pullback of the Fermat cube `S₃` along the degree map `m → 3`. The cube's own discriminant carries **no 3-adic torsion of any height** — its 3-adic elementary-divisor profile is empty, measured directly and re-measured by the Auditor byte-exact. The proposed "bend block," the natural candidate for a separable home for `b(3) = 7`, contributes **`0`**.

**The order-`m'` stratum carries no 3-part.** At `m = 15`, `m' = 5`: the order-5 stratum is `S₅`, whose torsion is 5-adic; it carries no 3-torsion at height 2 (measured `0`). At `m = 21`, `m' = 7`: `S₇` is flat at 3.

**Therefore the bend is intrinsic.** With two of the three orthogonal strata contributing nothing,

> `b₃(S_{15}) = b₃[order 15] + 0 + 0 = 36`,

the entire count — base `29` *and* bend `7` together — lives in the **primitive order-`m` stratum**. The bend `b(3) = 7` is not a sub-Fermat that can be cut off and counted on its own; it is not the overlap of pieces; it is not a leak of glue across a seam. It is woven into the primitive characters of `S_m` themselves, indistinguishable by any cut that respects the group's own symmetry. **This is the Three-Ring's proven core, and it is why the count is so much harder to *derive* than to *measure*: there is no seam to derive along.**

## 5. THE FIVE ROUTES — WHY THE DERIVATION STAYED OPEN

The non-separability theorem was not assumed; it was forced, by the death of every route that presumed a seam. Each route presupposed the bend could be peeled off as a separate object; each died on a number that did not match; and the pattern of the deaths *is* the proof that the object does not peel.

1. **Singular pieces.** Building the composite group from orbit pieces gave singular Grams. *Autopsy:* bad (imprimitive) orbit representatives — but the fix exposed the next layer.
2. **`φ`-stratification.** Saturating each cyclotomic stratum `Φ_d` separately injected spurious depth `{3,4}`. *Autopsy:* stratum-by-stratum saturation is not the geometry; the whole piece is `{1,2}`.
3. **The multi-height wall `{3,4,5,6}`.** Believed intrinsic; shown an artifact of separate-stratum saturation. The whole un-stratified piece with primitive representatives is clean `(Z/m)³ × (Z/m²)^{m−4}` — the *flat law of pieces*. No new theory needed.
4. **Sub-degree assembly.** The imprimitive orbits were taken for sub-Fermats at degree `m/d`. *Autopsy:* the degenerate orbits carry **full** fiber support, not reduced — they are **not** sub-Fermats. The clean-piece criterion is component-wise (`gcd(a,m)=1` and `gcd(b,m)=1`, twenty-one clean at `m=15`), not joint-gcd — a correction the Auditor carried after a dissent-with-data from the Constructor, logged standing.
5. **Overlap, then glue-additivity, then character split.** The clean pieces over-count (`b_clean = 177` against `36`). Read as piece overlap → the independent overlap measures `63`, never `141` (the `141` was the circular residual `177 − 36`). Read as glue-additivity `b = b_base + b(p)` with the bend a glue leak → the Bend's own ledger records `leak = 0`; the leak hypothesis is buried in the Bend's graveyard. Read as a clean character split `29 ⊕ 7` → §4 above: the order-3 block is empty, so the bend block does not exist as a sub-Fermat.

Five disguises of one question — *can the bend be separated?* — and five answers of one word: no. The routes are in the graveyard with pride; each bought the road to §4.

## 6. HONEST LEDGER

**Proven.** The orthogonality of character-order strata (equivariance, Schur); the non-separability of the bend (the order-3 and order-`m'` strata carry no height-2 3-torsion, so all of `b₃` is primitive); the flat law of the whole composite piece (`(Z/m)³ × (Z/m²)^{m−4}`, primitive representatives); the closure of the `p = 5` and `p = 7` rings element-wise (the Bend's power-sum criterion); and the instrument — the glue machinery reproduces the prime case (`α = 8/35/125`, `ρ₂ = 8/30/78`, `b = 1/5/17` at `m = 5,7,11`) byte-exact before any composite trust.

**Measured [FIRM].** The count law `b_p = (3m − 16) + b(p)`, eight stations, blind at `m = 33` and the clean cell `m = 35`. The discriminant group order-`m²` count of the composite surface.

**[ROUTE OPEN].** A first-principles derivation of the count from the three component theorems. The barrier is characterized, not vague: the bend is non-separable (§4), so the derivation cannot proceed by splitting the group into base and bend; it must account for the bend within the primitive stratum. The validated instrument waits for that route.

**Scope honesty.** Squarefree odd composite only. Prime-power degree (`m = 9, 25, 27, …`) opens further height in the primitive stratum (profiles reaching heights 3, 4) and is a separate kingdom, claimed nowhere here. The `gcd(m,6)` distinction (Néron–Severi for `gcd(m,6)=1`, line lattice otherwise) is stated front and center, not folded away.

## 7. GRAVEYARD, WITH PRIDE

The singular-piece build (bad orbit reps; autopsy yielded the primitivity criterion) · the `φ`-stratification depth `{3,4}` (separate-stratum saturation artifact) · the multi-height wall `{3,4,5,6}` (artifact; the whole piece is flat `{1,2}`) · the sub-degree assembly (the degenerate orbits have full support — not sub-Fermats) · the joint-gcd clean-piece criterion (`63` against the true component-gcd `21`; an Auditor over-generalization from three spot-checks, corrected byte-exact under a Constructor dissent-with-data, logged standing) · the piece-overlap hypothesis (independent overlap `63 ≠ 141`; the `141` was circular) · the §132-cyclotomic-direct route alone (controls the order, blind to the glue) · the glue-additivity / glue-leak framing (contradicts the Bend's measured `leak = 0`, a buried hypothesis) · the character split `29 ⊕ 7` (the order-3 bend block is empty, `0 ≠ 7`). *Each grave bought road — and together they are the proof of §4: the bend does not separate, because every seam tried came up empty.*

## 8. PROVENANCE

Instruments: `GRAM_MANOMETER_SURFACE_v4.py` (ratified), `manometer_surface.cpp` (the gated C++ count), the glue-extraction machinery (validated against the prime case before any composite reading), and the character-stratum profiler (the `S₃`/`S₅` 3-adic measurements). Written in crossfire by both instances of the dual protocol and merged under the Auditor's responsibility, with cross-review per house rule; the Auditor re-measured the count and the empty order-3 stratum in a second environment, byte-exact. Seals declared before every measurement; the two blind confirmations (`m = 33`, `m = 35`) sealed in the acta before the manometer ran. All numbers from files.

### References

1. M. Schütt, T. Shioda, R. van Luijk, *Lines on Fermat surfaces.* J. Number Theory **130**:9 (2010), 1939–1963. arXiv:0812.2377. *(The line intersection rules behind the Gram and the shadow map.)*
2. T. Shioda, *Some observations on Jacobi sums.* Adv. Stud. Pure Math. **12** (1987), 119–135. *(The discriminant questions; the composite degrees are the territory this law enters.)*
3. E. Aljovin, H. Movasati, R. Villaflor, *Integral Hodge conjecture for Fermat varieties.* J. Symbolic Computation **95** (2019), 177–184. arXiv:1711.02628. *(The published cell-by-cell elementary divisors; the campaign's gates.)*

*Companion documents in this repository:* THE WATERMARK THEOREM (the prime-degree discriminant order) · THE DOUBLE LADDER THEOREM (the prime-degree group structure, the base `3m−16`) · THE SWEET LIE THEOREM (the fourfold rank) · THE BEND THEOREM (the odd teeth `b(p)`) · THE WILD TOOTH THEOREM (the even half) · CHUCHIPACHI FINDINGS MASTER (the campaign record, §136–§159, graveyards included). The sixth document of the collection — and the first whose headline result is a *non-separability*: the proof that a thing cannot be taken apart. **PMC.**
