#pragma once
#include "string"

//サウンド名
using SoundName = std::string;

/*
* @brief	サウンドタイプ
*/
enum SOUND_TYPE
{
	SOUND_SE,
	SOUND_BGM,
	SOUND_MASTER,

	SOUND_COUNT,
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
