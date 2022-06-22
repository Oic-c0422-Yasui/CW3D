#pragma once

#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		�U���A�N�V����
	 */
	class RunJumpAttack3Action : public Action
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
		};
	private:
		//�p�����[�^�[
		Parameter					m_Parameter;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RunJumpAttack3Action(Parameter param)
			: Action()
			, m_Parameter(param)
		{
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {
			auto& vel = Velocity();
			//JUMPPOWER * 0.7
			vel->SetVelocityY(m_Parameter.jumpPower);
			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				vel->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
				//x:0.15
				vel->SetVelocityX(-m_Parameter.velocity.x);
			}
			else
			{
				vel->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
				vel->SetVelocityX(m_Parameter.velocity.x);
			}
		}

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		void Execution() override {
			if (Transform()->IsReverse())
			{
				Velocity()->SetVelocity(Vector3(-0.1f, 0, 0));
			}
			else
			{
				Velocity()->SetVelocity(Vector3(0.1f, 0, 0));
			}
		}

		/**
		 * @brief		�A�N�V�������̏I������
		 */
		void End() override {
		}

		void Jump()
		{
			Velocity()->SetVelocityY(m_Parameter.jumpPower);
		}

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_RUNJUMPATTACK3;
		}
	};
	//�|�C���^�u������
	using RunJumpAttack3ActionPtr = std::shared_ptr<RunJumpAttack3Action>;
}
