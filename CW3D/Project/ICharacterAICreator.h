#pragma once

#include	"ICharacterAI.h"

namespace ActionGame
{
	/**
	 * @brief		AI生成インターフェイス
	 */
	class __declspec(novtable) ICharacterAICreator
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~ICharacterAICreator() = default;

		/**
		 * @brief		コンストラクタ
		 */
		virtual CharacterAIPtr Create(const ActorPtr& actor, const StateMachinePtr& machine,
			const StateInputPtr& input) = 0;
	};
	//ポインタ置き換え
	using CharacterAICreatorPtr = std::shared_ptr<ICharacterAICreator>;
}