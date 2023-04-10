#include "EffectRenderer.h"

#include "ResourceManager.h"
#include "TimeScaleController.h"
#include "CameraController.h"



ActionGame::EffectRenderer::EffectRenderer()
	: Singleton<EffectRenderer>()
	, currentTime_(0)
	, renderer_()
	, sound_()
	, handle_()
{
}


ActionGame::EffectRenderer::~EffectRenderer()
{
	manager_->StopAllEffects();
	sound_.Reset();
	manager_.Reset();
	renderer_.Reset();
}

void ActionGame::EffectRenderer::SetUp()
{
	// 管理モジュールの設定
	manager_ = ::Effekseer::Manager::Create(8000);

	// 描画モジュールの設定
	renderer_ = ::EffekseerRendererDX11::Renderer::Create(
		g_pGraphics->GetDevice(), g_pGraphics->GetDeviceContext(), 8000);
	manager_->SetSpriteRenderer(renderer_->CreateSpriteRenderer());
	manager_->SetRibbonRenderer(renderer_->CreateRibbonRenderer());
	manager_->SetRingRenderer(renderer_->CreateRingRenderer());
	manager_->SetTrackRenderer(renderer_->CreateTrackRenderer());
	manager_->SetModelRenderer(renderer_->CreateModelRenderer());

	// テクスチャ、モデル、カーブ、マテリアルローダーの設定する。
	// ユーザーが独自で拡張できる。現在はファイルから読み込んでいる。
	manager_->SetTextureLoader(renderer_->CreateTextureLoader());
	manager_->SetModelLoader(renderer_->CreateModelLoader());
	manager_->SetMaterialLoader(renderer_->CreateMaterialLoader());
	manager_->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

	// 投影行列を設定
	const auto& pers = CameraControllerInstance.GetPerspectiveParam();
	renderer_->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovLH(
		pers.Fov,
		pers.Aspect,
		pers.Near, pers.Far));
	//// サウンドモジュールの設定
	//sound_ = ::EffekseerSound::Sound::Create( g_pSound->GetDevice(), 16, 16);

	//// 音再生用インスタンスから再生機能を指定
	//manager_->SetSoundPlayer(sound_->CreateSoundPlayer());

	//// サウンドデータの読込機能を設定する。
	//// ユーザーが独自で拡張できる。現在はファイルから読み込んでいる。
	//manager_->SetSoundLoader(sound_->CreateSoundLoader());
}

Effekseer::Handle ActionGame::EffectRenderer::Play(const std::string& key)
{
	//リソースマネージャーから指定されたエフェクトを取り出す
	Effekseer::EffectRef effect = ResourceManager<Effekseer::EffectRef>::GetInstance().GetResource(key);

	//再生
	return manager_->Play(effect, 0.0f, 0.0f, 0.0f);
}

void ActionGame::EffectRenderer::Update()
{
	manager_->Update(1.0f * TimeScaleControllerInstance.GetTimeScale());
	renderer_->SetTime(currentTime_ / 60.0f * TimeScaleControllerInstance.GetTimeScale());
}

void ActionGame::EffectRenderer::Render()
{
	//カメラコントローラーから座標を取得
	Vector3 pos = CameraControllerInstance.GetPosition();
	Vector3 look = CameraControllerInstance.GetLookPosition();

	//エフェクトのソート
	::Effekseer::Manager::DrawParameter param;
	
	param.CameraPosition = ::Effekseer::Vector3D(pos.x, pos.y, pos.z);
	param.CameraFrontDirection = ::Effekseer::Vector3D(look.x, look.y, look.z) - ::Effekseer::Vector3D(pos.x, pos.y, pos.z);
	Effekseer::Vector3D::Normal(param.CameraFrontDirection, param.CameraFrontDirection);
	param.IsSortingEffectsEnabled = true;
	
	// カメラ行列を設定
	renderer_->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtLH(
			::Effekseer::Vector3D(pos.x, pos.y, pos.z),
			::Effekseer::Vector3D(look.x, look.y, look.z),
			::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));
	renderer_->BeginRendering();
	manager_->Draw(param);
	renderer_->EndRendering();
}
