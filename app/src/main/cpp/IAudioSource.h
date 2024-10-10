//
// Created by Ivan Khulup on 23.12.2023.
//

#ifndef SYNTHBRIDGE_IAUDIOSOURCE_H
#define SYNTHBRIDGE_IAUDIOSOURCE_H

#endif //SYNTHBRIDGE_IAUDIOSOURCE_H

#include <oboe/Oboe.h>
class IAudioSource {
public:
    virtual oboe::Result renderAudio(void* outputBuffer, uint8_t channels_count, int32_t num_frames) = 0;
};