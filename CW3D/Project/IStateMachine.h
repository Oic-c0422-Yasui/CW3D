#pragma once
#include	"IState.h"

namespace Sample {

	/**
	 * @brief		�X�e�[�g�}�V�[���C���^�[�t�F�C�X
	 */
	class IStateMachine
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~IStateMachine() = default;

		/**
		 * @brief		�X�e�[�g�̒ǉ�
		 * @param[in]	state		�ǉ�����X�e�[�g
		 */
		virtual void AddState(const StatePtr& state) = 0;

		/**
		 * @brief		�X�e�[�g�̒ǉ�
		 * @param[in]	key			�X�e�[�g�L�[
		 * @param[in]	state		�ǉ�����X�e�[�g
		 */
		virtual void AddState(const StateKeyType& key, const StatePtr& state) = 0;

		/**
		 * @brief		�X�e�[�g�̕ύX
		 * @param[in]	key			�X�e�[�g�L�[
		 * @return		true		����
		 *				false		���s
		 */
		virtual bool ChangeState( const StateKeyType& key) = 0;

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		virtual void InputExecution() = 0;

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		virtual void Execution() = 0;

		/**
		 * @brief		�X�e�[�g���̐ڐG�C�x���g
		 * @param[in]	type		������������̃^�C�v
		 * @param[in]	obj			������������̃I�u�W�F�N�g
		 */
		virtual void CollisionEvent(unsigned int type, std::any obj) = 0;

		/**
		 * @brief		���݂̃X�e�[�g�擾
		 */
		virtual const StatePtr& GetCurrentState() const = 0;

		/**
		 * @brief		���݂̃X�e�[�g���w�肳�ꂽ�����̂��̂����f����
		 * @param[in]	key			�X�e�[�g�L�[
		 * @return		true		�w�肳�ꂽ�X�e�[�g
		 *				false		�Ⴄ
		 */
		virtual bool IsState(const StateKeyType& key) const = 0;
	};
	//�|�C���^�u������
	using StateMachinePtr = std::shared_ptr<IStateMachine>;
	using StateMachineWeakPtr = std::weak_ptr<IStateMachine>;

}