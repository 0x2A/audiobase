#include "jackchannel.h"
#include "audioengine.h"

namespace Audio
{
    JackChannel::JackChannel(AudioEngine* audioEngine, QObject *parent):
        Channel(audioEngine, parent)
    {
        //Set the default buffer size to 1 second
        m_Buffer = QtJack::AudioRingBuffer(audioEngine->SampleRate()); //TODO: Check if bigger or smaller buffer size is needed
    }

    int JackChannel::GetData(float *dataArray)
    {
        return m_Buffer.read(dataArray, m_AudioEngine->BufferSize());
    }

    int JackChannel::GetData(float *dataArray, int numberElements)
    {
        return m_Buffer.read(dataArray, numberElements);
    }

    void JackChannel::Write(float *dataArray, int numberElements)
    {
        if(m_Buffer.numberOfElementsCanBeWritten() <= 0)
            m_Buffer.reset();
        m_Buffer.write(dataArray, numberElements);
    }

    void JackChannel::SetBufferSize(int size)
    {
        m_Buffer = QtJack::AudioRingBuffer(size);
    }

    void JackChannel::ClearBuffer()
    {
        m_Buffer.reset();
    }

    const QtJack::AudioRingBuffer &JackChannel::GetAudioRingBuffer()
    {
        /*int samples = m_AudioEngine->SampleRate();
        float *buffer = new float[samples];
        for(int i=0; i < samples; i++)
        {
            buffer[i] = (qrand() / (float)INT_MAX) * 0.5f;
        }
        m_Buffer.write(buffer, samples);
        delete buffer;*/
        return m_Buffer;
    }


}

