#include "Shot.h"

using namespace ActionGame;



ActionGame::Shot::Shot()
	: m_Collider(std::make_shared<CAttackCollider>())
	, m_Position(0, 0, 0)
	, m_AABB()
	, m_Radius(0.0f)
	, m_ShowFlg(false)
	, m_EnableColliderFlg(false)
	, m_ParentCharaType(CHARA_TYPE::PLAYER)
	, m_Speed(0.0f)
	, m_KnockBackPower(0, 0, 0)
	, m_KnockBackDirection()
	, m_Offset(0, 0, 0)
	, m_Damage(0)
	, m_NextHitTime(0.0f)
	, m_CollisionType(COLLISION_TYPE::AABB)
	, m_ArmorBreakLevel(0)
	, m_GetUltGauge(0.0f)
	, m_ParentID(0)

{
}

ActionGame::Shot::~Shot()
{
}

void ActionGame::Shot::CreateBase(const Vector3& pos, const ShotCreateParameter& shot)
{
	m_Position = pos;
	m_Offset = shot.offset;
	m_ParentCharaType = shot.type;
	m_Damage = shot.damage;
	m_NextHitTime = shot.nextHitTime;
	m_Speed = 0.0f;
	m_ShowFlg = true;
	m_EnableColliderFlg = shot.collideFlg;
	m_KnockBackPower = shot.knockBack;
	m_KnockBackDirection = shot.direction;
	m_ArmorBreakLevel = shot.armorBreakLevel;
	m_GetUltGauge = shot.getUltGauge;
	m_ParentID = shot.parentID;
}



void ActionGame::Shot::Create(const Vector3& pos, const ShotSphere& sphire)
{
	//ベースのパラメータ作成
	CreateBase(pos, sphire);

	//追加のパラメータ作成
	m_Radius = sphire.Radius;
	m_Collider->SetPosition(m_Position);
	m_Collider->SetRadius(m_Radius);
	m_CollisionType = COLLISION_TYPE::SPHERE;
}

void ActionGame::Shot::Create(const Vector3& pos, const ShotAABB& aabb)
{
	//ベースのパラメータ作成
	CreateBase(pos, aabb);

	//追加のパラメータ作成
	m_Size = aabb.size;
	m_AABB.Size = m_Size;
	m_AABB.SetPosition(m_Position);
	m_CollisionType = COLLISION_TYPE::AABB;
}

void ActionGame::Shot::Create(const Vector3& pos, const ShotOBB& obb)
{
	//ベースのパラメータ作成
	CreateBase(pos, obb);

	//追加のパラメータ作成
	m_Size = obb.size;
	m_OBB.Position = m_Position;
	m_OBB.Size = m_Size;
	m_OBB.Angle = obb.angle;
	m_OBB.CalculateAxis();
	m_CollisionType = COLLISION_TYPE::OBB;
}

void ActionGame::Shot::ApplyColliderPosition()
{
	switch (m_CollisionType)
	{
	case COLLISION_TYPE::SPHERE:
	{
		m_Collider->SetPosition(m_Position);
		break;
	}
	case COLLISION_TYPE::AABB:
	{
		m_AABB.SetPosition(m_Position);
		break;
	}
	case COLLISION_TYPE::OBB:
	{
		m_OBB.Position = m_Position;
		break;
	}
	default:
	{
		break;
	}
	}
}

void ActionGame::Shot::Update()
{
	if (!m_ShowFlg)
	{
		return;
	}

	m_Position.x += m_Speed * TimeScaleControllerInstance.GetTimeScale(m_ParentCharaType);
	
	//コライダーの座標を現在の座標に合わせる
	ApplyColliderPosition();

	//タイマー更新
	UpdateTime();
	//ヒットID削除
	DeleteHitId();
}

void ActionGame::Shot::Render()
{
	if (!m_ShowFlg)
	{
		return;
	}
}


void ActionGame::Shot::UpdateTime()
{
	for (auto& id : m_HitIDs)
	{
		if (id.Time > 0.0f)
		{
			id.Time -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(m_ParentCharaType);
		}
	}
}


