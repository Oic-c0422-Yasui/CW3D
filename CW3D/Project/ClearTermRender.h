#pragma once
#include "GameDefine.h"

namespace Sample
{
	class ClearTermRender
	{
	protected:
		char* m_Description;

	public:
		ClearTermRender()
			:m_Description()
		{
		}

		virtual ~ClearTermRender() = default;
		virtual void Initialize() = 0;
		virtual void Render() = 0;
		
	};

	using ClearTermRenderPtr = std::shared_ptr<ClearTermRender>;
}