#pragma once

#include "IInput.h"
#include "IActor.h"


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
		 * @brief		�A�N�^�[�o�^
		 */
		virtual void SetActor(ActorPtr actor) = 0;

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
		 * @brief		�ǂݍ��ݎ��̏���
		 */
		virtual void SetUp() = 0;
		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		virtual void Start() = 0;

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		virtual void Execution() = 0;

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		virtual void InputExecution() = 0;

		/**
		 * @brief		�A�N�V�������̏I������
		 */
		virtual void End() = 0;

		/**
		 * @brief		�X�e�[�g���̐ڐG�C�x���g
		 * @param[in]	type		������������̃^�C�v
		 * @param[in]	obj			������������̃I�u�W�F�N�g
		 */
		virtual void CollisionEvent(unsigned int type, std::any obj) = 0;

		/**
		 * @brief		�X�e�[�g�̕ύX
		 * @param[in]	key			�X�e�[�g�L�[
		 * @return		true		����
		 *				false		���s
		 */
		virtual bool ChangeState(const StateKeyType & key) = 0;

		/**
		 * @brief		�X�e�[�g�̕ύX
		 * @param[in]	key			�X�e�[�g�L�[
		 * @param[in]	keepKey		�ێ����Ă����X�e�[�g�L�[
		 * @return		true		����
		 *				false		���s
		 */
		virtual bool ChangeState(const StateKeyType& key, const StateKeyType& keepKey) = 0;

		/**
		 * @brief		�ێ����Ă���X�e�[�g�ŕύX
		 * @return		true		����
		 *				false		���s
		 */
		virtual bool ChangeKeepState() = 0;

		/**
		 * @brief		�X�e�[�g���̎擾
		 */
		virtual const StateKeyType GetKey() const = 0;

		/**
		 * @brief		�ێ����Ă���X�e�[�g���̎擾
		 */
		virtual const StateKeyType GetKeepKey() const = 0;

		virtual void SetKeepKey(const StateKeyType& keepKey) = 0;
	};
	//�|�C���^�u������
	using StatePtr = std::shared_ptr<IState>;
}
