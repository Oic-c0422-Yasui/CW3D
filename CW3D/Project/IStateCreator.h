#pragma once

#include	"IStateMachine.h"

namespace Sample {

	/**
	 * @brief		�X�e�[�g�����C���^�[�t�F�C�X
	 */
	class __declspec(novtable) IStateCreator
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~IStateCreator() = default;

		/**
		 * @brief		����
		 */
		virtual bool Create(const StateMachinePtr& stateMachine, const ActorPtr& actor, const InputPtr& input) = 0;
	};
	//�|�C���^�u������
	using StateCreatorPtr = std::shared_ptr<IStateCreator>;
}