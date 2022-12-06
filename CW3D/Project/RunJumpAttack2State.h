#pragma once


#include	"AttackBaseState.h"
#include	"RunJumpAttack2Action.h"

namespace ActionGame {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class RunJumpAttack2State : public AttackBaseState
	{
	public:
		/*
		* @brief	�X�e�[�g�p�����[�^
		* @param	NextInputFrameTime �@���̓��͗P�\����
		* @param	AABBShotStatus �@AABB�̃V���b�g�p�����[�^
		*/
		struct Parameter : public BaseParam
		{
			float NextInputFrameTime;
			ShotAABB ShotStatus;
		};
	private:
		Parameter m_Parameter;
		/** �ړ��A�N�V���� */
		RunJumpAttack2ActionPtr			m_Attack2Action;

	protected:
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.ShotStatus; }
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RunJumpAttack2State(Parameter param);
			


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