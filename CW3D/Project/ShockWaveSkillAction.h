#pragma once

#include	"BaseAction.h"


namespace ActionGame {

	/**
	 * @brief		攻撃アクション
	 */
	class CShockWaveSkillAction : public CBaseAction
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
		CShockWaveSkillAction(BaseParameter baseParam, Parameter param);
			

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
	using ShockWaveSkillActionPtr = std::shared_ptr<CShockWaveSkillAction>;
}
