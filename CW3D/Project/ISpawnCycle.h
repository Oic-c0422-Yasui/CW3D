#pragma once

#include	<memory>

namespace Spawner
{
	/**
	 * @brief		�o���������菈��
	 */
	class __declspec(novtable) ISpawnCycle
	{
	public:
		/**
		 * @brief		�X�V
		 * @return		true�Ȃ�o��
		 */
		virtual bool Update() = 0;
		/**
		 * @brief		��ԃ��Z�b�g
		 */
		virtual void Reset() = 0;
	};
	//�|�C���^�u������
	using SpawnCyclePtr = std::shared_ptr<ISpawnCycle>;
}
