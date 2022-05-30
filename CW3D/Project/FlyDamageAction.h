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

	private:

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		FlyDamageAction()
			: Action()
		{
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {
			auto& knockBack = ParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);
			Velocity()->SetMaxGravity(GRAVITYMAX);
			Velocity()->SetGravity(GRAVITY);
			//Velocity()->SetVelocity(knockBack);
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
			return STATE_KEY_FLYDAMAGE;
		}
	};
	//�|�C���^�u������
	using FlyDamageActionPtr = std::shared_ptr<FlyDamageAction>;
}
