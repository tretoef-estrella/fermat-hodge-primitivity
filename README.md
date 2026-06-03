# The Hodge–Fermat Campaign

### Verifying the Integral Hodge Conjecture for high-dimensional Fermat varieties on a single 8 GB laptop

> A psychologist in Madrid, with no formal training as a mathematician, sat down at a MacBook Air — the thin consumer laptop, 8 GB of memory, one thread, deliberately throttled to a quarter of its power — and went after a problem the published computations had stopped short of. The tool for it, a criterion from 2016, was tested by its authors only up to a small table. He had a laptop and a refusal to quit. Over a series of sessions he decided sixteen cells of the problem, byte for byte — most of them past where the criterion had ever been run — found a place where the fast version of the method silently lies that nobody had marked on any map, proved that the same factorization which breaks the method also lays the cell's interior open in a recursive structure that says exactly where a counterexample could hide, opened one of those hiding places and proved — for odd characteristic — exactly what lives inside it, and finally turned the recursive structure itself, measured cell by cell, into a **theorem**: the rank every block contributes, at every coupling depth, for every block dimension, is the Degtyarev–Shimada value — closed by a single pen-and-paper identity, with the one condition it rested on discharged by proving that reducing the integral problem modulo a prime injects no phantom torsion.

This is the record of that campaign: what was computed, how, and exactly what is new versus what is confirmation.

**Architect:** Rafael Amichis Luengo (Madrid) · [tretoef@gmail.com](mailto:tretoef@gmail.com) · [github.com/tretoef-estrella](https://github.com/tretoef-estrella)
**Method base:** Degtyarev–Shimada combinatorial primitivity criterion (*J. Math. Soc. Japan* **68:3** (2016), 975–996; arXiv:1405.4683)
**Hardware:** MacBook Air M2 (2022), 8 GB RAM, single thread, throttled to 25% CPU. No swap. No cluster. No cloud.

---

## At a glance

| | |
|---|---|
| **Cells given a complete PRIMITIVE verdict** | 16 — `(10,3)`, `(8,4)`, `(8,5)`, `(6,5)`, `(6,6)`, `(6,7)`, `(6,8)`, `(6,9)`, the composite fourfolds `(4,4)`, `(4,6)`, `(4,10)`, `(4,12)`, `(4,14)`, and the prime-degree fourfolds `(4,13)`, `(4,17)`, `(4,19)` |
| **Cells decided beyond the Degtyarev–Shimada §5 table** | 11 of the 16 — every cell except `(4,4)`, `(4,6)`, `(4,10)`, `(4,12)`, `(6,5)`, which lie inside the published table and are here **independently confirmed** |
| **Deepest single computation** | `(6,9)`: a **3.45-billion-entry** closure, held at **1.07 bytes per entry** |
| **First composite-degree cell decided beyond the published table** | `(6,6)` — `m = 6 = 2 × 3`; the first cell where the *Frontier* manifests and is crossed |
| **Structural results** | (1) the *prime-power reduction frontier* (the *Frontier*) — where the fast method silently fails — and its constructive dual, the **CRT block split** (LETHAL DUAL), a RAM lever; (2) the **recursive block decomposition** of that split — each block's rank is a product of Degtyarev–Shimada recursion ladders, with torsion **provably localized to a single block** by idempotent centrality, and the per-block rank law now a **theorem for every block dimension** (the *block-rank theorem*), its one stated condition discharged by the **red link** (the `F_p` refinement is faithful — the integral block closure is `Z`-free, proven pen-and-paper, characteristic-independent); (3) the **interior of a single block** — the tensor-over-pairs structure (Degtyarev–Shimada's own §4.6) and the single-variable signature law are firm, and the **within-pair coupling is now identified as a functor** (the symmetric square `Sym²V`), **proven for odd characteristic**, with the characteristic-two obstruction shown to be the generic swap torsion — closing the within-pair class layer as a swan site; (4) **the grade-shift invariant** — across a 12-cell sweep the block rank is **blind to all fine modular structure and sees only the dimension `dimB`** (`all-B = DS₂(dimB+1)`, verified byte-exact, swan-free). See [THE_NAIL_THEOREM.md](THE_NAIL_THEOREM.md) (the block-rank theorem, now unconditional · [PDF](THE_NAIL_THEOREM_CLOSED.pdf)), [THE_BLOCK_DECOMPOSITION.md](THE_BLOCK_DECOMPOSITION.md), [THE_WITHIN_PAIR_FUNCTOR.md](THE_WITHIN_PAIR_FUNCTOR.md), and the standalone notes [THE_LOCALIZATION_THEOREM.md](THE_LOCALIZATION_THEOREM.md) and [SIXTEEN_VERDICTS.md](SIXTEEN_VERDICTS.md) (the certified verdicts, explicitly *not* a theorem). |
| **The within-pair, identified** | The within-pair survivor count is `dim(Sym²V)·c²` (coupled) or `dim(V⊗V)·c²` (free) — the tensor square collapsing to the symmetric square on the class layer. The quotient law `coupled/free = p^v/(2(p^v−1))` is proven; the realization is a theorem in **odd characteristic**, and the char-2 obstruction `(Z/2)^{p^v−1}` is the **generic** swap torsion, not Fermat-specific — ruling the swan out of the class layer. See [THE_WITHIN_PAIR_FUNCTOR.md](THE_WITHIN_PAIR_FUNCTOR.md). |
| **Within-pair coupling, from the sofa** | Coupling exists **only when a prime square divides `m`** (`p^v ≥ 3`) — square-free degrees are free. This redirects the swan hunt toward **prime-power degrees** (`8, 9, 16, 25, …`), computed entirely from the armchair. |
| **The capstone theorem** | The **block-rank theorem**: `rec(d, ℓ) = DS_{2(ℓ−1)}(d+1)` for *every* block dimension `d` and coupling depth `ℓ` — the recursive structure of the CRT split, measured cell by cell across the campaign, is now **proven**, not a pattern. The proof is a chain of module-dimension identities read from the Degtyarev–Shimada source (tensor decomposition Cor 1.7 · generating count Remark 4.4 · Lipshitz holonomic finiteness). Its one stated condition — that the measured block is the Degtyarev–Shimada core — is **discharged by the red link**: a pen-and-paper, characteristic-independent proof that the integral block closure is `Z`-free (it is the ring `Z[t]/φ` realised inside the pair, characteristic polynomial `φ`, via the cyclotomic identity `x·c₀ = −1`), so reducing modulo any prime is faithful and injects zero phantom torsion. See [THE_NAIL_THEOREM.md](THE_NAIL_THEOREM.md) · [PDF](THE_NAIL_THEOREM_CLOSED.pdf). |
| **What the theorem does *not* do** | It fixes the per-block **value** — the `C`-side ladder, and proves the `F_p` reduction faithful. It does **not** decide whether genuine integral torsion exists in some unmeasured block: that is Degtyarev–Shimada **Conjecture 1.2**, the campaign's *swan*, and it **remains open**. The theorem is the rigorous map of the minefield — torsion can only hide in a recursive-dimension `≥ 4` block deviating from the value — not the hunt's end. |

---

## What this is

The Integral Hodge Conjecture is one of the load-bearing questions of modern geometry: does every integral Hodge class on a smooth projective variety come from an actual algebraic subvariety, with whole-number coefficients? The general answer is *no* (Atiyah–Hirzebruch found counterexamples in 1962), which is exactly why the cases where it *does* hold are worth pinning down — and Fermat varieties, the most symmetric examples there are, have been a proving ground for the question since Shioda's work in 1979. The hard part is that checking even a single case is a serious computation, and the published computations stop early. This campaign pushes that boundary on hardware nobody would call serious.

For Fermat varieties — the surfaces and higher-dimensional analogues cut out by `x₀ᵐ + x₁ᵐ + ⋯ + xₙ₊₁ᵐ = 0` — Degtyarev and Shimada gave a purely combinatorial test: the standard linear cycles generate the full integral Hodge lattice **if and only if** a certain dimension computed over the complex numbers (`dim_C`) equals the same dimension computed over each prime field `F_p` for every prime `p` dividing `m`. When they agree, the cell is **PRIMITIVE**. When they disagree, the gap is **torsion** — and a torsion verdict in a degree where none is guaranteed would be a genuine surprise to the field.

The two halves are not equally cheap. The complex half collapses to a fast eigenbasis scan. The prime-field half requires honest Gaussian elimination over a finite field on a sparse system whose size explodes with the cell — millions to billions of nonzero entries. **That second half is the entire engineering problem of this project**, and it is where every record here was won: not by buying a bigger machine, but by repeatedly redesigning the computation so that a cell which "could not fit in 8 GB" suddenly fit, exactly, byte-for-byte.

Every number in this document comes from a run log in the repository. Nothing is from memory, and nothing is rounded to flatter — and where the published literature already holds a result, it is named as confirmation, not as discovery.

---

## Where the published frontier was, and where this campaign went

To be precise about what is new, here is the published state of the art, checked against the primary sources — and, crucially, against the exact computational table Degtyarev and Shimada published:

- **Degtyarev–Shimada (2016)** [1] state the criterion and, in their §5, report verifying it by computer in exactly these cases (their page 17, verbatim): **`(4,m)` for `3 ≤ m ≤ 12`, plus `(6,3)`, `(6,4)`, `(6,5)`, `(8,3)`.** That published table is the line this campaign measures itself against.
- **Aljovin–Movasati–Villaflor (2019)** [6] give an independent algorithm and a *theoretical* guarantee, but only under the condition **"d prime, or d = 4, or gcd(d, (n+1)!) = 1"**, and their implementation reaches only dimension **n ≤ 4**. Notably, they tabulate the lattice of primitive Hodge cycles but state they were **not able to compute its elementary divisors** — precisely the per-block torsion structure this campaign's decomposition opens (see [THE_BLOCK_DECOMPOSITION.md](THE_BLOCK_DECOMPOSITION.md)).
- **For surfaces (n = 2)** the problem — originally posed by **Aoki and Shioda in 1983** [3] — is *completely settled*: Schütt–Shioda–van Luijk [4] and Degtyarev [5] proved the lines generate the Néron–Severi group **if and only if m ≤ 4 or gcd(m, 6) = 1**. The surface literature deliberately works in degrees coprime to 6.

The lineage is worth seeing whole. Shioda asked in 1979 [2] whether the standard cycles generate the Hodge lattice of Fermat varieties; Aoki and Shioda sharpened the surface case in 1983; the surface verdict was closed by Schütt–Shioda–van Luijk and Degtyarev; and Degtyarev–Shimada turned the higher-dimensional question into a computable criterion in 2016, verified up to the §5 table above. **This campaign is the next link in that chain.** Eleven of its sixteen decided cells lie *beyond* that table — fourfolds and higher (`n = 4, 6, 8, 10`) in degrees and dimensions the published computation never reached. The deepest virgin cell, `(6,9)`, is a 3.45-billion-entry closure. The structural headline, `(6,6)`, lives in a composite degree (`m = 6 = 2 × 3`) past the table — and revealed, in the process, a boundary of the *fast* computational method itself that nobody had marked.

A word on honesty before the tables. Five of the sixteen cells — `(4,4)`, `(4,6)`, `(4,10)`, `(4,12)`, `(6,5)` — lie *inside* the Degtyarev–Shimada §5 table. They are **not** new verdicts. They are reported here as **independent confirmation**: the same answers DS obtained in 2015 with Gröbner-basis software, reproduced byte-exact a decade later on a throttled 8 GB consumer laptop by a completely different reduction engine. Independent reproduction on minimal hardware is a real and citable result — but it is confirmation, and it is labelled as confirmation throughout. The genuinely new verdicts are the other eleven.

---

## The cells conquered

Each verdict below is a *complete* verdict: the complex dimension `dim_C` **and** the prime-field dimension `dim_Fp` for every prime dividing `m`, computed independently and found equal. Every cell is **PRIMITIVE** — the linear cycles generate the integral Hodge lattice. Peak RAM and wall time are read directly from the run log named in the last column. All ran on the 8 GB MacBook Air, single thread, 25% CPU. The **status** column states plainly whether the cell is new (beyond the DS §5 table) or an independent confirmation of a published one. **Every engine and every log is in this repository — check it yourself: the engine column links to the source, the log column to the raw run output.** The full sixteen-verdict table also stands alone, with provenance, in [SIXTEEN_VERDICTS.md](SIXTEEN_VERDICTS.md) — labelled there, as here, a body of certified computations and *not* a theorem.

| Cell (n,m) | DIM = (m−1)ⁿ⁺¹ | dim_C = dim_Fp | Verdict | Status vs DS §5 | Peak RAM | Wall time | Engine | Log |
|---|---|---|---|---|---|---|---|---|
| (10,3) | 2,048 | 1,124 | PRIMITIVE | **new** (beyond table) | 14 MB | minutes | [HODGE_ENGINE_v3](engines/HODGE_ENGINE_v3.cpp) | [log](logs/PRUEBA_RECORD_10_3.txt) |
| (8,4) | 19,683 | 10,730 | PRIMITIVE | **new** (beyond table) | 0.72 GB | ~2 h 45 m | [HOUDINI](engines/HOUDINI.cpp) | [log](logs/CIC_8_4_run1.log) |
| (6,5) | 16,384 | 11,484 | PRIMITIVE | confirms DS §5 | 0.46 GB | ~58 m | [HOUDINI](engines/HOUDINI.cpp) | [log](logs/HOUDINI_6_5_diagnostico.log) |
| (6,6) | 78,125 | 59,392 | PRIMITIVE | **new** (beyond table) | 0.47 / 0.60 GB | 6,551 s / 11,532 s | [**ROSETTA STAR**](engines/ROSETTA_STAR.cpp) | [log](logs/ROSETTA_STAR_6_6_run1.log) |
| (6,7) | 279,936 | 235,206 | PRIMITIVE | **new** (beyond table) | 2.48 GB | 487 s | [HOUDINI HYPER SPARK](engines/HOUDINI_HYPER_SPARK.cpp) | [log](logs/HOUDINI_HYPER_SPARK_6_7_run1.log) |
| (6,8) | 823,543 | 720,264 | PRIMITIVE | **new** (beyond table) | 2.77 GB | 1,059 s | [HYPER SPARK PACKED](engines/HYPER_SPARK_PACKED.cpp) | [log](logs/HYPER_SPARK_PACKED_6_8_run1.log) |
| (6,9) | 2,097,152 | 1,907,032 | PRIMITIVE | **new** (beyond table) | 3.71 GB | 11,472 s | [HOUDINI SONIC BOOM STAR](engines/HOUDINI_SONIC_BOOM_STAR.cpp) | [log](logs/HOUDINI_SONIC_BOOM_STAR_6_9_run1.log) |
| (8,5) | 262,144 | 198,640 | PRIMITIVE | **new** (beyond table) | 2.57 GB | 4,601 s | [HOUDINI HYPER SPARK](engines/HOUDINI_HYPER_SPARK.cpp) | [log](logs/HOUDINI_HYPER_SPARK_8_5_run1.log) |
| (4,4) | 243 | 102 | PRIMITIVE | confirms DS §5 | 0.13 GB | seconds | [**LETHAL DUAL**](engines/LETHAL_DUAL_ENGINE.cpp) | [log](logs/LETHAL_DUAL_4_4_gate_run1.log) |
| (4,6) | 3,125 | 2,124 | PRIMITIVE | confirms DS §5 | 0.13 GB | seconds | [**LETHAL DUAL**](engines/LETHAL_DUAL_ENGINE.cpp) | [log](logs/LETHAL_DUAL_4_6_gate_run1.log) |
| (4,10) | 59,049 | 51,288 | PRIMITIVE | confirms DS §5 | 0.20 GB | 177 s | [**LETHAL DUAL**](engines/LETHAL_DUAL_ENGINE.cpp) | [log](logs/LETHAL_DUAL_4_10_run1.log) |
| (4,12) | 161,051 | 145,950 | PRIMITIVE | confirms DS §5 | 0.60 GB | 1,402 s | [**LETHAL DUAL**](engines/LETHAL_DUAL_ENGINE.cpp) | [log](logs/LETHAL_DUAL_4_12_run1.log) |
| (4,14) | 371,293 | 345,252 | PRIMITIVE | **new** (beyond table) | 2.218 GB | 5,788 s | [CHUCHIPACHI v2](engines/CHUCHIPACHI_v2.cpp) | [log](logs/CHUCHIPACHI_v2_4_14_char2_dump.log) |
| (4,13) | 248,832 | 228,912 | PRIMITIVE | **new** (beyond table) | 0.14 GB | 41 s | [JULIOCESAR INMORTAL](engines/JULIOCESARINMORTAL.cpp) | [log](logs/JULIOCESARINMORTAL_4_13_run1.log) |
| (4,17) | 1,048,576 | 998,016 | PRIMITIVE | **new** (beyond table) | 0.79 GB | 797 s | [JULIOCESAR INMORTAL](engines/JULIOCESARINMORTAL.cpp) | [log](logs/JULIOCESARINMORTAL_4_17_run1.log) |
| (4,19) | 1,889,568 | 1,815,948 | PRIMITIVE | **new** (beyond table) | 1.68 GB | 8,079 s | [JULIOCESAR INMORTAL](engines/JULIOCESARINMORTAL.cpp) | [log](logs/JULIOCESARINMORTAL_4_19_run1.log) |

Notes, kept honest:
- **The five confirmations vs the eleven new verdicts.** `(4,4)`, `(4,6)`, `(4,10)`, `(4,12)` (all `(4,m)` with `m ≤ 12`) and `(6,5)` lie inside the DS §5 table; their PRIMITIVE verdicts were first obtained by Degtyarev and Shimada and are here reproduced byte-exact by an independent engine on consumer hardware. The other eleven cells lie beyond the table and are new computational verdicts. Both counts are stated rather than blurred.
- `(6,6)` has **two** prime-field computations (char 2 and char 3, since 6 = 2 × 3); both returned the same rank, partition by partition. Its peaks and times are listed per characteristic.
- `(8,4)` and `(6,5)` each have two reduction passes (char-large and char-p). The listed peak is the larger of the two — the char-large pass — which is the true maximum of the cell; the char-p pass peaked lower (`(8,4)`: 0.42 GB; `(6,5)`: 0.40 GB). The listed time is the sum of both passes.
- `(4,14)` is listed from the **CHUCHIPACHI v2** dump run, which carries both the verdict *and* the per-block structure used in [THE_BLOCK_DECOMPOSITION.md](THE_BLOCK_DECOMPOSITION.md); its all-B monster block measured exactly `19,920 = DS₄(13)`, the recursive-law value, confirming the block decomposition on a closed cell.
- The "rank" reduced at each verdict is the *closing rank* `= DIM − dim_C` (e.g. `(8,5)`: `262,144 − 198,640 = 63,504`, held flat from partition 892 to 945 — the tail partitions add zero, confirming the span is complete).
- `(10,3)`'s log records flat 14 MB RAM but no second-resolution wall time; "minutes" is the honest description.
- The single largest object ever reduced in the campaign is `(6,9)`'s closure: **3.45 billion nonzero entries held on an 8 GB machine at 1.07 bytes per entry.**

**On the prime-degree fourfolds `(4,13)`, `(4,17)`, `(4,19)`.** These are decided by JULIOCESAR INMORTAL, whose Jordan-pruning relation `uᵐ⁻¹ = 0` is the *true* ring relation precisely because the degree is prime (φ does not factor — a single block, no CRT splitting to corrupt the pruning). They lie beyond the DS §5 table, so they are new verdicts; but **prime degree is also covered by the AMV/Aoki rational-generation results** — a torsion swan cannot hide there. They are honest census, not hunt: new data points, but in a region theory already expected to be white.

**The composite fourfold front and the (4,15) half-cell (LETHAL DUAL, this campaign).** The five `(4,m)` rows decided by the **CRT block split** (see *The Frontier's constructive dual* below) split cleanly by status. **`(4,6)`, `(4,10)`, `(4,12)` lie inside the DS §5 table** (`m ≤ 12`) and are **independent confirmations** of published composite-degree verdicts — reproduced byte-exact on 8 GB by a different method. **`(4,14)` lies beyond the table and is a genuinely new composite-degree verdict.** `(4,4)` (`m = 4`, a prime power) also lies in the table and falls additionally in AMV's `d = 4` case; it too is independently confirmed. Stating this split honestly matters: the composite-degree *front* is real and is this campaign's forward direction, but not every composite cell already computed here is virgin — three of them stand on Degtyarev and Shimada's own published shoulders, and say so.

One cell is deliberately recorded as **half-decided**, because honesty requires it: **`(4,15) = 3×5`**. Its complex half is `dim_C = 504,924`. The char-5 prime-field half **fits and closes**: `dim_F5 = 504,924 = dim_C`, peak 3.165 GB, PRIMITIVE in characteristic 5. The char-3 half **aborted clean under the no-swap RAM guard**: its all-B block (`dimB = 12`, block size `12⁵`) climbed to ~4.3 GB at 90% of the block and projects to ~4.85 GB at close — *within* the 5.4 GB guard, but the run was halted by the no-swap discipline before completing. The earlier description of this half as "RAM-bound beyond 8 GB" is corrected here: it is a no-swap-discipline stop, not a >8 GB wall. Crucially, the value that block would close to is **independently known and measured**: the all-B monster rank is `DS₄(13) = 19,920`, and the cell `(4,14)` char 2 — same `dimB = 12`, same recursive structure — **measured exactly that block at 19,920** (see [THE_BLOCK_DECOMPOSITION.md](THE_BLOCK_DECOMPOSITION.md)). So char 3 is **not a torsion candidate** — its monster block matches the recursive law to the digit; it is simply not yet closed in a single uninterrupted run on this hardware. Recorded verdict: *char 5 PRIMITIVE (fits, closed); char 3 consistent with PRIMITIVE (monster block matches `DS₄(13)`), not closed end-to-end under the no-swap guard; cell incomplete — one prime confirmed, one consistent-but-not-closed; NOT torsion.* The cell is parked, not abandoned. `(4,15)` also lies beyond the DS §5 table, so closing its char-3 half end-to-end would be a new verdict.

### The DOBERMAN sweep — the complex half, mapped across the mesh

Beyond the full verdicts, the sweep engine **DOBERMAN** computed the *complex half* `dim_C` for **38 cells** in well under an hour of total wall time, RAM flat throughout. These are not complete verdicts — the prime-field half is the expensive one — but they map the entire territory, pre-stage every future target, and (see "What the sweep confirmed" below) match a closed-form law. Every line is from the run log; `wall_s` is the time for that cell's complex half alone.

| Cell (n,m) | DIM | partitions | dim_C | off {3,4,6}? | m prime? | torsion-suspect? | wall (s) |
|---|---|---|---|---|---|---|---|
| (4,3) | 32 | 15 | 12 | no | yes | no | 0.000 |
| (4,4) | 243 | 15 | 102 | no | no | no | 0.000 |
| (6,3) | 128 | 105 | 58 | no | yes | yes | 0.000 |
| (4,5) | 1,024 | 15 | 624 | yes | yes | no | 0.000 |
| (4,6) | 3,125 | 15 | 2,124 | no | no | no | 0.000 |
| (4,7) | 7,776 | 15 | 5,916 | yes | yes | no | 0.001 |
| (6,4) | 2,187 | 105 | 1,080 | no | no | no | 0.002 |
| (4,8) | 16,807 | 15 | 13,506 | yes | no | no | 0.002 |
| (8,3) | 512 | 945 | 260 | no | yes | yes | 0.002 |
| (4,9) | 32,768 | 15 | 27,648 | yes | no | no | 0.002 |
| (4,10) | 59,049 | 15 | 51,288 | yes | no | no | 0.002 |
| (4,11) | 100,000 | 15 | 89,100 | yes | yes | no | 0.003 |
| (6,5) | 16,384 | 105 | 11,484 | yes | yes | yes | 0.004 |
| (4,12) | 161,051 | 15 | 145,950 | yes | no | no | 0.005 |
| (4,13) | 248,832 | 15 | 228,912 | yes | yes | no | 0.007 |
| (4,14) | 371,293 | 15 | 345,252 | yes | no | no | 0.010 |
| (4,15) | 537,824 | 15 | 504,924 | yes | no | no | 0.015 |
| (6,6) | 78,125 | 105 | 59,392 | no | no | no | 0.018 |
| (8,4) | 19,683 | 945 | 10,730 | no | no | no | 0.029 |
| (10,3) | 2,048 | 10,395 | 1,124 | no | yes | yes | 0.033 |
| (6,7) | 279,936 | 105 | 235,206 | yes | yes | yes | 0.058 |
| (6,8) | 823,543 | 105 | 720,264 | yes | no | yes | 0.157 |
| (6,9) | 2,097,152 | 105 | 1,907,032 | yes | no | yes | 0.372 |
| (8,5) | 262,144 | 945 | 198,640 | yes | yes | yes | 0.400 |
| (6,10) | 4,782,969 | 105 | 4,437,504 | yes | no | yes | 0.796 |
| (6,11) | 10,000,000 | 105 | 9,448,050 | yes | yes | yes | 1.618 |
| (12,3) | 8,192 | 135,135 | 4,760 | no | yes | yes | 1.642 |
| (10,4) | 177,147 | 10,395 | 103,358 | no | no | no | 2.531 |
| (8,6) | 1,953,125 | 945 | 1,577,380 | no | no | no | 2.829 |
| (6,12) | 19,487,171 | 105 | 18,610,840 | yes | no | yes | 3.076 |
| (6,13) | 35,831,808 | 105 | 34,550,388 | yes | yes | yes | 5.549 |
| (6,14) | 62,748,517 | 105 | 60,881,280 | yes | no | yes | 9.497 |
| (8,7) | 10,077,696 | 945 | 8,905,140 | yes | yes | yes | 14.456 |
| (8,8) | 40,353,607 | 945 | 36,758,430 | yes | no | yes | 54.691 |
| (10,5) | 4,194,304 | 10,395 | 3,340,528 | yes | yes | yes | 65.628 |
| (14,3) | 32,768 | 2,027,025 | 19,898 | no | yes | yes | 107.781 |
| (12,4) | 1,594,323 | 135,135 | 978,096 | no | no | no | 305.280 |
| (10,6) | 48,828,125 | 10,395 | 40,969,900 | no | no | no | 884.898 |

The deepest cell here, `(10,6)`, has its complex half computed from over **two million partitions** in under fifteen minutes. The "torsion-suspect" column flags cells where theory does *not* force primitivity (degree prime and/or outside {3,4,6}) — these are where a surprise could in principle live, and they are the campaign's forward targets.

### What the sweep confirmed — a closed-form law, and whose it is

The 38-cell sweep is a fast census, and it let the campaign confirm a closed-form law for the complex half. Here honesty about priority is essential, and it is stated plainly.

**The rank formula is Degtyarev and Shimada's, not this campaign's.** Their **Remark 4.4** (page 14 of [1]) gives the rank of `L(X)` in closed form, verbatim:

- `rank = 3m² − 9m + 6 + δₘ` for `n = 2`;
- `rank = 15m³ − 90m² + 175m − 100 + (15m − 39)δₘ` for `n = 4`;
- `rank = 105m⁴ − 1050m³ + 3955m² − 6335m + 3325 + (210m² − 1302m + 2010)δₘ` for `n = 6`;

where `δₘ ∈ {0,1}` satisfies `δₘ ≡ m − 1 (mod 2)`. The leading coefficient is the partition count `(2d+1)!!`, also from DS. **Note on naming:** this formula gives the rank of `L(X)` — the *closing rank*, equal to `DIM − dim_C`, the quantity the prime-field engine sums to — **not** `dim_C` itself. `dim_C = DIM − (Remark 4.4)`. (For `(4,6)`: Remark 4.4 gives `1001`, the closing rank; `dim_C = 3125 − 1001 = 2124`.) All campaign numbers respect this; the label is stated explicitly here to avoid the natural confusion.

What this campaign did is **independent numerical verification** of that published formula: the `n = 4` and `n = 6` rows of the DOBERMAN sweep reproduce DS Remark 4.4 byte-exact across every degree computed, with **zero outliers**. This is a genuine and useful check — DS's own §5 table reached only `m ≤ 12` in the `n = 4` row, and this sweep confirms their formula well past that — but it is *verification of their result*, not a discovery of a new one. The formula is theirs; the byte-exact confirmation across an extended range, and the calculator that evaluates it instantly, are this campaign's contribution. **No claim of a new formula is made.**

The verification carries one real consequence worth stating: because every decided cell is PRIMITIVE, `dim_Fp = dim_C` on each, so DS's formula also gives — for free, with no reduction — the rational rank the *expensive* prime-field half must equal **if** a cell is primitive. That makes the formula a ready-made target line for the swan hunt: a torsion cell would be precisely one whose measured `dim_Fp` departs from it. The formula cannot *find* torsion (it is the complex half, blind to the prime-field Jordan structure by construction), but it tells the hunt exactly what number to disbelieve — and the block decomposition (below) sharpens that into *which block* would carry the betrayal.

A note on counts, for precision: the sweep evaluated `dim_C` for **38 cells** in one run; of those, roughly **27 are values not present in any published table** (the rest are calibration cells with known values). "38 cells swept" and "~27 cells past the published tables" are two different counts of two different things, and both are honest — the first is the run, the second is its reach.

---

## The engines

The project's engineering is a single bloodline. Each engine was built only after the previous one's wall was *measured*, not guessed; each new name was earned by passing byte-exact validation gates against known cells before it was trusted. The names are deliberately playful — a house rule that a ridiculous name must carry a serious engine.

| Engine | The lever it added | Decided / enabled |
|---|---|---|
| **HODGE_ENGINE_v3** | Sparse tensorial generation + incremental Gaussian elimination — kills the dense `O(DIM²)` wall of naive approaches. | `(10,3)` and the calibration cells |
| **HOUDINI** | The escape act: compute the complex half in an **eigenbasis** where the ideal is block-diagonal, so `dim_C` falls out in milliseconds with no linear algebra at all. The prime half stays as honest reduction. | `(8,4)`, `(6,5)` |
| **DOBERMAN** | Family-wide sweep of the cheap complex half across every cell under a size ceiling, cheapest-first. | 38 cells' `dim_C` |
| **HOUDINI NAPKIN** | The **Jordan-mould starter**: work in the basis `u = t − 1`, where for `p \| m` each variable is nilpotent (`uᵐ⁻¹ = 0` exactly). Dead terms that would exceed the nilpotent ceiling are **never generated**. (2.17× lighter.) **Valid only for prime-power `m` — see the Frontier.** | (8,5) attempt |
| **HOUDINI NAPKIN TURBINA** | **Flow, not accumulation.** Each partition's small closure is saturated alone, folded into one shared echelon, and its intermediates discarded before the next enters. (≈5× lighter than NAPKIN on (6,5).) | (8,5) method |
| **HOUDINI HYPER SPARK** | The **dense-rebound fold**: scatter each row once into a dense scratch, subtract pivots in place, read the leading column from a tiny heap. (2.1× faster than TURBINA.) | `(8,5)`, `(6,7)` |
| **HYPER SPARK PACKED** | Shrink the *envelope*: store each echelon entry in 5 bytes instead of 16. | `(6,8)` |
| **HOUDINI SUPER BLACKHOLE** | Delta-varint columns. On `(6,9)` char 3 it ran a closure the older method projected at ~7.7 GB toward the low-GB band — but the char-3 tail explodes in the final 5% and it **aborted clean at the 5.4 GB guard, part 97**. A vein that opened the road and died near the summit. | `(6,9)` attempt (incomplete) |
| **HOUDINI SONIC BOOM STAR** | Varint columns **with the coefficient embedded** — **1.07 bytes per entry** on `(6,9)`. The production engine for the deep cells. | `(6,9)` |
| **ROSETTA STAR** | The fix for composite degree (see the Frontier). Reduces in the monomial basis with the *true* ring relation, correct for any `m`. | `(6,6)` |
| **LETHAL DUAL ENGINE** | The Frontier's constructive dual: `φ` **factors** over `F_p` for `p \| m`, the ring splits by CRT into independent blocks the shift respects; reduce them **one at a time and release** — RAM peak becomes the *largest single block*. | `(4,4)`, `(4,6)`, `(4,10)`, `(4,12)`, `(4,14)` |
| **LETHAL DUAL — BIG MONSTER** | Same mathematics, hardened: predictive RAM guard inside the monster all-B block, clean abort, heartbeat, scoreboard. | `(4,15)` char-5 half |
| **CHUCHIPACHI v2** | The block-dump engine: LETHAL DUAL with `--dump-blocks`, recording every CRT block's rank, exposing the per-block structure of [THE_BLOCK_DECOMPOSITION.md](THE_BLOCK_DECOMPOSITION.md). | `(4,14)`, the block dumps |
| **CHUCHIPACHIELESTRUJADOR** | The predictive-guard hardening of the dump engine. | `(4,15)` char-3 attempt (clean abort) |
| **CHUCHIPACHIBANGBANG** | The basis-dump engine: `--dump-basis-mask` prints the **raw generator monomials inside one chosen CRT block**, not just its rank. The instrument that opened the *interior* of a block — the within-pair exponent structure, the signature law, the quotient law and the `Sym²` functorial identification of [THE_WITHIN_PAIR_FUNCTOR.md](THE_WITHIN_PAIR_FUNCTOR.md). Gate-validated byte-exact (`(4,6)` char 2 = 1001, non-regression) before use. | the within-pair dumps `(4,6)`, `(4,12)` |
| **HOUDINI SUPERNOVA** | A fold-reorder attempt; measured honestly as a regression (tied STAR in time, worse in RAM). Gate-valid, recorded so the approach is not retried. The name is **unearned**. | — (not a win) |
| **HOUDINI ANTIGRAVITY** | Deferred-modulo arithmetic (1.55× faster on (6,5)) and **the accordion** — the echelon split into bellows, cold ones compressed. Built and gate-validated; its big-cell run is the next. | live vein |

Across this lineage, the campaign drove the storage cost of a single echelon entry from **16 bytes down to 1.07 bytes** — a **15× compression** won in exact arithmetic — and converted the bottleneck from "hold everything at once" to "let it flow through." That is why an 8 GB laptop reduced a 3.45-billion-entry system.

An engine name in this project is *earned* by a byte-exact result, never claimed in advance.

---

## The method, in one breath

For each cell, two numbers are computed and compared:

1. **The complex half (`dim_C`).** Over a prime `P ≡ 1 (mod m)` a primitive `m`-th root of unity exists, the shift operators become simultaneously diagonalizable, and the whole problem factorizes character-by-character — milliseconds. Cross-checked over several such primes (mandatory). This is the quantity DS give in closed form (Theorem 1.4 and Remark 4.4).

2. **The prime-field half (`dim_Fp`), for each `p \| m`.** Here no root of unity exists; the operator is a single nilpotent Jordan block. The dimension must be found by real sparse Gaussian elimination over `F_p`. This is the expensive half, the home of every engine above.

If `dim_C = dim_Fp` for all `p \| m`, the cell is **PRIMITIVE**. Both halves, every time — a one-sided computation is never a verdict.

**A hard limit, stated up front.** Every cell verified so far is PRIMITIVE, so the gap between the two halves (the "scar") has only ever been measured at zero. This means the method is, to date, an audited **primitivity *confirmator***, not a validated **torsion *detector***: confirmed to report "no torsion" correctly, but never tested reporting torsion where torsion exists, because no such Fermat cell is known. The block decomposition **proves** that any torsion would localize to a single CRT block, but before any future nonzero scar could be trusted, a synthetic positive control — a fabricated system with known torsion — must be shown to make the detector fire correctly. This is a binding requirement, not a footnote, and no result here depends on the scar as a detector. (A corollary established this campaign and recorded in [THE_WITHIN_PAIR_FUNCTOR.md](THE_WITHIN_PAIR_FUNCTOR.md): torsion is measured by Smith normal form / rank drop, **never** by equality of `F_p`- and `Q`-dimensions of a subspace — equal dimension does not imply torsion-free.)

The torsion the campaign hunts is **the swan** — the rare cell where the two halves disagree. By DS Corollary 1.5 it can involve only primes dividing `m`; rational-generation results make prime degrees barren. The hunt points at composite degrees with two or more distinct prime factors, past `{3,4,6}` and past the DS §5 table. The whole effort is the search for a black swan among cells everyone expects to be white, with enough rigour that a white verdict is trustworthy and a black one would be real.

---

## The structural results

### The (6,6) discovery — the prime-power reduction frontier

The first structural result has its own document: **[THE_FRONTIER_6_6.md](THE_FRONTIER_6_6.md)**.

In short: every cell conquered before `(6,6)` had a degree that was a power of a single prime. `(6,6)` is the first with **two distinct primes** (`6 = 2 × 3`) attacked by the fast engine, and the standard engine returned an *impossible* answer — saturating in characteristic 2, a different wrong value in characteristic 3. That asymmetry was the clue: a generic overflow fails the same way in both. It does not.

The diagnosis: the Jordan-mould's pruning rule `uᵐ⁻¹ = 0` is the *true* ring relation **if and only if `m` is a power of a single prime**. When `m` has two distinct prime factors the relation factors (a CRT splitting), the pruning imposes a false constraint, and the rank silently inflates. We call this the **prime-power reduction frontier** — the **Frontier**.

This is a genuinely new structural contribution; its priority is fixed carefully in the linked document. The classical cyclotomic fact is claimed by no one here. What is new is identifying *that* line as the precise point where this reduction fails **silently**, proving the corruption is graded by characteristic, and building the cure. **ROSETTA STAR** reduces in the monomial basis with the correct relation for any degree, and recovered the true verdict: `(6,6)` is **PRIMITIVE** by both primes, byte-exact, on the 8 GB laptop.

### The Frontier's constructive dual — the CRT block split (LETHAL DUAL)

The Frontier is a *destructive* fact: `φ` factoring over `F_p` is **why** the old pruning lies on composite degree. The same fact has a *constructive* face. For a prime `p | m`, `φ(t) = (t−1)ᵃ · g(t)ᵇ` over `F_p`, the factors **coprime** — so by CRT the quotient ring splits as `A × B`. The shift respects the split; tensored over the `n+1` variables, the space breaks into independent blocks, and the closure becomes a **direct sum**. Reduce them **one at a time and release**: memory peak collapses from *the whole closure* to *the largest single block*. Measured on `(4,6)`: the largest block peaks at **0.15×–0.39×** of the monolithic closure, byte-exact, sum of block-ranks equal to the monolithic rank. The cost is paid in CPU, not RAM — and the same factorization that *breaks* Jordan now *buys back* the memory.

### The recursive block decomposition — what lives inside the split

The second structural result has its own document: **[THE_BLOCK_DECOMPOSITION.md](THE_BLOCK_DECOMPOSITION.md)**. Three results, in descending order of firmness:

- **Localization is *proven*.** The CRT idempotents are polynomials in the shift variable, hence central; the module splits as a direct sum over blocks, its presentation matrix is block-diagonal, and the Smith normal form splits per block. Any torsion lives in exactly **one** block — the one that drops rank mod `p`. Written up in isolation with a worked idempotent in [THE_LOCALIZATION_THEOREM.md](THE_LOCALIZATION_THEOREM.md). (Verifier: [verifiers/CENTRALITY_DETECTOR_VERIFIER.py](verifiers/CENTRALITY_DETECTOR_VERIFIER.py).)

- **The per-block rank law is now a *theorem*.** Each block's rank is a product of two recursion ladders, each a DS rank at a *reduced* dimension. Built on `dimA ∈ {1,2}`, it **blind-predicted a `dimA = 4` cell (`(4,15)` char 5) correctly, block by block** — and is now **proven for every block dimension** in [THE_NAIL_THEOREM.md](THE_NAIL_THEOREM.md): the measured block is the Degtyarev–Shimada core (Cor 1.7, free tail), the core dimension is a closed lattice walk (Remark 4.4), the walk is the DS value, uniform in `d` by Lipshitz finiteness. The residual that was open in earlier versions — a pen-and-paper proof that the ladder value equals the DS reduced-dimension rank — is **closed**, and the one identification it rested on (the dictionary) is **discharged by the red link** (the `F_p` refinement is faithful; see below). (Verifiers: [GENERAL_PRODUCT_LAW_VERIFIER.py](verifiers/GENERAL_PRODUCT_LAW_VERIFIER.py), [DS_CONNECTION_VERIFIER.py](verifiers/DS_CONNECTION_VERIFIER.py), [chuchipachielconquistador.py](verifiers/chuchipachielconquistador.py).)

- **The number of blocks is computable from the sofa** — `1 + Σ_{d | m′, d>1} φ(d)/ord_d(p)`, verified byte-exact across 28 cases. (Verifier: [BLOCK_COUNT_LAW_VERIFIER.py](verifiers/BLOCK_COUNT_LAW_VERIFIER.py).)

Together these power [verifiers/RIFLE_FINAL.py](verifiers/RIFLE_FINAL.py) — the *velocidad de Fermat*, predicting a cell from the armchair with a per-prime **[FIRM]**/**[CONJ]** confidence flag.

### Inside a single block — the signature law, and the within-pair functor

The per-block law is *validated*; turning it into a theorem means proving each block's reduced factor is the same *object* as a DS reduced-dimension object. This subsection is recorded with its wrong turns, because the discipline that produced the verdicts governs the open work too.

- **The tensor-over-pairs structure (confirmed).** DS's own §4.6 writes the module as a tensor over partition **pairs**; the measured "rung" ladder confirms the unit is the pair, advancing once every *two* variables. DS's own structure, claimed by no one here.

- **The single-variable signature law (firm).** Inside a block, the `A`-idempotent annihilates exactly the monomials with exponent `≡ −1 (mod p^v)` — the top of the nilpotent `(t−1)`-adic filtration, governed by `(t−1)^{p^v} = t^{p^v} − 1`. Checked byte-exact across characteristics 2 and 3. (An earlier "cyclic involution `t ↦ t⁻¹`" reading was refuted with data and corrected to the Frobenius filtration — a seam caught and closed.)

- **The triangle law (proposed, then refuted out of sample — recorded, not hidden).** A conjecture said the within-pair coupling is always DS's triangular relation `ν ≤ μ (mod p^v)`. On `(4,12)` char 2 it matched byte-exact, set for set (54 pairs). But the owed out-of-sample test — `(4,6)` char 3 — **refuted it**: the within-pair object there is the **free tensor** (16 of 16), not the triangle (12). A property of one cell, not a law. The out-of-sample standard killed a beautiful artifact before it became a false theorem.

### The within-pair functor — the coupled flank closed for odd characteristic, the swan ruled out of the class layer

The grade-shift work above drove the open `F_p` question to a single dimension-only bijection. The next sessions opened the **interior of the all-A pair block** — the within-pair coupling itself — and closed it, with the full result in its own document: **[THE_WITHIN_PAIR_FUNCTOR.md](THE_WITHIN_PAIR_FUNCTOR.md)** (technical paper, [PDF](within_pair_functor.pdf)).

The chase ran exactly as the discipline demands — a beautiful single-cell conjecture, killed by its own out-of-sample test, and the refutation opening the real structure. Stated in order of how firmly each piece stands:

- **The quotient law is *proven* (combinatorial).** The within-pair survivor count factorizes as `(within-class) × (across-class)`: the within-class factor is always free (`c²`), and the across-class factor is either the full square `(p^v−1)²` (free regime) or the triangle `T(p^v−1) = (p^v−1)p^v/2` (coupled regime). The quotient `coupled/free = p^v/(2(p^v−1))` is *derived*, not fitted, and the regimes coincide exactly at `p^v = 2` — **not** at "p even" (the cell `(4,8)` at `p=2` has `p^v = 8` and is coupled, `28 ≠ 49`). This corrects an earlier "p-parity" axis byte-exact and supersedes the v-law-vs-p-parity dilemma: there is one continuous law in `p^v`, no axis to fix. The old "ρ imposes the order" explanation is **refuted with data** — ρ's support reaches the full square; the cut is in what survives, not what appears.

- **The within-pair is a *functor*, not a rank (proven identification, byte-exact 11 cells).** With `V = F_p^{p^v−1}` the live-class space and `W = F_p^c` the within-class space, `free = dim(V⊗V)·c²` and `coupled = dim(Sym²V)·c²`. The entire free/coupled distinction is the collapse of the tensor square `V⊗V` to the symmetric square `Sym²V` on the class layer; the triangular index set is exactly the canonical basis of `Sym²V`, which is *why* the triangle survives a full-square support. Four dimension/rank models were built and killed before the functor was found — the data said repeatedly "not a dimension," and the tool changed.

- **The realization is *proven for odd characteristic*.** The symmetrization in play is the swap `τ` of the two pair-variables; `ρ` only selects which classes are live. The map `σ = I+τ` is **surjective onto `Sym²V` in odd characteristic** — so the coupled identity `coupled = dim(Sym²V)·c²` is a theorem there. In **characteristic two** it falls short by exactly `p^v−1` dimensions, the cokernel being `(Z/2)^{p^v−1}`.

- **The characteristic-two obstruction is *generic* — the swan is ruled out of the class layer.** That `(Z/2)^{p^v−1}` torsion depends only on `dim V`, not on the Fermat data: it is the universal torsion of the swap involution on `V⊗V`, identical for Fermat and for a generic space of the same dimension (proven; the realization and torsion questions are literally the same question, `σ` surjective `⟺ p` odd, converging byte-exact). So the **within-pair class layer is closed as a site for a Fermat-specific torsion counterexample** — one candidate room for the swan, ruled out with data, by Smith normal form. This fixed a permanent campaign rule: torsion is measured by Smith form / rank drop, **never** by equality of `F_p`- and `Q`-dimensions — equal dimension does not imply torsion-free. Three mis-constructions were self-caught and graveyarded along the way (a dimension argument that violated exactly that rule; a global ρ-multiplication operator that mixed layers; a confusion of ρ-multiplication with symmetrization), each logged as a trap for the next attempt.

Honest scope, as everywhere here: the coupled identity is a theorem **in odd characteristic**; in characteristic two the obstruction is identified and shown generic, but is not an `F_p`-equality. The result closes **one layer** — the within-pair class layer. The full block, the B-factor, the cross-pair structure, and the high-dimensional ambient module remain open, and remain where a swan could still live. The verifier in the linked document recomputes every number — the quotient law, the `Sym²` identification, the `V⊗V = Sym² ⊕ Λ²` closure, and the Smith-form torsion in each characteristic — from scratch.

### The block-rank theorem, and the red link that made it unconditional — the capstone

The structural chain above — localization, the product law, the closed walk, the within-pair functor — converged on a single capstone, now standing as a theorem in its own document: **[THE_NAIL_THEOREM.md](THE_NAIL_THEOREM.md)** (technical paper, [PDF](THE_NAIL_THEOREM_CLOSED.pdf)).

**The theorem.** For every block dimension `d` and coupling depth `ℓ`, the rank a CRT block contributes is exactly the Degtyarev–Shimada value:
```
rec(d, ℓ) = DS_{2(ℓ−1)}(d+1),    for all d ≥ 0, ℓ ≥ 1.
```
Equivalently, that rank is the constant term of a closed lattice walk of `2ℓ` steps on `Z^⌊d/2⌋`. What was measured byte-exact across the campaign — the General Product Law, the *meshing* of the recursion ladders — is now proven, not a pattern. The proof is a chain of module-dimension identities read from the Degtyarev–Shimada source itself: the measured block **is** the DS core module (their tensor decomposition Cor 1.7, with a free tail isolating the core dimension cleanly), the core dimension **is** the closed walk (their Remark 4.4 applied one dimension down), and the depth step is a finite holonomic operator uniform in `d` (Lipshitz 1988). No appeal to "two sequences share a recursion" is made — that would not force equality; the tensor identity does.

**The one condition — and the red link that discharged it.** The theorem rested on a single identification, named openly as a condition rather than buried: that the campaign's measured CRT all-`A` block is the Degtyarev–Shimada core. That *dictionary* has two halves, and only one was ever open. The **geometric** half — that the `A`-idempotent `e_A` is the coordinate-zeroing cut `X(2s)` of DS §4.6 — was confirmed *verbatim* against the source. The **faithfulness** half — that the block measured over `F_p`, carrying the nilpotent `(t−1)`-primary tower (multiplicity `p^v−1` over `F_p`, against `1` over `C`), equals the DS core's reduction over `Z` **without phantom torsion injected when `Z → F_p`** — was the genuinely open link. It was carried by measurement: four cells, `dimA ∈ {1,2,3,7}`, characteristics 2 and 3, including the tallest manageable tower (`m = 8`, `dimA = 7`, tower height 7), every one giving **zero** injected torsion, by two independent instruments with a blindness control.

The **red link** turned that measurement into a proof — pen-and-paper, characteristic-independent. The integral block closure is shown to be a **free `Z`-module**, and a free module of rank `r` reduces faithfully modulo every prime (`Z^r ⊗ F_p = F_p^r`, no injection). The mechanism is a single cyclotomic identity. The within-pair closure is generated by the triangle `ρ`; collecting `y`-powers, its `y⁰`-component is `c₀ = 1 + x + ⋯ + x^{m−2}`, and the cyclotomic relation `x^{m−1} = −(1 + ⋯ + x^{m−2}) = −c₀` gives

```
x · c₀ = (x + ⋯ + x^{m−2}) + x^{m−1} = (c₀ − 1) + (−c₀) = −1.
```

So `x·c₀ = −1`: the shift-orbit of `c₀` reaches the unit `1` and therefore spans the whole ring. `ρ` is a cyclic vector, the within-pair closure is `Z[t]/φ` (characteristic polynomial exactly `φ`), hence free; a block at depth `ℓ` is a tensor of `ℓ` such free modules, hence free of rank `(m−1)^ℓ`; and freeness makes the `F_p` reduction faithful in **every** characteristic — including characteristic 2, where the tall tower lives. This is precisely *why* the within-pair closure is saturated while the image of `(t−1)` (Smith form `[1,…,1,m]`, index `m`) is **not**: the triangle *regenerates* the ring, the operator `(t−1)` *contracts* it. An earlier argument — "the shift is a unit, so its orbit is saturated" — was **refuted with data** (the unit-built `(t−1)` has non-saturated image) and replaced by the cyclotomic mechanism, which is sound; the dead argument is in the record.

With the geometric half textual and the faithfulness half a theorem, the dictionary is **discharged**, and the block-rank law is **unconditional**. Every number in the proof is recomputed from scratch by a self-contained verifier (`x·c₀ = −1` for `m = 4..12`; characteristic polynomial `= φ`; cyclicity; the `(t−1)` index; the `σ`-image 2-torsion that rules out the wrong mechanism).

**What it does not give — stated without perfume.** The red link proves the reduction injects no *spurious* torsion, so every primitivity verdict the campaign measured is genuine. It does **not** prove that *genuine* integral torsion is absent in some unmeasured block. That is Degtyarev–Shimada **Conjecture 1.2**, the *swan*, and it **remains open**. What the theorem gives the hunt is a rigorous map: torsion lives in one block (localization), the per-block value is fixed and the refinement is faithful, so a counterexample can only hide in a recursive-dimension `≥ 4` block that deviates from the DS value — `recdim 0, 2` are torsion-free by DS Cor 1.7. The search is thereby reduced from unbounded to pointed.



The work above left the `F_p` isomorphism resting on matching each block's reduced factor to a DS object. Pushing on that match produced a chain of catches:

- **The block is *not* DS's §17 coordinate cut — proven with a number.** The block's all-B rank and `X(2s)`'s rank are *different numbers* (`(4,6)`: block all-B = `400`, `DS₄(6) = 1001`). So the block is **two** reductions stacked: the §17 dimension cut (geometric, DS-proven) and a **grade shift** — purely algebraic, the new object.

- **The grade shift is "peel the Jordan tower," with a closed form.** It sends degree `m` to grade `dimB + 1 = m − dimA`. Validated out of sample up to `v = 2`. Target: prove a block of B-dimension `dimB` carries rank `DS₂(dimB + 1)`.

- **The Freedom Sweep — the invariant is a *dimension*, not a character.** A sweep of **12 cells** (primes 2,3,5,7; `v = 1` and `v = 2`) verified byte-exact: every cell satisfies `all-B = DS₂(dimB + 1)`, no swan. The decisive find: **three pairs with the same `dimB` but different modular structure give identical rank** — including a pair that *crosses the characteristic* (`dimB = 12`, one char 3, one char 2, both `396`). The rank is **blind** to Jordan type, `p`-power thickness, fat-point count — it sees **only `dimB`**. The conserved invariant is not a character; it is a single dimension. Any proof can ignore `p`, `v`, and the prime-to-`p` part entirely.

- **The clean attack, after two dead routes.** A fixed-relation ring deformation (reproduces the `(6,6)` Frontier failure) and a column-fill trace (reduces to the proven localization) were **buried with data**. The surviving route reframes the rank as `dimB³ − (survivors)`, survivor count structure-blind with closed form `(dimB − 1)³ + [dimB even] = dimB³ − DS₂(dimB + 1)`. The open problem, sharp: prove a **dimension-preserving bijection between fat-case and reduced-case survivors**, using `dimB` alone.

Said plainly: the open question is no longer "is the block a DS object" but "why does one dimension, `dimB`, fix the rank." Across these sessions: more successively finer catches, more routes buried honestly, and still **zero false theorems**.

---

## Reproducibility

Every engine is a single self-contained C++ file — exact modular arithmetic, no floating point, single-threaded. Pick any cell, build its engine, reproduce the verdict. For `(6,6)`:

```
g++ -O3 -march=native -std=c++17 -funroll-loops engines/ROSETTA_STAR.cpp -o ROSETTA_STAR
caffeinate -dims taskpolicy -c utility ./ROSETTA_STAR 6 6 2>&1 | tee my_run.log
```

Compare against [`logs/ROSETTA_STAR_6_6_run1.log`](logs/ROSETTA_STAR_6_6_run1.log) — agreement to the digit. Each engine prints a live heartbeat and aborts cleanly at a 5.4 GB guard before touching swap.

The structural results are independently checkable — each claim has a self-contained Python verifier that recomputes DS values from scratch:

```
python3 verifiers/CENTRALITY_DETECTOR_VERIFIER.py    # localization: idempotents central, module splits
python3 verifiers/GENERAL_PRODUCT_LAW_VERIFIER.py        # the per-block product law, incl. blind dimA=4
python3 verifiers/BLOCK_COUNT_LAW_VERIFIER.py            # the sofa block-count, vs direct factorization
python3 verifiers/RIFLE_FINAL.py 4 35                    # predict a cell from the sofa, with [FIRM]/[CONJ]
```

The within-pair functor is checked from scratch too — the quotient law, the `Sym²` identification, the `V⊗V = Sym² ⊕ Λ²` closure, and the Smith-form torsion in each characteristic are recomputed by the verifier block inside [THE_WITHIN_PAIR_FUNCTOR.md](THE_WITHIN_PAIR_FUNCTOR.md).

**Repository layout**

```
engines/      the C++ verifiers — one self-contained file each
logs/         the raw run output behind every number in this README
verifiers/    the Python verifiers (recompute DS from scratch)
assets/       the diagrams
THE_NAIL_THEOREM.md          the block-rank theorem, now unconditional (capstone)  ← updated
THE_NAIL_THEOREM_CLOSED.pdf  the block-rank theorem, technical paper (closed)      ← new
THE_FRONTIER_6_6.md          the (6,6) discovery, in full
THE_BLOCK_DECOMPOSITION.md   the recursive block decomposition, in full
THE_WITHIN_PAIR_FUNCTOR.md   the within-pair functor (Sym²), proven for odd characteristic
THE_CLOSED_WALK_LAW.md       the closed-walk reading of the DS rank polynomial
THE_LOCALIZATION_THEOREM.md  the torsion-localization theorem, isolated with a worked idempotent
SIXTEEN_VERDICTS.md          the sixteen certified verdicts, standalone (explicitly NOT a theorem)
```

Every verdict is reproducible from the matching engine + log; every structural claim, from the matching verifier. Nothing here asks for trust — it asks to be checked.

---

## Discipline

- **Numbers from logs only.** If a number is not in a file, it is not claimed.
- **Both halves, every cell.** A one-sided computation is never a verdict.
- **Cross-prime mandatory** for the complex half.
- **Byte-exact validation gates** against known cells before any engine is trusted.
- **Torsion is measured by Smith form / rank drop, never by `dim(F_p)` vs `dim(Q)`.** Equal dimension does not imply torsion-free; this rule was fixed when an early dimension argument was caught violating it, and it governs every future swan candidate.
- **Proven, validated, and conjectural are labelled distinctly.** Localization is proven; the per-block rank law is now a **theorem for every block dimension** ([THE_NAIL_THEOREM.md](THE_NAIL_THEOREM.md)), its one condition discharged by the red link (the `F_p` refinement proven faithful, characteristic-independent); the within-pair `Sym²` identification is proven, its realization a theorem for odd characteristic with the char-2 obstruction shown generic; the integral-torsion question (Conjecture 1.2, the swan) is flagged **open** and is never conflated with the value theorem.
- **Failed approaches are documented, not hidden** — the dead veins (the refuted dictionary, the vacuous total-check, the engine graveyard, the within-pair *triangle law* killed by its own out-of-sample test, and three self-caught within-pair mis-constructions) are part of the scientific record.
- **Priority fixed by literature search before any claim.** Classical facts cited as classical; the rank formula credited to DS Remark 4.4; published verdicts labelled confirmation; only the Frontier, the block decomposition, the block-rank theorem and its red link, the within-pair functor, and the engineering are named as new. The block-rank theorem proves DS's *own* values hold at all depths via DS's *own* tensor and generating identities — its novelty is the closed proof of the meshing and the faithfulness of the `F_p` reduction, not a new rank formula.

---

## Why this matters

Beyond the conjecture itself, the same primitivity questions sit underneath Néron–Severi lattices and the algebraic cycles of these varieties. The block decomposition adds an explicit, recursive anatomy of the integral cohomology lattice's torsion structure, with a *proof* that any torsion is confined to a single computable block — the exact place AMV left blank — a proven look *inside* that block (the within-pair coupling is `Sym²V`, a theorem in odd characteristic), and now a **theorem fixing the rank every block contributes at every coupling depth**, with the modular reduction proven faithful so the integral and complex pictures provably agree block by block. And the engineering stands on its own: exact sparse linear algebra over finite fields driven from 16 bytes per entry to 1.07 on commodity hardware is a reusable result independent of the mathematics it serves.

A clear word on scope: this campaign concerns the **integral** Hodge conjecture for **Fermat** varieties — a specific, bounded problem. It is *not* the Clay Millennium Hodge Conjecture (the rational statement) and makes no claim on it. The block-rank theorem fixes the value side; it does not resolve whether torsion exists — that is Conjecture 1.2, and it stays open.

The work continues. The torsion — the *swan* — has not been found; every cell so far is primitive. Eleven cells stand decided beyond the published table, five more confirm it byte-exact, the DS rank formula is verified well past where they ran it, the Frontier is named, the CRT split is laid open with a proven torsion-localization, the working face reached inside a single block and proved its interior (`Sym²V`, odd characteristic), and the recursive structure of the whole split is now a **theorem**: the rank every block contributes, at every coupling depth, for every block dimension, is the Degtyarev–Shimada value — with the `F_p` reduction proven faithful by the red link, so the result is unconditional. What remains is the swan itself. The theorem does not decide it; it maps it — a counterexample can only live in a recursive-dimension `≥ 4` block deviating from the value, and the hunt is now pointed there rather than wandering an unbounded space. The next stones are chosen, and the standard that governs them is the one that produced sixteen byte-exact verdicts, one capstone theorem, and zero false theorems.

---

## References

1. A. Degtyarev, I. Shimada, *On the topology of projective subspaces in complex Fermat varieties.* J. Math. Soc. Japan **68**:3 (2016), 975–996. arXiv:1405.4683.
2. T. Shioda, *The Hodge conjecture for Fermat varieties.* Math. Ann. **245** (1979), 175–184.
3. N. Aoki, T. Shioda, *Generators of the Néron–Severi group of a Fermat surface.* In: Arithmetic and Geometry, Progress in Mathematics **35**, Birkhäuser (1983), 1–12.
4. M. Schütt, T. Shioda, R. van Luijk, *Lines on Fermat surfaces.* J. Number Theory **130**:9 (2010), 1939–1963. arXiv:0812.2377.
5. A. Degtyarev, *Lines generate the Picard groups of certain Fermat surfaces.* arXiv:1305.3073.
6. E. Aljovin, H. Movasati, R. Villaflor, *Integral Hodge conjecture for Fermat varieties.* J. Symbolic Computation **95** (2019), 177–184. arXiv:1711.02628.
