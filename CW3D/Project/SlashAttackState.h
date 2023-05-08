#pragma once
#include "AttackBaseState.h"
#include	"Attack3Action.h"
#include	"Attack1Action.h"
#include "FixedYInhaleKnockBack.h"

namespace ActionGame {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class CSlashAttackState : public CAttackBaseState
	{
	public:
		/*
		* @brief	�X�e�[�g�p�����[�^
		* @param	ColliderStartFrameTime �ŏ��̓����蔻��J�n����
		* @param	CollideSecondStartFrameTime �@�Q�Ԗڂ̓����蔻��J�n����
		* @param	EndTime �@�I������
		* @param	AABBShotStatus �@AABB�̃V���b�g�p�����[�^
		* @param	EffectStatus �@	�G�t�F�N�g�̃p�����[�^
		*/
		struct Parameter : public BaseParam
		{
			float CollideFirstStartTime;
			float AnimChangeTime;
			float CollideSecondStartTime;
			float EndTime;
			ShotAABB ShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter parameter_;

		/** �ړ��A�N�V���� */
		Attack3ActionPtr			firstAction_;
		Attack1ActionPtr			secondAction_;


		bool isCollideStartFirst_;
		bool isFirstAnimChange_;
		bool isCollideStartSecond_;
	protected:
		virtual const KnockBackPtr GetKnockBack() { return std::make_shared<CFixedYInhaleKnockBack>(Actor()); }
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return parameter_.ShotStatus; }
		virtual const EffectCreateParameter& GetCreateEffectStatus() override { return parameter_.EffectStatus; }
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CSlashAttackState(Parameter param);


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
