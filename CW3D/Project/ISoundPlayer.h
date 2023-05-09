#pragma once
#include "SoundDefine.h"

class __declspec(novtable) ISoundPlayer
{
public:
	virtual ~ISoundPlayer() = default;

	virtual bool Play(const MyClass::SoundPtr& sound) const = 0;
	virtual bool Stop(const SoundName& name) const = 0;
	virtual bool Pause(const SoundName& name) const = 0;
	virtual bool Resume(const SoundName& name) const = 0;
	virtual bool IsPlay(const SoundName& name) const = 0;
	virtual float GetVolume(SOUND_TYPE type) const noexcept = 0;
	virtual void SetVolume(SOUND_TYPE type,float volume) noexcept = 0;
};
