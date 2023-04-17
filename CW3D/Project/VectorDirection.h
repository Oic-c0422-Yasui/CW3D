#pragma once
#include "Common.h"

namespace MyUtil
{
	/*
	* @brief	�x�N�g������
	*/
	class VectorDirection
	{
	public:
		/*
		* @brief	�O���x�N�g��
		*/
		static inline const Vector3 Forward() noexcept
		{
			return Vector3(0, 0, 1);
		}
		/*
		* @brief	����x�N�g��
		*/
		static inline const Vector3 Back() noexcept
		{
			return Vector3(0, 0, -1);
		}
		/*
		* @brief	�E���x�N�g��
		*/
		static inline const Vector3 Right() noexcept
		{
			return Vector3(1, 0, 0);
		}
		/*
		* @brief	�����x�N�g��
		*/
		static inline const Vector3 Left() noexcept
		{
			return Vector3(-1, 0, 0);
		}
		/*
		* @brief	����x�N�g��
		*/
		static inline const Vector3 Up() noexcept
		{
			return Vector3(0, 1, 0);
		}
		/*
		* @brief	�����x�N�g��
		*/
		static inline const Vector3 Down() noexcept
		{
			return Vector3(0, -1, 0);
		}

	};
}



