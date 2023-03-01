#pragma once
#include "EnemyBuildParameter.h"

namespace Spawner
{
	/**
	* @brief		出現パラメータ決定処理
	*/
	class EnemySpawnParameter
	{
	private:
		ActionGame::EnemyBuildParameterArrayPtr param_;
		size_t CurrentParameterNum_;
	public:
		/**
		 *	@brief		コンストラクタ
		 */
		EnemySpawnParameter(const ActionGame::EnemyBuildParameterArrayPtr& param);

		/**
		 * @brief		次へ
		 */
		void Next();

		/**
		 * @brief		状態リセット
		 */
		void Reset();

		const ActionGame::EnemyBuildParameterPtr& GetParameter() const noexcept;
	};

	using EnemySpawnParameterPtr = std::shared_ptr<EnemySpawnParameter>;
}

