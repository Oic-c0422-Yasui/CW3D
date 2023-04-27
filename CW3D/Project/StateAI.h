#pragma once

#include	"IStateAI.h"
#include	"InputDefine.h"

namespace ActionGame
{
	/**
	 * @brief		AI����
	 */
	class CStateAI : public IStateAI
	{
	private:
		//�A�N�^�[
		ActorPtr					actor_;

		//�X�e�[�g�}�V��
		StateMachinePtr				stateMachine_;

		//���̓N���X
		Input::StateInputPtr				input_;

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
		void SetInput(const Input::StateInputPtr& input) final { input_ = input; }
	protected:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CStateAI()
			: actor_()
			, stateMachine_()
			, input_() {
		}

		/** private�����o�擾��p */
		const ActorPtr& Actor() { return actor_; }
		const StateMachinePtr& StateMachine() { return stateMachine_; }
		const Input::StateInputPtr& Input() { return input_; }

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
			const Input::StateInputPtr& input, _Args&& ... args) {
			if (!std::is_base_of<CStateAI, T >::value)
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