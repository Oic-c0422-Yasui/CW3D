#pragma once

#include	"StateAI.h"
#include	"Player.h"
#include	"Collision.h"
#include	"Common.h"
#include	"InputDefine.h"
#include	"ServiceLocator.h"

namespace ActionGame {

	/**
	 * @brief		�ҋ@�X�e�[�g
	 */
	class IdleStateAI : public StateAI
	{
	private:
		bool			attackFlg;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		IdleStateAI()
			: StateAI()
			, attackFlg(false)
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
			attackFlg = false;
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
			collider.Size = Vector3(5, 1, 4.5);
			
			//�x���͈͓��ɓ����Ă�����ړ�
			if (CCollision::Collision(player->GetCollider(), collider) && CUtilities::Random(3) == 0)
			{
				collider.Size = Vector3(1.5f, 1, 1.0f);
				//�U���͈͓��ɓ����Ă�����U��
				if (CCollision::Collision(player->GetCollider(), collider))
				{
					if (!Input()->IsPush(INPUT_KEY_ATTACK))
					{
						transform->SetReverse(player->GetPosition().x < transform->GetPosition().x ? true : false);
						Input()->SetKeyValue(INPUT_KEY_ATTACK, 1.0f);
						attackFlg = true;
					}
				}
				else
				{
					if (!Input()->IsPush(INPUT_KEY_HORIZONTAL) && !Input()->IsNegativePush(INPUT_KEY_HORIZONTAL))
					{
						Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
							player->GetPosition().x < transform->GetPosition().x ? -CUtilities::RandomFloat() : CUtilities::RandomFloat());
					}
					if (!Input()->IsPush(INPUT_KEY_VERTICAL) && !Input()->IsNegativePush(INPUT_KEY_VERTICAL) && CUtilities::Random(10) == 0)
					{
						Input()->SetKeyValue(INPUT_KEY_VERTICAL,
							CUtilities::Random(10) < 4 ? -CUtilities::RandomFloat() : CUtilities::RandomFloat());
					}
				}
			}
			//��~���Ƀ����_���œK���ɋt��������
			else if (CUtilities::Random(50) == 0)
			{
				Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
					transform->IsReverse() ? 1.0f : -1.0f);

			}
			//��~���Ƀ����_���œK���Ƀv���C���[��������
			else if (CUtilities::Random(50) == 0)
			{
				Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
					player->GetPosition().x < transform->GetPosition().x ? -1.0f : 1.0f);
			}
			//�v���C���[�ƂP�Q���ȏ㗣��Ă���ꍇ
			else if (fabsf(player->GetPosition().x - transform->GetPosition().x) > 12.0f)
			{
				Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
					player->GetPosition().x < transform->GetPosition().x ? -1.0f : 1.0f);
			}

		}

		/**
		 * @brief		�I��
		 */
		void End() override {
		}
	};
}
