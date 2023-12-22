//
// Created by Ivan Khulup on 21.12.2023.
//

#ifndef SYNTHBRIDGE_SYNTHPLAYER_H
#define SYNTHBRIDGE_SYNTHPLAYER_H

#endif //SYNTHBRIDGE_SYNTHPLAYER_H

#include <oboe/Oboe.h>
#include <android/log.h>
#include <juce_dsp/juce_dsp.h>
#include "SynthAudioSource.h"

#define LOGE(TAG, TEXT) __android_log_write(ANDROID_LOG_ERROR, TAG, TEXT);
#define LOGD(TAG, TEXT) __android_log_write(ANDROID_LOG_DEBUG, TAG, TEXT);

class SynthPlayer: public oboe::AudioStreamDataCallback{
private:
    oboe::AudioStreamBuilder builder;
    std::shared_ptr<oboe::AudioStream> mStream;
    std::unique_ptr<SynthAudioSource> mAudioSource {};
public:
    explicit SynthPlayer();

    void start();
    void stop();

    void playSound(bool isDown);

    oboe::DataCallbackResult
    onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) override;
};