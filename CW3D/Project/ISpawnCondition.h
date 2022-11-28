#pragma once

#include	<vector>
#include	<memory>

namespace Spawner
{
	/**
	 * @brief		oŒ»ğŒ”»’èˆ—
	 */
	class __declspec(novtable) ISpawnCondition
	{
	public:
		/**
		 * @brief		”»’è
		 * @return		true ‚È‚çoŒ»
		 */
		virtual bool IsValid() const noexcept = 0;
	};

	using SpawnConditionPtr = std::shared_ptr<ISpawnCondition>;
	using SpawnConditionArray = std::vector<SpawnConditionPtr>;
}