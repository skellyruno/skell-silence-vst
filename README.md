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

## v1.3 UI and spectral-DSP polish

- **Existing compact geometry preserved:** 912×578 px default, resizable with the same
  1200×760 logical design space. No panel overlap reintroduced.
- The rack now highlights the *currently rendering* instruments, dims disabled
  devices, uses per-effect accent colours for their level controls, and labels
  its LIVE/ARMED state. The rules matrix highlights the active length class.
  Detector state (SOUND/PENDING/GAP/RECOVERING) is shown beside the envelope strip.
- Instrument settings have readable parameter captions and more spacious
  controls. Rotary knobs use vector hardware bezels and accurate position arcs.
- **Filtered Air FOLLOW is no longer a fixed low-pass approximation.** Six
  spectral bands are followed continuously from the incoming source; each
  detected gap stores its pre-gap envelope in its preallocated event record, so
  lookahead doesn't accidentally analyze a *future* hit. The noise generator
  can also use pink-tilted or white spectra, plus a color/brightness control.
- Hermite resampling improves the continuity of tape and granular reads.
  Tape Stop uses inexpensive polynomial slowing curves instead of a per-sample
  power function. Stutter Tail avoids duplicate remainder calculations.
- No new audio parameters or plugin IDs were added; old sessions and presets
  retain their automation and state. All new DSP state is bounded/preallocated.

**Verification:** portable C++17 tests cover spectrum tracking, Hermite reads,
FDN tails, gap events and 192 kHz numerical safety. GCC/Clang and AddressSanitizer/
UBSan runs passed locally. The real JUCE VST3 and DAW session still require the
GitHub Actions build and listening checks; no measured DAW CPU reduction or
commercial-quality separation is claimed here.

## v1.4 UI and audio polish

- Instrument enable indicators inherit the instrument color, and each strip shows a numeric level.
- Timeline recent-gap selection is visible, learned-map markers handle partial display windows, and PREVIEW is unavailable until a recorded gap is selected and playback is stopped.
- On leaving a gap, DUCK AFTER uses the **rendered, delayed** boundary for all trigger modes, including LEARN / LOCK; the audio-thread grid phase uses a one-step accumulator instead of per-sample `fmod`.
- Unprocessed samples pass through unchanged even with MIX above zero (no unnecessary limiting while the effects are silent); MIX zero is bit-exact dry.
- Instrument popups now explain each parameter and support double-click default reset; active-effects UI state is published once per audio block instead of once per sample.
- Reverb damping is adjusted to sample rate without expensive transcendentals in the per-sample loop.

All existing automation IDs and the original compact 912 × 578 initial size are preserved.

## v1.5 stereo and control polish

- **Stereo-aware detection** accumulates L/R signal powers before thresholding, so opposite-phase mixes and sidechains cannot falsely look silent. Mono still uses the same coherent detector.
- Separate pre-gap history, six-band FOLLOW profile, tape/stutter reading, synthesized textures and FDN processing for each channel; L/R ambience and source movement are preserved rather than summing wet to dual-mono. The impact's tonal component remains phase-consistent while noise can decorrelate.
- Tape Stop never advances into the gap after exhausting its pre-gap source; Reverse Swell maps an explicit pre-gap read window over the known gap length, with smooth swell onset. No claim of predicting unknown live gap endpoints without lookahead/map.
- Riser curves use inexpensive piecewise easing, avoiding per-sample general-purpose `pow` calls.
- The rack identifies mono vs stereo input, the timeline footer shows the selected gap's length, and the seven mini envelopes now reflect distinct instrument responses. v1.5 retains the default 912 × 578 window, resize behaviour, parameter IDs, automation and presets.

**Performance note:** Stereo uses two renderers instead of one and may cost more CPU on stereo material; the new riser curve reduces per-sample math. Measure full-plugin CPU and listen in FL Studio before a production release.


## v1.6 — stable gap rules, lighter impact, truthful timeline, compact layout

- The 4-class rules decision now **latches at the beginning of each rendered gap**. When real-time detection only estimates a gap's length, an updated estimate no longer switches all seven effect rules mid-gap. The following gap can use a different category. Lookahead/LEARN/LOCK still give the best alignment for predictive effects.
- Impact now uses recursive sub-pitch-glide and exponential envelopes, avoiding repeated per-sample `exp()` calls while retaining sample-rate-aware envelopes. Reset and replay are deterministic.
- Timeline envelopes reflect the enabled instrument rules for the gap's calculated class, instead of three fixed decorative envelopes. Preview and existing automation IDs are unchanged.
- Centralized 1200×760 design-space rectangles and increased the rules panel height to keep **all seven rows inside the 912×578 default window**, without overlapping the other panels.
- `tests/test_regression.cpp` runs geometry checks at 760/912/1200/1800 widths, rule-latch checks, deterministic impact checks at 44.1/48/96/192 kHz, and a maximum-rules stereo DSP stress test with finite-output and peak assertions. The stress test prints an approximate processing-time/audio-time ratio; this is **not an FL Studio CPU or glitch benchmark**. It does not replace host rendering tests.
- Full JUCE/VST3 builds run in GitHub Actions; portable C++ tests run locally without JUCE. Final host UI rendering, automatable parameter interaction, FL Studio session latency and glitch-free audio still require host validation.


## v1.6.1 — boundary smoothing and live UI consistency

- InstrumentMixer no longer fades effects toward an *estimated* gap end. While live detection does not know the end yet, it only applies the entry fade; once the end is known it uses its real boundary. This prevents the level from dipping/reopening when a long gap crosses a predicted duration.
- A **sample-accurate 5 ms wet attack/release** (`GapTransition`) prevents abrupt entry when lookahead is disabled and the gap is confirmed after its true start. The release tapers the last wet sample into the existing reverb tail; it does not allocate in the audio callback.
- The timeline caches rules and level parameter pointers, redraws when they change even with playback stopped, and keeps a recent-gap selection tied to its sample timestamp as new gaps arrive.
- Portable regression tests cover unknown-end vs known-end gain, attack/release continuity, stereo balance, transport-reset silence, gap length latch, panel geometry and stress/CPU timing. See `bash tests/run_cpp_tests.sh`.
- The regression benchmarks are indicative only. Windows/macOS VST3 compilation and real DAW/FL Studio UI interaction, latency, CPU and audio comparison need separate verification.

## Permanent real-editor visual regression workflow

The optional **Skell Silence UI Renderer** builds the **actual**
`SkellSilenceAudioProcessor` and `SkellSilenceAudioProcessorEditor` as a separate
JUCE executable. It does **not** add GUI capture code to the released VST3 or
replace the UI with a mockup. It links `SkellCore::UIRenderer` from the immutable
`skellyruno/skell-vst-template` revision
`438bc74a86a40bf54cfa8089832a477822c8ccda`. The shipping VST3 continues
to use the repository's existing bundled SkellCore.

Configure, compile, and render the editor on a machine with JUCE and Xvfb
(or a desktop GUI session):

```bash
cmake -S . -B build-ui -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DSKELL_SILENCE_BUILD_UI_RENDERER=ON
cmake --build build-ui --target SkellSilenceUIRenderer --parallel 2
xvfb-run -a build-ui/SkellSilenceUIRenderer --output ui-screenshots
```

The `.github/workflows/ui-screenshots.yml` workflow runs these steps on every
meaningful UI source change and uploads PNG screenshots, a scene manifest, and
`contact-sheet.png` as `SkellSilence-JUCE-UI-Screenshots`. A failing render,
flat/blank image, or controls that clip panel bounds fails the job. Capture
scenes cover the one available Skell Ink theme and single workspace at the
minimum 760×481, shipping 912×578, standard 1200×760, and large 1500×950
sizes. State coverage includes idle, running detector, dry mix/disabled
instruments, grid, sidechain, MIDI, selected gaps, parameter range editor,
all seven real instrument settings callouts (including dropdown choices), and the workspace menu. No extra theme,
tab, or preset browser is invented for tests: LOAD/SAVE use native file
choosers and must additionally be examined in a real host session.

The screenshot executable calls the plugin's actual parameter attachments,
buttons and look-and-feel. Whenever a UI control, style or layout changes,
inspect the downloadable screenshot contact sheet and full-size minimum/compact
PNGs, correct clipping and hit targets, and rerun the workflow. Passing static
bounds checks alone is not a substitute for visual inspection or testing the
native file chooser and plugin in FL Studio.


### v1.7 visual console refresh
The editor keeps all existing automation IDs, 912x578 shipping size, and its one-workspace layout.
The hardware console language now uses higher-contrast typography, gradient metal panels, seven
colour-coded instrument strips with numerical IDs, integrated envelope cards, wider beat-rule
toggle targets, and clearer detector and dynamics grouping. Every source UI edit triggers the
existing SkellCore actual-editor screenshot workflow.

The brand glyph and rolling signal display are rendered directly by JUCE vectors using real processor data; no static screenshots are used as editor controls.


### v1.8 — MIDI gate and instrument rules glance view
- The MIDI trigger tracks held notes per channel: one note-off cannot close a
  gap while other notes remain down. Duplicate on and unmatched off messages
  are ignored; the gate resets on transport/runtime reset and max-gap timeout.
- Each instrument row now shows four short rule bars below its envelope
  (SHORT / MEDIUM / LONG / EXTRA LONG). Bars reflect existing automation,
  and the active gap length is outlined while that effect plays.
- Instrument-rack refresh compares actual parameter state and activity instead
  of repainting all seven rows on every timer tick.
- Keyboard focus is more visible on buttons and matrix switches.
- The SkellCore real-editor screenshot suite adds rule-change and disabled
  states and a JUCE-processor MIDI-overlap regression test.

- Trigger-source/LOCK changes reset only detector and MIDI gate state (not the
  audio delay/history), closing stale open events safely. GRID/MIDI and LOCK
  now publish their real gate state to the detector badge.
