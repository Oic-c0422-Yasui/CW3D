#pragma once

#include	"IStateCreator.h"




namespace ActionGame {

	/**
	 * @brief		�X�e�[�g�����C���^�[�t�F�C�X
	 */
	class PlayerStateCreator : public IStateCreator
	{
	public:
		/**
		 * @brief		����
		 */
		bool Create(const StateMachinePtr& stateMachine,
					const ActorPtr& actor,
					const Input::InputPtr& input) override;
			
	};
}