//
// Created by Ivan Khulup on 21.12.2023.
//

#include "SynthPlayer.h"
#include "LogUtils.h"
#include <android/log.h>

SynthPlayer::SynthPlayer(AAssetManager& assetManager) : mAudioSource(SampleAudioSource::newSourceFromAsset(assetManager, "kick_047_sloppy.wav")) {
}

void SynthPlayer::start() {
    oboe::Result result = builder.setSharingMode(oboe::SharingMode::Exclusive)
            ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
            ->setSampleRateConversionQuality(oboe::SampleRateConversionQuality::Best)
            ->setFormat(oboe::AudioFormat::Float)
            ->setFormatConversionAllowed(true)
            ->setDataCallback(this)
            ->setChannelCount(1)
            ->setSampleRate(44100)
            ->openStream(mStream);

    if (result != oboe::Result::OK) {
        LOGE("Synth Player", "Synth player initialization failed with result code: ");
    }

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
    mAudioSource->playOneShotSound();
}

oboe::DataCallbackResult
SynthPlayer::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
    mAudioSource->renderAudio(audioData, audioStream->getChannelCount(), numFrames);
    return oboe::DataCallbackResult::Continue;
}
