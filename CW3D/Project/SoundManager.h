#pragma once
#include "ISoundPlayer.h"
#include "ISoundRegister.h"
#include <map>

class CSoundManager : public ISoundPlayer,ISoundRegister
{
private:
	//サウンド辞書
	using SoundMap = std::unordered_map<SoundName, MyClass::SoundPtr>;
	//タグ付きサウンド辞書
	using TagSoundMap = std::unordered_map<SCENE_SOUND_TAG, SoundMap>;
	
	TagSoundMap soundMap_;

public:
	CSoundManager();
	~CSoundManager();

	bool Play(const SoundName& name) const override;
};

