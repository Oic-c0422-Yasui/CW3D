#include "EffectController.h"
#include "EffectRenderer.h"

void Sample::CEffectController::Create(const Effekseer::Handle& handle, const Vector3& position, EffectCreateParameter param)
{
	SetPosition(handle, position + param.offset);
	SetScale(handle, param.scale);
	SetRotate(handle, param.rotate);
	SetSpeed(handle, param.speed);
}

Sample::EffectPtr Sample::CEffectController::Play(const std::string& resouceName,const Vector3& position, EffectCreateParameter param)
{
	Sample::EffectPtr efc = std::make_shared<Effect>(EffectRendererInstance.Play(resouceName));
	m_Effects.push_back(efc);
	Create(efc->GetHandle(), position, param);
	efc->Initialize(param.offset);
	return efc;
}

void Sample::CEffectController::Update()
{
	for (auto& effect : m_Effects)
	{
		effect->Update();
	}
}

void Sample::CEffectController::Delete()
{
	auto removeIt = std::remove_if(m_Effects.begin(), m_Effects.end(), [&](const EffectPtr& effect) {
		return effect->IsStop() == true; });
	m_Effects.erase(removeIt, m_Effects.end());
}

void Sample::CEffectController::Reset()
{
	m_Effects.clear();
}

void Sample::CEffectController::SetRotate(const Effekseer::Handle& handle, const Vector3& rotate)
{
	EffectRendererInstance.GetManager()->SetRotation(handle, rotate.x, rotate.y, rotate.z);
}

void Sample::CEffectController::SetPosition(const Effekseer::Handle& handle, const Vector3& pos)
{
	EffectRendererInstance.GetManager()->SetLocation(handle, pos.x, pos.y, pos.z);
}

void Sample::CEffectController::SetScale(const Effekseer::Handle& handle, const Vector3& scale)
{
	EffectRendererInstance.GetManager()->SetScale(handle, scale.x, scale.y, scale.z);
}

void Sample::CEffectController::SetColor(const Effekseer::Handle& handle, const Vector4& color)
{
	EffectRendererInstance.GetManager()->SetAllColor(handle, Effekseer::Color(color.r, color.g, color.b, color.a));
}

void Sample::CEffectController::AddPosition(const Effekseer::Handle& handle, const Vector3& pos)
{
	EffectRendererInstance.GetManager()->AddLocation(handle, Effekseer::Vector3D(pos.x, pos.y, pos.z));
}

void Sample::CEffectController::SetSpeed(const Effekseer::Handle& handle,float speed)
{
	EffectRendererInstance.GetManager()->SetSpeed(handle, speed);
}
