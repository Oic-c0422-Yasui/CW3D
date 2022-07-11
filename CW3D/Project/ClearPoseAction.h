#pragma once

#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		�U���A�N�V����
	 */
	class ClearPoseAction : public Action
	{
	public:
		/**
			 * @brief		�U���A�N�V�����̐ݒ�l
			 */
		struct Parameter
		{
			//�A�j���[�V�����p�����[�^�[
			AnimParam				anim;
			AnimParam				fallAnim;
			//�����l
			Vector3					decelerate;
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
		ClearPoseAction(Parameter param)
			: Action()
			, m_Parameter(param)
		{
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {
			if (Transform()->GetPositionY() > 0.0f)
			{
				AnimationState()->ChangeMotionByName(m_Parameter.fallAnim.name, m_Parameter.fallAnim.startTime, m_Parameter.fallAnim.speed,
					m_Parameter.fallAnim.tTime, m_Parameter.fallAnim.loopFlg, MOTIONLOCK_OFF, TRUE);
			}
			else
			{
				StartAnim();
			}

			Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
			float rotateY = Transform()->GetRotateY();

			Velocity()->SetRotateY(rotateY, MOF_ToRadian(0), 0.18f);
			Velocity()->SetGravity(m_Parameter.gravity);
			Velocity()->SetMaxGravity(m_Parameter.maxGravity);
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

		void StartAnim()
		{
			AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
				m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_CLEARPOSE;
		}
	};
	//�|�C���^�u������
	using ClearPoseActionPtr = std::shared_ptr<ClearPoseAction>;
}
