#pragma once

#include	<memory>
namespace Spawner
{
	/**
	 * @brief		出現オブジェクト生成処理
	 */
	template < typename T >
	class ISpawnObjectCreator
	{
	public:
		/**
		 * @brief		生成
		 */
		virtual ActionGame::ActorObjectPtr Create() = 0;
	};

	template <typename T> using SpawnObjectCreatorPtr = std::shared_ptr<ISpawnObjectCreator<T>>;
}