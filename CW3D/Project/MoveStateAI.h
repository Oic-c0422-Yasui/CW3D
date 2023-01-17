#pragma once

#include	"StateAI.h"
#include	"Player.h"
#include	"Collision.h"
#include	"InputDefine.h"
#include	"ParameterDefine.h"
#include	"ServiceLocator.h"

namespace ActionGame {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class MoveStateAI : public StateAI
	{
	private:
		//������������
		int				currentLostTime;
		bool			attackFlg;

		Vector3			m_AttackRange;
		Vector3			m_VigilangeRange;
		int				m_AttackTiming;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		MoveStateAI(Vector3 vigilangeRange , Vector3 attackRange,int timing)
			: StateAI()
			, currentLostTime(0)
			, attackFlg(false)
			, m_AttackRange(attackRange)
			, m_VigilangeRange(vigilangeRange)
			, m_AttackTiming(timing)
		{
		}

		/**
		 * @brief		���p�L�[�̓o�^
		 */
		void RegisterKey() override {
			Input()->AddKey(INPUT_KEY_HORIZONTAL);
			Input()->AddKey(INPUT_KEY_VERTICAL);
			Input()->AddKey(INPUT_KEY_ATTACK);
		}

		/**
		 * @brief		�J�n
		 */
		void Start() override {
			currentLostTime = 0;
			attackFlg = false;
		}

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