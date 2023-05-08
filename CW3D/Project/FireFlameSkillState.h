#pragma once

#include	"AttackBaseState.h"
#include	"NoneGravityAction.h"
#include	"FallAction.h"
#include	"FixedYInhaleKnockBack.h"

namespace ActionGame {

	/**
	 * @brief		�X�e�[�g
	 */
	class CFireFlameSkillState : public CAttackBaseState
	{
	public:
		/*
		* @brief	�X�e�[�g�p�����[�^
		* @param	ChargeTime �����蔻��J�n����
		* @param	ColliderStartFrameTime �����蔻��J�n����
		* @param	ColliderEndFrameTime �@�����蔻��I������
		* @param	EndTime �@��ԏI������
		* @param	AABBShotStatus �@AABB�̃V���b�g�p�����[�^
		* @param	ChargeEffectStatus �@	�G�t�F�N�g�̃p�����[�^
		* @param	EffectStatus �@	�G�t�F�N�g�̃p�����[�^
		*/
		struct Parameter : public BaseParam
		{
			float ChargeTime;
			float CollideStartTime;
			float CollideEndTime;
			float EndTime;
			ShotAABB ShotStatus;
			EffectCreateParameter ChargeEffectStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter parameter_;
		/** �ړ��A�N�V���� */
		NoneGravityActionPtr			nonGravityAction_;
		FallActionPtr					fallAction_;

		bool isStartCollide_;

		float currentChargeTime_;

		bool isLanding_;
	private:
		void SettingCamera();

	protected:
		virtual const KnockBackPtr GetKnockBack() { return std::make_shared<CFixedYInhaleKnockBack>(Actor()); }
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return parameter_.ShotStatus; }
		virtual const EffectCreateParameter& GetCreateEffectStatus() override { return parameter_.EffectStatus; }

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CFireFlameSkillState(Parameter param);



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