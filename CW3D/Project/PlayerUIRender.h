#pragma once

#include "PlayerHPRender.h"
#include "SkillControllerRender.h"
#include "SkillRenderContainer.h"
#include "UltimateGaugeRender.h"
#include "UltGaugePresenter.h"

namespace ActionGame
{
	/**
	 * @brief		プレイヤーUI
	 */
	class CPlayerUIRender
	{
	private:
		PlayerHPRenderPtr HPRender_;
		SkillControllerRenderPtr skillControllerRender_;
		SkillRenderContainerPtr skillsRender_;
		UltimateGaugeUIRenderPtr UltGaugeRender_;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CPlayerUIRender();

		/**
		 * @brief		デストラクタ
		 */
		~CPlayerUIRender();


		bool Load();

		void Initialize();

		const PlayerHPRenderPtr& GetHPRender() const noexcept
		{
			return HPRender_;
		}

		/**
		 * @brief		プレイヤーUI描画
		 */
		void Render();

		void Release();

	};

	using PlayerUIRenderPtr = std::shared_ptr<CPlayerUIRender>;
}
