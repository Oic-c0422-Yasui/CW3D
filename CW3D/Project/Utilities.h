#pragma once

#include "Common.h"

namespace Sample
{
	class MyUtilities
	{
	public:

		//時間ごとの値を返す
		//戻り値:現在時間での値
		static float Timer(float startValue,float currentTime,float endValue,float endTime)
		{
			float result = 0;
			if (endTime <= currentTime)
			{
				result = endValue;
			}
			else
			{
				float startVal = startValue;
				float endVal = endValue;
				float now = currentTime / endTime;
				result = startVal + (endVal - startVal) * now;
			}

			return result;
		}

		//時間ごとの値を返す(回転用)
		//戻り値:現在時間での回転値
		static float RotateTimer(float startValue, float currentTime, float endValue, float endTime)
		{
			float result = 0;
			//移動角度
			float end = endValue;
			MOF_NORMALIZE_RADIANANGLE(end);
			float start = startValue;
			MOF_NORMALIZE_RADIANANGLE(start);

			
			//差分角度
			float sa = end - start;
			MOF_ROTDIRECTION_RADIANANGLE(sa);

			sa = Timer(start, currentTime, start + sa, endTime);
			result = MOF_NORMALIZE_RADIANANGLE(sa);

			return result;
		}

		//イージングの種類
		enum EASING_TYPE {
			EASE_LINER,
			EASE_IN_SINE,
			EASE_OUT_SINE,
			EASE_INOUT_SINE,
		};

		//アニメーション用構造体
		struct ANIM_DATA
		{
			float	Time;
			float	Value;
			EASING_TYPE EasingType;

		};

		// アニメーション用構造体
		typedef struct tag_ANIMV3_DATA
		{
			float	Time;
			Vector3	Value;
			EASING_TYPE EasingType;

		}ANIMV3_DATA;


		//保管アニメーション
		static float InterpolationAnim(float animTime, ANIM_DATA* animData, int count)
		{
			int phase;
			for (phase = 1; phase < count; phase++)
			{
				if (animTime < animData[phase].Time)
				{
					break;
				}
			}
			phase = min(phase, count - 1);

			float nt = animTime - animData[phase - 1].Time;
			float at = animData[phase].Time - animData[phase - 1].Time;
			float t = nt / at;
			t = MOF_CLIPING(t, 0.0f, 1.0f);

			switch (animData[phase].EasingType)
			{
			case EASE_IN_SINE:
			{
				t = 1.0f - cos(MOF_MATH_HALFPI * t);
				break;
			}
			case EASE_OUT_SINE:
			{
				t = sin(MOF_MATH_HALFPI * t);
				break;
			}
			case EASE_INOUT_SINE:
			{
				t = 0.5f - 0.5f * cos(MOF_MATH_PI * t);
				break;
			}
			default:
				break;
			}

			float from = animData[phase - 1].Value;
			float to = animData[phase].Value;
			return from + (to - from) * t;
		}

		//保管アニメーション
		static Vector3 InterpolationAnim(float animTime, ANIMV3_DATA* animData, int count)
		{
			int phase;
			for (phase = 1; phase < count; phase++)
			{
				if (animTime < animData[phase].Time)
				{
					break;
				}
			}
			phase = min(phase, count - 1);

			float nt = animTime - animData[phase - 1].Time;
			float at = animData[phase].Time - animData[phase - 1].Time;
			float t = nt / at;
			t = MOF_CLIPING(t, 0.0f, 1.0f);

			switch (animData[phase].EasingType)
			{
			case EASE_IN_SINE:
			{
				t = 1.0f - cos(MOF_MATH_HALFPI * t);
				break;
			}
			case EASE_OUT_SINE:
			{
				t = sin(MOF_MATH_HALFPI * t);
				break;
			}
			case EASE_INOUT_SINE:
			{
				t = 0.5f - 0.5f * cos(MOF_MATH_PI * t);
				break;
			}
			default:
				break;
			}

			Vector3 from = animData[phase - 1].Value;
			Vector3 to = animData[phase].Value;
			return from + (to - from) * t;
		}

		
	};

	using AnimV3Ptr = std::shared_ptr<MyUtilities::ANIMV3_DATA>;
}


