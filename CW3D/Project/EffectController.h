#pragma once
#include "Effect.h"
#include "EffectManager.h"
#include "Singleton.h"

namespace Sample 
{
	class CEffectController : public Singleton<CEffectController>
	{
		friend class Singleton<CEffectController>;
	private:
		std::vector<EffectPtr> m_Effects;
		CEffectController()
			: Singleton<CEffectController>()
		{
		}
	public:

		EffectPtr Play(const std::string& resouceName)
		{
			EffectPtr efc = std::make_shared<CEffect>(EffectManagerInstance.Play(resouceName));
			m_Effects.push_back(efc);
			return efc;
		}

		EffectPtr& GetEffect(int id)
		{
			assert(m_Effects[id]);
			return m_Effects[id];
		}

		void Update()
		{
			for (auto& effect : m_Effects)
			{
				effect->Update();
			}
		}

		void SetRotate(const Effekseer::Handle& handle,const Vector3& rotate)
		{
			EffectManagerInstance.GetManager()->SetRotation(handle, rotate.x, rotate.y, rotate.z);
		}

		void SetPosition(const Effekseer::Handle& handle, const Vector3& pos)
		{
			EffectManagerInstance.GetManager()->SetLocation(handle, pos.x, pos.y, pos.z);
		}

		void SetScale(const Effekseer::Handle& handle, const Vector3& scale)
		{
			EffectManagerInstance.GetManager()->SetScale(handle, scale.x, scale.y, scale.z);
		}

		void SetColor(const Effekseer::Handle& handle, const Vector4& color)
		{
			EffectManagerInstance.GetManager()->SetAllColor(handle, Effekseer::Color(color.r, color.g, color.b, color.a));
		}

		void AddPosition(const Effekseer::Handle& handle, const Vector3& pos)
		{
			EffectManagerInstance.GetManager()->AddLocation(handle, Effekseer::Vector3D(pos.x, pos.y, pos.z));
		}

		void SetSpeed(const Effekseer::Handle& handle, const float& speed)
		{
			EffectManagerInstance.GetManager()->SetSpeed(handle, speed);
		}

		void Delete()
		{
			auto removeIt = std::remove_if(m_Effects.begin(), m_Effects.end(), [&](const EffectPtr& effect) {
				return effect->IsStop() == true; });
			m_Effects.erase(removeIt, m_Effects.end());
		}

	};
	//簡易アクセス用
	#define EffectControllerInstance 	Sample::CEffectController::GetInstance()
}



