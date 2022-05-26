#pragma once


#include "TemplateSingleton.h"
#include "Common.h"


namespace Sample
{
	class CSkillManager : public Singleton<CSkillManager>
	{
		friend class Singleton<CSkillManager>;
	private:

		CSkillManager()
			: Singleton<CSkillManager>()
		{
		}

	public:

		void Update()
		{
			
		}


	};
}
//簡易アクセス用
#define SkillManagerInstance 	Sample::CSkillManager::GetInstance()

