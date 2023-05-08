#pragma once

#include	"BaseState.h"
#include	"DamageAction.h"

namespace ActionGame {

	/**
	 * @brief		�_���[�W�X�e�[�g
	 */
	class CDamageState : public CBaseState
	{
	public:
		/*
		* @brief	�X�e�[�g�p�����[�^
		* @param	ColliderStartFrameTime �����蔻��J�n����
		*/
		struct Parameter
		{
			BYTE armor;
		};
	private:
		//�_���[�W�X�e�[�g
		DamageActionPtr			action_;
		Parameter parameter_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CDamageState(Parameter param);
			

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
