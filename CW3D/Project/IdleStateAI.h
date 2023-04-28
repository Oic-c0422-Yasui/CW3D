#pragma once

#include	"BaseStateAI.h"
#include	"Player.h"
#include	"Collision.h"
#include	"Common.h"
#include	"InputDefine.h"
#include	"ServiceLocator.h"

namespace ActionGame {

	/**
	 * @brief		�ҋ@�X�e�[�g
	 */
	class CIdleStateAI : public CBaseStateAI
	{
	protected:
		bool			isAttack_;

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
		virtual void RegisterKey() override;

		/**
		 * @brief		�J�n
		 */
		virtual void Start() override;

		/**
		 * @brief		�X�V
		 */
		virtual void Update() override;

		/**
		 * @brief		�I��
		 */
		virtual void End() override;
	};
}
