#pragma once
#include "State.h"
#include "StartPoseAction.h"

namespace ActionGame
{
	/*
	* @brief	�J�n�|�[�Y�X�e�[�g
	*/
    class StartPoseState :  public State
    {
	public:
		/*
		* @brief	�X�e�[�g�p�����[�^
		* @param	Time �|�[�Y����
		*/
		struct Parameter
		{
			float Time;
		};
	private:
		Parameter m_Parameter;

		//�J�n�|�[�Y�A�N�V����
		StartPoseActionPtr			m_Action;
		//���ݎ���
		float						currentTime_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		StartPoseState(Parameter param);

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


