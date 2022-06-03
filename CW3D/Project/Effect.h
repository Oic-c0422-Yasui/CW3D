#pragma once
#include "Common.h"
namespace Sample
{
	struct EffectCreateParameter
	{
		std::string name;
		Vector3 offset;
		Vector3 scale;
		Vector3 rotate;
		float speed;
	};
	class CEffect
	{
		
	private:

		Effekseer::EffectRef				m_Effect;
		Effekseer::Handle					m_Handle;
		CVector3							m_Position;
		Vector3								m_Rotation;
		bool								m_StopFlg;
		Vector3								m_Offset;

	public:

		CEffect(Effekseer::Handle handle)
			: m_Effect()
			, m_Handle(handle) 
			, m_StopFlg(false)
		{
			
		}
		~CEffect();
		void Initialize();
		void Update();

		const bool& IsStop() noexcept
		{
			return  m_StopFlg;
		}

		void SetStop(bool isStop) noexcept
		{
			m_StopFlg = isStop;
		}

		Effekseer::Handle GetHandle()
		{
			return m_Handle;
		}


	
	};

	//ポインタ置き換え
	using EffectPtr = std::shared_ptr<CEffect>;
}

