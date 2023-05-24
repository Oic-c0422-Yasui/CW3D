#pragma once
#include "StateBuilder.h"

namespace ActionGame
{

	class StateBuilderDictionary
	{
	private:
		std::map < std::string, StateBuilderPtr > dictionary_;
	public:
		StateBuilderDictionary();
		~StateBuilderDictionary();
	};

}

