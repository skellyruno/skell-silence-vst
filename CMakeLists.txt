cmake_minimum_required(VERSION 3.22)
project(SkellSilence VERSION 1.7.0 LANGUAGES C CXX)
include(FetchContent)
if(DEFINED JUCE_PATH AND EXISTS "${JUCE_PATH}/CMakeLists.txt")
  add_subdirectory("${JUCE_PATH}" JUCE)
else()
  FetchContent_Declare(JUCE GIT_REPOSITORY https://github.com/juce-framework/JUCE.git GIT_TAG 8.0.12 GIT_SHALLOW TRUE)
  FetchContent_MakeAvailable(JUCE)
endif()

# The optional visual-regression executable pins a tested upstream SkellCore
# revision. Normal plugin builds keep using the existing bundled core, avoiding
# a new release dependency and preserving the plugin's shipping configuration.
option(SKELL_SILENCE_BUILD_UI_RENDERER "Build the real-editor headless JUCE screenshot harness" OFF)
set(SKELL_SILENCE_RENDERER_SKELLCORE_COMMIT "438bc74a86a40bf54cfa8089832a477822c8ccda")
if(SKELL_SILENCE_BUILD_UI_RENDERER)
  FetchContent_Declare(SkellCoreUIRenderer
    GIT_REPOSITORY https://github.com/skellyruno/skell-vst-template.git
    GIT_TAG ${SKELL_SILENCE_RENDERER_SKELLCORE_COMMIT}
    GIT_SHALLOW FALSE
    SOURCE_SUBDIR SkellCore)
  FetchContent_MakeAvailable(SkellCoreUIRenderer)
  if(NOT TARGET SkellCore::UIRenderer)
    message(FATAL_ERROR "Pinned SkellCore does not provide SkellCore::UIRenderer")
  endif()
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/SkellCore/CMakeLists.txt")
  add_subdirectory(SkellCore)
endif()

juce_add_plugin(SkellSilence
  COMPANY_NAME "Skell Audio"
  BUNDLE_ID "uno.skellyr.silence"
  PLUGIN_MANUFACTURER_CODE SkAu
  PLUGIN_CODE Sl01
  FORMATS VST3 Standalone
  PRODUCT_NAME "Skell Silence"
  IS_SYNTH FALSE
  NEEDS_MIDI_INPUT TRUE
  NEEDS_MIDI_OUTPUT FALSE
  IS_MIDI_EFFECT FALSE
  COPY_PLUGIN_AFTER_BUILD FALSE)
juce_generate_juce_header(SkellSilence)
file(GLOB_RECURSE SKELL_SOURCE CONFIGURE_DEPENDS "Source/*.h" "Source/*.cpp")
target_sources(SkellSilence PRIVATE ${SKELL_SOURCE})
target_compile_features(SkellSilence PRIVATE cxx_std_17)
target_compile_definitions(SkellSilence PUBLIC JUCE_VST3_CAN_REPLACE_VST2=0)
target_compile_definitions(SkellSilence PRIVATE JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0)
target_link_libraries(SkellSilence PRIVATE juce::juce_audio_utils juce::juce_audio_processors juce::juce_gui_extra juce::juce_dsp)

if(TARGET SkellCore::DSP AND TARGET SkellCore::UI)
  target_link_libraries(SkellSilence PRIVATE SkellCore::DSP SkellCore::UI)
endif()

# Development-only executable: links the genuine PluginProcessor and PluginEditor
# from the plugin shared-code target, never any screenshot mockup. This target is
# not included in the released VST3 or Standalone bundles.
if(SKELL_SILENCE_BUILD_UI_RENDERER)
  add_executable(SkellSilenceUIRenderer tests/ui_renderer.cpp)
  target_include_directories(SkellSilenceUIRenderer PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}/SkellSilence_artefacts/JuceLibraryCode")
  target_link_libraries(SkellSilenceUIRenderer PRIVATE
    SkellSilence SkellCore::DSP SkellCore::UI SkellCore::UIRenderer
    juce::juce_audio_utils juce::juce_audio_processors juce::juce_gui_extra)
  target_compile_definitions(SkellSilenceUIRenderer PRIVATE
    JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0 JUCE_VST3_CAN_REPLACE_VST2=0)
  target_compile_features(SkellSilenceUIRenderer PRIVATE cxx_std_17)
endif()
