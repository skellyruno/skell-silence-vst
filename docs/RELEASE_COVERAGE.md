# Skelly release coverage ledger
Updated: 2026-11-17 15:46 EST (SkellyChoir PR #9 reproducible Windows checkout fix; exact-head CI running)
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
| Skell Silence — skell-silence-vst | 2026-11-16 (previous release selection; exact-head rerun and UI recheck passed) | PR #14 head `f9fd082eaba48b1691ad3d8690218d71f2c543a2`; Windows run #43927197784 passed DSP, Windows VST3 build, JUCE host regression, SkellCore actual editor capture 82/82, bundle staging and pluginval strictness 5. Artifact #14258200082: one `Skell Silence.vst3`, v2.8.0, AMD64 PE32+, module 3,913,216 bytes; module SHA-256 `307d36410937415855f68884cc27eea6034c7a153c4f86f049aff268bf6d0666`; archive digest `9103143dee94731059b6179d63d815730ae5b628a57b134affee9be0882207bc`. UI artifact #14256363697: 82 manifest scenes + 3 guided-tour screenshots + contact sheet; digest `19195ef4618e8a9e60754e0b450a7a714bd16fb199a40066171eeef43b0f235a`. I inspected the contact sheet, an all-scenes montage and representative full-size minimum/menu/tour/standard views; contact sheet is no longer black and no visible clipping/overlap was found. | FL Studio save/reopen and audio A/B; independent Quick4 capture; vendor URL/support-email and licensing approval. |
| Skell Key — skell-key-vst | 2026-11-17 (selected; strict staged-metadata release gate added) | Preserved baseline PR #9 head `3d8c97db934debe2083f67875f6a3080f1513061`; exact-head Windows run #44009458351 passed Release VST3, tuning CTest 2/2, flat staging and pluginval strictness 5. Artifact #14295249929 independently inspected: 2,157,887-byte one-level ZIP, SHA-256 `9074e154b4fffc0056e4002335994359209d6dccf69d41c000a52fc883fafa37`; exactly one `Skell Key.vst3`; one AMD64 PE32+ module, 4,918,784 bytes, SHA-256 `71c973dcc346bd007c0724bffae9a08807408c983cef5a5112c457b5ac7b6f3c`. Original moduleinfo SHA-256 `cba009b343db6ca26d9821a301e099907d8cf55ab00106714033ea6d704461a2`; strict JSON parser rejects its JUCE trailing comma. New draft PR #10 current head `0dbd76f256f6a91799e4ba2acf59ad3352dadcfe`, branch `release/key-strict-moduleinfo-20261117`, stacked on PR #9; adds staged-only normalization, product/vendor/version + processor/controller + unique-CID checks, original/staged hashes, verification sidecar, no-overwrite staging and 30-day preview retention. Local suite 12/12 passed. Exact-head run #44040263771 passed Windows Release build and tuning CTest, then failed one false-positive regex assertion because the fixture deliberately includes literal `,}` inside a quoted description; strict JSON parsing itself passed. Corrected in commit `0dbd76f256f6a91799e4ba2acf59ad3352dadcfe`. Exact-head run #44041085916: configure passed, Windows Release build in progress at this update; no new package/pluginval artifact claimed. Blank vendor URL/E-Mail and missing root LICENSE/COPYING/NOTICE remain blockers. | Finish run #44041085916, confirm Windows build, tuning CTest 2/2, 12 normalizer tests, strict metadata verification, pluginval 5 and upload; independently inspect new artifact and hashes. Then FL Studio scan/load, key/scale/A4 sync with SkellyTune Mini, state/automation/old-project recall, musical A/B, Quick4 renderer, licensing and approved contact metadata. |
| Skell Delay — skell-delay-vst | 2026-11-17 (Ecosystem Development merged stability PR #2; not selected by Release & Launch this run) | PR #2 merged as `00b45315b79e194a3775b0f8a689d13ef93914a0`; post-merge main run #44077183182 succeeded. Uploaded artifacts: Windows #14325942388 (4,786,194 bytes; digest `sha256:f0427f15bf5b4033938b17296b5a373769a3ae4fa1e60e11af5da61d8fbd919d`), Linux #14325164773 and macOS #14326437408. These post-merge artifacts were not independently downloaded/inspected in this run. Prior exact-head run #43909229094 passed Windows/Linux/macOS, CTest and pluginval strictness 10; the Windows DSP test stack overflow and legacy-state default restoration were corrected. | Independently download and inspect the post-merge Windows VST3 archive and checksums; then FL Studio load/save/reopen, preset/state recall, UI Quick4, musical A/B and target-hardware CPU/latency. |
| Skell Preset — skell-preset-vst | 2026-11-16 (Preset Audit latest run; Windows VST3 and host fixture passed, Alchemist trial not promoted) | Current draft build is v0.7.0 from merge commit `78c762db`; Windows CTest 41/41, portable CTest 32/32, startup/state restoration and native rack host fixture passed. The 50-preset bank audit found 0 duplicate names, invalid macro ranges or invalid cover indices. Alchemist Factory 49 vs 48: spectral error improved 0.486 to 0.454 dB, but dynamic-envelope error worsened 3.523 to 3.595 dB, so Factory 49 remains experimental and Factory 48 stays champion. Four 15-second 24-bit FLAC previews and measurement JSON were verified; headless Chromium playback timed out. FL Studio remains unrun. | Keep Factory 49 unpromoted; continue independent compressor-blend A/B; inspect the compiled UI/Quick4; FL Studio preset/state recall and target-hardware CPU/latency; preserve factory 43/46/48. |
| Skell Master — skell-master-vst | 2026-11-17 (Preset Audit advanced Deuce; release branches actively owned by Preset Audit) | PR #14 head `f7b04a1c9d753392f932c3009f0ea145c2957bbe`, run #44048251784, passed; PR #15 head `b557a54a75990a2d30852b7b8e615fa7fd68b056`, run #44080300222, passed. Changes move Deuce five-band color before the internal limiter, preserve post-downsample +2 dB/5 kHz presence, gate optional color while bypassed and retain warm crossover history. Preset Audit reports CTest 9/9, UI geometry 5/5 and hosted synthetic VST3 audio at three sample rates. PRs #14/#15 and related true-peak branches remain active; do not edit them. | Keep branch ownership; complete full-band true-peak safety, user-listened A/B, target-hardware CPU/latency, FL Studio save/reopen and package/licensing/contact checks. |
| Modular FX Suite — skell-rack-vst | 2026-11-17 (selected; VST3-only release packaging and CI) | Draft PR #4, branch `release/windows-vst3-only-juce812-20261117`, current head `829de4513cedabcb9f841eb6a402d0d1e9b7e5f2`, based on main `273eba05567e6cf0f7ba02d9e819b5981d637d82`. No open PRs/issues existed before selection. Main CMake used JUCE 8.0.0 and `FORMATS VST3 AU Standalone`; the package workflow was manual-only. Preserved baseline Windows run #38243301476 / artifact #11743164423, source commit `f559550b3c5e0fdff641e00b74ef0ef2a72c9451`; GitHub digest and downloaded ZIP SHA-256 both `8d9010de7d062c941db44164b94cee6de8a6b8b5f975dd1fbf3aec865499c753`. Baseline binary SHA-256 `fa8a8397276c53bad85d5f9993301122453adf4935cad4e8c47173a060f21eed`; original moduleinfo SHA-256 `f41c17bbffc177e4fb96fe778f682b9288744b6a08659dca3a5389a44ac37d3e`. The real baseline had JUCE trailing commas and passed the new local staged-copy repackage, strict JSON parse and ZIP CRC; original bundle bytes were not modified. PR #4 pins JUCE 8.0.12, makes the CMake target VST3-only, adds PR/main/manual Windows validation, a fail-closed one-bundle/AMD64 PE32+ packager, 10 regression tests, pluginval strictness 5, provenance, SHA256 sidecars and 30-day preview retention. Local packager tests 10/10 passed; real baseline repackage passed. Quick4 kit restored with JUCE 8.0.12. No local full plugin build or screenshot claimed because the container could not resolve `github.com`. Exact-head Windows run #44053093571 and real-editor Guided Tour run #44053093565 are in progress; no new artifact or screenshots claimed yet. The superseded PR build run #44052919418 was cancelled by PR-only concurrency; older Guided Tour run #44052919426 remains in progress (no direct cancellation action available). No CTest/DSP suite or root LICENSE/COPYING/NOTICE exists; VST3 vendor URL and support email are blank. | Finish exact-head Windows build, package tests, pluginval 5 and artifact/hash inspection; inspect the four current-head UI screenshots; then add DSP CTest/NaN/denormal/clipping/bypass/CPU coverage, FL Studio and musical A/B; obtain license/contact approval and verify installer/SkellyHub rollback. |
| Skell EQ — skell-eq-vst | 2026-11-17 (selected; A/B state regression integrated and exact-head Windows package verified) | Draft PR #11, branch `release/eq-vst3-ab-state-integration-20261117`, head `17083497a48f27ee767b37bd4776acd79dd81b1f`, based on PR #9 release-hardening head `fe35edb7720b17b1120b5394cad79d1b3ee3aae0`. Exact-head Windows run #44030332461 passed Release VST3 build, all 4 CTests (including `SkellyEQStateRoundtrip`), staged-bundle verifier, pluginval strictness 5, provenance and upload. Artifact #14305256971 (`SkellyEQ-V2.7-Windows-VST3`, 2,089,242 bytes, 14-day retention) independently inspected: valid ZIP CRC; exactly one flat v2.7.0 `Skelly EQ.vst3`; strict JSON moduleinfo; two unique class IDs; one AMD64 PE32+ module (4,513,280 bytes); no Standalone or nested ZIP; all three SHA256SUMS entries match. Archive SHA-256 `3be64d6fdf824a772f36f0de7d4ae90d6305be82aae692b7cdfca7346e3c2ee1`; binary SHA-256 `84c697f35c6caea1384fb23ecca75889b63014725e19480bf492560263d1cc0c`; moduleinfo SHA-256 `02e6db2008db4a5cd2344df17d8053cb41cd7f5c98b2f290899842e8e1b5eb87`; manifest records source commit `17083497a48f27ee767b37bd4776acd79dd81b1f`, CI checkout merge commit `ebf94bfddb7b84624b4c89895f445debb6097704`, and run #44030332461. PR #9 and #10 remain untouched/open. Artifact is PREVIEW_ONLY. Quick4 persistent kit was restored locally (JUCE 8.0.12 + pinned SkellCore), but EQ is not yet wired in the Quick4 router, current EQ source is not locally checked out, and required Linux JUCE development packages are missing; no EQ Quick4 screenshot claimed. Repository root has no LICENSE/COPYING/NOTICE and moduleinfo vendor URL/support email are blank. | Implement/compile the repo-specific opt-in local Quick4 renderer and router entry when current source and Linux dependencies are available; capture/inspect four real editor scenes. Then FL Studio scan/load/save/reopen, automation and old-project recall, musical A/B, target-hardware CPU/latency, licensing/support metadata, SkellyHub rollback. |
| Skell Spacer — skell-spacer-vst | 2026-11-16 (V17 RC packaging candidate; exact-head CI/artifact independently checked) | PR #7 head `3e85ce55e58575e526c73caa603434789d0500b7`; run #43865954713 passed parameter-ID compatibility, DSP/stress/zero-allocation tests, CPU matrix, offline 15-second dry/key/processed WAVs, Windows build, real JUCE editor audit, pluginval strictness 5 and provenance. Artifact #14226276938: one flat `Skell Spacer.vst3`, v1.2.0, AMD64 PE32+, module 3,825,664 bytes, SHA-256 `18ea0f559660ecc91f4d878cce7cbde9081f76240631df31d040f6f278680be1`; archive digest `b3350788419bc8d368577b356fff06d1002f7789686908e7d1ef566b02628e07`. Moduleinfo uses Steinberg JSON5 trailing commas. UI artifact #14225352982 (18 screenshots), DSP/audio/CPU artifact #14225861051 and pluginval log #14226436643 exist. Manifest still blocks FL Studio, Quick4 local renderer, user A/B, target hardware CPU, host-state reopen, licensing, installer/updater rollback, storefront, vendor URL/support email. | FL Studio sidechain/state reopen; inspect all 18 editor captures and real Quick4; user audio A/B; target-hardware CPU; licensing and Hub install/update/rollback. |
| Skell Choir — skell-choir-vst | 2026-11-17 (urgent CI regression follow-up) | PR #8 head `d8db48ba400fbbfc8a4ac828ad41aaba6f71d454` run #44163286082 failed at CMake configure because `SOURCE_COMMIT` head SHA was absent from depth-1 synthetic-merge checkout; native DSP/state/UI-stub and 14 package tests passed. Follow-up PR #9 adds `fetch-depth: 0` to the Windows checkout only (commit `3e6634fc5c8655bc620a0907c936679a138bd4bc`); exact-head run #44173099588 is in progress. Prior independently inspected baseline artifact #14279527660 remains the known-good preview; no new artifact is claimed. | Confirm run #44173099588 completes configure, Windows Release VST3 build, one-bundle staging, AMD64 PE32+, pluginval strictness 5, provenance and upload; inspect new artifact and hashes, then FL Studio, Quick4/current-head UI, state/preset recall, musical A/B, CPU/latency and licensing. |
| SkellGlitch — skell-gate-vst | 2026-11-16 (current release selection; substantive implementation) | Prior run #94 / commit `fcac874a963331943b9a267e32a103034b3abeea` failed after VST3 link because workflow still requested removed `SkellGlitch_Standalone.vcxproj` (`MSB1009`). Draft PR #8 latest head `2935ee64180a4a9dde69399a0b4f86747206ce80`: JUCE 8.0.12 exact pin, Windows VST3-only workflow, JSON5-aware fail-closed package verifier, 13 tests, Windows Python setup, pluginval strictness 5, actual PR-head SHA + Actions run ID/attempt/event/ref in manifest, real JUCE UI smoke and flat bundle+manifest artifact. Run #97 (#43936168153): Linux verifier tests and C++ DSP CTest passed; Windows checkout/configure is in progress. Runs #95/#96 were superseded by newer PR heads; no Glitch binary/artifact or FL Studio acceptance verified yet. | Complete exact-head Windows MSVC build, UI smoke, bundle verifier, pluginval and artifact inspection; then FL Studio state/automation and audio A/B. |
| Skell Cast — skell-cast-vst | 2026-11-17 (selected; substantive release-packaging and host-compatibility implementation) | Draft PR #4: https://github.com/skellyruno/skell-cast-vst/pull/4, branch `release/cast-vst3-manifest-20261116b`, head `33ad4f499f6424b585b45dfc6f3d57a3d3c61b84`, based on main `2c7aa7a1ca5e19f22c3738269130ccf31bc21242`. Preserved baseline: Actions run #43776801697, artifact #14186867360, 2,490,074-byte archive SHA-256 `8704574f6e1faceb67d63071991244bd0c53dc63db8dd9b1489430611f81d7fc`; binary `SkellCast.vst3/Contents/x86_64-win/SkellCast.vst3`, 5,473,792 bytes, SHA-256 `a0cd341fe1baa7aa24e43de41695287b722570ac15cc54fb73f2bda04ed7e185`, AMD64 PE32+; moduleinfo SHA-256 `2273784a4f863049745f7d6ce25755bdd419ebc2e6b520598cd917cde14e1af4` and fails strict JSON because of JUCE trailing commas. PR #4 adds an isolated staged-copy normalizer/verifier, exact single Release bundle + AMD64 PE32+ + unique processor/controller CIDs, 13 Python stdlib tests, build provenance separating PR-head SHA from CI merge SHA, readiness and preview-only notices, SHA256SUMS, backup-safe local staging, pluginval strictness 5, and a host program name fix (`getProgramName(0)` returns `Default`). A source contract also protects the global sharing opt-in default (OFF); no DSP, UI, program count, parameter IDs or saved state were changed. Local package tests passed 13/13; staging the actual baseline passed, strict JSON parses in the staged copy, source metadata is unchanged and all generated hashes recompute. Portable CMake core-only harness compiled the repository's `AudioFifo`, `OutputRouting`, `OutputSelection` and `core_tests.cpp` with GCC 14.2; CTest passed 1/1 in Release and 1/1 with ASan/UBSan. These are not a full plugin build. Latest exact-head Windows run #44022455337 has CMake configure passed and Release build in progress; CTest, 13 package tests, pluginval and artifact upload are pending. Earlier superseded PR-only runs were automatically cancelled by the PR concurrency group. Superseded PR #3 was closed unmerged after moving release tools from `tools/` to `packaging/`; its unrelated SkellCore generator workflow failed because `tools/test_new_plugin.py` expected `SkellCompressorAudioProcessor` while this repository's source class is `SkellCastProcessor`. The failure is not in PR #4's changed-file set. Vendor URL/support email remain blank; licensing, global-sharing consent wording, FL Studio/OBS/WASAPI, real pass-through A/B, target-hardware CPU/latency, signing, installer, updater and rollback remain open. | Finish exact-head Windows build/CTest/13 package tests/pluginval 5 and upload; download and independently inspect the new artifact, strict JSON, module identity and every checksum; then FL Studio/OBS/WASAPI and old-project/state/automation acceptance. |
| Skel Pad / Scratch — skell-scratch-vst | 2026-11-15 (reported) | Prior checkpoint reported VST3-only PR; no binary rechecked. | Verify exact plugin identity, artifact and host load. |
| Skell Separator — skell-separator-vst | 2026-11-16 (selected this checkpoint; substantive Windows release-gate implementation now built and packaged) | Draft PR #4 head `68cf4cf8d687a7d56f2e78714661b5270e4df508`, branch `release/separator-vst3-artifact-gate-20261115`. Exact-head Windows run #44013800819 passed 11 verifier tests, CMake, Release build, staging, pluginval 1.0.4 strictness 5 and upload. Artifact #14298141483: 3,368,575 bytes, SHA-256 `03febf7fb4373caab72345951f0c5c7ae773418122057eb90cfc14980d344891`; independently inspected: one flat `Skell Separator.vst3`, v1.13.0, Skell Audio, one AMD64 PE32+ module 7,853,056 bytes, binary SHA-256 `537e0af1e80517740f5ca7b3227f995a91ca491f9832ed035a7a81381fe120be`, two unique class IDs, strict normalized JSON, all five checksums matched, no nested ZIP. Pluginval report #14297627624 ends in SUCCESS; its optional external VST3-validator subtest was skipped because no validator path was configured. Neural/ASan run #44013800868 passed all 17 steps. Real JUCE screenshot run #44013801079 passed; artifact #14298141489 (715,520 bytes, SHA-256 `e5d45c74a8a3dddbd15843d5a3fcaec3dc15ac2c29c156165617fe3d9abebbeb`) contains eight screenshots + manifest; representative standard/compact/large/bypass/neural/solo/tour captures inspected with no clipping or overlap. | FL Studio scan/load/bypass/automation/save-reopen and old-project compatibility; real vocal/music A/B; target-hardware CPU/latency and real-stem dropout tests; optional Steinberg VST3 validator path; Quick4 local renderer; license, vendor URL/support email, Hub updater/rollback and storefront. |
| Skell Stop / StopDial — skell-stop-vst | 2026-11-17 (selected; safe Windows install/update/rollback) | Preserved draft PR #3, branch `release/stopdial-vst3-package-guard-20261116`, head `381038d37b429813a9c629650ce765f9d184444f`. Its exact-head run #44028239371 passed Linux sanitizer DSP and Windows configure/Release build, JUCE DSP/host CTest, 10 package-verifier tests, one-bundle staging, pluginval strictness 5, screenshot capture and upload. Baseline artifact #14303823607: archive SHA-256 `2de54d9ffbf66bcbf7a6798dc76aa24cf47ea372187b0c7179e09c29611e01c3`; one StopDial v2.3.1 VST3; AMD64 PE32+ module 6,572,544 bytes, SHA-256 `d28339f145baa5bb70b7f7ba34927a0f724277c7b5d9bc1f38e0c52e32ae5d59`. Manifest preserves source commit `0eec59e9d5d3d463f2c1bef8e2afd87a15b72894` and PR head `381038d37b429813a9c629650ce765f9d184444f`. Independent archive inspection confirmed ZIP integrity, exactly one VST3 module, no EXE/nested ZIP, AMD64 PE32+ and matching manifest hash/size. UI artifact #14304575936 (SHA-256 `f88adac22c6d8f51f6bfeeb580681e68d8b1a3276e1e12476713d5393ac802b5`) was inspected at 435×535, 725×892 and 1087×1338; no visible clipping/overlap. New draft PR #4: https://github.com/skellyruno/skell-stop-vst/pull/4, branch `release/stopdial-safe-install-rollback-20261117`, head `ed92187596b37e7a49886b9f1843c76e35f2507a`, stacked on PR #3 without editing its branch. Adds checksum-verified PowerShell install/update with WhatIf, manifest/moduleinfo/CID/PE32+ checks, staged replacement, timestamped verified backup and explicit rollback; includes helper + install guide + package-wide SHA256SUMS; Windows CI adds 18 install/upgrade/rollback/tamper assertions and extends preview/UI artifact retention to 30 days. No local PowerShell runtime is available; the new test suite is not yet verified. Exact-head push run #44110652422 was pending at this ledger update; earlier intermediate-commit run #44110409942 was still in progress and is not exact-head evidence. | Finish exact-head Windows build, CTest, package verifier, 18 PowerShell assertions, pluginval strictness 5 and upload; independently download the new artifact and verify every checksum/manifest/build SHA. Then FL Studio scan/load, save/reopen, automation/preset recall, real audio A/B, target-hardware CPU/latency, license approval, support email and SkellHub updater/rollback. |
| Skell AdlibLab — skell-adliblab-vst | 2026-11-15 (reported) | Prior checkpoint reported validator smoke tests; no artifact rechecked. | Windows VST3, pluginval, state/preset round-trip and host scan. |
| SkellyTune Mini — skelltune-mini | 2026-11-15 (reported) | Prior checkpoint reported binary-gate PR; no artifact rechecked. | Verify x64 bundle, tuning reference, parameter state and FL Studio. |
| Skell Fan — skell-fan-vst | 2026-11-16 (previous release selection; exact-head pluginval repair now passed) | Preserved baseline artifact #14176270462 from run #43749240041: v1.9.0, one AMD64 PE32+ VST3 module, 9,404,416 bytes, original binary SHA-256 `bfafbc0437d958d637763933a81b1766c790bc8ebd759bae4a0463966b6a284f`, archive SHA-256 `0a383ec17c73246122fd128c746bfd8f983105c3378647842c636b5ef3ccfc95`. PR #10 exposed pluginval strictness 5 failure: program 0 had no name. PR #11 commit `a1ffdaf2354f4929a8680d31439d03bdb87342bd` fixes `getProgramName(0)` to `Chorus - Classic` and corrects its regression assertion. Exact-head Windows run #43944668734 passed source checks, 16 package tests, CMake configure/build, DSP/portable tests, VST3 staging, metadata normalization, AMD64 PE32+ verification and pluginval strictness 5. Artifact #14264828558 is a flat bundle + `build-info.json` + `SHA256SUMS.txt`, size 4,889,994 bytes, archive SHA-256 `0d2e247dc21ad5672eaa9dbbc1d84b5edba80bf6af80436fc7ad0b37e66d58d8`; binary SHA-256 `115cee937f29573d98dd62a0464ec9c5c1792d605cc1cc68c3a776d223a7a39d`. I independently inspected the artifact: one `SkellFan.vst3`, v1.9.0, strict JSON metadata, valid PE signature/machine/PE32+; manifest says PREVIEW_ONLY. UI snapshot artifact #14265127600 digest `866d1a2cb6568e15e3f4b75c0287b127dcf3e7d337ab1e0ca4e6252bee41e461` is available but not inspected in this run. | FL Studio scan/automation/state save-reopen, old-project compatibility, real music A/B, target-hardware CPU/latency, vendor URL/support email and license review; reconcile PR #8 UI and PR #9 VST3 release branch before any release. |
| Skell Flang — skell-flang-vst | Not logged | No current release artifact or CI state independently inspected. | Inventory workflow and Windows bundle; validate modulation stability/CPU and host automation. |
| Skell Afar — skell-afar-vst | 2026-11-16 (release packaging selection; exact-head preview now built and inspected) | Draft PR #9: https://github.com/skellyruno/skell-afar-vst/pull/9, branch `release/afar-vst3-package-only-20261116`, head `c8215b82ab0f8b09036cd2a45967f6a80028037c`, stacked on PR #8 at `1337a2c1f1baa8a41c3ff00621627cbc29e04198`. Exact-head run #44008363338 passed Windows VST3 compile, physics/DSP CTest, six package-verifier tests, single-bundle staging, pluginval strictness 5 and upload; run #44008363339 real-SkellCore headless/sanitizer passed; run #44008363345 actual JUCE Guided Tour screenshot job passed; run #44008363346 portable DSP passed. Artifact #14296195883 (6,100,257 bytes; archive SHA-256 `91777b84aad024b8015b7b510ffb53c3414aee74d2091d0adccbc955ac0d8f80`) independently inspected: one `Skell-Afar.vst3`, v0.6.0, one AMD64 PE32+ module 6,096,896 bytes, binary SHA-256 `141df41650f510b5cbf49210f34c8a359fa9049481f5686fb397336a5275340f`, strict normalized JSON, 2 unique class IDs, all 5 sidecar checksums matched; artifact is flat and PREVIEW_ONLY. Vendor URL/support email are blank. Shared SkellCore v0.7.0 true-peak/intersample issue #32 remains a mastering/limiter blocker; FL Studio host, old preset/state/automation recall, real vocal A/B, CPU/latency, licensing and commercial contact approval remain unverified. | Resolve/accept SkellCore issue #32 and verify real vocal A/B; FL Studio scan/load/state recall and old projects; target-hardware CPU/latency; license and approved vendor/support details before any production release. |
| Skell Maw — skell-maw-vst | 2026-11-17 (previous Release & Launch selection; install-guide follow-up) | Baseline PR #3 exact-head run #44031640565 passed Windows x64 build, package checks and all seven pluginval strictness-5 checks; artifact #14306008513 was independently inspected (seven AMD64 PE32+ VST3s, 14 unique CIDs, 16 SHA-256 entries; ZIP SHA-256 `efe0d67b4c60a2a7fd2e5e0ec169f5b8359b2f00bc58a441bcb28bb9d46e582f`). New draft PR #5 head `b19f46e3da3b12f0ad58a515b51d7700e52480a2`, run #44078225191, failed the Windows package-validator test with `KeyError: 'WINDOWS-VST3-INSTALL.txt'`; later staging/pluginval/upload steps were skipped. | Fix the install-guide checksum/manifest regression on an owned branch; rerun exact-head Windows package tests + seven pluginval checks and independently inspect the resulting artifact; then FL Studio and commercial metadata. |
| Skell Necromancer — skell-necromancer-vst | 2026-11-17 (previous selection; current packaging branch not selected while its recent head is under active review) | Preserved PR #1 DSP/UI baseline `44e511247ac0331115dedb9c4464bc980dfb9694`. Draft PR #2 branch `release/necromancer-vst3-package-retention-20261117` is now at head `056b8abb1a516238aac70f094c61a3073ee1ad59`; exact-head Windows run #44037583647 passed build, DSP CTests, source/UI geometry, LUFS/true-peak references and real JUCE screenshots/rune motion, but failed the package-verifier suite at `tests/test_vst3_packager.py:89` in `test_packages_one_valid_x64_bundle_with_manifest_and_checksum`. The archive contains the separately licensed root-level `THIRD_PARTY_NOTICES/OFL-Montserrat.txt`; the test incorrectly requires every ZIP entry to begin with the VST3 bundle path. Packaging/upload and pluginval were skipped; no new artifact exists. Preserve the font notice and fix the archive-layout assertion on the owning branch; do not edit PR #2 concurrently. | Correct the package test to allow only the expected root-level OFL notice (or deliberately place it inside the bundle), prove notice preservation and exact one-bundle/one-module layout, then rerun Windows build, package tests, pluginval 5 and independent artifact inspection. Follow with FL Studio, state/automation/preset recall, audio A/B, CPU/latency, licensing and approved support metadata. |
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
**Current selection: Skell Delay — draft PR #9.** Delay was selected over the other candidates because its exact-head release PR #7 had a confirmed metadata-gate failure: run #43908905273 passed Windows build, CTest and pluginval strictness 10, then failed the parser on JUCE's generated trailing commas. The older Windows CTest stack overflow was separately fixed in PR #2; its fresh exact-head run #43909229094 passed Windows/Linux/macOS build, CTest and pluginval 10. This is a near-release packaging defect, distinct from the older DSP/state chain. Master remains a serious DSP safety blocker; Key still has a pluginval exit-status discrepancy; Choir's corrected exact-head package gate now passes but still lacks FL Studio acceptance.

Upstream [PR #7](https://github.com/skellyruno/skell-delay-vst/pull/7) is now at head `7879d32b44800f3a14eb51d846b484335027f95b`. It adds `System.Text.Json` AllowTrailingCommas normalization followed by strict reparsing and native macOS AU validation with `auval`. Exact-head run #43982892665: Linux passed; Windows failed because the PowerShell regression probe calls a `JsonSerializer.Serialize` overload that does not exist for `JsonElement`; macOS remains in progress. Our separate PR #9 replaces that PowerShell verifier with the tested Python staging gate.

Our [draft PR #9](https://github.com/skellyruno/skell-delay-vst/pull/9) is on branch `release/delay-package-provenance-20261116`, head `5a148e78213d099a912d6956912b8e561f137654`, stacked on the updated PR #7 head. It adds `scripts/verify_windows_vst3.py` and `tests/test_release_package.py`, runs the tests on Windows, stages the VST3 into a fresh `package/` folder, normalizes only the staged metadata, validates exact bundle/module count, product/vendor/version, unique component/controller CIDs and AMD64 PE32+ DLL structure, then writes `build-info.json` and `SHA256SUMS.txt` only after pluginval strictness 10. The first run #43983221858 failed the unit-test step because the test CMake fixture put COMPANY_NAME and PRODUCT_NAME on one line; the real CMake uses separate property lines. That fixture was corrected in commit `6d2cdbf3d7141afabecd1906ba0306377459353a`. Run #43983322085 passed Windows package-verifier tests and CMake configure but remains in progress on its older head. The latest workflow commit `5a148e78213d099a912d6956912b8e561f137654` makes non-Windows uploaded plugin artifacts VST3-only; new exact-head run #43984652327 is in progress: Windows package-verifier tests passed; Windows package-verifier tests and all three Configure steps passed; Windows/Linux/macOS Release builds are running; superseded run #43983322085 was automatically cancelled by PR concurrency. No completed build, CTest, pluginval or new Delay artifact is claimed yet. The superseded stale-head PR #8 was closed without merging and points to PR #9.

The previous Windows baseline artifact #14246574699 from PR #2 run #43909229094 was independently downloaded and inspected: archive SHA-256 `8bbfaeab36b00b112482c168bcd93291d3b613580fa20b7ac4f24527ed49af87`; one `Skell-Delay.vst3` bundle; AMD64 PE32+ DLL 8,943,104 bytes, SHA-256 `6ba2d21beb46920767c1ec261072bebf644dd3de8385288c626912f41afe8954`; metadata identity `Skell-Delay / Skelly Audio / 1.0.0`. It is a preserved preview baseline, not a release; its JUCE-generated metadata contains trailing commas and it lacks the new provenance manifest.

Skell Choir's corrected exact-head run #43973500170 now passed both Windows package and native-tests jobs, including the 14 package-verifier tests. New artifact #14279527660 was downloaded and independently inspected: ZIP 5,240,853 bytes, SHA-256 `7c2e310df10ffa7f8e7d568f66d0369e4a0485ce42025cad0e80e1db3536e955`; four direct files (one VST3 bundle, strict moduleinfo.json, build-info.json and SHA256SUMS.txt), no nested ZIP or EXE. The module is AMD64 PE32+, 10,593,280 bytes, SHA-256 `921c7b7599e14a8047f745ab0f15b1eb70b8c9a31573dc2f35f2b043b49cd2d1`; all three sidecar checksums match. Manifest remains PREVIEW_ONLY. FL Studio, real music A/B, target-hardware CPU/latency, current-head Quick4 UI, licensing, vendor/support metadata and Hub rollback remain open.

The latest Preset Audit did not promote Alchemist Factory 49: its spectral error improved from 0.486 to 0.454 dB, but dynamic-envelope error worsened from 3.523 to 3.595 dB. Factory 48 remains the champion. The latest website work is V83 Artist, V84 Creative and V23 Showcase; source tests pass, but browser/GPU/mobile acceptance and deployment remain unverified.

**Next run:** rotate to Skell Master, not Delay again, unless Delay develops a critical new regression. First inspect branch ownership. Prioritize true-peak protection because the Preset Audit reports approximately +0.464 dBTP overshoot in a synthetic near-Nyquist stress case and an 11-sample latency concern; do not claim a mastering limiter release until those are corrected and measured.

No PR was merged. No public release, installation over an existing version, website deployment, DNS change, payment action or irreversible update was performed.



## First product launch readiness matrix

**Lead packaging candidate: Skell Choir 0.9.0 preview.** Its corrected exact-head Windows build/package and native suites passed, and artifact #14279527660 was independently inspected. This is a packaging lead, not a final product selection or release approval.

| Gate | Status | Evidence / next requirement |
|---|---|---|
| Windows build / download | PASS — preview | Artifact [#14279527660](https://github.com/skellyruno/skell-choir-vst/actions/runs/43973500170/artifacts/14279527660); one direct VST3 bundle, build-info and SHA256SUMS. Not public. |
| Verified sound / A-B | UNVERIFIED | Real music A/B and owner listening approval not completed. |
| Host compatibility | UNVERIFIED | FL Studio scan, automation, state save/reopen and old-project compatibility not run. |
| Stable presets | UNVERIFIED | Preset compatibility and host recall require validation. |\n| UI / Quick4 | UNVERIFIED | Persistent Quick4 kit restored; current Delay pin is JUCE 8.0.17-security, but kit contains 8.0.12 and no Delay renderer target. Do not reuse Master screenshots. |
| Licensing / attribution | UNVERIFIED | Third-party notices and redistribution rights require review. |
| Updater / rollback | UNVERIFIED | SkellyHub install, update, backup and rollback not exercised. |
| Website storefront / email signup | UNVERIFIED | Website source checks pass; browser, storefront and signup acceptance remain outstanding. |
| Release notes | UNVERIFIED | Final versioned notes not approved. |
| Support / contact | BLOCKED | Vendor URL and support email are blank in current plugin metadata. |
| Pricing / trial | OWNER APPROVAL REQUIRED | Pricing, trial length and commercial terms must be approved by the user. |

A green build or downloadable Actions artifact is not a commercial release. Keep this candidate private until every gate is independently closed.


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
