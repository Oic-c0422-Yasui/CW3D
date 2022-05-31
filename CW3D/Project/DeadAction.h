#pragma once
#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		�_���[�W�A�N�V����
	 */
	class DeadAction : public Action
	{
	public:
		//�I������
		float						m_FinishTime;
		//���ݎ���
		float						m_CurrentTime;
	private:

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		DeadAction()
			: Action()
		{
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {
			auto& knockBack = ParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);
			Velocity()->SetDecelerate(PLAYER_SPEED, PLAYER_SPEED);
			m_CurrentTime = 0;
			m_FinishTime = 3;
		}

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		void Execution() override {
			if (AnimationState()->IsEndMotion())
			{
				m_CurrentTime += CUtilities::GetFrameSecond();
				auto& alpha = ParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);

				alpha = MyUtilities::Timer(1.0f, m_CurrentTime, 0, m_FinishTime);
			}
		}

		/**
		 * @brief		�A�N�V�������̏I������
		 */
		void End() override {
		}



		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_DEAD;
		}
	};
	//�|�C���^�u������
	using DeadActionPtr = std::shared_ptr<DeadAction>;
}
