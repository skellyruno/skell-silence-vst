## Release & Launch checkpoint 54 — 2026-11-20 03:54 ET

### Selected project: SkellyChoir (skell-choir-vst)

Selected after checkpoint 53 Skell Delay. This is a different non-DeEsser plugin and a near-ready Windows VST3 candidate with a proven exact-head build, pluginval, package verifier and installer/update/rollback pipeline. The decisive release blocker was that the public repository uploaded the installable VST3 package as a public Actions artifact, so it was not a private owner-testing channel.

### Cross-automation and branch-ownership check

- Ecosystem Development's latest completed result selected PitchNet, draft PR #1, commit 7472ae802a3a781cd3b5a3f66b12a1a78fd71a7b; 12 standalone assertions passed, full CI was not surfaced. A newer Ecosystem attempt was failed/incomplete, and no Choir branch was reported active there.
- Preset Quality Audit's latest usable completed report is Run 11; the newest scheduled attempt was still in progress. It owns active Preset/Master/EQ work, so those projects were not selected.
- Websites Development's latest completed result is V125: Preset Showcase V38 13/13, Artist 100/100, Creative 48/48; no deployment or DNS change.
- Nightly Blueprint's latest completed report recorded zero verified commercial releases and zero verified revenue. It still identifies Delay as the first owner-side FL Studio acceptance candidate and SkellyChoir second.
- Master has current Deuce true-peak work on PR #33 with CI in progress; EQ has stacked release/installer/A-B PRs; Maw has a current owner-approval/package-fix chain. These were not selected to avoid branch overlap.
- DeEsser remains parked. No DeEsser work was performed.

### Protected baseline and exact-head evidence

Parent product PR #13: https://github.com/skellyruno/skell-choir-vst/pull/13
Source head: bfd0669d443ce899b33edef070f1e818686bebcb
Exact-head run: https://github.com/skellyruno/skell-choir-vst/actions/runs/44657440273

Confirmed parent results:
- Native DSP/room/state/UI-stub suite: 40/40.
- Windows x64 MSVC Release VST3 build and exact bundle staging: PASS.
- Strict moduleinfo and AMD64 PE32+ verification: PASS.
- pluginval v2.0.0-beta3 strictness 5: PASS.
- Windows package verifier: 28/28.
- Installer/update/rollback: 20 assertions.
- ZIP CRC and all 6/6 SHA256SUMS entries passed in the independent inspection comment.
- One flat VST3 bundle, two unique class IDs; module SHA-256 09a114142d0d3f80619157991a3aecf41921ffe2d40837857b260d269e8e9a4f.

Protected public Actions artifact #14593862630:
- 5,252,338 bytes.
- Archive SHA-256 5ecb469b63cf8ae0ad63a51ecd1b96f9ea0c7efe25cb19b32bab67bb462ecc30.
- It remains publicly accessible until its current 2026-12-04 expiry. This checkpoint did not delete it, change repository visibility, or claim it is private.

### New packaging implementation — draft PR #14

Product PR: https://github.com/skellyruno/skell-choir-vst/pull/14
Branch: release/choir-private-preview-artifact-guard-20261120
Base: PR #13 head bfd0669d443ce899b33edef070f1e818686bebcb
Commit: 520cfce8360befc875d69cde1814cc79a6530cc3
Four files changed in one commit.

- .github/workflows/build.yml: keeps Windows build, package verification, pluginval, provenance and installer self-tests; emits an explicit notice on public repositories and gates the installable VST3 artifact upload on github.repository_visibility == private.
- tests/test_release_package.py: adds a regression test that the only installable SkellyChoir-Windows-VST3 upload is private-repository-only.
- docs/RELEASE_CHECKLIST.md and docs/WINDOWS-VST3-INSTALL.md: distinguish public CI validation from private owner delivery and explain that old public artifacts are not retroactively privatized.

No DSP, UI source, VST3 class IDs, parameter/automation IDs, presets, host-state schema or installer swap/rollback behavior changed. PR #14 remains draft and stacked; no merge.

### Exact-head CI status at checkpoint

- Windows/native run #44707207579: Windows build job PASS — CMake configure, MSVC Release VST3 build, exact bundle staging, AMD64 PE32+ metadata verification, pluginval strictness 5, provenance, installer/update/rollback self-test and public withholding notice all passed. The product upload step was SKIPPED and the build run artifact list is empty. The separate native DSP/state/UI-stub plus Python package-test job remains in progress; overall run not yet green.
- Real JUCE/Xvfb UI run #44707207538: SUCCESS. The renderer produced all 35 current-head PNGs and the integrity/provenance verifier passed. Artifact #14616066318 is 7,055,108 bytes with archive SHA-256 e5844c878cbec0fe99bbb77dadf698fd7eb2c79d112486c1928b1d234831f8ff. Independent ZIP check passed; all 35 PNGs matched manifest hashes, had unique hashes and dimensions 33×765x534, 1×730x500 and 1×1300x900. A 35-image contact sheet and representative main, smallest, largest, first-run, room, listen, stems, neon-green and key/scale screenshots were visually inspected; no visible clipping or overlap found.
- No installable artifact from PR #14 was uploaded or is claimed. The separate non-installable UI screenshot artifact is QA evidence only.

### Remaining release gates

- Windows VST3: parent PASS; PR #14 exact head pending.
- Native tests: parent 40/40; PR #14 exact head pending.
- pluginval: parent strictness 5 PASS; PR #14 exact head pending.
- Package verifier / installer: parent 28/28 and 20 assertions PASS; PR #14 exact head pending.
- Private download path: NOT ESTABLISHED. Public repository artifacts are not private.
- FL Studio scan/load, save/reopen, automation, preset/state and old-project compatibility: UNVERIFIED.
- Real musical A/B and owner listening approval: UNVERIFIED.
- Target-machine CPU/latency/glitch checks: UNVERIFIED.
- Local Quick4 current-source screenshots: UNVERIFIED; repository pin is JUCE 8.0.16-security while the restored shared Quick4 bundle is JUCE 8.0.12.
- Licensing/attribution, owner-approved LICENSE/COPYING, vendor URL/support email and code signing: BLOCKED pending owner decisions/evidence.
- Storefront/email signup and pricing/trial: owner decision and website lane.

### Next step

Finish PR #14's exact-head Windows/native and real JUCE/Xvfb workflows. Confirm that public CI still completes all build and validation gates but skips the installable VST3 upload; inspect the actual 35-scene UI artifact if produced. Then obtain owner Windows/FL Studio, real audio A/B and target-PC CPU/latency acceptance, and establish a private delivery path. Next release selection must be a different non-DeEsser project unless a critical regression appears. No merge, tag, public release, deployment, DNS or payment action.
