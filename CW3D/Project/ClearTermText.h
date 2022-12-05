#pragma once
#include "GameDefine.h"

namespace ActionGame
{
	class ClearTermText
	{
	protected:
		char* m_Description;

	public:
		ClearTermText(char* description)
			:m_Description(description)
		{
		}

		virtual ~ClearTermText() = default;
		virtual void Initialize() = 0;
		virtual void Render();
		
	};

	using ClearTermTextPtr = std::shared_ptr<ClearTermText>;
}