#pragma once


#include	"AttackBaseState.h"
#include	"JumpBeamSkillAction.h"


namespace ActionGame {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class JumpBeamSkillState : public AttackBaseState
	{
	public:
		struct Parameter : public BaseParam
		{
			float CollideStartFrameTime;
			float CollideEndFrameTime;
			ShotAABB AABBShotStatus;
			ShotSphere SphereShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter m_Parameter;
		/** �ړ��A�N�V���� */
		JumpBeamSkillActionPtr			m_SkillAction;

		bool collideStartFlg;

		bool m_DelayInputFlg;

		ShotSphere m_ShotStatusSphere;

		EffectCreateParameter m_EffectStatus;

		//������
		void Initialize();
	protected:
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.AABBShotStatus; }
		virtual const ShotSphere& GetCreateShotStatusSphere() override { return m_ShotStatusSphere; }
		virtual const EffectCreateParameter& GetCreateEffectStatus() override { return m_EffectStatus; }
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		JumpBeamSkillState(Parameter param);

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