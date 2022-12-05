#pragma once

#include	"State.h"
#include	"RunLandingAction.h"

namespace ActionGame {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class RunLandingState : public State
	{
	private:
		/** �ړ��A�N�V���� */
		RunLandingActionPtr			m_LandingAction;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RunLandingState();
			

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override;

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override;

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override;


		/**
		 * @brief		�X�e�[�g���̏I������
		 */
		void End() override;



		/**
		 * @brief		�X�e�[�g���̐ڐG�C�x���g
		 * @param[in]	type		������������̃^�C�v
		 * @param[in]	obj			������������̃I�u�W�F�N�g
		 */
		void CollisionEvent(unsigned int type, std::any obj) override;

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const StateKeyType GetKey() const override;
	};

}