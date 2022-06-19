#pragma once

#include	"IStateAI.h"

namespace Sample
{
	/**
	 * @brief		AI処理
	 */
	class StateAI : public IStateAI
	{
	private:
		//アクター
		ActorPtr					actor_;

		//ステートマシン
		StateMachinePtr				stateMachine_;

		//入力クラス
		StateInputPtr				input_;

		/**
		 * @brief		アクター登録
		 */
		void SetActor(const ActorPtr& actor) final { actor_ = actor; }

		/**
		 * @brief		ステートマシン登録
		 */
		void SetStateMachine(const StateMachinePtr& machine) final
		{
			stateMachine_ = machine;
		}

		/**
		 * @brief		入力登録
		 */
		void SetInput(const StateInputPtr& input) final { input_ = input; }
	protected:
		/**
		 * @brief		コンストラクタ
		 */
		StateAI()
			: actor_()
			, stateMachine_()
			, input_() {
		}

		/** privateメンバ取得専用 */
		const ActorPtr& Actor() { return actor_; }
		const StateMachinePtr& StateMachine() { return stateMachine_; }
		const StateInputPtr& Input() { return input_; }

		/**
		 * @brief		利用キーの登録
		 */
		virtual void RegisterKey() = 0;
	public:
		/**
		 * @brief		新規ステートの生成
		 * @return		生成したステート
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