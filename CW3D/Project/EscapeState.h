#pragma once


#include	"AttackBaseState.h"
#include	"EscapeAction.h"


namespace ActionGame {

	/**
	 * @brief		����X�e�[�g
	 */
	class CEscapeState : public CAttackBaseState
	{
	public:
		/*
		* @brief	�X�e�[�g�p�����[�^
		* @param	ThroughStartTime�@		�����蔻��J�n����
		* @param	ThroughEndTime	�@		���̓��͗P�\����
		* @param	InputAttackStartTime	�U���̓��͉\�J�n����
		* @param	EscapeStartTime �@		����J�n����
		* @param	EscapeTime �@	�@		�������
		*/
		struct Parameter : public BaseParam
		{
			float ThroughStartTime;
			float ThroughEndTime;
			float InputAttackStartTime;
			float EscapeStartTime;
			float EscapeTime;
		};
	private:
		Parameter parameter_;

		/** �ړ��A�N�V���� */
		EscapeActionPtr			action_;

		bool isThrough_;
		bool isEscape_;
		float isEscapeCurrentTime_;
	protected:

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CEscapeState(Parameter param);
			

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