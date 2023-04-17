#pragma once
#include "Common.h"

namespace MyUtil
{
	/*
	* @brief	ベクトル方向
	*/
	class VectorDirection
	{
	public:
		/*
		* @brief	前方ベクトル
		*/
		static inline const Vector3 Forward() noexcept
		{
			return Vector3(0, 0, 1);
		}
		/*
		* @brief	後方ベクトル
		*/
		static inline const Vector3 Back() noexcept
		{
			return Vector3(0, 0, -1);
		}
		/*
		* @brief	右方ベクトル
		*/
		static inline const Vector3 Right() noexcept
		{
			return Vector3(1, 0, 0);
		}
		/*
		* @brief	左方ベクトル
		*/
		static inline const Vector3 Left() noexcept
		{
			return Vector3(-1, 0, 0);
		}
		/*
		* @brief	上方ベクトル
		*/
		static inline const Vector3 Up() noexcept
		{
			return Vector3(0, 1, 0);
		}
		/*
		* @brief	下方ベクトル
		*/
		static inline const Vector3 Down() noexcept
		{
			return Vector3(0, -1, 0);
		}

	};
}



