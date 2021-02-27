#include "Audio.h"

#include <iostream>

void Audio::InitAudio()
{
	FMOD_RESULT result = FMOD_RESULT::FMOD_OK;
	FMOD::System* _system;
	FMOD::System_Create(&_system);

	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! " << '(' << result << ')' << std::endl;
	}

	_system->init(100, FMOD_INIT_NORMAL, 0);

	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! " << '(' << result << ')' << std::endl;
	}

	system = _system;
}

bool Audio::isComplete(FMOD::Channel* channel, FMOD::Sound* sound)
{
	channel->getPosition(&audioPos, FMOD_TIMEUNIT_MS);
	sound->getLength(&length, FMOD_TIMEUNIT_MS);

	if (audioPos == length)
	{
		return true;
	}

	else
	{
		return false;
	}
}

FMOD::Sound* Audio::CreateSound(const char* filepath, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* exInfo)
{
	FMOD::Sound* sound;
	FMOD_RESULT soundClip = system->createSound(filepath, FMOD_2D, exInfo, &sound);
	if (soundClip != FMOD_RESULT::FMOD_OK)
	{
		std::cout << soundClip << std::endl;
	}
	return sound;
}

FMOD::Channel* Audio::PlaySound(FMOD::Sound* sound, FMOD::ChannelGroup* channelgroup, bool paused)
{
	FMOD::Channel* channel;
	system->playSound(sound, 0, false, &channel);
	return channel;
}