#pragma once

#include "PlayerHPRender.h"
#include "SkillControllerRender.h"
#include "SkillRenderContainer.h"
#include "UltimateGaugeRender.h"
#include "UltGaugePresenter.h"

namespace Sample
{
	/**
	 * @brief		プレイヤーHPUI
	 */
	class CPlayerUIRender
	{
	private:
		PlayerHPRenderPtr m_HPRender;
		SkillControllerRenderPtr m_SkillControllerRender;
		SkillRenderContainerPtr m_SkillsRender;
		UltimateGaugeUIRenderPtr m_UltGaugeRender;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CPlayerUIRender()
			: m_HPRender(std::make_shared<CPlayerHPRender>())
			, m_SkillControllerRender(std::make_shared<CSkillControllerRender>())
			, m_SkillsRender(std::make_shared<CSkillRenderContainer>())
			, m_UltGaugeRender(std::make_shared<CUltimateGaugeRender>())
		{

		}

		/**
		 * @brief		デストラクタ
		 */
		~CPlayerUIRender() {
			Release();
		}


		void Load()
		{
			auto& player = ServiceLocator< CPlayer >::GetService();
			m_SkillControllerRender->Load();
			m_HPRender->Load();
			m_SkillsRender->Load();
			m_UltGaugeRender->Load();
			
			CUltGaugePresenter::Present(player, m_UltGaugeRender);
		}

		void Initialize()
		{
			auto GetPosition = [this](const std::string& key) { return m_SkillControllerRender->GetSkillPosition(key); };
			m_SkillsRender->Initialize(GetPosition);
		}

		const PlayerHPRenderPtr& GetHPRender() const noexcept
		{
			return m_HPRender;
		}

		/**
		 * @brief		プレイヤーUI描画
		 */
		void Render() {
			m_SkillControllerRender->Render();
			m_SkillsRender->Render();
			m_HPRender->Render();
			m_UltGaugeRender->Render();
			m_SkillControllerRender->RenderKeyName();
		}

		void Release(void) {
			m_SkillControllerRender->Release();
			m_SkillControllerRender.reset();
			m_SkillsRender->Release();
			m_SkillsRender.reset();
			m_HPRender->Release();
			m_HPRender.reset();
			m_UltGaugeRender->Release();
			m_UltGaugeRender.reset();
		}

	};

	using PlayerUIRenderPtr = std::shared_ptr<CPlayerUIRender>;
}
