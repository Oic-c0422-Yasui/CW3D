#pragma once


#include	"AttackBaseState.h"
#include	"NoneGravityAction.h"
#include	"InhaleKnockBack.h"

namespace ActionGame {

	/**
	 * @brief		移動ステート
	 */
	class CJumpStormSkillState : public CAttackBaseState
	{
	public:
		/*
		* @brief	ステートパラメータ
		* @param	AttackFrequencyFrameTime 当たり判定の発生頻度
		* @param	DurationTime 　攻撃持続時間
		* @param	ContinueTime 　攻撃を持続するかの猶予時間
		* @param	AABBShotStatus 　AABBのショットパラメータ
		* @param	EffectStatus 　	エフェクトのパラメータ
		*/
		struct Parameter : public BaseParam
		{
			float AttackFrequencyFrameTime;
			float DurationTime;
			float ContinueTime;
			ShotAABB ShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter parameter_;
		/** 移動アクション */
		NoneGravityActionPtr			action_;
		float							attackTime_;
		bool							isContinue_;
		std::string						inputKey_;
	protected:
		virtual const KnockBackPtr GetKnockBack() override { return std::make_shared<CInhaleKnockBack>(Actor()); }
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return parameter_.ShotStatus; }
		virtual const EffectCreateParameter& GetCreateEffectStatus() override { return parameter_.EffectStatus; }
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CJumpStormSkillState(Parameter param);

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