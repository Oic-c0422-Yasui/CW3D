#pragma once

#include	"State.h"
#include	"DamageAction.h"

namespace ActionGame {

	/**
	 * @brief		�_���[�W�X�e�[�g
	 */
	class DamageState : public State
	{
	public:
		struct Parameter
		{
			float time;
		};
	private:
		Parameter m_Parameter;
		//�_���[�W�X�e�[�g
		DamageActionPtr			m_DamageAction;
		//���ݎ���
		float						currentTime_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		DamageState(Parameter param);
			

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
