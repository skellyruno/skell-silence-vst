# Skelly Release Coverage — Checkpoint 52

**Recorded:** 2026-11-20, 01:18 ET  
**Selected project:** Skell-Snap — Windows x64 VST3  
**Repository:** https://github.com/skellyruno/skell-snap  
**Product PR:** https://github.com/skellyruno/skell-snap/pull/1  
**Status:** First exact-head Windows build and bundle-verifier run passed. Follow-up exact-head run #44686204462 is in progress with VST3-only build targeting and pluginval strictness 5. No installable artifact was uploaded because the repository is public.

This append-only checkpoint follows checkpoint 51. It does not replace the StopDial evidence or alter the protected source archive.

## 1. Selection and ownership

Skell-Snap was selected because it is a newly created, previously unworked plugin repository and the user's latest direct instruction in the recent project context was to use the new `skell-snap` repository and run its Windows VST3 workflow. At selection time:

- Repository main baseline: `edfd390b179b9cdad2668ea7df4f9fcfa86171e7`.
- Original source archive Git blob SHA: `8b0bad343fbfdcd004e9685eb18f0d6a5a7cf6eb`.
- Main had no open issues or pull requests.
- Only the `main` branch existed before this run.
- No other automation reported active work on Skell-Snap.
- Skell-Snap is a non-DeEsser plugin and a different project from checkpoint 51 StopDial.

The source archive, DSP implementation, UI, parameter IDs, state, presets and class identities were not changed. The archive blob and baseline commit remain on main.

## 2. Cross-automation check

Latest actual results rechecked during this run:

- **Preset Quality Audit:** the newest scheduled attempt at 05:59 UTC failed with only “There was a problem with your scheduled task.” It produced no new engineering result. The latest usable completed report remains Run 11, covering Alchemist alignment, production/experimental preset banks, preset recall, Rack, EQ and Master. No Skell-Snap branch was reported active.
- **Ecosystem Development:** latest completed result at 06:03 UTC selected PitchNet, PR #1, commit `7472ae802a3a781cd3b5a3f66b12a1a78fd71a7b`, adding ARA processed-audio archive-header validation and 12 regression assertions; CI was awaiting verification. The run did not report Skell-Snap work.
- **Websites Development:** latest completed V123 at 05:57 UTC implemented Artist V108's post-release countdown accessibility transition; Creative passed 44/44 and Preset Showcase 12/12, with packages verified and Quick4/JUCE 8.0.12 restored. No website deployment or DNS change occurred.
- **Nightly Blueprint:** latest completed November 19 review still recorded zero verified commercial releases and zero verified revenue. Skell Delay remained the first owner-side FL Studio acceptance candidate. No Nightly project was changed by this run.

Master was not selected because the Ecosystem and Preset lanes had current Master work in the previous completed results; this run instead used a newly created repository with no competing PR, issue or active branch. StopDial was not repeated. DeEsser remains parked.

## 3. Release-engineering changes

Product PR #1: https://github.com/skellyruno/skell-snap/pull/1  
Branch: `release/verify-windows-vst3-private-preview-20261120`  
Base: `main` at `edfd390b179b9cdad2668ea7df4f9fcfa86171e7`  
Latest head: `45c901e9957531ab89d2854c8cee81076327d125`  
Six commits; four files changed.

- `scripts/verify-vst3-bundle.ps1`: requires exactly one `Skell-Snap.vst3` bundle, strict parseable moduleinfo JSON, non-empty name/version, at least one class, unique class IDs, exactly one module under `Contents/x86_64-win`, and a valid AMD64 PE header. Writes `release-manifest.json` and `SHA256SUMS` bound to the workflow build commit.
- The verifier self-test accepts a valid AMD64 fixture and rejects duplicate class IDs, duplicate top-level bundles, and wrong PE architecture.
- `.github/workflows/windows-vst3.yml`: runs the verifier, uses PR-only concurrency cancellation, protects main/manual builds, builds the `SkellSnap_VST3` target only (not JUCE Standalone), and adds pluginval v2.0.0-beta3 strictness 5.
- Checkout/upload actions were upgraded to Node 24-compatible v6 versions.
- Installable VST3 artifact upload runs only for private repositories. Since Skell-Snap is public, the installable product artifact is withheld.
- README and BUILDING.md describe the release gates, public-artifact restriction and owner-side acceptance boundary.

No production DSP/UI source, VST3 class IDs, parameter IDs, presets, host state or automation IDs were modified.

## 4. Exact-head Windows CI

### First exact-head run — PASS

[Windows VST3 run #44685396412](https://github.com/skellyruno/skell-snap/actions/runs/44685396412) completed SUCCESS on prior draft head `7f4c9d9a12ed10c73f5c993c8717f8da86379be9`.

- PowerShell verifier self-test: PASS, including the positive fixture and rejection of duplicate CIDs, wrong PE architecture and duplicate bundles.
- Portable DSP executable: `ALL PASSED`; worst absolute pitch error was 0.35 cents over 84 cases.
- Windows compiler: Visual Studio 18 2026 / MSVC 19.51.36260.0.
- JUCE 8.0.12 configure and Windows x64 Release VST3 build: PASS.
- Actual bundle verifier: PASS; module name/version `Skell-Snap 0.1.0`, two classes, AMD64 PE.
- Module SHA-256: `51dac26725acd9008a8d74a65f4bb676bde1417fdfc24108a08c4bdf33eaebbd`.
- Public-repository withholding notice: emitted; product upload: SKIPPED; run artifacts: none.

The first run exposed two cleanup items: the default CMake build also compiled the Standalone target, and Visual Studio reported unused `CMAKE_BUILD_TYPE`. It also emitted a JUCE splash-screen-flag warning and a Node 20 deprecation warning from checkout@v4. The follow-up removes the unused CMake variable, builds only `SkellSnap_VST3`, and upgrades checkout/upload to v6.

### Follow-up exact-head run — IN PROGRESS

[Windows VST3 run #44686204462](https://github.com/skellyruno/skell-snap/actions/runs/44686204462) targets latest head `45c901e9957531ab89d2854c8cee81076327d125`.

At the latest job-step check:
- Source archive extraction: PASS.
- PowerShell release-verifier self-test: PASS.
- Portable DSP CMake configure: PASS.
- Portable DSP executable: PASS (step completed; full log not yet retrieved).
- JUCE VST3 configure: IN PROGRESS.
- VST3-only compile, bundle verification, pluginval strictness 5 and public-artifact withholding: PENDING.

No pass is inferred for steps that have not completed. The first run is a valid prior-head build result; it does not substitute for latest-head pluginval.

## 5. Artifact and release-readiness matrix

| Gate | Status | Evidence / next action |
|---|---|---|
| Source baseline | Protected | Main commit and source-archive Git blob SHA recorded above |
| Windows x64 VST3 compile | Prior head PASS; latest head pending | Finish run #44686204462 |
| Portable DSP tests | Prior head PASS; latest step PASS | Prior run worst error 0.35 cents / 84 cases; retrieve latest log |
| Verifier self-test | Prior and latest head PASS | Valid AMD64 fixture; duplicate CIDs/bundles and wrong PE rejected |
| Bundle structure / metadata / AMD64 PE | Prior head PASS; latest pending | Prior module name/version, 2 classes, AMD64 PE and module hash recorded above |
| VST3-only target | Implemented; latest build pending | Confirm log shows only `SkellSnap_VST3`, no Standalone target |
| pluginval strictness 5 | Added; pending | Run #44686204462 |
| Manifest / checksums | Prior head generated; not persisted | Public artifact withheld, so inspect exact-head logs after verifier |
| Private preview distribution | BLOCKED | Repository is public; no private delivery location configured |
| FL Studio scan/load and state recall | UNVERIFIED | Owner Windows/FL Studio session |
| Real vocal A/B, CPU, glitches and latency | UNVERIFIED | Same-source level-matched A/B and target-hardware measurements |
| Licensing / attribution / EULA | BLOCKED | No root LICENSE, LICENSE.txt, NOTICE or THIRD_PARTY_NOTICES.md found; confirm source/asset rights and notices |
| Vendor/support/signing | BLOCKED | Owner-approved identity, support contact and signing |
| Storefront / pricing / trial | Awaiting owner approval | Website lane and owner decision |

No UI source changed and no UI screenshot was generated. The available local container has CMake and Git but no PowerShell executable, Windows host, FL Studio or Quick4 runtime. Owner-side host and visual acceptance remain unverified.

## 6. Next step

1. Finish exact-head run #44686204462 and retrieve its job logs.
2. Fix any PowerShell, CMake, JUCE, DSP, bundle-verifier or pluginval failure at its root cause; keep PR #1 draft.
3. Confirm the VST3-only target did not build Standalone, the bundle manifest/checksum step passed, pluginval strictness 5 passed, and the public product artifact upload was skipped.
4. Establish an owner-controlled private distribution location before producing an installable preview.
5. Obtain owner-side Windows/FL Studio, state/automation and real-audio acceptance; resolve licensing/attribution, vendor/support and signing.
6. The next release-engineering selection must rotate to a different non-DeEsser plugin after fresh ownership checks; do not repeat Skell-Snap absent a critical regression.

No merge, tag, public release, repository-visibility change, website deployment, DNS change, payment action or irreversible setting change occurred.
