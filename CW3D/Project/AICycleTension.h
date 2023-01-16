#pragma once
#include "IAICycle.h"
#include	"Player.h"
#include "ServiceLocator.h"

namespace ActionGame
{
	/**
	 * @brief		�v���C���[�Ƃ̋����ŋٔ��x�Ƃ��Ď������菈��
	 */
    class AICycleTension : public IAICycle
	{
	private:
		//���̃A�N�^�[
		ActorPtr		m_Actor;

		//�ҋ@����
		int			m_CurrentTime;
	public:
		/**
		 *	@brief		�R���X�g���N�^
		 */
		AICycleTension(ActorPtr actor)
			: m_Actor(actor)
			, m_CurrentTime(0)
		{
		}

		/**
		 * @brief		�X�V
		 * @return		true�Ȃ�o��
		 */
		bool Update() override;

		/**
		 * @brief		��ԃ��Z�b�g
		 */
		void Reset() override {
			m_CurrentTime = 0;
		}
	};
}


