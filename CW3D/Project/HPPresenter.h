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
		* @brief	敵のHP情報をUI側へ通知する
		* @param	view	通常HPのUI
		*/
		static void Present(const EnemyPtr& enemy, const ActionGame::NormalEnemyHPRenderPtr& view);
		/*
		* @brief	敵のHP情報をUI側へ通知する
		* @param	view	ボスHPのUI
		*/
		static void Present(const EnemyPtr& enemy, const ActionGame::BossHPRenderPtr& view);

		/*
		* @brief	プレイヤーのHP情報をUI側へ通知する
		* @param	view	プレイヤーHPのUI
		*/
		static void Present(const PlayerPtr& player, const ActionGame::PlayerHPRenderPtr& view);

	};
}

