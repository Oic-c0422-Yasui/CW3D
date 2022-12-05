#pragma once

#include	<memory>
namespace Spawner
{
	/**
	 * @brief		�o���I�u�W�F�N�g��������
	 */
	template < typename T >
	class ISpawnObjectCreator
	{
	public:
		/**
		 * @brief		����
		 */
		virtual ActionGame::ActorObjectPtr Create() = 0;
	};

	template <typename T> using SpawnObjectCreatorPtr = std::shared_ptr<ISpawnObjectCreator<T>>;
}