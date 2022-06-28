#pragma once
#include "Collision.h"
#include "Player.h"
#include "Shot.h"

namespace Sample
{

	/**
	 * @brief		“G‚Æ“G‚Ì‚ ‚½‚è”»’è
	 */
	template < >
	inline void CCollision::CollisionObj<>(ShotPtr& shot, PlayerPtr& player) {
		//‚Ç‚¿‚ç‚©‚ª”ñ•\Ž¦
		if (!shot->IsShow() || !player->IsShow()) { return; }
		if (!shot->GetCollideFlg()) { return; }
		if (shot->GetCharaType() == CHARA_PLAYER) { return; }
		if (shot->IsHitId(player->GetID())) { return; }
		//’e‚Ì‹éŒ`‚²‚Æ‚É”»’è
		switch (shot->GetColliderType())
		{
		case COLLITION_SPHERE:
		{
			if (!CCollision::Collision(shot->GetColliderSphere(), player->GetCollider()))
			{
				return;
			}
			break;
		}
		case COLLITION_AABB:
		{
			if (!CCollision::Collision(shot->GetColliderAABB(), player->GetCollider()))
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
		shot->AddHit(player->GetID());
		player->Damage(shot->GetDirection()->Get(player->GetPosition()), knockBack, shot->GetDamage(),shot->GetArmorBreakLevel());
	}

	template< >
	inline void CCollision::CollisionObj<>(PlayerPtr& player, ShotPtr& shot) {
		return CollisionObj(player, shot);
	}
}