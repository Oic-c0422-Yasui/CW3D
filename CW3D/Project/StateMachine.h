#pragma once

#include	"IStateMachine.h"

namespace Sample {

	/**
	 * @brief		ステートマシーン
	 */
	class StateMachine : public IStateMachine, public std::enable_shared_from_this<StateMachine>
	{
	protected:
		/** ステートマップ */
		using StateMap = std::unordered_map< StateKeyType, StatePtr >;
		StateMap		stateMap_;

		/** 現在のステート */
		StatePtr		currentState_;

		StateKeyType	tempChangeKey_;
		
	public:
		/**
		 * @brief		コンストラクタ
		 */
		StateMachine()
			: enable_shared_from_this()
			, stateMap_()
			, currentState_()
			, tempChangeKey_()
		{

		}

		/**
		 * @brief		ステートの追加
		 * @param[in]	state		追加するステート
		 */
		void AddState(const StatePtr& state) override {
			AddState(state->GetKey(), state);
		}

		/**
		 * @brief		ステートの追加
		 * @param[in]	key			ステートキー
		 * @param[in]	state		追加するステート
		 */
		void AddState(const StateKeyType& key, const StatePtr& state) override {
			stateMap_[key] = state;
			state->SetStateMachine(weak_from_this());
		}

		/**
		 * @brief		ステートの変更
		 * @param[in]	key			ステートキー
		 * @return		true		成功
		 *				false		失敗
		 */
		bool ChangeState(const StateKeyType& key) override {
			auto& nextState = stateMap_.find(key);
			if (nextState == stateMap_.end())
			{
				return true;
			}
			//前のステートの終了
			if (currentState_)
			{
				currentState_->End();
			}
			//ステートの更新と開始
			currentState_ = nextState->second;
			currentState_->SetKeepKey(tempChangeKey_);
			currentState_->Start();
			return false;
		}
		/**
		 * @brief		ステートの変更
		 * @param[in]	key			ステートキー
		 * @return		true		成功
		 *				false		失敗
		 */
		bool ChangeState(const StateKeyType& key, const StateKeyType& keepKey) override {
			auto& nextState = stateMap_.find(key);
			if (nextState == stateMap_.end())
			{
				return true;
			}
			//前のステートの終了
			if (currentState_)
			{
				currentState_->End();
			}
			//ステートの更新と開始
			tempChangeKey_ = keepKey;
			currentState_ = nextState->second;
			currentState_->SetKeepKey(tempChangeKey_);
			currentState_->Start();
			return false;
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {
			if (currentState_) { currentState_->InputExecution(); }
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
			if (currentState_) { currentState_->Execution(); }
		}

		/**
		 * @brief		ステート内の接触イベント
		 * @param[in]	type		当たった相手のタイプ
		 * @param[in]	obj			当たった相手のオブジェクト
		 */
		void CollisionEvent(unsigned int type, std::any obj) override {
			if (currentState_) { currentState_->CollisionEvent(type, obj); }
		}

		/**
		 * @brief		現在のステート取得
		 */
		const StatePtr& GetCurrentState() const override {
			return currentState_;
		}

		/**
		 * @brief		現在のステートが指定された名称のものか判断する
		 * @param[in]	key			ステートキー
		 * @return		true		指定されたステート
		 *				false		違う
		 */
		bool IsState(const StateKeyType& key) const override {
			auto& nextState = stateMap_.find(key);
			if (nextState == stateMap_.end())
			{
				return false;
			}
			return nextState->second == currentState_;
		}

		/**
		 * @brief		登録されているすべてのステートをセットアップする
		 */
		void SetUp() const override
		{
			for (auto& state : stateMap_)
			{
				state.second->SetUp();
			}
		}
	};

}