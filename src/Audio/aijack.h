#ifndef AIJACK_H
#define AIJACK_H

#include "QList"

#include "IAudioInterface.h"
#include "Client"
#include "Processor"
#include "RingBuffer"
#include "QAudioDecoder"
#include "channel.h"

namespace Audio
{
    class AiJack : public IAudioInterface, QtJack::Processor
    {
        Q_OBJECT

    public:

        struct IOPort
        {
            QtJack::AudioPort audioPort;
            Channel* connectedChannel;

            IOPort() : connectedChannel(0)
            {}
        };
        ~AiJack();

        // IAudioInterface interface
        AiJack(AudioEngine *audioEngine);
        void ConnectOutputPortToChannel(int idx, Channel *);
        Channel *GetConnectedChannelFromOutputPort(int portId);

        // IAudioInterface interface
        int Initialize(int numInPorts, int numOutPorts);
        int BufferSize();
        int SampleRate();

        // Processor interface
        void process(int samples);


    public Q_SLOTS:

        void onServerShutdown();
        void onSampleRateChanged(int sampleRate);
        void onBufferSizeChanged(int bufferSize);

    private:

        QtJack::Client m_Client;

        QList<QtJack::AudioPort> m_InPorts;
        QMap<quint32, IOPort> m_OutPorts;

        QtJack::AudioRingBuffer _ringBufferLeft;
        QtJack::AudioRingBuffer _ringBufferRight;
    };
}
#endif // AIJACK_H
