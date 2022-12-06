#pragma once


#include	"AttackBaseState.h"
#include	"RunJumpAttack3Action.h"

namespace ActionGame {

	/**
	 * @brief		移動ステート
	 */
	class RunJumpAttack3State : public AttackBaseState
	{
	public:
		/*
		* @brief	ステートパラメータ
		* @param	ColliderStartFrameTime 最初の当たり判定開始時間
		* @param	NextInputFrameTime 　最初の当たり判定開始時間
		* @param	AABBShotStatus 　AABBのショットパラメータ
		*/
		struct Parameter : public BaseParam
		{
			float CollideFirstStartFrameTime;
			float CollideSecondStartFrameTime;
			ShotAABB ShotStatus;
		};
	private:
		Parameter m_Parameter;
		/** 移動アクション */
		RunJumpAttack3ActionPtr			m_Attack3Action;


		bool collideStartFlg;
	protected:
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.ShotStatus; }
	public:
		/**
		 * @brief		コンストラクタ
		 */
		RunJumpAttack3State(Parameter param);
			


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