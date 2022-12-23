#pragma once
#include "Collision.h"
#include "Player.h"
#include "Shot.h"


namespace ActionGame
{

	/**
	 * @brief		弾とプレイヤーのあたり判定
	 */
	template < >
	inline void CCollision::CollisionObj<>(ShotPtr& shot, PlayerPtr& player) {
		//どちらかが非表示
		if (!shot->IsShow() || !player->IsShow()) { return; }
		if (!shot->IsEnableCollider()) { return; }
		if (shot->GetParentCharaType() == CHARA_TYPE::PLAYER) { return; }
		if (shot->IsHit(player->GetID())) { return; }
		if (player->IsInvincible()) { return; }
		//弾の矩形ごとに判定
		switch (shot->GetCollisionType())
		{
		case COLLISION_TYPE::SPHERE:
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
		case COLLISION_TYPE::AABB:
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
		//プレイヤーが回避状態なら
		if (player->IsEscape())
		{
			player->AddUltGauge(20.0f);
			auto& invincible = player->GetActor()->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
			invincible = 1.0f;

			MyUtilities::ANIM_DATA_ARRAY anims(
				{	
					{0.0f,TimeScaleControllerInstance.GetTimeScale()},
					{0.05f,TimeScaleControllerInstance.GetTimeScale()},
					{0.1f,0.0f},
					{0.15f,0.0f},
					{0.5f,TimeScaleControllerInstance.GetTimeScale()}
				}
			);

			TimeScaleControllerInstance.SetTimeScale(anims);
		}
		else
		{
			//ノックバック値設定
			Vector3 knockBack = shot->GetKnockBackPower();
			shot->AddHit(player->GetID());
			player->Damage(shot->GetDirection()->Get(player->GetPosition()), knockBack, shot->GetDamage(),shot->GetArmorBreakLevel());
		}
	}

	template< >
	inline void CCollision::CollisionObj<>(PlayerPtr& player, ShotPtr& shot) {
		return CollisionObj(player, shot);
	}
}