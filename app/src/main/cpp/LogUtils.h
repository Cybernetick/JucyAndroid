//
// Created by Ivan Khulup on 23.12.2023.
//

#ifndef SYNTHBRIDGE_LOGUTILS_H
#define SYNTHBRIDGE_LOGUTILS_H

#endif //SYNTHBRIDGE_LOGUTILS_H
#include <android/log.h>


#define LOGE(TAG, TEXT) __android_log_write(ANDROID_LOG_ERROR, TAG, TEXT);
#define LOGD(TAG, TEXT) __android_log_write(ANDROID_LOG_DEBUG, TAG, TEXT);