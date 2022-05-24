#pragma once
#include "TemplateSingleton.h"
#include "Common.h"
#include "Effect.h"
#include "ResourceManager.h"

namespace Sample
{
	class CEffectManager : public Singleton<CEffectManager>
	{
		friend class Singleton<CEffectManager>;
	private:
		EffekseerRendererDX11::RendererRef m_Renderer;
		Effekseer::ManagerRef m_Manager;
		EffekseerSound::SoundRef m_Sound;

		CEffectManager()
			: Singleton<CEffectManager>()
		{
		}

	public:

		void Set()
		{
			// 管理モジュールの設定
			m_Manager = ::Effekseer::Manager::Create(8000);

			// 描画モジュールの設定
			m_Renderer = ::EffekseerRendererDX11::Renderer::Create(
				g_pGraphics->GetDevice(), g_pGraphics->GetDeviceContext(), 8000);
			m_Manager->SetSpriteRenderer(m_Renderer->CreateSpriteRenderer());
			m_Manager->SetRibbonRenderer(m_Renderer->CreateRibbonRenderer());
			m_Manager->SetRingRenderer(m_Renderer->CreateRingRenderer());
			m_Manager->SetTrackRenderer(m_Renderer->CreateTrackRenderer());
			m_Manager->SetModelRenderer(m_Renderer->CreateModelRenderer());

			// テクスチャ、モデル、カーブ、マテリアルローダーの設定する。
			// ユーザーが独自で拡張できる。現在はファイルから読み込んでいる。
			m_Manager->SetTextureLoader(m_Renderer->CreateTextureLoader());
			m_Manager->SetModelLoader(m_Renderer->CreateModelLoader());
			m_Manager->SetMaterialLoader(m_Renderer->CreateMaterialLoader());
			m_Manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

			//// サウンドモジュールの設定
			//sound = ::EffekseerSound::Sound::Create( g_pSound->GetDevice(), 16, 16);

			//// 音再生用インスタンスから再生機能を指定
			//manager->SetSoundPlayer(sound->CreateSoundPlayer());

			//// サウンドデータの読込機能を設定する。
			//// ユーザーが独自で拡張できる。現在はファイルから読み込んでいる。
			//manager->SetSoundLoader(sound->CreateSoundLoader());
		}



		Effekseer::Handle Play(const std::string& resouceName)
		{
			//リソースマネージャーから指定されたエフェクトを取り出し
			Effekseer::EffectRef effect = ResourceManager<Effekseer::EffectRef>::GetInstance().GetResourceT(resouceName);

			return m_Manager->Play(effect, 0, 0, 0);
		}

		 Effekseer::ManagerRef& GetManager()
		{
			return m_Manager;
		}

		void Update()
		{
			m_Manager->Update();
			//m_Renderer->SetTime();
		}

		void Render()
		{
			// 投影行列を設定
			m_Renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovLH(
				60.0f / 180.0f * 3.14f,
				(float)g_pGraphics->GetTargetWidth() / (float)g_pGraphics->GetTargetHeight(),
				1.0f, 500.0f));

			// カメラ行列を設定
			m_Renderer->SetCameraMatrix(
				::Effekseer::Matrix44().LookAtLH(
					::Effekseer::Vector3D(0, 0, 0),
					::Effekseer::Vector3D(0, 0, 0),
					::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));

			m_Renderer->BeginRendering();
			m_Manager->Draw();
			m_Renderer->EndRendering();
		}



	};
}
//簡易アクセス用
#define EffectManagerInstance 	Sample::CEffectManager::GetInstance()

