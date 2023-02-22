#pragma once
#include <memory>
#include "CollisionDefine.h"

namespace MyUtil
{
	/*
	* @brief	�R���C�_�[�p���N���X
	*/
	class CColliderBase
	{
	protected:
		//�����蔻��̃^�C�v
		COLLISION_TYPE type_;
	public:
		virtual ~CColliderBase() = default;
		/*
		* @brief	�ڐG����
		* @param	collider�@�R���C�_�[
		*/
		virtual bool IsCollision(const CColliderBase& collider) = 0;

		
		/*
		* @brief	�ڐG����
		* @param	collider�@�R���C�_�[�̃|�C���^
		*/
		virtual bool IsCollision(const ColliderPtr& collider) = 0;

	};
	using ColliderPtr = std::shared_ptr<CColliderBase>;

	
}


