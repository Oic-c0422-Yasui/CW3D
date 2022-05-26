#pragma once


#include "TemplateSingleton.h"
#include "Common.h"
#include "Skill.h"


namespace Sample
{
	class CSkillManager : public Singleton<CSkillManager>
	{
		friend class Singleton<CSkillManager>;
	private:

		std::vector<SKillPtr> m_Skills;


		CSkillManager()
			: Singleton<CSkillManager>()
			, m_Skills()
		{
		}

	public:

		SKillPtr Create(std::string key,std::string button,char* name,float ct,int damage)
		{
			auto add = std::make_shared<CSkill>();
			m_Skills.push_back(add);
			add->Create(key, button, name, ct, damage);
			return add;
		}

		size_t GetCount() const noexcept
		{
			return m_Skills.size();
		}

		SKillPtr GetSkill(int id)
		{
			assert(m_Skills[id]);
			return m_Skills[id];
		}

		SKillPtr GetSkill(std::string key)
		{
			for (auto& skill : m_Skills)
			{
				if (skill->GetKey() == key)
				{
					return skill;
				}
			}
			return nullptr;
		}



	};
}
//簡易アクセス用
#define SkillManagerInstance 	Sample::CSkillManager::GetInstance()

