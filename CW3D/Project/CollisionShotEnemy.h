#pragma once
#include "Collision.h"
#include "Enemy.h"
#include "Shot.h"

namespace Sample
{
	
	/**
	 * @brief		敵と敵のあたり判定
	 */
	template < >
	inline void CCollision::CollisionObj<>(ShotPtr& shot, EnemyPtr& enemy) {
		//どちらかが非表示
		if (!shot->IsShow() || !enemy->IsShow()) { return; }
		if (!shot->GetCollideFlg()){ return; }
		if (shot->GetCharaType() == CHARA_ENEMY) { return; }
		if (shot->IsHitId(enemy->GetID())) { return; }
		//弾の矩形ごとに判定
		switch (shot->GetColliderType())
		{
		case COLLITION_SPHERE:
		{
			if (!CCollision::Collision(shot->GetColliderSphere(), enemy->GetCollider()))
			{
				return;
			}
			break;
		}
		case COLLITION_AABB:
		{
			if (!CCollision::Collision(shot->GetColliderAABB(), enemy->GetCollider()))
			{
				return;
			}
			break;
		}
		default:
			break;
		}

		//ノックバック値設定
		Vector3 knockBack = shot->GetKnockBack();
		shot->AddHit(enemy->GetID());
		enemy->Damage(shot->GetDirection()->Get(enemy->GetPosition()), knockBack, shot->GetDamage(), shot->GetArmorBreakLevel());
	}
}