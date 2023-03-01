#pragma once
#include "Enemy.h"
#include "Player.h"
#include "NormalEnemyHPRender.h"
#include "BossHPRender.h"
#include "PlayerHPRender.h"

namespace ActionGame
{
	class CHPPresenter
	{
	public:
		/*
		* @brief	�G��HP����UI���֒ʒm����
		* @param	view	�ʏ�HP��UI
		*/
		static void Present(const EnemyPtr& enemy, const ActionGame::NormalEnemyHPRenderPtr& view);
		/*
		* @brief	�G��HP����UI���֒ʒm����
		* @param	view	�{�XHP��UI
		*/
		static void Present(const EnemyPtr& enemy, const ActionGame::BossHPRenderPtr& view);

		/*
		* @brief	�v���C���[��HP����UI���֒ʒm����
		* @param	view	�v���C���[HP��UI
		*/
		static void Present(const PlayerPtr& player, const ActionGame::PlayerHPRenderPtr& view);

	};
}

