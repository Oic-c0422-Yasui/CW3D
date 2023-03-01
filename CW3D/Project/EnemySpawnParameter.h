#pragma once
#include "EnemyBuildParameter.h"

namespace Spawner
{
	/**
	* @brief		�o���p�����[�^���菈��
	*/
	class EnemySpawnParameter
	{
	private:
		ActionGame::EnemyBuildParameterArrayPtr param_;
		size_t CurrentParameterNum_;
	public:
		/**
		 *	@brief		�R���X�g���N�^
		 */
		EnemySpawnParameter(const ActionGame::EnemyBuildParameterArrayPtr& param);

		/**
		 * @brief		����
		 */
		void Next();

		/**
		 * @brief		��ԃ��Z�b�g
		 */
		void Reset();

		const ActionGame::EnemyBuildParameterPtr& GetParameter() const noexcept;
	};

	using EnemySpawnParameterPtr = std::shared_ptr<EnemySpawnParameter>;
}

