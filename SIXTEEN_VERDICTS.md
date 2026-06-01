# Sixteen byte-exact primitivity verdicts for Fermat cells on a single 8 GB laptop
### A certified body of computational results — eleven beyond the published table, five independent confirmations. **This is not a theorem.**

**Rafael Amichis Luengo** — Madrid · github.com/tretoef-estrella
**Version 1.1 — 1 June 2026**

---

## Abstract

This document records, in one place and with full provenance, sixteen complete **PRIMITIVE** verdicts on Fermat cells obtained on a throttled 8 GB consumer laptop using the Degtyarev–Shimada criterion. **It is not a theorem and makes no claim to be one.** It is a body of *certified computational results*: for each cell, the complex dimension `dim_C` and the prime-field dimension `dim_Fp` for every prime `p` dividing the degree were computed independently and found equal, so the standard linear cycles generate the full integral Hodge lattice — the cell is **PRIMITIVE**. Eleven of the sixteen lie beyond the Degtyarev–Shimada §5 table and are genuinely new verdicts; five lie inside it and are labelled throughout as *independent confirmations* — the same answers reproduced byte-exact by a different engine on minimal hardware a decade later. Every number below is read directly from a run log in the public repository; none is from memory. The value of this record is reproducibility and reach on small hardware, not a proof: a verdict is a certified computation, not a theorem about all cells.

**Status of this document.** A *verdict* is the outcome of a finite, exact computation on one specific cell: it certifies that, *for that cell*, the integral Hodge conjecture holds (the linear cycles generate). It does **not** prove the conjecture for any infinite family, and it is **not a theorem** in the mathematical sense. Where this document overlaps the companion note *The localization of torsion to a single CRT block* (`THE_LOCALIZATION_THEOREM.md`), that note contains the one proven theorem; this document contains certified data. The distinction is kept sharp on purpose.

## 1. The criterion and what a verdict certifies

For a Fermat variety cut out by `x_0^m + x_1^m + ··· + x_{n+1}^m = 0`, Degtyarev and Shimada [1] gave a combinatorial test: the standard linear cycles generate the full integral Hodge lattice **if and only if** a dimension computed over `C` equals the same dimension computed over `F_p` for every prime `p | m`. When they agree the cell is **PRIMITIVE**; when they disagree the gap is torsion, and a torsion verdict in a degree where none is guaranteed would be a genuine surprise.

The two halves are not equally cheap. The complex half collapses to a fast eigenbasis scan. The prime-field half requires exact Gaussian elimination over a finite field on a sparse system whose size grows as `(m−1)^{n+1}` — millions to billions of nonzero entries. That second half is the entire engineering problem, and it is where each result here was won: not with a bigger machine but by repeatedly redesigning the reduction so that a cell that "could not fit in 8 GB" fit exactly, byte for byte. The single largest object reduced in the campaign is the closure of `(6,9)`: **3.45 billion nonzero entries held on an 8 GB machine at 1.07 bytes per entry.**

Each verdict below is *complete*: `dim_C` and `dim_Fp` for every prime dividing `m`, computed independently and found equal. Peak RAM and wall time are read directly from the named run log. All runs were on a MacBook Air M2, single thread, throttled to 25% CPU, no swap, no cluster, no cloud.

## 2. The sixteen verdicts

`DIM = (m−1)^{n+1}` is the ambient dimension and `dim_C = dim_Fp` is the common value certifying primitivity. "Status" states plainly whether the cell is new (beyond the DS §5 table) or an independent confirmation of a published one.

| Cell (n,m) | DIM | dim_C = dim_Fp | Status | Peak RAM | Engine | Log |
|---|---:|---:|---|---:|---|---|
| (10,3) | 2,048 | 1,124 | new | 14 MB | `HODGE_ENGINE_v3` | `PRUEBA_RECORD_10_3.txt` |
| (8,4) | 19,683 | 10,730 | new | 0.72 GB | `HOUDINI` | `CIC_8_4_run1.log` |
| (8,5) | 262,144 | 198,640 | new | 2.57 GB | `HOUDINI_HYPER_SPARK` | `HOUDINI_HYPER_SPARK_8_5_run1.log` |
| (6,5) | 16,384 | 11,484 | confirms | 0.46 GB | `HOUDINI` | `HOUDINI_6_5_diagnostico.log` |
| (6,6) | 78,125 | 59,392 | new | 0.47/0.60 GB | `ROSETTA_STAR` | `ROSETTA_STAR_6_6_run1.log` |
| (6,7) | 279,936 | 235,206 | new | 2.48 GB | `HOUDINI_HYPER_SPARK` | `HOUDINI_HYPER_SPARK_6_7_run1.log` |
| (6,8) | 823,543 | 720,264 | new | 2.77 GB | `HYPER_SPARK_PACKED` | `HYPER_SPARK_PACKED_6_8_run1.log` |
| (6,9) | 2,097,152 | 1,907,032 | new | 3.71 GB | `HOUDINI_SONIC_BOOM_STAR` | `HOUDINI_SONIC_BOOM_STAR_6_9_run1.log` |
| (4,4) | 243 | 102 | confirms | 0.13 GB | `LETHAL_DUAL` | `LETHAL_DUAL_4_4_gate_run1.log` † |
| (4,6) | 3,125 | 2,124 | confirms | 0.13 GB | `LETHAL_DUAL` | `LETHAL_DUAL_4_6_gate_run1.log` † |
| (4,10) | 59,049 | 51,288 | confirms | 0.20 GB | `LETHAL_DUAL` | `LETHAL_DUAL_4_10_run1.log` |
| (4,12) | 161,051 | 145,950 | confirms | 0.60 GB | `LETHAL_DUAL` | `LETHAL_DUAL_4_12_run1.log` |
| (4,14) | 371,293 | 345,252 | new | 2.218 GB | `CHUCHIPACHI_v2` | `CHUCHIPACHI_v2_4_14_char2_dump.log` |
| (4,13) | 248,832 | 228,912 | new | 0.14 GB | `JULIOCESARINMORTAL` | `JULIOCESARINMORTAL_4_13_run1.log` |
| (4,17) | 1,048,576 | 998,016 | new | 0.79 GB | `JULIOCESARINMORTAL` | `JULIOCESARINMORTAL_4_17_run1.log` |
| (4,19) | 1,889,568 | 1,815,948 | new | 1.68 GB | `JULIOCESARINMORTAL` | `JULIOCESARINMORTAL_4_19_run1.log` |

**†** The cells `(4,4)` and `(4,6)` confirm DS §5 and close in seconds; their listed log is the engine's byte-exact *gate* run (the validation pass that also produces the verdict), not a separate long production run. The rank closed is identical to the verdict. All other rows are production run logs.

Every cell is **PRIMITIVE**: the linear cycles generate the integral Hodge lattice. "new" means beyond the Degtyarev–Shimada §5 table; "confirms" means an independent byte-exact reproduction of a verdict already inside it. Engines live under `engines/` and logs under `logs/` in the repository; every one is public and independently checkable.

## 3. Honest accounting

**Eleven new, five confirmations — stated, not blurred.** The cells `(4,4)`, `(4,6)`, `(4,10)`, `(4,12)` (all `(4,m)` with `m ≤ 12`) and `(6,5)` lie *inside* the Degtyarev–Shimada §5 table. Their PRIMITIVE verdicts were first obtained by Degtyarev and Shimada in 2015 with Gröbner-basis software; they are reproduced here byte-exact, a decade later, by a completely different reduction engine on a throttled 8 GB consumer laptop. Independent reproduction on minimal hardware is a real and citable result — but it is confirmation, and it is labelled as confirmation. The other eleven cells lie beyond the table and are genuinely new computational verdicts.

**Notes on specific rows.** The cell `(6,6) = 2 × 3` has two prime-field computations (characteristics 2 and 3); both returned the same rank, partition by partition, and its peaks and times are listed per characteristic. The cells `(8,4)` and `(6,5)` each have two reduction passes (char-large and char-p); the listed peak is the larger pass, the true maximum of the cell.

**The half-decided cell `(4,15) = 3 × 5`.** Recorded separately and honestly. Its char-5 prime-field half fits and closes: `dim_F5 = 504,924 = dim_C`, PRIMITIVE in characteristic 5. Its char-3 half aborted clean under the no-swap RAM guard before completing; the block it would close to is independently known (`DS_4(13) = 19,920`, the same value measured exactly in `(4,14)` char 2, which shares the recursive structure), so char 3 is *consistent with primitive and is not a torsion candidate* — but it is not closed end-to-end on this hardware. Verdict: char 5 PRIMITIVE (closed); char 3 consistent with primitive, not closed under the no-swap discipline; cell incomplete, **not torsion**. It is parked, not abandoned, and is excluded from the count of sixteen.

**What a verdict does and does not establish.** A verdict certifies the integral Hodge conjecture *for one named cell*, by exact computation. It does not prove the conjecture for any infinite family and is not a theorem. Because every decided cell is PRIMITIVE, `dim_Fp = dim_C` on each, so the Degtyarev–Shimada formula gives — for free — the rank the expensive prime-field half must equal *if* a cell is primitive; this turns the formula into a target line for the search for a torsion counterexample (the value to disbelieve), but the formula cannot itself find torsion. The torsion counterexample has not been found.

**Scope.** This concerns the integral Hodge conjecture for Fermat varieties — a specific, bounded problem. It is not the Clay Millennium (rational) Hodge conjecture and makes no claim on it.

## 4. Reproducibility

Every engine and every run log is in the public repository `github.com/tretoef-estrella`. Each verdict row links to the source of the engine that produced it and to the raw run output from which its peak RAM, wall time, and dimensions are read. The complex and prime-field halves are computed by independent code paths; equality of the two is the verdict. No number in this document is from memory; each is read from a named log.

## References

[1] A. Degtyarev, I. Shimada, *On the topology of projective subspaces in complex Fermat varieties.* J. Math. Soc. Japan 68:3 (2016), 975–996. doi:10.2969/jmsj/06830975. arXiv:1405.4683.

[2] E. Aljovin, H. Movasati, R. Villaflor, *Integral Hodge conjecture for Fermat varieties.* J. Symbolic Computation 95 (2019), 177–184. arXiv:1711.02628.
