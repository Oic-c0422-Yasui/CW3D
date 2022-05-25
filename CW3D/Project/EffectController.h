#pragma once
#include "Effect.h"
#include "EffectManager.h"
#include "TemplateSingleton.h"

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

		void SetRotate(const Effekseer::Handle& handle,const Vector3& rotate)
		{
			EffectManagerInstance.GetManager()->SetRotation(handle, rotate.x, rotate.y, rotate.z);
		}

		void SetPosition(const Effekseer::Handle& handle, const Vector3& pos)
		{
			EffectManagerInstance.GetManager()->SetLocation(handle, pos.x, pos.y, pos.z);
		}

		void SetScale()
		{

		}

		void AddPosition()
		{

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



