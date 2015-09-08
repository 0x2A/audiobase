#ifndef AITYPES
#define AITYPES

namespace Audio
{
    enum class InterfaceTypes
    {
#ifdef USE_JACK
       Jack,
#endif
    };
}

#endif // AITYPES

