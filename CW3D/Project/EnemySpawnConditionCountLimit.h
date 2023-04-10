#pragma once
#include "ISpawnCondition.h"

namespace Spawner
{
	/**
	 *	@brief		�X�|�[���̍ő吔
	 */
	class CEnemySpawnConditionCountLimit : public ISpawnCondition
	{
	private:
		//���E��
		size_t		maxCount_;
		//���ݐ�
		size_t		count_;
	public:
		/**
		 *	@brief		�R���X�g���N�^
		 */
		CEnemySpawnConditionCountLimit(size_t maxCount);
	
		/**
		 * @brief		����
		 * @return		true �Ȃ�o��
		 */
		bool IsValid() const noexcept override;
	
		/**
		 * @brief		���݂̃X�|�[�����ݒ�
		 * @param		count	���݂̃X�|�[����
		 */
		void SetCount(size_t count) noexcept
		{
			count_ = count;
		}
	};
	using EnemySpawnConditionCountLimitPtr = std::shared_ptr<CEnemySpawnConditionCountLimit>;

}


