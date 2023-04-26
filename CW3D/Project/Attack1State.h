#pragma once


#include	"AttackBaseState.h"
#include	"Attack1Action.h"


namespace ActionGame {

	/**
	 * @brief		攻撃ステート
	 */
	class CAttack1State : public CAttackBaseState
	{
	public:
		/*
		* @brief	ステートパラメータ
		* @param	ColliderStartFrameTime 当たり判定開始時間
		* @param	NextInputFrameTime 　次の入力猶予時間
		* @param	AABBShotStatus 　AABBのショットパラメータ
		* @param	EffectStatus 　	エフェクトのパラメータ
		* @param	MoveCompensation	移動補正パラメータ
		*/
		struct Parameter : public BaseParam
		{
			float CollideStartFrameTime;
			float NextInputFrameTime;
			ShotAABB ShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter parameter_;

		/** 移動アクション */
		Attack1ActionPtr			action_;

		bool isStartCollide_;

	protected:
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return parameter_.ShotStatus; }
		virtual const EffectCreateParameter& GetCreateEffectStatus() override { return parameter_.EffectStatus; }
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CAttack1State(Parameter param);

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