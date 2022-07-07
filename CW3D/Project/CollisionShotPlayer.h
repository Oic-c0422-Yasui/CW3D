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
		if (player->IsInvincible()) { return; }
		//’e‚Ì‹éŒ`‚²‚Æ‚É”»’è
		switch (shot->GetColliderType())
		{
		case COLLITION_SPHERE:
		{
			if (player->IsEscape())
			{
				if (!CCollision::Collision(shot->GetColliderSphere(), player->GetEscapeCollider()))
				{
					return;
				}
			}
			else if (!CCollision::Collision(shot->GetColliderSphere(), player->GetCollider()))
			{
				return;
			}
			break;
		}
		case COLLITION_AABB:
		{
			if (player->IsEscape())
			{
				if (!CCollision::Collision(shot->GetColliderAABB(), player->GetEscapeCollider()))
				{
					return;
				}
			}
			else if (!CCollision::Collision(shot->GetColliderAABB(), player->GetCollider()))
			{
				return;
			}
			break;
		}
		default:
			break;
		}

		if (player->IsEscape())
		{
			player->AddUltGauge(20.0f);
			auto& invincible = player->GetActor()->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
			invincible = 1.0f;
			MyUtilities::ANIM_DATA anim[] =
			{
				{0.0f,TimeControllerInstance.GetTimeScale()},
				{0.05f,TimeControllerInstance.GetTimeScale()},
				{0.1f,0.0f},
				{0.15f,0.0f},
				{0.5f,TimeControllerInstance.GetTimeScale()}
			};
			TimeControllerInstance.SetTimeScale(anim, _countof(anim));
		}
		else
		{
			//ƒmƒbƒNƒoƒbƒN’lÝ’è
			Vector3 knockBack = shot->GetKnockBack();
			shot->AddHit(player->GetID());
			player->Damage(shot->GetDirection()->Get(player->GetPosition()), knockBack, shot->GetDamage(),shot->GetArmorBreakLevel());
		}
	}

	template< >
	inline void CCollision::CollisionObj<>(PlayerPtr& player, ShotPtr& shot) {
		return CollisionObj(player, shot);
	}
}