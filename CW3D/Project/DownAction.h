#pragma once
#include	"BaseAction.h"


namespace ActionGame {

	/**
	 * @brief		ダメージアクション
	 */
	class CDownAction : public CBaseAction
	{
	public:
		/**
		 * @brief		攻撃アクションの設定値
		 */
		struct Parameter
		{

			//減速値
			Vector3					decelerate;
		};
	private:
		//パラメーター
		Parameter					parameter_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CDownAction(BaseParameter baseParam, Parameter param);
			

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
	using DownActionPtr = std::shared_ptr<CDownAction>;
}
