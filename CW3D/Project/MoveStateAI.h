#pragma once

#include	"StateAI.h"
#include	"Player.h"
#include	"Collision.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class MoveStateAI : public StateAI
	{
	private:
		//������������
		int				currentLostTime;
		bool			attackFlg;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		MoveStateAI()
			: StateAI()
			, currentLostTime(0)
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
			currentLostTime = 0;
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
			collider.Size = Vector3(5, 3, 5);
			//�x���͈͓��Ƀv���C���[�����Ȃ��Ȃ�ƃJ�E���g���Ĉ���ɒ�~
			if (!CCollision::Collision(player->GetCollider(), collider))
			{
				currentLostTime++;
				if (currentLostTime < 5)
				{
					Input()->SetKeyValue(INPUT_KEY_HORIZONTAL, transform->IsReverse() ? -1.0f : 1.0f);
				}
				//�v���C���[�ƂP�Q���ȏ㗣��Ă���ꍇ
				else if (fabsf(player->GetPosition().x - transform->GetPosition().x) > 12.0f)
				{
					//�ړ�����
					float sx = player->GetPosition().x - transform->GetPosition().x;
					float sz = player->GetPosition().z - transform->GetPosition().z;
					sx /= 300.0f;
					sz /= 10.0f;
					sx = ((sx < -1.0f) ? -1.0f : ((sx > 1.0f) ? 1.0f : sx));
					sz = -((sz < -1.0f) ? -1.0f : ((sz > 1.0f) ? 1.0f : sz));
					Input()->SetKeyValue(INPUT_KEY_HORIZONTAL, sx);
					Input()->SetKeyValue(INPUT_KEY_VERTICAL, sz);
				}
				return;
			}
			else
			{
				currentLostTime = 0;
			}
			//�ړ�����
			float sx = player->GetPosition().x - transform->GetPosition().x;
			float sz = player->GetPosition().z - transform->GetPosition().z;
			sx /= 300.0f;
			sz /= 10.0f;
			sx = ((sx < -1.0f) ? -1.0f : ((sx > 1.0f) ? 1.0f : sx));
			sz = -((sz < -1.0f) ? -1.0f : ((sz > 1.0f) ? 1.0f : sz));
			
			//�U���{�b�N�X
			collider.Size = Vector3(1.5f, 1, 1.0f);
			//�U���͈͓��ɓ����Ă�����U��
			/*if (!attackFlg)
			{*/
			if (CCollision::Collision(player->GetCollider(), collider))
			{
				if (CUtilities::Random(5) == 0)
				{
					Input()->SetKeyValue(INPUT_KEY_ATTACK, 1.0f);
					attackFlg = true;
				}
			}
			else
			{
				Input()->SetKeyValue(INPUT_KEY_HORIZONTAL, sx);
				Input()->SetKeyValue(INPUT_KEY_VERTICAL, sz);
			}
			//}
			
		}

		/**
		 * @brief		�I��
		 */
		void End() override {
		}
	};
}