#pragma once

#include	"IStateAI.h"

namespace ActionGame
{
	/**
	 * @brief		AI処理インターフェイス
	 */
	class __declspec(novtable) ICharacterAI
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~ICharacterAI() = default;

		/**
		 * @brief		更新
		 */
		virtual void Update() = 0;
	};
	using CharacterAIPtr = std::shared_ptr<ICharacterAI>;
}

