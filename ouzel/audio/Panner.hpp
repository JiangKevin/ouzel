// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_AUDIO_PANNER_HPP
#define OUZEL_AUDIO_PANNER_HPP

#include "audio/Source.hpp"
#include "audio/Destination.hpp"

namespace ouzel
{
    namespace audio
    {
        class Audio;

        class Panner final: public Source, public Destination
        {
        public:
            Panner(Audio& initAudio);
            ~Panner();

            Panner(const Panner&) = delete;
            Panner& operator=(const Panner&) = delete;

            Panner(Panner&&) = delete;
            Panner& operator=(Panner&&) = delete;

        private:
            Audio& audio;
            uintptr_t nodeId = 0;
        };
    } // namespace audio
} // namespace ouzel

#endif // OUZEL_AUDIO_PANNER_HPP