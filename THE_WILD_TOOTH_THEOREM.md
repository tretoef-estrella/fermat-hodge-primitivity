# THE WILD TOOTH THEOREM
### El Diente Salvaje — the prime the Bend left outside, tamed by its own ledger; the deep towers a kingdom of depth mod 4
Rafael Amichis Luengo · Madrid · tretoef@gmail.com · github.com/tretoef-estrella · 8 June 2026
Companion to THE WATERMARK THEOREM, THE DOUBLE LADDER THEOREM, THE SWEET LIE THEOREM and THE BEND THEOREM (same repository).
Computations: MacBook Air M2, 8 GB RAM, single thread, 25% CPU.

---

The Bend Theorem proved where and why the discriminant profile law of Fermat surfaces bends at odd primes, and closed its statement with a parenthesis: *p = 2, even degree — both channels open and wild — the even half's separate kingdom, outside this document.* This document enters that kingdom and tames the animal. The prime 2 is wild for two reasons, both now named: over **F**₂ every power-sum channel is open at once — Σt^j ≡ 1 for every j ≥ 1, including the odd channels k = 1, 3 that no odd prime ever sees — and, deeper, the polynomial calculus itself FOLDS: t² ≡ t, so quadratic and linear are the same function and the odd kingdom's bookkeeping collapses. A folded frame with every door open is not chaos; it is a smaller, stranger room. What survives the collapse is a sharper law than the wildness suggested: one constant for every squarefree even degree, one constant for every deep tower of two — the latter NEGATIVE, a rank deficit no odd prime ever produced — one one-line ledger that explains both, and the odd teeth besides, and an anatomy in which **every dimension carries a name**, closed in the same day the document was written.

## 0. STATEMENT

Let S_m be the Fermat surface of even degree *m*, *G* the SSvL line Gram, σ the shadow map onto the twelve channels, and **b(2) = rank_{F₂}(G) − 12(m−3)** the bend constant at 2.

**Theorem (the Wild Tooth).**
- **[Squarefree law, FIRM]** For every squarefree even m: **b(2) = 14**, with uniform anatomy: radical of dimension 7 — five surviving cross-family **mass ties** and two cross-family **parity ties**, every dimension named (§2) — and shadow corank 15.
- **[Tower law, FIRM]** For m = 2^e, e ≥ 3: **b(2) = −6** — a NEGATIVE bend, rank below the 12(m−3) baseline — with constant anatomy: radical 21 (parity-polynomial 15, plus six **second-bit ties**, §4), shadow corank 21. The ground floor m = 4 is the lone exception: b(2) = +6 (corank already 21, radical still 9).
- **[The universal ledger — the crown]** All bend constants, at every prime and every degree measured, obey one line:

> **b(p) = 36 − corank_p(σ) − dim(radical_p),**

with 36 = 12 channels × 3 polynomial degrees the fixed baseline. Verified seven of seven: (m,p) = (15,5): 18+16 → b = 2 · (13,13): 18+18 → 0 · (6,2): 15+7 → 14 · (10,2): 15+7 → 14 · (4,2): 21+9 → +6 · (32,2): 21+21 → −6 · and the odd Bend's accounting b = 18 − radical recovered entire as the corank-18 special case. **Odd primes never move the corank; the wild tooth moves BOTH terms.**

## 1. THE TWO FACES OF WILDNESS

**(i) All channels open.** Over **F**₂, Σ_t t^j ≡ 1 for every j ≥ 1 — the (p−1) | k criterion of the Bend admits everything, including the odd channels invisible to every odd prime. The Bend's kernel structure (the generalized circulant K(t,t′) = κ(αt + βt′ mod m), proven at general m) applies verbatim; what changes is that no door is ever shut.

**(ii) The fold.** As functions on **F**₂, t² ≡ t: per channel the polynomial space collapses to {constant, parity}. The odd kingdom's generic frame — 18 radical identities, 18 shadow relations, both polynomial of degree ≤ 2 — does not reduce mod 2; it FOLDS, and the wild tooth's arithmetic is the arithmetic of that folding, at two levels.

## 2. THE FOLD AT THE RADICAL LEVEL — every dimension named

Mod 2 the certified linear (6) and polarization (3) frames land in one parity sector of rank **5** — four collisions, polarization ≡ linear by the fold. The true mass frame (extracted from two odd kingdoms, m = 15 p5 and m = 13 p13: dimension 9 at both, identical integral span, entries {0, ±1} — each generator a cross-family mass tie) keeps full rank 9: the constant sector does not fold. Death census with full tail freedom, byte-identical at m = 6 and m = 10: **mass deaths 4, survivors 5 · parity deaths 4, survivor 1** — and pure parity content in the radical is ZERO: nothing of the parity sector survives without a constant tail welded on.

The seventh dimension — and with it the full mixed pair — is the even kingdom's own inhabitant, now named: the **cross-family parity ties**, the parity analogue of the odd mass ties. The all-directions parity mass of two families agrees up to a constant tail, and the tails are exact and m-independent:

> **allpar(f₀) + allpar(f₁) ≡ 1[f₀:k−l] + 1[f₀:k+l] + 1[f₁:k]**,  **allpar(f₀) + allpar(f₂) ≡ 1[f₀:k] + 1[f₂:k]**,

with the third tie their sum — cyclic consistency exact. Verified at THREE kingdoms (m = 6, 10, 14, byte-identical tails); the asymmetry of the tails records the unit shift of the family-0/family-2 incidence rule. **Census closed: 7 = 5 mass ties + 2 parity ties, nothing unnamed.**

## 3. THE FOLD AT THE CORANK LEVEL — the three collisions, named

The 18 shadow relations (gated at the odd control m = 15, p = 5: all 18 in the left kernel of σ, rank 18 = corank, full span — no mod-2 reading trusted before that gate fired green) are, per family: three constant ties (the four direction-masses agree), two linear relations (−k+l+(k−l) and −k−l+(k+l)), and the **parallelogram identity** (k−l)² + (k+l)² = 2k² + 2l². Mod 2:

> **PARALLELOGRAM ≡ lin₁ + lin₂ (one collision per family, three in all: 18 → 15).**

Verified two ways: machine extraction byte-identical at m = 6 and m = 10, and symbolically — the parallelogram's weight vector (−2t², −2t², t², t²) folds to (0, 0, t, t), which is exactly lin₁ + lin₂ ≡ (−2t, 0, t, t) mod 2. The corank term of the squarefree ledger (15) is the folded trinity, and the bend's 14 = 36 − 15 − 7 closes as pure bookkeeping.

## 4. THE TOWERS — THE MOD-4 KINGDOM, AND THE NEGATIVE BEND

At m = 2^e the shadow corank is **21 = 18 − 3 + 6**: the same three fold-collisions, PLUS six new relations (two per family) that exist only when 4 | m — **mod-4 carry windows**, identities of residue indicators, e.g. per family the complementary pair `ind[k∈{0,1}] + ind[l∈{1,2}] + ind[k−l=1] + ind[k+l=0] ≡ 0` and its bit-flipped twin — verified by hand on all 16 points of (**Z**/4)², carry arithmetic of the half-residues, structure no odd kingdom can possess.

The radical meanwhile grows from 9 (m = 4) to a stable 21 (m = 8 through 64), carrying six dimensions beyond the polynomial frame — the campaign's first radical content outside constants and parities anywhere. Those six are now identified: as cosets modulo the polynomial frame they are spanned by the **second bit of t** — the patterns ind[t mod 4 ∈ {2,3}] (= b₁) and ind[t mod 4 = 3] (= b₁·parity) — in cross-family tie combinations, the **second-bit ties** (the cleanest: the second bit of the k−l channels of families 1 and 2, tied). Extracted at m = 8 and m = 16 with byte-equal structure, the supports doubling exactly as residue classes mod 4: at m = 16 the patterns still factor through t mod 4, never mod 8.

**The unified statement: the deep 2-tower lives entirely at depth mod 4.** The corank's six carry windows and the radical's six second-bit ties are the two faces of one phenomenon — the first Jordan layer above parity — and the measured constancy of the whole anatomy from m = 8 through m = 64 says no deeper layer ever activates. The ledger then explains the walk with no further input: m = 4: 36 − 21 − 9 = **+6** (the windows already exist, the second-bit layer does not yet — at m = 4 the quarter is a single residue and the bit degenerates); m ≥ 8: 36 − 21 − 21 = **−6**. The negative bend is corank inflation and radical inflation together overshooting the baseline — **explained, not just measured.**

A correction carried openly: an earlier session note recorded the 2-adic filtration route as half-dead after a mod-4 layer test captured nothing. The proper coset extraction shows the opposite — the beyond content IS mod-4 structure; the earlier null was an accounting artifact of the layer test. The correction, with its data, is in the campaign acta — the only grave this campaign has ever exhumed.

## 5. THE FIELD RECORD

Squarefree: b(2) = 14 at m = 6, 10, 14 (blind census) joining the sealed (2,22) and (2,26) — five sightings, zero exceptions, **[FIRM]** (the Auditor re-measured m = 6, 10 byte-exact in a second environment). Towers: b(2) = +6, −6, −6, −6, −6 at m = 4, 8, 16, 32, 64 — the deep constant **[FIRM]** (m = 32 re-measured with an independent from-scratch bitset eliminator: rank 342 = 348 − 6), anatomy byte-constant through three full splits. Leak gate: ker(σ) pairs to zero under G at both squarefree cells — the form factors through the shadows at 2; every theorem sentence above was written after that gate, not before. The closing extraction machinery itself was gated against three sealed radical values (7, 21, 16 — two primes, three regimes) before any new object was trusted. Ledger: seven of seven, both parities, all three regimes.

## 6. HONEST LEDGER

**Proven / identified, nothing below:** the two faces of wildness; the universal ledger at seven stations; the fold at both levels with every collision named (radical: four; corank: three, parallelogram ≡ lin₁+lin₂, verified symbolically and by machine); the squarefree anatomy with every radical dimension carried by an explicit identity verified at three kingdoms; the tower anatomy with both inflations identified and the mod-4 depth statement; the mod-4 carry windows hand-verified 16/16; the true mass frame cross-kingdom certified; the leak gate paid.
**Measured [FIRM]:** the two field laws and their anatomies.
**Scope:** odd degrees obey the Bend Theorem; this document is the even half. The *discriminant* of even-degree surfaces (as opposed to the rank profile) is a different invariant and a different campaign — nothing here claims it.

## 7. GRAVEYARD, WITH PRIDE

The cubic even echo (registered in the acta before firing: the 2-tooth should echo ρ(S₂) = 2; measured global survivor 1 ≠ 2 — dead at first firing, falsifier published) · the nine-candidate within-family mass frame (the odd-kingdom control gate bit it at 7/9; its autopsy yielded the true cross-family frame, and the gate it built is now standard equipment) · the half-dead verdict on the 2-adic filtration route — **exhumed**: the only grave this campaign ever reopened, resurrected by the proper coset extraction with the correction recorded · one right-kernel-for-left-kernel script slip, self-caught on dimension reconciliation · one wrong radical convention and one naive coset slice in the closing extraction, both self-caught against the three-seal gate before anything was trusted. *Each grave bought road — and one gave it back.*

## 8. PROVENANCE

Instruments: GRAM_MANOMETER_SURFACE_v4.py (ratified), the packed-bitset F₂ eliminators (towers to n = 12288 in seconds; m = 32 reproduced by a second, independent implementation), the gated shadow-extraction machinery of the closing session (radical = σ(ker G), calibrated against three sealed values before use), and the session extraction scripts (frames, dossiers, window identities). Seals declared before every measurement; odd-kingdom control gates before every mod-2 reading (the campaign's standing lesson, built in); this document written in crossfire by both instances of the dual protocol and merged under the Auditor's responsibility, with cross-review per house rule. All numbers from files.

### References

1. M. Schütt, T. Shioda, R. van Luijk, *Lines on Fermat surfaces.* J. Number Theory **130**:9 (2010), 1939–1963. arXiv:0812.2377. *(The line intersection rules behind the Gram and the shadow map.)*
2. T. Shioda, *Some observations on Jacobi sums.* Adv. Stud. Pure Math. **12** (1987), 119–135. *(The discriminant questions; the even degrees are the half this document enters.)*
3. E. Aljovin, H. Movasati, R. Villaflor, *Integral Hodge conjecture for Fermat varieties.* J. Symbolic Computation **95** (2019), 177–184. arXiv:1711.02628. *(The published cell-by-cell elementary divisors; the campaign's gates.)*

*Companion documents in this repository:* THE WATERMARK THEOREM (the prime-degree discriminant) · THE DOUBLE LADDER THEOREM (the surface structure) · THE SWEET LIE THEOREM (the fourfold rank) · THE BEND THEOREM (the odd teeth; this document is its wild sibling) · CHUCHIPACHI FINDINGS MASTER (the campaign record, graveyards included). **The fifth document of the collection. PMC.**
