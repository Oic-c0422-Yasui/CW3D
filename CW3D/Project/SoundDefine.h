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

	SOUND_MASTER,	//全体のサウンド
	SOUND_COUNT,	//タイプの数
};

/*
* @brief	サウンド効果
*/
enum class SOUND_EFFECT_TYPE
{
	NONE,	//なし
	FADE,	//フェード
};
