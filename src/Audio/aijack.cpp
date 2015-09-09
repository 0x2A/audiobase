#include "aijack.h"
#include "jackchannel.h"

namespace Audio
{
    AiJack::AiJack(AudioEngine *audioEngine) :
        IAudioInterface(audioEngine)
    {
        connect(&m_Client, SIGNAL(sampleRateChanged(int)), this, SLOT(onSampleRateChanged(int)));
        connect(&m_Client, SIGNAL(bufferSizeChanged(int)), this, SLOT(onBufferSizeChanged(int)));
    }

    AiJack::~AiJack()
    {
        m_Client.disconnectFromServer();
    }

    int AiJack::Initialize(int numInPorts, int numOutPorts)
    {
        m_Client.connectToServer("Audiobase");

        //register input ports
        for(int i=0; i < numInPorts; i++)
        {
            QString name = "in_" + QString::number(i);
            m_InPorts.append(m_Client.registerAudioInPort(name));
        }

        //register output ports
        for(int i=0; i < numOutPorts; i++)
        {
            QString name = "out_" + QString::number(i);
            m_OutPorts[i].audioPort = (m_Client.registerAudioOutPort(name));
        }

        m_Client.setProcessor(this);
        m_Client.activate();

        m_SampleRate = m_Client.sampleRate();
        m_BufferSize = m_Client.bufferSize();

        //connect first two output channels to default system output
        for(int i=0; i < std::min(numOutPorts,2); i++)
        {

            QString name = "system:playback_" + QString::number(i+1);
            m_Client.connect(m_OutPorts[i].audioPort, m_Client.portByName(name));
        }

        return 0;
    }

    int AiJack::BufferSize()
    {
        return m_BufferSize;
    }

    int AiJack::SampleRate()
    {
        return m_SampleRate;
    }


    void AiJack::process(int samples)
    {
        //m_AudioBuffer.copyTo(m_OutPorts.first().buffer(samples));

        for(int i=0; i < m_OutPorts.size(); i++)
        {
            if(m_OutPorts[i].audioPort.isValid() && m_OutPorts[i].connectedChannel)
            {
                JackChannel* jkchnl = dynamic_cast<JackChannel*>(m_OutPorts[i].connectedChannel);
                if(jkchnl) //connected channel is a jackChannel, so we can directly use the RingBuffer
                {
                    auto buffer = jkchnl->GetAudioRingBuffer();
                    m_OutPorts[i].audioPort.buffer(samples).pop(buffer);
                }
                else //its not a jackChannel, so we need to insert the data byte by byte
                {
                    float *buffer = new float[samples];
                    auto chnl = m_OutPorts[i].connectedChannel;
                    chnl->GetData(buffer, samples);
                    auto outBuffer = m_OutPorts[i].audioPort.buffer(samples);
                    for(int j=0; j < samples; j++)
                        outBuffer.write(j, (QtJack::AudioSample)buffer[j]);

                    delete buffer;
                }
            }
        }
    }

    void AiJack::onServerShutdown()
    {
        qDebug() << "Server is shutting down!";
        //TODO: handle the server shutdown and do necessary stuff
    }

    void AiJack::onSampleRateChanged(int sampleRate)
    {
        m_SampleRate = sampleRate;
    }

    void AiJack::onBufferSizeChanged(int bufferSize)
    {
        m_BufferSize = bufferSize;
    }

    void AiJack::ConnectOutputPortToChannel(int id, Channel *channel)
    {
        //check if this id is valid by checking if the audioPort is valid
        if(!m_OutPorts[id].audioPort.isValid())
        {
            m_OutPorts.remove(id); //invalid audiPort so remove this entry we just created by calling [] operator
            return;
        }
        m_OutPorts[id].connectedChannel = channel;
    }

    Channel *AiJack::GetConnectedChannelFromOutputPort(int portId)
    {
        return m_OutPorts[portId].connectedChannel;
    }
}
