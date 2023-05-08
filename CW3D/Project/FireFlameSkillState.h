#pragma once

#include	"AttackBaseState.h"
#include	"NoneGravityAction.h"
#include	"FallAction.h"
#include	"FixedYInhaleKnockBack.h"

namespace ActionGame {

	/**
	 * @brief		ステート
	 */
	class CFireFlameSkillState : public CAttackBaseState
	{
	public:
		/*
		* @brief	ステートパラメータ
		* @param	ChargeTime 当たり判定開始時間
		* @param	ColliderStartFrameTime 当たり判定開始時間
		* @param	ColliderEndFrameTime 　当たり判定終了時間
		* @param	EndTime 　状態終了時間
		* @param	AABBShotStatus 　AABBのショットパラメータ
		* @param	ChargeEffectStatus 　	エフェクトのパラメータ
		* @param	EffectStatus 　	エフェクトのパラメータ
		*/
		struct Parameter : public BaseParam
		{
			float ChargeTime;
			float CollideStartTime;
			float CollideEndTime;
			float EndTime;
			ShotAABB ShotStatus;
			EffectCreateParameter ChargeEffectStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter parameter_;
		/** 移動アクション */
		NoneGravityActionPtr			nonGravityAction_;
		FallActionPtr					fallAction_;

		bool isStartCollide_;

		float currentChargeTime_;

		bool isLanding_;
	private:
		void SettingCamera();

	protected:
		virtual const KnockBackPtr GetKnockBack() { return std::make_shared<CFixedYInhaleKnockBack>(Actor()); }
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return parameter_.ShotStatus; }
		virtual const EffectCreateParameter& GetCreateEffectStatus() override { return parameter_.EffectStatus; }

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CFireFlameSkillState(Parameter param);



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