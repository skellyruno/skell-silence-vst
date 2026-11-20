# Skelly Release Coverage — Checkpoint 51

**Recorded:** 2026-11-20, 00:28 ET  
**Selected project:** Skell Stop / StopDial — Windows x64 VST3  
**Repository:** https://github.com/skellyruno/skell-stop-vst  
**Product follow-up:** https://github.com/skellyruno/skell-stop-vst/pull/7  
**Parent product PR:** https://github.com/skellyruno/skell-stop-vst/pull/6  
**Status:** Parent PR #6 exact-head Windows/Linux CI passed. Draft PR #7 exact-head run #44681318213 also completed SUCCESS; the private-only upload guard is verified for the public PR event. The product upload was skipped and only the separate UI diagnostic artifact was produced. No merge or release.

This append-only checkpoint supplements checkpoint 50. It does not replace prior evidence or change the parent PR #6 branch, existing binaries, DSP, UI, presets, parameter IDs, automation IDs, saved state or FL Studio projects.

## 1. Selection and rotation

The previous ledger selection was SkellGlitch / `skell-gate-vst` (checkpoint 50). This run selected a different plugin: StopDial.

The strongest current release blocker was a public-distribution leak in an otherwise passing Windows VST3 preview workflow:

- StopDial's PR #6 exact-head run [#44625564418](https://github.com/skellyruno/skell-stop-vst/actions/runs/44625564418) completed successfully on source head `3d1a5f2253b005cfd5675c7f8d69d03e97dd5b6c`.
- The Windows job passed CMake/MSVC VST3 compilation, JUCE CTest 2/2, the Python package verifier, install/update/rollback integration, pluginval strictness 5 and offscreen UI rendering. The Linux sanitizer-backed DSP job also passed.
- The workflow then uploaded the complete installable product package as Actions artifact #14577734466 even though `skell-stop-vst` is a public repository. The artifact is 2,926,553 bytes and includes the staged product package. This is a real preview-distribution exposure, not just a missing-documentation issue.
- The product artifact is already public. This run did not delete it, change repository visibility, or attempt to revoke access.
- StopDial was not owned by the latest Preset Audit, Ecosystem, Websites or Nightly source branches. The currently active Master, EQ, Preset, Rack, SkellForge, SkellCore, SkellWorld, Project Hub and website work was left untouched.
- Skell Delay remains the first owner-side FL Studio acceptance candidate in the Nightly review, but its release/legal branch chain is already active. No Delay branch was edited.
- DeEsser remains parked.

### Latest cross-automation evidence checked

- **Ecosystem Development:** latest completed run `fe0d26e8-8bac-8330-9298-3412514a59ea` advanced SkellWorld PR #19's mobile panel layout (Chromium 320/375/650/1440 checks passed; dashboard tests 35 passed, 1 skipped; Windows portable application passed) and reviewed SkellForge PR #31 dependency readiness (Ubuntu/Windows CLI tests and generated Windows VST3 smoke passed). It also advanced Skell Master PR #30's sample-rate-adaptive true-peak guard; latest run #44671847597 was still pending. No branch from that lane was touched.
- **Preset Quality Audit:** latest scheduled run `b2d911a1-c5e0-8330-8938-67b72b11cbc7` recorded failure. Its latest successful result remains Run 11, not the failed run: Alchemist alignment was corrected to 49 samples, the 55-entry experimental bank was audited without promotion, and Rack/EQ/Master test work was reported. No Preset-owned branch was edited.
- **Websites Development:** latest completed result is V122; a newer run `b846d40b-918c-832b-9fba-1f6f026a6818` was in progress. V122 reported Artist V107 with 100/100 tests, Creative 44/44, Preset Showcase 12/12, and Quick4/JUCE 8.0.12 restored. No website, DNS or deployment was changed.
- **Nightly Blueprint:** latest completed review `9612a6d4-3d94-832b-9f41-c2561fe78b87` created and validated three PDFs, but still recorded zero verified commercial releases and zero verified revenue. Skell Delay remained the first manual FL Studio acceptance candidate, with SkellyChoir second.

## 2. Protected parent baseline

**Parent product PR #6:** https://github.com/skellyruno/skell-stop-vst/pull/6  
**Parent branch:** `fix/stopdial-normalize-moduleinfo-before-package-20261119`  
**Parent head:** `3d1a5f2253b005cfd5675c7f8d69d03e97dd5b6c`  
**Parent exact-head run:** [#44625564418](https://github.com/skellyruno/skell-stop-vst/actions/runs/44625564418)

Confirmed parent results:

- Linux `dsp-regression`: sanitizer-enabled native DSP tests passed.
- Windows x64: CMake configure and MSVC Release VST3 build passed.
- JUCE CTest: 2/2.
- Python fail-closed package verifier: 17/17.
- Staged VST3 bundle validation passed.
- PowerShell install, idempotence, update, backup and rollback integration passed.
- pluginval strictness 5 passed.
- Offscreen JUCE UI renders were uploaded.
- Product artifact #14577734466 was uploaded unconditionally from the public repository.
- Parent-run UI artifact #14580260198 was uploaded but not re-downloaded. The new PR #7 run's separate UI artifact #14605035916 was downloaded and inspected below.

The parent PR #6 source fix normalizes Steinberg trailing commas in the staged `moduleinfo.json` before package checksums are generated and rejects unnormalized JSON5 in an already-built ZIP. PR #6 and its branch remain unchanged.

The parent product artifact was downloaded from Actions artifact #14577734466 into a private working copy and independently inspected.

- Archive: 2,926,553 bytes; ZIP CRC passed; SHA-256 `5d5d45eea32c2e4c96c04b274e67de3506997ff94e8a54f3a9141976fdceceef`.
- Exactly six entries: installer, Windows install guide, release manifest, checksum file, one flat `StopDial.vst3` bundle, and its single `Contents/x86_64-win/StopDial.vst3` module. No nested ZIP and no Standalone EXE.
- Module: AMD64 PE32+; 6,657,024 bytes; SHA-256 `2b5bd37512a06e87c8be0dc0f31bfc9e049da1a48a0f1f627ba03c3d635526f4`.
- `moduleinfo.json`: strict RFC 8259 JSON parse passed; StopDial 2.3.1; two class IDs `ABCDEF019182FAEB536B417553643031` and `ABCDEF011234ABCD536B417553643031`.
- All five `SHA256SUMS.txt` entries matched. The manifest records `pr_head_commit=3d1a5f2253b005cfd5675c7f8d69d03e97dd5b6c` and the workflow's synthetic merge `source_commit=f3d496c8ce77ed8e73e4934712374220d493d84c`.

This is an inspected working copy, not a claim that the historical public artifact became private. The original Actions artifact remains present and public; no repository setting or artifact was changed.

## 3. New source/workflow implementation — PR #7

**Draft PR:** https://github.com/skellyruno/skell-stop-vst/pull/7  
**Branch:** `fix/stopdial-withhold-public-preview-artifact-20261120`  
**Base:** PR #6 branch `fix/stopdial-normalize-moduleinfo-before-package-20261119`  
**Base SHA:** `3d1a5f2253b005cfd5675c7f8d69d03e97dd5b6c`  
**First implementation commit:** `d58f6d8ba107a4d055267e23a5739db74799af55`  
**Latest commit:** `65bdd3fe02be0aef35f4128d36f002e3df407ca1`

Three files changed:

1. `.github/workflows/build.yml`
   - The installable Windows VST3 artifact upload now runs only when `github.event.repository.private == true`.
   - Public/internal/unknown repository visibility does not produce the installable product artifact.
   - Public-repository runs emit an explicit Actions notice explaining that the product artifact is withheld.
   - Windows build, CTest, package verification, installer/update/rollback tests, pluginval and the separate UI diagnostic artifact remain enabled.
2. `tests/test_release_workflow.py`
   - Adds three dependency-free workflow-contract regressions: private-only product upload, public-repository withholding notice, and discovery of the release-contract tests.
   - The Windows verifier step now discovers `test_*.py`, so these tests run with the existing package-verifier suite.
3. `CHANGELOG.md`
   - Records the public-repository preview withholding policy and explicitly states that existing historical artifacts are not deleted.

No C++/DSP, editor UI, VST3 identity/class IDs, parameter IDs, presets, automation IDs, saved-state format, or installer install/update/rollback behavior changed.

## 4. Exact-head CI status — run #44681318213

[New PR #7 exact-head workflow run #44681318213](https://github.com/skellyruno/skell-stop-vst/actions/runs/44681318213) targets head `65bdd3fe02be0aef35f4128d36f002e3df407ca1`.

- Linux sanitizer DSP CTest: **1/1 PASS**.
- Windows x64 MSVC VST3 build: **PASS**.
- JUCE CTest: **2/2 PASS**.
- Python release/package tests: **21/21 PASS**, including all three new workflow-contract tests.
- PowerShell installer/update/rollback integration: **PASS**.
- pluginval strictness 5: **PASS**.
- Public-repository notice: emitted as intended.
- Installable product artifact upload: **SKIPPED** because the repository is public.
- The only new artifact is UI diagnostic artifact #14605035916 (663,345 bytes; SHA-256 `6b09715ee2c7ec25f300e80c4f09703c2a49ef79efe5d3eab97ed67799339a6b`); no installable product artifact was uploaded.

### UI screenshot review

The six-PNG artifact contains real JUCE-rendered editor captures. I inspected the main editor at 435×535, 725×892 and 1087×1338. No visible clipping or control overlap was found. The compact view is dense and its text is smaller, but controls and labels remain separated. UI source was not changed; menu interactions and local Quick4 capture remain unverified.

The prior parent run is green, but that does not validate this new branch. Keep PR #7 draft.

### Environment limitations

A local `git clone` attempt could not resolve `github.com` in the container. Remote GitHub Actions is running, but this run did not perform a local Windows build, native Quick4 capture, FL Studio launch, owner-machine install, or audio A/B. No new UI screenshot is claimed.

## 5. Release readiness matrix

| Gate | Status | Evidence / remaining work |
|---|---|---|
| Windows x64 VST3 build | Parent PASS; new PR pending | Parent run #44625564418 passed; wait for PR #7 run #44681318213 |
| Package metadata / bundle | Parent PASS | PR #6 strict JSON staging and package verifier passed |
| pluginval | Parent PASS | Strictness 5 passed on parent; rerun on PR #7 exact head |
| Private preview distribution | Private chat copy available; public upload guard verified | Original artifact #14577734466 remains public; new run #44681318213 uploaded no product artifact; establish a private release location for future preview builds |
| Install/update/rollback | Parent CI PASS; owner machine unverified | Parent PowerShell tests passed; target Windows profile not tested |
| FL Studio host compatibility | UNVERIFIED | Scan/load, bypass, transport, automation, preset/state recall, save/reopen and old-project compatibility |
| Sound / DSP A/B | UNVERIFIED | Real musical A/B, clipping/NaN/denormal/glitch review and user listening approval |
| CPU / latency | UNVERIFIED | Measure on the target Ryzen/Vega machine and actual FL Studio audio device |
| UI / Quick4 | Windows JUCE captures inspected; Quick4 partial | Current run UI artifact #14605035916 inspected at 435×535, 725×892 and 1087×1338; no visible clipping/overlap, compact text small. UI source unchanged; menus and local Quick4 remain unverified |
| Licensing / attribution / EULA | BLOCKED | Confirm JUCE/VST3 SDK and asset rights, notices and customer terms |
| Vendor / support / signing | BLOCKED | Factory Info URL confirmation, support email, signing identity and certificate remain owner-controlled |
| SkellyHub updater / rollback | NOT VERIFIED | Integrate only after private artifact location and manifest contract are approved |
| Website storefront / email signup | NOT VERIFIED | Website automation owns deployment; no deployment performed |
| Pricing / trial | AWAITING OWNER APPROVAL | No price, trial length or commercial entitlement assumed |

## 6. Next step

1. PR #7 exact-head Windows/Linux CI and the public-repository upload guard are verified; keep the PR draft until owner-side gates are complete.
2. Keep the existing public artifact #14577734466 intact; decide separately whether the repository should remain public. No visibility change is made here.
3. Establish an owner-controlled private distribution location before generating another installable preview artifact.
4. Run target Windows/FL Studio acceptance: scan/load, transport/bypass, automation, presets/state, save/reopen and old-project compatibility; then perform real audio A/B and target-hardware CPU/latency tests.
5. Resolve licensing/attribution, EULA, vendor/support contact and signing before any commercial release.

The next Release & Launch selection must be a different non-DeEsser plugin/project. Continue the six-run portfolio balance; do not return to StopDial unless a new critical regression appears. No merge, tag, public release, website deployment, DNS change, payment or irreversible repository setting change occurred.
