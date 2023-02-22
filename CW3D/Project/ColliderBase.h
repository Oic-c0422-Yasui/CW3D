#pragma once
#include <memory>
#include "CollisionDefine.h"

namespace MyUtil
{
	/*
	* @brief	コライダー用基底クラス
	*/
	class CColliderBase
	{
	protected:
		//当たり判定のタイプ
		COLLISION_TYPE type_;
	public:
		virtual ~CColliderBase() = default;
		/*
		* @brief	接触判定
		* @param	collider　コライダー
		*/
		virtual bool IsCollision(const CColliderBase& collider) = 0;

		
		/*
		* @brief	接触判定
		* @param	collider　コライダーのポインタ
		*/
		virtual bool IsCollision(const ColliderPtr& collider) = 0;

	};
	using ColliderPtr = std::shared_ptr<CColliderBase>;

	
}


