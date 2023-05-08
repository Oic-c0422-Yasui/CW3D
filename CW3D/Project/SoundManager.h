#pragma once
#include "ISoundPlayer.h"
#include "ISoundRegister.h"
#include <map>

class CSoundManager : public ISoundPlayer,ISoundRegister
{
private:
	//�T�E���h����
	using SoundMap = std::unordered_map<SoundName, MyClass::SoundPtr>;
	//�^�O�t���T�E���h����
	using TagSoundMap = std::unordered_map<SCENE_SOUND_TAG, SoundMap>;
	
	TagSoundMap soundMap_;

public:
	CSoundManager();
	~CSoundManager();

	bool Play(const SoundName& name) const override;
};

