#pragma once


#include	"BaseState.h"
#include	"FixedKnockBack.h"
#include	"EffectController.h"
#include	"ShotManager.h"
#include	"SkillDefine.h"
#include	"DamageUtilities.h"
#include	"MoveCompensationAction.h"

namespace ActionGame {

	/**
	 * @brief		移動ステート
	 */
	class CAttackBaseState : public CBaseState
	{
	public:
		typedef struct BASEPARAM
		{
			BYTE armorLevel;
		}BaseParam;
		

	protected:
		
		float							currentTime_;
		
		//次ステートのインプットが押されているか？
		bool							isNextInput_;


		std::vector<ShotPtr>			shots_;
		std::vector<EffectPtr>			effects_;

		//移動補正アクション
		MoveCompensationActionPtr		moveCompensation_;

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
		//アーマーレベルを設定する
		virtual void SetArmorLevel(BYTE level);
		
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