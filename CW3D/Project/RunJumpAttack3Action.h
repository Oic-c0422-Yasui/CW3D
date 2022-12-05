#pragma once

#include	"Action.h"
#include	"GameDefine.h"

namespace ActionGame {

	/**
	 * @brief		攻撃アクション
	 */
	class RunJumpAttack3Action : public Action
	{
	public:
		/**
		* @brief		攻撃アクションの設定値
		*/
		struct Parameter
		{
			//アニメーションパラメーター
			AnimParam				anim;
			//加速値
			Vector3					velocity;
			float					jumpPower;
			float					gravity;
			float					defaultGravity;
		};
	private:
		//パラメーター
		Parameter					m_Parameter;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		RunJumpAttack3Action(Parameter param);
			

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
		* @brief	ジャンプ
		*/
		void Jump();

		/**
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override;
	};
	//ポインタ置き換え
	using RunJumpAttack3ActionPtr = std::shared_ptr<RunJumpAttack3Action>;
}
