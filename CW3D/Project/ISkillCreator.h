#pragma once
#include	"IActor.h"
#include "SkillDefine.h"
#include "InputDefine.h"
#include "StateDefine.h"

namespace ActionGame {

	/**
	 * @brief		スキル生成
	 */
	class  __declspec(novtable) ISkillCreator
	{
	public:
		/**
		 * @brief		生成
		 */
		virtual bool Create(const ActorPtr& actor) = 0;
	};

	//ポインタ置き換え
	using SkillCreatorPtr = std::shared_ptr<ISkillCreator>;
}