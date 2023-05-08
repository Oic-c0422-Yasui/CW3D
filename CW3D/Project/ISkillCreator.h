#pragma once
#include	"IActor.h"
#include "SkillDefine.h"
#include "InputDefine.h"
#include "StateDefine.h"

namespace ActionGame {

	/**
	 * @brief		�X�L������
	 */
	class  __declspec(novtable) ISkillCreator
	{
	public:
		/**
		 * @brief		����
		 */
		virtual bool Create(const ActorPtr& actor) = 0;
	};

	//�|�C���^�u������
	using SkillCreatorPtr = std::shared_ptr<ISkillCreator>;
}