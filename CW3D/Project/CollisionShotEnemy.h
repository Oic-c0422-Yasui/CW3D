#pragma once
#include "Collision.h"
#include "Enemy.h"
#include "Shot.h"
#include "ActorObjectManager.h"
#include "GravityUtilities.h"

namespace ActionGame
{
	
	/**
	 * @brief		敵と弾のあたり判定
	 */
	template < >
	inline void CCollision::CollisionObj<>(ShotPtr& shot, EnemyPtr& enemy) {
		//どちらかが非表示
		if (!shot->IsShow() || !enemy->IsShow()) { return; }
		if (!shot->IsEnableCollider()){ return; }
		if (shot->GetParentCharaType() == CHARA_TYPE::ENEMY) { return; }
		if (shot->GetParentCharaType() == CHARA_TYPE::BOSS) { return; }
		if (shot->IsHit(enemy->GetID())) { return; }
		//弾の矩形ごとに判定
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

		//ノックバック値設定
		Vector3 knockBack = shot->GetKnockBackPower();
		shot->AddHit(enemy->GetID());
		//ダメージ設定
		enemy->Damage(shot->GetDirection()->Get(enemy->GetPosition()), knockBack, shot->GetDamage(), shot->GetArmorBreakLevel(),shot->GetDamageEffect());
		//獲得必殺技ゲージ
		float gauge = shot->GetRecieveUltGauge() * enemy->GetUltBoostMag();

		//重力スケール設定
		MyUtil::SetGravityScale(enemy->GetActor()->GetVelocity(), shot->GetGravityScale());

		auto actor =  ActorObjectManagerInstance.GetActor(shot->GetParentCharaType(), shot->GetParentID());
		actor->AddUltGauge(gauge);
	}

	template< >
	inline void CCollision::CollisionObj<>(EnemyPtr& enemy, ShotPtr& shot) {
		return CollisionObj(enemy, shot);
	}
}