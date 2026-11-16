# SkellSilence v2.8 — acceptance and release gate

## Scope and compatibility
- Audio/DSP: confirmed silence-start timestamp refinement (max 45 ms), sample-accurate level/on/rule automation, numerical dust-safe FDN idle.
- Preserves approved editor source, parameter identifiers and order, state serialization, factory defaults, VST3 identifier, and existing reported lookahead modes.
- No private reference recordings are committed.

## Automated verification (do not mark pass until CI confirms)
1. Linux portable DSP tests: existing v2.6/v2.7 checks plus test_v28_quality.cpp: vocal pauses across 44.1–192k, short percussion rests, 10ms level/enable slew, FDN sleep/re-excitation.
2. Synthetic per-effect performance: perf_v28.cpp, prints 350ms render time/ratio and peaks for OFF/MUTED/ALL7. Results describe the CI runner, NOT the user's DAW.
3. Windows x64 actual JUCE processor: SkellSilenceHostRegression tests preset/map/UI size state, parameter IDs, two plugin instances, bit-exact mix=0, host-bypass delay at 48k.
4. Windows VST3: one bundled module, PE64 machine check, optional moduleinfo.json parse, packaged SHA256 equality, pluginval strictness 5, artifact retention 7 days.
5. Quick4: editor source unchanged; do not replace native Quick4 screenshots with generated mockups.

## Outstanding FL Studio acceptance — real Windows host still required
Use v2.8 in a COPY of an existing FL Studio project (keep v2.7 reference). Check:
- Launch, VST3 scan, preset load, save/reopen project, parameter automation recall, previous project compatibility.
- Mix 0 dry bit-identical aside from declared latency; host bypass active mid-song; rapidly change enable/level/rule controls and check for clicks.
- AUTO vocal pauses, sidechain, GRID and MIDI triggers; 44.1/48/96k; lookahead OFF, 250ms, 500ms, one beat, one bar.
- Run 1/4/8 instances at 64/128/256/512/1024 buffer sizes. Record FL Studio CPU meter, declared PDC and loopback latency.
- Loudness-matched A/B against v2.7 using same vocals/drums. Preserve v2.7 if v2.8 degrades tone.
- Capture four genuine Quick4 JUCE UI scenes at minimum, default, large and menu states before external release.

CI pass means tested automated processor paths; it does NOT certify FL Studio behavior, Windows UI or subjective quality. Keep release packaging draft until host acceptance.