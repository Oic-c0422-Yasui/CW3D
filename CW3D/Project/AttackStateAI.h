#pragma once

#include	"StateAI.h"
#include	"Player.h"
#include	"Collision.h"
#include	"ServiceLocator.h"

namespace ActionGame {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class CAttackStateAI : public CStateAI
	{
	private:
		//������������
		int				currentLostTime;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CAttackStateAI();

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