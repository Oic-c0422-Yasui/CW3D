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
		int				interval;

		//�ҋ@����
		int				currentTime;
	public:
		/**
		 *	@brief		�R���X�g���N�^
		 */
		AICycleFixed(int wait)
			: interval(wait)
			, currentTime(0)
		{
		}

		/**
		 * @brief		�X�V
		 * @return		true�Ȃ�o��
		 */
		bool Update() override {
			currentTime++;
			if (currentTime > interval)
			{
				currentTime -= interval;
				return true;
			}
			return false;
		}

		/**
		 * @brief		��ԃ��Z�b�g
		 */
		void Reset() override {
			currentTime = 0;
		}
	};
}