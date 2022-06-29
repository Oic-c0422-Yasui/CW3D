#pragma once
#include	"Skill.h"

namespace Sample
{
	class CAdditionalSkill : public CSkill
	{
	private:
		float	m_AdditionalTime;

		int		m_AdditionalCount;

	public:
		CAdditionalSkill()
			:CSkill()
		{
		}
		~CAdditionalSkill()
		{
		}


	};

	//�|�C���^�u������
	using AdditionalSKillPtr = std::shared_ptr<CAdditionalSkill>;
}