#pragma once

#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		�U���A�N�V����
	 */
	class RunJumpAttack2Action : public Action
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
			Vector3					velocity;
			float					jumpPower;
			float					gravity;
			float					defaultGravity;
		};
	private:
		//�p�����[�^�[
		Parameter					m_Parameter;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RunJumpAttack2Action(Parameter param)
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
			auto& vel = Velocity();

			vel->SetVelocityY(m_Parameter.jumpPower);
			vel->SetGravity(m_Parameter.gravity);

			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);

				Velocity()->SetVelocityX(-m_Parameter.velocity.x);
			}
			else
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
				Velocity()->SetVelocityX(m_Parameter.velocity.x);
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
			Velocity()->SetGravity(m_Parameter.defaultGravity);
		}

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_RUNJUMPATTACK2;
		}
	};
	//�|�C���^�u������
	using RunJumpAttack2ActionPtr = std::shared_ptr<RunJumpAttack2Action>;
}
