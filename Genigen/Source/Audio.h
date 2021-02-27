#pragma once

#include "../Dependencies/FModCore/include/fmod.hpp"
#include "../Dependencies/FModCore/include/fmod_common.h"

class Audio
{
public:
	void InitAudio();
	bool isComplete(FMOD::Channel* channel, FMOD::Sound* sound);
	FMOD::Channel* PlaySound(FMOD::Sound* sound, FMOD::ChannelGroup* channelgroup, bool paused);
	FMOD::Sound* CreateSound(const char* filepath, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* exinfo);
	FMOD::System* system;

private:
	unsigned int audioPos = 0;
	unsigned int length = 0;
};
