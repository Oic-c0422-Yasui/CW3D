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
			//�ړ��p�x
			float my = endValue - startValue;
			MOF_NORMALIZE_RADIANANGLE(my);

			//�����p�x
			float sa = my - startValue;
			MOF_ROTDIRECTION_RADIANANGLE(sa);


			float result = 0;
			if (endTime <= currentTime)
			{
				result = endValue;
			}
			else
			{
				float sa = startValue;
				float endVal = endValue;
				float now = currentTime / endTime;
				result = sa + (endVal - sa) * now;
			}

			return result;
		}
	};

}


