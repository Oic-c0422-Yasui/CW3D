#pragma once
#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		�_���[�W�A�N�V����
	 */
	class DownAction : public Action
	{
	public:

	private:

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		DownAction()
			: Action()
		{
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {
			
			Velocity()->SetDecelerate(0.05f, 0.05f);
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
			return STATE_KEY_DOWN;
		}
	};
	//�|�C���^�u������
	using DownActionPtr = std::shared_ptr<DownAction>;
}
