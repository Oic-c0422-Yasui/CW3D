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
		bool			attackFlg;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		MoveStateAI()
			: StateAI()
			, currentLostTime(0)
			, attackFlg(false)
		{
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
			attackFlg = false;
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
			collider.Size = Vector3(5, 3, 5);
			//警戒範囲内にプレイヤーがいなくなるとカウントして一定後に停止
			if (!CCollision::Collision(player->GetCollider(), collider))
			{
				currentLostTime++;
				if (currentLostTime < 5)
				{
					Input()->SetKeyValue(INPUT_KEY_HORIZONTAL, transform->IsReverse() ? -1.0f : 1.0f);
				}
				//プレイヤーと１２ｍ以上離れている場合
				else if (fabsf(player->GetPosition().x - transform->GetPosition().x) > 12.0f)
				{
					//移動入力
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
			//移動入力
			float sx = player->GetPosition().x - transform->GetPosition().x;
			float sz = player->GetPosition().z - transform->GetPosition().z;
			sx /= 300.0f;
			sz /= 10.0f;
			sx = ((sx < -1.0f) ? -1.0f : ((sx > 1.0f) ? 1.0f : sx));
			sz = -((sz < -1.0f) ? -1.0f : ((sz > 1.0f) ? 1.0f : sz));
			
			//攻撃ボックス
			collider.Size = Vector3(1.5f, 1, 1.0f);
			//攻撃範囲内に入ってきたら攻撃
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
		 * @brief		終了
		 */
		void End() override {
		}
	};
}