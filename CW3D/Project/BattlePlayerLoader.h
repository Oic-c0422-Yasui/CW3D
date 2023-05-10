#pragma once
#include "Player.h"

namespace ActionGame
{
	class BattlePlayerLoader
	{
	public:
		/*
		* @brief	バトルシーン用にプレイヤーの読み込みを行う
		*/
		static bool Load(const PlayerPtr& player,const Input::InputPtr& input);
	};
}


