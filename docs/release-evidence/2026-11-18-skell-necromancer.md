# Skell Necromancer release evidence — 2026-11-18

## Scope and decision

Reviewed the current commercial-release gate and Windows VST3-only target for **Skell Necromancer**. This is a release-readiness record, not a product approval. Both relevant PRs remain draft and unmerged:

- [PR #3 — commercial metadata/license gate](https://github.com/skellyruno/skell-necromancer-vst/pull/3), head `b55e94d719d32463d40528762274299b5fc19ee8`.
- [PR #4 — Windows VST3-only product target](https://github.com/skellyruno/skell-necromancer-vst/pull/4), head `8df3a63cc0c011d435530aeeec13eff0d31bceec`.

**Current status: PREVIEW_ONLY.** The commercial gate is implemented, but the actual package manifest says `commercial_release: false` and `license_file: null`. No product license, vendor URL or support email was supplied.

## Exact-head CI evidence

- PR #3 Windows run [#44056313880](https://github.com/skellyruno/skell-necromancer-vst/actions/runs/44056313880) completed successfully. The job passed Windows configure/build, DSP CTests (8/8), source integrity, reference UI geometry, independent LUFS/8x true-peak checks, package-verifier tests (17/17), package staging, pluginval 1.0.4 strictness 5 and artifact uploads.
- PR #4 Windows run [#44153560771](https://github.com/skellyruno/skell-necromancer-vst/actions/runs/44153560771) completed successfully on the VST3-only head. The job passed configure/build, the explicit VST3-only output check, DSP CTests, source integrity, UI geometry, independent LUFS/8x true-peak checks, real JUCE UI capture/rune-motion verification, package-verifier tests, package staging, pluginval strictness 5 and artifact uploads.

These are GitHub Windows-runner results. They do not establish FL Studio acceptance or target-PC performance.

## Preserved package baseline — PR #4

[Windows VST3 artifact #14361011381](https://github.com/skellyruno/skell-necromancer-vst/actions/runs/44153560771/artifacts/14361011381)

- Downloaded outer artifact: 2,774,024 bytes; SHA-256 `3a9878a83d5fab62cac6ee45e4958c2e9bfcc257e39cfd35e02d62219ec317af` (matches the GitHub artifact digest).
- Outer ZIP CRC passed; it contains the VST3 ZIP, provenance manifest and detached checksum.
- Inner VST3 ZIP: 2,775,047 bytes; SHA-256 `ee5d1dd6f16a75818c5a299ae5418e180e5a818d6e26511f6f4d59b4a43c9890`; CRC passed.
- One flat `Skell-Necromancer.vst3` bundle; no Standalone target or nested ZIP.
- Product `Skell-Necromancer` 0.1.0 / Skell Audio; exactly two distinct expected processor/controller CIDs.
- One Windows module: 5,180,928 bytes, AMD64 PE32+; binary SHA-256 `6d5096ba6d580af35ff6cd88de9de9b606808ad879d7aec83ffef8ffd879e938`.
- Package manifest source head: `8df3a63cc0c011d435530aeeec13eff0d31bceec`; CI checkout merge commit: `e8c00ece98333f2a2864aca78071e7ad94baf721`; workflow run: `44153560771`.
- Manifest explicitly records `commercial_release: false`, `license_file: null`, and no third-party license beyond the bundled Montserrat OFL notice.

This artifact is preserved as a verified Windows preview baseline, not as a distributable commercial build.

## Real UI review

[Real JUCE UI artifact #14361395394](https://github.com/skellyruno/skell-necromancer-vst/actions/runs/44153560771/artifacts/14361395394), 4,096,877 bytes; SHA-256 `ebc1adf099aec357661d0d948115474dff701a8a8e14e932bc4810537ad100a4`.

Inspected four representative surfaces from the actual editor capture:

- Compact: 810×428.
- Default: 1157×612.
- Large: 1736×918.
- Rune animation before/after at 1157×612.

No visible clipping or overlap was found at those sizes. The compact view's secondary labels are dense but remain within their bounds. Menus/popups, alternate theme, live interaction, control-state retention and real-time animation CPU were not captured or exercised; those remain UNVERIFIED. No mockups were generated.

## Commercial gates still open

1. Owner-approved root product `LICENSE` or `COPYING`; the packager's `--commercial-release` mode correctly refuses to proceed without it.
2. Owner-approved HTTPS vendor URL and valid support email in VST3 Factory Info.
3. Upstream JUCE 8.0.12 and pinned SkellCore license/attribution review; the current preview package only embeds the Montserrat OFL notice.
4. A real install/update/backup/rollback path; PR #4 currently produces a VST3 preview ZIP, not an installer.
5. FL Studio scan/load, host PDC, preset/state/automation save-reopen and old-project compatibility.
6. Owner listening and rights-cleared real-audio A/B; the existing LUFS/8x true-peak tests are reference checks, not a mastering-grade certification.
7. Target Windows hardware CPU/latency profiling and code-signing decision.

No legal terms, contact details, price, trial length or distribution permission were invented.

## First-product recommendation

**Keep Skell Key as the provisional first distribution candidate**, not an approved release. Its current draft chain already has a checksum-verified Windows VST3 package plus tested per-user install/update/rollback behavior. Its exact-head preview artifact #14408776507 was independently re-downloaded in this run: 2,168,633 bytes, SHA-256 `d26911874f6891ab1744b9a3c5709104e46705fab8359d1710e4ad05de532513`; ZIP CRC passed, the 4,918,784-byte module is AMD64 PE32+, binary SHA-256 `90cee58ddf11d5ff61f8d49b3a66007ce1fd5d143ce69a5acecf17a3814f792c`, and all 11 package plus 3 tool checksum entries matched. Its own preview notice still says no approved product license, no vendor URL and no support email; FL Studio, Key↔Mini session sync, musical A/B, state recall, target hardware and signing remain open.

Necromancer is a strong second engineering candidate because it has deeper DSP/reference checks and actual editor captures, but it has no installer/rollback yet and makes more demanding mastering-grade claims. Neither product is commercially releasable today.

## Changes in this run

Documentation and release evidence only. No plugin source, DSP, presets, automation IDs, host state, artwork, installer, production binary, website, price or license terms were changed. No PR was merged and no public release was created.
