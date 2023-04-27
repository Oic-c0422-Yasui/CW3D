#pragma once

#include	"IStateCreator.h"




namespace ActionGame {

	/**
	 * @brief		ステート生成インターフェイス
	 */
	class PlayerStateCreator : public IStateCreator
	{
	public:
		/**
		 * @brief		生成
		 */
		bool Create(const StateMachinePtr& stateMachine,
					const ActorPtr& actor,
					const Input::InputPtr& input) override;
			
	};
}