#pragma once

#include	<vector>
#include	<memory>

namespace Spawner
{
	/**
	 * @brief		�o���������菈��
	 */
	class __declspec(novtable) ISpawnCondition
	{
	public:
		/**
		 * @brief		����
		 * @return		true �Ȃ�o��
		 */
		virtual bool IsValid() const noexcept = 0;
	};

	using SpawnConditionPtr = std::shared_ptr<ISpawnCondition>;
	using SpawnConditionArray = std::vector<SpawnConditionPtr>;
}