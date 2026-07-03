# THE ODD SYMMETRIC THEOREM
**A standalone result of Operación Glotón / The Sofa Theorem campaign.**
*Constructor: Induráin · Audited cold by Blas (four independent verifications) · Architect: Rafael Amichis Luengo · Madrid, 3 July 2026.*

---

## Statement

Work over a field 𝕜 of characteristic ≠ 2 (the campaign uses 𝕜 = F₃; the theorem is characteristic-free away from 2). Let S = 𝕜[s₀, …, s₅]. For each of the fifteen perfect matchings J of the six indices, let

  I_J := ( s_a + s_b : {a,b} ∈ J ) ⊂ S,

the ideal of the 3-plane V_J on which the variables pair off with opposite signs. Let e_k = e_k(s₀,…,s₅) denote the elementary symmetric polynomials.

> **Theorem (Odd Symmetric).**  ∩_{J} I_J = (e₁, e₃, e₅).
> Moreover (e₁, e₃, e₅) is a regular sequence; the quotient S/(e₁,e₃,e₅) is a reduced complete intersection of dimension 3 and degree 15, whose irreducible components are exactly the fifteen planes V_J.

No even elementary symmetric polynomial lies in any I_J (e₂ restricts to −(x²+y²+z²) ≠ 0 on every V_J), so the odd ideal is exact — neither generator can be dropped, none can be added.

## Proof

**Step 1 (⊇: the odd symmetrics vanish on every pairing plane).** Fix J and parametrize V_J by (x, −x, y, −y, z, −z). For odd k, split the k-subsets of the six slots by how they meet the three pairs. A subset containing a full pair contributes the factor x·(−x) times a term whose complementary part is summed symmetrically over the remaining slots; grouping these by the complement, each group's sum is the elementary symmetric of {y, −y, z, −z}-type sets of odd residual size, and pairs of terms differing by one sign-flip cancel. A subset meeting each chosen pair in exactly one slot carries an odd number of sign choices in total, and the involution flipping the sign of one fixed selected pair matches terms in cancelling couples. Concretely: e₁ ↦ x − x + y − y + z − z = 0; e₃ ↦ 0 and e₅ ↦ 0 by the same cancellation (for e₅, the leave-one-out products come in ± pairs). Hence e₁, e₃, e₅ ∈ I_J for all J, i.e. (e₁,e₃,e₅) ⊆ ∩ I_J.

**Step 2 (the varieties agree).** Let s = (s₀,…,s₅) ∈ 𝕜̄⁶ satisfy e₁(s) = e₃(s) = e₅(s) = 0. Then

  ∏ᵢ (t − sᵢ) = t⁶ + e₂t⁴ + e₄t² + e₆

is a polynomial in t². Since char 𝕜 ≠ 2, its root multiset is invariant under t ↦ −t, and the multiplicity of the root 0 is even. Therefore the multiset {s₀,…,s₅} has the form {α, −α, β, −β, γ, −γ}, and one may choose a perfect matching J of the indices pairing each value with an opposite one: s lies on V_J. Hence V(e₁,e₃,e₅) = ⋃_J V_J set-theoretically.

**Step 3 (regular sequence, degree, reducedness).** By Step 2 the variety of the 3-generated ideal (e₁,e₃,e₅) has dimension 3, so the ideal has height 3 and e₁, e₃, e₅ is a regular sequence. The quotient is a complete intersection, hence Cohen–Macaulay and unmixed, of degree 1·3·5 = 15 by Bézout. Its support consists of the fifteen pairwise-distinct linear 3-planes V_J, each of degree 1; unmixedness forces every component to appear, and the degree count 15 = Σ (multiplicities) over fifteen components forces every multiplicity to equal 1. A generically reduced Cohen–Macaulay scheme (Serre's R₀ + S₁) is reduced, so (e₁,e₃,e₅) is a radical ideal. Consequently

  (e₁, e₃, e₅) = I( ⋃_J V_J ) = ∩_J I_J. ∎

## Remarks

1. **Numerical confirmation.** Over F₃ the Hilbert functions of both sides agree in degrees 1–7: 1, 6, 22, 61, 142, 292, 547 (probe log `PROBE_V57_ODD_SYMMETRIC_v1.log`; per-leg memberships of e₃, e₅ verified for all fifteen matchings). The identity itself is proven for all degrees by the argument above and carries no parameters.
2. **Symmetry.** Both sides are S₆-stable; the fifteen matchings form a single S₆-orbit with stabilizer of order 48, and the theorem identifies the ideal of that orbit of 3-planes with the span of the odd half of the fundamental invariants — a complete intersection presentation of a subspace arrangement, with Bézout number equal to the orbit size.
3. **Frobenius compatibility (char 3).** e_k(s)³ = e_k(s³): in characteristic 3 the elementary symmetric polynomials commute with the Frobenius endomorphism, since cubing is additive. This is the property that makes the theorem the correct closed form of the campaign's bone: the object is stable under the very map that generates the tower.
4. **Role in the campaign.** With m_v = (s₀^{3^v}, …, s₅^{3^v}), the Degtyarev–Shimada saturation statement for the Fermat tower is equivalent to ∩_J (I_J + m_v) = (e₁,e₃,e₅) + m_v for all v. The theorem above is the m-free core of that statement; the tower inclusion is treated in the campaign documents (V58).

*Cera carnauba, perfume Chanel.* — **Induráin (Constructor)**
