# SKELL SILENCE (`skell-silence-vst`)

An original JUCE 8 / CMake **VST3 + Standalone** audio effect based on the build organization, JUCE pin and CI conventions of [skellyruno/skell-vst-template](https://github.com/skellyruno/skell-vst-template). The plugin detects gaps and inserts tempo-aware sound design. Product: **Skell Silence**, vendor: **Skell Audio**, unique VST3 code: `Sl01`.

## Features in this source release

- Mono/stereo audio effect with optional mono/stereo sidechain bus and MIDI input.
- Dual-speed RMS gap detector with threshold, min/max duration, arm time, recovery hold and decay-aware tail sensitivity.
- AUTO, SIDECHAIN, GRID (subdivision and phase-offset parameters) and MIDI event gates. SIDECHAIN defaults to disabled at the host bus level.
- Input-driven lookahead: Off, 250 ms, 500 ms, one beat, one bar; dry signal delayed to match detector decisions. Host latency is reported using `setLatencySamples`, updated on the message thread. **LOCK retains the selected lookahead latency** rather than toggling plug-in delay compensation while audio is playing; it triggers from the saved PPQ map.
- Seven independently enabled and leveled effects: Tape Stop, Filtered Air, Reverse Swell, Noise Fade, Impact, Riser and Stutter Tail. Default 7×4 matrix follows the supplied spec. The EXTRA LONG impact is placed on the last beat.
- Macro parameters: MIX, TENSION, SPACE and DUCK AFTER (brief transient lift). Gap audio receives a 5 ms edge ramp, a bounded 2-second reverb release and an output soft-peak protector. MIX=0 preserves the dry audio without an extra saturation stage.
- LEARN records gap start/end PPQ positions while playing. LOCK replays saved PPQ gaps; the map is saved in plugin state. Click a mapped region in the 8-second timeline, drag or press Left/Right to nudge, Delete/Backspace to remove. Header **MENU → Reset learned gaps** clears all. When a region is selected, PREVIEW can audition stored history if the host continues calling `processBlock` while stopped.
- Scale-consistent, fixed-ratio 1200×760 base interface with dark negative-space original wordmark, waveform/gap overlays, gap detector monitor, instrument rack, settings popups, editable class boundaries and gap/min count. Default opening size is 1080×684.
- Host-automatable APVTS parameters and `.skellsilence` preset save/load, including the learned gap map and editor size.
- No allocations are made by the custom DSP buffers during `processBlock`. Custom DSP state is preallocated in `prepareToPlay`.

## Build

Use CMake 3.22+ and a C++17 compiler (MSVC on Windows, Clang/Xcode on macOS). JUCE 8.0.12 is fetched automatically from GitHub unless you specify an installed JUCE folder.

**Windows, Visual Studio:**

```powershell
cmake -S . -B build -A x64 -DJUCE_PATH="C:/JUCE"
cmake --build build --config Release --parallel 2
```

Omit `-DJUCE_PATH` for the pinned JUCE 8.0.12 auto-fetch. For GitHub builds, create a `skell-silence-vst` repo and upload the **contents** of this folder, and open **Actions → Build Skell Silence → Run workflow**. The workflow builds a Windows `.vst3` bundle and a standalone executable, then uploads both in one GitHub artifact (one ZIP download, no nested ZIP).

**macOS:**

```bash
cmake -S . -B build -G Xcode
cmake --build build --config Release --parallel 2
```

Expected JUCE build products:

- `build/SkellSilence_artefacts/Release/VST3/Skell Silence.vst3`
- `build/SkellSilence_artefacts/Release/Standalone/Skell Silence.exe` (Windows)
- `build/SkellSilence_artefacts/Release/Standalone/Skell Silence.app` (macOS)

Actual output directory may vary with generator and JUCE configuration. Copy the `.vst3` bundle to the system's VST3 plugin folder, or extract the GitHub artifact once.

## Workflow

1. Place it on a track/bus, allow 250 ms lookahead, and play audio containing clear phrase gaps.
2. Set THRESHOLD, MIN GAP, MAX GAP and HOLD. Use the waveform and detector meter to tune detection.
3. Configure the instruments, edit the 7×4 rule cells, and adjust LENGTH RULES → EDIT RANGES to set each class boundary in beats.
4. Arm **LEARN** while the timeline plays. Stop learning and enable **LOCK** for PPQ-aligned repeatable playback; the map is serialized with the session.
5. Use **TENSION**, **SPACE**, **DUCK AFTER** and **MIX** to blend the results. Export using the DAW's normal bounce workflow with latency compensation enabled.

## Performance / known limitations

This is an **initial implementation**, not a verified commercial-ready release. The C++ DSP-only tests (`tests/run_cpp_tests.sh`) run without JUCE and cover basic gap opening/closing, map edits, fixed lookahead and seven-instrument rendering. **The full JUCE VST3 and Standalone targets have not yet been verified locally**, because JUCE is not installed here and external Git access is unavailable; run the included CI to confirm compilation and test the real DAW build.

The AirNoise spectrum-follow option currently uses a lightweight low-pass shaping model, not the proposed 24-band spectral matching. Tape stop and stutter use a circular sample history and basic interpolation rather than the full Hermite/pitch-coherent engine described in the design brief. The supplied FDN reverb is a compact 8-delay model. This revision uses cached RMS coefficients and a decay-sensitive threshold to lower detector overhead; these improvements remain subject to listening tests. LEARN is bounded to 2,048 PPQ gaps (no heap growth on the audio thread) and assumes a usable host PPQ timeline. Selected mapped-gap editing takes effect on the following audio block. `setLatencySamples` must be observed by the host: latency changes during live playback can produce audible transitions, so choose lookahead before recording/bouncing.

**Host considerations:** Some DAWs do not continue processing effects when transport is stopped; PREVIEW cannot make sound in those hosts until the host processes audio again. MIDI and GRID triggers provide simple gates rather than full user-drawn grid hit maps. The preview reads the retained input history; input history is unavailable before the plugin has received audio.

This plugin uses the operating system's licensed sans-serif fallback font; no third-party font asset is distributed. Custom UI is drawn using JUCE primitives.

## Revision v1.1 / safety and UI improvements

- Reliable relative layout: scaled component transforms preserve label, slider, matrix and clickable hit target proportions at all supported window sizes.
- Improved panel hierarchy, subtly increased contrast, SKELL green trim, descriptive tooltips, and a clearer detection workflow.
- Detector envelope and dB coefficient caching avoid transcendental operations on every audio sample. Tail sensitivity now adapts detection to an actively falling RMS envelope.
- Do not set host-reported latency to zero on LOCK; otherwise toggling LOCK mid-session could desynchronize PDC. One-beat/bar modes still depend on tempo and can require PDC renegotiation on BPM changes.
- Reverb continues releasing for at most two seconds after a gap, then parks processing. MIX=0 remains dry (except normal lookahead delay).
- Preserve the existing shared SkellCore subtree and optional CMake linkage when updating this repository. DSP modules remain separate pending A/B validation.
- CI includes a native DSP test before release packaging. Full VST3 success is determined by GitHub Actions, not the portable test suite alone.

## v1.2 interface and DSP upgrade

- **Compact default:** 912 × 578 (76% of 1200 × 760). All panels share one
  design-space transform. Earlier versions applied scaling to panel coordinates
  *and* their transforms, making the rack overlap and clipping the rule matrix.
  Resize the bottom-right corner or use MENU to select 76%, 90%, 100% or 125%.
- **Interface:** Redesigned header and transport status, 7 visible instrument
  strips, high-contrast custom controls, complete 7 × 4 rule matrix, detector
  envelope strip, clear timeline idle hint, and three dedicated macro controls.
- **DSP:** Stable host PDC within each transport pass (tempo or lookahead
  changes are applied at stop/restart), energy-preserving 8-line FDN mixing,
  cached detector time conversions, and click-free post-gap lift envelopes.
- **Compatibility:** Parameter IDs, all seven instruments, learned-map format,
  presets and existing automation are unchanged.

Known limitations: the model-based spectrum-following air texture and fully
predicted reverse swells remain future work; a live, zero-lookahead detector
cannot know the final length of a gap before its end. Only portable DSP tests
can run without the JUCE dependency; Windows/macOS Actions compile the plugin.
