#pragma once

#include	"StateAI.h"
#include	"Player.h"
#include	"Collision.h"
#include	"ServiceLocator.h"

namespace ActionGame {

	/**
	 * @brief		移動ステート
	 */
	class AttackStateAI : public StateAI
	{
	private:
		//見失った時間
		int				currentLostTime;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		AttackStateAI()
			: StateAI()
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

		}

		/**
		 * @brief		更新
		 */
		void Update() override {
			////プレイヤー取得
			const auto& player = ServiceLocator< CPlayer >::GetService();
			const auto& transform = Actor()->GetTransform();
			//警戒ボックス
			CAABB collider;
			collider.SetPosition(transform->GetPosition());
			collider.Size = Vector3(1.2f, 1, 1.0f);

			//警戒範囲内に入ってきたら攻撃
			if (CCollision::Collision(player->GetCollider(), collider))
			{
				Input()->SetKeyValue(INPUT_KEY_ATTACK, 1.0f);
			}
		}

		/**
		 * @brief		終了
		 */
		void End() override {
		}
	};
}