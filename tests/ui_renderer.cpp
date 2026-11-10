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
            editRanges, instrument0, instrument6, workspaceMenu };

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
    {"compact-idle", "DEFAULT / COMPACT"},
    {"compact-playing", "ACTIVE DETECTOR"},
    {"compact-selected", "GAP SELECTED"},
    {"compact-dry-mix", "DRY / DISABLED"},
    {"compact-grid", "GRID TRIGGER"},
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
} // namespace

int main(int argc, char** argv) {
  juce::ScopedJuceInitialiser_GUI gui;
  const juce::String target = argc >= 3 && juce::String(argv[1]) == "--output"
      ? juce::String::fromUTF8(argv[2]) : "ui-screenshots";
  const auto output = juce::File::getCurrentWorkingDirectory().getChildFile(target);
  SkellSilenceAudioProcessor p;
  p.prepareToPlay(48000., 256);
  generateDetectorInput(p);
  int failures = 0;
  {
    SkellSilenceAudioProcessorEditor editor(p);
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
    }
    // Real control overlays at both the minimum and shipping window sizes.
    for (const auto& s : { sizes[0], sizes[1] }) {
      addScene(options, juce::String(s.name) + "-edit-ranges", s.width, s.height, editRanges);
      addScene(options, juce::String(s.name) + "-instrument-0", s.width, s.height, instrument0);
      addScene(options, juce::String(s.name) + "-instrument-6", s.width, s.height, instrument6);
      addScene(options, juce::String(s.name) + "-menu", s.width, s.height, workspaceMenu);
    }
    options.mustDiffer = {
      {"compact-idle", "compact-playing"},
      {"compact-idle", "compact-dry-mix"},
      {"compact-idle", "compact-grid"},
      {"compact-idle", "compact-selected"},
      {"compact-idle", "compact-edit-ranges"},
      {"compact-idle", "compact-instrument-0"},
      {"compact-idle", "compact-instrument-6"}
    };
    options.configure = [&](const Scene& scene) {
      closeExistingOverlays(editor);
      editor.setSize(scene.width, scene.height);
      const auto mode = static_cast<Mode>(scene.mode);
      for (int i = 0; i < 7; ++i)
        setParameter(p, juce::String(skell::dsp::instrumentIds[size_t(i)]) + "On", 1.f);
      setParameter(p, "mix", 0.65f);
      setParameter(p, "triggerSource", 0.f);
      p.isPlaying.store(mode == playing);
      p.detectorState.store(mode == playing ? 2 : 0);
      p.activeLengthClass.store(mode == playing ? 2 : -1);
      p.activeMask.store(mode == playing ? 0b0111011 : 0);
      if (mode == dryMix) {
        setParameter(p, "mix", 0.f);
        for (int i = 0; i < 7; ++i)
          setParameter(p, juce::String(skell::dsp::instrumentIds[size_t(i)]) + "On", 0.f);
      }
      if (mode == grid) setParameter(p, "triggerSource", 2.f);
      if (mode == sidechain) setParameter(p, "triggerSource", 1.f);
      if (mode == midi) setParameter(p, "triggerSource", 3.f);
      if (auto* timeline = dynamic_cast<skell::ui::GapTimeline*>(findById(editor, "timeline")))
        timeline->selectRecentGap(mode == selected ? 0 : -1);
      if (mode == editRanges || mode == instrument0 || mode == instrument6
          || mode == workspaceMenu) {
        const auto id = mode == editRanges ? "edit-ranges"
                        : mode == instrument0 ? "instrument-settings-0"
                        : mode == instrument6 ? "instrument-settings-6" : "menu";
        if (auto* button = dynamic_cast<juce::Button*>(findById(editor, id)))
          { if (button->onClick) button->onClick(); }
      }
    };
    options.inspect = [&] {
      juce::StringArray issues;
      checkChildren(editor, issues);
      return issues;
    };
    const auto report = skellcore::ui::headless::render(editor, output, options);
    for (const auto& err : report.errors) {
      std::fprintf(stderr, "Screenshot validation: %s\n", err.toRawUTF8());
      ++failures;
    }
    if (report.captured != static_cast<int>(options.scenes.size())) {
      std::fprintf(stderr, "Expected %zu actual-editor PNGs; got %d\n",
                   options.scenes.size(), report.captured);
      ++failures;
    }
    if (!makeContactSheet(output)) {
      std::fprintf(stderr, "Cannot write contact sheet\n");
      ++failures;
    }
    std::printf("SkellCore real-editor screenshots: %d / %zu scenes, errors %d\n",
                report.captured, options.scenes.size(), failures);
    closeExistingOverlays(editor);
  }
  p.releaseResources();
  return failures == 0 ? 0 : 1;
}
