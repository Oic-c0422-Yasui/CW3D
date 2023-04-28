#pragma once

#include	"BaseStateAI.h"
#include	"Player.h"
#include	"Collision.h"
#include	"InputDefine.h"
#include	"ParameterDefine.h"
#include	"ServiceLocator.h"

namespace ActionGame {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class CMoveStateAI : public CBaseStateAI
	{
	private:
		//������������
		int				currentLostTime_;
		bool			isAttack_;

		Vector3			attackRange_;
		Vector3			vigilangeRange_;
		int				attackTiming_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CMoveStateAI(Vector3 vigilangeRange, Vector3 attackRange, int timing);
			

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
		void End() override {
		}
	};
}