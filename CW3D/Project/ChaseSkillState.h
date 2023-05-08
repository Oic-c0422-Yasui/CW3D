#pragma once
#include "AttackBaseState.h"
#include	"DropKickSkillAction.h"
#include	"AdditionalSkill.h"

namespace ActionGame {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class CChaseSkillState : public CAttackBaseState
	{
	public:
		/*
		* @brief	�X�e�[�g�p�����[�^
		* @param	ColliderStartFrameTime �����蔻��J�n����
		* @param	ColliderEndFrameTime �@�����蔻��I������
		* @param	AABBShotStatus �@AABB�̃V���b�g�p�����[�^
		* @param	EffectStatus �@	�G�t�F�N�g�̃p�����[�^
		*/
		struct Parameter : public BaseParam
		{
			float CollideStartTime;
			float CollideEndTime;
			ShotAABB ShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter parameter_;
		/** �ړ��A�N�V���� */
		DropKickSkillActionPtr			action_;

		bool isStartCollide_;
		bool isDelayInput_;
		std::string inputKey_;

		AdditionalWeakSKillPtr skillRef_;

		//������
		void Initialize();
	protected:
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return parameter_.ShotStatus; }
		virtual const EffectCreateParameter& GetCreateEffectStatus() override { return parameter_.EffectStatus; }
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CChaseSkillState(Parameter param);


		/**
		 * @brief		�X�e�[�g�̏�����������
		 */
		void SetUp() override;

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