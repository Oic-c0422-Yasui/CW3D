#pragma once

#include	"BaseState.h"
#include	"IdleAction.h"

namespace ActionGame {

	/**
	 * @brief		�ҋ@�X�e�[�g
	 */
	class CIdleState : public CBaseState
	{
	public:
		struct Parameter
		{
			float idleTime;
		};
	private:
		Parameter parameter_;
		/** �ړ��A�N�V���� */
		IdleActionPtr			action_;
		float					timeScale_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CIdleState(Parameter param);
			

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
		 * @param[in]	parentType		������������̃^�C�v
		 * @param[in]	obj			������������̃I�u�W�F�N�g
		 */
		void CollisionEvent(unsigned int type, std::any obj) override;

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const StateKeyType GetKey() const override;
	};

}