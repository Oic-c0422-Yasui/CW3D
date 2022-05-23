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

	private:

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		DamageAction()
			: Action()
		{
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {

			Velocity()->SetVelocity(Vector3(0.2f, 0.0f, 0.0f));
			Velocity()->SetDecelerate(0.05f,0.05f);
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