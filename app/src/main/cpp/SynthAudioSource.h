//
// Created by Ivan Khulup on 22.12.2023.
//

#ifndef SYNTHBRIDGE_SYNTHAUDIOSOURCE_H
#define SYNTHBRIDGE_SYNTHAUDIOSOURCE_H

#endif //SYNTHBRIDGE_SYNTHAUDIOSOURCE_H

#include "IAudioSource.h"
#include <juce_dsp/juce_dsp.h>
#include <oboe/Oboe.h>

using namespace juce;
class SynthAudioSource : public IAudioSource {
public:
    SynthAudioSource(int sample_rate, int samples_per_block, int channel_count);

    void startNote();
    void stopNote();

    oboe::Result renderAudio(void *outputBuffer, int32_t numFrames) override;

private:
    dsp::Oscillator<float> oscillator {};
    AudioBuffer<float> buffer {};
    bool mIsNoteOn{false};
    int mChannel_count = -1;

};