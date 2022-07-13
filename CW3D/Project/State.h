#pragma once

#include	"StateMachine.h"

namespace Sample {

	/**
	 * @brief		ステート基底クラス
	 */
	class State : public IState
	{
	private:

		/** アクタークラス */
		ActorPtr					actor_;

		/** 所属ステートマシン */
		StateMachineWeakPtr			stateMachine_;

		/** 入力クラス */
		InputPtr					input_;

		StateKeyType				tempChangeKey_;


		/**
		 * @brief		アクター登録
		 */
		void SetActor(ActorPtr actor) final { actor_ = actor; }

		/**
		 * @brief		ステートマシン登録
		 */
		void SetStateMachine(StateMachineWeakPtr machine) final { stateMachine_ = machine; }

		/**
		 * @brief		入力登録
		 */
		void SetInput(InputPtr input) final { input_ = input; }
	protected:
		/**
		 * @brief		コンストラクタ
		 */
		State()
			: actor_()
			, stateMachine_()
			, input_() {
		}

		/** privateメンバ取得専用 */
		const InputPtr& Input() { return input_; }
		const ActorPtr& Actor() { return actor_; }

		/**
		 * @brief		読み込み時の処理
		 */
		void SetUp()override {}

		/**
		 * @brief		ステートの変更
		 * @param[in]	key			ステートキー
		 * @return		true		成功
		 *				false		失敗
		 */
		bool ChangeState(const StateKeyType& key) override {
			return stateMachine_.lock()->ChangeState(key);
		}
		/**
		 * @brief		ステートの変更
		 * @param[in]	key			ステートキー
		 * @param[in]	keepKey		保持しておくステートキー
		 * @return		true		成功
		 *				false		失敗
		 */
		bool ChangeState(const StateKeyType& key, const StateKeyType& keepKey) override {
			return stateMachine_.lock()->ChangeState(key,keepKey);
		}

		bool ChangeKeepState() override
		{
			return stateMachine_.lock()->ChangeState(tempChangeKey_);
		}

		const StateKeyType GetKeepKey() const override
		{
			return tempChangeKey_;
		}

		void SetKeepKey(const StateKeyType& keepKey) override
		{
			tempChangeKey_ = keepKey;
		}

	public:
		/**
		 * @brief		新規ステートの生成
		 * @return		生成したステート
		 */
		template < typename T, typename... _Args >
		static std::shared_ptr< T > Create(ActorPtr actor, InputPtr input, _Args&& ... args) {
			if (!std::is_base_of<State, T >::value)
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