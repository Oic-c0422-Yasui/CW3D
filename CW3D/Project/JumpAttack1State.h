#pragma once


#include	"AttackBaseState.h"
#include	"JumpAttack1Action.h"


namespace ActionGame {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class JumpAttack1State : public AttackBaseState
	{
	public:
		struct Parameter : public BaseParam
		{
			float CollideStartFrameTime;
			ShotAABB ShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter m_Parameter;
		/** �ړ��A�N�V���� */
		JumpAttack1ActionPtr			m_JumpAttack1Action;

		const float EffectStartFrameTime = GameFrameTime * 20.0f;

		bool collideStartFlg;

	protected:
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.ShotStatus; }
		virtual const EffectCreateParameter& GetCreateEffectStatus() override { return m_Parameter.EffectStatus; }
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		JumpAttack1State(Parameter param);
			

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