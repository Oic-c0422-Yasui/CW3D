#pragma once


#include	"BaseStateAI.h"

namespace ActionGame {

	/**
	 * @brief		待機ステート
	 */
	class CMutantIdleStateAI : public CBaseStateAI
	{
	private:
		float			startSkillHPRate_;
		Vector3			vigilanceRange_;
		Vector3			attackRange_;
		Vector3			skillRange_;
		int				attackTiming_;
		int				skillTiming_;

	private:
		void ActivateSkill();

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CMutantIdleStateAI(Vector3 vigilanceRange, Vector3 attackRange, Vector3 skillRange,
			int attackTiming, int skillTiming, float skillStartHpRate);

		/**
		 * @brief		利用キーの登録
		 */
		void RegisterKey() override;

		/**
		 * @brief		開始
		 */
		void Start() override;

		/**
		 * @brief		更新
		 */
		void Update() override;

		/**
		 * @brief		終了
		 */
		void End() override;
	};

}
