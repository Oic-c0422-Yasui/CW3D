#pragma once

#include	"json.hpp"
#include	"JsonStageLoader.h"
#include	"JsonDivisionCreator.h"
#include	"StageBase.h"

namespace Sample 
{



class StageCreator
{
private:

public:
	/**
		 * @brief		コンストラクタ
		 */
	StageCreator();

	static StagePtr Create(const DivisionArrayPtr& division);
};

}