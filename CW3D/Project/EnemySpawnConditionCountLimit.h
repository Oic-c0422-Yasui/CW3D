#pragma once
#include "ISpawnCondition.h"

namespace Spawner
{
	/**
	 *	@brief		スポーンの最大数
	 */
	class CEnemySpawnConditionCountLimit : public ISpawnCondition
	{
	private:
		//限界数
		size_t		maxCount_;
		//現在数
		size_t		count_;
	public:
		/**
		 *	@brief		コンストラクタ
		 */
		CEnemySpawnConditionCountLimit(size_t maxCount);
	
		/**
		 * @brief		判定
		 * @return		true なら出現
		 */
		bool IsValid() const noexcept override;
	
		/**
		 * @brief		現在のスポーン数設定
		 * @param		count	現在のスポーン数
		 */
		void SetCount(size_t count) noexcept
		{
			count_ = count;
		}
	};
	using EnemySpawnConditionCountLimitPtr = std::shared_ptr<CEnemySpawnConditionCountLimit>;

}


