# The Bend Theorem
### The power-sum mechanism of the composite profile law — the teeth are where the channels open
Rafael Amichis Luengo · Madrid · tretoef@gmail.com · github.com/tretoef-estrella · 7 June 2026 · Companion to THE_WATERMARK_THEOREM, THE_DOUBLE_LADDER_THEOREM and THE_SWEET_LIE_THEOREM (same repository). Computations: MacBook Air M2, 8 GB RAM, single thread, 25% CPU.

## 0. STATEMENT

Let S_m be the Fermat surface of degree m, and let G be the SSvL line Gram. For a prime p | m, define the **bend constant**

> **b(p) = rank_{F_p}(G) − 12(m−3).**

**Theorem (the Bend).** b(p) depends only on p, through the divisibility (p−1) | k of the pairing channels k ∈ {2, 4}:
- **b(p) = 0 for every prime p ≥ 7** — both channels closed, the profile law runs verbatim;
- **b(5) = 2** — only the quadratic channel k=4 open: the two family-relative polarization radicals die, the global survives;
- **b(3) = 7 = 2 + 3 + 2** — both channels open: two mass radicals, three moment-compatibility radicals, and two polarization radicals die; in every sector the family-relative copies die and the global combinations survive;
- (p = 2, even degree: both channels open and wild — the even half's separate kingdom, outside this document.)

Equivalently: composite-degree profiles obey the prime law per own prime with the corrections #m²-div = 3m−16 + b(p), #m-div = 3m²−24m+59 − 2b(p), and prime-power towers carry the bend as 2b strays (field record below).

## 1. THE OBJECTS

The twelve shadow channels (3 families × 4 pencil directions k, l, k−l, k+l), each a function space on Z/m. The form factors through the shadows at every p | m (leak = 0, measured); the **shadow radical** has generic dimension 18 = 9 (mass) + 6 (moment compatibilities) + 3 (polarizations), all CYCLIC across the family triangle (the hyperbolic SSvL pairing transports each identity to the neighbouring families' channels), with INTEGRAL coefficient frame (entries in {±1, ±2}, certified). The entire radical is polynomial of degree ≤ 2 in t — beyond-degree-2 is zero in every measured kingdom — so the bookkeeping world is finite and complete. **b(p) = 18 − dim(radical mod p).**

## 2. THE MECHANISM — THE PAIRING IS MADE OF POWER SUMS

**Kernel structure (measured 78/78 blocks at m=15, integer level):** every channel-pair kernel is a generalized circulant, K(t,t') = κ(αt + βt' mod m). Consequently the pairing of polynomial patterns t^a × t^b expands as an integer combination of power sums Σ_t t^j with j ≤ a+b ≤ 4. Reduced mod p (p | m, where the polynomial calculus is canonical — see §7), the classical evaluation applies:

> **Σ_{t ∈ F_p} t^j ≡ −1 if (p−1) | j, and ≡ 0 otherwise.**

Channels: linear sector pairs through k=2; polarization sector through k=4. Open channels by prime: p=3 → {2, 4} both (measured row over Z/15: [0,0,1,0,1]); p=5 → {4} only ([0,0,0,0,2]); **p ≥ 7 → none (p−1 ≥ 6 > 4): no polynomial detector can exist, hence b(p) = 0 — the flat law is mechanism-complete, forever.**

## 3. THE THREE SECTOR CHAINS AT p = 3

**(i) Mass −2 [PROVEN, v95].** The complete-Radon mass identity of F₃² (the four pencil slopes exhaust P¹(F₃), and 4 ≡ 1): one all-directions condition per family, 3 candidates − 1 overlap (sum of generic trinity = sum of Radon conditions; union rank 5) = 2 deaths, the dead named: the two cross-family k±l constant singletons.

**(ii) Linear −3 [conditions explicit; k=2 channel].** Death conditions in the integral compat frame: L1−L4+L5+L6 = 0, L2−L4−L5−L6 = 0, L3+L5+L6 = 0; survivors are the cross-family symmetric combinations (cleanest: L5−L6, the F1↔F2 symmetric moment pair). Detector functionals extracted from the annihilator with value-triples (0,2,0)/(0,1,0); the channel is Σt², open only at p=3.

**(iii) Polarization −2 [closed by identity coincidence + k=4 channel].** Mod 3 the polarization pattern (−2,−2,1,1) ≡ (1,1,1,1): the polarization identity and the all-directions quadratic identity are the same identity in char 3 (difference = 3(k²+l²) ≡ 0, literal). Survivor by formula: the global all-family combination; deaths: the two relatives.

## 4. THE FIVE-TOOTH — THE SAME ANIMAL, ONE CHANNEL

The polarization death conditions at p=5 are **identical** to p=3's (P1+P3 = 0, P2−P3 = 0 in the integral frame; identical global survivor (1,−1,−1) = the all-family pattern (2,2,−1,−1)). Every detector catching a polarization at p=5 is PURE quadratic, and all detector value-triples annihilate the survivor exactly. b(5) = 2 is the polarization bite through the only open channel, Σt⁴ — not a separate mechanism. The founding "m=5 exception" of the odd-prime profile law was b(5) biting at its own prime (h₀ = 26 = 24+2).

## 5. THE FLAT LAW, p ≥ 7 — MECHANISM COMPLETE

All power sums Σ(t mod p)^j, 1 ≤ j ≤ 4, vanish identically for p ≥ 7. No pairing channel, no detector, no death: the radical reduces full, b(p) = 0. Field: 7, 11, 13 measured flat in every cell (own towers and as partners) — SEVEN p ≥ 7 sightings itemized from files, zero exceptions.

## 6. THE FIELD RECORD

Profile-level seals 7/7 · blind exponents 26/26 · the bend formula b(p) = h₀ − 12(m−3) exact on FIFTEEN field profiles (squarefree both sides, towers, gates) plus the two founding prime gates · prime-power towers: base-m floors verbatim (m = 9, 25, 27 with 2b strays; m = 49 with zero, the sealed falsifier that survived — 4/4) · the necessary condition **bending requires p | m** PROVEN (no shadow factoring over Z).

## 7. HONEST LEDGER

PROVEN: the p|m necessity; the mass-2 chain; the polarization identity coincidence (symbolic); the flat-law mechanism modulo the kernel expansion's general-m write-up. DEMONSTRATED STRUCTURALLY (measured, certified frames, detectors in hand): the kernel circulant structure (78/78 at m=15 — the general-m proof is the SSvL incidence rules, finite write-up); the linear-3 conditions; the channel table. MEASURED [FIRM]: the field record. The canonicity note: the polynomial calculus on Z/m exists mod p exactly when p | m (moment weights wrap with step carries otherwise) — the teeth are where the structure exists, the second face of the p|m necessity.

## 8. GRAVEYARD, WITH PRIDE

The one-tooth phrase (killed by its own table: b(5)=2, 5∤6) · the shadow-leak hypothesis (leak = 0 measured) · the integral-radical framing (σ(ker_Z G) rank 128 — its autopsy yielded the p|m necessity) · the per-family symbol frame (the true frame is cyclic) · the foreign-prime witnesses at m=15 (non-canonical chop — its autopsy yielded the canonicity note) · "2+2+3" (overlapping filters; corrected 2+3+2) · one Auditor display-slip and one Constructor transpose, both self-caught. Each grave bought road.

## 9. PROVENANCE

Instruments: GRAM_MANOMETER_SURFACE_v4.py (ratified), gandalfsonrie.cpp (double-gated, checkpointed), session extraction scripts (radical formulas, symbol frames, detector functionals, kernel census). All numbers from files; seals before measurement; cross-review before any repo upload per house protocol. PMC.

## References

1. M. Schütt, T. Shioda, R. van Luijk, *Lines on Fermat surfaces.* J. Number Theory **130**:9 (2010), 1939–1963. arXiv:0812.2377. (The line intersection rules behind the Gram.)
2. T. Shioda, *Some observations on Jacobi sums.* Advanced Studies in Pure Mathematics **12** (1987), 119–135. (The discriminant questions this campaign's surface theorems answer; the composite and even degrees are the territory this document's mechanism opens.)
3. E. Aljovin, H. Movasati, R. Villaflor, *Integral Hodge conjecture for Fermat varieties.* J. Symbolic Computation **95** (2019), 177–184. arXiv:1711.02628. (The published cell-by-cell elementary divisors; the campaign's gates.)

Companion documents in this repository: THE_WATERMARK_THEOREM (the prime-degree discriminant, proven) · THE_DOUBLE_LADDER_THEOREM (the surface structure) · THE_SWEET_LIE_THEOREM (the fourfold rank) · CHUCHIPACHI_FINDINGS_MASTER (the campaign record, graveyards included).
