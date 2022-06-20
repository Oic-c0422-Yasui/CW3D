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
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		MoveStateAI()
			: StateAI()
			, currentLostTime(0) {
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
		}

		/**
		 * @brief		�X�V
		 */
		void Update() override {
			//�v���C���[�擾
			const auto& player = ServiceLocator< CPlayer >::GetService();
			const auto& transform = Actor()->GetTransform();
			////�x���{�b�N�X
			//const Vector3F pos = transform->GetPos() + (transform->IsReverse() ? Vector3F(-150, 50, 0) : Vector3F(150, 50, 0));
			//const Vector3F size(280, 50, 80);
			////�x���͈͓��Ƀv���C���[�����Ȃ��Ȃ�ƃJ�E���g���Ĉ���ɒ�~
			//if (!CollisionFunction::CollisionAABB(player->GetPos(), player->GetSize(), pos, size))
			//{
			//	currentLostTime++;
			//	if (currentLostTime < 3)
			//	{
			//		Input()->SetKeyValue(HorizontalKey, transform->IsReverse() ? -1.0f : 1.0f);
			//	}
			//	return;
			//}
			//else
			//{
			//	currentLostTime = 0;
			//}
			////�ړ�����
			//float sx = player->GetPos().x - transform->GetPos().x;
			//float sz = player->GetPos().z - transform->GetPos().z;
			//sx /= 300.0f;
			//sz /= 60.0f;
			//sx = ((sx < -1.0f) ? -1.0f : ((sx > 1.0f) ? 1.0f : sx));
			//sz = ((sz < -1.0f) ? -1.0f : ((sz > 1.0f) ? 1.0f : sz));
			//Input()->SetKeyValue(HorizontalKey, sx);
			//Input()->SetKeyValue(VerticalKey, sz);
			////�U���{�b�N�X
			//const Vector3F atkpos = transform->GetPos() + (transform->IsReverse() ? Vector3F(-30, 20, 0) : Vector3F(30, 20, 0));
			//const Vector3F atksize(25, 25, 15);
			////�U���͈͓��ɓ����Ă�����U��
			//if (CollisionFunction::CollisionAABB(player->GetPos(), player->GetSize(), atkpos, atksize) &&
			//	RandomUtility::Random(10) == 0)
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