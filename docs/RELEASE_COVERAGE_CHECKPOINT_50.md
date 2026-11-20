# Skelly Release Coverage — Checkpoint 50

**Recorded:** 2026-11-20, 00:05 ET  \
**Selected project:** SkellGlitch / Skell-Glitch (Windows x64 VST3)  \
**Repository:** https://github.com/skellyruno/skell-gate-vst  \
**Product PR:** https://github.com/skellyruno/skell-gate-vst/pull/10  \
**Parent release PR:** https://github.com/skellyruno/skell-gate-vst/pull/9  \
**Status:** Exact-head Linux and Windows CI completed SUCCESS. The installer-inclusive ZIP was generated and checksum-verified in CI but deliberately withheld because the repository is public. FL Studio and owner-machine acceptance remain UNVERIFIED.

This checkpoint is append-only and supplements checkpoint 49. It does not change or replace the prior SkellyTune report, PR #9, the original source branch, VST3 identity, presets, UI, host state, automation IDs, or FL Studio projects.

## 1. Selection and cross-automation rationale

The previous Release & Launch selection was SkellyTune / AutoTune. This run deliberately selected a different non-DeEsser plugin.

SkellGlitch won because it had the strongest verified Windows release baseline and one clearly bounded release blocker that could be advanced without changing audio DSP or the UI:

- Parent PR #9 exact-head run [#44664854681](https://github.com/skellyruno/skell-gate-vst/actions/runs/44664854681) passed its Linux release/archive tests and DSP CTest, Windows x64 MSVC VST3 build, real JUCE UI smoke, Windows CTest, pluginval strictness 5 (1 passed / 0 failed), Steinberg VST3 validation, package verifier, and deterministic preview ZIP generation.
- The parent workflow explicitly withheld the product ZIP because skell-gate-vst is public. Its earlier PR #8 VST3 artifact remains publicly accessible; the PR #9 workflow cannot retroactively restrict that historical artifact.
- The parent PR #9 documentation identified the missing per-user installer, update and rollback as open release gates. This was a practical, isolated packaging improvement that did not require a commercial release decision.
- SkellyTune was not repeated: its latest Release run found four offline DSP failures (vibrato/glide pitch motion, onset trace/latency, diagnostic audio identity, and scalar/SIMD exact parity).
- Skell Master was not selected because the Preset Audit lane has active Master/Preset/Rack/EQ work and the latest observed Master release PR #30 had a failing exact-head workflow. No active Master branch was edited.
- Skell Delay remains the first owner-side FL Studio acceptance candidate in the Nightly Blueprint; its current release/installer/legal PR chain is already active. No Delay branch was edited.
- Skell Key had a green Windows packaging/installer PR #14, but key-detection accuracy and owner-host acceptance remain separate. No Key branch was edited.
- DeEsser remains parked. No concurrent product branch was modified.

### Latest automation coordination

- **Preset Quality Audit:** latest completed Run 11 report advanced Alchemist reference analysis and the Preset factory-bank audit. A newer audit run was in progress at the time of this check. Its active Master, EQ, Preset and Rack branches were left untouched.
- **Ecosystem Development:** latest completed run advanced SkellWorld PR #19 mobile panel layout and SkellForge PR #31 dependency-readiness checks. The SkellForge checks passed; the Foundation lane remains responsible for SkellForge/SkellNative/SkellCore. No shared branch was edited.
- **Websites Development:** V122 completed Artist V107 and regression-tested Creative and Preset Showcase. Artist tests 100/100, Creative tests 44/44 and Preset QA commands 12/12 passed. No website was deployed, and no DNS or payment action occurred.
- **Nightly Blueprint:** latest review still reports zero verified commercial releases and zero verified revenue. Skell Delay remains the first manual FL Studio acceptance candidate, with SkellyChoir second. November 20 is the scheduled Letters From The Grave release date; website work remains separately owned.

## 2. Parent baseline — PR #9

**Parent branch:** `release/glitch-deterministic-preview-archive-20261117`  \
**Parent head:** `f414bd4b1dc5e20c472605d89bd14280967ed2ba`  \
**Parent run:** [#44664854681](https://github.com/skellyruno/skell-gate-vst/actions/runs/44664854681)

Confirmed parent results:

- Linux: 28/28 Python release-verifier/archive tests and portable DSP CTest 1/1.
- Windows: JUCE 8.0.12 / pinned SkellCore configure, MSVC x64 VST3 build, Windows CTest 1/1, real offscreen JUCE UI smoke at four sizes, VST3 bundle verifier, pluginval strictness 5, Steinberg VST3 validator exit 0, deterministic ZIP and checksum generation.
- Manifest: SkellGlitch 1.7.3 / Skelly / Windows x64.
- VST3 module SHA-256: `e30eb08d46c9236a640fc80de6f5d8a1dcc0e801f02e3a0793f09f5341f49e72`.
- moduleinfo.json SHA-256: `81db5ff87d3252d2ca88498c7792a012fcf464a4a12dc31af9d63ca497b41ec2`.
- Deterministic ZIP SHA-256: `7a1311d2d5ecc857d1ee544a6173c6f4752c3db82bce3ac4f26aad832f7bf4d6`.
- Product ZIP upload: skipped as intended because the repository is public. No current product-download link exists.
- UI screenshot artifact [#14597547792](https://github.com/skellyruno/skell-gate-vst/actions/runs/44664854681/artifacts/14597547792): 1,325,575 bytes; SHA-256 `578a9b489eb269546152e1bc39a7ca5eb586bf9082691e1e6cb97275309f830d`.

### Independent screenshot inspection

Downloaded artifact #14597547792 and inspected its actual seven PNGs, including the 480×360 compact editor, 960×720 default editor, 1200×900 large editor, and 960×720 Settings panel. The larger layouts showed no visible clipping or control overlap; the compact 480×360 layout remains dense with smaller text, but controls were not visibly colliding. The Settings panel and four main controls remain inside the editor bounds. This run did not change UI source, so these are baseline observations, not post-change UI claims.

Downloaded UI artifact path in the run container: /mnt/data/SkellGlitch-UI-Snapshots.zip. ZIP SHA-256: `578a9b489eb269546152e1bc39a7ca5eb586bf9082691e1e6cb97275309f830d`.

## 3. Product source and packaging implementation — PR #10

**Draft PR:** https://github.com/skellyruno/skell-gate-vst/pull/10  \
**Branch:** `release/glitch-per-user-installer-rollback-20261120`  \
**Parent/base:** PR #9 branch `release/glitch-deterministic-preview-archive-20261117`  \
**Base SHA:** `f414bd4b1dc5e20c472605d89bd14280967ed2ba`  \
**Head commit:** `6313412d14c0081d815b8cf65893f43a3ca7dabc`  \
**Commit message:** feat(release): add safe per-user VST3 preview install and rollback  \
**Change size:** 7 files, 952 additions, 19 deletions; one coherent commit.

Implemented:

1. Added scripts/Install-SkellGlitchPreview.ps1, requiring PowerShell 7 and Windows.
2. Defaults to %LOCALAPPDATA%/Programs/Common/VST3/SkellGlitch.vst3; machine-wide destinations are rejected.
3. Uses a per-user backup directory under %LOCALAPPDATA%/SkellGlitch/Backups.
4. Validates the package's exact top-level inventory, release-manifest provenance, source SHA, workflow run/attempt fields, module and moduleinfo hashes, module size, version, file-level SHA256SUMS.txt, and VST3-only bundle layout before changing files.
5. Rejects reparse points/junctions, unsafe checksum paths, unlisted or extra files, duplicate VST3 modules, standalone executables, mismatched version metadata and tampered module bytes.
6. Stages and verifies the new bundle before replacing the installed bundle.
7. Preserves the previous bundle in a unique backup before an update. Reinstalling an identical bundle is a no-op and does not create another backup.
8. Adds explicit rollback to a selected backup; the version being rolled back is preserved as a separate safety backup. A first-install rollback removes only the preview bundle.
9. Supports -WhatIf; it does not modify FL Studio projects, presets, parameter/automation IDs or host state.
10. Makes the installer a required file in scripts/package_windows_vst3.py, so it is included in the deterministic ZIP and its internal SHA256SUMS list.
11. Adds tests/Test-SkellGlitchPreviewInstaller.ps1 for real Windows integration coverage: dry-run, first install, idempotent reinstall, update, rollback, first-install removal, tampered module, unexpected files, checksum path traversal, and rejection of machine-wide/out-of-scope paths.
12. Updates .github/workflows/build.yml to copy the installer into the staged package and run the PowerShell integration test before ZIP creation. The existing private-repository-only product artifact guard remains unchanged.
13. Updates the packaged preview instructions and README.

No C++ DSP, UI source, JUCE/SkellCore pin, CMake plugin target, VST3 vendor/product IDs, class IDs, parameter IDs, automation IDs, factory preset IDs, state serialization or version changed. No existing binary or owner project was overwritten.

## 4. Exact-head validation — run #44678649998

[PR #10 exact-head workflow run #44678649998](https://github.com/skellyruno/skell-gate-vst/actions/runs/44678649998) targets commit 6313412d14c0081d815b8cf65893f43a3ca7dabc. Both workflow jobs completed SUCCESS.

**Linux job — PASS**

- Python release/archive unit tests: 30/30 passed.
- Portable C++ DSP test executable built successfully.
- DSP CTest: 1/1 passed; stress output reported 768,000 stereo frames and a finite checksum.
- The archive tests confirm the installer is included and required; workflow-contract tests confirm the Windows installer integration runs before archive creation.

**Windows x64 job — PASS**

- JUCE 8.0.12 and pinned SkellCore checkout/configure passed.
- Windows x64 MSVC VST3 and JUCE UI smoke targets compiled successfully.
- Windows DSP test executable compiled; Windows CTest 1/1 passed.
- Real JUCE offscreen UI smoke rendered and validated four window sizes.
- VST3 package staging and release-manifest verification passed.
- pluginval v2.0.0-beta3 strictness 5: 1 passed, 0 failed. Cold/warm open, editor, audio processing, plugin state, automation, parameter, bus-layout and DPI checks completed. Embedded VST3 validator exited 0.
- Windows PowerShell 7 installer integration printed `SkellGlitch installer integration tests: PASS`. Dry-run, first install, identical reinstall no-op, update, rollback to previous version, first-install removal, tampered module rejection, unexpected file rejection, checksum path traversal rejection, and machine-wide/out-of-scope path rejection passed.
- The integration suite uses a synthetic test VST3 fixture to validate installer behavior. It does not replace owner-machine installation or FL Studio host acceptance.
- Deterministic installer-inclusive preview ZIP was generated and checksum sidecar written. ZIP SHA-256: `5cabd20aaba54ed52c7cbe5bf59793629de3ffb54c91e7cfa6f6771435ae3132`.
- Release manifest module SHA-256: `54900d798db4bf2dd8566c5f7400a147cf57ba6e4402c724d212413c76c43827`. moduleinfo SHA-256: `81db5ff87d3252d2ca88498c7792a012fcf464a4a12dc31af9d63ca497b41ec2`.
- The product ZIP upload step was skipped as intended because the repository is public. No product ZIP artifact or download link exists. The workflow uploaded only the real JUCE UI snapshot artifact #14603827434 (1,325,372 bytes; SHA-256 `294b022b56c2aabf834be30cb2aaa74c348cf8bef8a33da3a71204092f41f594`).

### Current-head screenshot inspection

Downloaded artifact #14603827434 and inspected all seven PNGs: 480×360, 720×540, 960×720, 1200×900, Amethyst skin, Burst skin and Settings. The 960×720 and 1200×900 layouts show no visible clipping or control overlap. The Settings overlay stays inside the editor bounds. The default/Burst skin uses the green accent; Amethyst uses purple. The compact 480×360 layout is dense and its labels are small, but no control collision or off-canvas element was visible. No UI source was changed in this PR; these are post-build captures and inspection, not interactive host testing.

A separate earlier push run #44677880833 on the parent PR #9 head f414bd4... completed successfully; it is not evidence for PR #10.

## 5. Release readiness matrix

| Gate | Status | Evidence / next requirement |
|---|---|---|
| Windows x64 VST3 build | PASS on PR #10 exact head | MSVC x64 VST3 target built in run #44678649998 |
| VST3 bundle structure / version / duplicates | PASS on PR #10 exact head | Exact-head package verifier passed |
| pluginval strictness 5 | PASS on PR #10 exact head | 1 passed / 0 failed; embedded VST3 validator exit 0 |
| Steinberg VST3 validator | PASS on PR #10 exact head | pluginval's VST3 validator exited 0 |
| Deterministic ZIP / checksums | PASS on PR #10 exact head; withheld | Installer-inclusive ZIP SHA-256 `5cabd20aaba54ed52c7cbe5bf59793629de3ffb54c91e7cfa6f6771435ae3132`; no public product artifact |
| Installer / update / backup / rollback | PASS in Windows CI with synthetic fixture | Dry-run, install, idempotence, update, rollback, first-install removal and fail-closed cases passed; owner-machine install and SkellHub integration remain unverified |
| DSP smoke | PASS: Linux CTest 1/1 and Windows CTest 1/1 | Real musical A/B and owner target-hardware tests still unverified |
| FL Studio scan/load / bypass / automation | UNVERIFIED | Owner Windows/FL Studio session required |
| Preset/state recall and old-project compatibility | No state/IDs changed; runtime UNVERIFIED | Open/save/reopen owner projects and recall factory/user presets |
| UI | PASS: current-head JUCE screenshots generated and inspected at four sizes plus skins/settings | No UI source changed; interaction/animation and FL Studio editor behavior remain unverified |
| Licensing / attribution / EULA | BLOCKED | JUCE, VST3, SkellCore and asset licensing/attribution review |
| Updater / rollback | Rollback helper implemented; SkellHub integration absent | Test helper on owner Windows machine, then review SkellyHub install/update/rollback integration |
| Storefront / email signup | Separate website automation | No deploy or storefront claim in this run |
| Release notes | Preview notice and README updated | Final public notes require release approval |
| Support/contact/vendor identity | BLOCKED | Owner must approve real vendor URL and support contact |
| Pricing / trial | AWAITING OWNER APPROVAL | No price, trial or payment action taken |

## 6. Remaining blockers and next release step

1. Finish PR #10 exact-head Windows run #44678649998. Inspect the PowerShell integration log and correct any real failures without weakening assertions.
2. Confirm Windows build, JUCE UI smoke, CTest, package verifier, pluginval 5, Steinberg validator and installer-inclusive deterministic ZIP all pass on the exact PR #10 head.
3. Download and independently inspect any allowed CI artifacts. The public repository must continue to withhold the product ZIP; do not publish a public preview as a substitute for private delivery.
4. Have the owner test FL Studio scan/load, bypass, transport, automation, presets, save/reopen and old-project compatibility.
5. Perform real musical A/B and target-machine CPU/latency checks. No audio A/B or owner host test was performed in this run.
6. Complete JUCE/VST3/SkellCore and asset licensing/attribution, EULA, vendor/support details, signing and SkellHub integration before commercial distribution.
7. Keep PR #10 and parent PR #9 draft. No merge, tag, public release, website deployment, DNS change, payment, or irreversible repository visibility change occurred.

The next Release & Launch run must select a different non-DeEsser plugin/project after fresh automation and branch-ownership checks. Do not select SkellGlitch again unless a critical regression appears. DeEsser remains parked.
