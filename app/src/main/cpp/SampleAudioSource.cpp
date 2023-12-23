//
// Created by Ivan Khulup on 23.12.2023.
//

#include "SampleAudioSource.h"

SampleAudioSource *
SampleAudioSource::newSourceFromAsset(AAssetManager &assetManager, const char *assetName) {
    AAsset *asset = AAssetManager_open(&assetManager, assetName, AASSET_MODE_BUFFER);

    if (!asset) {
        LOGE("SampleAudioSource", "Error opening asset")
        return nullptr;
    }
    off_t length = AAsset_getLength(asset);
    LOGD("SampleAudioSource", "opened asset successfully")

    float *buff = new float[length];
    AAsset_read(asset, buff, length);

    juce::AudioFormatManager formatManager{};
    formatManager.registerBasicFormats();
    auto reader = formatManager.createReaderFor(
            std::make_unique<juce::MemoryInputStream>(buff, length, false));

    juce::AudioBuffer<float> buffer{};
    buffer.setSize(reader->numChannels, reader->lengthInSamples);
    buffer.clear();
    reader->read(&buffer, 0, reader->lengthInSamples, 0, true, true);

    return new SampleAudioSource(std::move(buffer));
}

oboe::Result SampleAudioSource::renderAudio(void *outputBuffer, int32_t numFrames) {
    if (!playSound) {
        memset(outputBuffer, 0, sizeof(float) * numFrames);
    } else {
        auto output = static_cast<float *>(outputBuffer);
        for (int i = 0; i < numFrames; ++i) {
            if (i + cursor < mBuffer.getNumSamples()) {
                output[i] = mBuffer.getSample(0, i + cursor);
            } else {
                break;
            }
        }
        if (cursor >= mBuffer.getNumSamples()) {
            cursor = 0;
            playSound = false;
        } else {
            cursor += numFrames;
        }
    }

    return oboe::Result::OK;
}

void SampleAudioSource::playOneShotSound() {
    playSound = true;
}
