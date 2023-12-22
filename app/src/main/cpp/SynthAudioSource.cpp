//
// Created by Ivan Khulup on 22.12.2023.
//

#include "SynthAudioSource.h"

SynthAudioSource::SynthAudioSource(int sample_rate, int samples_per_block, int channel_count) {
    dsp::ProcessSpec spec;
    spec.sampleRate = sample_rate;
    spec.maximumBlockSize = samples_per_block;
    spec.numChannels = channel_count;

    oscillator.prepare(spec);
    oscillator.setFrequency(440.0f);
    oscillator.initialise([](float x) { return sin(x); });
    mChannel_count = channel_count;
}

void SynthAudioSource::startNote() {
    //default to A4 for now
    mIsNoteOn = true;
}

void SynthAudioSource::stopNote() {
    mIsNoteOn = false;
}

oboe::Result SynthAudioSource::renderNext(void *audioStream, int32_t samples_count) {
    if (!mIsNoteOn)  {
        memset(audioStream, 0, sizeof(float) * samples_count);
    } else {
        buffer.setSize(mChannel_count, samples_count);
        buffer.clear();
        auto output = static_cast<float *>(audioStream);
        auto block = juce::dsp::AudioBlock<float> { buffer };
        oscillator.process(juce::dsp::ProcessContextReplacing<float>(block));
        for (int channel = 0; channel < block.getNumChannels(); ++channel) {
            for (int i = 0; i < samples_count; ++i) {
                output[i + channel] = buffer.getSample(channel, i);
            }
        }
    }

    return oboe::Result::OK;
}
