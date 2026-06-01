# The within-pair functor of a Fermat CRT block

### A symmetric-square law for the within-pair survivor count, its proof for odd characteristic, and the localization of the characteristic-two obstruction to the generic swap torsion

**Rafael Amichis Luengo** — Madrid · [github.com/tretoef-estrella](https://github.com/tretoef-estrella)
**Version 1.0 · 1 June 2026**

> Companion to [THE_LOCALIZATION_THEOREM.md](THE_LOCALIZATION_THEOREM.md). Localization proves *where* any torsion of a Fermat cell must live (one CRT block); this note opens the *interior* of the all-A pair block of that splitting, identifies the within-pair survivor as a symmetric square, proves the coupled law in odd characteristic, and shows the characteristic-two obstruction is the generic torsion of the swap — closing the within-pair class layer as a site for a Fermat-specific counterexample.

---

## Abstract

This note determines the within-pair survivor count of an all-`A` pair block in the Chinese-Remainder splitting of a Fermat cell, the combinatorial object that controls the `F_p`-isomorphism question on the coupled flank of the author's computational campaign. Three results are established.

1. The survivor count factorizes as `(within-class) × (across-class)`, with the within-class factor always free (`c²`) and the across-class factor either the full square `(p^v−1)²` (the **free** regime) or the triangle `T(p^v−1) = (p^v−1)p^v/2` (the **coupled** regime); the resulting **quotient law** `coupled/free = p^v / (2(p^v−1))` is *derived, not fitted*, and its degeneration `coupled = free` occurs exactly at `p^v = 2`.
2. The coupled object is identified **functorially**: with `V = F_p^{p^v−1}` the live-class space, the coupled survivor is `dim(Sym²V)·c²` and the free survivor is `dim(V⊗V)·c²`, so the entire free/coupled distinction is the collapse of the tensor square to the symmetric square on the class layer; the triangular index set is exactly the canonical basis of `Sym²V`, which resolves why the triangle survives a full-square support.
3. The **realization** question — does the relevant symmetrization map surject onto `Sym²V` — is answered: it is **surjective in odd characteristic** (so the coupled identity is a theorem there), and in **characteristic two it falls short by exactly `p^v−1`** dimensions, the cokernel being `(Z/2)^{p^v−1}`. This cokernel is shown to be the **generic** torsion of the swap involution on `V⊗V`, depending only on `dim V` and not on the Fermat data; hence the within-pair class layer is **closed** as a site for a Fermat-specific torsion counterexample.

Every numerical statement is reproduced byte-exact by a self-contained verifier across the cells named in the text. The torsion counterexample has not been found; this note closes one candidate layer with data and proves the coupled law for odd characteristic.

---

## 1. Setting and the object

Fix a Fermat cell `(n,m)` with `n` even and a prime `p | m`, and write `m = p^v · m'` with `p ∤ m'`, so `p^v` is the `p`-part of `m`. Over `F_p` the relevant cyclotomic quotient factors into a `(t−1)`-primary part `A` and a coprime cofactor `B`; the Chinese Remainder Theorem splits the per-variable ring as `A × B`, and tensoring over the variables decomposes the cohomology module into CRT blocks. The localization of torsion to a single such block is proven separately in [THE_LOCALIZATION_THEOREM.md](THE_LOCALIZATION_THEOREM.md). This note concerns the interior of one block: the **all-`A` pair block**, in which two distinguished variables — a **pair** — both lie in the `A`-factor.

The single-variable signature is governed by the Frobenius identity `(t−1)^{p^v} = t^{p^v} − 1` over `F_p`: the `A`-idempotent annihilates exactly the monomials whose exponent is `≡ −1 (mod p^v)`. The surviving exponents form the signature set

```
S = S(m, p^v) = { k ∈ {0,…,m−1} : k mod p^v ≠ p^v − 1 }.
```

The **within-pair survivor count** is the number of distinct exponent pairs the two `A`-variables realize. It takes one of two values:

```
free(m,p^v)     = |S|²
triangle(m,p^v) = #{ (a,b) ∈ S×S : (b mod p^v) ≤ (a mod p^v) }.
```

Measured anchors from the reduction engine: `(4,6)` at `p=3 → 16` (free); `(4,12)` at `p=2 → 54` (coupled).

## 2. The factorization and the quotient law

**Lemma 1 (residue-class structure of `S`).** `S` is the disjoint union of exactly `p^v−1` residue classes mod `p^v` — namely `0,1,…,p^v−2` — each of cardinality `c = m/p^v`; the class `p^v−1` is absent. In particular `|S| = (p^v−1)·c`.

*Proof.* `k ∈ S` iff `k mod p^v ∈ {0,…,p^v−2}`; each such residue is attained by exactly `m/p^v = c` values of `k`, since `p^v | m`. ∎

**Theorem 1 (within-pair factorization).** Writing each surviving exponent by its residue class `r ∈ {0,…,p^v−2}` and its within-class position, the survivor count factorizes as within-class × across-class, the within-class factor always `c²`, and

```
free     = c² · (p^v−1)²
triangle = c² · T(p^v−1) = c² · (p^v−1)p^v/2,   T(k) = k(k+1)/2.
```

*Proof.* By Lemma 1 a pair `(a,b)` is determined by the residue pair `(r_a,r_b)` and, independently, by `c` within-class positions for each — a factor `c²` with no `a`–`b` constraint. Free allows all `(p^v−1)²` residue pairs. The triangle splits on equality: `r_b < r_a` gives `C(p^v−1,2)` residue pairs, `r_b = r_a` gives `p^v−1`, each contributing `c²`:

```
triangle = c²·[ (p^v−1)(p^v−2)/2 + (p^v−1) ] = c²·(p^v−1)·[ (p^v−2)/2 + 1 ] = c²·(p^v−1)p^v/2. ∎
```

**Corollary 1 (quotient law).** `triangle/free = p^v / (2(p^v−1))`. The within-class factor `c²` cancels because it is identical in both regimes; the quotient is a pure function of the thickness `p^v`.

**Corollary 2 (degeneration).** `triangle = free ⟺ p^v = 2` — equivalently a single live class, where triangle and square coincide. The degeneration is governed by `p^v = 2`, **not** by the parity of `p`: the cell `(4,8)` at `p=2` has `p^v = 8` and is **coupled** (`T(7) = 28 ≠ 49`).

**Remark.** The earlier reading — that `ρ` imposes the order `r_b ≤ r_a` on the support — is **false**: `ρ`'s support reaches the *full* square of live-class pairs in every measured cell (e.g. `(4,18)` at `p=3` reaches all 64 while the triangle has 36). The triangle is not a constraint on which monomials appear; it is what survives. This motivates §3.

## 3. The functorial identification

Let `V = F_p^{p^v−1}` (live-class space), `W = F_p^c` (within-class space).

**Theorem 2 (functorial identification).** The within-pair survivor count is the dimension of a functor of `V`, tensored with the free within-class factor:

```
free    = dim(V⊗V)·c² = (p^v−1)²·c²
coupled = dim(Sym²V)·c² = T(p^v−1)·c².
```

The free/coupled distinction is the single statement that, on the class layer, the tensor square `V⊗V` is replaced by the symmetric square `Sym²V`. The triangular index set `{(a,b): b ≤ a}` is exactly the canonical basis of `Sym²V` (the size-two multisets) — which is why the triangle survives a full-square support.

**Corollary 3.** The degeneration `p^v = 2` is the geometric fact `Sym²(F_p¹) = F_p¹ = F_p¹⊗F_p¹`. The decomposition

```
V⊗V = Sym²V ⊕ Λ²V,    (p^v−1)² = (p^v−1)p^v/2 + (p^v−1)(p^v−2)/2,
```

holds over `Z` and over `F_p` for `p` odd; the coupling keeps `Sym²V` and discards `Λ²V`.

## 4. The realization question, and the characteristic-two obstruction

The symmetrization in play is the swap `τ` of the two pair variables: interchanging the two `A`-variables *is* `τ` on `V⊗V`, and `ρ` contributes only *which* classes are live, not a separate symmetrizer. Realization is the surjectivity of `σ = I+τ` onto `Sym²V`.

**Theorem 3 (realization).** Let `σ = I+τ` on `V⊗V`, `V = F_p^{p^v−1}`.
- *(i)* For `p` odd, `im(σ) = Sym²V` over `F_p`: the symmetrization is **surjective**, and the coupled identity `coupled = dim(Sym²V)·c²` holds as an `F_p`-statement.
- *(ii)* For `p = 2`, `im(σ)` falls short of `Sym²V` by exactly `p^v−1` dimensions; the integral cokernel of `σ` carries torsion `(Z/2)^{p^v−1}`, concentrated on the diagonal.

*Proof (computational, byte-exact).* Over `Z`, `σ(e_i⊗e_j) = e_i⊗e_j + e_j⊗e_i`; off-diagonal symmetric vectors receive multiplicity one, diagonal vectors `e_i⊗e_i` multiplicity two. The Smith normal form over `Z` has exactly `p^v−1` elementary divisors equal to `2` (one per diagonal class), the rest units. Mod `p`: for `p` odd the `2`'s are units (rank unchanged, `im(σ) = Sym²V`); for `p = 2` the `p^v−1` diagonal entries are divisible by `p` (rank drops by `p^v−1`, cokernel acquires `(Z/2)^{p^v−1}`). Verified by Smith normal form and independently by the `F_p`-versus-`Q` rank drop of `σ`, §5. ∎

**Theorem 4 (the obstruction is generic).** The cokernel torsion `(Z/2)^{p^v−1}` of Theorem 3(ii) depends only on `dim V = p^v−1`, not on the Fermat data: for any `F_p`-space `V` of dimension `n`, the cokernel of `I+τ` over `Z` carries `(Z/2)^n` in characteristic two — the diagonal where symmetric and alternating squares coincide mod 2. Fermat inherits this torsion exactly, adding and removing not a single factor of `2`.

*Proof.* The argument of Theorem 3 uses only the swap `τ` and the multiplicity-two diagonal; no Fermat input enters, so the count is `n = dim V` for generic `V`, and `ρ` enters only through `dim V = p^v−1`. Verified byte-exact for plain `V` of dimensions 1, 2, 3, 4, 7. ∎

**Corollary 4 (the two threads are one).** The realization question (is `σ` surjective onto `Sym²V`?) and the torsion question (does char 2 carry torsion in the `Sym²/Λ²` layer?) are the same question: `σ` surjective `⟺ coker(σ) = 0 ⟺ p` odd, and in char 2, `coker(σ) = (Z/2)^{p^v−1}` is the generic swap torsion. They converge byte-exact.

## 5. Significance and scope

**What is proved.** The within-pair survivor count is `Sym²V` tensored with the free within-class factor (Theorem 2); the realization `im(σ) = Sym²V` is a theorem in odd characteristic (Theorem 3(i)); the characteristic-two shortfall is the **generic** swap torsion `(Z/2)^{p^v−1}`, not Fermat-specific (Theorems 3(ii), 4).

**What this closes for the swan hunt.** The within-pair class layer is **closed** as a site for a Fermat-specific integral torsion counterexample: its only characteristic-two torsion is the universal swap torsion, identical for Fermat and for a generic space of the same dimension. This closure is by Smith normal form — the correct tool, since torsion is detected by elementary divisors and rank drop, **never** by equality of `F_p`- and `Q`-dimensions of a subspace.

**What this does not give.** The result concerns one layer (the within-pair class layer). Other layers — the full block, the `B`-factor, the cross-pair structure, the high-dimensional ambient module — are not addressed and remain open. The coupled identity is a theorem in odd characteristic; in characteristic two the obstruction is identified and shown generic, but the coupled identity is not an `F_p`-equality there. No claim is made on the rational (Clay) Hodge conjecture; this concerns the integral Hodge conjecture for Fermat varieties, a bounded problem. The torsion counterexample has not been found; every measured cell is primitive.

## 6. Reproducibility

```python
def tensor(n): return n*n
def sym2(n):   return n*(n+1)//2
def alt2(n):   return n*(n-1)//2
def vpv(m,p):
    v=0; mm=m
    while mm%p==0: mm//=p; v+=1
    return v, p**v
def S_of(m,pv): return [k for k in range(m) if k%pv!=pv-1]
def free(m,pv): return len(S_of(m,pv))**2
def triangle(m,pv):
    S=S_of(m,pv); return sum(1 for a in S for b in S if (b%pv)<=(a%pv))
for (m,p) in [(6,3),(8,2),(12,2),(6,2),(18,3),(9,3),(25,5),(14,7),(16,2),(21,3)]:
    v,pv=vpv(m,p); nc=pv-1; c=m//pv
    assert free(m,pv)     == tensor(nc)*c*c     # free = dim(V x V) * c^2
    assert triangle(m,pv) == sym2(nc)*c*c       # coupled = dim(Sym^2 V) * c^2
    assert sym2(nc)+alt2(nc) == tensor(nc)      # V x V = Sym^2 + Alt^2 closes
    assert abs(triangle(m,pv)/free(m,pv) - pv/(2*(pv-1))) < 1e-12   # quotient law
print("WITHIN-PAIR FUNCTOR OK")
```

The realization theorem (Theorem 3) and the generic-torsion theorem (Theorem 4) are verified by Smith normal form of `I+τ` over `Z` and by its `F_p`-versus-`Q` rank drop, in each cell's own characteristic, for `p ∈ {2,3,5,7}`: char 2 gives exactly `p^v−1` divisors divisible by 2; odd char gives zero. Checks return zero discrepancies.

---

## References

1. R. Amichis Luengo, *The localization of torsion to a single CRT block.* Campaign note v1.1, 1 June 2026.
2. A. Degtyarev, I. Shimada, *On the topology of projective subspaces in complex Fermat varieties.* J. Math. Soc. Japan **68**:3 (2016), 975–996. arXiv:1405.4683.
3. E. Aljovin, H. Movasati, R. Villaflor, *Integral Hodge conjecture for Fermat varieties.* J. Symbolic Computation **95** (2019), 177–184. arXiv:1711.02628.
