#pragma once

#include	"Action.h"
#include	"MoveAction.h"

namespace Sample {

	/**
	 * @brief		�U���A�N�V����
	 */
	class Attack1Action : public Action
	{
	public:
		MoveActionPtr			m_MoveAction;
	private:
		//�p�����[�^�[

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Attack1Action()
			: Action()
		{
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {
			m_MoveAction->Reset();
		}

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		void Exection() override {
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
			return STATE_KEY_ATTACK1;
		}
	};
	//�|�C���^�u������
	using Attack1ActionPtr = std::shared_ptr<Attack1Action>;
}
