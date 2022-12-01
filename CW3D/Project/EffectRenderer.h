#pragma once
#include "Singleton.h"
#include "Common.h"
#include "Effect.h"


namespace Sample
{
	/*
	* @brief	�G�t�F�N�g�`��N���X
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
		* @brief	�����ݒ�
		*/
		void Initialize();
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
			return m_Manager;
		}


	};
}
//�ȈՃA�N�Z�X�p
#define EffectRendererInstance 	Sample::EffectRenderer::GetInstance()

