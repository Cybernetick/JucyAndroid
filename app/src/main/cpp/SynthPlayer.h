//
// Created by Ivan Khulup on 21.12.2023.
//

#ifndef SYNTHBRIDGE_SYNTHPLAYER_H
#define SYNTHBRIDGE_SYNTHPLAYER_H

#endif //SYNTHBRIDGE_SYNTHPLAYER_H

#include <oboe/Oboe.h>
#include <juce_dsp/juce_dsp.h>
#include "SampleAudioSource.h"

class SynthPlayer: public oboe::AudioStreamDataCallback{
private:
    oboe::AudioStreamBuilder builder;
    std::shared_ptr<oboe::AudioStream> mStream;
    std::unique_ptr<SampleAudioSource> mAudioSource;
public:
    explicit SynthPlayer(AAssetManager& assetManager);

    void start();
    void stop();

    void playSound(bool isDown);

    oboe::DataCallbackResult
    onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) override;
};