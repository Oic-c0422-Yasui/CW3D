#pragma once

#include	"ICharacterAI.h"
#include	"IAICycle.h"

namespace ActionGame
{
	/**
	 * @brief		AI処理
	 */
	class CharacterStateAI : public ICharacterAI
	{
	protected:
		//ステートマップ
		StateAIMap					stateAIMap_;

		//現在のステート
		StateAIPtr					currentAI_;

		//アクター
		ActorPtr					actor_;

		//ステートマシン
		StateMachinePtr				stateMachine_;

		//入力クラス
		StateInputPtr				input_;

		//入力状態保存
		using KeyMap = std::unordered_map<IInput::KeyType, float >;
		KeyMap						currentKeyVelues_;

		//判定周期
		AICyclePtr					cycle_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CharacterStateAI(const ActorPtr& actor, const StateMachinePtr& machine,
			const StateInputPtr& input, const AICyclePtr& cycle)
			: stateAIMap_()
			, currentAI_()
			, actor_(actor)
			, stateMachine_(machine)
			, input_(input)
			, currentKeyVelues_()
			, cycle_(cycle)
		{
		}

		/**
		 * @brief		デストラクタ
		 */
		~CharacterStateAI() override = default;

		/**
		 * @brief		ステートの追加
		 * @param[in]	key			ステートキー
		 * @param[in]	state		追加するステート
		 */
		void AddStateAI(const StateKeyType& key, const StateAIPtr& state) {
			stateAIMap_[key] = state;
		}

		/**
		 * @brief		利用キーの登録
		 */
		void RegisterKey() {
			auto keys = input_->GetKeyList();
			for (const auto& v : keys)
			{
				currentKeyVelues_.emplace(v, 0.0f);
			}
		}

		/**
		 * @brief		更新
		 */
		void Update() override {
			//周期によって前のキー継続
			if (!cycle_->Update())
			{
				for (const auto& v : currentKeyVelues_)
				{
					input_->SetKeyValue(v.first, v.second);
				}
				return;
			}
			//現在のステートのAI取り出し
			const auto& currentState = stateMachine_->GetCurrentState();
			if (!currentState)
			{
				return;
			}
			auto& stateAI = stateAIMap_.find(currentState->GetKey());
			if (stateAI == stateAIMap_.end())
			{
				if (currentAI_)
				{
					currentAI_->End();
				}
				currentAI_.reset();
				return;
			}
			if (currentAI_ != stateAI->second)
			{
				if (currentAI_)
				{
					currentAI_->End();
				}
				currentAI_ = stateAI->second;
				currentAI_->Start();
			}
			currentAI_->Update();

			//キー状態保存
			for (auto& v : currentKeyVelues_)
			{
				v.second = input_->GetAxis(v.first);
			}
		}
	};

}

