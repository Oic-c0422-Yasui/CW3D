#pragma once

#include	"BaseState.h"
#include	"DownAction.h"

namespace ActionGame {

	/**
	 * @brief		�_���[�W�X�e�[�g
	 */
	class CDownState : public CBaseState
	{
	public:
		/*
		* @brief	�p�����[�^
		* @param	endTime �I������
		*/
		struct Parameter
		{
			float endTime;
		};
	private:
		Parameter parameter_;

		//�_�E���X�e�[�g
		DownActionPtr				action_;
		//���ݎ���
		float						currentTime_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CDownState(Parameter param);
			

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
