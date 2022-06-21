#pragma once
#include "Collision.h"
#include "Enemy.h"
#include "Shot.h"

namespace Sample
{
	
	/**
	 * @brief		�G�ƓG�̂����蔻��
	 */
	template < >
	inline void CCollision::CollisionObj<>(ShotPtr& shot, EnemyPtr& enemy) {
		//�ǂ��炩����\��
		if (!shot->IsShow() || !enemy->IsShow()) { return; }
		if (!shot->GetCollideFlg()){ return; }
		if (shot->GetCharaType() == CHARA_ENEMY) { return; }
		if (shot->IsHitId(enemy->GetID())) { return; }
		//�e�̋�`���Ƃɔ���
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

		//�m�b�N�o�b�N�l�ݒ�
		Vector3 knockBack = shot->GetKnockBack();
		shot->AddHit(enemy->GetID());
		enemy->Damage(shot->GetDirection()->Get(enemy->GetPosition()), knockBack, shot->GetDamage());
	}
}