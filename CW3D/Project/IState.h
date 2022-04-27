#pragma once

#include "Input.h"


class CPlayer;

namespace Sample
{

	//�L�[
	using StateKeyType = std::string;

	//�O����`
	class IStateMachine;
	using StateMachineWeakPtr = std::weak_ptr<IStateMachine>;

	//�X�e�[�g�C���^�t�F�[�X
	class IState
	{
		//�X�e�[�g�}�V������̂ݓo�^���ł���l��friend�w��
		friend class StateMachine;
	protected:
		/**
		 * @brief		�X�e�[�g�}�V���o�^
		 */
		virtual void SetStateMachine(StateMachineWeakPtr machine) = 0;

		/**
		 * @brief		���͓o�^
		 */
		virtual void SetInput(InputPtr input) = 0;
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~IState() = default;

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		virtual void Start(CPlayer * player) = 0;

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		virtual void Execution(CPlayer * player) = 0;

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		virtual void InputExecution(CPlayer * player) = 0;

		/**
		 * @brief		�A�N�V�������̏I������
		 */
		virtual void End(CPlayer * player) = 0;

		/**
		 * @brief		�X�e�[�g���̐ڐG�C�x���g
		 * @param[in]	type		������������̃^�C�v
		 * @param[in]	obj			������������̃I�u�W�F�N�g
		 */
		virtual void CollisionEvent(CPlayer* player, unsigned int type, std::any obj) = 0;

		/**
		 * @brief		�X�e�[�g�̕ύX
		 * @param[in]	key			�X�e�[�g�L�[
		 * @return		true		����
		 *				false		���s
		 */
		virtual bool ChangeState(CPlayer * player, const StateKeyType & key) = 0;

		/**
		 * @brief		�X�e�[�g���̎擾
		 */
		virtual const StateKeyType GetKey() const = 0;
	};
	//�|�C���^�u������
	using StatePtr = std::shared_ptr<IState>;
}
