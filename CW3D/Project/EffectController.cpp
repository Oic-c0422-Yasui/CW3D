#include "EffectController.h"
#include "EffectRenderer.h"

void ActionGame::CEffectController::Create(const Effekseer::Handle& handle, const Vector3& position, EffectCreateParameter param)
{
	SetPosition(handle, position + param.offset);
	SetScale(handle, param.scale);
	SetRotate(handle, param.rotate);
	SetSpeed(handle, param.speed);
}

void ActionGame::CEffectController::Create(const Effekseer::Handle& handle, const Vector3& position,const EffectCreateParameterPtr& param)
{
	SetPosition(handle, position + param->offset);
	SetScale(handle, param->scale);
	SetRotate(handle, param->rotate);
	SetSpeed(handle, param->speed);
}

ActionGame::EffectPtr ActionGame::CEffectController::Play(const std::string& resouceName,const Vector3& position, EffectCreateParameter param)
{
	ActionGame::EffectPtr efc = std::make_shared<CEffect>(EffectRendererInstance.Play(resouceName));
	effectArray_.push_back(efc);
	Create(efc->GetHandle(), position, param);
	efc->Initialize(param.offset);
	return efc;
}

ActionGame::EffectPtr ActionGame::CEffectController::Play(const std::string& resouceName, const Vector3& position,const EffectCreateParameterPtr& param)
{
	ActionGame::EffectPtr efc = std::make_shared<CEffect>(EffectRendererInstance.Play(resouceName));
	effectArray_.push_back(efc);
	Create(efc->GetHandle(), position, param);
	efc->Initialize(param->offset);
	return efc;
}

void ActionGame::CEffectController::Update()
{
	for (auto& effect : effectArray_)
	{
		effect->Update();
	}
}

void ActionGame::CEffectController::Delete()
{
	auto removeIt = std::remove_if(effectArray_.begin(), effectArray_.end(), [&](const EffectPtr& effect) {
		return effect->IsStop() == true; });
	effectArray_.erase(removeIt, effectArray_.end());
}

void ActionGame::CEffectController::Reset()
{
	effectArray_.clear();
}

void ActionGame::CEffectController::SetRotate(const Effekseer::Handle& handle, const Vector3& rotate)
{
	EffectRendererInstance.GetManager()->SetRotation(handle, rotate.x, rotate.y, rotate.z);
}

void ActionGame::CEffectController::SetPosition(const Effekseer::Handle& handle, const Vector3& pos)
{
	EffectRendererInstance.GetManager()->SetLocation(handle, pos.x, pos.y, pos.z);
}

void ActionGame::CEffectController::SetScale(const Effekseer::Handle& handle, const Vector3& scale)
{
	EffectRendererInstance.GetManager()->SetScale(handle, scale.x, scale.y, scale.z);
}

void ActionGame::CEffectController::SetColor(const Effekseer::Handle& handle, const Vector4& color)
{
	EffectRendererInstance.GetManager()->SetAllColor(handle, Effekseer::Color(color.r, color.g, color.b, color.a));
}

void ActionGame::CEffectController::AddPosition(const Effekseer::Handle& handle, const Vector3& pos)
{
	EffectRendererInstance.GetManager()->AddLocation(handle, Effekseer::Vector3D(pos.x, pos.y, pos.z));
}

void ActionGame::CEffectController::SetSpeed(const Effekseer::Handle& handle,float speed)
{
	EffectRendererInstance.GetManager()->SetSpeed(handle, speed);
}
