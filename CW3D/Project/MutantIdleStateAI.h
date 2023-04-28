#pragma once


#include	"IdleStateAI.h"

namespace ActionGame {

	/**
	 * @brief		�ҋ@�X�e�[�g
	 */
	class CMutantIdleStateAI : public CIdleStateAI
	{
	private:
		bool isAngry;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CMutantIdleStateAI(Vector3 vigilanceRange, Vector3 attackRange, int attackTiming);

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
