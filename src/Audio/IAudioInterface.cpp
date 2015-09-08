#include "IAudioInterface.h"


Audio::IAudioInterface::IAudioInterface(Audio::AudioEngine *audioEngine)
{
    m_AudioEngine = audioEngine;
}

Audio::IAudioInterface::~IAudioInterface()
{
    //nothing to do here
}
