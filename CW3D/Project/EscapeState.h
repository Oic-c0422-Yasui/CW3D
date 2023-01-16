#pragma once


#include	"AttackBaseState.h"
#include	"EscapeAction.h"


namespace ActionGame {

	/**
	 * @brief		回避ステート
	 */
	class EscapeState : public AttackBaseState
	{
	public:
		/*
		* @brief	ステートパラメータ
		* @param	ThroughStartTime　当たり判定開始時間
		* @param	ThroughEndTime	　次の入力猶予時間
		* @param	EscapeStartTime 　回避開始時間
		* @param	EscapeTime 　	　回避時間
		* @param	EffectStatus 　	　エフェクトのパラメータ
		*/
		struct Parameter : public BaseParam
		{
			float ThroughStartTime;
			float ThroughEndTime;
			float EscapeStartTime;
			float EscapeTime;
		};
	private:
		Parameter m_Parameter;

		/** 移動アクション */
		EscapeActionPtr			m_EscapeAction;

		bool m_ThroughFlg;
		bool m_EscapeFlg;
		float m_EscapeCurrentTime;
	protected:

	public:
		/**
		 * @brief		コンストラクタ
		 */
		EscapeState(Parameter param);
			

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