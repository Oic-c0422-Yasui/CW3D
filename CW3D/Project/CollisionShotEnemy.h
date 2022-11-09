#pragma once
#include "Collision.h"
#include "Enemy.h"
#include "Shot.h"
#include "ActorObjectManager.h"

namespace Sample
{
	
	/**
	 * @brief		“G‚Æ’e‚Ì‚ ‚½‚è”»’è
	 */
	template < >
	inline void CCollision::CollisionObj<>(ShotPtr& shot, EnemyPtr& enemy) {
		//‚Ç‚¿‚ç‚©‚ª”ñ•\Ž¦
		if (!shot->IsShow() || !enemy->IsShow()) { return; }
		if (!shot->GetCollideFlg()){ return; }
		if (shot->GetCharaType() == CHARA_ENEMY) { return; }
		if (shot->IsHitId(enemy->GetID())) { return; }
		//’e‚Ì‹éŒ`‚²‚Æ‚É”»’è
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
		default:
			break;
		}

		//ƒmƒbƒNƒoƒbƒN’lÝ’è
		Vector3 knockBack = shot->GetKnockBack();
		shot->AddHit(enemy->GetID());
		//ƒ_ƒ[ƒWÝ’è
		enemy->Damage(shot->GetDirection()->Get(enemy->GetPosition()), knockBack, shot->GetDamage(), shot->GetArmorBreakLevel());
		//Šl“¾•KŽE‹ZƒQ[ƒW
		float gauge = shot->GetGetUltGauge() * enemy->GetUltBoostMag();

		auto& actor =  ActorObjectManagerInstance.GetActor(shot->GetCharaType(), shot->GetParentID());
		actor->AddUltGauge(gauge);
	}
}