#pragma once


#include "Singleton.h"
#include "Common.h"
#include "Skill.h"
#include "SkillData.h"


namespace Sample
{
	class CSkillManager : public Singleton<CSkillManager>
	{
		friend class Singleton<CSkillManager>;
	private:

		std::vector<SKillPtr> m_Skills;
		std::unordered_map<std::string, CSkillData> m_SkillData;

		CSkillManager()
			: Singleton<CSkillManager>()
			, m_Skills()
		{
		}

	public:

		SKillPtr Create(std::string key,std::string button,char* state, char* flyState)
		{
			auto add = std::make_shared<CSkill>();
			m_Skills.push_back(add);
			add->Create(key, button, state, flyState);
			return add;
		}

		void Update()
		{
			for (auto& skill : m_Skills)
			{
				skill->Update();
			}
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

		/*void AddData(std::string)*/

	};
}
//簡易アクセス用
#define SkillManagerInstance 	Sample::CSkillManager::GetInstance()

