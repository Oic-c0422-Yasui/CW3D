#pragma once


#include	"AttackBaseState.h"
#include	"EscapeAction.h"


namespace ActionGame {

	/**
	 * @brief		回避ステート
	 */
	class CEscapeState : public CAttackBaseState
	{
	public:
		/*
		* @brief	ステートパラメータ
		* @param	ThroughStartTime　		当たり判定開始時間
		* @param	ThroughEndTime	　		次の入力猶予時間
		* @param	InputAttackStartTime	攻撃の入力可能開始時間
		* @param	EscapeStartTime 　		回避開始時間
		* @param	EscapeTime 　	　		回避時間
		*/
		struct Parameter : public BaseParam
		{
			float ThroughStartTime;
			float ThroughEndTime;
			float InputAttackStartTime;
			float EscapeStartTime;
			float EscapeTime;
		};
	private:
		Parameter parameter_;

		/** 移動アクション */
		EscapeActionPtr			action_;

		bool isThrough_;
		bool isEscape_;
		float isEscapeCurrentTime_;
	protected:

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CEscapeState(Parameter param);
			

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