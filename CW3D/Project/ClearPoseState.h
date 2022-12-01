#pragma once

#include	"State.h"
#include	"ClearPoseAction.h"

namespace Sample {

	/**
	 * @brief		ダメージステート
	 */
	class ClearPoseState : public State
	{
	public:

	private:

		//ダウンステート
		ClearPoseActionPtr			m_ClearPoseAction;
		//現在時間
		float						m_CurrentTime;

		bool						m_AnimStartFlg;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		ClearPoseState()
			: State()
			, m_CurrentTime(0)
			, m_AnimStartFlg(false)
		{
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {

			m_ClearPoseAction = Actor()->GetAction<ClearPoseAction>(GetKey());
			m_ClearPoseAction->Start();
			m_AnimStartFlg = false;
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
			m_ClearPoseAction->Execution();
			if (Actor()->GetTransform()->GetPositionY() <= 0.0f && !m_AnimStartFlg)
			{
				//カメラ設定
				MyUtilities::ANIM_V3_DATA_ARRAY animPos(
					{
						{0.0f,Vector3(-5,2,-3)},
						{5.0f,Vector3(5,2,-3)},
						{5.0f,Vector3(0,2,-3)},
					}
				);
				MyUtilities::ANIM_V3_DATA_ARRAY animLookPos(
					{
						{0.0f,Vector3(0, 1, 0)},
						{0.0f,Vector3(0, 1, 0)},
						{5.0f,Vector3(0, 1, 0)},
					}
				);
				Vector3 offsetPos(7, 2, -2);
				Vector3 offsetLookPos(0, 0, 0);
				CameraPtr camera;
				camera = std::make_shared<CFixedCamera>(Actor()->GetPosition(), Actor()->GetPosition(), offsetPos, offsetLookPos);
				camera->SetAnim(animPos, animLookPos);
				CameraControllerInstance.SetCamera(camera);


				m_ClearPoseAction->StartAnim();
				m_AnimStartFlg = true;
			}
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {
		}

		/**
		 * @brief		ステート内の終了処理
		 */
		void End() override {
			m_ClearPoseAction->End();
		}

		/**
	 * @brief		ステート内の接触イベント
	 * @param[in]	type		当たった相手のタイプ
	 * @param[in]	obj			当たった相手のオブジェクト
	 */
		void CollisionEvent(unsigned int type, std::any obj) override {
		}

		/**
		 * @brief		ステートキーの取得
		 */
		const StateKeyType GetKey() const override {
			return STATE_KEY_CLEARPOSE;
		}
	};
}