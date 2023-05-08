#pragma once

#include "NPCStartPoseAction.h"
#include "AttackBaseState.h"

namespace ActionGame
{
	/*
	* @brief	NPC�J�n�|�[�Y�X�e�[�g
	*/
	class CNPCFollowCameraStartPoseState : public CAttackBaseState
	{
	public:
		/*
		* @brief	�X�e�[�g�p�����[�^
		* @param	Time �|�[�Y����
		*/
		struct Parameter
		{
			float Time;
			EffectCreateParameter EffectStatus;
			float EffectStartTime;
		};
	private:
		//�J�n�|�[�Y�X�e�[�g
		NPCStartPoseActionPtr			action_;

		Parameter parameter_;
		
		bool isStart_;
		bool isEffectStart_;

		//�J�����ݒ�
		void SettingCamera();
	protected:

		virtual const EffectCreateParameter& GetCreateEffectStatus() override { return parameter_.EffectStatus; }

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CNPCFollowCameraStartPoseState(Parameter param);

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
