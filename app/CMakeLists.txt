cmake_minimum_required(VERSION 3.22.1)

project(SynthPlayer)

add_library(native-bridge SHARED
        src/main/cpp/jni-bridge.cpp
        src/main/cpp/SynthPlayer.h
        src/main/cpp/SynthPlayer.cpp
        src/main/cpp/SynthAudioSource.h
        src/main/cpp/SynthAudioSource.cpp
        src/main/cpp/SampleAudioSource.h
        src/main/cpp/SampleAudioSource.cpp
        src/main/cpp/LogUtils.h
        src/main/cpp/IAudioSource.h)

#juce_generate_juce_header(SynthPlayer)
find_package(JUCE REQUIRED CONFIG NO_CMAKE_FIND_ROOT_PATH)

target_link_libraries(native-bridge
        log
        juce::juce_audio_devices
        juce::juce_audio_utils
        juce::juce_dsp)