#pragma once
#include "Collision.h"
#include "Player.h"
#include "Shot.h"

namespace Sample
{

	/**
	 * @brief		�G�ƓG�̂����蔻��
	 */
	template < >
	inline void CCollision::CollisionObj<>(ShotPtr& shot, PlayerPtr& player) {
		//�ǂ��炩����\��
		if (!shot->IsShow() || !player->IsShow()) { return; }
		if (!shot->GetCollideFlg()) { return; }
		if (shot->GetCharaType() == CHARA_PLAYER) { return; }
		if (shot->IsHitId(player->GetID())) { return; }
		//�e�̋�`���Ƃɔ���
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

		//�m�b�N�o�b�N�l�ݒ�
		Vector3 knockBack = shot->GetKnockBack();
		shot->AddHit(player->GetID());
		player->Damage(shot->GetDirection()->Get(player->GetPosition()), knockBack, shot->GetDamage(),shot->GetArmorBreakLevel());
	}

	template< >
	inline void CCollision::CollisionObj<>(PlayerPtr& player, ShotPtr& shot) {
		return CollisionObj(player, shot);
	}
}