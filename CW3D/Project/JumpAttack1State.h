#pragma once


#include	"AttackBaseState.h"
#include	"JumpAttack1Action.h"


namespace ActionGame {

	/**
	 * @brief		移動ステート
	 */
	class JumpAttack1State : public AttackBaseState
	{
	public:
		struct Parameter : public BaseParam
		{
			float CollideStartFrameTime;
			ShotAABB ShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter m_Parameter;
		/** 移動アクション */
		JumpAttack1ActionPtr			m_JumpAttack1Action;

		const float EffectStartFrameTime = GameFrameTime * 20.0f;

		bool collideStartFlg;

	protected:
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.ShotStatus; }
		virtual const EffectCreateParameter& GetCreateEffectStatus() override { return m_Parameter.EffectStatus; }
	public:
		/**
		 * @brief		コンストラクタ
		 */
		JumpAttack1State(Parameter param);
			

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