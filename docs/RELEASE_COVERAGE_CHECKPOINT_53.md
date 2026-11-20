# Skelly Release Coverage — Checkpoint 53

**Recorded:** 2026-11-20, 01:35 ET  
**Selected project:** Skell Delay — Windows x64 VST3  
**Repository:** https://github.com/skellyruno/skell-delay-vst  
**Product follow-up:** https://github.com/skellyruno/skell-delay-vst/pull/22  
**Base:** PR #19 exact head `146dc8e3c499da7159edbaa6528c488a69d5f5bc`  
**Latest source head:** `d38d0a9f6bbb1885e6b1da9347a2369d12249979`  
**Status:** Draft implementation committed; exact-head CI pending. No merge or release.

This checkpoint supplements the prior coverage records. It does not replace the protected Delay package, change the existing PR #19 branch, or alter DSP, VST3 class identity, parameter IDs, automation IDs, preset data or host-state format.

## 1. Selection and rotation

Checkpoint 51 selected StopDial; the intervening coverage ledger recorded Skell-Snap as checkpoint 52. This run selected Skell Delay, a different product from both.

Delay won because the latest Nightly Blueprint continues to identify it as the first owner-side FL Studio acceptance candidate, and it already has a real Windows x64 VST3 preview with a green exact-head pipeline. Unlike a speculative candidate, it has an independently inspectable package and a concrete owner-side acceptance path. Its release blockers are still material: legal approval, publisher contact, Quick4 UI acceptance, FL Studio/state/A-B/CPU acceptance, SkellHub review and signing.

The current issue #20 is a confirmed user-visible defect: six category filters are implemented but hidden, so VOCAL, RHYTHM, SPACE, TAPE, LO-FI and CREATIVE cannot be selected from the preset browser.

## 2. Cross-automation evidence checked

- **Preset Quality Audit:** newest scheduled attempt failed without a report. Latest usable completed Run 11 corrected Alchemist analysis alignment to 49 samples with a regression test; production factory bank 43 and experimental bank 55 were audited without promotion; Rack/EQ/Master checks were reported. No Preset-owned branch was edited.
- **Ecosystem Development:** latest completed result selected PitchNet, draft PR #1, commit `7472ae802a3a781cd3b5a3f66b12a1a78fd71a7b`, for ARA processed-audio archive-header validation and 12 assertions. Standalone C++17 assertions passed; full CI had not yet surfaced. No PitchNet or other Ecosystem branch was edited.
- **Websites Development:** latest completed V123 implemented Artist V108's post-release countdown accessibility transition; Creative 44/44 and Preset Showcase 12/12 passed. No public deployment or DNS change.
- **Nightly Blueprint:** latest completed review records zero verified commercial releases and zero verified revenue. Skell Delay remains the first owner-side FL Studio acceptance candidate; SkellyChoir is second.
- DeEsser remains parked. This is a substantive non-DeEsser implementation on Delay, distinct from the prior StopDial selection.

## 3. Protected baseline and package inspection

- Main baseline: `00b45315b79e194a3775b0f8a689d13ef93914a0`.
- PR #19 exact source head: `146dc8e3c499da7159edbaa6528c488a69d5f5bc`.
- Exact-head Windows workflow: [#44594311690](https://github.com/skellyruno/skell-delay-vst/actions/runs/44594311690), completed SUCCESS.
- Actions artifact #14565656993: 4,754,314 bytes; ZIP SHA-256 `90ced93cd6669418a2c2a55ec315b281981316b739cb9b1bd41439cf3614503d`.
- Independent inspection: ZIP CRC passed; 8/8 SHA256SUMS entries matched; strict moduleinfo JSON parsed; one flat `Skell-Delay.vst3` bundle; one `Contents/x86_64-win/Skell-Delay.vst3` module; AMD64 PE32+; two unique VST3 class IDs; no Standalone executable or duplicate bundle.
- Module SHA-256: `268a8017326277671a941a472b7078b0d179dacb57e8eeb1596c47e9e4f77737`.
- Manifest provenance: source commit `146dc8e3c499da7159edbaa6528c488a69d5f5bc`, CI checkout commit `3fe262c73189904c073462db4da0f1c39acc98fb`, workflow run `44594311690`.
- Manifest legal status is explicitly `not-approved-for-distribution`; release status is `preview-only`; publisher contact is incomplete and owner legal approval is not passed.
- Artifact #14565656993 was uploaded by a public repository workflow and remains publicly accessible. It is not a private preview store or a commercial download. No attempt was made to delete it or change repository visibility.

## 4. Implementation — draft PR #22

**PR:** https://github.com/skellyruno/skell-delay-vst/pull/22  
**Branch:** `fix/delay-accessible-preset-category-filter-v2-20261120`  
**Base:** PR #19 branch at `146dc8e3c499da7159edbaa6528c488a69d5f5bc`  
**Latest head:** `d38d0a9f6bbb1885e6b1da9347a2369d12249979`

Four files changed:

1. `Source/PresetBrowser.h`
   - Added a keyboard-focusable JUCE ComboBox for CATEGORY reset plus VOCAL, RHYTHM, SPACE, TAPE, LO-FI and CREATIVE.
   - Kept ALL/FAV/USER as direct quick filters and synchronized the combo with those controls.
   - Added accessible title/description and preserved search, preset audition, favourites, save/delete, randomise, undo/redo and serialized state.
2. `tests/dsp_tests.cpp`
   - Added JUCE regression assertions for selector visibility/bounds, keyboard focus, six category mappings, quick-filter reset and unchanged current preset.
3. `.github/workflows/release.yml`
   - Added a public-repository notice and restricted the installable Windows VST3 preview upload to `github.event.repository.private == true`.
   - Failure diagnostics remain separate.
4. `tests/test_release_workflow.py`
   - Added three workflow-contract tests for private-only product upload, public withholding notice and diagnostic artifact preservation.

No DSP code, parameter IDs, automation IDs, presets, VST3 class IDs, host-state format, CMake targets or approved artwork changed.

Initial PR #21 was superseded and closed without merge. Its branch remains preserved. Its first CI run #44690142565 was still in progress at the last check and used the older unconditional artifact-upload workflow. No artifact from that run is claimed or distributed; treat any resulting installable artifact as a public exposure and do not use it for release. PR #22 carries the private-only upload guard.

## 5. Validation

- Source-level contract checks passed: six category names, visible ComboBox, accessibility description, keyboard focus and top-row layout arithmetic (594 px used of 624 px available).
- PR #22 latest head `d38d0a9f6bbb1885e6b1da9347a2369d12249979`: workflow run [#44691128056](https://github.com/skellyruno/skell-delay-vst/actions/runs/44691128056) was pending at checkpoint time. No exact-head Windows compile, CTest, DSP/stress/realtime, pluginval, package, installer or public-upload-withholding pass is claimed yet.
- Local source clone could not be fetched because the container could not resolve github.com. The pinned JUCE 8.0.17-security ComboBox API declarations were checked upstream, but no local JUCE build or Quick4 screenshot was possible. Current UI capture, compact/large resize and keyboard popup interaction remain UNVERIFIED.
- FL Studio scan/load, bypass, automation, state/preset save-reopen, real musical A/B, target-PC CPU/latency, legal approval, reviewed EULA, vendor/support contact, signing and SkellHub updater acceptance remain separate gates.

## 6. Next step

Finish PR #22's exact-head Windows build, JUCE CTest, DSP/stress/realtime checks, pluginval strictness 10, package verification and PowerShell install/update/rollback. Confirm the public-repository notice appears and the installable product upload is skipped. Then obtain real Quick4 screenshots and interactions, followed by owner FL Studio scan/load, save/reopen, state/preset recall, musical A/B and CPU/latency acceptance.

Next Release & Launch selection must be a different non-DeEsser product after fresh automation/branch checks. No merge, tag, public release, website deployment, DNS change or payment action occurred.
