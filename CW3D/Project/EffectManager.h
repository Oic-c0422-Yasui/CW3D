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

			//// �T�E���h���W���[���̐ݒ�
			//sound = ::EffekseerSound::Sound::Create( g_pSound->GetDevice(), 16, 16);

			//// ���Đ��p�C���X�^���X����Đ��@�\���w��
			//manager->SetSoundPlayer(sound->CreateSoundPlayer());

			//// �T�E���h�f�[�^�̓Ǎ��@�\��ݒ肷��B
			//// ���[�U�[���Ǝ��Ŋg���ł���B���݂̓t�@�C������ǂݍ���ł���B
			//manager->SetSoundLoader(sound->CreateSoundLoader());
		}



		Effekseer::Handle Play(const std::string& resouceName)
		{
			//���\�[�X�}�l�[�W���[����w�肳�ꂽ�G�t�F�N�g�����o��
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
			// ���e�s���ݒ�
			m_Renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovLH(
				60.0f / 180.0f * 3.14f,
				(float)g_pGraphics->GetTargetWidth() / (float)g_pGraphics->GetTargetHeight(),
				1.0f, 500.0f));

			// �J�����s���ݒ�
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
//�ȈՃA�N�Z�X�p
#define EffectManagerInstance 	Sample::CEffectManager::GetInstance()

