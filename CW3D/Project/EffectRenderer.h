#pragma once
#include "Singleton.h"
#include "Common.h"
#include "Effect.h"


namespace ActionGame
{
	/*
	* @brief	エフェクト描画クラス
	*/
	class EffectRenderer : public Singleton<EffectRenderer>
	{
		friend class Singleton<EffectRenderer>;
	private:
		EffekseerRendererDX11::RendererRef renderer_;
		Effekseer::ManagerRef manager_;
		EffekseerSound::SoundRef sound_;
		EffekseerSound::SoundDataRef soundData_;
		Effekseer::Handle handle_;
		int currentTime_;

		EffectRenderer();

		~EffectRenderer() override;

	public:

		/*
		* @brief	初期設定
		*/
		void SetUp();
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
			return manager_;
		}


	};
}
//簡易アクセス用
#define EffectRendererInstance 	ActionGame::EffectRenderer::GetInstance()

