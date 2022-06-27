#pragma once

#include	"IStateMachine.h"

namespace Sample {

	/**
	 * @brief		ステート生成インターフェイス
	 */
	class __declspec(novtable) IStateCreator
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~IStateCreator() = default;

		/**
		 * @brief		生成
		 */
		virtual bool Create(const StateMachinePtr& stateMachine, const ActorPtr& actor, const InputPtr& input) = 0;
	};
	//ポインタ置き換え
	using StateCreatorPtr = std::shared_ptr<IStateCreator>;
}