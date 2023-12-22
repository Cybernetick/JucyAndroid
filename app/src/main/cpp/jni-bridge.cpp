//
// Created by Ivan Khulup on 21.12.2023.
//
#include <jni.h>
#include "SynthPlayer.h"

static SynthPlayer sPlayer;

extern "C" {

JNIEXPORT void JNICALL
Java_personal_vankhulup_synthbridge_MainActivity_startEngine(JNIEnv *env, jobject thiz) {
    sPlayer.start();
}

JNIEXPORT void JNICALL
Java_personal_vankhulup_synthbridge_MainActivity_stopEngine(JNIEnv *env, jobject thiz) {
    sPlayer.stop();
}

JNIEXPORT void JNICALL
Java_personal_vankhulup_synthbridge_MainActivity_tap(JNIEnv* env, jobject thiz, jboolean isDown) {
    sPlayer.playSound(isDown);
}

}