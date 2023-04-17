#pragma once

#include "Common.h"


namespace ActionGame
{
	/**
	 * @brief		�K�E�Z�X�L���p�t���[��UI
	 */
	class CSkillUltGaugeRender
	{
	private:

		std::shared_ptr<CTexture>			availableSkillFrame_;
		std::shared_ptr<CTexture>			unavailableSKillFrame_;
		std::shared_ptr<CTexture>			gaugeFrame_;

		float								gauge_;
		float								maxGauge_;

		Vector2								position_;
		Vector2								gaugePosition_;


	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CSkillUltGaugeRender();

		/**
		 * @brief		�f�X�g���N�^
		 */
		~CSkillUltGaugeRender();

		/*
		* @brief	�ǂݍ���
		* @return	true�@�Ȃ琬��
		*/
		bool Load();

		/*
		* @brief	������
		* @param	pos UI�̍��W
		*/
		void Initialize(const Vector2& pos);

		/*
		* @brief	�K�E�Z�Q�[�W�ݒ�
		* @param	gauge �K�E�Z�Q�[�W
		*/
		void SetGauge(float gauge)
		{
			gauge_ = gauge;
		}

		/*
		* @brief	�ő�K�E�Z�Q�[�W�ݒ�
		* @param	gauge �ő�K�E�Z�Q�[�W
		*/
		void SetMaxGauge(float gauge)
		{
			maxGauge_ = gauge;
		}


		/**
		 * @brief		�K�E�Z�Q�[�W������
		 */
		void Reset() noexcept;

		/**
		 * @brief		�`��
		 */
		void Render();

		/*
		* @brief		���
		*/
		void Release();
	};

	using SkillUltGaugeRenderPtr = std::shared_ptr<CSkillUltGaugeRender>;
}
