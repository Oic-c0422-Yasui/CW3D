#pragma once


#include	"Singleton.h"
#include	"Skill.h"



namespace ActionGame
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

		const SKillPtr Create(const std::string& key, const std::string& button, const std::string& texName,char* state, char* flyState)
		{
			auto& add = std::make_shared<CSkill>();
			m_Skills.push_back(add);

			add->Create(key, button, texName,state, flyState);
			return add;
		}
		const SKillPtr Create(const std::string& key, const std::string& button, const std::string& texName, char* state, char* flyState,const SKillPtr& skill)
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

		void Reset()
		{
			for (auto& skill : m_Skills)
			{
				skill->Reset();
			}
		}

		size_t GetCount() const noexcept
		{
			return m_Skills.size();
		}

		const SKillPtr& GetSkill(int id)
		{
			assert(m_Skills[id]);
			return m_Skills[id];
		}

		const SKillPtr GetSkill(const std::string& key) const noexcept
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
	//ポインタ置き換え
	using SkillControllerPtr = std::shared_ptr<CSkillController>;
}


