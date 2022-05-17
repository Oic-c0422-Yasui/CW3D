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
	};

}


