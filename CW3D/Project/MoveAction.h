#pragma once
#include "BaseAction.h"


namespace ActionGame {

	/**
	 * @brief		移動アクション
	 */
	class CMoveAction : public CBaseAction
	{
	public:
		/**
		* @brief		攻撃アクションの設定値
		*/
		struct Parameter
		{
			//減速値
			Vector3					decelerate;
			//加速値
			Vector3					velocity;
			Vector3					maxVelocity;
			float					gravity;
			float					maxGravity;
		};
	protected:
		//パラメーター
		Parameter					parameter_;
		enum class DIRECTION
		{
			RIGHT,
			RIGHT_UP,
			RIGHT_DOWN,
			LEFT,
			LEFT_UP,
			LEFT_DOWN,
		};
		DIRECTION currentDirection_;

		//向き初期化
		void InitDirection();
		//アクターの向きを変更する
		void ChangeDirection();

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CMoveAction(BaseParameter baseParam, Parameter param);
			

		/**
		 * @brief		アクション内の開始処理
		 */
		virtual void Start() override;

		/**
		 * @brief		アクション内の実行処理
		 */
		virtual void Execution() override;

		/**
		 * @brief		アクション内の終了処理
		 */
		virtual void End() override;

		/**
		 * @brief		加速
		 * @param[in]	x		加速量
		 * @param[in]	z		加速量
		 */
		void Acceleration(float x, float z);

		/**
		 * @brief		ステートキーの取得
		 */
		virtual const ActionKeyType GetKey() const override;
	};
	//ポインタ置き換え
	using MoveActionPtr = std::shared_ptr<CMoveAction>;

}

