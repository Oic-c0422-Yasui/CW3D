#pragma once

#include	"IAICycle.h"

namespace ActionGame
{
	/**
	 * @brief		�Œ�������菈��
	 */
	class AICycleFixed : public IAICycle
	{
	private:
		//�Ԋu
		int				m_Interval;

		//�ҋ@����
		int				m_CurrentTime;
	public:
		/**
		 *	@brief		�R���X�g���N�^
		 */
		AICycleFixed(int wait)
			: m_Interval(wait)
			, m_CurrentTime(0)
		{
		}

		/**
		 * @brief		�X�V
		 * @return		true�Ȃ�o��
		 */
		bool Update() override {
			m_CurrentTime++;
			if (m_CurrentTime > m_Interval)
			{
				m_CurrentTime -= m_Interval;
				return true;
			}
			return false;
		}

		/**
		 * @brief		��ԃ��Z�b�g
		 */
		void Reset() override {
			m_CurrentTime = 0;
		}
	};
}