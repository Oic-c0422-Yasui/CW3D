#pragma once


#include	"AttackBaseState.h"
#include	"BeamSkillAction.h"

namespace ActionGame {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class CBeamSkillState : public CAttackBaseState
	{
	public:
		/*
		* @brief	�X�e�[�g�p�����[�^
		* @param	ColliderStartFrameTime �����蔻��J�n����
		* @param	ColliderEndFrameTime �@�����蔻��I������
		* @param	AABBShotStatus �@AABB�̃V���b�g�p�����[�^
		* @param	OBBShotStatus �@OBB�̃V���b�g�p�����[�^
		* @param	EffectStatus �@	�G�t�F�N�g�̃p�����[�^
		*/
		struct Parameter : public BaseParam
		{
			float CollideStartFrameTime;
			float CollideEndFrameTime;
			ShotAABB AABBShotStatus;
			ShotOBB OBBShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter parameter_;
		/** �ړ��A�N�V���� */
		BeamSkillActionPtr			action_;


		bool isStartCollide_;
		bool isDelayInput_;


		EffectCreateParameter effectStatus_;

		//������
		void Initialize();
	protected:
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return parameter_.AABBShotStatus; }
		virtual const ShotOBB& GetCreateShotStatusOBB() override { return parameter_.OBBShotStatus; }
		virtual const EffectCreateParameter& GetCreateEffectStatus() override { return effectStatus_; }
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CBeamSkillState(Parameter param);
			

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