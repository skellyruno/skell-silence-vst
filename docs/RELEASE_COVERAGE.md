Updated: 2026-11-18 16:57 EST (Release & Launch selected Skell Flang after Spacer. Draft PR #18 repairs a truncated SHA-256 validation regex and removes accidentally embedded duplicate portable-job text from the provenance PowerShell block; concurrency cancellation is now PR-only so push-to-main and workflow_dispatch/manual runs are protected. PR #18 head `78e62cdd1d14c3521dde389f9fb18444e0ba48ac`; exact-head run #44406371683: portable DSP and ASan/UBSan passed, Windows CMake configure in progress, no new artifact yet. Preserved Windows artifact #14439047016 independently inspected (archive SHA-256 `f07c045a877a0554f69bf367f524b34c370fa19ae1ad6e9cd09feab9f59acbee`); UI artifact #14439790352 (81 PNGs) inspected at 540/720/1080 widths with no visible clipping. VST3 metadata URL and E-Mail remain empty; FL Studio/audio/state/hardware/licensing/contact gates remain open.)
Updated: 2026-11-18 15:50 EST (Release & Launch selected Skell Spacer and opened draft PR #8 for strict VST3 moduleinfo JSON normalization. Local normalizer tests 7/7; actual PR #7 artifact repaired and strict-parsed in an isolated copy; portable exact-head CI #44396064041 and push run #44396055079 passed, Windows #44396063940 pending at ledger update. SkellFan PR #12 exact-head Windows run #44384242825 is now green; installer-enabled artifact #14466532014 independently passed ZIP CRC, strict moduleinfo parsing, AMD64 PE32+ identity and all five checksums.)
Updated: 2026-11-18 14:51 EST (Independently downloaded Skell Spacer PR #7 artifact #14226276938. ZIP CRC and all three embedded hashes pass, bundle is flat and PE32+ AMD64, but strict JSON parsing fails on a trailing comma in moduleinfo.json. This is a concrete next release blocker; no Spacer source was modified in this run.)
Updated: 2026-11-18 14:50 EST (SkellFan PR #12 run #44376137274 failed only in installer integration: the tampered-binary test expected a checksum-manifest error, but the installer correctly rejected the binary earlier against build provenance. Corrected the assertion on the same draft branch in commit `7f82b9bc9a45ea9182c87be8b32df88f30d15654`; exact-head Windows run #44384242825 is in progress. No installer-enabled artifact is available yet.)
Updated: 2026-11-18 14:07 EST (SkellFan parent preview #14264828558 independently downloaded in this run; ZIP SHA-256 matches GitHub digest, ZIP CRC and all three embedded hashes pass; 8-scene Quick4 baseline inspected. Draft PR #12 exact-head Windows run #44376137274 is in progress at MSVC build; no new installer-enabled artifact or host acceptance claimed.)
Updated: 2026-11-18 (AdlibLab PR #11 exact-head DSP/ASan/UBSan 18/18, Windows VST3 build/pluginval/installer integration 14/14, and JUCE UI capture 10/10 passed; new private-preview artifact #14456259709 independently verified; FL Studio/audio/state/hardware acceptance remains unverified.)
Updated: 2026-11-18 12:54 EST (Release & Launch selected Skell AdlibLab after the previous Skell Delay run; draft PR #11 adds a checksum-verified per-user Windows preview installer and rollback. Parent Windows VST3/pluginval run #44287143589 and artifact #14419617362 were independently verified; exact-head PR #11 Actions had not appeared yet. No new installer artifact or host acceptance claimed.)
Updated: 2026-11-18 12:04 EST (Skell Delay exact-head run #44353755432 passed Windows CMake configure; MSVC Release VST3 build is in progress. Python release-package tests passed on this head. No new artifact or installer/host acceptance claimed.)
Updated: 2026-11-18 11:48 EST (Release & Launch selected Skell Delay; draft PR #13 adds a checksum-verified per-user Windows VST3 installer/update/backup/rollback. Exact-head run #44353755432 is in progress; no new artifact or host acceptance claimed.)
Updated: 2026-11-18 10:43 EST (Release & Launch selected SkellCast; draft PR #7 adds a checksum-verified per-user Windows VST3 installer, update, backup and rollback. Exact-head CI has not yet appeared; no new artifact or host acceptance is claimed.)
Updated: 2026-11-18 10:38 EST (Separator exact-head Windows run #44336350915 passed; artifact #14440794981 downloaded and verified. Exact-head real JUCE UI run #44336351222 passed; artifact #14441882893 downloaded, CRC-tested and all eight PNGs compared pixel-identical to baseline.)
Updated: 2026-11-18 10:28 EST (Release & Launch selected Skell Separator; draft PR #5 adds private Windows install/update/rollback; exact-head Windows CMake configure and package-verifier step passed, Release VST3 build still running; neural/ASan suite #44335144390 passed; no new artifact or host acceptance claimed.)
Updated: 2026-11-18 (Release run: Skell Flang PR #16 exact-head Windows run #44328432222 succeeded; 1,344 direct processBlock calls passed with host BPM playhead; pluginval 1 passed/0 failed; VST3 and 81 real JUCE UI captures independently downloaded and inspected. StopDial PR #4 artifact #14433953450 remains verified.)
Updated: 2026-11-18 (Release run: Skell Flang PR #16 host-playhead allocation gate extended; portable DSP and ASan/UBSan pass; exact-head Windows run #44328432222 still running at update; previous Windows preview baseline #14407071686 independently inspected. StopDial PR #4 exact-head Windows package #14433953450 verified.)
Updated: 2026-11-18 (Skell Necromancer PR #3/#4 exact-head Windows VST3 and real UI artifacts inspected; Skell Key PR #12 preview artifact independently reverified; Skell Key remains the provisional first distribution candidate; no product is commercially approved)
Updated: 2026-11-18 (Skell EQ strict metadata parser hardening; Skell Delay PR #12 full Windows/DSP/pluginval-10 artifact verified; Skell Key PR #12 installer safety and pluginval-5 artifact verified; baselines independently inspected; EQ latest build still pending)
Updated: 2026-11-18 05:39 EST (AdlibLab VST3 program-name defect fixed after strict pluginval failure; exact-head Linux gates pass; Windows revalidation pending)
Updated: 2026-11-18 05:37 EST (AdlibLab verifier/preview pipeline extended; local 10/10 tests and Linux CI pass; 100 real JUCE scenes inspected; Windows package gate still running)
Updated: 2026-11-18 05:28 EST (AdlibLab release verifier integrated into Windows VST3 preview workflow; local 10/10 verifier tests and Linux CI passed; Windows package gates pending)
Updated: 2026-11-18 05:10 EST (Afar real JUCE editor screenshots passed and inspected; first preview artifact superseded for stale dependency notice; corrected-head Windows/real-core workflows running)
Updated: 2026-11-18 00:54 EST (SkellyTune Mini exact-head Windows VST3 preview verified; pluginval false-negative fixed)
Updated: 2026-11-17 04:12 EST (Release & Launch checkpoint 21; Modular FX Suite Windows VST3-only package PR #4; exact-head CI in progress)
Owner: skellyruno
Purpose: Windows-first VST3 / EXE / installer release readiness. This is a coverage register, not a declaration that every listed project is releasable.

## Evidence rules
- "Reported" means the prior Release & Launch checkpoint recorded the selection/output; it was not re-run in this execution.
- "Not logged" means no release-engineering selection date was present in the last available coverage report. It does not mean the project was inactive.
- "Unverified" means no current Windows package, host acceptance, or other named gate was independently established here.
- Do not promote a project to release-ready from CI alone. Require packaged binary inspection, pluginval, host/FL Studio acceptance, sound/state checks, licensing and delivery readiness.
- DeEsser is parked for the required six-run non-DeEsser rotation, absent a critical security/regression emergency.

## Current execution
| Project | Last release selection | Verified output / oldest blocker | Next release test |
|---|---|---|---|
| SkellFan — skell-fan-vst | 2026-11-18 (selected in prior run; installer integration fix now exact-head green) | Draft PR #12 head `7f82b9bc9a45ea9182c87be8b32df88f30d15654`; Windows run #44384242825 passed all 18 steps: source consistency, fail-closed package verifier, CMake/Release x64 build, DSP/portable tests, staged metadata and AMD64 PE32+ checks, pluginval strictness 5, per-user installer WhatIf/fresh/idempotent/update/backup/rollback/tamper tests and artifact upload. Artifact #14466532014: 4,915,169 bytes, SHA-256 `d931b394dc5692eccf73285224a830b4cc98ece89f2b9cd5c12ebf6b7cf357ca`; independently downloaded, ZIP CRC passed, one SkellFan 1.9.0 VST3 bundle, two unique CIDs, strict JSON, AMD64 PE32+ module 9,491,456 bytes, all five SHA256SUMS entries matched; installer and guide embedded. Oldest blockers: FL Studio, real music A/B, state/preset/automation/old-project recall, target CPU/latency, vendor/support contacts, licensing and signing. | Owner FL Studio scan/load, music A/B, old-project/state recall, target-hardware CPU/latency, licensing/contact and signed installer approval. |
| Skell Silence — skell-silence-vst | 2026-11-16 (previous release selection; exact-head rerun and UI recheck passed) | PR #14 head `f9fd082eaba48b1691ad3d8690218d71f2c543a2`; Windows run #43927197784 passed DSP, Windows VST3 build, JUCE host regression, SkellCore actual editor capture 82/82, bundle staging and pluginval strictness 5. Artifact #14258200082: one `Skell Silence.vst3`, v2.8.0, AMD64 PE32+, module 3,913,216 bytes; module SHA-256 `307d36410937415855f68884cc27eea6034c7a153c4f86f049aff268bf6d0666`; archive digest `9103143dee94731059b6179d63d815730ae5b628a57b134affee9be0882207bc`. UI artifact #14256363697: 82 manifest scenes + 3 guided-tour screenshots + contact sheet; digest `19195ef4618e8a9e60754e0b450a7a714bd16fb199a40066171eeef43b0f235a`. I inspected the contact sheet, an all-scenes montage and representative full-size minimum/menu/tour/standard views; contact sheet is no longer black and no visible clipping/overlap was found. | FL Studio save/reopen and audio A/B; independent Quick4 capture; vendor URL/support-email and licensing approval. |
| Skell Key — skell-key-vst | 2026-11-17 (last Release selection; Ecosystem Development follow-up verified 2026-11-18) | Draft PR #12 head `89932b22ffc1caffc5a53be5c9061c9c87efb3da`; Windows run #44261809007 passed Release VST3 build, tuning-sync tests, strict moduleinfo, one-level staging/provenance, private-preview install/update/rollback assertions, pluginval 1.0.4 strictness 5 and artifact uploads. Artifact #14408776507: 2,168,633 bytes; archive SHA-256 `d26911874f6891ab1744b9a3c5709104e46705fab8359d1710e4ad05de532513`; ZIP CRC passed, 13 entries, one flat Skell Key.vst3 bundle, Skell Key 0.1.0 / Skell Audio, two unique CIDs, one AMD64 PE32+ module 4,918,784 bytes, module SHA-256 `90cee58ddf11d5ff61f8d49b3a66007ce1fd5d143ce69a5acecf17a3814f792c`; all 11 package SHA256SUMS and all 3 tool SHA256SUMS entries independently matched. Installer, install guide, release notes, preview-only notice and third-party notices are embedded. Still PREVIEW_ONLY: FL Studio scan/load, Key↔Mini sync, musical A/B, state/project recall, target CPU/latency, Quick4 UI, licensing, approved vendor/support details and signed installer. | Owner-host and two-plugin sync tests; musical A/B; state/automation/old-project recall; Quick4; license/contact and install/update/rollback approval. |
| Skell Delay — skell-delay-vst | 2026-11-18 (selected in previous run; installer update-fixture regression follow-up now owned by another active branch editor) | Draft PR #13 remains preserved; branch `release/delay-private-preview-installer-rollback-20261118`; latest head `df9c43ef93e9c3ca62a6da3c277050b52b20b402`, stacked on PR #12 head `dba3425f9ce11932fb8dc76c192043d33258ed88`. Parent Windows run #44299900149 and artifact #14426686086 remain verified: one Skell-Delay 1.0.0 / Skelly Audio AMD64 PE32+ VST3, 8,945,152-byte module, SHA-256 `28379cd7d28afde63c6841a31345a536b3b39077edc515b62153195475be8814`, two unique CIDs and parent checksums matched. Exact-head run #44353755432 failed only at the new update/rollback integration assertion after the fixture changed build-info without changing the VST3 bundle tree. Follow-up head `df9c43ef...` changes the fixture's moduleinfo version to 1.0.1 and updates the bundle manifest/checksums so it represents a real bundle update; Windows run #44364117623 failed in the PowerShell installer test at Test-SkellDelayPreviewInstaller.ps1 line 154 with a ParserError: unexpected token 'Updated'. The follow-up branch is owned by another active editor and was not modified in this run. This branch was left untouched because it had already been advanced by another editor. | Complete #44364117623, verify Windows build/CTest/pluginval strictness 10/PowerShell update-backup-rollback tests and inspect the new artifact; then owner FL Studio scan/load, state/preset/automation recall, audio A/B, target CPU/latency, licensing/contact and signing. |
| Skell Pad / ScratchPad — skell-scratch-vst | 2026-11-17 (selected; strict staged metadata and pluginval release gate completed in draft PR #3) | Exact-head PR #3 commit `c0a02fb382d7fe0757c32ff5b104bb28ab3fb29c`; Windows run #44235737076 passed Release VST3 compile, DSP/real-JUCE processor-editor CTests, UI geometry, one-bundle AMD64 PE32+ staging, pluginval v2.0.0-beta3 strictness 5, provenance/checksums and artifact upload. Artifact #14397173525: 2,090,655 bytes, SHA-256 `69698ec9caeab13789a78508834e913a6bfe8e7ade2f305c37363bd48653118a`; ZIP CRC passed, exactly one ScratchPad.vst3, one 3,800,576-byte AMD64 PE32+ module, binary SHA-256 `a26ae22bb477c391cdb9d3290398af1f8f090792162745585e42f472ce6fb17c`; all 11 SHA256SUMS entries matched. Moduleinfo normalized from original SHA `c063128486a643b39d72e44d1b959fc545e5e6b29d29d096aa15556b215fcfcc` to strict JSON SHA `c4d5bfb505dd543d005ac9ed9a6c44054a79d50e233506fdb5d609eaf2fe7a9a`; product ScratchPad 1.19.0 / Skell Audio and both protected CIDs verified. Six real JUCE editor PNGs inspected at 441x263, 882x526, 1323x789 plus guided-tour/active-meter scenes; no visible clipping/overlap found. | FL Studio scan/load/save/reopen, real audio A/B, preset/state recall, target-hardware CPU/latency, vendor URL/support email, licensing/attribution, signed install/update/rollback. |
| BPM Delay Calculator — -bpmdelay-calculator-vst | 2026-11-17 (selected; release packaging PR #1 plus focused follow-up PR #2) | Main baseline `6366ff31c5ab8e76ec4a231100ba97a07096d3f9` (2026-10-16); no pre-existing Windows VST3 binary/installer in repository inventory. Draft PR #1 `release/windows-vst3-package-20261117` adds VST3-only packaging, strict pluginval 1.0.4 strictness 5, PE32+/Mach-O architecture validation, provenance and checksums. Draft PR #2 branch `release/delaycalc-default-program-name-20261118`, head `3cc6e1182c88c1cd1f46afc3bd32f884103b75ea`, stacked on PR #1: fixes the empty `getProgramName(0)` to `Default`; adds staged-only JUCE trailing-comma normalization, strict JSON/duplicate-key/non-finite checks, CMake-derived product/vendor/version and both class IDs, pluginval on normalized staging, manifest identity evidence and 8 normalizer regression tests. The ZIP now embeds PREVIEW_ONLY.txt plus explicit release blockers, and the manifest checksums the notice. Local normalizer suite 8/8 passed; the expanded package-marker assertion is pending CI. No Actions runs/check-runs/combined status contexts are visible for the repo's PR heads; no new VST3 artifact or Windows build is claimed. Quick4 was restored, but its JUCE 8.0.12 does not match this repo's JUCE 8.0.15 pin and its renderer does not support this plugin. | Obtain exact-head Windows Actions execution; package tests, CMake/Release VST3, pluginval 5, artifact/hash inspection; then FL Studio scan/load, audio passthrough, UI interaction, save/reopen, target-hardware CPU/latency, license/contact and installer/rollback. |
| Skell Preset — skell-preset-vst | 2026-11-16 (Preset Audit latest run; Windows VST3 and host fixture passed, Alchemist trial not promoted) | Current draft build is v0.7.0 from merge commit `78c762db`; Windows CTest 41/41, portable CTest 32/32, startup/state restoration and native rack host fixture passed. The 50-preset bank audit found 0 duplicate names, invalid macro ranges or invalid cover indices. Alchemist Factory 49 vs 48: spectral error improved 0.486 to 0.454 dB, but dynamic-envelope error worsened 3.523 to 3.595 dB, so Factory 49 remains experimental and Factory 48 stays champion. Four 15-second 24-bit FLAC previews and measurement JSON were verified; headless Chromium playback timed out. FL Studio remains unrun. | Keep Factory 49 unpromoted; continue independent compressor-blend A/B; inspect the compiled UI/Quick4; FL Studio preset/state recall and target-hardware CPU/latency; preserve factory 43/46/48. |
| Skell Master — skell-master-vst | 2026-11-17 (Preset Audit advanced Deuce; release branches actively owned by Preset Audit) | PR #14 head `f7b04a1c9d753392f932c3009f0ea145c2957bbe`, run #44048251784, passed; PR #15 head `b557a54a75990a2d30852b7b8e615fa7fd68b056`, run #44080300222, passed. Changes move Deuce five-band color before the internal limiter, preserve post-downsample +2 dB/5 kHz presence, gate optional color while bypassed and retain warm crossover history. Preset Audit reports CTest 9/9, UI geometry 5/5 and hosted synthetic VST3 audio at three sample rates. PRs #14/#15 and related true-peak branches remain active; do not edit them. | Keep branch ownership; complete full-band true-peak safety, user-listened A/B, target-hardware CPU/latency, FL Studio save/reopen and package/licensing/contact checks. |
| Modular FX Suite — skell-rack-vst | 2026-11-17 (selected; VST3-only release packaging and CI) | Draft PR #4, branch `release/windows-vst3-only-juce812-20261117`, current head `829de4513cedabcb9f841eb6a402d0d1e9b7e5f2`, based on main `273eba05567e6cf0f7ba02d9e819b5981d637d82`. No open PRs/issues existed before selection. Main CMake used JUCE 8.0.0 and `FORMATS VST3 AU Standalone`; the package workflow was manual-only. Preserved baseline Windows run #38243301476 / artifact #11743164423, source commit `f559550b3c5e0fdff641e00b74ef0ef2a72c9451`; GitHub digest and downloaded ZIP SHA-256 both `8d9010de7d062c941db44164b94cee6de8a6b8b5f975dd1fbf3aec865499c753`. Baseline binary SHA-256 `fa8a8397276c53bad85d5f9993301122453adf4935cad4e8c47173a060f21eed`; original moduleinfo SHA-256 `f41c17bbffc177e4fb96fe778f682b9288744b6a08659dca3a5389a44ac37d3e`. The real baseline had JUCE trailing commas and passed the new local staged-copy repackage, strict JSON parse and ZIP CRC; original bundle bytes were not modified. PR #4 pins JUCE 8.0.12, makes the CMake target VST3-only, adds PR/main/manual Windows validation, a fail-closed one-bundle/AMD64 PE32+ packager, 10 regression tests, pluginval strictness 5, provenance, SHA256 sidecars and 30-day preview retention. Local packager tests 10/10 passed; real baseline repackage passed. Quick4 kit restored with JUCE 8.0.12. No local full plugin build or screenshot claimed because the container could not resolve `github.com`. Exact-head Windows run #44053093571 and real-editor Guided Tour run #44053093565 are in progress; no new artifact or screenshots claimed yet. The superseded PR build run #44052919418 was cancelled by PR-only concurrency; older Guided Tour run #44052919426 remains in progress (no direct cancellation action available). No CTest/DSP suite or root LICENSE/COPYING/NOTICE exists; VST3 vendor URL and support email are blank. | Finish exact-head Windows build, package tests, pluginval 5 and artifact/hash inspection; inspect the four current-head UI screenshots; then add DSP CTest/NaN/denormal/clipping/bypass/CPU coverage, FL Studio and musical A/B; obtain license/contact approval and verify installer/SkellyHub rollback. |
| Skell EQ — skell-eq-vst | 2026-11-18 (selected; strict moduleinfo parser hardening in existing PR #11) | Draft PR #11 head `24df947b676bbbb98356c755c2b09c5f1d8b2b98`, branch `release/eq-vst3-ab-state-integration-20261117`; commits `8818bbbc38110bcad0bf2cd81197bd7fe20aed56`, `7b098850e2e186e34bc5bea8d9989c679e0e79df`, `24df947b676bbbb98356c755c2b09c5f1d8b2b98`. Preserved parent artifact #14344965701 independently inspected: 2,089,377 bytes, archive SHA-256 `cf2593f667a446b16f346b27e57e8a98825fe71f257b5d2dec877b26829618e2`; four entries, one flat v2.7.0 VST3 bundle, two CIDs, AMD64 PE32+ module 4,513,280 bytes, module SHA-256 `fc55a69d71e9a9075547887a49eb31ed4103e25114f7f75f7d5f844bb685ff27`, moduleinfo SHA-256 `02e6db2008db4a5cd2344df17d8053cb41cd7f5c98b2f290899842e8e1b5eb87`; all three embedded hashes matched. Parser now rejects duplicate object keys, NaN/±Infinity and float exponent overflow before writing metadata; tests assert invalid source remains unchanged. First attempt #44308347400 failed at an incorrectly escaped test fixture; corrected intermediate head passed source and parser tests; superseded run #44308509617 was cancelled after a newer PR-only head. Latest exact-head run #44309210216 on `24df947b676bbbb98356c755c2b09c5f1d8b2b98` passed source checks and expanded parser self-test; CMake configure was still running at last observation, so no new compile/CTest/pluginval/artifact is claimed. | Finish exact-head Windows configure/build, all 4 CTests incl. A/B state round-trip, pluginval strictness 5, staged bundle/provenance/hash inspection. Then FL Studio scan/load, automation/bypass/save/reopen, old-project recall, musical A/B, target CPU/latency, Quick4 UI, license/contact and installer/SkellHub rollback. PREVIEW_ONLY. |
| Skell Spacer — skell-spacer-vst | 2026-11-18 (selected after SkellFan; strict metadata packaging fix in draft PR #8) | PR #7 head `3e85ce55e58575e526c73caa603434789d0500b7`; run #43865954713 passed parameter IDs, DSP/stress/zero-allocation, CPU matrix, offline render, Windows VST3 build, 18-scene JUCE editor audit and pluginval 5, but artifact #14226276938 failed strict JSON parsing because JUCE-generated `moduleinfo.json` has trailing commas. Draft PR #8 head `0fa0d6bec76a59a1f2c8161dc96aa45ab7efcdc8` adds a string-aware normalizer, strict identity/class/CID validation and seven regression tests. Local suite 7/7 passed; the exact PR #7 artifact was normalized and strict-parsed locally without touching its binary. PR #8 portable CI #44396064041 and duplicate push run #44396055079 passed; Windows run #44396063940 was still running at this ledger update. Parent artifact SHA-256 `b3350788419bc8d368577b356fff06d1002f7789686908e7d1ef566b02628e07`; one flat bundle, AMD64 PE32+, all three original checksums matched. UI artifact #14225352982 (18 actual screenshots) was inspected at min/default/max, four skins and 125/150% scaling; no visible clipping/overlap found. Oldest blockers: FL Studio sidechain/state reopen, local Quick4 renderer, user audio A/B, target CPU/latency, licensing, vendor/support details, installer/updater rollback and storefront. | Complete exact-head Windows run #44396063940; download and independently inspect its normalized artifact, verify strict JSON/checksums and pluginval 5; then FL Studio sidechain/state reopen, Quick4 wiring, real audio A/B, target hardware, licensing/contact and installer/update/rollback. |
| Skell Choir — skell-choir-vst | 2026-11-17 (selected; Windows CMake checkout regression repaired and package independently verified) | Parent draft PR #8 head `d8db48ba400fbbfc8a4ac828ad41aaba6f71d454` had failed run #44163286082 at CMake because the PR head object was missing from depth-1 checkout. Follow-up PR #9 commit `3e6634fc5c8655bc620a0907c936679a138bd4bc` added `fetch-depth: 0` to the Windows checkout. Exact-head run #44173099588: Windows build and native-tests jobs both passed; native suite includes all 14 package-verifier tests. Artifact #14369236040 (`SkellyChoir-Windows-VST3`, 5,241,142 bytes) downloaded and independently inspected: ZIP CRC passed; exactly four files (direct VST3 bundle, strict moduleinfo.json, build-info.json, SHA256SUMS.txt); one module at `SkellyChoir.vst3/Contents/x86_64-win/SkellyChoir.vst3`, 10,593,280 bytes, AMD64 PE32+; two unique VST3 class IDs; all three sidecar hashes match. Archive SHA-256 `9eea66b10fdf06a053d0dca2b9638c7834ca108001b2407c83d0b1ca5fc62495`; binary SHA-256 `46d34556e31f3ff3231ec48ed7eacbbe3403125225db93cecb271cb34eead8f4`; moduleinfo SHA-256 `71ead2f33cd16064bce36ebe992e68ef3893c1b910f05319634f96186768a385`. Manifest source commit matches PR #9 head; pluginval strictness 5 passed. Version 0.9.0 remains PREVIEW_ONLY because FL Studio, real musical A/B, target-hardware CPU/latency, third-party attribution, owner-approved LICENSE/COPYING, HTTPS vendor URL and support email remain blockers. Original baseline artifact #14279527660 remains preserved. | Keep PRs #8/#9 draft; Quick4 current-source screenshots and interactive UI review, FL Studio scan/load/state/preset/automation/old-project recall, musical A/B, target-hardware CPU/latency, license/attribution and approved vendor/support metadata. |
| SkellGlitch — skell-gate-vst | 2026-11-16 (current release selection; substantive implementation) | Prior run #94 / commit `fcac874a963331943b9a267e32a103034b3abeea` failed after VST3 link because workflow still requested removed `SkellGlitch_Standalone.vcxproj` (`MSB1009`). Draft PR #8 latest head `2935ee64180a4a9dde69399a0b4f86747206ce80`: JUCE 8.0.12 exact pin, Windows VST3-only workflow, JSON5-aware fail-closed package verifier, 13 tests, Windows Python setup, pluginval strictness 5, actual PR-head SHA + Actions run ID/attempt/event/ref in manifest, real JUCE UI smoke and flat bundle+manifest artifact. Run #97 (#43936168153): Linux verifier tests and C++ DSP CTest passed; Windows checkout/configure is in progress. Runs #95/#96 were superseded by newer PR heads; no Glitch binary/artifact or FL Studio acceptance verified yet. | Complete exact-head Windows MSVC build, UI smoke, bundle verifier, pluginval and artifact inspection; then FL Studio state/automation and audio A/B. |
| Skell Cast — skell-cast-vst | 2026-11-18 (selected; private installer/update/rollback implementation in draft PR #7) | Existing verified parent preview: PR #6 head `a6c1a27e4229df03f9f196094e0309be85a79ad4`, Windows run #44028766379 passed Release VST3 build, core CTest, package-verifier tests, single-bundle staging and pluginval strictness 5. Artifact #14303933435: 5,493,142 bytes, archive SHA-256 `a4cc77ea2a7c77cec5ac21c9669c4d67b3ad80abb782a440a334541d52cac98e`; one flat SkellCast.vst3, AMD64 PE32+ module, binary SHA-256 `c2429ea6e5c32e9886ad5b86db96b78c06ef58c72cafdca41890f3434c3e2780`. Baseline artifact #14186867360 remains preserved. New draft PR #7 `release/cast-private-installer-rollback-20261118`, head `a03a60ffa6a2268f72846f908bfa329552ee31a1`, stacked on PR #6: adds PowerShell 7 per-user install/update/verified-backup/rollback helper, package checksum/provenance/VST3 metadata checks, installer copy in package, Windows integration tests (WhatIf, fresh/idempotent install, update, rollback, tamper/path traversal/duplicate and non-finite JSON/invalid target) and source-contract safety tests. Exact-head Windows run #44342195642 is in progress; CMake/JUCE configure passed and the Release VST3 build is running. The prior superseded PR-only run #44341340635 was automatically cancelled. No new artifact or Windows installer pass is claimed. | Exact-head Windows CMake/MSVC VST3 build, CTest, Python verifier tests, PowerShell install/update/rollback suite, pluginval strictness 5 and artifact/hash inspection; then owner FL Studio scan/load, CABLE/SPARE routing, OBS capture, pass-through A/B, state recall, target CPU/latency, license/contact and code-signing approval. |
| Skel Pad / Scratch — skell-scratch-vst | 2026-11-15 (reported) | Prior checkpoint reported VST3-only PR; no binary rechecked. | Verify exact plugin identity, artifact and host load. |
| Skell Separator — skell-separator-vst | 2026-11-18 (selected; private Windows installer/update/rollback and exact-head release package verified) | Draft PR #5 current head `4c1a1426a3942723f6b793b0cd446b872801cb66`, branch `release/separator-private-installer-rollback-20261118`, stacked on PR #4 package-hardening head `68cf4cf8d687a7d56f2e78714661b5270e4df508`. Current exact-head Windows run #44336350915 passed: Python package verifier, CMake configure, Windows x64 Release VST3 compile, one-bundle package staging, PowerShell install/update/rollback (26 assertions), pluginval v1.0.4 strictness 5 and both artifact uploads. VST3 preview artifact #14440794981, 3,368,574 bytes, SHA-256 `178de35d6b9a6729e352c4e8306ef7f9c4a7c56417dfb164398d2c1d520afcd7`; module 7,853,056 bytes, SHA-256 `f8349e1826349efaf791c8c769c02c5e4f534b517f0032212db2746f61047f19`. ZIP CRC and all five SHA256SUMS entries passed; exactly one top-level VST3 bundle and one AMD64 PE32+ module; no standalone or duplicate VST3. pluginval report #14441473481: 1 plugin found, strictness 5 SUCCESS; tested 44.1/48/96 kHz and 64–1024 block sizes, editor, state, automation and buses. Steinberg VST3 validator path was not configured and therefore skipped. Neural/ASan run #44336351323 passed all 17 steps. Actual JUCE exact-head UI artifact #14441882893: 715,520 bytes, SHA-256 `49ba1daf08670daff912d16f0fbe47bcbbd9ebbf9963bb4372a98231322623b6`; exact-head run #44336351222 passed; eight screenshots inspected, all pixel-identical to PR #4 baseline. Previous first-run failure #44335144422 was a StrictMode null-Count bug in Compare-Object handling, corrected in commit `4c1a1426`; superseded run not used for release acceptance. Preserved baseline artifact #14298141483: 3,368,575 bytes; archive SHA-256 `03febf7fb4373caab72345951f0c5c7ae773418122057eb90cfc14980d344891`; module SHA-256 `537e0af1e80517740f5ca7b3227f995a91ca491f9832ed035a7a81381fe120be`. Baseline/new modules are same size and differ in 12 bytes limited to PE/build timestamp and embedded compile date/time strings; no DSP/UI source changed. Oldest blockers: owner-side FL Studio scan/load/bypass/automation/save-reopen and old-project compatibility; rights-cleared real vocal/music A/B; target-hardware CPU/latency; Quick4 interactive host capture; license/attribution, approved vendor/support contacts, signing and SkellyHub integration. | Owner-side FL Studio and real audio/hardware acceptance; then license/support/signing approval and SkellyHub integration before any commercial release. |
| Skell Stop / StopDial — skell-stop-vst | 2026-11-17 (previous Release selection; exact-head follow-up verified 2026-11-18) | Draft PR #4 head `62f7f0bc2f863cf141640ec9c44ce4dd2fdef007`, branch `release/stopdial-safe-install-rollback-20261117`; exact-head Windows run #44319695813 passed VST3 build, 2/2 JUCE CTests, 17/17 Python verifier tests, PowerShell install/update/rollback assertions, pluginval strictness 5 and Linux ASan/UBSan DSP. Artifact #14433953450: 2,906,137 bytes, archive SHA-256 `0c3176a0c651b40dac1e473f6b51207d4d30127d5fdfc116b2c910ca32af43fa`; one flat StopDial.vst3 bundle, one AMD64 PE32+ module, two unique class IDs and all five embedded hashes matched. Preserved baseline artifact #14341256462 and its module hash; only 10 binary bytes differ from the new build due to PE timestamp and embedded build date/time strings; no DSP source changed. UI artifact #14435156405 contains six real JUCE captures pixel-identical to the prior version; standard/large views inspected with no clipping or overlap. | Owner FL Studio scan/load, automation/preset/state save/reopen, musical A/B, target-hardware CPU/latency, licensing/contact and SkellyHub installer/update/rollback approval. |
| Skell AdlibLab — skell-adliblab-vst | 2026-11-18 (selected; private-preview install/update/backup/rollback implementation completed) | Protected baseline artifact #14196755327 remains recorded. Parent PR #10 head `7187275fd2f5aee8ee5c58ec03caa78f8ca4d2f9`; parent Windows run #44287143589 and artifact #14419617362 passed the previous Release build/pluginval 5. New draft PR #11: `https://github.com/skellyruno/skell-adliblab-vst/pull/11`; branch `release/adliblab-private-preview-installer-rollback-20261118`; head `398f69b1d2373934e5943937e689e142fbbd36b9`. Exact-head Windows run #44365584373 passed DSP/ASan/UBSan/static job 18/18 and Windows VST3 job 14/14 including MSVC x64 build, exactly one VST3 bundle, strict metadata/AMD64 PE32+ verifier, pluginval v2.0.0-beta3 strictness 5 (1 passed/0 failed), PowerShell WhatIf/install/idempotence/root/path/tamper/update/backup/rollback integration (11 checks), and artifact upload. New artifact #14456259709: 7,900,747 bytes; GitHub SHA-256 `dbc501bf8900b4a593691a1b45a9c12a5d891aa9e832b23c5da0a274208e3866`; independently downloaded, ZIP CRC passed, 14 entries, no duplicate/case-colliding paths, all 13 SHA256SUMS entries matched, one 7,839,232-byte AMD64 PE32+ module SHA-256 `ef6c2ff15eb2a46e31627c1158f63a12b23a4a52c60da42e09f09d35ec69a6fa`, product 0.10.2 / Skell Audio, two protected CIDs, installer and guide present, no standalone EXE. UI run #44365584546 passed 10/10; artifact #14456771291 contains 100 scenes plus contact sheet (101 PNGs), all byte-identical to parent UI artifact #14419183558; contact sheet/minimum cosmic layout/preset overlay inspected with no visible clipping or overlap. Exact dependency pins: JUCE 8.0.12 `29396c22c93392d6738e021b83196283d6e4d850`; SkellCore `eb56702153c4373799a4e8e2663e0f158c0115a6`. | Next test: owner-side FL Studio scan/load and MIDI routing, state/preset/automation save-reopen, real musical A/B, target-PC CPU/latency, licensing/attribution, approved vendor/support contacts and signing. Keep PR #11 draft until host/audio/hardware and commercial gates are owner-approved. |
| SkellyTune Mini — skelltune-mini | 2026-11-18 (selected; installer/rollback and exact VST3 class inventory hardened) | PR #10 head `e2946a0b87437aa43242fe76e44e5824330882b9`; Windows run #44274095131 passed 14 installer/rollback assertions, x64 configure/build, editor startup smoke, strict metadata staging, AMD64 PE32+, pluginval v2.0.0-beta3 strictness 5 and artifact upload; portable DSP #44274095187 passed. Artifact #14412709628: 2,934,075 bytes, SHA-256 `3cf7dc8385d71a4cfe8591e7c7c444d6ea406c841ec1fb21de6bb3b3648cfd48`; independent ZIP CRC pass, one flat VST3 bundle, no nested ZIP, strict JSON, two unique CIDs, one 6,571,520-byte AMD64 PE32+ module, all 11 SHA256SUMS entries matched. New draft PR #11 head `022523ced3a5b1fb0c6575f1bcf9a2c633c3908a` requires exactly one processor + one controller and rejects an unexpected third class. Exact-head Windows run #44275482816 passed all 15 installer/rollback assertions, CMake, Release VST3 build, editor startup/layout/paint/IPC smoke, flat package staging, pluginval strictness 5 and upload; portable DSP #44275482606 passed. Artifact #14414742253: 2,934,159 bytes, SHA-256 `a0ae57de953c84d0372f40088db74b7bfe0dc9dc39e2ce441bf335efdad79089`; independent inspection confirms one flat bundle, 2 unique CIDs, AMD64 PE32+ module, all 11 checksums and installer/README/license notices. | FL Studio scan/load/save/reopen, human musical A/B, preset/state/automation recall, target-hardware CPU/latency, installer rollback on a real test machine, licensing and approved vendor/support contacts. PREVIEW_ONLY. |
| Skell Fan — skell-fan-vst | 2026-11-16 (previous release selection; exact-head pluginval repair now passed) | Preserved baseline artifact #14176270462 from run #43749240041: v1.9.0, one AMD64 PE32+ VST3 module, 9,404,416 bytes, original binary SHA-256 `bfafbc0437d958d637763933a81b1766c790bc8ebd759bae4a0463966b6a284f`, archive SHA-256 `0a383ec17c73246122fd128c746bfd8f983105c3378647842c636b5ef3ccfc95`. PR #10 exposed pluginval strictness 5 failure: program 0 had no name. PR #11 commit `a1ffdaf2354f4929a8680d31439d03bdb87342bd` fixes `getProgramName(0)` to `Chorus - Classic` and corrects its regression assertion. Exact-head Windows run #43944668734 passed source checks, 16 package tests, CMake configure/build, DSP/portable tests, VST3 staging, metadata normalization, AMD64 PE32+ verification and pluginval strictness 5. Artifact #14264828558 is a flat bundle + `build-info.json` + `SHA256SUMS.txt`, size 4,889,994 bytes, archive SHA-256 `0d2e247dc21ad5672eaa9dbbc1d84b5edba80bf6af80436fc7ad0b37e66d58d8`; binary SHA-256 `115cee937f29573d98dd62a0464ec9c5c1792d605cc1cc68c3a776d223a7a39d`. I independently inspected the artifact: one `SkellFan.vst3`, v1.9.0, strict JSON metadata, valid PE signature/machine/PE32+; manifest says PREVIEW_ONLY. UI snapshot artifact #14265127600 digest `866d1a2cb6568e15e3f4b75c0287b127dcf3e7d337ab1e0ca4e6252bee41e461` is available but not inspected in this run. | FL Studio scan/automation/state save-reopen, old-project compatibility, real music A/B, target-hardware CPU/latency, vendor URL/support email and license review; reconcile PR #8 UI and PR #9 VST3 release branch before any release. |
| Skell Flang — skell-flang-vst | 2026-11-18 (selected after Spacer; provenance/checksum workflow repair in draft PR #18) | Draft PR #18, branch `fix/flang-provenance-workflow-script-20261118`, head `78e62cdd1d14c3521dde389f9fb18444e0ba48ac`, stacked on PR #17 head `014222082f67eb5c3e72711ed7ad45e6b8b0f347`. Fixes the truncated anchored 64-hex SHA-256 regex and removes duplicated portable job YAML that had been embedded inside the PowerShell run block; limits `cancel-in-progress` to pull_request events, preserving push-to-main and manual `workflow_dispatch`. Exact-head Windows run #44406371683 is in progress; portable DSP and ASan/UBSan jobs passed, Windows CMake configure is running; no new artifact claimed. Previous exact-head run #44406338034 failed. Preserved baseline artifact #14439047016: 1,633,379 bytes, archive SHA-256 `f07c045a877a0554f69bf367f524b34c370fa19ae1ad6e9cd09feab9f59acbee`; ZIP CRC passed, exactly one flat `Skell-Flang.vst3` bundle, strict `moduleinfo.json`, version 0.9.2 / Skell Audio / two unique CIDs, one AMD64 PE32+ module 3,523,584 bytes, binary SHA-256 `e8927658662b978ba6bf4def2040edc3896d1af86821a9d1eb47bd41e8fa2c70`; moduleinfo SHA-256 `55b920dc439e1eaaa64dd4b48781ec5b32b0817eee33102bb0ed0b7efc41e518`. Moduleinfo `Factory Info.URL` and `E-Mail` are empty. UI artifact #14439790352: 5,901,560 bytes, SHA-256 `8f83ff3b2eedcadd0d3a7702297fe5b05890c19f6d4ba77a48bd21a4180ac269`; 81 PNGs (76 full-scene renders plus 5 smoke/contact-sheet images) inspected at compact 540px, standard 720px and large 1080px; no visible clipping/overlap. Oldest blockers: package provenance/checksum/preview notice absent from preserved baseline, owner-approved vendor URL/support email, FL Studio scan/load/save-reopen, real audio A/B, state/preset/automation recall, target-hardware CPU/latency, licensing/attribution, installer/updater rollback and signing. | Complete exact-head run #44406371683; if green, download and independently verify the new VST3 artifact, strict metadata, provenance and every checksum; then owner FL Studio/audio/state/hardware, approved vendor/support details, licensing and installer/update/rollback. |
| Skell Afar — skell-afar-vst | 2026-11-18 (selected; experimental shared-limiter integration; Windows and real-core tests passed on first head; corrected notice now in revalidation) | Protected PR #10 head `642747244270380dfe09bc3d9f8673ab73779b7d`; Windows run #44203361778 and real-core sanitizer #44203361746 passed. Baseline artifact #14382996753 re-downloaded and independently verified: 6,120,924 bytes, SHA-256 `e243c86eac7b9efcb91a8fcd2e76fc76753b7f1af7dc6b85f7e62fdfc3555ab9`; ZIP CRC pass, one flat bundle, one 6,096,896-byte AMD64 PE32+ module, 2 classes, 9/9 checksums matched. New draft PR #11 first head `53f90b4a7afe6ac4be7b7722b4fe680deaf2ff49` passed Windows run #44280992708 (CMake, Release VST3, CTest 12/12, package verifier, staging, 17 installer assertions, Steinberg VST3 validator exit 0, pluginval strictness 5); real-core ASan/UBSan #44280992598 passed CTest 13/13, including `SkellAfarTruePeakIntegration` (1.84 s). Its first artifact #14416928294 (6,120,924 bytes; SHA-256 `7cfc047e9375997a8c6636e01241ecd46a88381e70e7452342ca6b777495b74c`; module SHA `d0c11b576f11efca27d1f1d2b458970da8080b811a3fd8de52a70e00b58ea2ca`) passed ZIP/PE32+/CID/9 checksum checks, but was marked SUPERSEDED because `THIRD-PARTY-NOTICES.txt` still carried the old Core pin. Follow-up commit `a50ddbc7a946bba2baf3681fb17be14561f123b1` corrects the notice to exact experimental Core PR #43 commit `e972e49ef93e021a3993110a0a9603d9774e9def` and reiterates narrow MIT scope/commercial clearance. Corrected-head Windows run #44282855459, real-core ASan/UBSan #44282855521 and JUCE screenshot run #44282855412 were in progress at update time. Real JUCE screenshot run #44280992545 passed; artifact #14416728684 is 3,254,245 bytes, SHA-256 `abe0a97c0a9f85cef7d712dcfb3c1b51ec954376c55d45ddbb7abe96036851ee`, containing 9 real screenshots plus manifests at 825×525, 1100×700 and 1650×1050 (Pro, guided tour and Simple). I inspected compact/default/large, tour and Simple captures; no visible clipping/overlap found. | Finish corrected-head Windows/real-core checks and independently inspect the new artifact with exact notice pin; then FL Studio scan/load, PDC/state/preset/automation recall, real vocal/music A/B, target-PC CPU/latency, commercial licensing and vendor/support approval. Core issue #32 remains open; PR #43 remains draft; detector not BS.1770-certified. PREVIEW_ONLY. |
| Skell Maw — skell-maw-vst | 2026-11-17 (previous Release & Launch selection; install-guide follow-up) | Baseline PR #3 exact-head run #44031640565 passed Windows x64 build, package checks and all seven pluginval strictness-5 checks; artifact #14306008513 was independently inspected (seven AMD64 PE32+ VST3s, 14 unique CIDs, 16 SHA-256 entries; ZIP SHA-256 `efe0d67b4c60a2a7fd2e5e0ec169f5b8359b2f00bc58a441bcb28bb9d46e582f`). New draft PR #5 head `b19f46e3da3b12f0ad58a515b51d7700e52480a2`, run #44078225191, failed the Windows package-validator test with `KeyError: 'WINDOWS-VST3-INSTALL.txt'`; later staging/pluginval/upload steps were skipped. | Fix the install-guide checksum/manifest regression on an owned branch; rerun exact-head Windows package tests + seven pluginval checks and independently inspect the resulting artifact; then FL Studio and commercial metadata. |
| Skell Necromancer — skell-necromancer-vst | 2026-11-18 (commercial-gate PR #3 and VST3-only PR #4 exact-head Windows checks passed; package and real UI artifacts inspected) | Draft PR #3 head `b55e94d719d32463d40528762274299b5fc19ee8`, Windows run #44056313880 passed CTest 8/8, source/UI geometry, independent LUFS/8x true-peak references, 17 package tests and pluginval 1.0.4 strictness 5. Draft PR #4 head `8df3a63cc0c011d435530aeeec13eff0d31bceec`, Windows run #44153560771 passed VST3-only output check, CTest, UI geometry, reference metering, real JUCE capture/rune motion, package tests and pluginval 5. Artifact #14361011381: 2,774,024 bytes, SHA-256 `3a9878a83d5fab62cac6ee45e4958c2e9bfcc257e39cfd35e02d62219ec317af`; inner VST3 ZIP SHA-256 `ee5d1dd6f16a75818c5a299ae5418e180e5a818d6e26511f6f4d59b4a43c9890`; one flat `Skell-Necromancer.vst3`, one AMD64 PE32+ module 5,180,928 bytes, SHA-256 `6d5096ba6d580af35ff6cd88de9de9b606808ad879d7aec83ffef8ffd879e938`, two expected unique CIDs. Manifest records `commercial_release=false`, `license_file=null`, blank URL/email, and only the Montserrat OFL notice. UI artifact #14361395394: 4,096,877 bytes, SHA-256 `ebc1adf099aec357661d0d948115474dff701a8a8e14e932bc4810537ad100a4`; actual 810×428, 1157×612 and 1736×918 captures plus rune before/after inspected; no visible clipping/overlap. | Owner-approved product license; JUCE/SkellCore license/attribution review; HTTPS vendor URL/support email; installer/update/rollback; FL Studio/PDC/state/preset/automation recall; owner listening and real-audio A/B; target-PC CPU/latency; signing. PREVIEW_ONLY. |
| Skell Gate — skell-gate-vst | Not logged | No current release artifact or CI state independently inspected. | Inventory workflow and test bypass, gate timing, denormals and x64 package. |
| Skell Rack — skell-rack-vst | Not logged | No current release artifact or CI state independently inspected. | Inventory plugin format, dependencies, installer/export and host compatibility. |
| Skell AutoTune — skell-autotune-vst | Not logged | Default branch is devin/1778052783-initial-plugin; release baseline and branch purpose need verification. | Confirm branch/PR ownership and JUCE/VST3 packaging before any changes. |
| Skell Spectre — skell-spectre-vst | Not logged | No current release artifact or CI state independently inspected. | Confirm relationship to SkellGlitch, then inspect x64 package and DSP gates. |
| Skell Chess — skell-chess-vst | Not logged | No current release artifact or CI state independently inspected. | Inventory product scope, build target and licensing before release work. |
| BPM Delay Calculator — -bpmdelay-calculator-vst | 2026-11-17 (selected 2026-11-17; VST3-only preview packaging) | Draft PR #1: https://github.com/skellyruno/-bpmdelay-calculator-vst/pull/1, branch `release/windows-vst3-package-20261117`, current head `721db621c326cf1e8d3083edb2bfbb3a87288941`, based on main `6366ff31c5ab8e76ec4a231100ba97a07096d3f9`. Before selection it had no open PR/issues, only main, and zero recorded Actions runs. Main CMake built VST3 + Standalone; the workflow uploaded both and treated pluginval as continue-on-error. PR restricts CMake to VST3, makes pinned pluginval 1.0.4 strictness 5 required, triggers PR/push/manual checks, and adds deterministic package+SHA-256/provenance. Local package tests **7/7 passed**. No pre-existing Windows binary/artifact was found, so no backup is claimed. Current PR head still has no Actions run or status checks; no package artifact exists yet. | Confirm Actions trigger/permissions; exact-head Windows x64 build, pluginval strictness 5, package tests and archive/hash inspection; then FL Studio host-tempo follow, pass-through, project save/reopen, actual UI capture and target-hardware checks. Commercial license/contact metadata must be resolved before release. |
| Checkmate — skell-chess-vst | 2026-11-17 (selected; VST3-only preview packaging) | Draft PR #8: https://github.com/skellyruno/skell-chess-vst/pull/8, branch `release/windows-vst3-preview-package-20261117`, head `b0cd10d73bf6e70cab81047e4c5deefbe6160dc8`, based on main `b21fe68482af69af0d1ca8bfa47e20f6bdd34518`. Baseline main run #43560219659 passed but artifact #14100575125 included both VST3 and EXE; archive SHA-256 `ba8023cfb249f3505221d5bb907e5e7318267b0c80a2dfb8098abbd504dc32e1`, VST3 module SHA-256 `a555a830f6d499e4362e69a4f88228b0fd803b3da3c2f1ed8800ab529240e995`, original moduleinfo SHA-256 `c7eed96d9f690440e1414887c4f47f816fe4534ddca2fbfe07831869fb1f0d79`, and Standalone EXE SHA-256 `e560c4ba0b6130994848bc9b85aea2b1faac120faf0d6c5229ae7831055b6fa7`. The staged normalized moduleinfo SHA-256 is `31527d73da2912538e414aa6cbce66e5c2d07f7152d3ea83cdd102e2095372f0`. New PR uploads VST3 only, keeps Standalone local, normalizes JUCE trailing commas only in staged moduleinfo, verifies AMD64 PE32+, v2.4.0, vendor and two unique class IDs, adds provenance/checksums/preview+rollback notes, and requires pluginval 1.0.4 strictness 5. Local tests 12/12 passed; staging the actual baseline passed and all hashes recomputed. PR run #44099624708 passed CMake Configure and is in the Windows Release Build step; no new artifact/pluginval result claimed. | Finish exact-head Windows build/CTest, 12 tests, pluginval 5, current-build UI preview and VST3-only artifact upload; independently download/check ZIP and hashes; then FL Studio MIDI/audio/state/automation and old-project acceptance, license/contact approval, installer/Hub rollback. |
| MuCalc — MuCalc-VST | Not logged | No current release artifact independently inspected. | Verify standalone/VST3 intent, packaging and numerical tests. |
| MetaTuneInspiredvst | Not logged | Reference/inspired project; license/attribution and distributable status unverified. | Audit origin, licenses and whether it is an internal reference or product. |
| EndlessSmileInspired-VST3 | Not logged | Reference/inspired project; license/attribution and distributable status unverified. | Audit origin, licenses and whether it is an internal reference or product. |
| PitchNet | Not logged | Model/dependency provenance and redistribution terms unverified. | Audit dependency/license provenance before bundling or distribution. |
| LYRICFORGE | Not logged | Product role and downloadable deliverable not assessed. | Confirm whether it is part of the Skelly launch portfolio; inventory build/export. |
| FLAMEEWRLD-Studio-Vocal-Chain | Not logged | Chain/reference project; distributable licensing and format unverified. | Confirm ownership and third-party plugin dependencies before packaging. |
| Skell Sound Match — skell-sound-match | Not logged | No current distributable artifact independently inspected. | Inventory Windows build and validate matching references/data dependencies. |
| SkellCore — skellcore-vst-template | 2026-11-16 (Ecosystem run) | PR #38 font fallback/clickable update badge has four CI workflows green; PR #39 reusable Egyptian rune toolkit has three CI workflows green; PR #40 plugin identity and font/emoji QA documentation remains draft. No standalone distributable or cross-plugin adoption matrix verified. | Validate shared font/emoji/rune components across at least two consuming plugins and retain Windows editor captures. |
| SkellForge — skellforge | 2026-11-16 (Ecosystem run) | Draft PR #28 on `fix/native-moduleinfo-schema-guard-20261116`, stacked on PR #27, adds fail-closed malformed metadata/class validation and four regression tests. Commits `c95a05e5135aed41eca806a84e12328242787155` and `41c9942428d5f4ade4481928a001ff54f5aa5af0`. Ubuntu/Windows CLI, native generator, Windows JUCE-free VST3 compile and official Steinberg validator passed. Experimental artifact SHA-256 `e6910fcda67683f5c0be3a6167a5731cab656e6bf89b95d775880e35eee1208f`; not a commercial release. | Inspect Windows native artifact, licensing/notices, host load and reproducible installer/export. |
| SkellNative — skellnative | Not logged | Ecosystem run #11 reports PR #5 Windows VST3/foundation checks passing; host acceptance not established. | Verify JUCE-free VST3 bundle and load in an actual host. |
| SkellLang — skellLang | 2026-11-16 (Ecosystem run) | PR #4 native schema v2 CI passed; previous 53/54 result included one symlink-permission skip. No signed Windows distributable or external security review established. | Resolve/justify the platform-specific skip, run Windows packaging/security review and verify recovery/decryption boundary. |
| SkellWorld — SkellWorld | 2026-11-16 (Ecosystem run) | PR #18 paired TCP_NODELAY benchmark: at 32 synthetic peers, Linux median p95 event-fanout latency changed from ~40.57 ms to ~0.895 ms; Windows showed no comparable gain. This is localhost protocol testing, not DAW/audio latency. | Verify Windows runtime/security and keep the benchmark claim scoped to synthetic networking. |
| Skell Project Hub — skell-project-hub | 2026-11-16 (Ecosystem run) | v2.3 reliability/plugin-verification work reviewed; no verified Windows installer/export or real install/update/backup/rollback cycle recorded. | Test discovery, install, update, backup and rollback against inspected Windows VST3 preview bundles. |
| Skell Studio / DAW — skell-studio | Not logged | Separate Studio automation last recorded Nov 13; Ecosystem run #11 reports ML-first bootstrap draft. No release installer or FLP acceptance verified here. | Windows startup/build, FLP import/open, VST3 hosting, audio-device setup and installer/export. |
| Artist / album website | 2026-11-16 (Websites V83) | 36/36 source checks passed; November 20 release date, 12 tracks, `untitled.wav`, Music and Plugins pages preserved; five audio previews decoded. Browser playback, mobile-device acceptance, storefront and email signup remain unverified. | Real browser playback/mobile layout; coordinate storefront, email signup, pricing/trial and product metadata with release engineering. |
| Skelly Creative / 322-inspired site | 2026-11-16 (Websites V84) | 14/14 source tests passed. Corrected skull orbital/cheek/maxilla/teeth geometry; renderer now uses ResizeObserver instead of per-frame layout measurement. Actual front/turned/mobile procedural-mesh captures were regenerated; front/turn changed 75,111 pixels. Chromium/GPU WebGL remains blocked by ERR_BLOCKED_BY_ADMINISTRATOR; domain spelling and physical mobile performance remain unverified. | Real browser/WebGL/mobile acceptance and owner-confirmed domain before any deployment. |
| Skell Preset Showcase website | 2026-11-16 (Websites V23) | 42/42 source checks passed; five reduced-motion checks passed. Existing ecosystem/skull implementation preserved. Chromium/GPU WebGL and full-page desktop/mobile browser acceptance remain unverified; no deployment. | Verify V23 in real browser/WebGL, inspect full-page desktop/mobile and preserve prior recovery archives. |

## Rotation commitments
1. Skell Silence — substantive Windows VST3, pluginval and UI capture verification.
2. Skell Stop / StopDial — package-verifier correction and Windows rerun.
3. SkellGlitch — Windows VST3-only release workflow and verifier.
4. SkellFan — exact-head pluginval strictness-5 defect repair passed.
5. Skell Choir — direct VST3 bundle staging, strict metadata/PE32+ validation, pluginval 5, native tests and all 14 package-verifier tests passed; artifact #14279527660 independently inspected.
6. Skell Key — exact-head run #43965038432 still has the pluginval report/exit-code mismatch; diagnose before acceptance.
7. Skell Delay — current substantive release-packaging work: safe JUCE metadata normalization, strict JSON/CID checks, AMD64 PE32+ validation, preview provenance and checksums. PR #9 exact-head rerun #43983322085 queued after fixture correction.
8. At least seven distinct non-DeEsser plugins now have substantive release-engineering work: Silence, StopDial, SkellGlitch, SkellFan, Choir, Key and Delay. Continue rotating and broaden to Skell Master, Maw, Skell Studio/DAW, Project Hub, SkellForge/SkellNative/SkellCore and installers.
9. Next release selection should be a different project: **Skell Master** is the leading candidate because the latest Preset Audit confirms the output limiter remains sample-peak-based and a synthetic near-Nyquist case overshoots the intended true-peak ceiling by about +0.464 dBTP, with an 11-sample global latency concern. The repository currently has several active drafts (#5–#9); inspect exact branch ownership and avoid the Preset Audit branch before touching DSP. If all relevant branches are being edited, rotate to **Skell Maw** instead.
10. Keep DeEsser parked for the six-run hold unless a critical security/regression emergency is proven.

## Current release decision

**Provisional first distribution candidate: Skell Key 0.1.0 preview.** The exact-head Windows VST3 package and CI install/update/rollback assertions are verified on draft PR #12 (run #44261809007; artifact #14408776507). The artifact is a flat AMD64 PE32+ bundle and its 11 package plus 3 tool checksums matched when independently re-downloaded. This makes Key the shortest current delivery path, not a commercially approved product.

Key remains PREVIEW_ONLY and unsigned. No owner-approved product LICENSE/COPYING exists; the pinned JUCE 8.0.12 and SkellCore license/attribution need review; VST3 Factory Info URL and E-Mail are blank. FL Studio scan/load, Key↔Mini sync, rights-cleared real-audio A/B, state/preset/automation recall, target-PC CPU/latency, real-device install/rollback and code signing remain open.

**Engineering alternate: Skell Necromancer 0.1.0 preview.** Draft PR #3's commercial metadata gate and PR #4's Windows VST3-only target both have exact-head Windows CI green. Artifact #14361011381 and real UI artifact #14361395394 were independently inspected. The package still records `commercial_release=false` and `license_file=null`; vendor URL/email are blank, and no installer/rollback or FL Studio/owner-listening/target-hardware acceptance is established. Its mastering-oriented DSP claims require more extensive true-peak, loudness, A/B and CPU evidence.

Skell Choir remains a verified packaging baseline, Skell Delay remains a strong VST3 package candidate, and Skell EQ/Afar continue strict metadata hardening; none is promoted to commercial-ready from CI alone.

**Decision: no commercial release is authorized.** Keep preview artifacts private, preserve their checksums and source revisions, and do not add generic legal text, guessed contact details, pricing, trial terms or distribution permissions.
## First product launch readiness matrix

**Provisional first distribution candidate: Skell Key 0.1.0 preview.** It is the shortest current path because the exact-head Windows VST3 package and per-user install/update/rollback test pipeline are already verified. This is a recommendation only, not owner approval or a commercial-release decision. Skell Necromancer is the second engineering candidate: its DSP/reference checks and actual UI capture are stronger, but it has no installer/rollback package and carries additional mastering-grade acceptance work.

| Gate | Status | Evidence / next requirement |
|---|---|---|
| Windows VST3 build / download | PASS — private preview | [Skell Key artifact #14408776507](https://github.com/skellyruno/skell-key-vst/actions/runs/44261809007/artifacts/14408776507); 2,168,633 bytes, archive SHA-256 `d26911874f6891ab1744b9a3c5709104e46705fab8359d1710e4ad05de532513`; one flat AMD64 PE32+ module, binary SHA-256 `90cee58ddf11d5ff61f8d49b3a66007ce1fd5d143ce69a5acecf17a3814f792c`; all 11 package and 3 tool checksums matched. |
| Installer / update / rollback | PASS — CI only | Draft Key PR #11/#12 Windows run #44261809007 passed the package, install/update/rollback and non-destructive test-root assertions. A real target-PC install/rollback is still UNVERIFIED. |
| FL Studio scan/load | UNVERIFIED | Owner-side Windows host test required. |
| Key ↔ SkellyTune Mini sync | UNVERIFIED | Verify a real two-plugin session and saved/reopened project. |
| Sound / analysis A-B | UNVERIFIED | Test rights-cleared commercial recordings; existing score/synthetic corpus is not a guarantee. |
| Preset / state / automation recall | UNVERIFIED | Save, close, reopen and verify existing projects and parameter automation. |
| Current UI / Quick4 | UNVERIFIED | No current Skell Key Quick4 screenshot or interaction capture was inspected in this run. |
| Product and third-party licensing | BLOCKED — owner review | No approved product LICENSE/COPYING; JUCE 8.0.12 and pinned SkellCore license/attribution require review. The preview notice is not a license grant. |
| Vendor URL / support | BLOCKED — owner input | Current VST3 Factory Info URL and E-Mail are blank. Do not invent contact details. |
| Code signing | UNVERIFIED | Current installer/package is unsigned; certificate and signing policy are owner decisions. |
| Website storefront / email signup | UNVERIFIED | Coordinate with Websites automation; no deployment or commerce changes in this run. |
| Pricing / trial / terms | OWNER APPROVAL REQUIRED | No price, trial duration, refund or commercial terms were selected. |

**Engineering alternate — Skell Necromancer 0.1.0:** exact-head Windows VST3-only build, DSP/reference tests, package validation, pluginval strictness 5 and real UI captures passed on PR #4; its artifact remains `commercial_release=false` with no product license or vendor/support contacts. FL Studio, owner listening, target-hardware CPU/latency, installer/rollback and mastering-grade true-peak/loudness acceptance remain open.

A green build or downloadable Actions artifact is not a commercial release. Keep both candidates private until every gate is independently closed.
## Release & Launch checkpoint 11 — 2026-11-16 19:55 EST

### Selected project: Skell EQ (skell-eq-vst)

Selected after the Preset Quality Audit explicitly identified the missing automated A/B snapshot host-state roundtrip test. Master was not selected because the Preset automation had just changed its true-peak PR #9 branch and its exact-head Windows workflow was active; Delay was already under the previous release selection and its latest package run has now completed. EQ's package PR #9 had passed its exact-head Windows gates, leaving a concrete, isolated compatibility gap to close.

- New draft PR #10: https://github.com/skellyruno/skell-eq-vst/pull/10
- Branch: test/eq-ab-snapshot-state-roundtrip-20261116
- Single squashed commit: 90bbe8e9cb0dee225a8c50fb70fd7804de7db1d0
- Base: main at 07089a613e06a24e0ef5ea3491e945601cbb45e5
- Files: tests/state_roundtrip.cpp and CMakeLists.txt only.
- Change: JUCE-backed Windows-only CTest harness instantiates the real processor and exercises A/B snapshot store/load, host-state serialization/restoration, current parameter state, selected-band restore, repeated saves without nested snapshots, old-state compatibility, and malformed/unknown/out-of-range/non-finite snapshot data. It creates a test console executable only; the plugin remains VST3-only.
- Exact-head Actions run #43991230953: Windows and macOS configure passed; both builds were still in progress at the 19:55 check. No new test result or artifact is claimed. Windows CTest must pass before PR #10 can advance.
- Local Quick4 kit was restored from Library; JUCE 8.0.12 and CMake/Ninja/C++/xvfb-run are present. EQ's exact SkellCore include pin is c4ae09c896fa84279d3cc42f19925f97a7e5c124. The kit's existing renderer supports Master/Preset, not EQ, and this run did not have a local EQ checkout; therefore no local EQ compile or current EQ screenshot is claimed. This is a state-test-only change, with no UI edits.

### Freshly verified neighboring release evidence

**Skell Delay PR #9** — https://github.com/skellyruno/skell-delay-vst/pull/9

- Exact head: 5a148e78213d099a912d6956912b8e561f137654
- Run #43984652327 completed successfully on Windows, Linux and macOS. Windows package-verifier tests, CMake configure/build, DSP/stress/real-time CTest, Windows VST3 staging, and pluginval strictness 10 passed. Linux and macOS configure/build, CTest and pluginval strictness 10 passed.
- Windows artifact #14284769004: https://github.com/skellyruno/skell-delay-vst/actions/runs/43984652327/artifacts/14284769004
- Downloaded archive SHA-256: d0f0196f3395af5e4b0d7ecba86a1366bdfea7c92e8be20752a47b45e763599b
- Independent inspection: ZIP CRC passed; exactly one Skell-Delay.vst3 bundle and one Windows module; metadata Skell-Delay / Skelly Audio / 1.0.0, strict JSON, two classes; AMD64 PE32+ binary size 8,945,152 bytes, SHA-256 7b9b131368a41412e6e15f0e879908c984c53a1bf5d4300c28b1f499f111adbe; build-info.json and all three SHA256SUMS entries verified.
- Archive includes a package/ wrapper directory and the VST3 bundle, manifest and checksums. No installer executable is present in this artifact despite the workflow's installer-upload step name. Manifest remains preview-only.
- Oldest blockers: FL Studio scan/automation/save-reopen and old-project compatibility; real audio A/B and owner approval; vendor URL/support email; target Windows CPU/latency; Quick4; license/attribution; SkellHub updater/rollback. Do not call this a release.

**Skell EQ PR #9** — https://github.com/skellyruno/skell-eq-vst/pull/9

- Exact head: fe35edb7720b17b1120b5394cad79d1b3ee3aae0
- Run #43903503501 succeeded: source checks, CMake configure/build, existing DSP CTests, VST3 staging, strict metadata/identity, AMD64 PE32+, pluginval strictness 5 and provenance.
- Artifact #14245745380: https://github.com/skellyruno/skell-eq-vst/actions/runs/43903503501/artifacts/14245745380
- Downloaded archive SHA-256: c53830878b07930c87036cee1f1344157c6f38fa1495e54ee15dffcf46e2c610
- Independently inspected: ZIP CRC passed; exactly one Skelly EQ.vst3 bundle and one Windows module; Skelly EQ / Skelly Audio / 2.7.0, two unique class IDs; AMD64 PE32+ module 4,513,280 bytes, SHA-256 d556ddb218ffb5fa25db8b238a0e001694c2fab1278db1d76ab243dabe229414; all three SHA256SUMS entries matched. Manifest remains preview-only.
- Oldest blockers remain FL Studio compatibility/state recall, real audio A/B, vendor/support metadata, target-hardware CPU/latency and rollback. PR #10 adds the missing automated A/B state coverage; its exact-head build is not yet complete.

**Skell Master PR #9** — https://github.com/skellyruno/skell-master-vst/pull/9

- Latest exact head: c4e57d85f42892417e2b305bc023f194666aed12
- Preset automation reports Windows workflow #43986671477 passed Windows VST3 build, CTest 9/9, strict metadata, true-peak guard, five-band coloration, post-limiter presence, UI geometry/contrast and hosted VST3 audio at three rates. This is cross-automation evidence, not a fresh Release & Launch build in this checkpoint.
- Keep PRs #5–#9 draft and do not edit their active branches while the Preset automation owns them. FL Studio and user-listening acceptance remain open.

### Next rotation

Do not select EQ again next run unless PR #10 reveals a new critical regression. Prefer a different under-served plugin such as Skell Maw, Afar, Separator or Cast after checking active branches and exact-head CI. DeEsser remains parked. Continue the minimum-three-distinct-non-DeEsser implementation requirement; the current rotation has already included Silence, Stop/StopDial, Glitch, Fan, Choir, Key, Delay and now EQ.


### PR #10 VST3-only follow-up — 2026-11-16 20:00 EST

- EQ PR #10 head was consolidated into one commit, 5518262771d72286302340994a2ce44b86d367ea, still based on main 07089a613e06a24e0ef5ea3491e945601cbb45e5.
- CMake now removes the old Standalone plugin format. The product target is VST3-only; the new Windows-only console test executable is not a plugin format. enable_testing() is explicit for the new test gate.
- New exact-head run #43992090707 is in progress on Windows and macOS; Configure is running and build/CTest/package steps are pending. No exact-head Windows build or A/B state-test result is claimed yet.
- Superseded run #43991230953 completed its macOS build/CTest but its Windows build was still running at the 20:00 check. The available GitHub connector exposes no workflow-cancel action, so no cancellation was attempted; this old PR-only run was not a main/manual/release run.


## Release & Launch checkpoint 12 — 2026-11-16 20:53 EST

### Selected project: Skell Maw (skell-maw-vst)

Skell Maw was selected after checking the latest Preset, Ecosystem, Websites and Nightly results. The Preset automation was actively editing Skell Master PR #9; Ecosystem's latest implementation was Delay and SkellNative, and its next planned workstream is Skell Studio; Websites was on Artist V86; the latest nightly report was the November 15 review. Maw had a real existing Windows VST3 collection artifact and a concrete packaging defect, while neither open Maw branch was being edited by those latest automation runs.

- Existing source PR #1 remains open/draft at `ba44383cb14d1a84eff0a6d256c7acdd4c1065a3`; its exact-head Windows build and JUCE-free DSP tests passed in run #43630679741.
- Existing PR #2 (hero readout bounds) remains open/draft at `8c92d0557d123e8f5e67bb2e11f1448491157808`; it is untouched and has no associated workflow run.
- New stacked draft PR #3: https://github.com/skellyruno/skell-maw-vst/pull/3
- Branch: `release/maw-package-manifest-20261116`; latest commit `863372d8e9539976d2975cf2bbad816209d06041`; base branch `agent/skell-maw-quality-20261114` at PR #1 head `ba44383cb14d1a84eff0a6d256c7acdd4c1065a3`.
- Added `Tools/verify_vst3_package.py` and `Tools/tests/test_verify_vst3_package.py`; updated `.github/workflows/build.yml`.
- The package verifier requires exactly seven named VST3 bundles, one correctly named `Contents/x86_64-win/*.vst3` module per bundle, AMD64 PE headers, strict normalized moduleinfo JSON, expected product/vendor/version, processor + controller class pair, globally unique CIDs, and writes a build provenance manifest, preview-only notice and SHA256SUMS.
- The eight-test Python suite passed locally. Running the same validator against the actual downloaded Windows CI artifact staged all seven bundles; all checksums recomputed successfully. It identified blank vendor URL/support email as commercial-release warnings.
- The original Actions artifact was double-wrapped: the outer artifact ZIP contains a second `SkellMaw-VST3.zip`. PR #3 changes Actions upload to the staged package directory directly, so the downloaded artifact will contain the flat bundles and sidecars without a nested ZIP.
- Exact-head PR #3 run #43999384010: Linux `dsp_tests` passed. Windows job has completed checkout and Python setup; CMake configure was in progress at the checkpoint. The new Windows compile, package-tool tests, staging and artifact upload are not yet passed.
- The local normalized repack from the existing Windows binary baseline is available at `SkellMaw-Windows-VST3-Preview-normalized-run43630679741.zip`, SHA-256 `a8233c35857122df492840e43e568b055cfd1a66c364cf55d8b32efb9fcfc746`. It is a metadata-normalized repack of the old CI binary, not a new build or commercial release.

### Release gates still open for Maw

- Windows compile and package verifier on PR #3's exact head.
- FL Studio scan, loading, automation, project save/reopen and old-project compatibility.
- Real music audio A/B and owner listening approval.
- Target Windows hardware CPU and latency.
- Current editor/menu/animation inspection and Quick4 screenshot workflow.
- Licensing/attribution, vendor URL and support email.
- Installer/export, SkellyHub install/update/backup/rollback.
- Storefront, email signup, support and pricing/trial approval.

### Next rotation

Do not select Maw again on the next run unless a new critical regression appears. Choose a different non-DeEsser project after checking exact-head CI and active branch ownership; Afar or Separator are candidates, with Skell Studio/Project Hub also remaining in the broader rotation. DeEsser remains parked.

No PR was merged. No installer was published, no existing installation was overwritten, and no website, DNS, payment or production action was taken.


### Checkpoint 12 CI follow-up — 2026-11-16 20:55 EST

- Added seven individual Tracktion/pluginval strictness-5 steps, one for each named Maw VST3 bundle, before the artifact upload. Windows job timeout is 60 minutes.
- Latest PR #3 head is `77762003da0a88f9ecbd9ed9da1b08e53749a397`; exact-head workflow run #43999540508 is pending. The superseded PR-only run #43999384010 was automatically cancelled during Windows configure; main/manual/release runs were not touched.
- Keep PR #3 draft until all seven pluginval checks, Windows build, package tests, strict metadata/PE validation and artifact upload pass.

### Checkpoint 12 verifier hardening follow-up — 2026-11-16 20:57 EST

- Tightened the PE check from AMD64 machine-only to AMD64 PE32+ optional-header magic `0x20b`; also rejects extra architecture module files inside a bundle.
- Added two regression tests (PE32 rejection and duplicate-architecture rejection). Local suite now passes 8/8.
- Re-ran the verifier against the actual seven-bundle Windows artifact. All seven modules passed AMD64 + PE32+ checks, all 14 class IDs were unique, strict normalized metadata parsed, and every generated SHA256SUMS entry matched. Repacked preview archive is 60,105,517 bytes with SHA-256 `dbdc83a34ab8be1e7c0d59accfe36cbb70eb0cbe57b236aba179a38a80220325`.
- Current PR #3 head: `863372d8e9539976d2975cf2bbad816209d06041`; exact-head Actions run #43999829295 is pending. Keep all seven pluginval strictness-5 checks and the artifact upload as mandatory gates.

### Next-run candidate evidence — Afar vs Separator

Afar currently outranks Separator for the next different-plugin selection: its latest VST3-only release PR #7 has a proven Windows package-step failure after successful compile and 5/5 tests because the PowerShell packaging step still demands a Standalone EXE. This is a concrete, bounded release blocker and no artifact was uploaded. Separator PR #4 has a successful Windows package/upload run and artifact #14191561557, so its next step is independent artifact inspection and host/runtime testing rather than a known CI repair. Recheck current branch ownership before starting Afar; PR #7 and #8 remain open/draft and neither branch should be edited in place.

### Checkpoint 12 CI progress — 2026-11-16 21:05 EST

Exact-head Maw PR #3 run #43999829295 advanced: Linux DSP tests passed, Windows CMake configure passed, and the Windows seven-plugin Release build is now running. Package-verifier tests, staging, pluginval strictness 5 for all seven bundles and artifact upload have not run yet. Keep draft; no merge.


## Release & Launch checkpoint 13 — 2026-11-16 21:48 EST

### Highest-priority selection: Skell Maw

The latest Nightly Blueprint review surfaced a new, exact-head release blocker in Maw, so it took priority over routine rotation: Windows run #43999829295 compiled the seven-plugin collection and passed its DSP, package-verifier and staging steps, then failed the first pluginval strictness-5 check on Dark Forest with `Programlist 000->Program 000: has no name`. The six remaining pluginval checks and artifact upload were skipped. This is a concrete VST3 host/program-list compatibility failure, not a speculative issue.

- Fixed the shared source root cause on Maw PR #3: `MawProcessorBase::getProgramName(0)` now returns `Default` instead of an empty string while `getNumPrograms()` advertises one program.
- Commit: `8c9a352dc80bffb1e5a7a489abeda5fc9120a312`.
- Fresh exact-head run #44007318584: Linux DSP tests passed; Windows configure is running. All seven pluginval reruns and artifact upload remain pending.
- PR #3 remains draft. No merge.

### Additional non-DeEsser release work: Skell Afar

Afar's prior VST3-only PR #7 had a reproducible Windows package failure because the workflow still required a Standalone EXE. A new child draft PR #9 is stacked on the latest v0.6.0 / SkellCore v0.7.0 integration PR #8, preserving PRs #7 and #8:

- Branch `release/afar-vst3-package-only-20261116`, head `9e594ce5b851ad3dfaccf0d7abe08100c8fdd937`.
- CMake now builds VST3 only; workflow no longer searches for `Skell-Afar.exe`.
- Added one-bundle packaging, strict metadata/version/class/CID checks, AMD64 PE32+ validation, preview provenance, checksums, and strictness-5 pluginval.
- Local Python verifier suite: 6/6 passed.
- Exact-head run #44006917500: artwork and JUCE/SkellCore configure passed; Windows compile is in progress. Real-SkellCore headless sanitizer and Guided Tour screenshot workflows remain in progress. No current-head package is available yet.

### Cross-automation check

- Ecosystem Development's latest completed work was Skell Delay's PowerShell metadata-gate repair (PR #7, commit `053efeb`, new run #43998879350) and Skell Studio screenshot work (PR #10, run #43998686231); no Maw or Afar branch was reported active there.
- Websites Development completed Creative V87; Artist V86 and Preset Showcase V24 remain separately tracked. No deployment or DNS action.
- Preset Quality Audit's latest scheduled execution failed with the generic message "There was a problem with your scheduled task"; no new code/test result was available from that run.
- Nightly Blueprint Review independently identified the Maw program-name failure and prioritized its correction.
- DeEsser remains parked; no DeEsser work was performed.

### Rotation and next test

This execution contains substantive work on two distinct non-DeEsser plugins: Maw (shared VST3 program-name fix + package gate follow-up) and Afar (VST3-only packaging/workflow + verifier tests). At least one more distinct non-DeEsser plugin must receive substantive implementation within the next six-run window. After Maw's urgent CI rerun, the next release selection should rotate away from both Maw and Afar unless a new critical regression appears; inspect Separator's existing successful artifact or choose another under-served plugin after checking branch ownership.

No draft PR was merged. No public release, production installation, website deployment, DNS change or payment action was performed.


## Release & Launch checkpoint 14 — 2026-11-16 22:16 EST

### Selected project: Skell Key (skell-key-vst)

Key was selected instead of another already-green packaging branch because its newest one-level VST3 packaging PR #8 had a confirmed exact-head Windows workflow failure at the final pluginval gate, despite the saved pluginval report showing `SUCCESS`. The artifact upload was skipped, so there was no new installable one-level bundle. Separator PR #4's Windows package run and Skell Silence PR #14's Windows/pluginval run were green; Maw's newly fixed seven-plugin run and Afar's VST3-only package run have now also completed successfully. Key was the clearest isolated CI false-negative with a direct, bounded fix.

- PR #8 remains open/draft at head `3786211d3c9496565c35a11b743fa9a9113275d2`; its existing baseline and packaging work were preserved.
- Failed run #43965038432: Windows VST3 configure/build passed, tuning sync CTest passed 2/2, one-level package staging passed, pluginval strictness 5 emitted a report ending in `SUCCESS`, but the PowerShell script saw an empty `$LASTEXITCODE` and failed the gate. No product artifact was uploaded. Report artifact #14276525530 is preserved; SHA-256 `514458b762296f47d2064445f3a5c90e52085369ee9d45f6904d4b7343aab219`.
- New draft PR #9: https://github.com/skellyruno/skell-key-vst/pull/9; branch `fix/key-pluginval-exitcode-20261116`; latest commit `3d8c97db934debe2083f67875f6a3080f1513061`; stacked on PR #8 branch `release/key-flat-vst3-artifact-20261116`.
- Changed only `.github/workflows/build.yml`: run pinned pluginval with `Start-Process -Wait -PassThru`, gate on the actual process `ExitCode`, preserve stdout/stderr logs in the always-uploaded diagnostic artifact, require exactly one pluginval text report and a final `SUCCESS` marker before uploading the flat VST3 bundle. The file was fetched again after the write and checked for a single report-upload step and a single VST3 artifact-upload step.
- Exact-head PR run #44009458351 is now running on commit `3d8c97db934debe2083f67875f6a3080f1513061`; Windows CMake configure passed and the Release VST3 build is running; CTest, pluginval and artifact upload are pending. An earlier intermediate push run #44009317071 failed before a job was available and is superseded by this corrected PR run. Do not infer the process invocation works until the current run completes.
- No DSP, UI, VST3 identity, parameter IDs, presets, saved state or host automation changed.

### Newly closed packaging CI results (independent artifact inspection)

**Skell Maw PR #3** — https://github.com/skellyruno/skell-maw-vst/pull/3

- Exact-head Windows run #44007318584 passed Windows Release compile, eight package verifier tests, bundle staging, all seven pluginval strictness-5 checks and upload; Linux DSP job passed.
- Artifact #14295408141: https://github.com/skellyruno/skell-maw-vst/actions/runs/44007318584/artifacts/14295408141
- Downloaded ZIP size 60,106,306 bytes; SHA-256 `97e9e42da8969ea68ff345d4b875d1905a0ea7f8ed49b82760b3ff79b7aed4ef`. ZIP CRC passed.
- Exactly seven expected VST3 bundle roots and seven Windows modules; all AMD64 PE32+, v1.0.0, Skell Audio; 14 class IDs unique; all 16 checksum manifest entries recomputed and matched. No nested ZIP or Standalone executable.
- All seven moduleinfo files have blank vendor URL and support email. Package is preview-only; FL Studio, real audio A/B, licensing and owner contact approval remain unverified.

**Skell Afar PR #9** — https://github.com/skellyruno/skell-afar-vst/pull/9

- Exact-head run #44008363338 passed Windows VST3 build, CTest, package verifier, bundle staging, pluginval strictness 5 and artifact upload; real-SkellCore sanitizer/headless run #44008363339, JUCE Guided Tour screenshot run #44008363345 and portable DSP run #44008363346 also passed.
- Artifact #14296195883: https://github.com/skellyruno/skell-afar-vst/actions/runs/44008363338/artifacts/14296195883
- Downloaded ZIP size 6,100,257 bytes; SHA-256 `91777b84aad024b8015b7b510ffb53c3414aee74d2091d0adccbc955ac0d8f80`. ZIP CRC passed; exactly one flat `Skell-Afar.vst3`, v0.6.0, one AMD64 PE32+ module (6,096,896 bytes; SHA-256 `141df41650f510b5cbf49210f34c8a359fa9049481f5686fb397336a5275340f`), 2 unique class IDs, strict normalized JSON and all five checksum entries matched.
- Artifact is explicitly preview-only. Vendor URL/support email are blank. Shared SkellCore issue #32 (true-peak/intersample overshoot), FL Studio host/state recall, musical A/B, CPU/latency and licensing remain release blockers.

### Cross-automation check

- Preset Quality Audit latest run returned the generic scheduled-task failure message; no new Preset source/test result was available. Skell Master PR #9 remains owned by the Preset workstream; no Master branch was edited.
- Ecosystem Development latest result: Skell Delay release metadata PowerShell fix PR #7 / commit `053efeb` and Skell Studio screenshot work PR #10; SkellCore PR #39, SkellForge PR #28, Project Hub PR #13, EQ PR #10, Preset PR #50 and Master PR #9 are active/preserved. No overlapping branch was edited.
- Websites Development latest result: Creative V87 five-page source and static QA; Artist V86 and Preset Showcase V24 remain separate. No website deployment/DNS action.
- Nightly Blueprint Review independently recorded the Maw program-name blocker and its correction; three PDFs were validated. DeEsser remains parked.

### Next release step and rotation

Keep Key PR #9 draft until exact-head Windows CI proves the Start-Process exit-code gate, strictness-5 pluginval and one-level bundle upload. Then independently download and verify the flat artifact. After Key, rotate to a different project rather than repeating Key: Separator artifact #14191561557 still needs independent inspection, while StopDial PR #3's latest Windows workflow failed and should be checked for its exact failure before a new branch is chosen. Do not edit other active PR branches.

No PR was merged. No public release, production install, website deployment, DNS change or payment action was performed.


## Release & Launch checkpoint 15 — 2026-11-16 22:49 EST

### Selected project: Skell Separator (skell-separator-vst)

Separator was selected after the prior Key run because the latest release evidence showed a near-ready Windows VST3 build with a concrete packaging gap: the successful baseline Actions artifact was double-wrapped, its moduleinfo used JUCE trailing commas, and the workflow had no pluginval gate. The other current candidates were either owned by active automation branches (Delay, Master, Studio, EQ, Project Hub) or had Windows validation still in progress (StopDial). Maw, Afar and Key already had successful preview packages, so Separator was the best non-overlapping implementation target.

- PR #4 remains draft: https://github.com/skellyruno/skell-separator-vst/pull/4
- Branch: `release/separator-vst3-artifact-gate-20261115`
- Latest head at this checkpoint: `68cf4cf8d687a7d56f2e78714661b5270e4df508`; based on main `f0b2eb8e651cf9c65e204c544db0cc691eeaaee5`.
- Added `tools/verify_vst3_package.py` and 11 offline regression tests in `tests/test_vst3_package.py`.
- Verifier checks exactly one bundle/module, CMake-derived product version, vendor/product/class identity, processor/controller categories, unique 32-hex class IDs, duplicate JSON keys, AMD64 PE32+ and the expected Windows VST3 path. It normalizes JUCE trailing commas only in the staged copy and confirms the source bundle remains unchanged.
- Staged output includes `build-info.json`, `vst3-verification.json`, `PREVIEW-ONLY.txt` and `SHA256SUMS.txt`.
- Workflow now pins pluginval 1.0.4, runs strictness 5 through `Start-Process -Wait -PassThru`, requires a clean SUCCESS report, and uploads the stage directory directly to eliminate the nested ZIP.
- Local equivalent verifier suite passed 11/11; the real downloaded baseline bundle passed identity, version, class/CID and PE32+ checks. The baseline artifact was not a new build.
- Exact-head Windows run #44013800819 passed the package-verifier tests and had CMake configure in progress at the checkpoint; build, stage, pluginval and artifact upload remain pending. Neural run #44013800868 and UI screenshot run #44013801079 were still running. Do not claim current-head acceptance until all finish.
- UI artifact #14191458575 was inspected: standard/compact/large/bypass/neural/guided-tour screenshots show no visible clipping or overlap. Quick4 local rendering is not wired for this repo.

### Prior checkpoint follow-up — Skell Key

The Key release fix is now verified, closing the prior checkpoint's pending item:
- Exact-head run #44009458351 completed successfully: Windows Release build, tuning CTest 2/2, staging, pluginval strictness 5 and upload all passed.
- Artifact #14295249929 was downloaded and independently inspected: one flat VST3 bundle, no nested ZIP, AMD64 PE32+ module and correct binary hash; details are in the project row above.
- The factory metadata still has blank URL/email and the repository lacks a license notice. This is a technical preview, not a commercial release.

### Cross-automation ownership and priority check

- **Preset Quality Audit** latest result: Skell Master PR #9 Windows build, CTest 9/9, true-peak guard, coloration, presence, UI geometry and hosted audio at three rates passed. The Preset automation actively owns Master PR #9; no Master branch was edited.
- **Ecosystem Development** latest result: Skell Delay PR #7 PowerShell metadata serializer correction and Skell Studio PR #10 screenshot timing/duplicate-capture fixes; SkellCore PR #39, SkellForge PR #28, Project Hub PR #13, EQ PR #10 and Preset PR #50 remain active. No overlapping branches were edited.
- **Websites Development** latest result: Skelly Creative V87 five-page implementation and static regression/screenshot checks; Artist V86 and Preset Showcase V24 remain separate. No deployment, DNS or payment action.
- **Nightly Blueprint Review** updated both master blueprints and the consolidated progress PDF; it confirmed the Maw program-name failure from earlier evidence. Maw's later exact-head run #44007318584 is now green with seven pluginval passes and artifact upload.
- **DeEsser remains parked**; no DeEsser branch, issue or PR was changed.

### Remaining release gates

- Separator: exact-head Windows build/pluginval/artifact; FL Studio scan/load/bypass/state/automation; old-project compatibility; neural/ONNX runtime and streaming latency; audio A/B; CPU/latency on target hardware; licensing and contact metadata.
- Key: FL Studio/key synchronization, state recall, A/B, licensing and contact metadata.
- Maw/Afar: FL Studio, listening approval, license/contact metadata; Afar also remains blocked by SkellCore true-peak issue #32.
- All preview packages remain unmerged and non-commercial. SkellyHub updater/rollback, storefront/email signup, support and pricing/trial approval remain portfolio-wide blockers.

### Next rotation

Do not select Separator again next run unless its exact-head CI reveals a new critical failure. Choose a different non-DeEsser plugin after checking current branch ownership and exact-head Actions; Cast is an under-served candidate, while StopDial should not be edited until its in-progress PR #3 validation finishes.

No PR was merged. No public release, production install, website deployment, DNS change or payment action was performed.


## Release & Launch checkpoint 16 — 2026-11-17 00:04 EST

### Selected project: Skell Cast (skell-cast-vst)

Cast followed Separator in the non-DeEsser rotation. It was selected because the actual latest baseline artifact contained a confirmed strict-metadata packaging defect and had no provenance/checksum manifest or pluginval gate. Skell Maw's newer exact-head run #44007318584 passed Windows compile, all seven pluginval strictness-5 checks and upload (artifact #14295408141), so its earlier program-list CI failure is no longer the highest unresolved packaging blocker. Cast's old artifact remains a valid binary baseline but not a strict, reproducible preview package. During Cast's own source review, `getProgramName(0)` was also found to return empty while one program is advertised; PR #4 fixes that with the host-visible name `Default`. The current global sharing source default is OFF, and PR #4 preserves that opt-in behavior.

- Draft PR #4: https://github.com/skellyruno/skell-cast-vst/pull/4
- Branch: `release/cast-vst3-manifest-20261116b`
- Commit: `1edd855d8565e7354a068339a53e2dd95423201e`
- Added isolated `packaging/verify_vst3_package.py` and 10 standard-library tests; hardened `scripts/Package-Windows.ps1`; added strictness-5 pluginval and PR-only concurrency cancellation; documented the preserved baseline and remaining release gates.
- Latest exact-head run #44021776458 is pending at Windows CMake configure. No new Cast build or downloadable artifact is claimed yet.
- Quick4 was not run: outbound GitHub DNS failed in the current container, so JUCE 8.0.17-security and the local Quick4 renderer could not be retrieved. No UI or DSP source was changed.

### Other candidate status

- Skell Maw PR #3 exact-head run #44007318584 passed and artifact #14295408141 was independently inspected: seven flat Windows x64 VST3 bundles, AMD64 PE32+, strict JSON, 14 unique CIDs and all 16 checksums matched. FL Studio and commercial gates remain open.
- Skell Cast's prior PR #2 and PR #1 remain separate drafts; PR #4 does not edit their branches or Source files.
- A first draft PR #3 was closed unmerged after its `tools/` path caused the unrelated SkellCore plugin-generator workflow to run and fail on the repository-specific class-name assertion. The release changes were relocated under `packaging/` in PR #4, so the final PR does not change `tools/` or `SkellCore/`. The failure is recorded above, not represented as a Cast DSP or Windows build failure.
- DeEsser remains parked.

### Next rotation

The next run must select a different non-DeEsser project. Stop/StopDial is now the leading candidate because exact-head Windows run #43936906930 failed pluginval strictness 5 on an unnamed program while compile, CTest and package staging passed. Recheck PR #3 branch ownership; do not edit that branch concurrently, and use a separate focused branch if unclaimed. Skell Necromancer is the alternate neglected candidate; its existing PR #1 has a successful Windows build but no downloadable Actions artifact was present. Do not return immediately to Cast unless its exact-head run reveals a critical regression.


## Release & Launch checkpoint 17 — 2026-11-17 01:06 EST

### Selected project: Skell Stop / StopDial

StopDial followed the previous Maw run. The exact-head Windows failure in PR #3 was a concrete release blocker: pluginval strictness 5 reported `Programlist 000->Program 000: has no name` after the Windows VST3 build, CTest, package verifier and bundle staging had all passed. The previous release run's source inspection showed `getNumPrograms()` returned one while `getProgramName(0)` returned an empty string. StopDial was therefore selected ahead of routine feature work; the PR branch had not changed since its prior failed run and no other automation reported ownership.

### Source and release changes

- Commit `a309cbe48a3f28a7e038f3f00ed4cd18d52f437f`: `getProgramName(0)` now returns `Default`, while retaining the existing one-program count.
- Commit `71cf773369bcb79333fd6fad4e00d4f3273ad9c8`: JUCE host regression assertion checks one program and a non-empty program name.
- Commit `381038d37b429813a9c629650ce765f9d184444f`: package manifest now records both the exact checked-out build commit (`source_commit`) and PR branch head (`pr_head_commit`). This is important because GitHub PR workflows build a synthetic merge commit, not just the branch head.
- No DSP, UI, parameter IDs, preset state, program count or saved-state keys changed. PR #3 remains draft.

### Verification

- Exact-head PR run #44026943821 on branch head `71cf773369bcb79333fd6fad4e00d4f3273ad9c8`: Windows Release VST3 build, JUCE DSP/host CTest, fail-closed package verifier, one-bundle staging, pluginval strictness 5, actual JUCE editor capture and artifact upload all passed; Linux sanitizer DSP passed.
- Artifact #14304221188 independently passed ZIP CRC, bundle layout, metadata identity/version, AMD64 PE32+, binary SHA-256 and two-class-ID checks. It is a private preview, not a public release.
- The exact-head PR artifact's `source_commit` is the synthetic merge SHA `dc58421734c8681763761e95db69d9858777a525`, which is the commit actually built; GitHub run metadata identifies the PR head separately. The new `pr_head_commit` field makes that distinction self-contained in the manifest.
- Latest exact-head provenance run #44028239371: Linux sanitizer DSP passed; Windows configure passed and the VST3 build is in progress at this checkpoint. No artifact from commit `381038d` is claimed yet.
- Actual JUCE UI screenshots at 435×535, 725×892 and 1087×1338 were inspected. Before/after source-fix captures were pixel-identical; no clipping or overlap was visible. The editor source was not changed.
- Local JUCE 8.0.12 clone/Quick4 restoration was attempted, but outbound GitHub DNS resolution failed in this container. Current-head local Quick4 and FL Studio checks remain unverified.

### Cross-automation ownership check

- Preset Audit advanced Alchemist and reported 41/41 Skell Preset tests passed; Factory 52 remains experimental, and EQ PR #9 has the valid package path while PR #10's artifact metadata/program-name defects remain flagged.
- Ecosystem Development advanced SkellForge PR #15 and SkellCore PR #41; Skell Delay PR #7 passed its exact-head cross-platform workflow. No shared branch was edited.
- Websites Development completed Skelly Creative V87; Artist V86 and Preset Showcase V24 remain separate. No deployment or DNS action.
- Nightly Blueprint's prior Maw program-list finding is resolved by the previous run's verified seven-plugin package; no DeEsser work was performed.

### Next rotation

Next candidate: **Skell Necromancer**. Existing draft PR #1 head `44e511247ac0331115dedb9c4464bc980dfb9694` passed Windows workflow #43806103369 through build, CTest, source/UI checks, independent loudness/true-peak references, actual JUCE screenshot and silent-rune capture, and package/upload steps. The Actions artifact list currently returns no retained artifact, so the next release run should use a separate release branch from that exact head, rebuild the Windows VST3, extend artifact retention, and independently inspect bundle identity, PE32+, pluginval, manifest and hashes. This rotates away from EQ and expands the non-DeEsser release portfolio.

No PR was merged, no public release or website deployment was performed, and no payment/DNS changes were made.


## Checkpoint 18 — 2026-11-17 01:20 EST

- **Selected: Skell EQ.** Preset Audit had confirmed that PR #10's A/B state test passed but its standalone artifact was not distributable (non-strict moduleinfo and empty VST3 program name); PR #9 already supplied a passing Windows VST3 release-hardening line. Draft PR #11 integrates both without changing DSP, UI, parameter IDs, presets or serialized-state schema. Exact-head Windows run #44030332461 was still building at the time of this ledger update; do not accept or distribute until the state CTest, pluginval, package and provenance gates pass.
- **StopDial completed the previous rotation step.** Exact-head run #44028239371 passed Windows build/CTest, verifier, pluginval strictness 5, Linux sanitizer DSP and artifact upload. Artifact #14303823607 was downloaded and independently inspected; its archive digest and embedded binary hash are recorded in the table above. FL Studio and commercial gates remain open.
- **Next selection: Skell Necromancer.** PR #1's exact-head Windows workflow #43806103369 passed, but no retained artifact is currently listed. Use a separate packaging branch from its exact head; preserve PR #1 and its approved UI/DSP work.
- DeEsser remains parked. Maw, StopDial and EQ are three distinct non-DeEsser release-engineering projects in the current rotation; continue to Necromancer next.


### Checkpoint 18 validation follow-up — 2026-11-17 01:33 EST

- Skell EQ exact-head Windows run #44030332461 is now **SUCCESS**. CTest output confirms 4/4: `SkellyDspSmoke`, `SkellyLinearPhaseTest`, `SkellyLinearReferenceTest`, and `SkellyEQStateRoundtrip`. pluginval reports `SUCCESS` at strictness 5.
- Artifact #14305256971 was downloaded and independently inspected. It contains exactly four files: one VST3 bundle, strict moduleinfo, build-info and SHA256SUMS. All checksums match; no Standalone or duplicate bundle. Archive digest and binary digest are recorded in the EQ row.
- Quick4 persistent DevKit `Skell_Quick4_Persistent_DevKit.zip` was materialized from `/skellworld/Quick4` and restored to `/mnt/data/skell-quick4`. JUCE 8.0.12 and pinned SkellCore source are present. EQ still needs a current local source checkout, an opt-in renderer target/router entry, and missing Linux GUI/audio development packages; the kit's offline `debs/` directory is empty. No Quick4 EQ capture is claimed.
- StopDial's current-head JUCE UI artifact #14304575936 was also downloaded and inspected at 435×535, 725×892 and 1087×1338; no visible clipping/overlap was found.


## Checkpoint 19 — 2026-11-17 01:55 EST

- **Selected: Skell Necromancer (skell-necromancer-vst).** The previous release checkpoint explicitly identified it as the next candidate: PR #1's Windows build and actual JUCE UI checks passed, but its one-day Actions artifact was no longer retrievable. This was a concrete distribution blocker, and the repository had no active editing branch from the other current automation results. Skell Maw was not selected because Ecosystem Development is actively working on its packaging PR #3; Skell Master remains in the Preset Audit's active sound-matching work; EQ was the immediately preceding release selection; DeEsser remains parked.
- Preserved PR #1 and exact source baseline `44e511247ac0331115dedb9c4464bc980dfb9694`. Created stacked draft PR #2 on `release/necromancer-vst3-package-retention-20261117`, commit `dff3e97087e1e82b1c2148a01b1bb37f0a175329`, targeting PR #1's branch so the diff contains only five packaging/docs files.
- New packager refuses ambiguous/multiple bundles and overwrites; verifies VST3 module metadata, unique class IDs, AMD64 PE headers, ZIP CRC and archived per-file SHA-256; emits source/run provenance, manifest and checksum sidecar. Windows VST3 artifact retention increases to 30 days; UI capture retention increases to 14 days. Distributable remains VST3-only; developer Standalone target is not included in the ZIP.
- Local regression suite: 9/9 passed with synthetic Windows PE64 VST3 bundle fixtures. Exact-head GitHub Windows runs #44035666459 (push) and #44035708103 (pull_request) both completed Configure and entered Release Build; both were still in progress at the time of this ledger update. The two events produced duplicate checks for the same SHA; no workflow-cancellation action was available, so neither run was cancelled. No new Windows artifact, pluginval result or real-host acceptance is claimed.
- Other automation evidence checked: Preset Audit advanced Alchemist and retained Factory 48 as champion (Factory 52 not promoted; 41/41 Skell Preset tests). Ecosystem Development advanced Maw package safety on PR #3 (Windows build still running). Websites advanced Preset Showcase V25 with 5/5 site suites; no deployment. The latest nightly blueprint still names Maw as a candidate, but Maw is owned by the active Ecosystem branch.
- **Next different candidate: Skell Afar.** Its release branch has several stacked drafts (#4–#9), including package-only PR #9, so first inspect exact-head CI and branch ownership. Do not modify any active Afar branch; use a new branch from its latest verified head only if the package blocker remains and no other automation owns that branch.
- DeEsser remains parked. No PR was merged, no public release, website deployment, DNS or payment action occurred.


## Checkpoint 20 — 2026-11-17 02:24 EST

- **Selected: Skell Key (skell-key-vst).** This follows the Skell EQ selection with a different plugin. It beat unrelated feature work because the existing Windows VST3 candidate already had a passing exact-head build and pluginval result, while independent inspection exposed a concrete distribution defect: JUCE emitted trailing commas in the actual nested `moduleinfo.json`, making the existing artifact invalid for strict JSON consumers. The fix could be isolated from DSP/UI and preserve the known-good binary.
- Downloaded and inspected baseline artifact #14295249929 from Windows run #44009458351. Archive SHA-256 `9074e154b4fffc0056e4002335994359209d6dccf69d41c000a52fc883fafa37`; one `Skell Key.vst3` bundle; AMD64 PE32+ module SHA-256 `71c973dcc346bd007c0724bffae9a08807408c983cef5a5112c457b5ac7b6f3c`; original moduleinfo SHA-256 `cba009b343db6ca26d9821a301e099907d8cf55ab00106714033ea6d704461a2`.
- Opened draft PR #10, branch `release/key-strict-moduleinfo-20261117`, commit `9b8940a7bcfc781a9f035f767bc35623f0fc78ac`, stacked on PR #9 head without editing its branch. Added the dependency-free normalizer, 12 regression tests, strict product/vendor/version/class/CID validation, source/staged hashes, a verification sidecar, no-overwrite staging, 30-day preview retention and README release-gate documentation. No DSP, UI, presets, parameter IDs, VST3 identity or host-state schema changed.
- Local normalizer tests: **12/12 passed** after correcting the false-positive assertion. The actual downloaded baseline moduleinfo passed normalization in a separate staged copy; source metadata hash remained unchanged, staged strict JSON parsed, and the original VST3 binary hash remained unchanged. Normalized staged moduleinfo SHA-256: `c61f9bd8438a618904a74efe261b3b9b08ea069cf8adc18b048f1a2ec3fc19d1`.
- Exact-head Windows run #44040263771 completed with Release VST3 build and tuning CTest passing, but the new test step failed on a false-positive regex that matched the intentional literal `,}` inside the quoted Description; strict JSON parsing had already passed. Corrected the assertion to compare parsed metadata objects in commit `0dbd76f256f6a91799e4ba2acf59ad3352dadcfe`. Exact-head Windows run #44041085916 has configured successfully and is in the Release VST3 build step; no new package/pluginval artifact is claimed yet.
- **Branch ownership exclusions:** Ecosystem Development is advancing Skell Maw PR #3, so its branch was not touched. Preset Audit is working on Skell Master Deuce and factory-state PRs, so those branches were not touched. Necromancer PR #2 has a recent exact-head package-test failure involving the root-level OFL font notice; its branch was not modified. Website V89 remains a separate workstream.
- Restored the persistent Quick4 DevKit locally; both bundled archives passed checksum verification, and JUCE 8.0.12 plus pinned SkellCore were restored to `/mnt/data/skell-quick4`. No Key UI change was made and no current-source Quick4 screenshot is claimed; the Key repository still needs its own renderer integration.
- **Next rotation:** Skell Necromancer after its PR #2 packaging branch is no longer being edited; if it remains owned/active, choose another under-served plugin rather than overlap. DeEsser remains parked. No merge, public release, website deployment, DNS, payment or production overwrite occurred.


## Release & Launch checkpoint 21 — 2026-11-17 04:12 EST

### Selected project: Modular FX Suite (skell-rack-vst)

Necromancer was the stated next candidate after EQ, but its packaging branch is already active in draft PR #2 (`release/necromancer-vst3-package-retention-20261117`) with a recent pluginval follow-up. I avoided overlapping that branch. Modular FX Suite had no open PRs/issues and a stale release path: its last successful Windows package run was October 12, while current CMake still built AU and Standalone alongside VST3 and pinned JUCE 8.0.0. This was a concrete Windows distribution-policy gap with no other automation branch owner.

- Draft PR #4: https://github.com/skellyruno/skell-rack-vst/pull/4
- Branch: `release/windows-vst3-only-juce812-20261117`
- Baseline main SHA: `273eba05567e6cf0f7ba02d9e819b5981d637d82`; latest branch head: `829de4513cedabcb9f841eb6a402d0d1e9b7e5f2`.
- CMake now pins JUCE 8.0.12, accepts a local JUCE_PATH, builds VST3 only and disables automatic post-build copying. Manufacturer/plugin codes and product identity are unchanged.
- New Windows release workflow runs on PR/main/manual, cancels only superseded PR checks, builds x64, tests the package verifier, packages one flat bundle, runs pluginval strictness 5 against the exact extracted package and retains preview artifacts for 30 days. The existing Guided Tour workflow was aligned with VST3-only and strict single-bundle checks, with PR-only concurrency.
- New packager verifies product/vendor/version, processor/controller classes, unique CIDs, AMD64 PE32+, safe archive paths, no Standalone executable/nested ZIP, CRC and file hashes; it normalizes JUCE trailing commas only in the packaged copy and refuses to overwrite existing outputs. Local tests: 10/10 passed.
- Preserved and independently inspected baseline artifact #11743164423 from run #38243301476. GitHub digest matched the downloaded archive SHA-256; its binary was AMD64 PE32+. Repackaging the real baseline locally passed CRC and strict moduleinfo parsing without modifying the original source bundle.
- Exact-head Windows run #44053093571 and current-head real-editor run #44053093565 are in progress. The superseded PR build run #44052919418 was cancelled automatically; the older Guided Tour run #44052919426 is still running because the available Actions interface has no direct cancel operation.
- Quick4 persistent kit was restored and its JUCE 8.0.12 source confirmed. Full local plugin build/renderer was not possible because outbound GitHub DNS is unavailable in the container. No local screenshot or Windows runtime claim is made.
- No DSP CTest suite or root product license is present. Vendor URL and support email remain blank. FL Studio, musical A/B, DSP edge cases/CPU, licensing, installer and SkellyHub rollback remain open.

### Cross-automation ownership check

- Ecosystem Development's latest Maw result supersedes the nightly review's older pluginval failure: the current Maw Windows release run passed its seven strictness-5 checks. Maw's packaging branch remains owned by Ecosystem Development; no Maw branch was edited.
- Preset Audit continues Deuce/Alchemist sound-matching and reports 41/41 Preset tests; Master branches remain owned by that automation.
- Websites Development continues Skelly Creative and Preset Showcase work; no deploy/DNS/payment action was performed.
- Nightly Blueprint's latest report still lists Maw as the release candidate, but its failure evidence predates the newer passing Maw run. The release rotation therefore used the unserved Modular FX Suite package gap.
- DeEsser remains parked.

### Next rotation

Next run should choose a different non-DeEsser plugin unless the Modular FX Suite exact-head build exposes a critical release regression. Do not edit the active Necromancer PR #2 branch. Recheck branch ownership and exact-head Actions before selecting the next product.

No PR was merged, no public release was published, no stable baseline was overwritten, and no website deployment, DNS or payment action occurred.

## Release & Launch checkpoint — 2026-11-17 08:04 EST

### Selected project: BPM Delay Calculator

Selected skellyruno/-bpmdelay-calculator-vst because its last source commit was 2026-10-16, it had no open issues or pull requests and only the main branch, and its Actions API showed zero recorded workflow runs. Its CMake target included Standalone alongside VST3; the existing workflow copied both into artifacts and allowed pluginval failure to pass with continue-on-error. This was a clear, isolated release-packaging gap and no other automation was editing this repository.

Implemented draft PR #1, branch release/windows-vst3-package-20261117, head 721db621c326cf1e8d3083edb2bfbb3a87288941:
- CMake now builds VST3 only; JUCE 8.0.15, version 1.1.0, manufacturer code Dlyc, product code Dcal and processor/state source remain unchanged.
- CI now includes pull_request, push and manual triggers, pinned pluginval 1.0.4 strictness 5 as a required gate, and Windows-first VST3 preview packaging.
- Added a deterministic package verifier/archiver with AMD64 PE32+ and Mach-O checks, moduleinfo presence, duplicate-module rejection, ZIP CRC, exact manifest coverage, per-file hashes, provenance, detached SHA-256 and refusal to overwrite an existing preview.
- Added five then two additional local regression cases. Final local result: 7/7 passed.
- No pre-existing VST3 binary or Actions artifact was found in this repository, so no backup is claimed. No DSP, UI, VST3 IDs, parameters or saved-state schema changed.

### Release gates
- Passed: local Python package tests 7/7.
- Pending / not reported: exact-head Windows/macOS CMake build, pluginval 1.0.4 and artifact upload. GitHub returned no workflow run and no commit statuses for head 721db621c326cf1e8d3083edb2bfbb3a87288941; do not call CI started or passed.
- Unverified: actual Windows/FL Studio load, host-tempo follow, audio pass-through, state/project save-reopen, Quick4 UI screenshots, visual interaction, audio A/B, target-hardware CPU/latency.
- Quick4 persistent kit was restored and checksum-verified. Its bundled JUCE is 8.0.12, while this repository pins 8.0.15; the Quick4 capture helper is not configured for this plugin. No mismatched build or screenshot was claimed.
- Commercial blocker: no owner-approved root LICENSE and vendor support/contact metadata remain absent. No signed installer, SkellyHub updater/rollback, storefront or pricing approval.

### Cross-automation results checked
- Skell Preset Quality Audit: Skell Master PR #14 and #15 exact-head Windows workflows #44048251784 and #44080300222 passed; current Deuce DSP/true-peak branches remain owned by that automation. Alchemist Factory 52 CPU optimization was rejected rather than promoted.
- Skell Ecosystem Development: Skell Delay PR #2 merged as 00b45315b79e194a3775b0f8a689d13ef93914a0; post-merge main run #44077183182 succeeded and uploaded Windows/Linux/macOS artifacts. The Windows artifact still needs independent archive inspection and FL Studio acceptance.
- Skelly Websites Development: V91 advanced Preset Showcase V26 with 6/6 regression suites passing; WebGL verification remains unverified. No deployment, DNS or payment changes.
- Skell Maw: PR #5 exact-head Windows run #44078225191 failed in the install-guide package test (KeyError: WINDOWS-VST3-INSTALL.txt); this is a follow-up release blocker, but it did not justify repeating the Maw selection after the required rotation. The verified baseline artifact from PR #3 remains separate and intact.
- DeEsser remains parked.

### Next rotation
Select a different non-DeEsser project after checking its current branches and exact-head CI. Do not repeat BPM Delay Calculator next run unless its new CI reveals a critical regression. Keep at least three distinct non-DeEsser substantive implementations within the six-run window; continue preserving draft-only status until real host acceptance and commercial gates are satisfied.

## Release & Launch checkpoint 22 — 2026-11-17 09:07 EST

### Selected project: Checkmate (skell-chess-vst)

Checkmate was selected after the BPM Delay Calculator rotation because its repository had no open PRs or issues, its last Windows main build was a usable but non-release-ready candidate, and its existing artifact included a Standalone EXE alongside the VST3. The workflow did not run pluginval, and the actual VST3 moduleinfo.json contained JUCE trailing commas. This was a concrete packaging gap with no active branch owner.

- Draft PR #8: https://github.com/skellyruno/skell-chess-vst/pull/8
- Branch: `release/windows-vst3-preview-package-20261117`
- Main baseline: `b21fe68482af69af0d1ca8bfa47e20f6bdd34518`
- PR head: `b0cd10d73bf6e70cab81047e4c5deefbe6160dc8` (two focused commits)
- Added a Windows PR/main/manual workflow with PR-only concurrency cancellation, CTest, 12 package tests, pluginval v1.0.4 strictness 5, separate current-build UI evidence, and a 30-day VST3-only preview artifact.
- The Standalone CMake target remains available for local development, but the downloadable artifact contains only Checkmate.vst3.
- Added a fail-closed package verifier for exact bundle inventory, x86_64-win module path, AMD64 PE32+, product/vendor/version, two VST3 class categories and unique class IDs. JUCE trailing commas are normalized only in the staged copy.
- Added build provenance, module SHA-256, per-file SHA256SUMS, preview-only notice and manual backup/rollback instructions.
- Local package regression tests: **12/12 passed**. Staging the real baseline artifact passed architecture, metadata, class-ID and checksum checks; no EXE was present in the staged package. The original artifact and source module were not modified.
- Baseline artifact #14100575125 was downloaded and independently inspected: 8,103,936-byte AMD64 PE32+ VST3 module, SHA-256 `a555a830f6d499e4362e69a4f88228b0fd803b3da3c2f1ed8800ab529240e995`; original archive SHA-256 `ba8023cfb249f3505221d5bb907e5e7318267b0c80a2dfb8098abbd504dc32e1`. The same main commit's UI evidence artifact #14100575117 was inspected; no obvious clipping/overlap was found and no UI source changed.
- Exact-head PR workflow #44099624708 passed CMake Configure and is in the Windows Release Build step. A branch-push run #44098832105 is also running from the initial base commit using the old workflow; it is not treated as evidence for the new package changes and was left untouched because it is a push/release-branch run, not a superseded PR run.
- Quick4 persistent kit was restored and checksum-verified; JUCE 8.0.12 source is present. The bundled capture helper supports Master/Preset only, and the container could not resolve github.com to fetch current Checkmate source. No fresh Checkmate Quick4 screenshot or local full plugin build is claimed.
- Commercial blockers remain: no root LICENSE/COPYING/NOTICE, blank vendor URL and support email, no signed installer/SkellyHub updater, and no FL Studio, MIDI routing, state recall, audio A/B or target-hardware CPU/latency acceptance.

### Cross-automation ownership check

- Preset Quality Audit's latest result advanced Skell Preset PR #58 with 11 explicit-null parser regression cases; exact-head portable CTest 32/32 passed, but the latest Windows build and package tests remain pending. Master PR #15's earlier Windows VST3 artifact was independently checked by that automation. No Preset-owned branch was edited.
- Ecosystem Development's latest result merged Skell Delay PR #2 as `00b45315b79e194a3775b0f8a689d13ef93914a0`; post-merge main CI #44077183182 passed. Skell Maw PR #5 has a new active exact-head Windows run #44096649781 after its package-guide parser correction; its branch is owned by the active release workstream and was not touched.
- Websites Development completed V91 with Preset Showcase V26 and 6/6 regression suites; WebGL remains unverified. No deploy, DNS or payment action.
- Nightly Blueprint's Maw failure evidence predates the passing PR #3 package baseline; the new PR #5 install-guide follow-up is active. No Maw branch was edited.
- DeEsser remains parked.

### Next rotation

Choose a different non-DeEsser project after checking current branch ownership and exact-head Actions. Do not repeat Checkmate next run unless its new Windows build exposes a critical regression. Continue rotating across at least three distinct non-DeEsser projects in the six-run window.

No PR was merged, no public release was published, no stable baseline was overwritten, and no website deployment, DNS or payment action occurred.


## Release & Launch checkpoint 23 — 2026-11-17 10:08 EST

### Selected project: Skell Stop / StopDial (skell-stop-vst)

StopDial was selected after Checkmate because PR #3's exact-head Windows VST3 build, JUCE DSP/host tests, package verifier, pluginval strictness 5, actual UI capture and artifact upload had all passed. The independently inspected artifact was already a usable VST3-only preview, but it had no end-user install/update/rollback helper or package-wide checksum list, and its preview retention was only seven days. This was a concrete final-mile distribution gap. Key's current package PR is green but its open accuracy issue requires unseen audio data; Fan's package workflow is already green; Cast has active real-time/persistence PRs. StopDial had no competing automation branch owner, and the new work is on a separate branch stacked above PR #3.

- Draft PR #4: https://github.com/skellyruno/skell-stop-vst/pull/4
- Branch: release/stopdial-safe-install-rollback-20261117
- Base: PR #3 branch release/stopdial-vst3-package-guard-20261116, head 381038d37b429813a9c629650ce765f9d184444f
- PR #4 head: ed92187596b37e7a49886b9f1843c76e35f2507a; three commits, six files changed.
- Added scripts/Install-StopDial.ps1: verifies package-wide SHA256SUMS, release manifest, moduleinfo product/version/class IDs, exactly one x86_64-win module, AMD64 PE32+ and bundle hashes. It supports WhatIf, idempotent installs, staged replacement, timestamped backup before update, post-install verification and explicit rollback. Rollback preserves the version being replaced in a new backup. It does not self-elevate, edit registry/DAW settings or run in the background.
- Added scripts/Test-Install-StopDial.ps1 and INSTALL-WINDOWS.txt; updated README and changelog. CI copies the helper/instructions into the VST3 artifact, writes SHA256SUMS for every package file, runs the PowerShell tests and retains preview/UI artifacts for 30 days.
- No DSP, UI, parameter IDs, APVTS state, presets, VST3 identity or source audio changed. No actual user-machine installation or rollback was performed.
- Baseline artifact #14303823607 was downloaded and independently inspected: archive SHA-256 2de54d9ffbf66bcbf7a6798dc76aa24cf47ea372187b0c7179e09c29611e01c3; one StopDial.vst3 bundle; module SHA-256 d28339f145baa5bb70b7f7ba34927a0f724277c7b5d9bc1f38e0c52e32ae5d59; module size 6,572,544 bytes; AMD64 PE32+. The artifact contains no Standalone EXE or nested ZIP. Manifest source commit and PR head were verified.
- UI artifact #14304575936 was downloaded and inspected at 435×535, 725×892 and 1087×1338. No obvious clipping/overlap was found; no UI source changed.
- Local container has no PowerShell runtime, so the new install/upgrade/rollback tests are not claimed as locally passed. Exact-head Windows push run #44110652422 is pending; intermediate commit run #44110409942 is still in progress and is not exact-head acceptance. No new package artifact exists yet.

### Release gates

- Passed on PR #3 baseline: Windows Release VST3 build, JUCE DSP/host CTest, 10 package tests, pluginval strictness 5, actual UI captures and independently inspected baseline ZIP/binary.
- Implemented but pending exact-head CI: installer WhatIf, fresh install, idempotent install, update with backup, rollback with pre-rollback backup, tampered-package rejection and binary-hash mismatch rejection (18 assertions).
- Unverified: FL Studio scan/load, project save/reopen, automation/preset recall, real audio A/B, target-hardware CPU/latency, physical Windows installation, SkellHub integration.
- Commercial blockers: root LICENSE/COPYING/NOTICE approval and vendor support email remain unresolved. The helper is a preview install utility, not a signed commercial installer or automatic updater.
- No merge, public release, website deployment, DNS, payment or production overwrite occurred.

### Cross-automation ownership check

- Preset Quality Audit's latest actual result advanced Alchemist in PR #58: reset all eight serialized macros on factory switch; portable CTest 32/32 passed, latest Windows build pending. No Preset branch was touched.
- Ecosystem Development's latest actual result fixed the Skell Maw PR #5 install-guide checksum parser; its new Windows validation run #44096649781 is active. Maw remains owned by that automation; no Maw branch was touched.
- Websites V91 completed Preset Showcase V26 with 6/6 regression suites; WebGL remains unverified. No website deployment, DNS or payment action.
- Nightly Blueprint's latest report predates the newest Maw package correction; it remains a reference, not a reason to repeat Maw.
- DeEsser remains parked.

### Next rotation

Next release run must select a different non-DeEsser plugin/project after checking fresh automation results and branch ownership. The six-run portfolio now has substantive release work across BPM Delay Calculator, Checkmate and StopDial; continue widening coverage rather than returning to one plugin. Keep every draft unmerged until real host acceptance and commercial gates are complete.


## Release & Launch checkpoint 24 — 2026-11-17 15:46 EST

### Selected project: SkellyChoir — urgent CI regression follow-up

The prior run selected SkellyChoir and restored its direct Windows VST3 preview package workflow in draft PR #8. Its exact-head run #44163286082 then exposed a new release-blocking CMake configure regression: the Windows checkout uses GitHub's synthetic PR merge commit at default depth 1, while CMakeLists.txt resolves the PR head SHA from SOURCE_COMMIT using `git show -s --format=%ct`. The head object was absent (`fatal: bad object d8db48ba400fbbfc8a4ac828ad41aaba6f71d454`). The native DSP/state/UI-stub suite and all 14 package-verifier tests passed; Windows configure failed, so no package was built or uploaded.

This repeat selection is limited to repairing that newly exposed release regression; it does not reopen unrelated Choir feature work.

- Parent draft PR #8: https://github.com/skellyruno/skell-choir-vst/pull/8
- Follow-up draft PR #9: https://github.com/skellyruno/skell-choir-vst/pull/9
- Follow-up branch: `fix/choir-fetch-source-commit-for-reproducible-build-20261117`
- Follow-up commit: `3e6634fc5c8655bc620a0907c936679a138bd4bc`
- Only `.github/workflows/build.yml` changed: the Windows checkout now uses `fetch-depth: 0`, ensuring the exact PR head commit is available while still building the PR merge ref. Native-test checkout remains shallow. Package staging, AMD64 PE32+ verification, pluginval strictness 5, provenance ordering and PR-only cancellation are unchanged.
- Exact-head workflow run #44173099588 is queued/in progress. No build, artifact, pluginval result or host acceptance is claimed until it completes.
- Existing baseline artifact #14279527660 and its previously recorded hashes remain preserved; no baseline file or product binary was overwritten.

### Cross-automation ownership and latest evidence

- **Skell Maw:** Ecosystem-owned draft PR #8, head `8d5bf055270a429dbde6776136431a8bac95a28e`; exact-head Windows run #44162139895 failed at “Test private-preview install and rollback” after the VST3 compilation and 10 package-verifier tests passed. The failure reports that the install test did not accept the seven staged bundle names. The branch remains owned by Ecosystem Development and was not edited.
- **Skell Necromancer:** draft PR #3, head `b55e94d719d32463d40528762274299b5fc19ee8`; exact-head run #44056313880 succeeded: Windows Release VST3 build, CTest 8/8, package-verifier 17/17, pluginval strictness 5, and UI capture/inspection. FL Studio, musical A/B and commercial metadata remain unverified.
- **Skell Silence:** draft PR #17, head `34494b2496c85c65fe91c8bca5b0f4612c95a1ac`; run #44135077869 passed portable DSP and Windows build jobs. Manual install/rollback and FL Studio remain unverified.
- **Skell Delay:** Ecosystem PR #2 is merged. The post-merge main result #44077183182 is reported as successful by the latest Ecosystem update; this PR-only commit-run lookup did not return it, so its artifact inspection remains separate.
- **Skell Preset:** Preset-owned draft PR #46, head `494e7ce8a0a3e2186aa344ed3a0bd2db3a63d4ec`; run #43878988985 passed portable and Windows VST3 jobs. No Preset branch was touched.
- **Websites / Studio:** latest reported website v93 completed 30/30 Creative tests and 14/14 browser tests; Skell Studio's latest reported Windows build and screenshot run passed. These are cross-automation reports, not re-run in this release execution. No website deployment, DNS or payment action occurred.
- DeEsser remains parked; its routine unresolved editor-lifecycle work does not override the non-DeEsser release rotation.

### Next distinct project: SkellyTune Mini

Mini remains the next selection after this Choir regression repair. Its current draft PR #7 head `0da2b7481aa9c3806b568bc13b410518b1f96e95` has a proven Windows packaging failure in run #43806470929: the VST3 build and editor startup/layout/paint/audio-callback smoke passed, and the portable DSP run #43806470938 passed, but the package step compared a PowerShell single-quoted suffix containing doubled literal backslashes with a real Windows path containing single separators. The next run should correct this using normalized path components / `[IO.Path]::Combine`, add a regression for the expected module location, and re-run the exact-head Windows package gate. Do not edit the existing PR #7 branch; use a focused follow-up branch stacked on it.

No merge, public release, production overwrite, website deployment, DNS change or payment action occurred.


## Release & Launch checkpoint 25 — 2026-11-17 16:45 EST

### Selected project: SkellyTune Mini — Windows VST3 packaging recovery

Mini was selected because the prior run had already proven a concrete release-blocking packaging defect after the Windows VST3 build and editor smoke succeeded. This was a distinct non-DeEsser plugin and avoided overlapping active source branches.

- Parent draft PR #7: https://github.com/skellyruno/skelltune-mini/pull/7
- Parent head: `0da2b7481aa9c3806b568bc13b410518b1f96e95`
- Failure run #43806470929: Windows VST3 build and GUI smoke passed (processor startup, editor construction, 432x414 / 720x690 / 1008x966 layouts, paint, parameter updates, audio callback, and hub-free SkellKey -> Mini transfer); packaging failed at the module-path suffix comparison. The actual module path contained normal Windows separators, but the expected PowerShell single-quoted string contained doubled literal backslashes.
- Portable DSP run #43806470938 passed.
- Follow-up draft PR #8: https://github.com/skellyruno/skelltune-mini/pull/8
- Branch: `fix/mini-normalize-vst3-module-path-20261117`
- Commit: `e7317a993f7b2277f5376eb8e763e7808d898aab`
- Only `.github/workflows/build.yml` changed. The check now uses `[System.IO.Path]::GetRelativePath` and `[System.IO.Path]::Combine`, with regression probes accepting the exact Windows module layout and rejecting a Linux architecture directory or wrong module name.
- Exact-head Windows run #44183282064 started; build job was in progress at the checkpoint. No artifact, pluginval pass or new package is claimed yet.
- PR #7's branch was not modified. No DSP/UI/preset/parameter/state changes, merge, public release or production overwrite occurred.

### Choir follow-up completed and independently verified

The previous Choir CI recovery is now complete:
- Draft PR #9 commit `3e6634fc5c8655bc620a0907c936679a138bd4bc`; exact-head run #44173099588 completed with both Windows build and native-tests jobs successful.
- Artifact #14369236040 was downloaded and independently inspected. ZIP CRC passed; the archive contains exactly four expected files and one Windows VST3 module. The module is AMD64 PE32+, 10,593,280 bytes. Strict moduleinfo JSON has two unique class IDs. All three SHA256SUMS entries match.
- Archive SHA-256: `9eea66b10fdf06a053d0dca2b9638c7834ca108001b2407c83d0b1ca5fc62495`.
- Binary SHA-256: `46d34556e31f3ff3231ec48ed7eacbbe3403125225db93cecb271cb34eead8f4`.
- Manifest records pluginval strictness 5 passed and source commit matching PR #9. The 0.9.0 artifact remains PREVIEW_ONLY; FL Studio, Quick4/current-head visual acceptance, A/B, target-hardware CPU/latency, attribution, owner-approved license, vendor URL and support email remain open.

### Cross-automation ownership and latest results

- **Preset Quality Audit:** Alchemist same-take native A/B rendered across five factory candidates; no factory was promoted. Factory 52 had best measured spectral/envelope error but would exceed the estimated true-peak ceiling if loudness-matched. EQ Windows build was reported verified, with new Windows CI pending. No Preset branch was touched.
- **Ecosystem Development:** Maw PR #8 has a corrected install-guide checksum parser; Windows validation #44162139895 remains in progress. Necromancer PR #3 exact-head run #44056313880 passed Windows VST3, CTest 8/8, package tests 17/17 and pluginval 5. Silence PR #17 run #44135077869 passed portable DSP and Windows build. Delay PR #2 is merged; run #44077183182 passed Windows, Linux and macOS jobs. Project Hub PR #14 Windows check passed. No competing branch was edited.
- **Websites:** latest V94 advanced Preset Showcase V27; 92/92 regression tests and 18/18 HTTP checks passed. No deploy, DNS or payment action.
- **DeEsser:** remains parked; no critical emergency justified overriding the non-DeEsser rotation.

### Next rotation

Next run must select a different plugin/project, not Mini or Choir. A reasonable candidate is **Skell Delay** for independent inspection of its merged Windows VST3 artifact (PR #2 / run #43909229094 artifact #14246574699) and confirmation of release metadata/host blockers, after checking fresh branch ownership. Other candidate projects should be compared against current exact-head CI and actual artifact availability. Continue the non-DeEsser rotation; no unverified merge or public release.


Quick4 environment note for checkpoint 25: the persistent `Skell_Quick4_Persistent_DevKit.zip` was retrieved from `/skellworld/Quick4`, checksum-manifest verified, and restored to `/mnt/data/skell-quick4`. It contains JUCE 8.0.12 and the pinned SkellCore source. The bundled `build_capture.py` supports only `master` and `preset`, not Mini; the container also lacks `ft2build.h`, X11 extension and ALSA development packages. Therefore no Mini Quick4 binary or screenshots were produced, and no stale renderer/screenshots were substituted.


## Release & Launch checkpoint 26 — 2026-11-17

### Selected project: Skell Afar — safe private-preview installation and rollback

Afar was selected over the other candidates because its parent Windows VST3 branch already had a successful exact-head build, package validation and pluginval strictness 5, plus a real JUCE editor capture artifact. The concrete remaining distribution gap was that users had a raw preview bundle but no verified per-user install/update/rollback path or complete release notes/attribution in the downloadable package. No Afar issues were open. SkellForge and Maw were left to the active Ecosystem Development branches; Master/Preset work was left to Preset Quality Audit; Mini and Choir were not reselected as the primary project in this run. DeEsser remains parked.

- Parent PR #9 / tested head: https://github.com/skellyruno/skell-afar-vst/pull/9 / c8215b82ab0f8b09036cd2a45967f6a80028037c.
- New draft PR #10: https://github.com/skellyruno/skell-afar-vst/pull/10.
- Branch: release/afar-safe-install-rollback-20261117; head bba78ac40d76e3b82d91b300901f58f3c54f4c13; stacked on PR #9's branch. PR #9 and its artifact were not modified.
- Code/package changes: checksum-verified PowerShell install/update/rollback; backup verification before replacement; same-volume staged install; failure restoration; 17 Windows regression assertions; user install instructions; v0.6.0 private-preview release notes; scoped SkellCore/SkellyTune MIT notice; updated VST3-only README and artifact packaging workflow.
- Commits on the follow-up branch include installer/test/docs/workflow/README changes; final head is recorded above after the preview-marker correction. No C++ DSP, UI, preset, parameter ID, automation ID or host-state code changed.
- Exact-head Windows run #44195359767 and real-SkellCore ASan/UBSan run #44195359853 were in progress at ledger update. No exact-head artifact or test pass is claimed until they complete. Local PowerShell is unavailable.
- Parent artifact #14296195883 remains preserved (archive digest 91777b84aad024b8015b7b510ffb53c3414aee74d2091d0adccbc955ac0d8f80). Existing real JUCE UI artifact #14295551951 was inspected across default/compact/large, Simple/Pro and tour views; no visible clipping/overlap was found. The Quick4 kit was restored with JUCE 8.0.12, but its capture helper supports only Master/Preset and the current container could not resolve github.com to fetch a local Afar checkout. No new local UI capture is claimed.
- SkellCore issue #32 remains open: measured inter-sample overshoot is about +0.25 dB above the -1 dBFS ceiling. The preview must not claim true-peak certification or a mastering guarantee.

### Newly confirmed Mini packaging blocker

Mini's exact-head path-fix run #44183282064 succeeded, but artifact #14372274632 is not release-ready. Independent download showed one nested ZIP, one AMD64 PE32+ module and no duplicate module, but moduleinfo.json fails strict JSON because of trailing commas; no build-info or SHA256SUMS sidecars are present and no pluginval strictness 5 run was part of that workflow. This is a new concrete package-level blocker, not a reason to revisit DeEsser.

### Cross-automation ownership and next rotation

The latest GitHub checks show active work in SkellForge and Maw under Ecosystem Development, and Preset/Master work under Preset Quality Audit; those branches were not edited. Website development remains separate; no deployment, DNS, payment or public release action occurred. The previous release coverage entries for Choir, Mini and Afar provide substantive work across three distinct non-DeEsser plugins.

**Next run selection: SkellyTune Mini**, a different plugin from Afar. Fix the strict metadata/provenance/hash packaging gap on a focused follow-up branch, preserve the current build/artifact as baseline, run pluginval strictness 5 and independently inspect the resulting flat VST3 package. Do not change DSP/UI or merge until the exact-head package and host gates are verified.


### Afar Windows installer test correction — 2026-11-17

The first exact-head Windows run #44195359767 completed configure, Release VST3 compilation, all 12 Windows CTests, all six package-validator tests, bundle staging and tool-copy/checksum generation. The 17-assertion install test stopped at installer line 109 because PREVIEW-ONLY.txt did not contain the exact preview-only marker required by the package verifier. The workflow was corrected in commit 8d208c5f625d12ebe9e312bb38e47ce17a35fb32 to write an explicit release_status: preview-only marker. The first run's pluginval and artifact-upload steps were skipped as designed. The new exact-head run is pending; do not mark the install/update/rollback tests passed until the new run completes.


## Release & Launch checkpoint 27 — 2026-11-17 (Afar installer CI regression repair)

### Selected project: Skell Afar — urgent install/update/rollback CI follow-up

The previous Afar release run had corrected the preview-status marker, but the new exact-head Windows run exposed a second release-blocking failure in the install test. I treated this as the allowed urgent exception to the rotation rule rather than leaving a broken installer branch behind. This is a test/runtime failure in the new installer path, not a DSP or UI regression.

- PR #10: https://github.com/skellyruno/skell-afar-vst/pull/10
- Branch: `release/afar-safe-install-rollback-20261117`
- Previous head: `8d208c5f625d12ebe9e312bb38e47ce17a35fb32`
- New commit: `642747244270380dfe09bc3d9f8673ab73779b7d` — `fix: keep ShouldProcess in installer script scope`
- Failure evidence: Windows run #44196506023 passed configure, Release VST3 compilation, Windows CTest 12/12, six package-validator tests, staging and installer-tool copy. It failed the fresh-install test with PowerShell 7: `Exception calling "ShouldProcess" with "2" argument(s): "Object reference not set to an instance of an object."`
- Root cause: the script passed its `$PSCmdlet` object into a nested helper function and called `ShouldProcess` there. The command runtime was detached in that helper scope.
- Fix: call `ShouldProcess` in the advanced script scope, pass only its Boolean result to the install/rollback helpers, and preserve WhatIf/idempotent behavior. The test harness explicitly disables confirmation for non-interactive mutation tests.
- Exact-head Windows run #44203361778 completed successfully: Release VST3 compile, Windows CTest 12/12, six package-validator tests, staging, 17 installer assertions, pluginval v2.0.0-beta3 strictness 5 and artifact upload all passed. Real-SkellCore ASan/UBSan run #44203361746 passed CTest 12/12. Artifact #14382996753 (6,120,924 bytes) has SHA-256 `e243c86eac7b9efcb91a8fcd2e76fc76753b7f1af7dc6b85f7e62fdfc3555ab9`; [exact workflow artifact](https://github.com/skellyruno/skell-afar-vst/actions/runs/44203361778/artifacts/14382996753). Independent inspection confirmed one AMD64 PE32+ VST3 module, strict JSON, two unique class IDs, ZIP CRC and complete package/tool checksums. The artifact is accessible through a public repository Actions run, not private storage; no live release was published.
- Parent artifact #14296195883 remains preserved as the known-good VST3 baseline; archive SHA-256 `91777b84aad024b8015b7b510ffb53c3414aee74d2091d0adccbc955ac0d8f80`; binary SHA-256 `141df41650f510b5cbf49210f34c8a359fa9049481f5686fb397336a5275340f`.
- No DSP, UI, preset, parameter ID, automation ID or project-state code changed. The existing real JUCE Guided Tour capture artifact #14295551951 remains the visual baseline. The persistent Quick4 kit was restored from the ChatGPT Library; both embedded bundles passed checksum verification and JUCE 8.0.12/SkellCore are present. No new screenshot is claimed because the UI did not change. A fresh local Afar renderer was not built: the current source checkout is unavailable because github.com DNS fails, and required Linux FreeType/XRandR/ALSA development headers are absent (apt update timed out).

### Rotation exception and next selection

SkellyTune Mini remains the next distinct plugin. Its PR #8 head `e7317a993f7b2277f5376eb8e763e7808d898aab` passed the path-fix Windows run #44183282064, but independent inspection of artifact #14372274632 found a nested ZIP, invalid strict JSON from JUCE trailing commas, no build provenance, no SHA256SUMS and no pluginval strictness-5 result. That is still the next package implementation target after the urgent Afar installer repair.

### Cross-automation ownership check

- **Preset Quality Audit:** latest completed run corrected the Deuce master-bus A/B comparison; no factory was promoted. Updated Master renderer CI remains pending. No Preset/Master branch was edited.
- **Ecosystem Development:** latest completed result changed SkellForge PR #29 and Skell Maw PR #8; the newest Ecosystem run is active on those areas. No concurrent branch was edited.
- **Websites Development:** V96 completed with 139/139 regression tests and 21/21 HTTP checks; GPU WebGL remains unverified. No website deployment, DNS or payment action occurred.
- **Nightly blueprints:** the latest review still identifies Maw as a release candidate; its active Ecosystem branch owns that work. DeEsser remains parked.

No PR was merged, no live release was published, and no website/DNS/payment action occurred.


## Release & Launch checkpoint 28 — 2026-11-17 (SkellyTune Mini packaging implementation)

### Selected project: SkellyTune Mini — flat Windows VST3 preview recovery

Mini was selected because its exact-head path-fix build had passed, but the real downloadable artifact still failed release packaging. The Windows build was successful on PR #8 run #44183282064; independent inspection of artifact #14372274632 found that the Actions ZIP contained a second ZIP, its moduleinfo.json was not strict JSON, and it had no build provenance, SHA256SUMS, license notices or pluginval strictness-5 evidence. This is a concrete release blocker, not a feature request. Maw was left to the active Ecosystem branch; Master/Preset were left to Preset Quality Audit; Afar's previous run is complete. DeEsser remains parked.

- Parent PR #8: https://github.com/skellyruno/skelltune-mini/pull/8; head `e7317a993f7b2277f5376eb8e763e7808d898aab`.
- New draft PR #9: https://github.com/skellyruno/skelltune-mini/pull/9.
- Branch: `release/mini-flat-package-strict-metadata-20261117`; current head `872b6b66a94335593ac9cb6f7f79ae019813eb70`, one coherent commit stacked on PR #8.
- Implementation: strict JUCE moduleinfo trailing-comma normalization on a staged copy only; product/version/vendor/two required VST3 class categories/unique 32-character IDs validated; seven dependency-free Python unit tests; direct bundle-directory artifact upload; build provenance distinguishes PR head SHA from synthetic CI checkout SHA and records resolved JUCE/SkellCore revisions; SHA256SUMS generation and recomputation; project/JUCE/SkellCore/HelixTune notices; pluginval v2.0.0-beta3 pinned by its upstream asset digest and run at strictness 5.
- No DSP, UI, presets, VST3 identity, parameter IDs, automation IDs or host-state code changed. PRs #7 and #8 remain open/draft; no merge or public release occurred.

### Validation status at ledger update

- Local metadata-normalizer tests: 7/7 passed.
- Real baseline artifact moduleinfo.json: normalized and accepted by strict Python JSON parsing; name/version/vendor and both existing class IDs validated.
- Real baseline binary: 6,571,008 bytes; AMD64 PE32+; one VST3 module; SHA-256 `ea99c5a2ac7a9d7c1af9bd8ba0e2df6c455dc3921bc4c87a9443180450be1a39`.
- Exact-head portable DSP run #44212653651 passed all workflow steps, including the saved real-vocal render/analysis.
- Windows run #44212653636 passed setup, metadata tests, configure, Release VST3 compile, editor startup smoke and package staging, but pluginval failed the VST3 validator because the sole program had an empty name; artifact upload was skipped. Fix commit 872b6b66 returns Default and adds a smoke assertion. New exact-head Windows run #44213523212 and portable DSP run #44213523208 are in progress; no strictness-5 pass or new artifact is claimed.
- Superseded Windows PR run #44212386851 was automatically cancelled after the branch head changed; only PR-scoped CI was superseded. Main and manual workflows were not cancelled.
- Quick4 persistent kit restored and checksum-verified; JUCE 8.0.12 and SkellCore are present. The current Quick4 capture helper only supports Master/Preset, Mini source could not be cloned because github.com DNS resolution is unavailable, and Linux FreeType/XRandR/ALSA development headers are missing. No current Mini screenshots are claimed.
- FL Studio scan/load, musical A/B, preset/state/automation recall, target-hardware CPU/latency and commercial JUCE license entitlement remain UNVERIFIED. The new preview artifact is hosted in a public repository Actions run, not private storage.

### Cross-automation ownership check

- **Ecosystem Development:** latest actual result has SkellCore WorldLink PR #42 under test, SkellForge PR #29 green, and Maw PR #8 under active work. No competing branch was edited.
- **Preset Quality Audit:** latest actual result reports Deuce master-bus verification advanced, Windows Master build passed, 53 factory presets audited and a private WAV render still pending; no experimental factory preset was promoted. No Master/Preset branch was edited.
- **Websites Development:** latest actual result V97 implemented Skell Preset Skull Showcase V28, with 99/99 regression tests and 26/26 HTTP checks; no deployment, DNS or payment action occurred.
- **Nightly Blueprint Review:** Maw remains the selected release candidate with a Windows plugin-validation failure; active Ecosystem ownership was respected.
- **DeEsser:** remains parked; no critical security or regression emergency justified an exception.

### Next release step

Finish the exact-head Mini Windows build, inspect its new artifact and pluginval strictness-5 output, then perform real FL Studio/Quick4/audio/state/CPU acceptance and obtain licensing approval. The next primary selection after Mini must be a different non-DeEsser project, after checking current branch ownership; do not repeat Mini absent a genuinely urgent new regression.

No merge, commercial release, website deployment, DNS change or payment action occurred.

### Mini pluginval root-cause follow-up — 2026-11-17

- Windows run #44212653636 proved the new packaging path works through staging: build, editor startup/layout/paint/SkellKey IPC smoke, strict metadata normalization, PE32+ AMD64 check, license copy, source/dependency provenance and SHA256SUMS recomputation all passed.
- Pinned pluginval v2.0.0-beta3 strictness 5 ran. Its scan, open, plugin info, editor, audio processing at 44.1/48/96 kHz and 64–1024 blocks, state, automation, editor automation, bus and DPI checks completed. The only reported failing subtest was the bundled VST3 validator: `Programlist 000->Program 000: has no name!!!`.
- Root cause confirmed in `Source/PluginProcessor.h`: `getNumPrograms()` returned 1 but `getProgramName(int)` returned an empty string. Fix commit `872b6b66a94335593ac9cb6f7f79ae019813eb70` returns `Default` for index 0 and adds a GUI-smoke assertion for a non-empty default program name. Program count, IDs, state and DSP are unchanged.
- Artifact upload was skipped after the validator failure; no invalid new artifact was published. Portable DSP rerun #44213523208 passed all steps, including regression, gain/subsonic diagnostics, CPU diagnostic and saved real-singer render. Exact-head Windows run #44213523212 passed CMake configure and Release VST3 compilation; editor startup smoke is in progress. The strictness-5 gate remains open until the Windows rerun passes.


### Checkpoint 29 — Skell Key install/update/rollback

- Selected Skell Key after Mini as the next distinct non-DeEsser product. The prior Skell Key release chain had a fully passing Windows build and a real artifact that could be independently inspected; no Preset, Ecosystem, Website or Nightly automation reported active edits to the Key branch.
- New draft PR #11: https://github.com/skellyruno/skell-key-vst/pull/11. Commit `ebb85f70b50bc0fcf6bc3602a4ed9fa7e11de344`; four commits stacked on PR #10: initial implementation `ebb85f7`, checksum-array return fix `db6e76c`, fixture-copy fix `0951384`, and explicit result-object return fix `fb24ee1`. It adds `Install-Skell-Key.ps1`, a PowerShell install/update/rollback harness, a Windows install guide, release notes, third-party/license-status notice, full package checksums and build provenance. Existing plugin binary, DSP, UI, preset bank, VST3 identity, parameter IDs, automation IDs and state schema are untouched.
- Protected package evidence: artifact #14308894745 / run #44041085916; archive SHA-256 `7d734fa1726896398e4abf6ca75ae7c525c396ed8e111a47f529e996b8d49668`; module SHA-256 `45cf2a246275a2e19c105af35fe7bff7ef283845af3dab2490a56e37bd393662`; strict moduleinfo and two expected unique class IDs verified after download. This artifact remains a public Actions preview, not private storage or a commercial release.
- Intermediate PR-only run #44221356391 was safely cancelled after the branch correction; main and manual CI were not cancelled. Runs #44221356391 and #44221642663 were superseded by PR-only concurrency after source corrections; main/manual CI were not cancelled. Exact-head run #44222152036 passed CMake configure and is compiling Release VST3. No installer assertion pass, pluginval result or PR #11 artifact is claimed until the run completes. The container has no PowerShell runtime, so the PowerShell suite is delegated to the actual Windows runner.
- Commercial release remains blocked on FL Studio scan/load, two-plugin Key/Mini session sync, musical A/B, state/project recall, target-hardware CPU/latency, Quick4 UI inspection, product/dependency license approval and vendor/support contact.
- Next selection must be a different non-DeEsser plugin after branch-ownership checks. Do not repeat Key unless a critical new regression appears.
- No merge, public GitHub Release, production install, website deployment, DNS change or payment action occurred.


## Release & Launch checkpoint 30 — 2026-11-17 (Skell Pad / ScratchPad strict VST3 package gate)

### Selected project and rationale

Selected **Skell Pad / ScratchPad (skell-scratch-vst)** after checking the latest Ecosystem, Websites, Preset and Nightly results and current GitHub PR/Actions ownership. It is a different plugin from the immediately preceding Mini and Delay selections. ScratchPad's existing Windows build and real editor smoke were already green, but its independently downloaded package contained a concrete, fixable release blocker: JUCE-generated moduleinfo.json had trailing commas and failed strict JSON parsing; the existing workflow had no pluginval strictness-5 gate, provenance manifest or complete checksums. There were no open ScratchPad issues and only the preserved parent release PR #2 before this follow-up.

Skell Key was compared and is currently further along: its exact-head run #44222152036 passed the Windows VST3 build, tuning tests, installer/update/rollback assertions and pluginval strictness 5, and its artifact #14391775664 passed independent checksum/metadata/PE inspection. Its remaining work is owner/host/audio/licensing/contact acceptance rather than a source-side release blocker that can be resolved safely without owner data. Skell Afar's exact-head run #44203361778 also passed its Windows package, 17 installer assertions and pluginval, but SkellCore issue #32 still records about +0.25 dB reconstructed inter-sample overshoot, so true-peak safety cannot be certified. Delay's exact-head Windows run #44227889870 is now fully green and its artifact was independently inspected. Mini's exact-head run #44213523212 still fails pluginval's VST3 validator with the empty program-name regression; Mini was not reselected. Maw's seven-plugin preview passed its seven pluginval checks in the Nightly review, but owner FL Studio acceptance and vendor/support metadata remain open. ScratchPad was selected because its strict-metadata defect and missing pluginval/provenance gates are concrete and directly fixable now, while avoiding active branches owned by other agents.

### Implementation and exact evidence

- New draft PR #3: https://github.com/skellyruno/skell-scratch-vst/pull/3.
- Branch: release/scratchpad-strict-vst3-metadata-pluginval-20261118.
- Commits: 36cd83e4ce5f7e511303e85b36e792852619a774 (normalizer/tests/workflow/provenance) and 9f1377744a465998f40f75986528f37dd47162c3 (README history-preserving clarification), followed by 37776ea0035bd029032186a6b7754560daefdaa9 (fix GitHub Actions expression interpolation).
- The implementation changes only the staged release metadata copy; it does not rewrite the compiled VST3 module or alter DSP, UI, presets, plugin identity, parameter/automation IDs or host state.
- Local Python metadata regression tests: 12/12 passed. The real baseline metadata was normalized and strict-parsed; product ScratchPad 1.19.0 / Skell Audio and both protected CIDs/categories passed. Original metadata SHA-256 c063128486a643b39d72e44d1b959fc545e5e6b29d29d096aa15556b215fcfcc; normalized metadata SHA-256 c4d5bfb505dd543d005ac9ed9a6c44054a79d50e233506fdb5d609eaf2fe7a9a.
- Workflow YAML parsed locally. The first PR-open run #44234340395 failed before job creation because literal backslashes were left before GitHub expressions in the workflow. The expression escaping was corrected in commit 37776ea.
- Exact-head Windows run #44235055442: metadata regression tests and CMake configure passed, then the PR-only run was cancelled during compilation after a public-access wording correction. New run #44235737076 is running from head c0a02fb; checkout, metadata tests and Windows CMake configure passed; Release VST3 compilation is in progress. The prior PR-only run #44234426581 was automatically cancelled by the configured PR-only concurrency rule after the source head changed. No Windows build, CTest, pluginval or new artifact pass is claimed yet.
- Existing baseline artifact #14188908006 remains preserved and independently inspected: archive 2,088,122 bytes, SHA-256 23f8344870999d38bee4e4dd3a121700903b417fb39eaeae3191d12f0b7093f6; one VST3 bundle, one AMD64 PE32+ module 3,800,576 bytes, SHA-256 3a185e3ae07f52d5c8d7a7723a8883d6716fcf55a93368e46c2193f207ddfd83; six actual JUCE editor preview PNGs.
- Inspected real baseline scenes at 441x263, 882x526 active-meter and 1323x789. No visible clipping/overlap was found in those captures. No UI source was changed and no new screenshot is claimed.

### Cross-automation handoff

- **Ecosystem Development:** latest actual run completed Project Hub reduced-motion/accessibility PR #16; exact-head Windows CI passed. SkellCore PR #42, SkellForge PR #29 and SkellWorld PR #18 were reported green; Delay's DSP fix is on main. No active branch was edited.
- **Websites Development:** latest actual result V97 completed the Creative mobile caption/animation fix; 160/160 recorded checks passed and the three-site backup was verified. HTTP navigation limitations were disclosed; no deployment/DNS action occurred.
- **Preset Quality Audit:** latest actual run 11 advanced Alchemist Factory 53 measurements, audited 54 factory definitions, passed 41/41 Windows and 32/32 portable tests, and withheld Factory 53 promotion because aggregate improvement was negligible and envelope error slightly worsened. No Master/Preset branch was edited.
- **Nightly Blueprint Review:** latest review reports Skell Maw's seven-plugin Windows preview and all seven pluginval checks passed; FL Studio and owner contact/licensing gates remain open. The review recommended testing Maw in FL Studio before changing release direction.
- DeEsser remains parked. Three distinct non-DeEsser products have now received substantive release engineering across the recent rotation: SkellyTune Mini, Skell Delay and Skell Pad/ScratchPad.

### Remaining gates and next step

Keep PR #3 draft. Finish exact-head Windows Release VST3 build, CTest, editor smoke/UI geometry, staged PE/metadata verification, pluginval strictness 5, provenance/checksums and artifact upload; download and inspect the resulting artifact. FL Studio scan/load/save-reopen, real musical A/B, preset/state/automation recall, target-hardware CPU/latency, installer/update/rollback, JUCE/VST3 licensing and owner-approved vendor URL/support email remain unverified. The next primary run should select a different project unless a genuinely urgent ScratchPad regression appears.

No PR was merged, no public release was published, and no website deployment, DNS, payment or irreversible installation action occurred.


### ScratchPad default-program pluginval prevention — 2026-11-17 23:06 EST

The baseline processor returned one program but getProgramName(0) was empty. This matches the exact pluginval strictness-5 failure in SkellyTune Mini run #44213523212, so I fixed the root cause before the new ScratchPad build reached validation. Commit 2a27488e922c6c5659d530fd3e84f3dd74e3c013 returns Default for program index 0 and the actual JUCE integration test asserts the one-program/default-name contract. The fix does not change program count, VST3 class IDs, parameter IDs, automation IDs, DSP or state format. New exact-head run #44235055442 is pending. The previous PR-only run #44234426581 is superseded; the connector exposes no manual cancel action, and the workflow's PR-only concurrency cancellation remains enabled.


Quick4 follow-up: retrieved and checksum-verified the persistent Skell Quick4 kit from the Library; restored JUCE 8.0.12 and SkellCore into /mnt/data/skell-quick4. The kit's build_capture.py supports Master and Preset only, not ScratchPad. Local FreeType, XRandR, Xinerama, Xcursor, ALSA and GL development packages are missing. The repository's existing CMake BUILD_TESTING integration executable compiles the actual ScratchPad processor/editor, verifies layout at 441x263, 882x526 and 1323x789, and captures real JUCE screenshots in Windows CI. No new local Quick4 screenshot or local Linux build is claimed.

Public-access correction: the repository is public, so GitHub Actions artifacts are publicly accessible. The workflow's PREVIEW_ONLY marker and README now accurately describe an engineering preview without implying private access. No private distribution channel was created.

## Release & Launch checkpoint 31 — 2026-11-17 (BPM Delay Calculator VST3 release hardening)

### Selected project and rationale

Selected **BPM Delay Calculator** (skellyruno/-bpmdelay-calculator-vst) as the next distinct plugin after ScratchPad. The Ecosystem automation's latest actual report named this repo as the next plugin rotation and identified its VST3-only release PR as needing exact-head Windows/pluginval validation. The open PR had no visible Actions runs/check-runs. Source review found a concrete validator defect: getNumPrograms() advertised one program while getProgramName(0) returned empty. This matches the empty-program-name strict pluginval failure already observed in SkellyTune Mini. The package gate also accepted non-empty UTF-8 moduleinfo without parsing strict JSON or verifying CMake identity; an existing verified JUCE package from another plugin demonstrates trailing commas can occur in JUCE moduleinfo. These source-side defects are directly fixable without changing DSP or protected IDs.

Skell Key and Skell Delay are now exact-head Windows-green and principally await owner-side FL Studio/audio/licensing acceptance; ScratchPad's latest run is green and its artifact has been independently inspected. Skell Afar still has SkellCore issue #32 true-peak overshoot; Mini still has its pluginval program-name failure; Maw has a seven-plugin preview but needs owner FL Studio acceptance. BPM Delay Calculator therefore won on a real source/package blocker plus a neglected plugin rotation, not because a generic audit was due.

### Implementation

- Draft PR #2: https://github.com/skellyruno/-bpmdelay-calculator-vst/pull/2, stacked on parent release packaging PR #1.
- Branch: release/delaycalc-default-program-name-20261118.
- Commits: 1b823ea64f51da2ae3af35af13bcd0f09b030604 (default program name), 116aa4095990393e8769b96b25db7aaa386158ae (strict staged moduleinfo/package identity gate), 5bf5edecf21b1c31f8af4a2590a34c0b53dce9d1 (macOS stage path and test-fixture corrections), 3cc6e1182c88c1cd1f46afc3bd32f884103b75ea (embed PREVIEW_ONLY notice and release blockers in the ZIP).
- Source fix returns Default only for program index 0 and an empty string for out-of-range indices. Program count, manufacturer/product codes, plugin identity, parameter IDs, DSP, presets and state format remain unchanged.
- Added an escape-aware normalizer that changes only a separate release-stage copy, validates strict JSON, duplicate keys, non-finite values, product/vendor/version and both CIDs derived from CMake, and records original/normalized SHA-256. The original build bundle remains untouched.
- The workflow now stages/normalizes before running pluginval 1.0.4 strictness 5 and packages that exact staged bundle. The ZIP contains PREVIEW_ONLY.txt and release-blocker metadata, so a public Actions artifact is not mistaken for a commercial release. Existing macOS validation is preserved; Windows remains primary.
- Local normalizer regression tests: 8/8 passed. Full package-validator suite, Windows CMake/Release build, CTest, pluginval and artifact creation are not claimed.

### CI / environment status

The connected GitHub query returns no workflow runs, check-runs or combined status contexts for this repository's PR heads, including after the new commits. This is not a passing CI result. No Windows build or download artifact exists for the new head yet. The persistent Quick4 kit was retrieved, checksum-verified and restored; however, its JUCE 8.0.12 differs from this repo's pinned JUCE 8.0.15 and its renderer only supports Master/Preset, so it was not used to override dependencies or claim a local Delay Calculator build/screenshot.

### Cross-automation handoff

- **Ecosystem Development:** Project Hub PR #16 reduced-motion/browser checks and Windows package verification passed; latest report named BPM Delay Calculator as the next plugin rotation.
- **Websites Development:** Creative V97 mobile caption/animation defect fixed; 160/160 recorded checks passed and three-site backup verified; no deployment.
- **Preset Quality Audit:** Alchemist Factory 53 actual comparison completed; 54 factory definitions audited; Windows 41/41 and portable 32/32 passed; Factory 53 remains experimental and unpromoted.
- **Nightly Blueprint:** Skell Maw seven-plugin Windows preview and seven pluginval checks passed; FL Studio and owner contact/licensing remain open.
- DeEsser remains parked. ScratchPad is now confirmed Windows-green; this run selected a different plugin. Three or more distinct non-DeEsser products have received substantive implementation across the recent rotation.

### Next step

Keep PRs #1 and #2 draft. First obtain a real exact-head Windows Actions run (or resolve why this repository is not producing runs), then require package tests, Windows Release VST3 build, CTest, pluginval strictness 5, provenance/checksums and independent artifact inspection. After that, perform owner-side FL Studio scan/load, audio passthrough, UI interaction, save/reopen and target-hardware CPU/latency; resolve licensing, vendor/support contacts and install/update/rollback before any commercial release.

No merge, public release, user installation, website deployment, DNS change or payment action occurred.


## Release & Launch checkpoint 32 — 2026-11-18 (SkellyTune Mini Windows VST3 preview recovery)

### Selected project: SkellyTune Mini — strict package and validator recovery

Mini was selected because the prior exact-head package work had completed, but its pluginval step falsely failed after printing `SUCCESS`; the PowerShell error text contained a blank exit code. This blocked artifact upload despite a passing VST3 validation summary. The change stayed in the existing focused PR #9 branch and did not touch DSP, UI source, presets, parameter IDs, automation IDs, or project state.

- Commit `58ed7234ea073c51c49a8d988880d78fc5b8f408` replaces reliance on `$LASTEXITCODE` with `Start-Process -Wait -PassThru`, captures stdout/stderr, and validates the actual process exit code.
- Exact-head Windows run #44246677362 passed configure, Release x64 VST3 build, editor startup/IPC smoke, strict metadata normalizer, flat staging, PE32+ architecture checks, pluginval v2.0.0-beta3 strictness 5 and artifact upload.
- Portable DSP run #44246677298 passed 39/39 CTests and emitted real-vocal, latency and synthetic callback diagnostics. The synthetic Linux CPU probe is not a substitute for the user's Windows target hardware or FL Studio.
- Artifact #14402302989 was independently downloaded. ZIP CRC passed; one flat VST3 bundle, no nested ZIP; strict JSON and two unique class IDs; AMD64 PE32+ module; all 10 package checksums recomputed; required project and dependency notices present. Archive digest `ef7a24f219fe14be972729a6a783492940176e36c416decdead715dcd1feaa3f`; module digest `cd47123add08719b824fd6fa99df02bf3216b81ba2ef4b924d224911bc305043`.
- The older PR #8 artifact remains preserved as a historical compile baseline, not a distributable package. No last-known binary was overwritten.
- Quick4 kit restored and checksums verified, but its helper supports only Master/Preset and this container lacks FreeType/XRandR/Xinerama/Xcursor/ALSA/GL development headers. No current Mini screenshot is claimed.
- Mini remains PREVIEW_ONLY. FL Studio host behavior, human musical A/B, state recall, installer/update/rollback, commercial JUCE licensing entitlement and vendor/support metadata remain open.

### Next selection

Rotate away from Mini unless a new release-blocking regression appears. Recheck exact-head CI and branch ownership for under-served Necromancer, Afar, Separator, Cast and the other neglected plugins before choosing the next source-side task. DeEsser remains parked for the non-DeEsser rotation.

## Release & Launch checkpoint 33 — 2026-11-18 (SkellyTune Mini installer identity hardening)

### Selection and priority rationale

Selected **SkellyTune Mini** as a different non-DeEsser product from the preceding Skell Maw run. The exact-head PR #10 Windows package/installer pipeline had just completed successfully, producing a usable flat preview bundle with a reversible install path. Source review found one remaining fail-open metadata edge: the installer required at least two VST3 classes and checked for processor/controller categories, but would accept a third unexpected class if the two expected categories were still present. Mini's actual shipped module contract is exactly two classes. This was a concrete release-integrity defect and could be fixed without touching the audio processor, DSP, UI, presets or host identity.

Key was not selected because Ecosystem Development owns its active installer-safety PR #12. Maw was not repeated because it was the preceding Release primary and its next gate is owner FL Studio acceptance. Afar has a separate active installer PR #10 with successful Windows CI and remains the next distinct candidate.

### Source implementation

- Repository: `skellyruno/skelltune-mini`.
- New draft PR #11: https://github.com/skellyruno/skelltune-mini/pull/11.
- Branch: `release/mini-exact-class-inventory-20261118`.
- Commit: `022523ced3a5b1fb0c6575f1bcf9a2c633c3908a`.
- Parent: PR #10 head `e2946a0b87437aa43242fe76e44e5824330882b9`.
- File changed: `release/Install-SkellyTuneMini.ps1`.
- The installer now rejects any `moduleinfo.json` inventory other than exactly two class entries. Its Windows self-test adds a third uniquely identified class with a recomputed checksum manifest and asserts rejection.
- No DSP, UI, presets, plugin class IDs, parameter IDs, automation IDs, saved-state schema or host integration changed.
- PR #11 remains draft and unmerged.

### Exact-head build and artifact evidence

**Parent PR #10 — completed and independently inspected**

- Windows run #44274095131 passed the 14 installer/rollback assertions, x64 CMake configure, Release VST3 build, processor/editor startup smoke, flat package staging, strict metadata checks, AMD64 PE32+ validation, pluginval v2.0.0-beta3 strictness 5 and artifact upload.
- Portable DSP run #44274095187 passed.
- Artifact #14412709628: 2,934,075 bytes; archive SHA-256 `3cf7dc8385d71a4cfe8591e7c7c444d6ea406c841ec1fb21de6bb3b3648cfd48`.
- Independent inspection: ZIP CRC passed; one flat `SkellyTune Realtime.vst3` bundle; no nested ZIP; strict moduleinfo JSON; product 3.3.1 / Skelly Audio; two unique class IDs; one 6,571,520-byte AMD64 PE32+ module; all 11 SHA256SUMS entries matched; installer, project license and third-party notices included.
- PR #10 description updated with the exact successful run and artifact evidence; PR remains draft.

**New PR #11 — exact-head validation passed**

- Windows run #44275482816 passed: installer self-test 15/15, CMake configure, Release VST3 build, processor/editor startup + layout/paint/IPC smoke, flat package staging, strict moduleinfo normalization, AMD64 PE32+ checks, pluginval v2.0.0-beta3 strictness 5 and artifact upload.
- Portable DSP run #44275482606 passed.
- Artifact #14414742253: 2,934,159 bytes, SHA-256 `a0ae57de953c84d0372f40088db74b7bfe0dc9dc39e2ce441bf335efdad79089`; independently inspected with ZIP CRC pass, one flat VST3 bundle, no nested ZIP, strict JSON, exactly two unique class IDs, AMD64 PE32+ module, 11/11 checksums, installer and license notices.

### Environment and quality-gate limitations

The persistent Quick4 kit was restored from the Library and its source archives passed the included checksum verification. JUCE 8.0.12 and SkellCore are present at `/mnt/data/skell-quick4`. The kit's documented Quick4 screenshot router supports Master and Preset, not Mini; no Mini screenshot is claimed. This runtime has no local PowerShell 7 and no FL Studio host, so the actual Windows installer self-test is delegated to GitHub's Windows runner and real DAW acceptance remains unverified.

### Cross-automation coordination

- **Ecosystem Development:** latest actual result focused Skell Key installer test-harness cleanup safety (PR #12); its Windows run #52 was in progress. Its next workstream is Foundation/SkellWorld. No Key branch was edited.
- **Preset Quality Audit:** latest actual result advanced Alchemist Factory 53 measurement and the 54-entry bank audit; Windows 41/41 and portable 32/32 passed. Factory 53 remains experimental and unpromoted. The current Preset run is active, so no Master/Preset branch was touched.
- **Websites Development:** latest actual result fixed Skelly Creative mobile caption/animation overlap; 160/160 combined checks reported passing. No deployment, DNS or commerce changes.
- **Nightly Blueprint:** reported Maw's seven-plugin preview and pluginval gates green, while FL Studio and owner support/licensing acceptance remain outstanding.
- DeEsser remains parked under the November 15 directive.

### Release readiness

| Gate | Status |
|---|---|
| Windows VST3 build/download | Parent PR #10 and PR #11 exact-head builds/artifacts verified |
| Pluginval strictness 5 | Parent PR #10 and PR #11 passed |
| Portable DSP regressions | Parent and PR #11 portable runs passed |
| Installer/rollback logic | Parent PR #10 14/14 and PR #11 15/15 assertions passed |
| Bundle metadata / architecture / hashes | Parent artifact independently verified |
| FL Studio scan/load | UNVERIFIED |
| Preset/state/automation recall | UNVERIFIED in a real host |
| Human musical A/B | UNVERIFIED |
| Target-hardware CPU/latency | UNVERIFIED |
| Commercial licensing / vendor / support | OWNER APPROVAL REQUIRED |
| Storefront / email signup / pricing / trial | Coordinate with Websites automation; owner decisions required |

### Next selection and action

PR #11's exact-head Windows build, 15 installer assertions, editor smoke, pluginval and artifact inspection are complete. After this Mini execution, rotate to **Skell Afar** as the next distinct plugin, after checking current PR/Actions ownership and the SkellCore true-peak concern. This advances the rolling non-DeEsser implementation count: Skell Maw (previous run) + SkellyTune Mini (this run) + Skell Afar (next candidate).

No PR merged, no public release published, no production installation, website deployment, DNS change or payment action occurred.


## Release & Launch checkpoint 34 — 2026-11-18 (Skell Afar experimental true-peak integration)

### Selection rationale

Selected **Skell Afar** as the next distinct non-DeEsser product after SkellyTune Mini. Afar had a verified Windows VST3/installer baseline, a reproducible release-blocking inter-sample concern in SkellCore issue #32, and an independently green shared-core draft fix (PR #43). This is more valuable than starting unrelated UI/features because the audio-safety issue blocks any true-peak assurance. The Core PR branch is owned by its existing workstream; this run did not edit it. The Afar installer PR #10 branch was also left untouched.

### Source implementation

- Repository: `skellyruno/skell-afar-vst`.
- New draft PR #11: https://github.com/skellyruno/skell-afar-vst/pull/11.
- Branch: `test/afar-truepeak-core-integration-20261118`.
- Commit: `53f90b4a7afe6ac4be7b7722b4fe680deaf2ff49`.
- Parent: Afar PR #10 exact head `642747244270380dfe09bc3d9f8673ab73779b7d`.
- Shared dependency pin: experimental SkellCore PR #43 head `e972e49ef93e021a3993110a0a9603d9774e9def` (PR #43 remains draft).
- Files: `CMakeLists.txt`, `README.md`, `tests/test_true_peak_integration.cpp`, `docs/TRUEPEAK_INTEGRATION.md`.
- The new test runs only when the exact real SkellCore checkout is supplied; the old stub cannot mask a dependency regression. It exercises Afar's actual `SceneDSP` output path with the creative path bypassed, preserving the final limiter/sample guard. It checks 44.1/48/96 kHz, 7 kHz/13.517 kHz/0.435×Fs stress tones, both quality modes, finite/stereo output, sample ceiling, 3 ms latency and an independent 16-phase/64-tap Blackman reconstruction. Regression budgets are 0.12 dB Economy and 0.04 dB Standard; these are not BS.1770 certification.
- No plugin parameter IDs, VST3 CIDs, APVTS state, presets, UI, or host automation were changed.

### Validation status at ledger update

- Windows VST3 run #44280992708: in progress.
- Real SkellCore ASan/UBSan run #44280992598: configure and compile passed; CTest still in progress.
- Real JUCE Guided Tour screenshots run #44280992545: queued/in progress; no screenshot artifact yet.
- SkellCore PR #43 exact-head Windows, portable and sanitizer workflows passed; its Ubuntu 48 kHz stereo limiter benchmark reported 0.892% (Economy) / 1.665% (Standard) of one real-time stream. This is not Afar full-chain or target-PC CPU profiling.
- The previous Afar artifact was downloaded and independently inspected: archive digest above; ZIP CRC passed, 9/9 manifest entries matched, exactly one flat bundle and one AMD64 PE32+ module. Existing artifact and installer PR #10 remain preserved.

### Cross-automation coordination

- Ecosystem Development's latest actual result is Key installer test-harness cleanup safety PR #12; its next run is in progress. No Key branch was edited.
- Websites and Preset Quality latest scheduled runs reported task failures; no branch was touched and their prior completed work was not assumed to be the latest result.
- Nightly Blueprint's latest completed review reported Maw's seven-plugin preview gates green; FL Studio and owner-side commercial gates remain open.
- DeEsser remains parked.

### Next selection

After Afar's exact-head gates are complete, rotate to a different non-DeEsser project. Recheck under-served Flang, Cast, EQ, Separator and other candidates for fresh CI/branch ownership; do not select Afar again unless its new integration test exposes a critical regression.

No PR merged, no public release, production install, website deployment, DNS change or payment action occurred.


### Afar PR #11 exact-head follow-up — 2026-11-18 05:07 EST

- Windows run [#44280992708](https://github.com/skellyruno/skell-afar-vst/actions/runs/44280992708) completed successfully: JUCE 8.0.12 configure, Release VST3 compile, Windows CTest 12/12, package validator, VST3 staging, 17 installer/update/rollback assertions, Steinberg VST3 validator exit code 0, pluginval v2.0.0-beta3 strictness 5 (1 passed, 0 failed), artifact upload.
- Artifact #14416928294: 6,120,924 bytes; ZIP SHA-256 `7cfc047e9375997a8c6636e01241ecd46a88381e70e7452342ca6b777495b74c`. Independent inspection: ZIP CRC pass; 11 entries; one flat VST3 bundle; strict moduleinfo, exactly two original CIDs, AMD64 PE32+ module 6,096,896 bytes; all 9 SHA256SUMS / TOOLS-SHA256SUMS entries matched. Module SHA-256 `d0c11b576f11efca27d1f1d2b458970da8080b811a3fd8de52a70e00b58ea2ca`. Build provenance: source merge commit `1b613a39afd1b7e291ff71107a7d1a9426ee31e7`, source ref `refs/pull/11/merge`, run #44280992708.
- Real-core ASan/UBSan run [#44280992598](https://github.com/skellyruno/skell-afar-vst/actions/runs/44280992598) passed CTest 13/13. The new `SkellAfarTruePeakIntegration` test passed in 1.84 s; the full suite took 409.08 s, with the existing LoudnessCharacter test taking 251.08 s and Reverb_engine 59.50 s.
- Real JUCE screenshot workflow [#44280992545](https://github.com/skellyruno/skell-afar-vst/actions/runs/44280992545) has configured the actual editor and is building `SkellAfarTourScreenshots`; screenshot capture and visual review remain pending.
- The Windows artifact is a private-preview CI artifact, not a commercial release. FL Studio, musical A/B, target-PC CPU/latency and licensing remain unverified. Core PR #43 and issue #32 remain draft/open; no merge or release was performed.


### Afar UI and provenance follow-up — 2026-11-18 05:10 EST

- Real JUCE editor workflow [#44280992545](https://github.com/skellyruno/skell-afar-vst/actions/runs/44280992545) passed: actual editor renderer built and tutorial verified at 825×525, 1100×700 and 1650×1050. Artifact #14416728684 (3,254,245 bytes; ZIP SHA-256 `abe0a97c0a9f85cef7d712dcfb3c1b51ec954376c55d45ddbb7abe96036851ee`) contains 6 Pro/tour captures plus 3 Simple captures and manifests. Compact, default, large, tour and Simple views were inspected; no visible clipping or overlap found.
- Artifact #14416928294 was deliberately marked superseded after independent inspection found its `THIRD-PARTY-NOTICES.txt` still named the previous Core pin `7694ffee5880aed050c33d713b310f853e13d096`, while CMake and build-info used PR #43 head `e972e49ef93e021a3993110a0a9603d9774e9def`. This was corrected in Afar commit `a50ddbc7a946bba2baf3681fb17be14561f123b1` without changing DSP/UI. The corrected-head Windows, real-core sanitizer and screenshot workflows are in progress; do not use the superseded ZIP as the current package.
- Quick4 kit was restored and its embedded source archives checksum-verified; local Afar screenshot build was not possible because the kit renderer only supports Master/Preset and the runtime lacks FreeType/XRandR/Xinerama/Xcursor/ALSA development headers. The real JUCE screenshot evidence above came from the actual Afar editor renderer, not a mockup.


### SkellCast private installer implementation — 2026-11-18 10:43 EST

- Selected SkellCast after reviewing Preset, Ecosystem, Websites and Nightly latest results and current open PR/Actions state. Cast PR #6 had a proven exact-head Windows VST3 build and pluginval strictness-5 pass, while its own README still listed installer/update/backup/rollback as release blockers. Flang and AdlibLab had recent active branch work; Separator already had a new installer branch and successful exact-head run; Cast was the clearest non-overlapping installer gap.
- Draft PR #7: https://github.com/skellyruno/skell-cast-vst/pull/7
- Branch `release/cast-private-installer-rollback-20261118`, head `a03a60ffa6a2268f72846f908bfa329552ee31a1`, base PR #6 branch `fix/cast-audio-thread-safe-settings-20261117` at `a6c1a27e4229df03f9f196094e0309be85a79ad4`.
- Adds per-user Windows VST3 installation, idempotent update, SHA-256-verified backup and explicit rollback. `-WhatIf` is supported; no administrator elevation or machine-wide install is the default. The helper only replaces the plugin bundle and does not modify registry, global sharing preferences, presets, host state or FL Studio projects.
- The package verifier now embeds `Install-SkellCast.ps1` in the preview package and hashes it. The Windows workflow now gates artifact upload on the PowerShell integration suite. The test suite exercises fresh install, repeat install, update, backup, rollback, malformed/tampered package and backup, path traversal, duplicate/non-finite JSON and invalid existing target.
- PR #7 is draft and unmerged. Exact-head Windows run #44342195642 is in progress; CMake/JUCE configure passed and the Release VST3 build is running. CTest, package verification, installer integration, pluginval and artifact upload remain pending. The superseded PR-only run #44341340635 was automatically cancelled. No new artifact is claimed.
- Existing parent artifact #14303933435 and original baseline #14186867360 remain preserved; no DSP, UI, parameter IDs, automation IDs or state schema were changed.
- Oldest blockers: exact-head Windows CI, owner-side FL Studio scan/load, CABLE/SPARE + OBS integration, real audio A/B, state/session recall, target CPU/latency, licensing, approved vendor/support metadata and code signing.
- Next test: exact-head Windows build, CTest, package-verifier tests, installer integration tests and pluginval strictness 5; then owner-host acceptance. No PR merged or public release performed.


### SkellCast CI follow-up — 2026-11-18 10:45 EST

- Added a changelog to the package, embedded it alongside the installer, and made the installer require the changelog as a package sidecar.
- Hardened checksum parsing by preserving the manifest digest before path validation, and require backup folders to contain exactly one bundle plus one manifest.
- Latest branch head: `a03a60ffa6a2268f72846f908bfa329552ee31a1`.
- Exact-head Windows workflow run #44342195642 is in progress. CMake configure is running; no compile, CTest, package, installer, pluginval or artifact result is yet claimed.
- The superseded PR-only run #44341340635 was automatically cancelled by the repository's PR-only concurrency policy. Main/manual/release jobs were not cancelled.


### SkellCast exact-head progress — 2026-11-18 11:03 EST

- Run #44342195642 passed checkout, Python 3.12 setup and CMake/JUCE configure.
- Release VST3 build is in progress. CTest, Python package tests, package staging, PowerShell install/update/rollback integration, pluginval strictness 5 and artifact upload have not run yet.
- No new downloadable artifact or host acceptance is claimed.


## Release & Launch checkpoint 35 — 2026-11-18 (Skell Delay private-preview delivery)

### Selection rationale

Selected **Skell Delay** as the next non-DeEsser product after the previous Release & Launch run selected SkellCast. Delay beat the other available candidates because its exact PR #12 head had a fresh, independently verifiable Windows x64 VST3 package with the full DSP/stress/realtime suite and pluginval strictness 10 passing, while the package had no per-user private installer/update/rollback path. SkellCast had just received that implementation, so selecting it again would violate the required project rotation.

- **BPM Delay Calculator:** Ecosystem Development's latest completed run identified a fixture mismatch in PR #2 and named it as its next plugin task. That branch is owned by the active Ecosystem workstream; this run did not touch its repository or branch.
- **Skell Key:** its existing draft release chain already has tested installer/update/rollback and a verified Windows preview; no Key branch was edited.
- **Skell Maw:** its seven-plugin preview has pluginval coverage, but its next critical gate is owner-side FL Studio acceptance; no Maw branch was edited.
- **SkellCast:** previous Release & Launch selection; its PR #7 remains preserved and was not modified.
- **Skell Delay:** exact-head Windows build and pluginval 10 already passed; a safe per-user preview installer was the clearest remaining distribution gap that could be implemented without editing another agent's branch.

### Source and packaging changes

- Product repo: `skellyruno/skell-delay-vst`.
- Draft PR #13: https://github.com/skellyruno/skell-delay-vst/pull/13.
- Branch: `release/delay-private-preview-installer-rollback-20261118`.
- Latest commit: `6bc6136069d05cc44dd54f697816f7e27f1f2bbc`.
- Parent PR #12 head: `dba3425f9ce11932fb8dc76c192043d33258ed88`; no edits were made to PR #12, PR #11 or main.
- Adds `installer/windows/Install-SkellDelayPreview.ps1`: PowerShell 7 per-user install to `%LOCALAPPDATA%\\Programs\\Common\\VST3`, WhatIf, explicit confirmation, idempotent install, verified update backup, staged swap and explicit rollback.
- Adds `installer/windows/Test-SkellDelayPreviewInstaller.ps1`: Windows CI integration tests for WhatIf, fresh install, idempotence, filesystem-root refusal, unsafe checksum-path rejection, tampered package rejection, update backup, tampered-backup rejection and byte-for-byte rollback.
- Adds `docs/INSTALL_PREVIEW.md`; updates installer and release checklists.
- Extends `scripts/verify_windows_vst3.py` to embed the installer and guide and record every VST3 bundle file in the build manifest. `SHA256SUMS.txt` now covers every bundle file, installer, guide and build-info manifest.
- Adds the PowerShell integration gate after package staging and before artifact upload in the Windows release workflow.
- No DSP, UI, presets, parameter IDs, automation IDs, VST3 CIDs, host-state format, FL Studio projects, registry, machine-wide plugin folders, licensing terms or owner contact data were changed.

### Preserved baseline and independent inspection

Parent Windows run [#44299900149](https://github.com/skellyruno/skell-delay-vst/actions/runs/44299900149) passed:
- Python release-package verifier tests.
- Windows x64 CMake/JUCE configure and Release VST3 compilation.
- DSP, stress and real-time CTests.
- pluginval strictness 10.
- VST3 bundle staging and artifact upload.

Parent artifact [#14426686086](https://github.com/skellyruno/skell-delay-vst/actions/runs/44299900149/artifacts/14426686086) was downloaded and independently inspected in this run:
- ZIP: 4,788,680 bytes; SHA-256 `af32060fff2018e9358a52907a38e0fe6df5ea07828afa3007cec7e2956eb77c`; ZIP CRC passed.
- Four archive entries: one package directory containing one Skell-Delay VST3 bundle, moduleinfo.json, build-info.json and SHA256SUMS.txt.
- Product/version/vendor: Skell-Delay 1.0.0 / Skelly Audio; manifest status PREVIEW_ONLY.
- One Windows module: 8,945,152 bytes, AMD64 PE32+, binary SHA-256 `28379cd7d28afde63c6841a31345a536b3b39077edc515b62153195475be8814`.
- Two distinct original component/controller CIDs.
- All three parent SHA256SUMS entries recomputed and matched.

The original parent artifact remains unchanged and downloadable. No new artifact is claimed for PR #13 until the exact-head Windows workflow completes.

### Exact-head CI and superseded runs

- PR #13 first head `9e8ef3364c157a8f59c8dbb109103434c292d9a7`, run [#44353393550](https://github.com/skellyruno/skell-delay-vst/actions/runs/44353393550): Python release-verifier tests passed; run was automatically cancelled during CMake configure after a follow-up safety commit.
- Intermediate head `5ef0f4e90dcdef31da5bbb66c38a3b474d10f1a2`, run [#44353702535](https://github.com/skellyruno/skell-delay-vst/actions/runs/44353702535): automatically cancelled when the next commit superseded it.
- Latest head `6bc6136069d05cc44dd54f697816f7e27f1f2bbc`, run [#44353755432](https://github.com/skellyruno/skell-delay-vst/actions/runs/44353755432): in progress at ledger update. Do not claim MSVC build, CTest, installer integration, pluginval or a new artifact until completion.
- Repository PR-only concurrency cancelled only superseded draft PR runs. Main, release and manual jobs were not cancelled.
- PR #13 remains draft and unmerged.

### Cross-automation coordination

- **Preset Quality Audit:** latest completed run advanced Alchemist with nine actual candidate renders and corrected production preset defaults/legacy-import behavior in draft PR #67. Portable checks passed 18/18 and reference diagnostics 4/4; exact-head Windows VST3/native tests remain pending. No Preset branch was edited.
- **Ecosystem Development:** latest completed run fixed a Skell Studio playlist label-sizing defect and added three regression tests in draft PR #10; exact-head Windows build and replacement screenshots remain pending. Its next named plugin task is BPM Delay Calculator PR #2's fixture mismatch; no branch overlap occurred.
- **Websites Development:** latest report records Artist/Album V100 at 122/122 regression checks and 30/30 HTTP checks, while the current website automation execution is still in progress. No site, domain, DNS or deployment was changed.
- **Nightly Blueprint:** latest completed review recorded Skell Maw's seven-plugin Windows preview and seven pluginval passes, with FL Studio, vendor/support and commercial gates still open. No Maw branch was edited.
- DeEsser remains parked; no DeEsser work was selected.

### Release readiness and oldest blockers

| Gate | Status |
|---|---|
| Parent Windows VST3 build/download | PASS — private preview only |
| Parent DSP/stress/realtime CTests | PASS |
| Parent pluginval strictness 10 | PASS |
| Parent bundle, PE architecture, metadata and checksums | PASS — independently inspected |
| New complete package checksum inventory | Implemented; exact-head CI pending |
| New per-user installer/update/backup/rollback | Implemented; Windows integration pending |
| FL Studio scan/load and project/state recall | UNVERIFIED |
| Real musical A/B and owner listening | UNVERIFIED |
| Target-hardware CPU/latency | UNVERIFIED |
| Current-source Quick4 UI/menu/resize inspection | UNVERIFIED |
| Licensing/third-party attribution | OWNER REVIEW REQUIRED |
| Vendor URL and support email | OWNER INPUT REQUIRED |
| Code signing | UNVERIFIED; certificate decision required |
| Storefront/email signup, pricing/trial | Coordinate with Websites; owner approval required |

### Next release step

Finish the exact-head Windows run #44353755432. Fix any real PowerShell/packaging/build failure before another feature. If it passes, download and independently inspect the new artifact, verify all embedded hashes and the installer sidecars, and keep PR #13 draft. Then owner-side FL Studio scan/load, preset/state/automation save/reopen, real audio A/B and target-hardware CPU/latency are still required before release consideration.

No PR was merged, no public release published, no production install, website deployment, DNS change or payment action occurred.


### Skell Delay exact-head CI update — 2026-11-18 12:04 EST

- Latest PR #13 head remains `6bc6136069d05cc44dd54f697816f7e27f1f2bbc`.
- Windows run [#44353755432](https://github.com/skellyruno/skell-delay-vst/actions/runs/44353755432): checkout and Python 3.12 setup passed; the expanded Python release-package verifier suite passed; Windows CMake configure passed; MSVC Release VST3 build is now in progress.
- DSP/stress/realtime CTests, pluginval strictness 10, package staging, PowerShell integration, artifact upload and host acceptance have not run yet.
- No new artifact is available. Keep PR #13 draft and do not treat configure success as a completed Windows build.


### Skell AdlibLab private-preview installer — 2026-11-18 12:54 EST

#### Selection rationale

Selected **Skell AdlibLab** as a different non-DeEsser product from the previous Skell Delay selection. It beat the remaining candidates because PR #10 now had a fresh, independently downloadable Windows x64 VST3 artifact after the previous strict pluginval program-name failure was fixed. The exact-head Windows run passed the Release build, strict metadata normalization, PE32+ verifier and pluginval strictness 5. The package still explicitly said it had no installer, updater or rollback, making private distribution the concrete remaining gap. Skell Key already has tested installer/rollback; Skell Studio and BPM Delay Calculator are in the active Ecosystem workstream; Skell Master branches are owned by Preset Audit. No overlapping branch was edited.

#### Source and packaging changes

- Product repo: `skellyruno/skell-adliblab-vst`.
- Draft PR #11: https://github.com/skellyruno/skell-adliblab-vst/pull/11.
- Branch: `release/adliblab-private-preview-installer-rollback-20261118`.
- Latest head: `398f69b1d2373934e5943937e689e142fbbd36b9`.
- Parent: PR #10 exact head `7187275fd2f5aee8ee5c58ec03caa78f8ca4d2f9`; PR #10, PR #9 and main were not modified.
- Adds `installer/windows/Install-SkellAdlibLabPreview.ps1`: PowerShell 7 per-user install to `%LOCALAPPDATA%\\Programs\\Common\\VST3`, WhatIf, explicit confirmation, idempotence, full SHA256SUMS inventory verification, strict JSON, exact product/vendor/version, protected CIDs, AMD64 PE32+ checks, verified update backup, staged swap and explicit rollback.
- Adds `installer/windows/Test-SkellAdlibLabPreviewInstaller.ps1`: WhatIf, fresh install, idempotence, filesystem-root refusal, existing-file target preservation, package-overlap refusal, checksum path traversal, tampered package, versioned update, verified backup, tampered-backup rejection and rollback preserving the replaced version.
- Adds `docs/INSTALL-PREVIEW.md`; embeds the installer and guide in the Windows artifact; both are covered by SHA256SUMS.
- Windows workflow runs the PowerShell integration suite after package/checksum assembly and before artifact upload. README and PREVIEW-ONLY text now accurately describe the unsigned manual helper, not a signed/commercial installer or automatic update service.
- No DSP, UI, presets, parameter IDs, automation IDs, VST3 CIDs, host-state format, FL Studio projects, license notices, registry or machine-wide plugin folders changed.

#### Preserved parent artifact and independent inspection

Parent Windows run [#44287143589](https://github.com/skellyruno/skell-adliblab-vst/actions/runs/44287143589) passed the sanitizer-backed DSP job and Windows x64 Release VST3 build, strict moduleinfo normalization, fail-closed package verifier, pluginval v2.0.0-beta3 strictness 5, dependency notices/provenance and artifact upload.

Parent artifact [#14419617362](https://github.com/skellyruno/skell-adliblab-vst/actions/runs/44287143589/artifacts/14419617362):
- 7,870,106 bytes; archive SHA-256 `e436c14f5eb6a477222b1e0e96c3b5f50c49ca90a0e19ffa5c5b62c67e49f1f7`.
- ZIP CRC passed; 12 entries; no duplicate or case-colliding paths.
- All 11 SHA256SUMS records recomputed and matched.
- One `Skell AdlibLab.vst3`, version 0.10.2 / Skell Audio, two unique protected CIDs, one AMD64 PE32+ module of 7,839,232 bytes; binary SHA-256 `0678602e733b2ee1db9a9092696a24a948c3dfa75e4b88b454f8377302d9bb78`.
- Build provenance pins JUCE 8.0.12 to `29396c22c93392d6738e021b83196283d6e4d850` and SkellCore to `eb56702153c4373799a4e8e2663e0f158c0115a6`.

Real JUCE UI parent artifact [#14419183558](https://github.com/skellyruno/skell-adliblab-vst/actions/runs/44287143585/artifacts/14419183558) and exact-head PR #11 artifact [#14456771291](https://github.com/skellyruno/skell-adliblab-vst/actions/runs/44365584546/artifacts/14456771291) are both 18,941,428 bytes. Parent ZIP SHA-256 `18571d2487451ca25e6246a17c8a760ea9b7cba1261c62b61e85f1e17318a582`; PR #11 ZIP SHA-256 `c5d537f3d07be8be22be6cafbed0edecdb5189ea24048830f2d6b97b585adddd`. Each contains 100 scene PNGs plus contact sheet; all 101 PNGs are byte-identical between runs. I inspected the contact sheet, minimum-size cosmic layout and preset overlay; no clipping or overlap was visible.

#### Exact-head CI and release gates

- PR #11 head `398f69b1d2373934e5943937e689e142fbbd36b9`; Windows run [#44365584373](https://github.com/skellyruno/skell-adliblab-vst/actions/runs/44365584373) passed all 18 sanitizer/DSP/static safety steps; MSVC x64 Release compile, bundle staging, strict metadata normalization, AMD64 PE32+ verification, pluginval strictness 5, installer integration and artifact upload all passed on exact head. Real JUCE UI run [#44365584546](https://github.com/skellyruno/skell-adliblab-vst/actions/runs/44365584546) completed all 10 steps and uploaded artifact [#14456771291](https://github.com/skellyruno/skell-adliblab-vst/actions/runs/44365584546/artifacts/14456771291): 101 PNGs (100 scenes plus contact sheet), byte-identical to parent UI artifact #14419183558. Installer-enabled artifact [#14456259709](https://github.com/skellyruno/skell-adliblab-vst/actions/runs/44365584373/artifacts/14456259709) is available and independently verified; it remains unsigned and preview-only.
- PR #11 remains draft. No merge or public release.
- The Windows runner completed the new installer integration suite successfully. This Linux container still has no FL Studio host, so FL Studio scan/load and owner-side audio/state/hardware acceptance remain unverified.
- FL Studio MIDI routing/scan/load, preset/state/automation save-reopen, real adlib/music A/B, target-PC CPU/latency, licensing/attribution, HTTPS vendor URL/support email, signing and commercial approval remain open.
- Parent PR #10 artifact is preserved; no backup of user files or installed plugin was performed or claimed.

#### Cross-automation coordination

- Preset Quality's visible open work remains on Alchemist and Skell Master PRs; no Preset branch was edited.
- Ecosystem Development's visible open work includes Skell Studio PR #10 and BPM Delay Calculator PR #2; neither branch was edited.
- Websites Development's latest visible result remains Artist/Album V100 at 122/122 regression checks and 30/30 HTTP checks; no site, DNS or deployment was changed.
- Nightly Blueprint's latest completed ledger entry remains Skell Maw's seven-plugin preview and seven pluginval passes; no Maw branch was edited.
- DeEsser remains parked.

#### Next release step

Wait for PR #11's exact-head Windows run. Fix any real MSVC, PowerShell, packaging or checksum failure. If green, download and independently inspect the installer-enabled artifact and every checksum. Keep PR #11 draft until owner-side FL Studio scan/load, MIDI routing, state/preset/automation save-reopen, real audio A/B and target-hardware CPU/latency are complete.

### SkellFan private preview installer — 2026-11-18 14:02 EST

- Product repo: `skellyruno/skell-fan-vst`.
- Draft PR #12: https://github.com/skellyruno/skell-fan-vst/pull/12.
- Branch: `release/fan-private-preview-installer-rollback-20261118`.
- Commit: `6aefb614db653641099b643fc083b41cb1269ebd`; stacked on PR #11 exact head `a1ffdaf2354f4929a8680d31439d03bdb87342bd`.
- Added `scripts/Install-SkellFanPreview.ps1`, `tests/Test-SkellFanPreviewInstaller.ps1`, and `docs/INSTALL_PREVIEW.md`; workflow stages the installer/guide, hashes both, runs Windows integration tests before artifact upload, and README documents preview/rollback.
- The installer is PowerShell 7, per-user under LocalAppData, WhatIf plus explicit approval/confirmation, VST3 metadata/CID/AMD64 PE32+ and five-file SHA-256 verification, safe path checks, staged install, verified update backup and explicit rollback. It refuses an unowned existing VST3 and does not touch registry, global VST3 paths, FL Studio projects, presets or automation IDs.
- Exact-head Windows run [#44376137274](https://github.com/skellyruno/skell-fan-vst/actions/runs/44376137274) on commit `6aefb614` completed with the Windows Release build, DSP/portable tests, package verification and pluginval strictness 5 passing; installer integration then failed because the tampered-binary test expected `SHA-256 mismatch`, while the installer correctly rejected the binary earlier with `Binary/moduleinfo hash differs from provenance`. This is a test expectation defect, not an installer acceptance failure. Corrected only the expected rejection text in commit `7f82b9bc9a45ea9182c87be8b32df88f30d15654`. Exact-head Windows rerun [#44384242825](https://github.com/skellyruno/skell-fan-vst/actions/runs/44384242825) is in progress; no installer-enabled artifact is claimed until it passes.
- Parent preview artifact #14264828558 remains preserved with SHA-256 `0d2e247dc21ad5672eaa9dbbc1d84b5edba80bf6af80436fc7ad0b37e66d58d8`; parent module SHA-256 `115cee937f29573d98dd62a0464ec9c5c1792d605cc1cc68c3a776d223a7a39d`. No baseline file or prior PR branch was overwritten.
- FL Studio scan/load, real-audio A/B, preset/state/automation recall, target-hardware CPU/latency, local Quick4 current-source inspection, licensing/attribution, vendor/support and code signing remain unverified. PR #12 remains draft; no merge or public release.


#### Additional SkellFan verification note

- Parent preview ZIP downloaded to the working container and independently checked: ZIP CRC passed; SHA-256 matched GitHub artifact digest `0d2e247dc21ad5672eaa9dbbc1d84b5edba80bf6af80436fc7ad0b37e66d58d8`; all three embedded checksum entries matched.
- Real Quick4 renderer artifact #14187699060 was run under Xvfb twice from source commit `0284773522881a0d945537f9fb9328a27771d6d2`; both runs reported 8/8 scenes and 0 errors. The second capture's eight PNGs were archived for handoff. Main/default, rotary, active processing, alternate skin, 574px compact, 956px large and 1434px maximum scenes were inspected; no visible clipping, overlap or control crowding was found.
- This is a baseline UI capture, not a current-head native rebuild. The compare from `0284773522881a0d945537f9fb9328a27771d6d2` to PR #11 parent `a1ffdaf2354f4929a8680d31439d03bdb87342bd` contains no `Source/PluginEditor` changes; PR #12 changes packaging only. Menu interaction, hover and animation smoothness were not exercised by the static Quick4 scenes.
