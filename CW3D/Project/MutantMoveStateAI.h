#pragma once
#include	"BaseStateAI.h"

namespace ActionGame {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class CMutantMoveStateAI : public CBaseStateAI
	{
	private:
		//������������
		int				currentLostTime_;

		float			startSkillHPRate_;
		Vector3			attackRange_;
		Vector3			vigilangeRange_;
		Vector3			skillRange_;
		int				attackTiming_;
		int				skillTiming_;

	private:
		void ActivateSkill();

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CMutantMoveStateAI(Vector3 vigilangeRange, Vector3 attackRange, Vector3 skillRange,
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
