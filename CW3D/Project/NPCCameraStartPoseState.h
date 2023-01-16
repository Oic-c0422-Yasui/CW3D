#pragma once
#include "State.h"
#include "NPCStartPoseAction.h"


namespace ActionGame
{
	/*
	* @brief	NPC開始ポーズステート
	*/
	class NPCCameraStartPoseState : public State
	{
	public:
		/*
		* @brief	ステートパラメータ
		* @param	Time ポーズ時間
		*/
		struct Parameter
		{
			float Time;
		};
	private:
		//開始ポーズステート
		NPCStartPoseActionPtr			m_Action;
		//現在時間
		float						m_CurrentTime;

		Parameter m_Parameter;
		
		bool m_StartFlg;

		//カメラ設定
		void SettingCamera();
	public:
		/**
		 * @brief		コンストラクタ
		 */
		NPCCameraStartPoseState(Parameter param);

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

