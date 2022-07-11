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
		/**
					 * @brief		�U���A�N�V�����̐ݒ�l
					 */
		struct Parameter
		{
			//�A�j���[�V�����p�����[�^�[
			AnimParam				anim;
			//�����l
			Vector3					decelerate;
			//�I������
			float					finishTime;
		};
	private:
		//�p�����[�^�[
		Parameter					m_Parameter;

		//���ݎ���
		float						m_CurrentTime;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		DeadAction(Parameter param)
			: Action()
			, m_Parameter(param)
			, m_CurrentTime(0.0f)
		{
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {
			AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
				m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
			auto& knockBack = ParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);
			Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
			m_CurrentTime = 0;
		}

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		void Execution() override {
			if (AnimationState()->IsEndMotion())
			{
				m_CurrentTime += CUtilities::GetFrameSecond();
				auto& alpha = ParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
				alpha = MyUtilities::Timer(1.0f, m_CurrentTime, 0, m_Parameter.finishTime);
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
