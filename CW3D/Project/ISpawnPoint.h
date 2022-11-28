#pragma once

#include	<memory>
#include	"Common.h"

namespace Spawner
{
	/**
	 * @brief		出現位置決定処理
	 */
	class __declspec(novtable) ISpawnPoint
	{
	public:
		/**
		 * @brief		次へ
		 */
		virtual void Next() = 0;

		/**
		 * @brief		状態リセット
		 */
		virtual void Reset() = 0;

		/**
		 * @brief		出現位置取得
		 */
		virtual const Vector3& GetPosition() const noexcept = 0;

	};

	using SpawnPointPtr = std::shared_ptr<ISpawnPoint>;
}
