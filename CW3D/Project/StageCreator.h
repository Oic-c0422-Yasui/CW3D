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
		 * @brief		�R���X�g���N�^
		 */
	StageCreator();

	static StagePtr Create(const DivisionArrayPtr& division);
};

}