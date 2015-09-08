#include "channel.h"

namespace Audio
{
    Channel::Channel(AudioEngine* audioEngine, QObject *parent) : QObject(parent)
    {
        m_AudioEngine = audioEngine;
    }
}
