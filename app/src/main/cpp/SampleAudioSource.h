//
// Created by Ivan Khulup on 23.12.2023.
//

#ifndef SYNTHBRIDGE_SAMPLEAUDIOSOURCE_H
#define SYNTHBRIDGE_SAMPLEAUDIOSOURCE_H

#endif //SYNTHBRIDGE_SAMPLEAUDIOSOURCE_H

#include <juce_audio_formats/juce_audio_formats.h>
#include <android/asset_manager.h>
#include "LogUtils.h"
#include "IAudioSource.h"

class SampleAudioSource : public IAudioSource{
public:
    static SampleAudioSource* newSourceFromAsset(AAssetManager& assetManager, const char* assetName);

    oboe::Result renderAudio(void *outputBuffer, int32_t numFrames) override;
    void playOneShotSound();

private:
    explicit SampleAudioSource(const juce::AudioBuffer<float> &mBuffer) : mBuffer(mBuffer) {}
    const juce::AudioBuffer<float> mBuffer {};
    bool playSound { false };
    int cursor = 0;
};