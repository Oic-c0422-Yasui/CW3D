#pragma once


#include	"AttackBaseState.h"
#include	"StormSkillAction.h"
#include	"FixedYInhaleKnockBack.h"


namespace ActionGame {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class StormSkillState : public AttackBaseState
	{
	public:
		/*
		* @brief	�X�e�[�g�p�����[�^
		* @param	AttackFrequencyFrameTime �����蔻��̔����p�x
		* @param	DurationTime �@�U����������
		* @param	ShotStatus �@AABB�̃V���b�g�p�����[�^
		* @param	EffectStatus �@	�G�t�F�N�g�̃p�����[�^
		*/
		struct Parameter : public BaseParam
		{
			float AttackFrequencyFrameTime;
			float DurationTime;
			ShotAABB ShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter m_Parameter;
		/** �ړ��A�N�V���� */
		StormSkillActionPtr			m_SkillAction;
		float						m_AttackTime;

		bool						m_ContinueFlg;
		std::string					m_Key;


	protected:
		virtual const KnockBackPtr GetKnockBack() override { return std::make_shared<CFixedYInhaleKnockBack>(Actor()); }
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.ShotStatus; }
		virtual const EffectCreateParameter& GetCreateEffectStatus() override { return m_Parameter.EffectStatus; }
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		StormSkillState(Parameter param);
			
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