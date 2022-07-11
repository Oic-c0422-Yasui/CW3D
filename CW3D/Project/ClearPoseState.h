#pragma once

#include	"State.h"
#include	"ClearPoseAction.h"

namespace Sample {

	/**
	 * @brief		�_���[�W�X�e�[�g
	 */
	class ClearPoseState : public State
	{
	public:

	private:

		//�_�E���X�e�[�g
		ClearPoseActionPtr			m_ClearPoseAction;
		//���ݎ���
		float						m_CurrentTime;

		bool						m_AnimStartFlg;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		ClearPoseState()
			: State()
			, m_CurrentTime(0)
			, m_AnimStartFlg(false)
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {

			m_ClearPoseAction = Actor()->GetAction<ClearPoseAction>(GetKey());
			m_ClearPoseAction->Start();
			if (Actor()->GetTransform()->GetPositionY() <= 0.0f)
			{
				m_AnimStartFlg = true;
				MyUtilities::ANIMV3_DATA animPos[] =
				{
					{0.0f,Vector3(-5,2,-3)},
					{5.0f,Vector3(5,2,-3)},
					{5.0f,Vector3(0,2,-3)},
				};
				MyUtilities::ANIMV3_DATA animLookPos[] =
				{
					{0.0f,Vector3(0, 1, 0)},
					{0.0f,Vector3(0, 1, 0)},
					{5.0f,Vector3(0, 1, 0)},
				};
				Vector3 pos(7, 2, -2);
				Vector3 lookPos(0, 0, 0);
				CameraPtr camera;
				camera = std::make_shared<CFixedCamera>(Actor()->GetPosition(), Actor()->GetPosition(), pos, lookPos);
				camera->SetAnim(animPos, animLookPos, _countof(animPos));
				CameraControllerInstance.SetCamera(camera);
			}
			else
			{
				m_AnimStartFlg = false;
			}
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {
			m_ClearPoseAction->Execution();
			if (Actor()->GetTransform()->GetPositionY() <= 0.0f && !m_AnimStartFlg)
			{
				m_ClearPoseAction->StartAnim();
				m_AnimStartFlg = true;
			}
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override {
		}

		/**
		 * @brief		�X�e�[�g���̏I������
		 */
		void End() override {
			m_ClearPoseAction->End();
		}

		/**
	 * @brief		�X�e�[�g���̐ڐG�C�x���g
	 * @param[in]	type		������������̃^�C�v
	 * @param[in]	obj			������������̃I�u�W�F�N�g
	 */
		void CollisionEvent(unsigned int type, std::any obj) override {
		}

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const StateKeyType GetKey() const override {
			return STATE_KEY_CLEARPOSE;
		}
	};
}