# Skelly Release Coverage — Checkpoint 47

**Recorded:** 2026-11-19, 20:55 ET  
**Selected project:** SkellyChoir / OmniChoir FX  
**Repository:** https://github.com/skellyruno/skell-choir-vst

This is an append-only checkpoint supplement to [docs/RELEASE_COVERAGE.md](https://github.com/skellyruno/skell-silence-vst/blob/docs/release-coverage-maw-commercial-gate-20261119/docs/RELEASE_COVERAGE.md). Earlier project rows and checkpoint history remain unchanged.

## Selection and ownership evidence

SkellyChoir was selected after SkellyTune Mini because its current release-validation PR had a confirmed exact-head CI failure. PR #11's Windows job succeeded through MSVC Release VST3 build, bundle staging, PE32+ verification, pluginval strictness 5, installer/update/rollback, provenance and artifact upload. The separate native job passed 39 tests but failed the final `ui_syntax` check because the test-only JUCE stand-in lacked methods that the screenshot writer correctly calls from JUCE 8.0.16-security.

- Failing exact-head run: [#44515654996](https://github.com/skellyruno/skell-choir-vst/actions/runs/44515654996).
- Windows build job: passed.
- Native job: 39 passed, 1 failed (`ui_syntax` only).
- JUCE source of truth: [8.0.16-security FileOutputStream header](https://github.com/juce-framework/JUCE/blob/8.0.16-security/modules/juce_core/files/juce_FileOutputStream.h). It declares `flush()`, `getPosition()`, `getStatus()`, and `Result truncate()`.
- Existing PR #11 branch was not edited. The fix is isolated in a new stacked draft.

Cross-automation check:
- Ecosystem Development's latest completed result worked on Skell Maw; PR #15 exact-head Windows run #44627722227 passed its seven-plugin package/build/installer/pluginval gate. No Choir branch ownership was reported.
- Preset Quality Audit's latest scheduled run failed without a substantive result; no Choir branch ownership could be established from that run. GitHub PR/branch checks were used instead.
- Websites Development V119 completed Artist V106 (14/14 release scenarios), Creative V104 regression, and Preset Showcase V36 QA. No Choir source branch was touched.
- Nightly Blueprint's latest available review recommends Skell Delay for first owner-side FL Studio acceptance. Delay currently has an active legal-package/installer PR chain (#18/#19) and issue #20; those branches were left untouched.
- Afar has active PRs #11/#12 and depends on experimental SkellCore PR #43; those branches were left untouched.
- DeEsser remains parked.

## Implementation

**Draft PR #13:** https://github.com/skellyruno/skell-choir-vst/pull/13  
**Branch:** `fix/choir-juce-stub-file-output-stream-20261119`  
**Base:** PR #11 exact head `b534a7e8cb779242070d819f9b8406d1021a71d7`  
**Current head:** `bfd0669d443ce899b33edef070f1e818686bebcb`

Two files changed:
- `tests/juce_stub/JuceHeader.h`: added the minimal `juce::Result` stand-in and the actual JUCE 8 FileOutputStream signatures needed by `tools/screenshots.cpp`.
- `tests/juce_stub/README.md`: documents the API slice and pinned JUCE version.

Commits:
- `6118e31039d52d9c6114e3e76668a060fa2514de` — align the test stand-in API.
- `bfd0669d443ce899b33edef070f1e818686bebcb` — document the stand-in API.

No production DSP, UI, VST3 module, presets, parameter IDs, automation IDs, class IDs, host-state schema, installer logic, legal notices or FL Studio projects changed. No artifact or baseline was overwritten.

## Exact-head validation status

- New PR #13 workflow [#44657440273](https://github.com/skellyruno/skell-choir-vst/actions/runs/44657440273) remains in progress.
- Latest poll: Windows configure, MSVC Release build, exact bundle staging and PE32+ metadata verification passed; pluginval strictness 5 is running; installer/provenance/artifact upload remain pending.
- Native test suite remains in progress; package-verifier tests are pending.
- Local checkout was attempted but this execution container could not resolve github.com. No local build or local Quick4 screenshot is claimed.
- Previous baseline: PR #10 artifact [#14482735854](https://github.com/skellyruno/skell-choir-vst/actions/runs/44420964148/artifacts/14482735854), 5,252,321 bytes; archive SHA-256 `1c35c3bd48009f1b49ee08ae5d704564dadd545bfd6974ce8968a6ee30445ba5`; module SHA-256 `63cd3016c64c6069cbcec452ac066bc8f3a6425baa0ff68a0aa50d08f3044080`. Its prior exact-head Windows/native workflow passed; it is a historical preview baseline, not FL Studio acceptance or a commercial release.


## Real UI screenshot inspection

Downloaded the JUCE screenshot artifact [#14526230838](https://github.com/skellyruno/skell-choir-vst/actions/runs/44515655187/artifacts/14526230838) from the PR #11 screenshot workflow and independently inspected it.

- ZIP CRC: passed.
- PNGs: 35/35 decoded successfully.
- Dimensions: 33 at 765×534, one at 730×500, one at 1300×900.
- Duplicate image hashes: zero.
- Full-size inspection: first-run tour, smallest editor, selected long preset (“Midnight Cathedral”), plus a contact sheet including Easy, Pro, large, neon-green theme and key/scale states.
- No visible clipping, overlap, off-canvas controls or unreadable tour-card text was found in these captures.
- The current PR #13 changes only the syntax-test stand-in and its README, not the UI. Therefore no new UI screenshot was required for this change. Local Quick4/current-source capture remains UNVERIFIED because this execution container could not resolve github.com for a local checkout.

## Fresh protected-baseline verification

Re-downloaded PR #10 artifact [#14482735854](https://github.com/skellyruno/skell-choir-vst/actions/runs/44420964148/artifacts/14482735854) to `/mnt/data/SkellyChoir-PR10-Baseline-Windows-VST3.zip` and independently checked it during this checkpoint.

- Archive size: 5,252,321 bytes.
- Archive SHA-256: `1c35c3bd48009f1b49ee08ae5d704564dadd545bfd6974ce8968a6ee30445ba5`.
- ZIP CRC: passed.
- Exact flat package entries: installer, checksum manifest, build-info, one VST3 bundle (moduleinfo + x64 module), third-party notices and Windows install guide; no nested product ZIP or extra VST3.
- SHA256SUMS: 6/6 entries matched.
- Module: 10,593,280 bytes, AMD64 PE32+ (machine 0x8664, optional magic 0x20b), SHA-256 `63cd3016c64c6069cbcec452ac066bc8f3a6425baa0ff68a0aa50d08f3044080`.

## Coverage row — SkellyChoir

| Field | Current record |
|---|---|
| Last selected | 2026-11-19 (Checkpoint 47) |
| Verified output | PR #10 Windows VST3 baseline artifact #14482735854; PR #11 Windows build/package/pluginval/installer job passed, but overall native job failed 39/40 |
| Oldest blocker | Owner-side FL Studio scan/load, state/preset/automation recall, real musical A/B, target-PC CPU/latency, licensing/attribution and vendor/support approval |
| Immediate CI blocker | Test-only JUCE stub was behind the real JUCE 8 FileOutputStream API; fix submitted in PR #13 |
| Next test | Exact-head run #44657440273: require native 40/40 including `ui_syntax`, Windows MSVC VST3/package/pluginval/installer all green; then real editor screenshot/Quick4 and owner FL Studio acceptance |

## Rotation decision

SkellyChoir beat Skell Delay for this run because the exact-head Choir CI had a demonstrated failing required gate with a small root-cause correction that did not touch production plugin code. Delay remains a stronger owner-side FL Studio candidate, but its current legal/installer PR chain is already active and was not duplicated. The next release run should rotate away from Choir unless a new critical regression appears; continue to keep DeEsser parked.
