#pragma once


#include	"State.h"
#include	"FixedKnockBack.h"
#include	"EffectController.h"
#include	"ShotManager.h"
#include	"SkillDefine.h"
#include	"DamageUtilities.h"
#include	"VectorUtilities.h"

namespace ActionGame {

	/**
	 * @brief		移動ステート
	 */
	class CAttackBaseState : public CState
	{
	public:
		typedef struct BASEPARAM
		{
			BYTE armorLevel;
		}BaseParam;
		/*
		* @brief	基底移動補正パラメータ
		* @param	isEnable		補正が有効か？
		* @param	endTime			終了時間
		* @param	sightAngle		視野角（度数法）
		* @param	minDistance		最小補正距離
		*/
		struct BaseCompensationParam
		{
			bool isEnable;
			float endTime;
			float sightAngle;
			float maxDistance;
		};
		/*
		* @brief	移動補正パラメータ
		* @param	isEnable		補正が有効か？
		* @param	endTime			終了時間
		* @param	sightAngle		視野角（度数法）
		* @param	maxDistance		最大補正距離
		* @param	isActorInSight	視野内に目標アクターがいるか？
		* @param	currentTime		現在時間
		* @param	minDistance		最小補正距離
		* @param	targetPos		目標アクターのトランスフォーム
		*/
		struct MoveCompensationParam : public BaseCompensationParam
		{

			bool isActorInSight;
			float currentTime;
			float minDistance;
			TransformPtr targetPos;
		};

	protected:
		
		float							currentTime_;
		
		//次ステートのインプットが押されているか？
		bool							isNextInput_;


		std::vector<ShotPtr>			shots_;
		std::vector<EffectPtr>			effects_;

		
		MoveCompensationParam moveCompentionParam_;

	protected:
		/* プライベート関数 */

		//ショット解放
		void ReleaseShot();
		//エフェクト解放
		void ReleaseEffect();
		//ノックバック取得
		virtual const KnockBackPtr GetKnockBack() { return std::make_shared<CFixedKnockBack>(Actor()); }
		//ショットのステータス作成（箱）
		virtual const ShotAABB& GetCreateShotStatusAABB();
		//ショットのステータス作成（回転を考慮した箱）
		virtual const ShotOBB& GetCreateShotStatusOBB();
		//ショットのステータス作成（球体）
		virtual const ShotSphere& GetCreateShotStatusSphere();
		//エフェクトのステータス作成
		virtual const EffectCreateParameter& GetCreateEffectStatus();
		//箱の弾を作成する
		virtual void CreateShotAABB();
		//回転を考慮した箱の弾を作成する
		virtual void CreateShotOBB();
		//球体の弾を作成する
		virtual void CreateShotSphere();
		//エフェクトを作成する
		virtual void CreateEffect();
		
		/*
		* @brief	視野内にアクターがいるか？
		* @param[out]	outPos			一番近くのアクター座標を格納する(※アクターがいた場合)
		* @param[out]	outMinDistance	最小検知距離を格納する
		* @param		sightAngle		視野角（度数法）
		* @param		maxDistance		最大検知距離
		* @return		true　なら存在する
		*/
		bool IsActorInSight(TransformPtr& outPos,float& offsetSize, float sightAngle, float maxDistance);

		/*
		* @brief	近くのアクターに向けて移動補正をかける
		* @param[in,out]	param		移動補正パラメータ
		* @retval			true		移動完了
		* @retval			false		移動中
		*/
		bool MoveCompensation(MoveCompensationParam& param);

		void SettingMoveCompensationParam(const BaseCompensationParam& param);
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CAttackBaseState();

		/**
		 * @brief		ステート内の開始処理
		 */
		virtual void Start() override;

		/**
		 * @brief		ステート内の実行処理
		 */
		virtual void Execution() override;

		/**
		 * @brief		ステート内の入力処理
		 */
		virtual void InputExecution() override;

		/**
		 * @brief		ステート内の終了処理
		 */
		virtual void End() override;
		
	};

}