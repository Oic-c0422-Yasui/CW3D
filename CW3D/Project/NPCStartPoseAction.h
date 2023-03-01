#pragma once
#include "BaseAction.h"


namespace ActionGame
{
    /**
     * @brief		開始ポーズアクション
     */
    class CNPCStartPoseAction : public CBaseAction
    {
	public:
		/**
		* @brief		攻撃アクションの設定値
		*/
		struct Parameter
		{
			//オフセット位置
			Vector3					offsetPos;
			//終了時間
			float					finishTime;
		};
	private:
		//パラメーター
		Parameter					parameter_;

		Vector3						tmpOffsetPos_;

		float						currentTime_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CNPCStartPoseAction(BaseParameter baseParam, Parameter param);


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

		/*
		* @brief		アニメーションが終了しているか
		*/
		bool IsEndAnimation() const noexcept;
	};
	//ポインタ置き換え
    using NPCStartPoseActionPtr = std::shared_ptr<CNPCStartPoseAction>;
}


