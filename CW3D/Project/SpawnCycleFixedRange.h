#pragma once
#include "ISpawnCycle.h"

namespace Spawner
{
	/**
	 * @brief		�o���������菈��
	 */
	class SpawnCycleFixedRange : public ISpawnCycle
	{
	private:

		//�Ԋu
		float			m_Interval;

		//�ҋ@����
		float			m_CurrentTime;
	public:
		/**
		 *	@brief		�R���X�g���N�^
		 */
		SpawnCycleFixedRange(int interval);

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

