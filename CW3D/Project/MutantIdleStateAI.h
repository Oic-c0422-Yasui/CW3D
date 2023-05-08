#pragma once


#include	"BaseStateAI.h"

namespace ActionGame {

	/**
	 * @brief		�ҋ@�X�e�[�g
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
		 * @brief		�R���X�g���N�^
		 */
		CMutantIdleStateAI(Vector3 vigilanceRange, Vector3 attackRange, Vector3 skillRange,
			int attackTiming, int skillTiming, float skillStartHpRate);

		/**
		 * @brief		���p�L�[�̓o�^
		 */
		void RegisterKey() override;

		/**
		 * @brief		�J�n
		 */
		void Start() override;

		/**
		 * @brief		�X�V
		 */
		void Update() override;

		/**
		 * @brief		�I��
		 */
		void End() override;
	};

}
