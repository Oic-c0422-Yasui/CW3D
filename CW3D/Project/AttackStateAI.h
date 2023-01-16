#pragma once

#include	"StateAI.h"
#include	"Player.h"
#include	"Collision.h"
#include	"ServiceLocator.h"

namespace ActionGame {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class AttackStateAI : public StateAI
	{
	private:
		//������������
		int				currentLostTime;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		AttackStateAI()
			: StateAI()
		{
		}

		/**
		 * @brief		���p�L�[�̓o�^
		 */
		void RegisterKey() override {
			Input()->AddKey(INPUT_KEY_HORIZONTAL);
			Input()->AddKey(INPUT_KEY_VERTICAL);
			Input()->AddKey(INPUT_KEY_ATTACK);
		}

		/**
		 * @brief		�J�n
		 */
		void Start() override {

		}

		/**
		 * @brief		�X�V
		 */
		void Update() override {
			////�v���C���[�擾
			const auto& player = ServiceLocator< CPlayer >::GetService();
			const auto& transform = Actor()->GetTransform();
			//�x���{�b�N�X
			CAABB collider;
			collider.SetPosition(transform->GetPosition());
			collider.Size = Vector3(1.2f, 1, 1.0f);

			//�x���͈͓��ɓ����Ă�����U��
			if (CCollision::Collision(player->GetCollider(), collider))
			{
				Input()->SetKeyValue(INPUT_KEY_ATTACK, 1.0f);
			}
		}

		/**
		 * @brief		�I��
		 */
		void End() override {
		}
	};
}