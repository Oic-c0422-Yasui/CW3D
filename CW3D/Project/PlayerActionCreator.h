#pragma once

#include	"IActionCreator.h"



namespace ActionGame {
	/**
	 * @brief		�A�N�V���������C���^�[�t�F�C�X
	 */
	class PlayerActionCreator : public IActionCreator
	{
	public:
		/**
		 * @brief		����
		 */
		bool Create(const ActorPtr& actor) override;
	};
}