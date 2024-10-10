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

    auto *buff = new float[length];
    AAsset_read(asset, buff, length);

    juce::AudioFormatManager formatManager{};
    formatManager.registerBasicFormats();
    auto reader = formatManager.createReaderFor(
            std::make_unique<juce::MemoryInputStream>(buff, length, false));

    juce::AudioBuffer<float> buffer;
    buffer.setSize(reader->numChannels, reader->lengthInSamples);
    buffer.clear();
    reader->read(&buffer, 0, reader->lengthInSamples, 0, true, true);
    delete[] buff;

    return new SampleAudioSource(buffer);
}

oboe::Result SampleAudioSource::renderAudio(void *outputBuffer, uint8_t output_channels_count, int32_t num_frames) {
    if (!playSound) {
        memset(outputBuffer, 0, sizeof(float) * num_frames);
    } else {
        auto output = static_cast<float *>(outputBuffer);
        auto num_channels = mBuffer.getNumChannels();
        for (int i = 0; i < num_frames ; ++i) {
            if (i + cursor < mBuffer.getNumSamples()) {
                if (output_channels_count == 2 && num_channels == 2) {
                    output[i] = mBuffer.getSample(0, i + cursor);
                    output[i + 1] = mBuffer.getSample(1, i + cursor);
                } else {
                    output[i] = mBuffer.getSample(0, i + cursor);
                }
            } else {
                break;
            }
        }
        if (cursor >= mBuffer.getNumSamples()) {
            cursor = 0;
            playSound = false;
        } else {
            cursor += num_frames;
        }
    }

    return oboe::Result::OK;
}

void SampleAudioSource::playOneShotSound() {
    playSound = true;
}