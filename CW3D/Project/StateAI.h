#pragma once

#include	"IStateAI.h"

namespace Sample
{
	/**
	 * @brief		AI����
	 */
	class StateAI : public IStateAI
	{
	private:
		//�A�N�^�[
		ActorPtr					actor_;

		//�X�e�[�g�}�V��
		StateMachinePtr				stateMachine_;

		//���̓N���X
		StateInputPtr				input_;

		/**
		 * @brief		�A�N�^�[�o�^
		 */
		void SetActor(const ActorPtr& actor) final { actor_ = actor; }

		/**
		 * @brief		�X�e�[�g�}�V���o�^
		 */
		void SetStateMachine(const StateMachinePtr& machine) final
		{
			stateMachine_ = machine;
		}

		/**
		 * @brief		���͓o�^
		 */
		void SetInput(const StateInputPtr& input) final { input_ = input; }
	protected:
		/**
		 * @brief		�R���X�g���N�^
		 */
		StateAI()
			: actor_()
			, stateMachine_()
			, input_() {
		}

		/** private�����o�擾��p */
		const ActorPtr& Actor() { return actor_; }
		const StateMachinePtr& StateMachine() { return stateMachine_; }
		const StateInputPtr& Input() { return input_; }

		/**
		 * @brief		���p�L�[�̓o�^
		 */
		virtual void RegisterKey() = 0;
	public:
		/**
		 * @brief		�V�K�X�e�[�g�̐���
		 * @return		���������X�e�[�g
		 */
		template < typename T, typename... _Args >
		static std::shared_ptr< T > Create(const ActorPtr& actor, const StateMachinePtr& machine,
			const StateInputPtr& input, _Args&& ... args) {
			if (!std::is_base_of<StateAI, T >::value)
			{
				return std::shared_ptr<T>();
			}
			auto ptr = std::make_shared<T>(args...);
			ptr->SetActor(actor);
			ptr->SetStateMachine(machine);
			ptr->SetInput(input);
			ptr->RegisterKey();
			return ptr;
		}
	};
}