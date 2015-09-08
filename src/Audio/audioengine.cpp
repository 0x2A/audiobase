#include "audioengine.h"

#ifdef USE_JACK
#include "aijack.h"
#include "jackchannel.h"
#endif

namespace Audio
{
    AudioEngine::AudioEngine(InterfaceTypes type)
        : QObject()
    {
        m_InterfaceType = type;
        switch(type)
        {
#ifdef USE_JACK
        case InterfaceTypes::Jack:
            m_AudioInterface = new AiJack(this);
            break;
#endif
        }
    }

    AudioEngine::~AudioEngine()
    {
        delete m_AudioInterface;
        m_AudioInterface = 0;
    }

    int AudioEngine::Initialize()
    {
        return m_AudioInterface->Initialize();
    }

    Channel *AudioEngine::CreateChannel()
    {
        Channel *channel;
        switch(m_InterfaceType)
        {
#ifdef USE_JACK
        case InterfaceTypes::Jack:
             channel = new JackChannel(this, this);
            break;
#endif
        }
        return channel;
    }

    int AudioEngine::BufferSize()
    {
        return m_AudioInterface->BufferSize();
    }

    int AudioEngine::SampleRate()
    {
        return m_AudioInterface->SampleRate();
    }

    int AudioEngine::BufferLengthms()
    {

    }
}
