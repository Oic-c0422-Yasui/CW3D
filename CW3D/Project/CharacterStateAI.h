#pragma once

#include	"ICharacterAI.h"
#include	"IAICycle.h"

namespace ActionGame
{
	/**
	 * @brief		AI����
	 */
	class CharacterStateAI : public ICharacterAI
	{
	protected:
		//�X�e�[�g�}�b�v
		StateAIMap					stateAIMap_;

		//���݂̃X�e�[�g
		StateAIPtr					currentAI_;

		//�A�N�^�[
		ActorPtr					actor_;

		//�X�e�[�g�}�V��
		StateMachinePtr				stateMachine_;

		//���̓N���X
		StateInputPtr				input_;

		//���͏�ԕۑ�
		using KeyMap = std::unordered_map<IInput::KeyType, float >;
		KeyMap						currentKeyVelues_;

		//�������
		AICyclePtr					cycle_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CharacterStateAI(const ActorPtr& actor, const StateMachinePtr& machine,
			const StateInputPtr& input, const AICyclePtr& cycle)
			: stateAIMap_()
			, currentAI_()
			, actor_(actor)
			, stateMachine_(machine)
			, input_(input)
			, currentKeyVelues_()
			, cycle_(cycle)
		{
		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		~CharacterStateAI() override = default;

		/**
		 * @brief		�X�e�[�g�̒ǉ�
		 * @param[in]	key			�X�e�[�g�L�[
		 * @param[in]	state		�ǉ�����X�e�[�g
		 */
		void AddStateAI(const StateKeyType& key, const StateAIPtr& state) {
			stateAIMap_[key] = state;
		}

		/**
		 * @brief		���p�L�[�̓o�^
		 */
		void RegisterKey() {
			auto keys = input_->GetKeyList();
			for (const auto& v : keys)
			{
				currentKeyVelues_.emplace(v, 0.0f);
			}
		}

		/**
		 * @brief		�X�V
		 */
		void Update() override {
			//�����ɂ���đO�̃L�[�p��
			if (!cycle_->Update())
			{
				for (const auto& v : currentKeyVelues_)
				{
					input_->SetKeyValue(v.first, v.second);
				}
				return;
			}
			//���݂̃X�e�[�g��AI���o��
			const auto& currentState = stateMachine_->GetCurrentState();
			if (!currentState)
			{
				return;
			}
			auto& stateAI = stateAIMap_.find(currentState->GetKey());
			if (stateAI == stateAIMap_.end())
			{
				if (currentAI_)
				{
					currentAI_->End();
				}
				currentAI_.reset();
				return;
			}
			if (currentAI_ != stateAI->second)
			{
				if (currentAI_)
				{
					currentAI_->End();
				}
				currentAI_ = stateAI->second;
				currentAI_->Start();
			}
			currentAI_->Update();

			//�L�[��ԕۑ�
			for (auto& v : currentKeyVelues_)
			{
				v.second = input_->GetAxis(v.first);
			}
		}
	};

}

