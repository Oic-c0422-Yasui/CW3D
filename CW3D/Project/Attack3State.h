#pragma once


#include	"AttackBaseState.h"
#include	"Attack3Action.h"

namespace ActionGame {

	/**
	 * @brief		移動ステート
	 */
	class CAttack3State : public CAttackBaseState
	{
	public:
		/*
		* @brief	ステートパラメータ
		* @param	ColliderStartFrameTime 最初の当たり判定開始時間
		* @param	CollideSecondStartFrameTime 　２番目の当たり判定開始時間
		* @param	AABBShotStatus 　AABBのショットパラメータ
		*/
		struct Parameter : public BaseParam
		{
			float CollideFirstStartTime;
			float CollideSecondStartTime;
			ShotAABB ShotStatus;
		};
	private:
		Parameter parameter_;

		/** 移動アクション */
		Attack3ActionPtr			action_;


		bool isCollideStartFirst_;
		bool isCollideStartSecond_;
	protected:
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return parameter_.ShotStatus; }
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CAttack3State(Parameter param);


		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override;

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override;

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override;



		/**
		 * @brief		ステート内の終了処理
		 */
		void End() override;

		/**
		 * @brief		ステート内の接触イベント
		 * @param[in]	parentType		当たった相手のタイプ
		 * @param[in]	obj			当たった相手のオブジェクト
		 */
		void CollisionEvent(unsigned int type, std::any obj) override;

		/**
		 * @brief		ステートキーの取得
		 */
		const StateKeyType GetKey() const override;
	};

}