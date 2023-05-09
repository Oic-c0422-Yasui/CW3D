#pragma once
#include "ISoundPlayer.h"
#include "ISoundRegister.h"
#include <map>

class CSoundPlayer : public ISoundPlayer
{
private:
	struct Sound_
	{
		MyClass::SoundPtr sound;
		uint32_t id;
	};
	//ÉTÉEÉìÉhé´èë
	using SoundMap = std::vector<impl>;
	
	SoundMap currentPlaySounds_;
	uint32_t settingId_;

	float volume_[SOUND_COUNT];

public:
	CSoundPlayer();
	~CSoundPlayer();

	bool Play(const MyClass::SoundPtr& sound) const override;
	bool Stop(const SoundName& name) const override;
	bool Pause(const SoundName& name) const override;
	bool Resume(const SoundName& name) const override;
	float GetVolume(SOUND_TYPE type) const noexcept override;
	void SetVolume(SOUND_TYPE type, float volume) noexcept override;

};

