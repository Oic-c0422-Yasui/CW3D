#pragma once
#include "Action.h"

namespace ActionGame
{

	/**
	 * @brief		ベースのアクション
	 */
	class CBaseAction : public CAction
	{
	public:
		/**
		 * @brief		ベースアクションの設定値
		 */
		struct BaseParameter
		{
			//アニメーションパラメーター
			AnimParam				anim;
		};
	protected:

		BaseParameter baseParam_;
	protected:
		/* プライベート関数 */

		//反転方向に回転させる
		void SetRotation(float rotateTime = 0.18f);

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CBaseAction(BaseParameter baseParam);

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
		virtual  void End() override;

		/**
		 * @brief		ステートキーの取得
		 */
		virtual  const ActionKeyType GetKey() const override = 0;

		/*
		* @brief		アニメーションの再生
		*/
		void PlayAnimation();
		/*
		* @brief		任意のアニメーションの再生
		* @param	name		アニメーション名
		* @param	startTime	開始時間
		* @param	speed		アニメーション速度
		* @param	tTime		補間時間
		* @param	isLoop		ループするか？
		*/
		void PlayAnimation(char* name,float startTime,float speed,
							float tTime, bool isLoop);
	};

}

