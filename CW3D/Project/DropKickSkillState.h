#pragma once

#include	"AttackBaseState.h"
#include	"DropKickSkillAction.h"
#include	"AdditionalSkill.h"

namespace ActionGame {

	/**
	 * @brief		移動ステート
	 */
	class CDropKickSkillState : public CAttackBaseState
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
		DropKickSkillActionPtr			action_;

		bool isStartCollide_;
		bool isDelayInput_;
		std::string inputKey_;

		AdditionalWeakSKillPtr skillRef_;
		
		//初期化
		void Initialize();
	protected:
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return parameter_.ShotStatus; }
		virtual const EffectCreateParameter& GetCreateEffectStatus() override { return parameter_.EffectStatus; }
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CDropKickSkillState(Parameter param);


		/**
		 * @brief		ステートの初期化時処理
		 */
		void SetUp() override;

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