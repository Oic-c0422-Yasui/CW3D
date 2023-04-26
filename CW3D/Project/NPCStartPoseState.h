#pragma once
#include "BaseState.h"
#include "NPCStartPoseAction.h"

namespace ActionGame
{
    /*
    * @brief	NPC�J�n�|�[�Y�X�e�[�g
    */
    class CNPCStartPoseState : public CBaseState
    {
	private:

		//�J�n�|�[�Y�X�e�[�g
		NPCStartPoseActionPtr			action_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CNPCStartPoseState();

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


