#pragma once


#include	"AttackBaseState.h"
#include	"JumpStormSkillAction.h"
#include	"FixedYInhaleKnockBack.h"

namespace ActionGame {

	/**
	 * @brief		移動ステート
	 */
	class JumpStormSkillState : public AttackBaseState
	{
	public:
		struct Parameter : public BaseParam
		{
			float SkillActionFrameTime;
			float FinishTime;
			ShotAABB ShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter m_Parameter;
		/** 移動アクション */
		JumpStormSkillActionPtr			m_SkillAction;
		float							m_AttackTime;
		bool							m_ContinueFlg;
		std::string						m_Key;
	protected:
		virtual const KnockBackPtr GetKnockBack() override { return std::make_shared<FixedYInhaleKnockBack>(Actor()); }
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.ShotStatus; }
		virtual const EffectCreateParameter& GetCreateEffectStatus() override { return m_Parameter.EffectStatus; }
	public:
		/**
		 * @brief		コンストラクタ
		 */
		JumpStormSkillState(Parameter param);

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
		 * @param[in]	type		当たった相手のタイプ
		 * @param[in]	obj			当たった相手のオブジェクト
		 */
		void CollisionEvent(unsigned int type, std::any obj) override;

		/**
		 * @brief		ステートキーの取得
		 */
		const StateKeyType GetKey() const override;
	};

}