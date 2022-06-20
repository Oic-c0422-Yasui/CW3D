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
			////警戒ボックス
			//const Vector3F pos = transform->GetPos() + (transform->IsReverse() ? Vector3F(-150, 50, 0) : Vector3F(150, 50, 0));
			//const Vector3F size(280, 50, 80);
			////警戒範囲内にプレイヤーがいなくなるとカウントして一定後に停止
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
			////移動入力
			//float sx = player->GetPos().x - transform->GetPos().x;
			//float sz = player->GetPos().z - transform->GetPos().z;
			//sx /= 300.0f;
			//sz /= 60.0f;
			//sx = ((sx < -1.0f) ? -1.0f : ((sx > 1.0f) ? 1.0f : sx));
			//sz = ((sz < -1.0f) ? -1.0f : ((sz > 1.0f) ? 1.0f : sz));
			//Input()->SetKeyValue(HorizontalKey, sx);
			//Input()->SetKeyValue(VerticalKey, sz);
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