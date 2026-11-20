## Release & Launch checkpoint 55 — 2026-11-20 05:05 ET

### Selected project: Skell-Snap (skell-snap)

Selected after SkellyChoir checkpoint 54. The user had just created this repository and requested the Windows VST3 action, so it took priority over another older plugin. Before touching it, GitHub showed no open issues or PRs, a public repository, and no active branch beyond the existing owner preview-verification branch. The previous main-branch Windows workflow #44711196611 had already completed successfully, but the installable package was withheld because Actions artifacts from a public repository are public. This run added source-input provenance on a new focused draft branch rather than modifying main or the existing branch.

### Cross-automation and branch ownership

- Skelly Ecosystem Development was in progress during this run; its latest completed result recorded in checkpoint 54 selected PitchNet PR #1. Its active branches were left untouched.
- Skelly Preset Quality Audit was also in progress; its latest usable completed result recorded in checkpoint 54 was Run 11. Active Preset/Master/EQ branches were left untouched.
- Skelly Websites Development was disabled; its latest completed result recorded in checkpoint 54 was V125. No website, DNS or deployment work was performed.
- The latest available nightly blueprint report recorded zero verified commercial releases and zero verified revenue. No pricing, payment or public-launch action was taken.
- Candidate checks showed active recent work on Fan, Flang, Afar, Spacer, Separator, Cast, Necromancer and Maw. Those branches/PR chains were not edited. DeEsser remains parked.

### Protected source baseline

- Repository: https://github.com/skellyruno/skell-snap
- Main baseline: `3cee6cd7b7406d4936ccd7ae2937566dfe579140`
- Preserved source archive: `source-archive/skell-snap.zip`, 25,284 bytes, Git blob SHA `8b0bad343fbfdcd004e9685eb18f0d6a5a7cf6eb`.
- The original ZIP was not modified. The Windows workflow extracts it into a temporary build tree and applies the existing idempotent default-program-name overlay; the source archive remains byte-for-byte in the repository.
- Existing branch `release/verify-windows-vst3-private-preview-20261120` was not modified.
- No product artifact was available to back up or deliver; both successful public runs intentionally withheld the installable VST3.

### Main-branch Windows action

[Run #44711196611](https://github.com/skellyruno/skell-snap/actions/runs/44711196611) completed SUCCESS on main commit `3cee6cd7b7406d4936ccd7ae2937566dfe579140`.

- Default-program-name patch self-test: PASS and idempotent.
- VST3 verifier self-test: PASS.
- Portable DSP test executable built and ran: PASS.
- JUCE configure and Windows x64 Release VST3 build: PASS.
- Exact bundle, moduleinfo, class-ID and AMD64 PE32+ verification: PASS; version 0.1.0, two classes.
- pluginval v2.0.0-beta3 strictness 5: 1 passed, 0 failed.
- Product upload: SKIPPED because the repository is public; artifact list empty.
- Built module SHA-256: `84661b3cf8e50ba584c2b30bba65348cbffc1d4c9a5dd257e35385bef0625bf6`.

### New release-provenance implementation

Draft product PR #2: https://github.com/skellyruno/skell-snap/pull/2

- Branch: `release/snap-provenance-source-inputs-20261120`
- Base: main commit `3cee6cd7b7406d4936ccd7ae2937566dfe579140`
- Commit: `1f3a30bf53a7d2669f6578aa956ebf3dde4ab092`
- Four files changed in one commit: `.github/workflows/windows-vst3.yml`, `scripts/verify-vst3-bundle.ps1`, `README.md`, and `BUILDING.md`.
- The verifier now requires the exact preserved source ZIP and the exact PowerShell program-name overlay, checks both inputs exist and are non-empty, and records each input's path, size and SHA-256 in `release-manifest.json` beside the built module hash.
- Self-tests verify the recorded source/overlay hashes and reject missing source inputs.
- The Windows workflow passes the real archive and overlay paths.
- No DSP, UI, parameter IDs, VST3 class IDs, presets, automation, serialized state or host behavior changed.

### Exact-head validation

[PR #2 Windows VST3 run #44715293897](https://github.com/skellyruno/skell-snap/actions/runs/44715293897) completed SUCCESS on commit `1f3a30bf53a7d2669f6578aa956ebf3dde4ab092`.

- Default-program patch self-test: PASS.
- VST3 verifier self-test, including source-input hash assertions and missing-input rejection: PASS.
- Portable DSP test executable: PASS.
- JUCE configure and Windows x64 Release VST3 build: PASS.
- Bundle/moduleinfo/class-ID/AMD64 PE32+ verification: PASS; version 0.1.0, two classes.
- pluginval v2.0.0-beta3 strictness 5: 1 passed, 0 failed.
- Public artifact withholding notice: PASS; installable upload SKIPPED.
- Actions artifact list: empty; no download link or product binary is claimed.
- Built module SHA-256: `07fdaa8071eef45ed1bf17da81f3ceb3223b1116049d616ebaf48272466d8e12`.

### Release readiness matrix

| Gate | Status |
|---|---|
| Windows x64 VST3 compile | PASS in GitHub Actions |
| Portable DSP tests | PASS in GitHub Actions |
| Bundle/moduleinfo/class IDs/AMD64 PE32+ | PASS in GitHub Actions |
| pluginval strictness 5 | PASS |
| Source archive + overlay provenance self-test | PASS |
| Downloadable installable artifact | NOT AVAILABLE — intentionally withheld on public repository |
| FL Studio scan/load and project recall | UNVERIFIED |
| Real vocal A/B and owner listening | UNVERIFIED |
| Target-PC CPU, latency and glitch checks | UNVERIFIED |
| Quick4 current-source UI capture/inspection | UNVERIFIED; no UI change was made in this run |
| Licensing/attribution and owner-approved notices | UNVERIFIED |
| Private delivery / updater / rollback acceptance | NOT ESTABLISHED |
| Storefront, support contact and pricing/trial | Owner/website decisions pending |

### Next step

Keep PR #2 draft and unmerged. Establish an approved private owner-testing delivery path, then complete FL Studio scan/load, bypass/routing, state and automation recall, project save/reopen, real vocal A/B and target-PC CPU/latency checks. The next release-engineering selection must be a different non-DeEsser project after checking fresh automation ownership and exact-head CI. No merge, tag, public release, website deployment, DNS change or payment operation occurred.
