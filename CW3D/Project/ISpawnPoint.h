#pragma once

#include	<memory>
#include	"Common.h"

namespace Spawner
{
	/**
	 * @brief		�o���ʒu���菈��
	 */
	class __declspec(novtable) ISpawnPoint
	{
	public:
		/**
		 * @brief		����
		 */
		virtual void Next() = 0;

		/**
		 * @brief		��ԃ��Z�b�g
		 */
		virtual void Reset() = 0;

		/**
		 * @brief		�o���ʒu�擾
		 */
		virtual const Vector3& GetPosition() const noexcept = 0;

	};

	using SpawnPointPtr = std::shared_ptr<ISpawnPoint>;
}
