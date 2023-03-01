#pragma once
#include "MoveAction.h"


namespace ActionGame {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class CRunJumpAction : public CMoveAction
	{
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CRunJumpAction(BaseParameter baseParam, CMoveAction::Parameter moveParam);
			

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override;

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		void Execution() override;

		/**
		 * @brief		�A�N�V�������̏I������
		 */
		void End() override;


		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override;

	};
	//�|�C���^�u������
	using RunJumpActionPtr = std::shared_ptr<CRunJumpAction>;
}

