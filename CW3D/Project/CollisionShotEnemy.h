#pragma once
#include "Collision.h"
#include "Enemy.h"
#include "Shot.h"
#include "ActorObjectManager.h"

namespace ActionGame
{
	
	/**
	 * @brief		敵と弾のあたり判定
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
		case COLLISION_SPHERE:
		{
			if (!CCollision::Collision(shot->GetColliderSphere(), enemy->GetCollider()))
			{
				return;
			}
			break;
		}
		case COLLISION_AABB:
		{
			if (!CCollision::Collision(shot->GetColliderAABB(), enemy->GetCollider()))
			{
				return;
			}
			break;
		}
		case COLLISION_OBB:
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

		//ノックバック値設定
		Vector3 knockBack = shot->GetKnockBack();
		shot->AddHit(enemy->GetID());
		//ダメージ設定
		enemy->Damage(shot->GetDirection()->Get(enemy->GetPosition()), knockBack, shot->GetDamage(), shot->GetArmorBreakLevel());
		//獲得必殺技ゲージ
		float gauge = shot->GetGetUltGauge() * enemy->GetUltBoostMag();

		auto id = shot->GetParentID();

		auto actor =  ActorObjectManagerInstance.GetActor(shot->GetCharaType(), shot->GetParentID());
		actor->AddUltGauge(gauge);
	}

	template< >
	inline void CCollision::CollisionObj<>(EnemyPtr& enemy, ShotPtr& shot) {
		return CollisionObj(enemy, shot);
	}
}