#pragma once
#include "Player.h"

namespace ActionGame
{
	class BattlePlayerLoader
	{
	public:
		/*
		* @brief	�o�g���V�[���p�Ƀv���C���[�̓ǂݍ��݂��s��
		*/
		static bool Load(const PlayerPtr& player,const Input::InputPtr& input);
	};
}


