#ifndef JACKCHANNEL_H
#define JACKCHANNEL_H

#include "channel.h"
#include "RingBuffer"

namespace Audio
{
    class JackChannel : public Channel
    {
    public:
        JackChannel(AudioEngine* audioEngine, QObject *parent = 0);

        // Channel interface
        int GetData(float *dataArray);
        int GetData(float *dataArray, int numberElements);
        void Write(float *dataArray, int numberElements);
        void SetBufferSize(int size = 1024);

        const QtJack::AudioRingBuffer& GetAudioRingBuffer();

    Q_SIGNALS:

    public Q_SLOTS:

    private:
        QtJack::AudioRingBuffer m_Buffer;
    };
}
#endif // JACKCHANNEL_H
