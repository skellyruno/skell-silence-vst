# Skelly release coverage ledger

Updated: 2026-11-16
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
| Skell Silence — skell-silence-vst | 2026-11-16 (current) | Main baseline v2.8 Windows VST3 artifact verified from Actions run 43783806349; PR #14 adds staged-package validation, checksums and PREVIEW_ONLY provenance. FL Studio, current-source Quick4, vendor URL and support email remain open. | Complete PR #14 Windows + portable CI; inspect new artifact/manifest; then FL Studio and Quick4 acceptance. |
| Skell Key — skell-key-vst | 2026-11-16 (prior checkpoint; reported) | Prior checkpoint reported PR #8 and a verified Windows artifact. Host/pluginval strictness 10 and version/vendor metadata remain unverified. | Verify artifact/PR #8 from source; pluginval and FL Studio save/reopen/tuning-sync. |
| Skell Delay — skell-delay-vst | Not logged by Release; Ecosystem work 2026-11-16 | Ecosystem run #11 reports Windows DSP test segfault; PRs #2/#3 are being edited there. No verified Windows VST3 artifact. | Do not overlap PRs #2/#3; inspect their CI diagnostics and fix root cause after owner branch work completes. |
| Skell Preset — skell-preset-vst | Not logged by Release; Preset Audit 2026-11-16 | Preset audit reports commit 4cf0a282 replacing Release-disabled assert checks; CI pending. Deuce/Alchemist reference audio unavailable; reported Studio EQ peak 2.4519 needs follow-up. | Verify Windows tests, EQ peak/gain safety, state recall and original-reference A/B when available. |
| Skell Master — skell-master-vst | Not logged | Open PRs #4 (fail-closed Windows package identity), #3 (sound QA prototypes), #1 (UI/control work). No release decision made here. | Review PR ownership/checks; verify Windows VST3 identity and Deuce A/B before packaging. |
| Skell EQ — skell-eq-vst | Not logged | Open PR #9 covers Windows-only VST3 packaging/binary verification. No artifact independently inspected here. | Review PR #9 CI and inspect actual bundle, metadata, pluginval and host behavior. |
| Skell Spacer — skell-spacer-vst | 2026-11-15 (reported) | Prior checkpoint reported PR #6 Windows build passed; no current artifact rechecked. | Verify PR/build artifact, pluginval, duplicate bundle absence and FL Studio load. |
| Skell Choir — skell-choir-vst | 2026-11-16 (reported) | Prior checkpoint reported validator/regression work; artifact not independently rechecked. | Inspect Windows VST3 package and state/host tests. |
| SkellGlitch — skell-spectre-vst / related repo | 2026-11-16 (reported) | Prior checkpoint reported VST3-only PR; repository mapping and artifact need confirmation. | Confirm exact product repo/PR, then verify Windows binary and package. |
| Skell Cast — skell-cast-vst | 2026-11-15 (reported) | Prior checkpoint reported denormal smoke test; no release artifact rechecked. | Windows VST3 compile, denormal/NaN stress, pluginval and package inspection. |
| Skel Pad / Scratch — skell-scratch-vst | 2026-11-15 (reported) | Prior checkpoint reported VST3-only PR; no binary rechecked. | Verify exact plugin identity, artifact and host load. |
| Skell Separator — skell-separator-vst | 2026-11-15 (reported) | Prior checkpoint reported packaging gate PR; no artifact rechecked. | Windows bundle validation, ONNX/runtime stability and FL Studio latency/crash test. |
| Skell Stop / StopDial — skell-stop-vst | 2026-11-15 (reported) | Prior checkpoint reported VST3-only PR; no artifact rechecked. | Verify plugin naming/IDs, binary and preset/state recall. |
| Skell AdlibLab — skell-adliblab-vst | 2026-11-15 (reported) | Prior checkpoint reported validator smoke tests; no artifact rechecked. | Windows VST3, pluginval, state/preset round-trip and host scan. |
| SkellyTune Mini — skelltune-mini | 2026-11-15 (reported) | Prior checkpoint reported binary-gate PR; no artifact rechecked. | Verify x64 bundle, tuning reference, parameter state and FL Studio. |
| Skell Fan — skell-fan-vst | Not logged | No current release artifact or CI state independently inspected. | Inventory workflow, last successful Windows VST3 artifact, then host and DSP gates. |
| Skell Flang — skell-flang-vst | Not logged | No current release artifact or CI state independently inspected. | Inventory workflow and Windows bundle; validate modulation stability/CPU and host automation. |
| Skell Afar — skell-afar-vst | Not logged | No current release artifact or CI state independently inspected. | Inventory workflow and dependencies; verify package, latency and state recall. |
| Skell Maw — skell-maw-vst | Not logged | No current release artifact or CI state independently inspected. | First release inventory: CI, VST3 target, licensing and baseline binary. |
| Skell Necromancer — skell-necromancer-vst | Not logged | UI/DSP development exists in recent project context; no current release artifact independently inspected. | Verify current UI branch ownership, Windows VST3 build and real editor screenshots. |
| Skell Gate — skell-gate-vst | Not logged | No current release artifact or CI state independently inspected. | Inventory workflow and test bypass, gate timing, denormals and x64 package. |
| Skell Rack — skell-rack-vst | Not logged | No current release artifact or CI state independently inspected. | Inventory plugin format, dependencies, installer/export and host compatibility. |
| Skell AutoTune — skell-autotune-vst | Not logged | Default branch is devin/1778052783-initial-plugin; release baseline and branch purpose need verification. | Confirm branch/PR ownership and JUCE/VST3 packaging before any changes. |
| Skell Spectre — skell-spectre-vst | Not logged | No current release artifact or CI state independently inspected. | Confirm relationship to SkellGlitch, then inspect x64 package and DSP gates. |
| Skell Chess — skell-chess-vst | Not logged | No current release artifact or CI state independently inspected. | Inventory product scope, build target and licensing before release work. |
| BPM Delay Calculator — -bpmdelay-calculator-vst | Not logged | No current release artifact independently inspected. | Verify standalone/VST3 intent, packaging and numerical tests. |
| MuCalc — MuCalc-VST | Not logged | No current release artifact independently inspected. | Verify standalone/VST3 intent, packaging and numerical tests. |
| MetaTuneInspiredvst | Not logged | Reference/inspired project; license/attribution and distributable status unverified. | Audit origin, licenses and whether it is an internal reference or product. |
| EndlessSmileInspired-VST3 | Not logged | Reference/inspired project; license/attribution and distributable status unverified. | Audit origin, licenses and whether it is an internal reference or product. |
| PitchNet | Not logged | Model/dependency provenance and redistribution terms unverified. | Audit dependency/license provenance before bundling or distribution. |
| LYRICFORGE | Not logged | Product role and downloadable deliverable not assessed. | Confirm whether it is part of the Skelly launch portfolio; inventory build/export. |
| FLAMEEWRLD-Studio-Vocal-Chain | Not logged | Chain/reference project; distributable licensing and format unverified. | Confirm ownership and third-party plugin dependencies before packaging. |
| Skell Sound Match — skell-sound-match | Not logged | No current distributable artifact independently inspected. | Inventory Windows build and validate matching references/data dependencies. |
| SkellCore — skellcore-vst-template | Not logged | Ecosystem run #11 reports GuidedTour integration merged; exact release artifact not checked. | Verify shared UI/font/symbol compatibility and pinned revision across consuming plugins. |
| SkellForge — skellforge | Not logged | Ecosystem run #11 reports PR #25 relevant CI passing; no release artifact inspected here. | Inspect Windows native build/export artifact and license notices. |
| SkellNative — skellnative | Not logged | Ecosystem run #11 reports PR #5 Windows VST3/foundation checks passing; host acceptance not established. | Verify JUCE-free VST3 bundle and load in an actual host. |
| SkellLang — skellLang | Not logged | Ecosystem run #11 reports PR #4 at 53/54 tests with one symlink-permission skip. | Resolve/justify skip and verify Windows build/distribution. |
| SkellWorld — SkellWorld | Not logged | Shared AGENTS.md commit reported; no distributable runtime artifact inspected. | Verify opt-in presence protocol, security boundary and installer/runtime packaging. |
| Skell Project Hub — skell-project-hub | Not logged | Ecosystem run #11 reports v2.3 reliability/plugin-verification work; Windows installer/export not checked. | Verify install/update/backup/rollback against real plugin bundles. |
| Skell Studio / DAW — skell-studio | Not logged | Separate Studio automation last recorded Nov 13; Ecosystem run #11 reports ML-first bootstrap draft. No release installer or FLP acceptance verified here. | Windows startup/build, FLP import/open, VST3 hosting, audio-device setup and installer/export. |
| Artist / album website | Not logged | Websites run v70 reports code checks passed; browser playback/mobile acceptance and deployment remain unverified. | Verify actual browser audio playback, release date/tracklist, mobile layout and signup. |
| Skelly Creative / 322-inspired site | Not logged | Websites run v70 reports source audit passed; Chromium/WebGL and domain spelling remain unverified. | Verify browser WebGL/mobile performance and confirm intended domain before deployment. |
| FLP utility suite (Multi, Missing Beat, Zip, Cleaner) | Not logged | Local EXE set referenced in project context; current source/binary hashes and installer not checked here. | Inventory all four baselines, run real FL Studio project safety tests and package one verified Windows EXE. |

## Rotation commitments
1. Current run: Skell Silence (non-DeEsser).
2. Next release run: choose a different project, after checking current branch/PR ownership.
3. Across the next six release runs: substantive implementation on at least three distinct non-DeEsser plugins when authenticated repository access permits.
4. Keep DeEsser parked for the six-run hold unless a critical security or regression emergency is proven.
5. Broaden beyond plugins regularly: Skell Studio/DAW, Project Hub, SkellForge/SkellNative/SkellCore and installers.

## Current release decision
Skell Silence v2.8 is a strong Windows preview candidate: baseline CI and packaged VST3 are verified, but PR #14 CI is still pending. No public release, merge, website deployment, DNS change, payment action or irreversible update is authorized.
