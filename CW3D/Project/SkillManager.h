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
//�ȈՃA�N�Z�X�p
#define SkillManagerInstance 	Sample::CSkillManager::GetInstance()

