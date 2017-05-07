#include "audioutil.hpp"
#include <spr/data/audio.hpp>
#include <spr/data/playingaudio.hpp>
#include <gamedata.hpp>
#include <spr/resources/audiosample.hpp>

int32_t queueAudio(spr::StringHash hash, GameData& data)
{
    auto foundSample = spr::findAudioSample(hash, data.spr);
    
    if(foundSample)
    {
        bool alreadyQueued = !findOne([&] (int32_t id, const spr::Audio& audio)
        {
            return audio.sample == *foundSample && !has(id, *data.spr.tPlayingAudio);
        }, *data.spr.tAudio).isNull();

        if(!alreadyQueued)
        {
            insert({*foundSample}, *data.spr.tAudio);
        }
    }
    else
    {
        TH_ASSERT(false, "Error, queuing audio " << hash.string << " which doesn't exist\n");
    }

    return 0;
}
