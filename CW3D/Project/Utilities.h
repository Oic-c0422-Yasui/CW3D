#pragma once

#include "Common.h"

namespace MyUtilities
{

	//時間ごとの値を返す
	//戻り値:現在時間での値
	float Timer(float startValue, float currentTime, float endValue, float endTime);

	//時間ごとの値を返す(回転用)
	//戻り値:現在時間での回転値
	float RotateTimer(float startValue, float currentTime, float endValue, float endTime);

	//イージングの種類
	enum class EASING_TYPE {
		LINER,
		IN_SINE,
		OUT_SINE,
		INOUT_SINE,
	};

	//アニメーション用構造体
	typedef struct tag_ANIM_DATA
	{
		float	Time;
		float	Value;
		EASING_TYPE EasingType;
	}ANIM_DATA;
	using ANIM_DATA_ARRAY = std::vector< ANIM_DATA>;

	// アニメーション用構造体
	typedef struct tag_ANIM_V3_DATA
	{
		float	Time;
		Vector3	Value;
		EASING_TYPE EasingType;

	}ANIM_V3_DATA;
	using ANIM_V3_DATA_ARRAY = std::vector< ANIM_V3_DATA>;

	//補間アニメーション
	float InterpolationAnim(float animTime, const ANIM_DATA_ARRAY& animData);

	//補間アニメーション
	float InterpolationAnim(float animTime, ANIM_DATA* animData, int count);

	//補間アニメーション
	Vector3 InterpolationAnim(float animTime, ANIM_V3_DATA* animData, int count);

	//補間アニメーション
	Vector3 InterpolationAnim(float animTime, const ANIM_V3_DATA_ARRAY& animData);

}


