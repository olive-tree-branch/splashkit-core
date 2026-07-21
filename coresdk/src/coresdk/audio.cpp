#include "audio_driver.h"
#include "audio.h"
#include "resources.h"
#include "backend_types.h"
#include "utility_functions.h"

#include <iostream>
#include <map>

namespace splashkit_lib
{
    static std::map<std::string, sound_effect> _sound_effects;

    struct _sound_data
    {
        pointer_identifier id;
        sk_sound_data effect;
        std::string filename;
        std::string name;
    };

    void open_audio()
    {
        sk_open_audio();
    }

    void close_audio()
    {
        sk_close_audio();
    }

    bool audio_ready()
    {
        return sk_audio_is_open();
    }
}
