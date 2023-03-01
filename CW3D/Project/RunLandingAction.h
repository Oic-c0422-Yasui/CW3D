#pragma once
#include "BaseAction.h"


namespace ActionGame {

	/**
	 * @brief		ダッシュ着地アクション
	 */
	class CRunLandingAction : public CBaseAction
	{
	public:
		/**
			 * @brief		攻撃アクションの設定値
			 */
		struct Parameter
		{

		};
	private:
		//パラメーター
		Parameter					parameter_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CRunLandingAction(BaseParameter baseParam, Parameter param);
			

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
	using RunLandingActionPtr = std::shared_ptr<CRunLandingAction>;
}

