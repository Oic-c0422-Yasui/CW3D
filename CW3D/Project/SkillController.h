#pragma once


#include	"Singleton.h"
#include	"Skill.h"
#include	"AdditionalSkill.h"


namespace Sample
{
	class CSkillController
	{
	private:

		std::vector<SKillPtr> m_Skills;

	public:

		CSkillController()
			: m_Skills()
		{
		}

		SKillPtr Create(const std::string& key, const std::string& button, const std::string& texName,char* state, char* flyState)
		{
			auto& add = std::make_shared<CSkill>();
			m_Skills.push_back(add);

			add->Create(key, button, texName,state, flyState);
			return add;
		}
		SKillPtr Create(const std::string& key, const std::string& button, const std::string& texName, char* state, char* flyState,const SKillPtr& skill)
		{
			auto& add = skill;
			m_Skills.push_back(add);

			add->Create(key, button, texName, state, flyState);
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

		AdditionalSKillPtr GetAddSkill(int id)
		{
			assert(m_Skills[id]);
			auto skill = std::static_pointer_cast<CAdditionalSkill>(m_Skills[id]);
			if (skill != nullptr)
			{
				return skill;
			}
			return nullptr;
		}

	};
	//ポインタ置き換え
	using SkillControllerPtr = std::shared_ptr<CSkillController>;
}


