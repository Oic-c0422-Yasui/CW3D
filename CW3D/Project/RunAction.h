#pragma once
#include "MoveAction.h"


namespace ActionGame {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class CRunAction : public CMoveAction
	{
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CRunAction(BaseParameter baseParam, Parameter param);
			
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
		 * @brief		���x���Z�b�g
		 */
		void Reset();

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override;
	};
	//�|�C���^�u������
	using RunActionPtr = std::shared_ptr<CRunAction>;

}

