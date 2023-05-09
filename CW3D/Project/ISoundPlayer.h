#pragma once
#include "Sound.h"

using SoundId = uint32_t;

class __declspec(novtable) ISoundPlayer
{
public:
	virtual ~ISoundPlayer() = default;

	virtual SoundId Play(const MyClass::SoundPtr& sound) = 0;
	virtual bool Stop(SoundId id) = 0;
	virtual bool Stop(SOUND_TYPE type) = 0;
	virtual bool AllStop() = 0;
	virtual bool Pause(SoundId id) = 0;
	virtual bool Resume(SoundId id) = 0;
	virtual bool IsPlay(SoundId id) const noexcept = 0;
	virtual float GetVolume(SOUND_TYPE type) const noexcept = 0;
	virtual void SetVolume(SOUND_TYPE type,float volume) noexcept = 0;
};
