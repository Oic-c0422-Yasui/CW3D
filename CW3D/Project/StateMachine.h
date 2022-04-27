#pragma once

#include	"IStateMachine.h"

namespace Sample {

	/**
	 * @brief		�X�e�[�g�}�V�[��
	 */
	class StateMachine : public IStateMachine, public std::enable_shared_from_this<StateMachine>
	{
	protected:
		/** �X�e�[�g�}�b�v */
		using StateMap = std::unordered_map< StateKeyType, StatePtr >;
		StateMap		stateMap_;

		/** ���݂̃X�e�[�g */
		StatePtr		currentState_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		StateMachine()
			: enable_shared_from_this()
			, stateMap_()
			, currentState_()
		{

		}

		/**
		 * @brief		�X�e�[�g�̒ǉ�
		 * @param[in]	state		�ǉ�����X�e�[�g
		 */
		void AddState(const StatePtr& state) override {
			AddState(state->GetKey(), state);
		}

		/**
		 * @brief		�X�e�[�g�̒ǉ�
		 * @param[in]	key			�X�e�[�g�L�[
		 * @param[in]	state		�ǉ�����X�e�[�g
		 */
		void AddState(const StateKeyType& key, const StatePtr& state) override {
			stateMap_[key] = state;
			state->SetStateMachine(weak_from_this());
		}

		/**
		 * @brief		�X�e�[�g�̕ύX
		 * @param[in]	key			�X�e�[�g�L�[
		 * @return		true		����
		 *				false		���s
		 */
		bool ChangeState(CPlayer* player, const StateKeyType& key) override {
			auto& nextState = stateMap_.find(key);
			if (nextState == stateMap_.end())
			{
				return true;
			}
			//�O�̃X�e�[�g�̏I��
			if (currentState_)
			{
				currentState_->End(player);
			}
			//�X�e�[�g�̍X�V�ƊJ�n
			currentState_ = nextState->second;
			currentState_->Start(player);
			return false;
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution(CPlayer* player) override {
			if (currentState_) { currentState_->InputExecution(player); }
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution(CPlayer* player) override {
			if (currentState_) { currentState_->Execution(player); }
		}

		/**
		 * @brief		�X�e�[�g���̐ڐG�C�x���g
		 * @param[in]	type		������������̃^�C�v
		 * @param[in]	obj			������������̃I�u�W�F�N�g
		 */
		void CollisionEvent(CPlayer* player, unsigned int type, std::any obj) override {
			if (currentState_) { currentState_->CollisionEvent(player, type, obj); }
		}

		/**
		 * @brief		���݂̃X�e�[�g�擾
		 */
		const StatePtr& GetCurrentState() const override {
			return currentState_;
		}

		/**
		 * @brief		���݂̃X�e�[�g���w�肳�ꂽ���̂̂��̂����f����
		 * @param[in]	key			�X�e�[�g�L�[
		 * @return		true		�w�肳�ꂽ�X�e�[�g
		 *				false		�Ⴄ
		 */
		bool IsState(const StateKeyType& key) const override {
			auto& nextState = stateMap_.find(key);
			if (nextState == stateMap_.end())
			{
				return false;
			}
			return nextState->second == currentState_;
		}
	};

}