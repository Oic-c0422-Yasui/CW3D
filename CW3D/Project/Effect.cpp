#include "Effect.h"
#include "EffectController.h"
#include "TimeScaleController.h"

namespace ActionGame
{
	CEffect::CEffect(Effekseer::Handle handle)
		: handle_(handle)
		, isStop_(false)
		, speed_(1.0f)
	{

	}
	CEffect::~CEffect()
	{

	}

	void CEffect::Initialize( const Vector3& offset,float speed,CHARA_TYPE type)
	{
		offset_ = offset;
		speed_ = speed;
		type_ = type;
	}

	void CEffect::Update()
	{
		if (!EffectControllerInstance.Exists(handle_))
		{
			isStop_ = true;
		}
		if (isStop_)
		{
			EffectControllerInstance.StopEffect(handle_);
		}

		float timeScale = TimeScaleControllerInstance.GetTimeScale(type_);
		EffectControllerInstance.SetSpeed(handle_, speed_ * timeScale);
	}
}