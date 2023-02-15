#pragma once
#include	"Action.h"


namespace ActionGame {

	/**
	 * @brief		ダメージアクション
	 */
	class DeadAction : public CAction
	{
	public:
		/**
					 * @brief		攻撃アクションの設定値
					 */
		struct Parameter
		{
			//アニメーションパラメーター
			AnimParam				anim;
			//減速値
			Vector3					decelerate;
			//終了時間
			float					finishTime;
		};
	private:
		//パラメーター
		Parameter					m_Parameter;

		//現在時間
		float						m_CurrentTime;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		DeadAction(Parameter param);
			

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override;

		/**
		 * @brief		アクション内の実行処理
		 */
		void Execution() override;

		/**
		 * @brief		アクション内の終了処理
		 */
		void End() override;



		/**
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override;
	};
	//ポインタ置き換え
	using DeadActionPtr = std::shared_ptr<DeadAction>;
}
