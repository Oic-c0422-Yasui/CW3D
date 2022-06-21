#pragma once

#include	"StateAI.h"
#include	"Player.h"
#include	"Collision.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		待機ステート
	 */
	class IdleStateAI : public StateAI
	{
	public:
		/**
		 * @brief		コンストラクタ
		 */
		IdleStateAI()
			: StateAI() {
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
			collider.Position = transform->GetPosition();
			collider.Size = Vector3(10, 3, 10);
			
			//警戒範囲内に入ってきたら移動
			if (CCollision::Collision(player->GetCollider(), collider))
			{
				Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
					
					player->GetPosition().x < transform->GetPosition().x ? -1.0f : 1.0f);
			}
			//停止中にランダムで適当に逆方向入力
			else if (RandomUtility::Random(100) == 0)
			{
				Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
					transform->IsReverse() ? 1.0f : -1.0f);
			}
			////攻撃ボックス
			//const Vector3F atkpos = transform->GetPos() + (transform->IsReverse() ? Vector3F(-30, 20, 0) : Vector3F(30, 20, 0));
			//const Vector3F atksize(25, 25, 15);
			////攻撃範囲内に入ってきたら攻撃
			//if (CollisionFunction::CollisionAABB(player->GetPos(), player->GetSize(), atkpos, atksize))
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
