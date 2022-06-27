#pragma once
#include "Action.h"


namespace Sample {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class IdleMotionAction : public Action
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
		};
	private:
		//�p�����[�^�[
		Parameter					m_Parameter;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		IdleMotionAction(Parameter param)
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

			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(180), 0.2f);
			}
			else
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(0), 0.2f);
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
		void Acceleration(float x, float z) {
			Velocity()->Acceleration(x * m_Parameter.velocity.x,
				z * m_Parameter.velocity.z);
		}

		/**
		 * @brief		���x���Z�b�g
		 */
		void Reset() {

		}



		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_IDLEMOTION;
		}
	};
	//�|�C���^�u������
	using IdleMotionActionPtr = std::shared_ptr<IdleMotionAction>;

}
