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
		int				currentTime_;
	public:
		/**
		 *	@brief		�R���X�g���N�^
		 */
		AICycleFixed(int wait)
			: m_Interval(wait)
			, currentTime_(0)
		{
		}

		/**
		 * @brief		�X�V
		 * @return		true�Ȃ�o��
		 */
		bool Update() override {
			currentTime_++;
			if (currentTime_ > m_Interval)
			{
				currentTime_ -= m_Interval;
				return true;
			}
			return false;
		}

		/**
		 * @brief		��ԃ��Z�b�g
		 */
		void Reset() override {
			currentTime_ = 0;
		}
	};
}