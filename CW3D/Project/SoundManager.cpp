#include "SoundManager.h"

CSoundPlayer::CSoundPlayer()
	:settingId_(0)
{
	for (int i = 0; i < SOUND_COUNT; i++)
	{
		volume_[i] = 1.0f;
	}
}

CSoundPlayer::~CSoundPlayer()
{
}

bool CSoundPlayer::Play(const MyClass::SoundPtr& name) const
{
	currentPlaySounds_.push_back(impl{ name , uid_ });

	return uid_;
}

bool CSoundPlayer::Stop(const SoundName& name) const
{
	return true;
}

bool CSoundPlayer::Pause(const SoundName& name) const
{
	return true;
}

bool CSoundPlayer::Resume(const SoundName& name) const
{
	return true;
}

float CSoundPlayer::GetVolume(SOUND_TYPE type) const noexcept
{
	switch (type)
	{
	case SOUND_SE: volume_[SOUND_SE]; break;
	case SOUND_BGM: volume_[SOUND_BGM]; break;
	case SOUND_MASTER: volume_[SOUND_MASTER]; break;
	default: break;
	}
	return 0.0f;
}

void CSoundPlayer::SetVolume(SOUND_TYPE type, float volume) noexcept
{
	if (type >= SOUND_COUNT) return;

	volume_[type] = std::clamp(volume, 0.0f, 1.0f);

	for(auto)
}
