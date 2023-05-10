#include "SoundPlayer.h"

CSoundPlayer::CSoundPlayer()
	:currentId_(0)
{
	for (int i = 0; i < SOUND_COUNT; i++)
	{
		volume_[i] = 1.0f;
	}
}

CSoundPlayer::~CSoundPlayer()
{
}

SoundId CSoundPlayer::Play(const MyClass::SoundPtr& sound)
{
	assert(sound);

	currentPlaySounds_.push_back(SoundMap{ sound , currentId_++ });

	float volume = volume_[sound->GetType()] * volume_[SOUND_MASTER];
	sound->SetVolume(volume);
	sound->Play();

	return currentId_;
}

bool CSoundPlayer::Stop(SoundId id)
{
	for (auto& sound : currentPlaySounds_)
	{
		if (sound.id == id)
		{
			return sound.sound->Stop();
		}
	}
	return false;
}

bool CSoundPlayer::Stop(SOUND_TYPE type)
{
	for (auto& sound : currentPlaySounds_)
	{
		if (sound.sound->GetType() == type)
		{
			sound.sound->Stop();
		}
	}
	return true;
}

bool CSoundPlayer::AllStop()
{
	for (auto& sound : currentPlaySounds_)
	{
		sound.sound->Stop();
	}

	ResetId();

	return true;
}


bool CSoundPlayer::Pause(SoundId id)
{
	for (auto& sound : currentPlaySounds_)
	{
		if (sound.id == id)
		{
			return sound.sound->Pause();
		}
	}
	return false;
}

bool CSoundPlayer::Resume(SoundId id)
{
	for (auto& sound : currentPlaySounds_)
	{
		if (sound.id == id)
		{
			return sound.sound->Resume();
		}
	}
	return false;
}

bool CSoundPlayer::IsPlay(SoundId id) const noexcept
{
	for (auto& sound : currentPlaySounds_)
	{
		if (sound.id == id)
		{
			return sound.sound->IsPlay();
		}
	}
	return false;
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

}

void CSoundPlayer::DeleteFinishSound() noexcept
{
	auto removeIt = std::remove_if(currentPlaySounds_.begin(), currentPlaySounds_.end(),
					[&](SoundMap sound) { return sound.sound->IsPlay() == false; });
		
	currentPlaySounds_.erase(removeIt, currentPlaySounds_.end());
}

void CSoundPlayer::ResetId() noexcept
{
	currentId_ = 0;
}
