#pragma once
#include "State.h"

namespace ActionGame
{
    /**
     * @brief		�x�[�X�̃X�e�[�g�N���X
     */
    class CBaseState : public CState
    {
	protected:
		/* �v���C�x�[�g�֐� */

		/*
		* @brief	���E�L�[��������Ă��邩�H
		*/
		bool IsPressHorizontalKey();
		/*
		* @brief	�㉺�L�[��������Ă��邩�H
		*/
		bool IsPressVirticalKey();
		/*
		* @brief	�����ꂩ�̈ړ��L�[��������Ă��邩�H
		*/
		bool IsPressMoveKey();

		/*
		* @brief	�󒆂ɂ��邩�H
		*/
		bool IsFly();

		/*
		* @brief	������Ă���L�[�ɍ��킹���X�L���ɕύX����
		*/
		void ChangeSkillState();

		/*
		* @brief	�^�C���X�P�[�����O�ȉ����H
		*/
		bool IsTimeScaleZero();

		/*
		* @brief	�󒆏�Ԃ��ŏ�ԕύX��؂�ւ���
		* @param	state	�n��X�e�[�g
		* @param	flyState	�󒆃X�e�[�g
		*/
		void SwitchFlyChangeState(const StateKeyType& state, const StateKeyType& flyState);

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CBaseState();

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		virtual void Start() override = 0;

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		virtual void Execution() override = 0;

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		virtual void InputExecution() override = 0;

		/**
		 * @brief		�X�e�[�g���̏I������
		 */
		virtual void End() override = 0;

    };

}

