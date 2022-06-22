#pragma once

#include	"StateAI.h"
#include	"Player.h"
#include	"Collision.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		�ҋ@�X�e�[�g
	 */
	class IdleStateAI : public StateAI
	{
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		IdleStateAI()
			: StateAI() {
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
			//�v���C���[�擾
			const auto& player = ServiceLocator< CPlayer >::GetService();
			const auto& transform = Actor()->GetTransform();
			//�x���{�b�N�X
			CAABB collider;
			collider.SetPosition(transform->GetPosition());
			collider.Size = Vector3(2, 3, 1);
			
			//�x���͈͓��ɓ����Ă�����ړ�
			if (CCollision::Collision(player->GetCollider(), collider))
			{
				if (!Input()->IsPush(INPUT_KEY_HORIZONTAL) && !Input()->IsNegativePush(INPUT_KEY_HORIZONTAL))
				{
					Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
						player->GetPosition().x < transform->GetPosition().x ? -1.0f : 1.0f);
				}
			}
			////��~���Ƀ����_���œK���ɋt��������
			//else if (CUtilities::Random(100) == 0)
			//{
			//	Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
			//		transform->IsReverse() ? 1.0f : -1.0f);
			//}
			////�U���{�b�N�X
			//const Vector3F atkpos = transform->GetPos() + (transform->IsReverse() ? Vector3F(-30, 20, 0) : Vector3F(30, 20, 0));
			//const Vector3F atksize(25, 25, 15);
			////�U���͈͓��ɓ����Ă�����U��
			//if (CollisionFunction::CollisionAABB(player->GetPos(), player->GetSize(), atkpos, atksize))
			//{
			//	Input()->SetKeyValue(AttackKey, 1.0f);
			//}
		}

		/**
		 * @brief		�I��
		 */
		void End() override {
		}
	};
}