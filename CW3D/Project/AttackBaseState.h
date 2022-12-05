#pragma once


#include	"State.h"
#include	"FixedKnockBack.h"
#include	"EffectController.h"
#include	"ShotManager.h"

namespace ActionGame {

	/**
	 * @brief		移動ステート
	 */
	class AttackBaseState : public State
	{
	public:
		typedef struct BASEPARAM
		{
			BYTE armorLevel;
		}BaseParam;
	protected:
		
		float							m_CurrentTime;
		bool							m_NextInputFlg;

		std::vector<ShotPtr>			m_pShots;
		std::vector<EffectPtr>			m_pEffects;

	protected:
		/* メンバ関数 */

		//ショット解放
		void ReleaseShot();
		//エフェクト解放
		void ReleaseEffect();
		//ノックバック取得
		virtual const KnockBackPtr GetKnockBack() { return std::make_shared<FixedKnockBack>(Actor()); }
		//ショットのステータス作成（立方体）
		virtual const ShotAABB& GetCreateShotStatusAABB();
		//ショットのステータス作成（球体）
		virtual const ShotSphere& GetCreateShotStatusSphere();
		//エフェクトのステータス作成
		virtual const EffectCreateParameter& GetCreateEffectStatus();
		//立方体の弾を作成する
		virtual void CreateShotAABB();
		//球体の弾を作成する
		virtual void CreateShotSphere();
		//エフェクトを作成する
		virtual void CreateEffect();
	public:
		/**
		 * @brief		コンストラクタ
		 */
		AttackBaseState();

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