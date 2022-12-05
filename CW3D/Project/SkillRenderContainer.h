#pragma once

#include "SkillRender.h"
#include "SkillPresenter.h"
#include "ServiceLocator.h"

#include "SkillUltGaugePresenter.h"
#include "SkillUltGaugeRender.h"
#include "UltimateSkill.h"
#include "AdditionalSkill.h"

namespace ActionGame
{
	/**
	 * @brief		スキルをまとめて表示する
	 */
	class CSkillRenderContainer
	{
	private:

		std::vector < ActionGame::SkillRenderPtr>	m_SkillRender;
		std::vector < ActionGame::SkillUltGaugeRenderPtr> m_UltGaugeRender;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CSkillRenderContainer()
		{
		}

		/**
		 * @brief		デストラクタ
		 */
		~CSkillRenderContainer() {

		}


		void Load()
		{
			auto& player = ServiceLocator< CPlayer >::GetService();
			auto& skillController = player->GetSkillController();
			for (int i = 0; i < skillController->GetCount(); i++)
			{
				auto& skillPtr = skillController->GetSkill(i);

				SkillRenderPtr render;
				if (std::dynamic_pointer_cast<CAdditionalSkill>(skillPtr) != nullptr)
				{
					//追加攻撃スキルならロード
					auto addRender = std::make_shared<CAdditionalSkillRender>();
					CSkillPresenter::Present(player, addRender, i);
					render = addRender;
				}
				else
				{
					render = std::make_shared<CSkillRender>();
				}
				CSkillPresenter::Present(player, render, i);

				render->Load(skillPtr->GetTexName());
				m_SkillRender.push_back(render);

				//必殺技ならロード
				if (std::dynamic_pointer_cast<CUltimateSkill>(skillPtr) != nullptr)
				{
					auto gauge = std::make_shared<CSkillUltGaugeRender>();
					gauge->Load();
					CSkillUltGaugePresenter::Present(player, gauge, i);
					m_UltGaugeRender.push_back(gauge);
				}
			}
		}

		void Initialize(std::function<Vector2(const std::string&)> fn)
		{
			auto& player = ServiceLocator< CPlayer >::GetService();
			auto& skillController = player->GetSkillController();
			int uindex = 0;
			for (int i = 0; i < skillController->GetCount(); i++)
			{
				auto& skillPtr = skillController->GetSkill(i);
				m_SkillRender[i]->Initialize(fn(skillPtr->GetButton()));

				if (std::dynamic_pointer_cast<CUltimateSkill>(skillPtr) != nullptr)
				{
					m_UltGaugeRender[uindex++]->Initialize(m_SkillRender[i]->GetPosition());
				}
			}
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
			for (int i = 0; i < m_UltGaugeRender.size(); i++)
			{
				m_UltGaugeRender[i]->Render();
			}

		}

		void Release(void) {
			for (int i = 0; i < m_SkillRender.size(); i++)
			{
				m_SkillRender[i].reset();
			}
			m_SkillRender.clear();
			for (int i = 0; i < m_UltGaugeRender.size(); i++)
			{
				m_UltGaugeRender[i].reset();
			}
			m_UltGaugeRender.clear();
		}
	};

	using SkillRenderContainerPtr = std::shared_ptr<CSkillRenderContainer>;
}
