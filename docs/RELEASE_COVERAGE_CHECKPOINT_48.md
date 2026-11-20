# Skelly Release Coverage — Checkpoint 48

**Recorded:** 2026-11-19, 21:45–21:59 ET  
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
- The combined PR diff from `main` is 11 commits ahead and 0 behind.
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
**Final head at checkpoint:** `d1f80b29f840a3b6c10323216dca6b595dbfe95c`  
**Base:** `main`  
**PR #8 remains open and draft** as the preserved VST3-only base. Neither PR was merged.

Three focused commits:
- `780caf9e38fb31497b91457bd9d251f9db8dcf0c` — make checksum creation exclusive; clean only this invocation's generated archive/checksum files after failure; allow safe retry in the same workspace.
- `229263e3d497fabdc075318325d5fd3c0420cbdf` — withhold the product ZIP from public repositories; add regression coverage and clarify the README.
- `d1f80b29f840a3b6c10323216dca6b595dbfe95c` — run exact-head CI on `release/**` branch pushes and test the trigger.

Files changed:
- `scripts/package_windows_vst3.py`
- `tests/test_release_archive.py`
- `.github/workflows/build.yml`
- `README.md`

No C++ DSP, UI, parameter IDs, plugin IDs, presets, serialized host state, VST3 binary, CMake target or FL Studio project changed.

## Test and CI status at checkpoint time

- Local Python archive/workflow regression suite: **14/14 passed**.
- Workflow YAML syntax parse: **passed** using PyYAML BaseLoader.
- Exact-head GitHub Actions [run #44663783061](https://github.com/skellyruno/skell-gate-vst/actions/runs/44663783061):
  - Portable release-verifier/archive tests: **PASS**.
  - Portable C++ DSP configure/build/CTest: **PASS**.
  - Windows JUCE/SkellCore configure: **PASS**.
  - Windows MSVC VST3/UI smoke compilation: **IN PROGRESS**.
  - Windows CTest, four-size JUCE UI smoke, exact VST3 package verifier, pluginval strictness 5, deterministic ZIP generation and artifact-withholding step: **PENDING**.
- Previous PR #8 exact-head Windows evidence remains valid for its own source head only; it is not treated as validation of PR #9.

## Distribution-safety decision

The product ZIP is now uploaded only when `github.event.repository.private == true`. The repository is currently public, so CI should build and verify the ZIP but skip the product-artifact upload. UI screenshots remain a separate inspectable artifact.

No repository visibility change, artifact deletion, public release, tag, merge, website deployment, DNS change, payment action or installer execution occurred. The older PR #8 artifact remains public; this guard does not make it private. No new product download link is claimed.

## Release readiness matrix

| Gate | Status at checkpoint | Evidence / next action |
|---|---|---|
| Windows VST3 build/download | Partial | PR #8 passed; combined PR #9 Windows build still running. Product ZIP withheld while repository is public. |
| Verified sound / DSP | Partial | Portable DSP CTests passed; no owner listening or musical A/B. |
| Host compatibility | UNVERIFIED | FL Studio scan/load, bypass, state recall and save/reopen still require owner machine. |
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
| Verified output | PR #8 exact-head Windows build/pluginval/UI smoke passed; prior artifact #14262560702 preserved. PR #9 local tests 14/14 and portable GitHub job passed; Windows job pending. |
| Oldest blocker | Private delivery path, then owner-side FL Studio/audio/state/hardware acceptance and commercial licensing/contact approval. |
| Next test | Complete PR #9 Windows build, CTest, real UI smoke, package verification and pluginval; verify public-repo product upload is skipped; then owner-side FL Studio and real-audio acceptance. |

## Rotation commitment

SkellGlitch is the current non-DeEsser selection. The next run must select a **different** non-DeEsser project unless a new critical regression appears. Keep DeEsser parked. Over the next six executions, deliver substantive implementation on at least three distinct non-DeEsser plugins when repository access permits; read-only audits and ledger updates do not count.
