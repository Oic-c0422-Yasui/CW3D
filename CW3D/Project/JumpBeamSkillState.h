#pragma once


#include	"AttackBaseState.h"
#include	"JumpBeamSkillAction.h"


namespace ActionGame {

	/**
	 * @brief		移動ステート
	 */
	class JumpBeamSkillState : public AttackBaseState
	{
	public:
		/*
		* @brief	ステートパラメータ
		* @param	ColliderStartFrameTime 当たり判定開始時間
		* @param	ColliderEndFrameTime 　当たり判定終了時間
		* @param	AABBShotStatus 　AABBのショットパラメータ
		* @param	OBBShotStatus 　OBBのショットパラメータ
		* @param	EffectStatus 　	エフェクトのパラメータ
		*/
		struct Parameter : public BaseParam
		{
			float CollideStartFrameTime;
			float CollideEndFrameTime;
			ShotAABB AABBShotStatus;
			ShotOBB	OBBShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter m_Parameter;
		/** 移動アクション */
		JumpBeamSkillActionPtr			m_SkillAction;

		bool collideStartFlg;

		bool m_DelayInputFlg;


		EffectCreateParameter m_EffectStatus;

		//初期化
		void Initialize();
	protected:
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.AABBShotStatus; }
		virtual const ShotOBB& GetCreateShotStatusOBB() override { return m_Parameter.OBBShotStatus; }
		virtual const EffectCreateParameter& GetCreateEffectStatus() override { return m_EffectStatus; }
	public:
		/**
		 * @brief		コンストラクタ
		 */
		JumpBeamSkillState(Parameter param);

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