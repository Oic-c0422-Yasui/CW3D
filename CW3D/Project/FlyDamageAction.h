#pragma once
#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		�_���[�W�A�N�V����
	 */
	class FlyDamageAction : public Action
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
			//�d��
			float					gravity;
			float					maxGravity;
		};
	private:
		//�p�����[�^�[
		Parameter					m_Parameter;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		FlyDamageAction(Parameter param)
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
			auto& knockBack = ParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);
			//GRAVITYMAX * 0.4f
			Velocity()->SetMaxGravity(m_Parameter.maxGravity);
			//GRAVITY
			Velocity()->SetGravity(m_Parameter.gravity);
			Transform()->SetThrough(true);
			Velocity()->SetVelocity(knockBack);
			//0.05
			Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
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
			Transform()->SetThrough(false);
		}



		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_FLYDAMAGE;
		}
	};
	//�|�C���^�u������
	using FlyDamageActionPtr = std::shared_ptr<FlyDamageAction>;
}
