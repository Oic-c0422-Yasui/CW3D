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
	};

}


