//
// Created by Ivan Khulup on 21.12.2023.
//
#include <jni.h>
#include <android/asset_manager_jni.h>
#include "SynthPlayer.h"

std::unique_ptr<SynthPlayer> sPlayer;

extern "C" {

JNIEXPORT void JNICALL
Java_personal_vankhulup_synthbridge_MainActivity_startEngine(JNIEnv *env, jobject thiz, jobject jAssetManager) {
    AAssetManager* assetManager = AAssetManager_fromJava(env, jAssetManager);

    if (assetManager == nullptr) {
        LOGE("JNI-BRIDGE","Could not obtain the AAssetManager");
        return;
    }
    sPlayer = std::make_unique<SynthPlayer>(*assetManager);
    sPlayer->start();
}

JNIEXPORT void JNICALL
Java_personal_vankhulup_synthbridge_MainActivity_stopEngine(JNIEnv *env, jobject thiz) {
    sPlayer->stop();
}

JNIEXPORT void JNICALL
Java_personal_vankhulup_synthbridge_MainActivity_tap(JNIEnv* env, jobject thiz, jboolean isDown) {
    sPlayer->playSound(isDown);
}

}