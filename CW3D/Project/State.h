#pragma once

#include	"StateMachine.h"
#include	"StateDefine.h"
#include	"InputDefine.h"

namespace ActionGame {

	/**
	 * @brief		�X�e�[�g���N���X
	 */
	class CState : public IState
	{
	private:

		/** �A�N�^�[�N���X */
		ActorPtr					actor_;

		/** �����X�e�[�g�}�V�� */
		StateMachineWeakPtr			stateMachine_;

		/** ���̓N���X */
		Input::InputPtr				input_;

		/** �ێ����Ă����L�[�̏��@*/
		StateKeyType				keepKey_;


		/**
		 * @brief		�A�N�^�[�o�^
		 */
		void SetActor(ActorPtr actor) final { actor_ = actor; }

		/**
		 * @brief		�X�e�[�g�}�V���o�^
		 */
		void SetStateMachine(StateMachineWeakPtr machine) final { stateMachine_ = machine; }

		/**
		 * @brief		���͓o�^
		 */
		void SetInput(Input::InputPtr input) final { input_ = input; }
	protected:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CState()
			: actor_()
			, stateMachine_()
			, input_() {
		}

		/** private�����o�擾��p */
		const Input::InputPtr& Input() { return input_; }
		const ActorPtr& Actor() { return actor_; }

		/**
		 * @brief		�ǂݍ��ݎ��̏���
		 */
		void SetUp()override {}

		/**
		 * @brief		�X�e�[�g�̕ύX
		 * @param[in]	key			�X�e�[�g�L�[
		 * @return		true		����
		 *				false		���s
		 */
		bool ChangeState(const StateKeyType& key) override {
			return stateMachine_.lock()->ChangeState(key);
		}
		/**
		 * @brief		�X�e�[�g�̕ύX
		 * @param[in]	key			�X�e�[�g�L�[
		 * @param[in]	keepKey		�ێ����Ă����X�e�[�g�L�[
		 * @return		true		����
		 *				false		���s
		 */
		bool ChangeState(const StateKeyType& key, const StateKeyType& keepKey) override {
			return stateMachine_.lock()->ChangeState(key,keepKey);
		}
		/*
		* @brief	�ێ����Ă����X�e�[�g�ɕύX
		* @retval		true		����
		* @retval		false		���s
		*/
		bool ChangeKeepState() override
		{
			return stateMachine_.lock()->ChangeState(keepKey_);
		}
		/*
		* @brief	�ێ��X�e�[�g�擾
		*/
		const StateKeyType GetKeepKey() const override
		{
			return keepKey_;
		}
		/*
		* @brief	�ێ��X�e�[�g�ݒ�
		* @param[in]	keepKey		�ێ����Ă����X�e�[�g�L�[
		*/
		void SetKeepKey(const StateKeyType& keepKey) noexcept override
		{
			keepKey_ = keepKey;
		}

	public:
		/**
		 * @brief		�V�K�X�e�[�g�̐���
		 * @return		���������X�e�[�g
		 */
		template < typename T, typename... _Args >
		static std::shared_ptr< T > Create(ActorPtr actor, Input::InputPtr input, _Args&& ... args) {
			if (!std::is_base_of<CState, T >::value)
			{
				return std::shared_ptr<T>();
			}
			auto ptr = std::make_shared<T>(args...);
			ptr->SetActor(actor);
			ptr->SetInput(input);
			return ptr;
		}
	};
}