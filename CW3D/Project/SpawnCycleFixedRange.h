#pragma once
#include "ISpawnCycle.h"
#include "CharaTypeDefine.h"

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
		float			currentTime_;

		CHARA_TYPE		type_;
	public:
		/**
		 *	@brief		�R���X�g���N�^
		 */
		SpawnCycleFixedRange(int interval,CHARA_TYPE type);

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

