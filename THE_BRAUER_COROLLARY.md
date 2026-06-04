# Corollaries of the Watermark Theorem

### The transcendental lattice and the Brauer group of Fermat surfaces of prime degree

**Rafael Amichis Luengo** · Madrid · [tretoef@gmail.com](mailto:tretoef@gmail.com) · [github.com/tretoef-estrella](https://github.com/tretoef-estrella)

**4 June 2026** · Version 1.0 · Companion to *The Watermark Theorem* [T]

---

## Abstract

The Watermark Theorem [T] gives, for every prime m ≥ 5, the exact discriminant of the Néron–Severi lattice of the complex Fermat surface S_m: |disc NS(S_m)| = m^{3(m−3)²}. We record here what falls out immediately. Corollary 1, fully rigorous and five lines long, computes the discriminant of the transcendental lattice: |disc T_m| = m^{3(m−3)²}, on rank (m−1)(m−3)². Corollary 2 pins the order of the discriminant group NS*/NS. Corollary 3 assembles the closed-form recipe for the order of the Brauer group of the good reductions of S_m over finite fields via the Artin–Tate formula — a formula whose every ingredient (the Frobenius eigenvalues, classically the Jacobi sums; the Néron–Severi discriminant, now the Theorem; the elementary q-powers) is explicit. The status of each statement — proven here, classical input, or evaluation left per (q, m) — is labelled line by line.

---

## 1. Setup

S_m ⊂ P³ is the Fermat surface of prime degree m ≥ 5. H²(S_m, Z) is unimodular (Poincaré duality) and torsion-free (S_m is a smooth hypersurface in P³, hence simply connected), of rank b₂ = m³ − 4m² + 6m − 2. NS = NS(S_m) is a primitive sublattice (it is the intersection of H² with H^{1,1}, hence saturated), of rank ρ = 3(m−1)(m−2) + 1 [Aoki–Shioda; Schütt–Shioda–van Luijk], and the Watermark Theorem gives |disc NS| = m^{3(m−3)²}. The transcendental lattice is T_m := NS^⊥ in H²(S_m, Z).

## 2. Corollary 1 — the transcendental lattice

> **|disc T_m| = m^{3(m−3)²}, and rank T_m = (m−1)(m−3)².**

**Proof.** For a primitive sublattice N of a unimodular lattice U with orthogonal complement T, the discriminant groups N*/N and T*/T are canonically isomorphic (anti-isometrically, by standard lattice theory: gluing inside U). Hence |disc T_m| = |disc NS| = m^{3(m−3)²} by the Theorem. The rank: b₂ − ρ = (m³ − 4m² + 6m − 2) − (3m² − 9m + 7) = m³ − 7m² + 15m − 9 = (m−1)(m−3)². ∎

*Checks:* m = 5: b₂ = 53, ρ = 37, rank T = 16 = 4·2², disc 5¹². m = 7: b₂ = 187, ρ = 91, rank T = 96 = 6·4², disc 7⁴⁸. m = 11: rank T = 640, disc 11¹⁹².

**Remark.** The exponent 3(m−3)² is three times the square of m−3 — and (m−3)², in Shioda's framework, counts a basic family of transcendental character orbits. Corollary 1 places that square on the transcendental side of the unimodular wall with a proof, where [7] could place it only conjecturally.

## 3. Corollary 2 — the discriminant group

> **|NS*/NS| = |T*/T| = m^{3(m−3)²}; both groups are m-groups.**

**Proof.** The order is the discriminant; the group is killed by a power of m since the discriminant is. ∎

The finer structure (the elementary divisors) is *measured, not proven*: the campaign's instrument rail shows the nonzero elementary-divisor profile of the line Gram coincides with the rows tabulated by Aljovin–Movasati–Villaflor for low degree (e.g. 5¹⁰·25 at m = 5; 7³⁸·49⁵ at m = 7), and the campaign's profile law (#(m²-divisors) = 3m − 16 for prime m ≥ 7) fits all published rows — catalogued in [W], conjectural beyond the measured range.

## 4. Corollary 3 — the Brauer group over finite fields: the closed recipe

Fix a prime power q = p^r with p ∤ m, and let X = S_m ⊗ F_q be the (smooth) reduction. The following inputs are classical:

- **(Tate for Fermat surfaces.)** The Tate conjecture holds for Fermat surfaces over finite fields (Tate's original cases and the inductive structure of Shioda–Katsura, *On Fermat varieties*, Tôhoku Math. J. 31 (1979); see also Tate, *Algebraic cycles and poles of zeta-functions*, 1965). Consequently Br(X) is finite and the Artin–Tate formula holds (Tate, Bourbaki 1966; Milne, Ann. of Math. 102 (1975)).
- **(Frobenius eigenvalues = Jacobi sums.)** The eigenvalues of Frobenius on H²_ét(X̄, Q_ℓ) are q times roots of unity on the algebraic part and the Jacobi-sum characters j(χ) on the transcendental part (Weil, 1949) — explicitly computable for each (q, m).
- **(Torsion.)** NS(X) is torsion-free for Fermat surfaces.

**The Artin–Tate formula** (in Milne's normalization) then reads, for X with b₁ = 0:

> **lim_{s→1} P₂(X, q^{−s}) / (1 − q^{1−s})^{ρ(X)} = ± |Br(X)| · |disc NS(X)| / ( q^{α(X)} · |NS(X)_tors|² ),  α(X) = χ(O_X) − 1,**

where P₂ is the degree-b₂ Frobenius factor of the zeta function and ρ the Néron–Severi rank over F_q. The Brauer order is thus the special value of P₂ at s = 1 divided by the Néron–Severi discriminant, up to the explicit q-power; for Fermat surfaces NS is torsion-free. The precise statement used is the Artin–Tate formula as established in Milne (1975); we do not restate its proof.

> **Corollary 3.** *For each q ≡ 1 (mod m) such that NS(X̄) is defined over F_q (full descent of the lines), the order |Br(X)| is given in closed form by the Artin–Tate special value with |disc NS(X)| = m^{3(m−3)²} supplied by the Watermark Theorem, the transcendental eigenvalues supplied by Weil's Jacobi sums, and χ(O_X) = 1 + p_g = 1 + (m−1)(m−2)(m−3)/6. Every ingredient is explicit; the evaluation is finite arithmetic per (q, m).*

**Status, line by line.** *Proven here:* the discriminant input (the Theorem) and the rank/holomorphic-genus arithmetic. *Classical, cited:* Tate for Fermat surfaces; the Artin–Tate formula; Weil's eigenvalue computation; the squareness of |Br| (Milne for q odd, completed in later literature). *Left explicit, per case:* the descent condition (q ≡ 1 mod m with the lines rational over F_q — under which NS(X) = NS(X̄) and disc NS(X) is the complex value), and the numerical evaluation of the Jacobi-sum product. No Brauer order is asserted for any specific (q, m) in this note; what is asserted is that the recipe is now closed — before the Theorem, its discriminant denominator was conjectural for every prime m beyond the verified range.

## 5. What is *not* claimed

The structure of Br(X) (beyond its order through the recipe), the supersingular cases p with special congruences, odd composite m, and the even half of the Watermark Law are outside this note. The complex (cohomological) Brauer group of S_m has divisible part of corank rank T_m = (m−1)(m−3)²; its torsion-theoretic fine structure is not addressed here.

## References

[T] R. Amichis Luengo, *The Watermark Theorem* (this repository: THE_WATERMARK_THEOREM.md / .pdf).
[W] *The Watermark Law* (this repository: THE_WATERMARK_LAW.md).
1. T. Shioda, *Some observations on Jacobi sums.* Adv. Stud. Pure Math. **12** (1987), 119–135.
2. M. Schütt, T. Shioda, R. van Luijk, *Lines on Fermat surfaces.* J. Number Theory **130**:9 (2010), 1939–1963.
3. N. Aoki, T. Shioda, *Generators of the Néron–Severi group of a Fermat surface.* Progr. Math. **35** (1983), 1–12.
4. T. Shioda, T. Katsura, *On Fermat varieties.* Tôhoku Math. J. **31** (1979), 97–115.
5. J. Tate, *Algebraic cycles and poles of zeta-functions.* In: Arithmetical Algebraic Geometry, Harper & Row (1965).
6. J. Tate, *On the conjectures of Birch and Swinnerton-Dyer and a geometric analog.* Séminaire Bourbaki **306** (1966).
7. J. S. Milne, *On a conjecture of Artin and Tate.* Ann. of Math. **102** (1975), 517–533.
8. A. Weil, *Numbers of solutions of equations in finite fields.* Bull. Amer. Math. Soc. **55** (1949), 497–508.

---

*Corollary 1 is a complete proof. Corollary 3 is a closed recipe with classical inputs cited and every conditional stated. Nothing here asks for trust — it asks to be checked.*
