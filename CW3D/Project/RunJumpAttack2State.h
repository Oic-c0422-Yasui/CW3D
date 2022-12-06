#pragma once


#include	"AttackBaseState.h"
#include	"RunJumpAttack2Action.h"

namespace ActionGame {

	/**
	 * @brief		移動ステート
	 */
	class RunJumpAttack2State : public AttackBaseState
	{
	public:
		/*
		* @brief	ステートパラメータ
		* @param	NextInputFrameTime 　次の入力猶予時間
		* @param	AABBShotStatus 　AABBのショットパラメータ
		*/
		struct Parameter : public BaseParam
		{
			float NextInputFrameTime;
			ShotAABB ShotStatus;
		};
	private:
		Parameter m_Parameter;
		/** 移動アクション */
		RunJumpAttack2ActionPtr			m_Attack2Action;

	protected:
		virtual const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.ShotStatus; }
	public:
		/**
		 * @brief		コンストラクタ
		 */
		RunJumpAttack2State(Parameter param);
			


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