#pragma once

#include	"StateAI.h"
#include	"Player.h"
#include	"Collision.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class MoveStateAI : public StateAI
	{
	private:
		//見失った時間
		int				currentLostTime;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		MoveStateAI()
			: StateAI()
			, currentLostTime(0) {
		}

		/**
		 * @brief		利用キーの登録
		 */
		void RegisterKey() override {
			Input()->AddKey(INPUT_KEY_HORIZONTAL);
			Input()->AddKey(INPUT_KEY_VERTICAL);
			Input()->AddKey(INPUT_KEY_ATTACK);
		}

		/**
		 * @brief		開始
		 */
		void Start() override {
			currentLostTime = 0;
		}

		/**
		 * @brief		更新
		 */
		void Update() override {
			//プレイヤー取得
			const auto& player = ServiceLocator< CPlayer >::GetService();
			const auto& transform = Actor()->GetTransform();
			//警戒ボックス
			CAABB collider;
			collider.SetPosition(transform->GetPosition());
			collider.Size = Vector3(3, 3, 3);
			//警戒範囲内にプレイヤーがいなくなるとカウントして一定後に停止
			if (!CCollision::Collision(player->GetCollider(), collider))
			{
				currentLostTime++;
				if (currentLostTime < 3)
				{
					Input()->SetKeyValue(INPUT_KEY_HORIZONTAL, transform->IsReverse() ? -1.0f : 1.0f);
				}
				return;
			}
			else
			{
				currentLostTime = 0;
			}
			//移動入力
			float sx = player->GetPosition().x - transform->GetPosition().x;
			float sz = player->GetPosition().z - transform->GetPosition().z;
			sx /= 300.0f;
			sz /= 60.0f;
			sx = ((sx < -1.0f) ? -1.0f : ((sx > 1.0f) ? 1.0f : sx));
			sz = ((sz < -1.0f) ? -1.0f : ((sz > 1.0f) ? 1.0f : sz));
			Input()->SetKeyValue(INPUT_KEY_HORIZONTAL, sx);
			Input()->SetKeyValue(INPUT_KEY_VERTICAL, sz);
			////攻撃ボックス
			//const Vector3F atkpos = transform->GetPos() + (transform->IsReverse() ? Vector3F(-30, 20, 0) : Vector3F(30, 20, 0));
			//const Vector3F atksize(25, 25, 15);
			////攻撃範囲内に入ってきたら攻撃
			//if (CollisionFunction::CollisionAABB(player->GetPos(), player->GetSize(), atkpos, atksize) &&
			//	RandomUtility::Random(10) == 0)
			//{
			//	Input()->SetKeyValue(AttackKey, 1.0f);
			//}
		}

		/**
		 * @brief		終了
		 */
		void End() override {
		}
	};
}