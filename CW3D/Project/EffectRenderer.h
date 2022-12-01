#pragma once
#include "Singleton.h"
#include "Common.h"
#include "Effect.h"


namespace Sample
{
	/*
	* @brief	エフェクト描画クラス
	*/
	class EffectRenderer : public Singleton<EffectRenderer>
	{
		friend class Singleton<EffectRenderer>;
	private:
		EffekseerRendererDX11::RendererRef m_Renderer;
		Effekseer::ManagerRef m_Manager;
		EffekseerSound::SoundRef m_Sound;
		Effekseer::Handle m_Handle;
		int currentTime;

		EffectRenderer()
			: Singleton<EffectRenderer>()
			, currentTime(0)
		{
		}

	public:

		/*
		* @brief	初期設定
		*/
		void Initialize();
		 /*
		  * @brief	更新
		  */
		 void Update();
		 /*
		  * @brief	描画
		  */
		 void Render();


		/*
		* @brief	エフェクト再生
		* @param	key エフェクトの名前
		* @return	再生ハンドル
		*/
		Effekseer::Handle Play(const std::string& key);

		/*
		* @brief	Effekseerマネージャー取得
		*/
		 Effekseer::ManagerRef& GetManager()
		{
			return m_Manager;
		}


	};
}
//簡易アクセス用
#define EffectRendererInstance 	Sample::EffectRenderer::GetInstance()

