#pragma once
#include "AttackBaseState.h"
#include	"Attack3Action.h"
#include	"Attack1Action.h"
#include "FixedYInhaleKnockBack.h"

namespace ActionGame {

	/**
	 * @brief		移動ステート
	 */
	class CSlashAttackState : public CAttackBaseState
	{
	public:
		/*
		* @brief	ステートパラメータ
		* @param	ColliderStartFrameTime 最初の当たり判定開始時間
		* @param	CollideSecondStartFrameTime 　２番目の当たり判定開始時間
		* @param	EndTime 　終了時間
		* @param	AABBShotStatus 　AABBのショットパラメータ
		* @param	EffectStatus 　	エフェクトのパラメータ
		*/
		struct Parameter : public BaseParam
		{
			float CollideFirstStartTime;
			float AnimChangeTime;
			float CollideSecondStartTime;
			float EndTime;
			ShotAABB ShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter parameter_;

		/** 移動アクション */
		Attack3ActionPtr			firstAction_;
		Attack1ActionPtr			secondAction_;


		bool isCollideStartFirst_;
		bool isFirstAnimChange_;
		bool isCollideStartSecond_;
	protected:
		virtual const KnockBackPtr GetKnockBack() { return std::make_shared<CFixedYInhaleKnockBack>(Actor()); }
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return parameter_.ShotStatus; }
		virtual const EffectCreateParameter& GetCreateEffectStatus() override { return parameter_.EffectStatus; }
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CSlashAttackState(Parameter param);


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
