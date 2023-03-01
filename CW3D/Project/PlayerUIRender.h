#pragma once

#include "PlayerHPRender.h"
#include "SkillControllerRender.h"
#include "SkillRenderContainer.h"
#include "UltimateGaugeRender.h"
#include "UltGaugePresenter.h"

namespace ActionGame
{
	/**
	 * @brief		�v���C���[UI
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
		 * @brief		�R���X�g���N�^
		 */
		CPlayerUIRender();

		/**
		 * @brief		�f�X�g���N�^
		 */
		~CPlayerUIRender();


		bool Load();

		void Initialize();

		const PlayerHPRenderPtr& GetHPRender() const noexcept
		{
			return HPRender_;
		}

		/**
		 * @brief		�v���C���[UI�`��
		 */
		void Render();

		void Release();

	};

	using PlayerUIRenderPtr = std::shared_ptr<CPlayerUIRender>;
}
