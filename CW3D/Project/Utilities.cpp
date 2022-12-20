#include "Utilities.h"

using namespace MyUtilities;

float MyUtilities::Timer(float startValue, float currentTime, float endValue, float endTime)
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

float MyUtilities::RotateTimer(float startValue, float currentTime, float endValue, float endTime)
{
	float result = 0;
	//ˆÚ“®Šp“x
	float end = endValue;
	MOF_NORMALIZE_RADIANANGLE(end);
	float start = startValue;
	MOF_NORMALIZE_RADIANANGLE(start);


	//·•ªŠp“x
	float sa = end - start;
	MOF_ROTDIRECTION_RADIANANGLE(sa);

	sa = Timer(start, currentTime, start + sa, endTime);
	result = MOF_NORMALIZE_RADIANANGLE(sa);

	return result;
}

float MyUtilities::InterpolationAnim(float animTime, const ANIM_DATA_ARRAY& animData)

{
	int phase;
	int count = animData.size();
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
	if (at <= 0.0f)
	{
		return animData[phase].Value;
	}
	float t = nt / at;
	t = MOF_CLIPING(t, 0.0f, 1.0f);

	switch (animData[phase].EasingType)
	{
	case EASING_TYPE::IN_SINE:
	{
		t = 1.0f - cos(MOF_MATH_HALFPI * t);
		break;
	}
	case EASING_TYPE::OUT_SINE:
	{
		t = sin(MOF_MATH_HALFPI * t);
		break;
	}
	case EASING_TYPE::INOUT_SINE:
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

float MyUtilities::InterpolationAnim(float animTime, ANIM_DATA* animData, int count)

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
	case EASING_TYPE::IN_SINE:
	{
		t = 1.0f - cos(MOF_MATH_HALFPI * t);
		break;
	}
	case EASING_TYPE::OUT_SINE:
	{
		t = sin(MOF_MATH_HALFPI * t);
		break;
	}
	case EASING_TYPE::INOUT_SINE:
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

Vector3 MyUtilities::InterpolationAnim(float animTime, ANIM_V3_DATA* animData, int count)

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
	case EASING_TYPE::IN_SINE:
	{
		t = 1.0f - cos(MOF_MATH_HALFPI * t);
		break;
	}
	case EASING_TYPE::OUT_SINE:
	{
		t = sin(MOF_MATH_HALFPI * t);
		break;
	}
	case EASING_TYPE::INOUT_SINE:
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

Vector3 MyUtilities::InterpolationAnim(float animTime, const ANIM_V3_DATA_ARRAY& animData)

{
	int phase;
	int count = animData.size();
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
	case EASING_TYPE::IN_SINE:
	{
		t = 1.0f - cos(MOF_MATH_HALFPI * t);
		break;
	}
	case EASING_TYPE::OUT_SINE:
	{
		t = sin(MOF_MATH_HALFPI * t);
		break;
	}
	case EASING_TYPE::INOUT_SINE:
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
