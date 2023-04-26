#pragma once
#include "Action.h"
#include "VectorUtilities.h"


namespace ActionGame
{
	/*
	* @brief	移動補正アクション
	*/
	class CMoveCompensationAction : public CAction
	{
	public:

		/*
		* @brief	基底移動補正パラメータ
		* @param	isEnable		補正が有効か？
		* @param	isEnableYaxis	Y軸にも補正をかけるか？
		* @param	endTime			終了時間
		* @param	sightAngle		視野角（度数法）
		* @param	minDistance		最小補正距離
		* @param	parentType			キャラタイプ
		*/
		struct BaseParameter
		{
			bool isEnable;
			bool isEnableYaxis;
			float endTime;
			float sightAngle;
			float maxDistance;
			CHARA_TYPE type;
		};
		/*
		* @brief	移動補正パラメータ
		* @param	isEnable		補正が有効か？
		* @param	isEnableYaxis	Y軸にも補正をかけるか？
		* @param	endTime			終了時間
		* @param	sightAngle		視野角（度数法）
		* @param	maxDistance		最大補正距離
		* @param	parentType			キャラタイプ
		* @param	isActorInSight	視野内に目標アクターがいるか？
		* @param	currentTime		現在時間
		* @param	minDistance		最小補正距離
		* @param	targetPos		目標アクターのトランスフォーム
		*/
		struct Parameter : public BaseParameter
		{

			bool isActorInSight;
			float currentTime;
			float minDistance;
			TransformPtr targetPos;
		};

	protected:

		Parameter param_;
		Parameter saveParam_;
		float	 currentTime_;

	protected:
		/* プライベート関数 */

		/*
		* @brief	視野内にアクターがいるか？
		* @param[out]	outPos			一番近くのアクター座標を格納する(※アクターがいた場合)
		* @param[out]	outMinDistance	最小検知距離を格納する
		* @param		parentType			キャラタイプ
		* @param		sightAngle		視野角（度数法）
		* @param		maxDistance		最大検知距離
		* @return		true　なら存在する
		*/
		bool IsActorInSight(TransformPtr& outPos, float& offsetSize, CHARA_TYPE type, float sightAngle, float maxDistance);

		/*
		* @brief	近くのアクターに向けて移動補正をかける
		* @param[in,out]	param		移動補正パラメータ
		* @retval			true		移動完了
		* @retval			false		移動中
		*/
		bool MoveCompensation(Parameter& param);

		void Move(Vector3 pos);

		void SettingMoveCompensationParam(const BaseParameter& param);

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CMoveCompensationAction(BaseParameter baseParam);

		/**
		 * @brief		アクション内の開始処理
		 */
		virtual void Start() override;

		/**
		 * @brief		アクション内の実行処理
		 */
		virtual void Execution() override;

		/**
		 * @brief		アクション内の終了処理
		 */
		virtual  void End() override;

		/**
		 * @brief		ステートキーの取得
		 */
		virtual  const ActionKeyType GetKey() const override;
		
	};

	using MoveCompensationActionPtr = std::shared_ptr<CMoveCompensationAction>;
}


