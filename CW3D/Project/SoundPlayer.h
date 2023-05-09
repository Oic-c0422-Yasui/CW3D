#pragma once
#include "ISoundPlayer.h"
#include <vector>



class CSoundPlayer : public ISoundPlayer
{
private:
	struct SoundMap
	{
		MyClass::SoundPtr sound;
		SoundId id;
	};
	//ÉTÉEÉìÉhé´èë
	
	std::vector<SoundMap> currentPlaySounds_;
	SoundId currentId_;

	float volume_[SOUND_COUNT];

public:
	CSoundPlayer();
	~CSoundPlayer();

	SoundId Play(const MyClass::SoundPtr& sound) override;
	bool Stop(SoundId id) override;
	bool Stop(SOUND_TYPE id) override;
	bool AllStop() override;
	bool Pause(SoundId id) override;
	bool Resume(SoundId id) override;
	bool IsPlay(SoundId id) const noexcept override;
	float GetVolume(SOUND_TYPE type) const noexcept override;
	void SetVolume(SOUND_TYPE type, float volume) noexcept override;
	void DeleteFinishSound() noexcept;
	void ResetId() noexcept;
};

