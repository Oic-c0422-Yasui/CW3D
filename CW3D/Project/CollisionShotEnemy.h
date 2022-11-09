#pragma once
#include "Collision.h"
#include "Enemy.h"
#include "Shot.h"
#include "ActorObjectManager.h"

namespace Sample
{
	
	/**
	 * @brief		�G�ƒe�̂����蔻��
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

		//�m�b�N�o�b�N�l�ݒ�
		Vector3 knockBack = shot->GetKnockBack();
		shot->AddHit(enemy->GetID());
		//�_���[�W�ݒ�
		enemy->Damage(shot->GetDirection()->Get(enemy->GetPosition()), knockBack, shot->GetDamage(), shot->GetArmorBreakLevel());
		//�l���K�E�Z�Q�[�W
		float gauge = shot->GetGetUltGauge() * enemy->GetUltBoostMag();

		auto& actor =  ActorObjectManagerInstance.GetActor(shot->GetCharaType(), shot->GetParentID());
		actor->AddUltGauge(gauge);
	}
}