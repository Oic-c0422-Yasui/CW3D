#pragma once
#include "Action.h"

namespace ActionGame
{
	/**
	 * @brief		クリアポーズアクション
	 */
	class StartPoseAction : public Action
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
			float					gravity;
			float					maxGravity;
		};
	private:
		//パラメーター
		Parameter					m_Parameter;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		StartPoseAction(Parameter param);


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

		/*
		* @brief		アニメーション開始
		*/
		void StartAnim();

		/**
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override;
	};
	//ポインタ置き換え
	using StartPoseActionPtr = std::shared_ptr<StartPoseAction>;
	
}
