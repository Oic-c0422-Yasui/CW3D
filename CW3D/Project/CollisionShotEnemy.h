#pragma once
#include "Collision.h"
#include "Enemy.h"
#include "Shot.h"
#include "ActorObjectManager.h"

namespace ActionGame
{
	
	/**
	 * @brief		�G�ƒe�̂����蔻��
	 */
	template < >
	inline void CCollision::CollisionObj<>(ShotPtr& shot, EnemyPtr& enemy) {
		//�ǂ��炩����\��
		if (!shot->IsShow() || !enemy->IsShow()) { return; }
		if (!shot->IsEnableCollider()){ return; }
		if (shot->GetParentCharaType() == CHARA_TYPE::ENEMY) { return; }
		if (shot->IsHit(enemy->GetID())) { return; }
		//�e�̋�`���Ƃɔ���
		switch (shot->GetCollisionType())
		{
		case COLLISION_TYPE::SPHERE:
		{
			if (!CCollision::Collision(shot->GetColliderSphere(), enemy->GetCollider()))
			{
				return;
			}
			break;
		}
		case COLLISION_TYPE::AABB:
		{
			if (!CCollision::Collision(shot->GetColliderAABB(), enemy->GetCollider()))
			{
				return;
			}
			break;
		}
		case COLLISION_TYPE::OBB:
		{
			if (!CCollision::Collision(shot->GetColliderOBB(), enemy->GetCollider()))
			{
				return;
			}
			break;
		}
		default:
			break;
		}

		//�m�b�N�o�b�N�l�ݒ�
		Vector3 knockBack = shot->GetKnockBackPower();
		shot->AddHit(enemy->GetID());
		//�_���[�W�ݒ�
		enemy->Damage(shot->GetDirection()->Get(enemy->GetPosition()), knockBack, shot->GetDamage(), shot->GetArmorBreakLevel());
		//�l���K�E�Z�Q�[�W
		float gauge = shot->GetGetUltGauge() * enemy->GetUltBoostMag();

		auto id = shot->GetParentID();

		auto actor =  ActorObjectManagerInstance.GetActor(shot->GetParentCharaType(), shot->GetParentID());
		actor->AddUltGauge(gauge);
	}

	template< >
	inline void CCollision::CollisionObj<>(EnemyPtr& enemy, ShotPtr& shot) {
		return CollisionObj(enemy, shot);
	}
}