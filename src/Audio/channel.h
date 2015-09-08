#ifndef AUDIO_CHANNEL_H
#define AUDIO_CHANNEL_H

#include <QObject>

namespace Audio
{
    class AudioEngine;
    class Channel : public QObject
    {
    public:
        Channel(AudioEngine* audioEngine, QObject *parent = 0);

        virtual void SetBufferSize(int size = 1024) = 0;

        virtual int GetData(float *dataArray) = 0;
        virtual int GetData(float *dataArray, int numberElements) = 0;
        virtual void Write(float *dataArray, int numberElements) = 0;

    Q_SIGNALS:

    public Q_SLOTS:

    protected:
        AudioEngine *m_AudioEngine;
    };
}

#endif // AUDIO_CHANNEL_H
