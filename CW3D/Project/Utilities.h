#pragma once

#include "Common.h"

namespace Sample
{
	class MyUtilities
	{
	public:

		//���Ԃ��Ƃ̒l��Ԃ�
		//�߂�l:���ݎ��Ԃł̒l
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

		//���Ԃ��Ƃ̒l��Ԃ�(��]�p)
		//�߂�l:���ݎ��Ԃł̉�]�l
		static float RotateTimer(float startValue, float currentTime, float endValue, float endTime)
		{
			float result = 0;
			//�ړ��p�x
			float end = endValue;
			MOF_NORMALIZE_RADIANANGLE(end);
			float start = startValue;
			MOF_NORMALIZE_RADIANANGLE(start);

			
			//�����p�x
			float sa = end - start;
			MOF_ROTDIRECTION_RADIANANGLE(sa);

			sa = Timer(start, currentTime, start + sa, endTime);
			result = MOF_NORMALIZE_RADIANANGLE(sa);

			return result;
		}

		//�C�[�W���O�̎��
		enum EASING_TYPE {
			EASE_LINER,
			EASE_IN_SINE,
			EASE_OUT_SINE,
			EASE_INOUT_SINE,
		};

		//�A�j���[�V�����p�\����
		struct ANIM_DATA
		{
			float	Time;
			float	Value;
			EASING_TYPE EasingType;

		};

		// �A�j���[�V�����p�\����
		typedef struct tag_ANIMV3_DATA
		{
			float	Time;
			Vector3	Value;
			EASING_TYPE EasingType;

		}ANIMV3_DATA;


		//�ۊǃA�j���[�V����
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

		//�ۊǃA�j���[�V����
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


