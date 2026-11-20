# Skelly Release Coverage — Checkpoint 48

**Recorded:** 2026-11-19, 21:45–22:06 ET  
**Selected project:** SkellGlitch  
**Repository:** https://github.com/skellyruno/skell-gate-vst  
**Product PR:** https://github.com/skellyruno/skell-gate-vst/pull/9

This checkpoint is append-only. It supplements checkpoint 47 and updates only the current execution row in the rolling coverage matrix; earlier checkpoint records and protected product branches remain intact.

## Selection and evidence

SkellGlitch was selected after SkellyChoir to continue the required non-DeEsser plugin rotation. It beat the other candidates because it had a near-ready Windows VST3 baseline and a specific, reproducible release-pipeline blocker: the deterministic preview-archive PR was stacked on the VST3-only branch, while the workflow accepted pull requests only when their base was `main`. PR #9 therefore had no exact-head Actions run.

The source review also found a concrete archive recovery defect: after ZIP creation failed, the generated `SHA256SUMS.txt` remained in the package directory and blocked retry. Separately, the repository is public, so uploading a product ZIP as a GitHub Actions artifact would not be a private download.

Evidence:
- PR #8 exact head `2935ee64180a4a9dde69399a0b4f86747206ce80` passed Windows x64 VST3 compilation, CTest, actual JUCE UI smoke at four sizes, package verification and pluginval strictness 5 in [run #43936168153](https://github.com/skellyruno/skell-gate-vst/actions/runs/43936168153).
- PR #9 originally targeted `release/glitch-vst3-only-20261116`, and the exact-head query returned zero workflow runs for its stacked head `1bd8e71f4deb4505434c44719694be24414fe0cf`.
- The combined PR diff from `main` is 12 commits ahead and 0 behind.
- The repository API reports `private: false`. The older PR #8 product artifact #14262560702 is publicly accessible; the new workflow cannot retroactively restrict it.

## Cross-automation and branch-ownership check

- **Ecosystem Development:** latest completed report, November 19 at 21:08 ET, worked on AdlibLab commercial release gates (PR #12). Its existing Windows VST3/package/pluginval baseline passed; screenshot capture was still running. Next workstream: Foundation (SkellForge, SkellNative and SkellCore). No SkellGlitch branch was reported active.
- **Preset Quality Audit:** latest completed report, Run 11, worked on Alchemist reference alignment, Skell Preset bank/state tests, Skell Rack, Skell EQ and Skell Master. Three Windows builds were still running. A newer scheduled run was in progress with no completed result available at selection time. No SkellGlitch branch was reported active.
- **Websites Development:** V120 completed Creative V105 pointer-performance work, three-site regression checks, and Quick4/JUCE 8.0.12 restoration. No plugin repository was changed.
- **Blueprint Nightly Review:** November 19 review reports zero verified commercial releases; Skell Delay remains the first owner-side FL Studio acceptance candidate, with SkellyChoir second. SkellForge/SkellNative foundation work remains separate.
- **Skell Studio Verified Upgrade:** the monitoring task was already disabled after its November 13 merge and post-merge CI checks; no new Studio work was inferred.
- **GitHub ownership:** Delay had recent push activity and an active legal/installer PR chain; Key, Afar, Silence, Spacer and Flang had existing open release branches. Preset/Master/EQ remain with the Preset lane. SkellGlitch's PR #8/#9 branches had no newer commits since November 17 before this run, and no other automation reported editing them. No other agent's branch was modified.

## Source and packaging changes

**Existing draft PR #9:** https://github.com/skellyruno/skell-gate-vst/pull/9  
**Branch:** `release/glitch-deterministic-preview-archive-20261117`  
**Final head at checkpoint:** `f414bd4b1dc5e20c472605d89bd14280967ed2ba`  
**Base:** `main`  
**PR #8 remains open and draft** as the preserved VST3-only base. Neither PR was merged.

Four focused commits:
- `780caf9e38fb31497b91457bd9d251f9db8dcf0c` — make checksum creation exclusive; clean only this invocation's generated archive/checksum files after failure; allow safe retry in the same workspace.
- `229263e3d497fabdc075318325d5fd3c0420cbdf` — withhold the product ZIP from public repositories; add regression coverage and clarify the README.
- `d1f80b29f840a3b6c10323216dca6b595dbfe95c` — run exact-head CI on `release/**` branch pushes and test the trigger.
- `f414bd4b1dc5e20c472605d89bd14280967ed2ba` — upgrade checkout/setup-python/upload-artifact to Node 24-compatible majors; add a regression test rejecting the legacy majors.

Files changed:
- `scripts/package_windows_vst3.py`
- `tests/test_release_archive.py`
- `.github/workflows/build.yml`
- `README.md`

No C++ DSP, UI, parameter IDs, plugin IDs, presets, serialized host state, VST3 binary, CMake target or FL Studio project changed.

## Test and CI status at checkpoint time

**First combined exact-head run — PASS:** [run #44663783061](https://github.com/skellyruno/skell-gate-vst/actions/runs/44663783061), source head `d1f80b29f840a3b6c10323216dca6b595dbfe95c`.
- Linux: 27/27 Python package/archive tests; portable DSP CTest 1/1.
- Windows: JUCE 8.0.12 + pinned SkellCore configure; MSVC Release x64 VST3 and UI-smoke build; Windows CTest 1/1; four-size JUCE UI smoke; strict package verifier; pluginval v2.0.0-beta3 strictness 5 (1 passed / 0 failed); Steinberg VST3 validator exit 0; deterministic ZIP/checksum generation.
- UI host smoke reported 28 factory programs with stable IDs, preset-audio smoke pass, knob automation/live rotary render pass, bypass impulse aligned at 6000 samples, and 256,000 stereo frames processed with reported latency 0.
- Manifest: SkellGlitch 1.7.3 / Skelly, Windows x64, one `SkellGlitch.vst3`, module `Contents/x86_64-win/SkellGlitch.vst3`; module SHA-256 `34221aa9e89f864de734938f9d5b6c7e6823eed76d6a6d55f61fa20c95b37eee`; moduleinfo SHA-256 `81db5ff87d3252d2ca88498c7792a012fcf464a4a12dc31af9d63ca497b41ec2`.
- Deterministic ZIP was generated but not uploaded: SHA-256 `5ed0fe683b96a7307d38d5ec4037188561d6ae0368134b8fa464713e6d93c7ce`.
- Product ZIP upload step: **SKIPPED as intended** because the repository is public. UI artifact [#14597930534](https://github.com/skellyruno/skell-gate-vst/actions/runs/44663783061/artifacts/14597930534): 1,325,078 bytes, SHA-256 `836720272fad85b413d6a3f7d39a518cca44af0b26c3e55dc9bd2475c304d488`.
- Downloaded UI artifact: ZIP CRC passed; all 7 PNGs decoded and SHA-256 recorded. Inspected default at 480×360, 720×540, 960×720 and 1200×900, plus Amethyst, Burst and Settings. No clipping/overlap; minimum-size text is small but controls remain visible. No UI source changed.

**Node 24 action follow-up:** commit `f414bd4b1dc5e20c472605d89bd14280967ed2ba` upgrades `actions/checkout@v7.0.1`, `actions/setup-python@v7.1.0`, and `actions/upload-artifact@v7.0.2`; each action manifest declares Node 24. A static regression verifies the new majors and rejects the old versions that emitted Node 20 deprecation warnings.

Current exact-head run [#44664854681](https://github.com/skellyruno/skell-gate-vst/actions/runs/44664854681) at head `f414bd4b1dc5e20c472605d89bd14280967ed2ba`:
- Portable Linux job: **PASS**.
- Windows JUCE/SkellCore configure: **PASS**.
- Windows MSVC VST3/UI-smoke compilation: **IN PROGRESS** at ledger update time.
- New-head CTest, UI smoke, pluginval, package and artifact-withholding gates: **PENDING**; no pass is inferred for this head yet.

Previous PR #8 exact-head Windows evidence remains valid for its own source head only; it is not treated as validation of PR #9.

## Distribution-safety decision

The product ZIP is now uploaded only when `github.event.repository.private == true`. The repository is currently public; run #44663783061 built and verified the ZIP and explicitly skipped the product-artifact upload. UI screenshots remain a separate inspectable artifact.

No repository visibility change, artifact deletion, public release, tag, merge, website deployment, DNS change, payment action or installer execution occurred. The older PR #8 artifact remains public; this guard does not make it private. No new product download link is claimed.

## Release readiness matrix

| Gate | Status at checkpoint | Evidence / next action |
|---|---|---|
| Windows VST3 build/download | PASS on first combined head; action-update head pending | PR #9 run #44663783061 passed MSVC VST3, package verification and pluginval; product ZIP generated but withheld because repository is public. Run #44664854681 is rebuilding after Node 24 action updates. |
| Verified sound / DSP | Partial | Portable and Windows CTests passed; pluginval 1/1; automated preset/bypass/latency smoke passed. Real musical A/B and target-PC CPU/latency remain unverified. |
| Host compatibility | Partial / UNVERIFIED | pluginval strictness 5 and native UI smoke passed; FL Studio scan/load, save/reopen and old-project compatibility still require owner machine. |
| Presets / automation / old projects | UNVERIFIED | No owner-side project migration or automation recall performed. |
| Licensing / attribution | BLOCKED | JUCE/VST3/SkellCore and asset notices need final owner/legal approval. |
| Installer / updater / rollback | Partial | Manual install/rollback guide only; no signed installer or SkellyHub updater/rollback. |
| Website storefront / email signup | Separate lane | Websites V120 checked site regressions; storefront purchase/fulfillment not accepted here. |
| Release notes | Partial | PR/README/private-preview note updated; final release notes not approved. |
| Support / contact | BLOCKED | Vendor URL and support email not approved for this product. |
| Pricing / trial | OWNER DECISION | No pricing or trial terms approved. |

## Coverage row — SkellGlitch

| Field | Current record |
|---|---|
| Last selected | 2026-11-19, Checkpoint 48 |
| Verified output | PR #8 baseline retained. PR #9 first combined head run #44663783061 passed Linux 27/27 tests + DSP CTest 1/1 and Windows VST3/CTest/UI smoke/package verifier/pluginval 1/1; UI artifact #14597930534 independently inspected. Node 24 follow-up run #44664854681 has Linux PASS and Windows compile in progress. Product ZIP generated but withheld. |
| Oldest blocker | Private delivery path, then owner-side FL Studio/audio/state/hardware acceptance and commercial licensing/contact approval. |
| Next test | Complete run #44664854681 on the Node 24 action head and verify the warning is gone; then owner-side FL Studio scan/load, state/automation recall, musical A/B, target CPU/latency and private-delivery approval. |

## Rotation commitment

SkellGlitch is the current non-DeEsser selection. The next run must select a **different** non-DeEsser project unless a new critical regression appears. Keep DeEsser parked. Over the next six executions, deliver substantive implementation on at least three distinct non-DeEsser plugins when repository access permits; read-only audits and ledger updates do not count.
