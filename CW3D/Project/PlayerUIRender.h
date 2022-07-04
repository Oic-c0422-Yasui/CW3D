#pragma once

#include "PlayerHPRender.h"
#include "SkillControllerUIRender.h"
#include "SkillsUIRender.h"

namespace Sample
{
	/**
	 * @brief		�v���C���[HPUI
	 */
	class PlayerUIRender
	{
	private:
		PlayerHPRenderPtr m_HPRender;
		SkillControllerUIRenderPtr m_SkillControllerRender;
		SkillsUIRenderPtr m_SkillsRender;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		PlayerUIRender()
			: m_HPRender(std::make_shared<PlayerHPRender>())
			, m_SkillControllerRender(std::make_shared<SkillControllerUIRender>())
			, m_SkillsRender(std::make_shared<SkillsUIRender>())
		{

		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		~PlayerUIRender() {
			Release();
		}


		void Load()
		{
			m_SkillControllerRender->Load();
			m_HPRender->Load();
			m_SkillsRender->Load();
		}

		void Initialize()
		{
			m_SkillsRender->Initialize(0, m_SkillControllerRender->GetSkillPosition(3));
			m_SkillsRender->Initialize(1, m_SkillControllerRender->GetSkillPosition(5));
			m_SkillsRender->Initialize(2, m_SkillControllerRender->GetSkillPosition(7));
			m_SkillsRender->Initialize(3, m_SkillControllerRender->GetSkillPosition(1));
		}

		const PlayerHPRenderPtr& GetHPRender() const noexcept
		{
			return m_HPRender;
		}

		/**
		 * @brief		�v���C���[UI�`��
		 */
		void Render() {
			m_SkillControllerRender->Render();
			m_SkillsRender->Render();
			m_HPRender->Render();
			m_SkillControllerRender->RenderKeyName();
		}

		void Release(void) {
			m_SkillControllerRender->Release();
			m_SkillControllerRender.reset();
			m_SkillsRender->Release();
			m_SkillsRender.reset();
			m_HPRender->Release();
			m_HPRender.reset();
		}

	};

	using PlayerUIRenderPtr = std::shared_ptr<PlayerUIRender>;
}
