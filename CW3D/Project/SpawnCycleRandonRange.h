#pragma once
#include "ISpawnCycle.h"
#include "Common.h"

namespace Spawner
{
	/**
	 * @brief		�o���������菈��
	 */
	class SpawnCycleRandomRange : public ISpawnCycle
	{
	private:
		//�Ԋu�ŏ�
		int				m_IntervalMin;
		//�Ԋu�ő�
		int				m_IntervalMax;

		//���݂̊Ԋu
		float			m_CurrentInterval;

		//�ҋ@����
		float			currentTime_;
	public:
		/**
		 *	@brief		�R���X�g���N�^
		 */
		SpawnCycleRandomRange(int min, int max);

		/**
		 * @brief		�X�V
		 * @return		true�Ȃ�o��
		 */
		bool Update() override;

		/**
		 * @brief		��ԃ��Z�b�g
		 */
		void Reset() override {
			currentTime_ = 0;
		}
	};
    
}


