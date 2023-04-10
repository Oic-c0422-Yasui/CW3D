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
	// �Ǘ����W���[���̐ݒ�
	manager_ = ::Effekseer::Manager::Create(8000);

	// �`�惂�W���[���̐ݒ�
	renderer_ = ::EffekseerRendererDX11::Renderer::Create(
		g_pGraphics->GetDevice(), g_pGraphics->GetDeviceContext(), 8000);
	manager_->SetSpriteRenderer(renderer_->CreateSpriteRenderer());
	manager_->SetRibbonRenderer(renderer_->CreateRibbonRenderer());
	manager_->SetRingRenderer(renderer_->CreateRingRenderer());
	manager_->SetTrackRenderer(renderer_->CreateTrackRenderer());
	manager_->SetModelRenderer(renderer_->CreateModelRenderer());

	// �e�N�X�`���A���f���A�J�[�u�A�}�e���A�����[�_�[�̐ݒ肷��B
	// ���[�U�[���Ǝ��Ŋg���ł���B���݂̓t�@�C������ǂݍ���ł���B
	manager_->SetTextureLoader(renderer_->CreateTextureLoader());
	manager_->SetModelLoader(renderer_->CreateModelLoader());
	manager_->SetMaterialLoader(renderer_->CreateMaterialLoader());
	manager_->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

	// ���e�s���ݒ�
	const auto& pers = CameraControllerInstance.GetPerspectiveParam();
	renderer_->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovLH(
		pers.Fov,
		pers.Aspect,
		pers.Near, pers.Far));
	//// �T�E���h���W���[���̐ݒ�
	//sound_ = ::EffekseerSound::Sound::Create( g_pSound->GetDevice(), 16, 16);

	//// ���Đ��p�C���X�^���X����Đ��@�\���w��
	//manager_->SetSoundPlayer(sound_->CreateSoundPlayer());

	//// �T�E���h�f�[�^�̓Ǎ��@�\��ݒ肷��B
	//// ���[�U�[���Ǝ��Ŋg���ł���B���݂̓t�@�C������ǂݍ���ł���B
	//manager_->SetSoundLoader(sound_->CreateSoundLoader());
}

Effekseer::Handle ActionGame::EffectRenderer::Play(const std::string& key)
{
	//���\�[�X�}�l�[�W���[����w�肳�ꂽ�G�t�F�N�g�����o��
	Effekseer::EffectRef effect = ResourceManager<Effekseer::EffectRef>::GetInstance().GetResource(key);

	//�Đ�
	return manager_->Play(effect, 0.0f, 0.0f, 0.0f);
}

void ActionGame::EffectRenderer::Update()
{
	manager_->Update(1.0f * TimeScaleControllerInstance.GetTimeScale());
	renderer_->SetTime(currentTime_ / 60.0f * TimeScaleControllerInstance.GetTimeScale());
}

void ActionGame::EffectRenderer::Render()
{
	//�J�����R���g���[���[������W���擾
	Vector3 pos = CameraControllerInstance.GetPosition();
	Vector3 look = CameraControllerInstance.GetLookPosition();

	//�G�t�F�N�g�̃\�[�g
	::Effekseer::Manager::DrawParameter param;
	
	param.CameraPosition = ::Effekseer::Vector3D(pos.x, pos.y, pos.z);
	param.CameraFrontDirection = ::Effekseer::Vector3D(look.x, look.y, look.z) - ::Effekseer::Vector3D(pos.x, pos.y, pos.z);
	Effekseer::Vector3D::Normal(param.CameraFrontDirection, param.CameraFrontDirection);
	param.IsSortingEffectsEnabled = true;
	
	// �J�����s���ݒ�
	renderer_->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtLH(
			::Effekseer::Vector3D(pos.x, pos.y, pos.z),
			::Effekseer::Vector3D(look.x, look.y, look.z),
			::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));
	renderer_->BeginRendering();
	manager_->Draw(param);
	renderer_->EndRendering();
}
