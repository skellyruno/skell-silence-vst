cmake_minimum_required(VERSION 3.22)
project(SkellSilence VERSION 1.2.0 LANGUAGES C CXX)
include(FetchContent)
if(DEFINED JUCE_PATH AND EXISTS "${JUCE_PATH}/CMakeLists.txt")
  add_subdirectory("${JUCE_PATH}" JUCE)
else()
  FetchContent_Declare(JUCE GIT_REPOSITORY https://github.com/juce-framework/JUCE.git GIT_TAG 8.0.12 GIT_SHALLOW TRUE)
  FetchContent_MakeAvailable(JUCE)
endif()

# Preserve the shared SkellCore library already present in the Skell template repository.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/SkellCore/CMakeLists.txt")
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
