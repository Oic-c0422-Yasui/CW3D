#pragma once
#include "Sound.h"

class __declspec(novtable) ISoundRegister
{
public:
	virtual ~ISoundRegister() = default;
	/*
	* @brief	サウンドを追加する
	* @param	sound	登録するサウンドのポインタ
	* @param	tag		登録されているサウンドのタグ
	* @param	name	登録されているサウンドの名前
	*/
	virtual void AddSound(const MyClass::SoundPtr& sound, SCENE_SOUND_TAG tag,const SoundName& name) = 0;
	/*
	* @brief	サウンドをすべて削除する
	*/
	virtual bool DeleteSound() = 0;
	/*
	* @brief	タグ内のサウンドを削除する
	* @param	tag		登録されているサウンドのタグ
	*/
	virtual bool DeleteSound(SCENE_SOUND_TAG tag) = 0;
	/*
	* @brief	タグ内のサウンドを削除する
	* @param	tag		登録されているサウンドのタグ
	* @param	name	登録されているサウンドの名前
	*/
	virtual bool DeleteSound(SCENE_SOUND_TAG tag, const SoundName& name) = 0;
};
