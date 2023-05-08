#include "Sound.h"

MyClass::CSound::CSound()
	: buffer_(nullptr)
	, data_()
{
}

MyClass::CSound::CSound(SoundBufferPtr buffer, const SoundData& data)
	: buffer_(buffer)
	, data_(data)
{
}

MyClass::CSound::CSound(SoundBufferPtr buffer, const SoundData& data)
{
}

MyClass::CSound::~CSound()
{
	buffer_.reset();
}

bool MyClass::CSound::Load(const char* fileName, const SoundData& data)
{
	data_ = data;

	SoundBufferPtr tmp;
	
	switch (data_.type)
	{
	case SOUND_TYPE::BGM:
		tmp = std::make_shared<CStreamingSoundBuffer>();
		break;
	case SOUND_TYPE::SE:
		tmp = std::make_shared<CSoundBuffer>();
		break;
	default: break;
	}

	if (!tmp->Load(fileName)) return false;

	buffer_ = tmp;
	
	return true;
}

bool MyClass::CSound::Load(SoundBufferPtr buffer, const SoundData& data)
{
	if (buffer == nullptr) return false;
	buffer_ = buffer;
	data_ = data;

	return true;
}

bool MyClass::CSound::Play()
{
	return buffer_->Play();
}

bool MyClass::CSound::Stop()
{
	return buffer_->Stop();
}

bool MyClass::CSound::Pause()
{
	return buffer_->Pause();
}

bool MyClass::CSound::Resume()
{
	return buffer_->Resume();
}

bool MyClass::CSound::IsLoop() const noexcept
{
	return buffer_->IsLoop();
}

float MyClass::CSound::GetTime() const noexcept
{
	return buffer_->GetTime();
}

float MyClass::CSound::GetPlayTime() const noexcept
{
	return buffer_->GetPlayTime();
}

float MyClass::CSound::GetVolume() const noexcept
{
	return buffer_->GetVolume();
}

float MyClass::CSound::GetPitch() const noexcept
{
	return buffer_->GetPitch();
}

void MyClass::CSound::SetLoop(bool isLoop) noexcept
{
	buffer_->SetLoop(isLoop);
}

void MyClass::CSound::SetVolume(float volume) noexcept
{
	buffer_->SetVolume(volume);
}

void MyClass::CSound::SetPitch(float pitch) noexcept
{
	buffer_->SetPitch(pitch);
}

