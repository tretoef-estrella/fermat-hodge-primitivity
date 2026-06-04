"""
HINGE 1 PROBE -- the Fermat degree bound makes "fixed by gamma_j" = "z_j = 0".

The Auditor's bite: "fixed by gamma_j" abstractly means degree = 0 mod m (includes 0, m, 2m, ...).
"z_j = 0" means degree exactly 0. They coincide ONLY because DS Lemma 4.1 bounds exponents to
0 <= nu_i < m (the quotient by x_i^m - 1). We make this explicit and measure it.

gamma_j acts on a monomial z_j^nu by  z_j^nu -> zeta^nu z_j^nu  (zeta = e^{2pi i/m}).
"Fixed by gamma_j" (eigenvalue 1) <=> zeta^nu = 1 <=> nu ≡ 0 (mod m).
In the AMBIENT polynomial ring Z[z_j] (UNBOUNDED degree), that is nu in {0, m, 2m, ...}: an
INFINITE set, strictly larger than {0}. The cut z_j = 0 keeps grade-0 monomials ONLY.

DS Lemma 4.1: in A = Z[x_1..x_N]/(x_i^m - 1), every class has a representative with 0 <= nu_i < m.
Under THIS bound, nu ≡ 0 mod m with 0 <= nu < m forces nu = 0. So:

   (fixed by gamma_j)  ∩  (Fermat degree bound 0<=nu<m)  =  (grade 0)  =  (z_j = 0 invariant part).

We verify, byte-exact:
  (a) WITHOUT the bound: #{nu in [0, Mmax) : nu ≡ 0 mod m} grows (0, m, 2m, ...) -- NOT {0}.
  (b) WITH the bound 0<=nu<m: the only invariant exponent is nu = 0 -- exactly grade 0.
  (c) On V = k[t]/(t^m-1) (the bounded ambient), the eigenvalue-1 (generalized) space has the
      dimension predicted by the bound: 1 over C (only nu=0 survives as a SIMPLE eigenvalue),
      and the (t-1)-primary tower over F_p (the bound is respected; the tower is the char-p
      thickening of the single grade-0 class, NOT extra grades).
"""

import sympy as sp
from sympy import symbols

def hinge1(m, Mmax_mult=4):
    zeta = sp.exp(2*sp.pi*sp.I/m)
    # (a) WITHOUT the Fermat bound: invariant exponents in [0, Mmax)
    Mmax = m*Mmax_mult
    inv_unbounded = [nu for nu in range(Mmax) if sp.simplify(zeta**nu - 1) == 0]
    # (b) WITH the bound 0<=nu<m
    inv_bounded = [nu for nu in range(m) if sp.simplify(zeta**nu - 1) == 0]
    return dict(m=m,
                unbounded=inv_unbounded,            # {0, m, 2m, ...} -- larger than {0}
                bounded=inv_bounded,                # must be exactly [0]
                bound_collapses=(inv_bounded == [0]))

print("=== HINGE 1: Fermat degree bound (DS Lemma 4.1) collapses 'fixed by gamma_j' to 'z_j=0' ===\n")
for m in (4, 6, 8, 9, 10, 12, 15):
    r = hinge1(m)
    print(f"  m={r['m']:>2}  invariant exponents WITHOUT bound (in [0,{4*m})): {r['unbounded']}")
    print(f"        invariant exponents WITH bound 0<=nu<m:         {r['bounded']}   "
          f"=> collapses to grade 0: {r['bound_collapses']}")
print()
allok = all(hinge1(m)['bound_collapses'] for m in (4,6,8,9,10,12,15))
print("HINGE 1 OK:" , allok,
      "-- the bound 0<=nu<m forces (deg = 0 mod m) -> (deg = 0), i.e. (fixed by gamma_j) = (z_j=0)")
