#pragma once
#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		�_���[�W�A�N�V����
	 */
	class DamageAction : public Action
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
			//�ő�d��
			float					maxGravity;
			//�d��
			float					gravity;
		};
	private:
		//�p�����[�^�[
		Parameter					m_Parameter;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		DamageAction(Parameter param)
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
			//MAXGRAVITY,GRAVITY
			Velocity()->SetMaxGravity(m_Parameter.maxGravity);
			Velocity()->SetGravity(m_Parameter.gravity);
			Velocity()->SetVelocity(knockBack);
			//xz:0.05f
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
		}

		

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_DAMAGE;
		}
	};
	//�|�C���^�u������
	using DamageActionPtr = std::shared_ptr<DamageAction>;
}
