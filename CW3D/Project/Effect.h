#pragma once
#include "Common.h"
#include "ResourceManager.h"
namespace Sample
{
	class CEffect
	{
	private:

		Effekseer::EffectRef				m_Effect;
		Effekseer::Handle					m_Handle;
		CVector3							m_Position;
		bool								m_StopFlg;

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
		void Render();
		void RenderDebug();
		void Render2DDebug();
		void Release();

		const bool& IsStop()
		{
			return  m_StopFlg;
		}

		Effekseer::Handle GetHandle()
		{
			return m_Handle;
		}


	
	};

	//ポインタ置き換え
	using EffectPtr = std::shared_ptr<CEffect>;
}

