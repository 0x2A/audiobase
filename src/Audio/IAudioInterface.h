#pragma once

namespace Audio
{

    class IAudioInterface
    {
    public:

        virtual int Initialize() = 0;
        virtual void process(int samples) = 0;

    protected:

    };

}
