#pragma once


#include	"AttackBaseState.h"
#include	"EscapeAction.h"


namespace ActionGame {

	/**
	 * @brief		����X�e�[�g
	 */
	class EscapeState : public AttackBaseState
	{
	public:
		/*
		* @brief	�X�e�[�g�p�����[�^
		* @param	ThroughStartTime�@�����蔻��J�n����
		* @param	ThroughEndTime	�@���̓��͗P�\����
		* @param	EscapeStartTime �@����J�n����
		* @param	EscapeTime �@	�@�������
		* @param	EffectStatus �@	�@�G�t�F�N�g�̃p�����[�^
		*/
		struct Parameter : public BaseParam
		{
			float ThroughStartTime;
			float ThroughEndTime;
			float EscapeStartTime;
			float EscapeTime;
		};
	private:
		Parameter m_Parameter;

		/** �ړ��A�N�V���� */
		EscapeActionPtr			m_EscapeAction;

		bool m_ThroughFlg;
		bool m_EscapeFlg;
		float m_EscapeCurrentTime;
	protected:

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		EscapeState(Parameter param);
			

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