#include "EffectRenderer.h"

#include "ResourceManager.h"
#include "TimeScaleController.h"
#include "CameraController.h"



void ActionGame::EffectRenderer::Initialize()
{
	// �Ǘ����W���[���̐ݒ�
	m_Manager = ::Effekseer::Manager::Create(8000);

	// �`�惂�W���[���̐ݒ�
	m_Renderer = ::EffekseerRendererDX11::Renderer::Create(
		g_pGraphics->GetDevice(), g_pGraphics->GetDeviceContext(), 8000);
	m_Manager->SetSpriteRenderer(m_Renderer->CreateSpriteRenderer());
	m_Manager->SetRibbonRenderer(m_Renderer->CreateRibbonRenderer());
	m_Manager->SetRingRenderer(m_Renderer->CreateRingRenderer());
	m_Manager->SetTrackRenderer(m_Renderer->CreateTrackRenderer());
	m_Manager->SetModelRenderer(m_Renderer->CreateModelRenderer());

	// �e�N�X�`���A���f���A�J�[�u�A�}�e���A�����[�_�[�̐ݒ肷��B
	// ���[�U�[���Ǝ��Ŋg���ł���B���݂̓t�@�C������ǂݍ���ł���B
	m_Manager->SetTextureLoader(m_Renderer->CreateTextureLoader());
	m_Manager->SetModelLoader(m_Renderer->CreateModelLoader());
	m_Manager->SetMaterialLoader(m_Renderer->CreateMaterialLoader());
	m_Manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

	// ���e�s���ݒ�
	m_Renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovLH(
		MOF_ToRadian(30),
		(float)g_pGraphics->GetTargetWidth() / (float)g_pGraphics->GetTargetHeight(),
		1.0f, 500.0f));
	//// �T�E���h���W���[���̐ݒ�
	//m_Sound = ::EffekseerSound::Sound::Create( g_pSound->GetDevice(), 16, 16);

	//// ���Đ��p�C���X�^���X����Đ��@�\���w��
	//m_Manager->SetSoundPlayer(sound->CreateSoundPlayer());

	//// �T�E���h�f�[�^�̓Ǎ��@�\��ݒ肷��B
	//// ���[�U�[���Ǝ��Ŋg���ł���B���݂̓t�@�C������ǂݍ���ł���B
	//m_Manager->SetSoundLoader(sound->CreateSoundLoader());
}

Effekseer::Handle ActionGame::EffectRenderer::Play(const std::string& key)
{
	//���\�[�X�}�l�[�W���[����w�肳�ꂽ�G�t�F�N�g�����o��
	Effekseer::EffectRef effect = ResourceManager<Effekseer::EffectRef>::GetInstance().GetResource(key);

	//�Đ�
	return m_Manager->Play(effect, 0.0f, 0.0f, 0.0f);
}

void ActionGame::EffectRenderer::Update()
{
	m_Manager->Update(1.0f * TimeScaleControllerInstance.GetTimeScale());
	m_Renderer->SetTime(currentTime / 60.0f * TimeScaleControllerInstance.GetTimeScale());
}

void ActionGame::EffectRenderer::Render()
{
	//�J�����R���g���[���[������W���擾
	Vector3 pos = CameraControllerInstance.GetPosition();
	Vector3 look = CameraControllerInstance.GetLookPosition();
	// �J�����s���ݒ�
	m_Renderer->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtLH(
			::Effekseer::Vector3D(pos.x, pos.y, pos.z),
			::Effekseer::Vector3D(look.x, look.y, look.z),
			::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));
	
	::Effekseer::Manager::DrawParameter param;
	param.IsSortingEffectsEnabled = true;
	m_Renderer->BeginRendering();
	m_Manager->Draw(param);
	m_Renderer->EndRendering();
}
