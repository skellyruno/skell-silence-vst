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

## Exact-head validation status — PASS

Exact PR #13 head `bfd0669d443ce899b33edef070f1e818686bebcb`, workflow [#44657440273](https://github.com/skellyruno/skell-choir-vst/actions/runs/44657440273), completed SUCCESS.

- Native DSP/room/state/UI-stub suite: **40 passed, 0 failed**, including `ui_syntax`.
- Windows MSVC Release VST3 build, exact bundle staging and AMD64 PE32+ metadata verification: passed.
- pluginval v2.0.0-beta3 strictness 5: **1 passed, 0 failed**.
- Windows package-verifier regression suite: **28/28 passed**.
- PowerShell installer/update/rollback self-test: **20 assertions passed**.
- Provenance, checksums and artifact upload: passed.
- No local build or local Quick4 screenshot is claimed; the execution container could not resolve github.com for a checkout.

Current artifact [#14593862630](https://github.com/skellyruno/skell-choir-vst/actions/runs/44657440273/artifacts/14593862630): 5,252,338 bytes; archive SHA-256 / GitHub artifact digest `5ecb469b63cf8ae0ad63a51ecd1b96f9ea0c7efe25cb19b32bab67bb462ecc30`. Independently downloaded and inspected: ZIP CRC passed; 7 package entries; one flat VST3 bundle; no nested ZIP or extra VST3; all 6/6 SHA256SUMS entries matched; strict moduleinfo JSON; two preserved unique class IDs; AMD64 PE32+ module (10,593,280 bytes), SHA-256 `09a114142d0d3f80619157991a3aecf41921ffe2d40837857b260d269e8e9a4f`. Build-info remains `preview-only` with legal/contact blockers; repository is public, so the Actions artifact is not a private download channel.

Baseline comparison against PR #10 artifact #14482735854: PE sections `.text`, `.data`, `.pdata`, `.rsrc` and `.reloc` are byte-identical; only `.rdata` differs (51 bytes), consistent with embedded build metadata. No DSP or code section changed. The baseline archive remains preserved: 5,252,321 bytes; SHA-256 `1c35c3bd48009f1b49ee08ae5d704564dadd545bfd6974ce8968a6ee30445ba5`; baseline module SHA-256 `63cd3016c64c6069cbcec452ac066bc8f3a6425baa0ff68a0aa50d08f3044080`.


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
| Verified output | PR #13 exact-head workflow #44657440273: 40/40 native tests, 28/28 package tests, Windows VST3 build, pluginval 1/1, installer 20 assertions; artifact #14593862630 independently inspected. PR #10 baseline retained. |
| Oldest blocker | Owner-side FL Studio scan/load, state/preset/automation recall, real musical A/B, target-PC CPU/latency, licensing/attribution and vendor/support approval |
| Immediate CI blocker | Resolved by PR #13: test-only JUCE stub now matches JUCE 8 FileOutputStream API; exact-head CI passed. |
| Next test | Owner-side FL Studio scan/load, audio/MIDI routing, state/preset/automation save-reopen, real musical A/B and target-PC CPU/latency; current-source Quick4 capture if local JUCE becomes available. |

## Rotation decision

SkellyChoir beat Skell Delay for this run because the exact-head Choir CI had a demonstrated failing required gate with a small root-cause correction that did not touch production plugin code. Delay remains a stronger owner-side FL Studio candidate, but its current legal/installer PR chain is already active and was not duplicated. The next release run should rotate away from Choir unless a new critical regression appears; continue to keep DeEsser parked.
