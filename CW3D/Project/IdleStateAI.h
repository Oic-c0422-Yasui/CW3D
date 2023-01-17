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

		Vector3			m_VigilangeRange;

		Vector3			m_AttackRange;

		int				m_AttackTiming;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		IdleStateAI(Vector3 vigilanceRange, Vector3 attackRange,int attackTiming)
			: StateAI()
			, attackFlg(false)
			, m_VigilangeRange(vigilanceRange)
			, m_AttackRange(attackRange)
			, m_AttackTiming(attackTiming)
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
			const auto& target = ServiceLocator< CPlayer >::GetService();
			const auto& transform = Actor()->GetTransform();
			//警戒ボックス
			CAABB collider;
			collider.SetPosition(transform->GetPosition());
			collider.Size = m_VigilangeRange;
			
			Vector2 vec(transform->GetPosition().x - target->GetPosition().x, transform->GetPosition().z - target->GetPosition().z);
			float length = sqrt(vec.x * vec.x + vec.y * vec.y);

			//警戒範囲内に入ってきたら移動
			if (CCollision::Collision(target->GetCollider(), collider))
			{
				collider.Size = m_AttackRange;
				//攻撃範囲内に入ってきたら攻撃
				if (CCollision::Collision(target->GetCollider(), collider))
				{
					if (!Input()->IsPush(INPUT_KEY_ATTACK) && CUtilities::Random(m_AttackTiming) == 0)
					{
						transform->SetReverse(target->GetPosition().x < transform->GetPosition().x ? true : false);
						Input()->SetKeyValue(INPUT_KEY_ATTACK, 1.0f);
						attackFlg = true;
					}
				}
				else
				{
					if (!Input()->IsPush(INPUT_KEY_HORIZONTAL) && !Input()->IsNegativePush(INPUT_KEY_HORIZONTAL))
					{
						Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
							target->GetPosition().x < transform->GetPosition().x ? -CUtilities::RandomFloat() : CUtilities::RandomFloat());
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
					target->GetPosition().x < transform->GetPosition().x ? -1.0f : 1.0f);
			}
			//プレイヤーと5ｍ以上離れている場合
			else if (length > 5.0f)
			{
				//移動入力
				float sx = target->GetPosition().x - transform->GetPosition().x;
				float sz = target->GetPosition().z - transform->GetPosition().z;
				sx /= 5.0f;
				sz /= 5.0f;
				sx = ((sx < -1.0f) ? -1.0f : ((sx > 1.0f) ? 1.0f : sx));
				sz = -((sz < -1.0f) ? -1.0f : ((sz > 1.0f) ? 1.0f : sz));
				Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,sx);
				Input()->SetKeyValue(INPUT_KEY_VERTICAL, sz);
			}

		}

		/**
		 * @brief		終了
		 */
		void End() override {
		}
	};
}
