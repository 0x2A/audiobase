#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <QObject>
#include "IAudioInterface.h"
#include "aitypes.h"
#include "QList"
#include "channel.h"

namespace Audio
{
    class AudioEngine : public QObject
    {
    public:
        explicit AudioEngine(InterfaceTypes type);
        ~AudioEngine();

        int Initialize();

        Channel *CreateChannel();
        int BufferSize();
        int SampleRate();

        int BufferLengthms();

        IAudioInterface *GetAudioInterface() {return m_AudioInterface;}

    Q_SIGNALS:


    public Q_SLOTS:

    private:
        InterfaceTypes m_InterfaceType;
        IAudioInterface *m_AudioInterface;
    };
}

#endif // AUDIOENGINE_H
