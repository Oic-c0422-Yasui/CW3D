#pragma once

#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		�U���A�N�V����
	 */
	class EscapeAction : public Action
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
		};
	private:
		//�p�����[�^�[
		Parameter					m_Parameter;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		EscapeAction(Parameter param)
			: Action()
			, m_Parameter(param)
		{
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {
			AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
				m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
			Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
			}
			else
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
			}
		}

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		void Execution() override {
		}

		/**
		 * @brief		�A�N�V�������̏I������
		 */
		void End() override {
		}

		/**
		 * @brief		����
		 * @param[in]	x		������
		 * @param[in]	z		������
		 */
		void Move(float x, float z) {
			Velocity()->SetVelocityX(x * m_Parameter.velocity.x);
			Velocity()->SetVelocityZ(z * m_Parameter.velocity.z);
		}

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_ESCAPE;
		}
	};
	//�|�C���^�u������
	using EscapeActionPtr = std::shared_ptr<EscapeAction>;
}
