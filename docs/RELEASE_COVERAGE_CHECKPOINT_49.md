# Skelly Release Coverage — Checkpoint 49

**Recorded:** 2026-11-19, 22:48–22:54 ET  
**Selected project:** SkellyTune / HumHouseVocalTune  
**Repository:** https://github.com/skellyruno/skell-autotune-vst  
**Release PR:** https://github.com/skellyruno/skell-autotune-vst/pull/6  
**Status:** Windows x64 VST3 build and pluginval passed; offline DSP gate failed 48/52; current product ZIP withheld from the public repository.

This checkpoint supplements checkpoint 48. It updates only the rolling coverage row and records the exact SkellyTune release work. Earlier checkpoints, PR #5 and its verified baseline remain intact.

## Selection and evidence

SkellyTune / AutoTune was selected after SkellyChoir and Skeleton Graveyard to continue the non-DeEsser rotation. This is the `skell-autotune-vst` repository, not the separate `skelltune-mini` project.

It beat the other available candidates because it had a concrete exact-head CI failure and a distribution-safety defect in an otherwise buildable Windows VST3 candidate:

- PR #5 exact-head run [#44522718748](https://github.com/skellyruno/skell-autotune-vst/actions/runs/44522718748) failed during runner setup with `Unable to resolve action Tracktion/pluginval@v2, unable to find version v2`.
- Earlier run [#44521572041](https://github.com/skellyruno/skell-autotune-vst/actions/runs/44521572041) had produced a Windows VST3 preview artifact.
- The repository API reports the repository is public. The earlier preview artifact was therefore publicly downloadable, not private.
- Preset Audit currently owns Alchemist, Preset, Rack, EQ and Master. Ecosystem Development's next Foundation lane owns SkellForge, SkellNative and SkellCore. Delay, Key, Afar, Silence, Spacer and Flang have active release/CI branches. Those branches were not modified.
- No active agent branch in `skell-autotune-vst` was edited. PR #5's branch and head were preserved; this run used a new follow-on branch.

## Cross-automation and branch-ownership check

- **Preset Quality Audit:** Run 11 completed with Alchemist reference alignment, Preset factory-bank and recall-fixture work, Rack UI/build checks, and EQ snapshot/contour verification. Three Windows builds were still running in the latest report. No SkellyTune branch was reported active.
- **Ecosystem Development:** latest completed report worked on AdlibLab commercial release gates in PR #12 and identified Foundation (SkellForge, SkellNative, SkellCore) as the next workstream. No SkellyTune branch was reported active.
- **Websites Development:** V120 completed Creative V105; 44/44 Node tests and 22/22 Chromium checks passed, all three sites were regression-tested, and Quick4/JUCE 8.0.12 was restored. No plugin repository was changed.
- **Blueprint Nightly Review:** November 19 review still reports zero verified commercial releases and zero verified revenue; Skell Delay remains the first owner-side FL Studio acceptance candidate, SkellyChoir second.
- **DeEsser remains parked.** No website deployment, DNS, payments or commercial release action was taken.

## Source and workflow changes

**Product PR #6:** https://github.com/skellyruno/skell-autotune-vst/pull/6  
**Branch:** `fix/skellytune-release-ci-guard-20261119`  
**Base:** PR #5 branch `release/skellytune-vst3-package-integrity-20261119`  
**Base SHA:** `497b91a29e2afdebdf449c1d39b8749134dd0ce4`  
**Final head:** `d72c2de3d2767ebaa0ab0ab9db0bca33622054cd`

Three commits:
- `f1e4dc0d90b057d5f9821b40c9af0507c97ce920` — pin pluginval action, add offline DSP gate and workflow-contract tests.
- `d72c2de3d2767ebaa0ab0ab9db0bca33622054cd` — run Windows and DSP jobs in parallel, require both for publish, and withhold public preview artifacts.

Files changed:
- `.github/workflows/build.yml`
- `tests/test_release_workflow.py`

Implemented:
1. Pin `Tracktion/pluginval/validate` to the published `v2.0.0-beta3` tag, matching the pluginval binary version.
2. Add an Ubuntu Release-mode offline DSP job using `SKELLYTUNE_DSP_TESTS_ONLY=ON`.
3. Run Windows VST3 build/package and DSP CTest in parallel so a DSP failure does not hide build evidence.
4. Require both jobs before release attachment.
5. Add four dependency-free workflow contract tests.
6. Upload the product ZIP only for a private repository or an explicitly published release event. Public PR/push/manual preview uploads are withheld.
7. Protect main, master, production, release/*, production/release-targeting PRs, manual runs and release events from superseded-run cancellation.

No DSP source, UI, presets, APVTS IDs, automation IDs, VST3 manufacturer/plugin codes, class IDs, version or package identity changed. PR #5 remains open and draft.

## Exact-head CI — run #44671211915

[Windows VST3 release package — run #44671211915](https://github.com/skellyruno/skell-autotune-vst/actions/runs/44671211915)

**Windows x64 VST3 job: PASS**
- Python package verifier and four workflow-contract tests: passed.
- CMake/JUCE Windows configure: passed.
- Windows 2022 / MSVC x64 VST3-only build: passed.
- pluginval v2.0.0-beta3 strictness 5: 1 passed / 0 failed.
- Steinberg VST3 validator exit code: 0.
- Package script: passed strict moduleinfo JSON, AMD64 PE32+, exact three-class inventory and flat VST3-only ZIP verification.
- Generated ZIP size: 2,592,024 bytes.
- Generated ZIP SHA-256: `2ed3f0c9e19a446fd17c3e275d7bba96504c37ea6a78df03479b0898cdde165c`.
- Product upload step: **SKIPPED as intended** because this repository is public.
- Pluginval report artifact [#14600616172](https://github.com/skellyruno/skell-autotune-vst/actions/runs/44671211915/artifacts/14600616172): 758 bytes; artifact digest `f1a559ad181b3398a3a901d67c4c88bc9778407f0db0e4f991d690bcdd672b70`.

The generated product ZIP existed only on the ephemeral runner and was not uploaded. No current-head product download link is claimed.

**Offline DSP Release job: FAIL**
- CMake configure: passed.
- DSP executable build: passed.
- CTest: 48/52 passed, 4 failed:
  - `autotune_regression`: 110 Hz vibrato and legato-glide pitch-motion assertions fail.
  - `onset_trace_regression`: trace/latency contract fails; waveform block difference is 0, four onset events were detected, and no invalid trace values were counted. The test does not print the latency values causing the failure.
  - `cancellation_diagnostic_regression`: enabling detailed diagnostics breaks a bit-identical audio assertion.
  - `detector_difference_regression`: scalar/SIMD bit-exact squared-difference assertion fails.
- Do not lower thresholds, delete tests or claim the suite passed. These failures are current-source DSP/test blockers surfaced by this new release gate; no DSP source was changed in PR #6.

The overall workflow is failed because the DSP gate failed. The owner-approved release attachment job was correctly skipped.

## Protected baseline and public exposure

Historical artifact [#14528960226](https://github.com/skellyruno/skell-autotune-vst/actions/runs/44521572041/artifacts/14528960226) was downloaded and independently inspected.

- Product: SkellyTune 1.1.2, Windows x64 VST3.
- Source provenance commit: `92ec434d4b5e52386a5522b7fb25f48eb59374a7`, workflow run #44521572041.
- GitHub outer artifact SHA-256: `89b2912ae28767317438d392486d177a666230640374f5d84cab853169234`.
- Inner product ZIP SHA-256: `40fd658e25a9fea9596b0b91c08ac286848b59c7903e6e2888531faf55595e7c`.
- VST3 module: 5,966,848 bytes; AMD64 PE32+; module SHA-256 `d1177d1125e95f8894bc616f7a1ade8fb65204ef7029de7e77c166872b542e92`.
- Exactly three preserved VST3 classes:
  - Audio Module Class: `ABCDEF019182FAEB48756D68536B746E`
  - Component Controller Class: `ABCDEF011234ABCD48756D68536B746E`
  - Plugin Compatibility Class: `ABCDEF01C0DEF00D48756D68536B746E`
- ZIP CRC passed; all five SHA256SUMS entries matched; strict moduleinfo JSON passed; no nested ZIP or duplicate bundle.

The historical artifact remains publicly downloadable. The new guard prevents future public preview uploads but cannot make this historical artifact private. No artifact deletion or repository-visibility change was attempted.

Commercial identity in `release/identity.json` remains unapproved: owner approval false; vendor URL and support email blank; license pending; third-party notices missing; EULA missing; trademark pending.

## Release readiness matrix

| Gate | Status | Evidence / next action |
|---|---|---|
| Windows x64 VST3 build | PASS | MSVC build passed on run #44671211915 |
| VST3 metadata and bundle | PASS | Strict JSON, AMD64 PE32+, three classes, flat VST3-only package |
| pluginval | PASS | Strictness 5, 1/1; Steinberg validator exit 0 |
| Downloadable private preview | BLOCKED | Product ZIP intentionally withheld from public repository; no private artifact store connected |
| Offline DSP suite | FAIL | 48/52; four failures listed above |
| FL Studio host | UNVERIFIED | No owner-side FL Studio session available |
| Preset/state/automation recall | PARTIAL | pluginval state and automation passed; full factory/host recall unverified |
| Audio A/B / CPU / latency | UNVERIFIED | No real-singer A/B or target-machine measurement |
| Licensing / attribution / EULA | BLOCKED | Vendor, license, notices and EULA incomplete |
| Updater / rollback | NOT VERIFIED | No owner-tested updater/rollback acceptance |
| Storefront / email signup | NOT VERIFIED | Website automation remains separate |
| Release notes / support / pricing / trial | PENDING | Owner approval required |

## Next release step

1. Investigate the four DSP failures without weakening tests; reconcile the repository handoff's 28-test baseline note with the current CMake suite of 52 tests.
2. Correct project-owned MSVC C4458 shadow warnings in `Source/NoteTransition.h`; third-party Steinberg SDK C4996 warnings remain external.
3. Re-run the complete 52-test DSP suite and exact-head Windows/pluginval/package pipeline.
4. Perform owner-side FL Studio scan/load, preset/state/automation save/reopen, real audio A/B and target-hardware CPU/latency tests.
5. Keep PR #6 draft. Do not merge or publish.
6. Next Release & Launch run should select a different non-DeEsser project after fresh ownership checks; DeEsser remains parked.

No merge, tag, live release, website deployment, DNS change, payment action, repository-visibility change or artifact deletion occurred.
