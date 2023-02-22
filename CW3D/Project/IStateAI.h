#pragma once
#include	"IStateMachine.h"
#include	"StateInput.h"

namespace ActionGame
{
	/**
	 * @brief		AI�����C���^�[�t�F�C�X
	 */
	class __declspec(novtable) IStateAI
	{
	protected:
		/**
		 * @brief		�A�N�^�[�o�^
		 */
		virtual void SetActor(const ActorPtr& actor) = 0;

		/**
		 * @brief		�X�e�[�g�}�V���o�^
		 */
		virtual void SetStateMachine(const StateMachinePtr& machine) = 0;

		/**
		 * @brief		���͓o�^
		 */
		virtual void SetInput(const Input::StateInputPtr& input) = 0;
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~IStateAI() = default;

		/**
		 * @brief		�J�n
		 */
		virtual void Start() = 0;

		/**
		 * @brief		�X�V
		 */
		virtual void Update() = 0;

		/**
		 * @brief		�I��
		 */
		virtual void End() = 0;
	};
	using StateAIPtr = std::shared_ptr<IStateAI>;
	using StateAIMap = std::unordered_map< StateKeyType, StateAIPtr >;
}