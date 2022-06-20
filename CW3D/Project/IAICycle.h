#pragma once

#include	<memory>

namespace Sample
{
	/**
	 * @brief		�������菈��
	 */
	class __declspec(novtable) IAICycle
	{
	public:
		/**
		 * @brief		�X�V
		 * @return		true�Ȃ画��
		 */
		virtual bool Update() = 0;
		/**
		 * @brief		��ԃ��Z�b�g
		 */
		virtual void Reset() = 0;
	};
	//�|�C���^�u������
	using AICyclePtr = std::shared_ptr<IAICycle>;
}
