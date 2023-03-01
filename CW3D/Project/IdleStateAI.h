#pragma once

#include	"StateAI.h"
#include	"Player.h"
#include	"Collision.h"
#include	"Common.h"
#include	"InputDefine.h"
#include	"ServiceLocator.h"

namespace ActionGame {

	/**
	 * @brief		�ҋ@�X�e�[�g
	 */
	class CIdleStateAI : public CStateAI
	{
	private:
		bool			isAttack;

		Vector3			vigilangeRange_;

		Vector3			attackRange_;

		int				attackTiming_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CIdleStateAI(Vector3 vigilanceRange, Vector3 attackRange, int attackTiming);
			
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
