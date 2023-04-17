#pragma once

#include "PlayerHPRender.h"
#include "SkillInfoRender.h"
#include "SkillRenderContainer.h"
#include "UltimateGaugeRender.h"
#include "UltGaugePresenter.h"
#include "ComboPresenter.h"

namespace ActionGame
{
	/**
	 * @brief		�v���C���[UI
	 */
	class CPlayerUIRender
	{
	private:
		//HP�`��
		PlayerHPRenderPtr			HPRender_;
		//�X�L�����`��
		SkillInfoRenderPtr			skillInfoRender_;
		//�X�L���摜�`��
		SkillRenderContainerPtr		skillsRender_;
		UltimateGaugeUIRenderPtr	UltGaugeRender_;
		//�R���{�`��
		ComboRenderPtr				comboRender_;
		
		//�\���t���O
		bool						isShow_;

	private:
		/* �v���C�x�[�g�֐��@*/
		//UI�\��
		void VisibleUI();
		//UI��\��
		void DisableUI();
		//�L�[�{�[�hUI�\��
		void ChangeKeyBoardUI();
		//�R���g���[���[UI�\��
		void ChangeControllerUI();
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CPlayerUIRender();

		/**
		 * @brief		�f�X�g���N�^
		 */
		~CPlayerUIRender();

		/*
		* @brief	�ǂݍ���
		* @param	player�@�v���C���[
		* @param	device	����f�o�C�X
		* @return	true�@�Ȃ琬��
		*/
		bool Load(const PlayerPtr& player, GameDevice device);

		/*
		* @brief	������
		*/
		void Initialize();

		/**
		 * @brief		UI�`��
		 */
		void Render();

		/**
		 * @brief		���
		 */
		void Release();

	};

	using PlayerUIRenderPtr = std::shared_ptr<CPlayerUIRender>;
}
