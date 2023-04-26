#pragma once


#include	"AttackBaseState.h"
#include	"ShockWaveSkillAction.h"
#include	"FixedXYInhaleKnockBack.h"

namespace ActionGame {

	/**
	 * @brief		移動ステート
	 */
	class CShockWaveSkillState : public CAttackBaseState
	{
	public:
		/*
		* @brief	ステートパラメータ
		* @param	ColliderStartFrameTime 当たり判定開始時間
		* @param	ColliderEndFrameTime 　当たり判定終了時間
		* @param	AABBShotStatus 　AABBのショットパラメータ
		* @param	EffectStatus 　	エフェクトのパラメータ
		*/
		struct Parameter : public BaseParam
		{
			float CollideStartFrameTime;
			float CollideEndFrameTime;
			ShotAABB ShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter parameter_;
		/** 移動アクション */
		ShockWaveSkillActionPtr			action_;

		bool isStartCollide_;
	protected:
		virtual const KnockBackPtr GetKnockBack() { return std::make_shared<CFixedXYInhaleKnockBack>(Actor()); }
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return parameter_.ShotStatus; }
		virtual const EffectCreateParameter& GetCreateEffectStatus() override { return parameter_.EffectStatus; }

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CShockWaveSkillState(Parameter param);



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