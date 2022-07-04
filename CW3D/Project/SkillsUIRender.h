#pragma once

#include "SkillUIRender.h"
#include "SkillPresenter.h"
#include "ServiceLocator.h"

namespace Sample
{
	/**
	 * @brief		プレイヤーCTUI
	 */
	class SkillsUIRender
	{
	private:

		std::vector < Sample::SkillUIRenderPtr>	m_SkillRender;


	public:
		/**
		 * @brief		コンストラクタ
		 */
		SkillsUIRender()
		{
		}

		/**
		 * @brief		デストラクタ
		 */
		~SkillsUIRender() {
		}


		void Load()
		{
			auto& player = ServiceLocator< CPlayer >::GetService();
			for (int i = 0; i < SKILL_COUNT; i++)
			{
				m_SkillRender.push_back(std::make_shared<SkillUIRender>());
				CSkillPresenter::Present(player, m_SkillRender[i], i);
			}
			m_SkillRender[0]->Load("Skill1");
			m_SkillRender[1]->Load("Skill2");
			m_SkillRender[2]->Load("Skill3");
			m_SkillRender[3]->Load("Escape");
		}

		void Initialize(int num, const Vector2& pos)
		{
			m_SkillRender[num]->Initialize(pos);
		}

		/**
		 * @brief		管理HP初期化
		 */
		void Reset() noexcept {

		}

		/**
		 * @brief		管理スコア初期化
		 */
		void Render() {
			for (int i = 0; i < m_SkillRender.size(); i++)
			{
				m_SkillRender[i]->Render();
			}

		}

		void Release(void) {
			for (int i = 0; i < m_SkillRender.size(); i++)
			{
				m_SkillRender[i].reset();
			}
			m_SkillRender.clear();
		}
	};

	using SkillsUIRenderPtr = std::shared_ptr<SkillsUIRender>;
}
