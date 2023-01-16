#pragma once
#include "IAICycle.h"
#include	"Player.h"
#include "ServiceLocator.h"

namespace ActionGame
{
	/**
	 * @brief		プレイヤーとの距離で緊迫度として周期決定処理
	 */
    class AICycleTension : public IAICycle
	{
	private:
		//元のアクター
		ActorPtr		m_Actor;

		//待機時間
		int			m_CurrentTime;
	public:
		/**
		 *	@brief		コンストラクタ
		 */
		AICycleTension(ActorPtr actor)
			: m_Actor(actor)
			, m_CurrentTime(0)
		{
		}

		/**
		 * @brief		更新
		 * @return		trueなら出現
		 */
		bool Update() override;

		/**
		 * @brief		状態リセット
		 */
		void Reset() override {
			m_CurrentTime = 0;
		}
	};
}


