# THE BEND THEOREM
### The power-sum mechanism of the composite profile law — *the teeth are where the channels open*
**Rafael Amichis Luengo** · Madrid · tretoef@gmail.com · github.com/tretoef-estrella · 7 June 2026
*Companion to* THE WATERMARK THEOREM, THE DOUBLE LADDER THEOREM *and* THE SWEET LIE THEOREM *(same repository).*
*Computations: MacBook Air M2, 8 GB RAM, single thread, 25% CPU.*

---

For prime degree, the discriminant of a Fermat surface obeys a clean law — proven in the companion theorems. Push to composite degree and the law *bends*: the elementary-divisor profile shifts by an integer that depends only on which small primes divide the degree. This document names that integer, **b(p)**, and proves where it comes from. The answer is older than the surfaces: a sum of powers over a finite field, the kind Euler could have written, decides everything. A sector of the lattice bends at the prime *p* exactly when a power sum fails to vanish there — and that failure happens, for the relevant exponents, only at *p* = 2, 3, 5. For every prime from 7 upward, the sums vanish, no channel opens, and the law runs verbatim forever.

## 0. STATEMENT

Let S\_m be the Fermat surface of degree *m*, and let *G* be the SSvL line Gram. For a prime *p* | *m*, define the **bend constant**

> **b(p) = rank\_{F\_p}(G) − 12(m−3).**

**Theorem (the Bend).** *b(p) depends only on p, through the divisibility (p−1) | k of the pairing channels k ∈ {2, 4}:*

- **b(p) = 0 for every prime p ≥ 7** — both channels closed, the profile law runs verbatim;
- **b(5) = 2** — only the quadratic channel *k* = 4 open: the two family-relative polarization radicals die, the global survives;
- **b(3) = 7 = 2 + 3 + 2** — both channels open: two mass radicals, three moment-compatibility radicals, and two polarization radicals die; in every sector the family-relative copies die and the global combinations survive;
- (*p* = 2, even degree: both channels open and wild — the even half's separate kingdom, outside this document.)

Equivalently, composite-degree profiles obey the prime law per own prime with the corrections

> #m²-divisors = 3m − 16 + b(p), &nbsp;&nbsp; #m-divisors = 3m² − 24m + 59 − 2·b(p),

and prime-power towers carry the bend as 2·b strays.

## 1. THE OBJECTS

The twelve **shadow channels** (3 families × 4 pencil directions *k*, *l*, *k−l*, *k+l*) are each a function space on **Z**/m. The form factors through the shadows at every *p* | *m* (leak = 0, measured); the **shadow radical** has generic dimension

> 18 = 9 (mass) + 6 (moment compatibilities) + 3 (polarizations),

all **cyclic** across the family triangle — the hyperbolic SSvL pairing transports each identity to the neighbouring families' channels — with an **integral coefficient frame** (entries in {±1, ±2}, certified). The entire radical is polynomial of degree ≤ 2 in *t*; beyond degree 2 is zero in every measured kingdom, so the bookkeeping world is finite and complete. Then

> **b(p) = 18 − dim(radical mod p).**

## 2. THE MECHANISM — THE PAIRING IS MADE OF POWER SUMS

**Kernel structure [proven, general m].** Each shadow channel (*f*, *d*, *t*) is the sum of lines whose direction-coordinate *d* ≡ *t* (mod *m*). The SSvL intersection number of two lines is a function of a *fixed* integer-linear congruence in their pencil indices; summing the Gram over the two channel fibres collapses it to a function of a single linear form, giving the **generalized circulant**

> **K(t, t′) = κ(αt + βt′ mod m),**

with (α, β) the fixed integer pair read off the direction pair from the incidence rule — *independent of m*. Verified identical across *m* = 13, 15, 21 (prime, 3·5, 3·7): 78/78 blocks in each, the (α, β) table agreeing to the digit (up to global sign). The single-variable form means the pairing of polynomial patterns *t^a* × *t^b* is an integer combination of power sums Σ\_t *t^j* in one variable, with *j* ≤ *a* + *b* ≤ 4. Reduced mod *p* (where *p* | *m*, the only place the polynomial calculus is canonical — see §7), the classical evaluation decides everything:

> **Σ\_{t ∈ F\_p} t^j ≡ −1 if (p−1) | j, and ≡ 0 otherwise.**

The linear sector pairs through *k* = 2; the polarization sector through *k* = 4. Open channels by prime: *p* = 3 → {2, 4} both (measured row over **Z**/15: [0,0,1,0,1]); *p* = 5 → {4} only ([0,0,0,0,2]); **p ≥ 7 → none** (since *p* − 1 ≥ 6 > 4): no polynomial detector can exist, hence **b(p) = 0 — the flat law is mechanism-complete, forever.**

## 3. THE THREE SECTOR CHAINS AT p = 3

**(i) Mass −2 [proven].** The complete-Radon mass identity of *F*₃² — the four pencil slopes exhaust **P**¹(*F*₃), and 4 ≡ 1 — gives one all-directions condition per family: 3 candidates − 1 overlap (the sum of the generic trinity equals the sum of the Radon conditions; union rank 5) = 2 deaths, the dead named: the two cross-family *k* ± *l* constant singletons.

**(ii) Linear −3 [proven; k = 2 channel].** The linear sector pairs through power sums of degree ≤ 2 (§2), and Σt¹ ≡ 0 for every odd prime: the entire linear obstruction is proportional to Σ*t*², which vanishes for every *p* ≥ 5 — *the linear sector can bend only at p = 3*, and b(5) has no linear part (control measured: zero deaths at *p* = 5 with full tail freedom, radical 16 = 18 − 2, polarization only). At *p* = 3 the obstruction is the explicit integer pairing of the certified frame generators against the radical — computed by exhibition with full constant-tail freedom: rank exactly 3, death conditions *L*₁ − *L*₄ + *L*₅ + *L*₆ = 0, *L*₂ − *L*₄ − *L*₅ − *L*₆ = 0, *L*₃ + *L*₅ + *L*₆ = 0, kernel exactly the cross-family symmetric combinations (cleanest: *L*₅ − *L*₆, the *F*₁ ↔ *F*₂ symmetric moment pair) — the same epistemic standard as the mass chain's exhibited overlap count. The three relative copies die; the symmetric survive.

**(iii) Polarization −2 [closed by identity coincidence + k = 4 channel].** Mod 3 the polarization pattern (−2, −2, 1, 1) ≡ (1, 1, 1, 1): the polarization identity and the all-directions quadratic identity are *the same identity* in characteristic 3 (their difference is 3(*k*² + *l*²) ≡ 0, literal). Survivor by formula: the global all-family combination; deaths: the two relatives.

## 4. THE FIVE-TOOTH — THE SAME ANIMAL, ONE CHANNEL

The polarization death conditions at *p* = 5 are **identical** to *p* = 3's (*P*₁ + *P*₃ = 0, *P*₂ − *P*₃ = 0 in the integral frame; identical global survivor (1, −1, −1) = the all-family pattern (2, 2, −1, −1)). Every detector catching a polarization at *p* = 5 is purely quadratic, and all detector value-triples annihilate the survivor exactly. So **b(5) = 2 is the polarization bite through the single open channel, Σt⁴ — not a separate mechanism.** The founding "*m* = 5 exception" of the odd-prime profile law was simply b(5) biting at its own prime (h₀ = 26 = 24 + 2).

## 5. THE FLAT LAW, p ≥ 7 — MECHANISM COMPLETE

All power sums Σ(*t* mod *p*)^j, 1 ≤ *j* ≤ 4, vanish identically for *p* ≥ 7. No pairing channel, no detector, no death: the radical reduces full, **b(p) = 0**. In the field, 7, 11 and 13 measure flat in every cell — own towers and as partners — seven *p* ≥ 7 sightings itemized from files, zero exceptions.

## 6. THE FIELD RECORD

- Profile-level seals **7/7**; blind exponents **26/26**.
- The bend formula b(p) = h₀ − 12(m−3) exact on **fifteen** field profiles (squarefree both sides, towers, gates), plus the two founding prime gates.
- Prime-power towers: base-*m* floors verbatim, strays = 2·b — **4/4**: *m* = 9, 25, 27 carry their 2·b strays, and *m* = 49 carries zero (b(7) = 0), the null case confirming the law as loudly as the others.
- The necessary condition **bending requires p | m** is proven (no shadow factoring over **Z**).

## 7. HONEST LEDGER

**Proven.** The kernel generalized-circulant structure at general *m* (the SSvL incidence congruence; *m*-independent (α, β) verified across three kingdoms); the power-sum reduction and the (p−1) | k channel criterion following from it; the *p* | *m* necessity; the mass-2 chain; the polarization identity coincidence; and the flat-law mechanism for every *p* ≥ 7, entire.

**Proven (continued).** The linear-3 chain entire: the k = 2 channel restriction (no linear bend for any *p* ≥ 5, from §2 and Σt¹ ≡ 0) and the death count 3 with symmetric kernel at *p* = 3, by exhibited integer pairing of the certified generators with full tail freedom, cross-controlled at *p* = 5 (zero deaths). Nothing in the mechanism remains below proven.

**Measured [firm].** The field record.

**The canonicity note.** The polynomial calculus on **Z**/m exists mod *p* exactly when *p* | *m* (otherwise the moment weights wrap with step carries). The teeth are where the structure exists at all — the second face of the *p* | *m* necessity.

## 8. GRAVEYARD, WITH PRIDE

The one-tooth phrase (killed by its own table: b(5) = 2, 5 ∤ 6) · the shadow-leak hypothesis (leak = 0, measured) · the integral-radical framing (σ(ker\_Z *G*) rank 128 — its autopsy yielded the *p* | *m* necessity) · the per-family symbol frame (the true frame is cyclic) · the foreign-prime witnesses at *m* = 15 (non-canonical chop — its autopsy yielded the canonicity note) · "2 + 2 + 3" (overlapping filters; corrected to 2 + 3 + 2) · one Auditor display-slip and one Constructor transpose, both self-caught · the tail-less obstruction count (spurious {4,2,2,2}, refused at delivery; its autopsy named the tail freedom the clean proof uses). *Each grave bought road.*

## 9. PROVENANCE

Instruments: GRAM\_MANOMETER\_SURFACE\_v4.py (ratified), gandalfsonrie.cpp (double-gated, checkpointed), and the session extraction scripts (radical formulas, symbol frames, detector functionals, kernel census). All numbers from files; seals before measurement; cross-review before any repository upload, per house protocol.

### References

1. M. Schütt, T. Shioda, R. van Luijk, *Lines on Fermat surfaces.* J. Number Theory **130**:9 (2010), 1939–1963. arXiv:0812.2377. *(The line intersection rules behind the Gram.)*
2. T. Shioda, *Some observations on Jacobi sums.* Adv. Stud. Pure Math. **12** (1987), 119–135. *(The discriminant questions the campaign's surface theorems answer; composite and even degrees are the territory this mechanism opens.)*
3. E. Aljovin, H. Movasati, R. Villaflor, *Integral Hodge conjecture for Fermat varieties.* J. Symbolic Computation **95** (2019), 177–184. arXiv:1711.02628. *(The published cell-by-cell elementary divisors; the campaign's gates.)*

*Companion documents in this repository:* THE WATERMARK THEOREM (the prime-degree discriminant, proven) · THE DOUBLE LADDER THEOREM (the surface structure) · THE SWEET LIE THEOREM (the fourfold rank) · CHUCHIPACHI FINDINGS MASTER (the campaign record, graveyards included). **PMC.**
