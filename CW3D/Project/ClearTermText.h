#pragma once
#include "Common.h"

namespace ClearTerm
{
	class CClearTermText
	{
	protected:
		char* description_;

	public:
		CClearTermText(char* description)
			:description_(description)
		{
		}

		virtual ~CClearTermText() = default;
		virtual void Initialize() = 0;
		virtual void Render();
		
	};

	using ClearTermTextPtr = std::shared_ptr<CClearTermText>;
}