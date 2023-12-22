//
// Created by Ivan Khulup on 21.12.2023.
//

#include "SynthPlayer.h"
#include <android/log.h>

SynthPlayer::SynthPlayer() {
}

void SynthPlayer::start() {
    oboe::Result result = builder.setSharingMode(oboe::SharingMode::Exclusive)
            ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
            ->setFormat(oboe::AudioFormat::Float)
            ->setFormatConversionAllowed(true)
            ->setDataCallback(this)
            ->setChannelCount(1)
            ->openStream(mStream);

    if (result != oboe::Result::OK) {
        LOGE("Synth Player", "Synth player initialization failed with result code: ");
    }
    int channel_count = mStream->getChannelCount();
    int sample_rate = mStream->getSampleRate();
    int samples_per_block = (mStream->getFramesPerBurst() * mStream->getBytesPerFrame()) /
                            mStream->getBytesPerSample();

    mAudioSource = std::make_unique<SynthAudioSource>(sample_rate, samples_per_block,
                                                      channel_count);
    LOGD("Synth Player", "stream build successful")
    mStream->setBufferSizeInFrames(mStream->getFramesPerBurst() * 2);
    oboe::Result streamStart = mStream->requestStart();
    if (streamStart != oboe::Result::OK) {
        LOGD("Synth Player", "Failed to start stream. ");
    }
    LOGD("Synth Player", "stream start successful")
}

void SynthPlayer::stop() {
    mStream->stop();
    mStream->close();
}

void SynthPlayer::playSound(bool isDown) {
    if (isDown) {
        mAudioSource->startNote();
    } else {
        mAudioSource->stopNote();
    }
}

oboe::DataCallbackResult
SynthPlayer::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
    auto sample_count = (numFrames * audioStream->getBytesPerFrame()) / audioStream->getBytesPerSample();
    mAudioSource->renderNext(audioData, sample_count);
    return oboe::DataCallbackResult::Continue;
}
