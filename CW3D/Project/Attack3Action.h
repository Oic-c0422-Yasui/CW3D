#pragma once

#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		�U���A�N�V����
	 */
	class Attack3Action : public Action
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
			//�����l
			Vector3					velocity;
			//�����l
			Vector3					velocity2;
		};
	private:
		//�p�����[�^�[
		Parameter					m_Parameter;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Attack3Action(Parameter param)
			: Action()
			, m_Parameter(param)
		{
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {
			//PLAYERSPEED * 0.3
			AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
				m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
				//x:0.05f
				Velocity()->SetVelocity(Vector3(-m_Parameter.velocity.x, m_Parameter.velocity.y, m_Parameter.velocity.z));
			}
			else
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
				//x:0.05f
				Velocity()->SetVelocity(Vector3(m_Parameter.velocity.x, m_Parameter.velocity.y, m_Parameter.velocity.z));
			}
			//PLAYERSPEED * 0.3
			Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
		}

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		void Execution() override {
			if (Transform()->IsReverse())
			{
				//x:0.1f
				Velocity()->SetVelocity(Vector3(-m_Parameter.velocity2.x, m_Parameter.velocity2.y, m_Parameter.velocity2.z));
			}
			else
			{
				Velocity()->SetVelocity(Vector3(m_Parameter.velocity2.x, m_Parameter.velocity2.y, m_Parameter.velocity2.z));
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
			return STATE_KEY_ATTACK3;
		}
	};
	//�|�C���^�u������
	using Attack3ActionPtr = std::shared_ptr<Attack3Action>;
}
