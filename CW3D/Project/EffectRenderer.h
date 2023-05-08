#pragma once
#include "Singleton.h"
#include "Common.h"
#include "Effect.h"


namespace ActionGame
{
	/*
	* @brief	�G�t�F�N�g�`��N���X
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
		* @brief	�����ݒ�
		*/
		void SetUp();
		 /*
		  * @brief	�X�V
		  */
		 void Update();
		 /*
		  * @brief	�`��
		  */
		 void Render();


		/*
		* @brief	�G�t�F�N�g�Đ�
		* @param	key �G�t�F�N�g�̖��O
		* @return	�Đ��n���h��
		*/
		Effekseer::Handle Play(const std::string& key);

		/*
		* @brief	Effekseer�}�l�[�W���[�擾
		*/
		 Effekseer::ManagerRef& GetManager()
		{
			return manager_;
		}


	};
}
//�ȈՃA�N�Z�X�p
#define EffectRendererInstance 	ActionGame::EffectRenderer::GetInstance()

