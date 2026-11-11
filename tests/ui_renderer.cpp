// Screenshot regression of the *real* Skell Silence JUCE editor.
// Run on the JUCE message thread; on Linux use xvfb-run.
#include "../Source/PluginEditor.h"
#include "../Source/PluginProcessor.h"
#include "../Source/ui/GapTimeline.h"
#include <SkellCore/HeadlessUIRenderer.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <array>
#include <cmath>
#include <cstdio>
#include <vector>

namespace {
using skellcore::ui::headless::Scene;
using skellcore::ui::headless::Options;

struct Size { const char* name; int width, height; };
constexpr std::array<Size, 4> sizes {{
  {"minimum", 760, 481}, {"compact", 912, 578},
  {"standard", 1200, 760}, {"large", 1500, 950}
}};

// The plugin currently has one skin and one workspace (not invented themes/tabs).
// Modes are real controls/states of the same editor, never a mock GUI.
enum Mode { idle, playing, dryMix, grid, sidechain, midi, selected,
            editRanges, instrument0, instrument1, instrument2, instrument3,
            instrument4, instrument5, instrument6, workspaceMenu, ruleOverride, disabledWet,
            simpleIdle, simplePlaying, simpleDry, simplePresets };

void setParameter(SkellSilenceAudioProcessor& p, const juce::String& id, float value) {
  if (auto* parameter = p.parameters.getParameter(id))
    parameter->setValueNotifyingHost(parameter->convertTo0to1(value));
}

juce::Component* findById(juce::Component& parent, const juce::String& id) {
  for (int i = 0; i < parent.getNumChildComponents(); ++i) {
    auto* child = parent.getChildComponent(i);
    if (child->getComponentID() == id) return child;
    if (auto* result = findById(*child, id)) return result;
  }
  return nullptr;
}

void closeExistingOverlays(juce::Component& editor) {
  juce::PopupMenu::dismissAllActiveMenus();
  for (int i = editor.getNumChildComponents() - 1; i >= 0; --i)
    if (auto* popup = dynamic_cast<juce::CallOutBox*>(editor.getChildComponent(i)))
      popup->dismiss();
}

// End-to-end host-independent audio regression using the actual processor:
// MIX=0 must preserve a stereo impulse at the declared lookahead sample offset.
bool testDryLatency() {
  SkellSilenceAudioProcessor p;
  setParameter(p, "mix", 0.f);
  setParameter(p, "lookahead", 1.f); // 250ms, exact at 48 kHz
  p.prepareToPlay(48000., 256);
  const int delay = p.latencyRequested.load();
  if (delay != 12000) return false;
  juce::AudioBuffer<float> audio(2, 256);
  juce::MidiBuffer events;
  constexpr int total = 12800;
  for (int start = 0; start < total; start += 256) {
    audio.clear();
    if (start == 0) {
      audio.setSample(0, 0, 0.5f);
      audio.setSample(1, 0, -0.35f);
    }
    events.clear();
    p.processBlock(audio, events);
    for (int i = 0; i < 256; ++i) {
      const int at = start + i;
      for (int ch = 0; ch < 2; ++ch) {
        const float sample = audio.getSample(ch, i);
        const float expected = at == delay ? (ch == 0 ? 0.5f : -0.35f) : 0.f;
        if (!std::isfinite(sample) || std::abs(sample - expected) > 1.e-5f)
          return false;
      }
    }
  }
  p.releaseResources();
  return true;
}

// Verify the modern MidiBufferIterator keeps exact note sample offsets.
bool testMidiGapPositions() {
  SkellSilenceAudioProcessor p;
  setParameter(p, "triggerSource", 3.f);
  setParameter(p, "mix", 0.f);
  p.prepareToPlay(48000., 256);
  juce::AudioBuffer<float> audio(2, 256);
  audio.clear();
  juce::MidiBuffer midi;
  midi.addEvent(juce::MidiMessage::noteOn(1, 60, juce::uint8(100)), 64);
  midi.addEvent(juce::MidiMessage::noteOff(1, 60), 192);
  p.processBlock(audio, midi);
  const auto recent = p.getRecentGap(0);
  const bool passed = p.getRecentCount() == 1 && recent.start == 64
                      && recent.end == 192;
  p.releaseResources();
  return passed;
}

// Real JUCE processBlock regression: overlapping notes form one held interval,
// then a new note retriggers cleanly. This catches MIDI state bugs that a
// portable gate unit test alone cannot detect in the audio processor.
bool testMidiOverlap() {
  SkellSilenceAudioProcessor p;
  setParameter(p, "triggerSource", 3.f);
  setParameter(p, "mix", 0.f);
  p.prepareToPlay(48000., 256);
  juce::AudioBuffer<float> audio(2,256);audio.clear();
  juce::MidiBuffer midi;
  midi.addEvent(juce::MidiMessage::noteOn(1,60,juce::uint8(100)),32);
  midi.addEvent(juce::MidiMessage::noteOn(2,72,juce::uint8(95)),48);
  midi.addEvent(juce::MidiMessage::noteOff(1,60),100);
  midi.addEvent(juce::MidiMessage::noteOff(2,72),184);
  midi.addEvent(juce::MidiMessage::noteOn(1,64,juce::uint8(100)),208);
  midi.addEvent(juce::MidiMessage::noteOff(1,64),248);
  p.processBlock(audio,midi);
  const auto first=p.getRecentGap(1),second=p.getRecentGap(0);
  const bool passed=p.getRecentCount()==2
      && first.start==32 && first.end==184
      && second.start==208 && second.end==248;
  p.releaseResources();
  return passed;
}

bool testMidiModeSwitchAndTelemetry() {
  SkellSilenceAudioProcessor p;
  setParameter(p,"triggerSource",3.f);
  setParameter(p,"mix",0.f);
  p.prepareToPlay(48000.,256);
  juce::AudioBuffer<float> audio(2,256);audio.clear();
  juce::MidiBuffer midi;
  midi.addEvent(juce::MidiMessage::noteOn(1,55,juce::uint8(100)),32);
  p.processBlock(audio,midi);
  if(p.detectorState.load()!=2)return false;
  setParameter(p,"triggerSource",2.f);midi.clear();audio.clear();
  p.processBlock(audio,midi);
  if(p.detectorState.load()!=0)return false;
  setParameter(p,"triggerSource",3.f);midi.clear();audio.clear();
  midi.addEvent(juce::MidiMessage::noteOff(1,55),25); // stale off ignored
  midi.addEvent(juce::MidiMessage::noteOn(1,60,juce::uint8(100)),64);
  midi.addEvent(juce::MidiMessage::noteOff(1,60),120);
  p.processBlock(audio,midi);
  const auto gap=p.getRecentGap(0);
  const bool passed=gap.start==2*256+64 && gap.end==2*256+120
      && p.detectorState.load()==0;
  p.releaseResources();return passed;
}

bool testZeroLookaheadDry() {
  SkellSilenceAudioProcessor p;
  setParameter(p, "lookahead", 0.f);
  setParameter(p, "mix", 0.f);
  p.prepareToPlay(44100.,256);
  if(p.latencyRequested.load()!=0)return false;
  juce::AudioBuffer<float> audio(2,256);
  for(int i=0;i<256;++i){
    audio.setSample(0,i,0.4f*std::sin(float(i)*0.129f));
    audio.setSample(1,i,-0.6f*std::cos(float(i)*0.093f));
  }
  juce::AudioBuffer<float> reference;reference.makeCopyOf(audio);
  juce::MidiBuffer midi;p.processBlock(audio,midi);
  bool passed=true;
  for(int ch=0;ch<2;++ch)for(int i=0;i<256;++i)
    if(audio.getSample(ch,i)!=reference.getSample(ch,i))passed=false;
  p.releaseResources();return passed;
}

void generateDetectorInput(SkellSilenceAudioProcessor& p) {
  // Actual processBlock with sound/silence/sound to populate waveform and
  // detected-gap widgets. No prerecorded/painted waveform or fake editor.
  constexpr int rate = 48000, block = 256;
  juce::AudioBuffer<float> audio(2, block);
  juce::MidiBuffer midi;
  for (int start = 0; start < rate * 4; start += block) {
    for (int i = 0; i < block; ++i) {
      const double seconds = double(start + i) / rate;
      const float envelope = seconds < 1.45 || seconds > 2.1 ? 0.45f : 0.0f;
      const float sample = envelope * std::sin(2.0 * juce::MathConstants<double>::pi
                                             * 217.0 * seconds);
      audio.setSample(0, i, sample);
      audio.setSample(1, i, 0.7f * sample);
    }
    midi.clear();
    p.processBlock(audio, midi);
  }
}

void checkChildren(juce::Component& root, juce::StringArray& issues, int depth = 0) {
  if (depth > 6) return;
  const auto bounds = root.getLocalBounds();
  for (int i = 0; i < root.getNumChildComponents(); ++i) {
    auto* c = root.getChildComponent(i);
    if (!c->isVisible()) continue;
    // Floating menus/callouts intentionally cover other panels.
    if (dynamic_cast<juce::CallOutBox*>(c) != nullptr) continue;
    const auto rect = c->getBoundsInParent();
    if (rect.isEmpty())
      issues.add("Empty child bounds: " + c->getComponentID());
    else if (!bounds.expanded(2).contains(rect))
      issues.add("Clipped child: " + (c->getComponentID().isEmpty()
          ? juce::String(c->getName().isEmpty() ? "unnamed" : c->getName())
          : c->getComponentID()) + " in " + root.getComponentID());
    checkChildren(*c, issues, depth + 1);
  }
}

void addScene(Options& options, const juce::String& name,
              int width, int height, Mode mode) {
  Scene scene;
  scene.id = name;
  scene.width = width;
  scene.height = height;
  scene.mode = static_cast<int>(mode);
  options.scenes.push_back(scene);
}

bool makeContactSheet(const juce::File& folder) {
  struct Tile { const char* file; const char* label; };
  constexpr std::array<Tile, 9> tiles {{
    {"compact-simple", "SIMPLE / DEFAULT"},
    {"compact-simple-playing", "SIMPLE / LISTENING"},
    {"compact-idle", "ADVANCED / CONTROLS"},
    {"compact-simple-dry", "SIMPLE / DRY MIX"},
    {"compact-simple-presets", "PRESET MENU"},
    {"compact-midi", "MIDI TRIGGER"},
    {"compact-edit-ranges", "EDIT LENGTHS"},
    {"compact-instrument-0", "TAPE STOP SETTINGS"},
    {"minimum-instrument-6", "MINIMUM / STUTTER"}
  }};
  constexpr int width = 492, imageHeight = 310, labelHeight = 30;
  juce::Image sheet(juce::Image::RGB, width * 3,
                    (imageHeight + labelHeight) * 3, true);
  juce::Graphics g(sheet);
  g.fillAll(juce::Colour(0xff070b11));
  for (size_t i = 0; i < tiles.size(); ++i) {
    const auto path = folder.getChildFile(juce::String(tiles[i].file) + ".png");
    const auto img = juce::ImageFileFormat::loadFrom(path);
    if (!img.isValid()) return false;
    const int x = int(i % 3) * width;
    const int y = int(i / 3) * (imageHeight + labelHeight);
    g.drawImageWithin(img, x + 8, y + 6, width - 16, imageHeight - 12,
                      juce::RectanglePlacement::centred);
    g.setColour(juce::Colour(0xffb5c6d3));
    g.setFont(juce::Font(juce::FontOptions(14.0f)));
    g.drawText(tiles[i].label, x + 12, y + imageHeight,
               width - 20, labelHeight, juce::Justification::centredLeft);
  }
  return skellcore::ui::headless::writePng(sheet,
                                          folder.getChildFile("contact-sheet.png"));
}
// Compare real scene pixels at finer resolution than the lightweight SkellCore
// blank-frame sampler. A ComboBox label can change inside a ~30x9 px region;
// the renderer's coarse fingerprint can correctly miss that subtle difference.
std::uint64_t visualFingerprint(const juce::Image& image) {
  std::uint64_t hash = 14695981039346656037ull;
  for (int y = 0; y < image.getHeight(); y += 2)
    for (int x = 0; x < image.getWidth(); x += 2) {
      hash ^= static_cast<std::uint64_t>(image.getPixelAt(x, y).getARGB());
      hash *= 1099511628211ull;
    }
  return hash;
}

// A normal single JUCE message loop (works when JUCE_MODAL_LOOPS_PERMITTED=0).
// The three phases deliberately yield to the event queue so attachment changes
// and async popup dismissal are applied before screenshots are taken.
class ScreenshotDriver final : private juce::Timer {
public:
  ScreenshotDriver(juce::Component& editorIn, const juce::File& outputIn,
                   const Options& opts)
      : editor(editorIn), output(outputIn), options(opts) {}

  void start() { startTimer(80); }
  int failures() const noexcept { return errorCount; }
private:
  void timerCallback() override {
    if (next >= options.scenes.size()) return;
    const auto& scene = options.scenes[next];
    if (phase == 0) {
      closeExistingOverlays(editor);
      phase = 1;
      return;
    }
    if (phase == 1) {
      if (options.configure) options.configure(scene);
      phase = 2;
      // PopupMenu is a real JUCE menu parented to the editor. In a truly
      // headless component host the native focus timer dismisses it shortly
      // after opening; capture it in the same message-loop turn instead of
      // creating an X11 desktop peer (which fails on some Xvfb servers).
      if (scene.mode == static_cast<int>(workspaceMenu) || scene.mode == static_cast<int>(simplePresets)) timerCallback();
      return;
    }
    Options one;
    one.project = options.project;
    one.minimumColours = options.minimumColours;
    one.scenes.push_back(scene);
    one.inspect = options.inspect;
    // Shared SkellCore::UIRenderer captures the real editor, checking image
    // dimensions, sampled color richness and every active layout assertion.
    const auto report = skellcore::ui::headless::render(editor, output, one);
    for (const auto& err : report.errors) {
      std::fprintf(stderr, "Screenshot validation: %s\n", err.toRawUTF8());
      ++errorCount;
    }
    captured += report.captured;
    if (report.captured == 1) {
      auto shot = skellcore::ui::headless::capture(editor, scene.width, scene.height);
      fingerprints[scene.id.toStdString()] = visualFingerprint(shot.image);
      juce::var row(new juce::DynamicObject());
      row.getDynamicObject()->setProperty("file", scene.id + ".png");
      row.getDynamicObject()->setProperty("width", scene.width);
      row.getDynamicObject()->setProperty("height", scene.height);
      row.getDynamicObject()->setProperty("mode", scene.mode);
      row.getDynamicObject()->setProperty("sampledColours", shot.distinctColours);
      rows.add(row);
    }
    ++next;
    phase = 0;
    if (next == options.scenes.size()) finish();
  }

  void finish() {
    if (captured != int(options.scenes.size())) {
      std::fprintf(stderr, "Expected %zu screenshots, captured %d\n",
                   options.scenes.size(), captured);
      ++errorCount;
    }
    for (const auto& pair : options.mustDiffer) {
      const auto lhs = fingerprints.find(pair.first.toStdString());
      const auto rhs = fingerprints.find(pair.second.toStdString());
      if (lhs == fingerprints.end() || rhs == fingerprints.end()
          || lhs->second == rhs->second) {
        std::fprintf(stderr, "Unchanged real UI state: %s / %s\n",
                     pair.first.toRawUTF8(), pair.second.toRawUTF8());
        ++errorCount;
      }
    }
    juce::var manifest(new juce::DynamicObject());
    manifest.getDynamicObject()->setProperty("renderer", "SkellCore real-editor JUCE v1");
    manifest.getDynamicObject()->setProperty("project", options.project);
    manifest.getDynamicObject()->setProperty("count", captured);
    manifest.getDynamicObject()->setProperty("scenes", juce::var(rows));
    if (!output.getChildFile("manifest.json").replaceWithText(
            juce::JSON::toString(manifest, false))) ++errorCount;
    if (!makeContactSheet(output)) {
      std::fprintf(stderr, "Contact sheet render failed\n");
      ++errorCount;
    }
    std::printf("SkellCore actual-editor capture: %d/%zu scenes, %d errors\n",
                captured, options.scenes.size(), errorCount);
    stopTimer();
    juce::MessageManager::getInstance()->stopDispatchLoop();
  }

  juce::Component& editor;
  juce::File output;
  const Options& options;
  size_t next = 0;
  int phase = 0, captured = 0, errorCount = 0;
  juce::Array<juce::var> rows;
  std::map<std::string, std::uint64_t> fingerprints;
};

} // namespace

int main(int argc, char** argv) {
  juce::ScopedJuceInitialiser_GUI gui;
  const juce::String target = argc >= 3 && juce::String(argv[1]) == "--output"
      ? juce::String::fromUTF8(argv[2]) : "ui-screenshots";
  const auto output = juce::File::getCurrentWorkingDirectory().getChildFile(target);
  if (!testDryLatency()) {
    std::fprintf(stderr, "Dry impulse / PDC alignment test failed\n");
    return 1;
  }
  if (!testMidiGapPositions()) {
    std::fprintf(stderr, "Sample-accurate MIDI gap position test failed\n");
    return 1;
  }
  if(!testMidiOverlap()) {
    std::fprintf(stderr, "Overlapping-note MIDI gap regression failed\n");
    return 1;
  }
  if(!testMidiModeSwitchAndTelemetry()) {
    std::fprintf(stderr,"MIDI trigger-mode switching or gap telemetry failed\n");
    return 1;
  }
  if(!testZeroLookaheadDry()) {
    std::fprintf(stderr, "Zero-lookahead / dry bypass regression failed\n");
    return 1;
  }
  SkellSilenceAudioProcessor p;
  p.prepareToPlay(48000., 256);
  generateDetectorInput(p);
  int failures = 0;
  {
    SkellSilenceAudioProcessorEditor editor(p);
    editor.dismissGuidedTourForScreenshot();
    editor.setAdvancedMode(false);
    const auto noTour=skellcore::ui::headless::capture(editor,760,481);
    if(!editor.replayGuidedTourForScreenshot()) {
      std::fprintf(stderr,"Shared first-run tutorial failed to open in real editor\\n");
      ++failures;
    } else {
      const auto withTour=skellcore::ui::headless::capture(editor,760,481);
      if(!withTour.image.isValid() || withTour.fingerprint==noTour.fingerprint) {
        std::fprintf(stderr,"GuidedTour screenshot missing or identical to normal editor\\n");
        ++failures;
      } else if(output.createDirectory().failed() ||
                !skellcore::ui::headless::writePng(
                   withTour.image,output.getChildFile("minimum-guided-tour.png"))) {
        std::fprintf(stderr,"Could not save real tutorial screenshot\\n");
        ++failures;
      }
    }
    editor.dismissGuidedTourForScreenshot();
    Options options;
    options.project = "Skell Silence actual JUCE PluginEditor (SkellCore pinned)";
    for (const auto& s : sizes) {
      addScene(options, juce::String(s.name) + "-idle", s.width, s.height, idle);
      addScene(options, juce::String(s.name) + "-playing", s.width, s.height, playing);
      addScene(options, juce::String(s.name) + "-dry-mix", s.width, s.height, dryMix);
      addScene(options, juce::String(s.name) + "-grid", s.width, s.height, grid);
      addScene(options, juce::String(s.name) + "-sidechain", s.width, s.height, sidechain);
      addScene(options, juce::String(s.name) + "-midi", s.width, s.height, midi);
      addScene(options, juce::String(s.name) + "-selected", s.width, s.height, selected);
      addScene(options, juce::String(s.name) + "-rule-override", s.width, s.height, ruleOverride);
      addScene(options, juce::String(s.name) + "-all-disabled", s.width, s.height, disabledWet);
    }
    // The first-run screen is a separate genuine editor mode. Capture it at
    // every supported size, plus its status / dry / preset states.
    for (const auto& s : sizes) {
      addScene(options, juce::String(s.name)+"-simple",s.width,s.height,simpleIdle);
      addScene(options, juce::String(s.name)+"-simple-playing",s.width,s.height,simplePlaying);
      addScene(options, juce::String(s.name)+"-simple-dry",s.width,s.height,simpleDry);
      addScene(options, juce::String(s.name)+"-simple-presets",s.width,s.height,simplePresets);
    }
    // Real control overlays at both the minimum and shipping window sizes.
    for (const auto& s : { sizes[0], sizes[1] }) {
      addScene(options, juce::String(s.name) + "-edit-ranges", s.width, s.height, editRanges);
      for (int instrument = 0; instrument < 7; ++instrument)
        addScene(options, juce::String(s.name) + "-instrument-" + juce::String(instrument),
                 s.width, s.height, static_cast<Mode>(instrument0 + instrument));
      addScene(options, juce::String(s.name) + "-menu", s.width, s.height, workspaceMenu);
    }
    options.mustDiffer = {
      {"compact-idle", "compact-simple"},
      {"compact-simple", "compact-simple-playing"},
      {"compact-simple", "compact-simple-dry"},
      {"compact-simple", "compact-simple-presets"},
      {"compact-idle", "compact-playing"},
      {"compact-idle", "compact-dry-mix"},
      {"compact-idle", "compact-grid"},
      {"compact-idle", "compact-selected"},
      {"compact-idle", "compact-edit-ranges"},
      {"compact-idle", "compact-instrument-0"},
      {"compact-idle", "compact-instrument-6"},
      {"compact-idle", "compact-menu"},
      {"compact-idle", "compact-rule-override"},
      {"compact-idle", "compact-all-disabled"}
    };
    Mode currentScene = idle;
    options.configure = [&](const Scene& scene) {
      editor.setSize(scene.width, scene.height);
      const auto mode = static_cast<Mode>(scene.mode);
      currentScene = mode;
      // Legacy instrument/control scenes intentionally use Advanced; first-run
      // scenes verify that the simplified view is genuinely the default UI.
      const bool simplified = mode >= simpleIdle;
      editor.setAdvancedMode(!simplified);
      for (int i = 0; i < 7; ++i)
        setParameter(p, juce::String(skell::dsp::instrumentIds[size_t(i)]) + "On", 1.f);
      setParameter(p, "mix", 0.65f);
      setParameter(p, "rule_tape_0", 1.f);
      setParameter(p, "rule_swell_2", 1.f);
      if(mode==ruleOverride){
        setParameter(p, "rule_tape_0", 0.f);
        setParameter(p, "rule_swell_2", 0.f);
      }
      if(mode==disabledWet)
        for(int i=0;i<7;++i)
          setParameter(p, juce::String(skell::dsp::instrumentIds[size_t(i)]) + "On", 0.f);
      setParameter(p, "triggerSource", 0.f);
      p.isPlaying.store(mode == playing || mode == simplePlaying);
      p.detectorState.store((mode == playing || mode == simplePlaying) ? 2 : 0);
      p.activeLengthClass.store((mode == playing || mode == simplePlaying) ? 2 : -1);
      p.activeMask.store((mode == playing || mode == simplePlaying) ? 0b0111011 : 0);
      if (mode == dryMix || mode == simpleDry) {
        setParameter(p, "mix", 0.f);
        for (int i = 0; i < 7; ++i)
          setParameter(p, juce::String(skell::dsp::instrumentIds[size_t(i)]) + "On", 0.f);
      }
      if (mode == grid) setParameter(p, "triggerSource", 2.f);
      if (mode == sidechain) setParameter(p, "triggerSource", 1.f);
      if (mode == midi) setParameter(p, "triggerSource", 3.f);
      if (auto* timeline = dynamic_cast<skell::ui::GapTimeline*>(findById(editor, "timeline")))
        timeline->selectRecentGap(mode == selected ? 0 : -1);
      if (mode == editRanges || (mode >= instrument0 && mode <= instrument6)
          || mode == workspaceMenu || mode == simplePresets) {
        const juce::String id = mode == editRanges ? juce::String("edit-ranges")
            : (mode == workspaceMenu || mode == simplePresets) ? juce::String("menu")
            : juce::String("instrument-settings-") + juce::String(int(mode - instrument0));
        if (auto* button = dynamic_cast<juce::Button*>(findById(editor, id)))
          if (button->onClick) button->onClick();
      }
    };
    options.inspect = [&] {
      juce::StringArray issues;
      checkChildren(editor, issues);
      int callouts = 0;
      for (int i = 0; i < editor.getNumChildComponents(); ++i)
        if (dynamic_cast<juce::CallOutBox*>(editor.getChildComponent(i)))
          ++callouts;
      const bool shouldHaveCallout = currentScene == editRanges
          || (currentScene >= instrument0 && currentScene <= instrument6);
      if (callouts != (shouldHaveCallout ? 1 : 0))
        issues.add("Expected exactly " + juce::String(shouldHaveCallout ? 1 : 0)
                   + " callouts, found " + juce::String(callouts));
      if (auto* lookahead = dynamic_cast<juce::ComboBox*>(findById(editor, "lookahead")))
        if (lookahead->getSelectedId() <= 0)
          issues.add("LOOKAHEAD chooser has no current value");
      if (auto* source = dynamic_cast<juce::ComboBox*>(findById(editor, "trigger-source"))) {
        const int expected = currentScene == grid ? 3 : currentScene == sidechain ? 2
                           : currentScene == midi ? 4 : 1;
        if (source->getSelectedId() != expected)
          issues.add("Trigger dropdown attachment did not reach expected selection "
                     + juce::String(expected));
      } else issues.add("Missing trigger dropdown");
      if (auto* mix = dynamic_cast<juce::Slider*>(findById(editor, "mix"))) {
        const double expected = (currentScene == dryMix || currentScene == simpleDry) ? 0.0 : 0.65;
        if (std::abs(mix->getValue() - expected) > 0.002)
          issues.add("MIX knob/parameter attachment did not update");
        if(mix->getTextFromValue(0.65)!="65%")
          issues.add("MIX should use whole percentage readouts");
      } else issues.add("Missing MIX control");
      if (editor.isAdvancedMode() != (currentScene < simpleIdle))
        issues.add("Simple/Advanced editor mode did not update");
      for (int i = 0; i < 7; ++i) {
        const auto id = "instrument-enable-" + juce::String(i);
        if (auto* button = dynamic_cast<juce::Button*>(findById(editor, id))) {
          const bool expected = currentScene != dryMix && currentScene != simpleDry && currentScene != disabledWet;
          if (button->getToggleState() != expected)
            issues.add(id + " is not in the expected automation state");
        } else issues.add("Missing instrument control " + id);
      }
      if(currentScene==ruleOverride){
        for(const auto& id : {"rule_tape_0","rule_swell_2"})
          if(p.parameters.getRawParameterValue(id)->load() >= 0.5f)
            issues.add("Rule overlay automation did not update: " + juce::String(id));
      }
      return issues;
    };
    // Ensure the actual first-run layout is limited to three controls and
    // never exposes the advanced rack or detector by default.
    editor.setAdvancedMode(false);
    if (editor.isAdvancedMode() || findById(editor, "simple-controls")==nullptr) {
      std::fprintf(stderr, "Simplified first-run UI did not initialize\n");
      ++failures;
    }
    // Exercise the actual header mode button (not just the editor test hook).
    if(auto* toggle=dynamic_cast<juce::Button*>(findById(editor,"toggle-advanced"))) {
      if(toggle->onClick) toggle->onClick();
      if(!editor.isAdvancedMode()) {std::fprintf(stderr,"Advanced button failed\n");++failures;}
      if(toggle->onClick) toggle->onClick();
      if(editor.isAdvancedMode()) {std::fprintf(stderr,"Simple button failed\n");++failures;}
    } else {std::fprintf(stderr,"Missing Simple/Advanced toggle\n");++failures;}
    // The plugin's JUCE build disables nested/modal message dispatch loops.
    // Use the one genuine JUCE runDispatchLoop, scheduling each cleanup,
    // configuration and capture on separate message-loop turns. This is the
    // same asynchronous lifecycle the VST3 uses, not a mocked UI.
    ScreenshotDriver driver(editor, output, options);
    driver.start();
    juce::MessageManager::getInstance()->runDispatchLoop();
    failures += driver.failures();
    closeExistingOverlays(editor);
  }
  p.releaseResources();
  return failures == 0 ? 0 : 1;
}
