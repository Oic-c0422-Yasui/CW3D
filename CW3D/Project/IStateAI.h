#pragma once
#include	"IStateMachine.h"
#include	"StateInput.h"

namespace ActionGame
{
	/**
	 * @brief		AI処理インターフェイス
	 */
	class __declspec(novtable) IStateAI
	{
	protected:
		/**
		 * @brief		アクター登録
		 */
		virtual void SetActor(const ActorPtr& actor) = 0;

		/**
		 * @brief		ステートマシン登録
		 */
		virtual void SetStateMachine(const StateMachinePtr& machine) = 0;

		/**
		 * @brief		入力登録
		 */
		virtual void SetInput(const Input::StateInputPtr& input) = 0;
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~IStateAI() = default;

		/**
		 * @brief		開始
		 */
		virtual void Start() = 0;

		/**
		 * @brief		更新
		 */
		virtual void Update() = 0;

		/**
		 * @brief		終了
		 */
		virtual void End() = 0;
	};
	using StateAIPtr = std::shared_ptr<IStateAI>;
	using StateAIMap = std::unordered_map< StateKeyType, StateAIPtr >;
}