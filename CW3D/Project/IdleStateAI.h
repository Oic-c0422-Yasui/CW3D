#pragma once

#include	"StateAI.h"
#include	"Player.h"
#include	"Collision.h"
#include	"Common.h"
#include	"InputDefine.h"
#include	"ServiceLocator.h"

namespace ActionGame {

	/**
	 * @brief		待機ステート
	 */
	class IdleStateAI : public StateAI
	{
	private:
		bool			attackFlg;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		IdleStateAI()
			: StateAI()
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
			collider.Size = Vector3(5, 1, 4.5);
			
			//警戒範囲内に入ってきたら移動
			if (CCollision::Collision(player->GetCollider(), collider) && CUtilities::Random(3) == 0)
			{
				collider.Size = Vector3(1.5f, 1, 1.0f);
				//攻撃範囲内に入ってきたら攻撃
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
			//停止中にランダムで適当に逆方向入力
			else if (CUtilities::Random(50) == 0)
			{
				Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
					transform->IsReverse() ? 1.0f : -1.0f);

			}
			//停止中にランダムで適当にプレイヤー方向入力
			else if (CUtilities::Random(50) == 0)
			{
				Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
					player->GetPosition().x < transform->GetPosition().x ? -1.0f : 1.0f);
			}
			//プレイヤーと１２ｍ以上離れている場合
			else if (fabsf(player->GetPosition().x - transform->GetPosition().x) > 12.0f)
			{
				Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
					player->GetPosition().x < transform->GetPosition().x ? -1.0f : 1.0f);
			}

		}

		/**
		 * @brief		終了
		 */
		void End() override {
		}
	};
}
