#pragma once

#include <QObject>

namespace Audio
{
    class AudioEngine;
    class Channel;
    class IAudioInterface : public QObject
    {


    public:
        IAudioInterface(AudioEngine *audioEngine);
        virtual ~IAudioInterface();

        virtual int Initialize(int numInPorts = 0, int numOutPorts = 2) = 0;
        //virtual void process(int samples) = 0;

        virtual int BufferSize() = 0;
        virtual int SampleRate() = 0;


        virtual void ConnectOutputPortToChannel(int idx, Channel*) = 0;
        virtual Channel* GetConnectedChannelFromOutputPort(int portId) = 0;

    protected:

        AudioEngine *m_AudioEngine;
        int m_BufferSize;
        int m_SampleRate;
    };

}
