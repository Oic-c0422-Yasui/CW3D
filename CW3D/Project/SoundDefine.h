#pragma once
#include "string"

//サウンド名
using SoundName = std::string;

/*
* @brief	サウンドタイプ
*/
enum class SOUND_TYPE
{
	SE,
	BGM
};

/*
* @brief	サウンド効果
*/
enum class SOUND_EFFECT_TYPE
{
	NONE,	//なし
	FADE,	//フェード
};

/*
* @brief	シーン別サウンドタグ
*/
enum class SCENE_SOUND_TAG
{
	ALWAYS, //ずっと使う
	TITLE,	//タイトルシーン
	HOME,	//拠点シーン
	BATTLE	//バトルシーン
};
