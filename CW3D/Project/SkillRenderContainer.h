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
	 * @brief		�X�L�����܂Ƃ߂ĕ\������
	 */
	class CSkillRenderContainer
	{
	private:

		std::vector < ActionGame::SkillRenderPtr>	skillRenderArray_;
		std::vector < ActionGame::SkillUltGaugeRenderPtr> ultGaugeRenderArray_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CSkillRenderContainer();

		/**
		 * @brief		�f�X�g���N�^
		 */
		~CSkillRenderContainer();

		/**
		 * @brief		�ǂݍ���
		 */
		bool Load();
		
		/**
		 * @brief		������
		 */
		void Initialize(std::function<Vector2(const std::string&)> fn);

		/**
		 * @brief		�`��
		 */
		void Render();

		/*
		* @brief		���
		*/
		void Release();
	};

	using SkillRenderContainerPtr = std::shared_ptr<CSkillRenderContainer>;
}
