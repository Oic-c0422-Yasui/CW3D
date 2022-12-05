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
		ActionGame::EnemyBuildParameterArrayPtr m_Param;
		int m_CurrentParameterNum;
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

