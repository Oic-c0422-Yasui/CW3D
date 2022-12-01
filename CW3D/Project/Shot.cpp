#include "Shot.h"

using namespace Sample;



Sample::CShot::CShot()
	: m_Collider(std::make_shared<CAttackCollider>())
	, m_Position(0, 0, 0)
	, m_AABB()
	, m_Radius(0.0f)
	, m_ShowFlg(false)
	, m_CollideFlg(false)
	, m_Type(CHARA_PLAYER)
	, m_Speed(0.0f)
	, m_KnockBack(0, 0, 0)
	, m_Offset(0, 0, 0)
	, m_Damage(0)
	, m_NextHitTime(0.0f)
	, m_CollisionType(COLLISION_AABB)
	, m_ArmorBreakLevel(0)
	, m_GetUltGauge(0.0f)
	, m_ParentID(0)

{
}

Sample::CShot::~CShot()
{
}

void Sample::CShot::Create(Vector3 pos, ShotSphere sphire)
{
	m_Position = pos;
	m_Offset = sphire.offset;
	m_Radius = sphire.Radius;
	m_Type = sphire.type;
	m_Damage = sphire.damage;
	m_NextHitTime = sphire.nextHitTime;
	m_Speed = 0.0f;
	m_Collider->SetPosition(m_Position);
	m_Collider->SetRadius(m_Radius);
	m_ShowFlg = true;
	m_CollideFlg = sphire.collideFlg;
	m_CollisionType = COLLISION_SPHERE;
	m_KnockBack = sphire.knockBack;
	m_Direction = sphire.direction;
	m_ArmorBreakLevel = sphire.armorBreakLevel;
	m_GetUltGauge = sphire.getUltGauge;
	m_ParentID = sphire.parentID;
}

void Sample::CShot::Create(Vector3 pos, ShotAABB aabb)
{
	m_Size = aabb.size;
	m_Position = pos;
	m_Offset = aabb.offset;
	m_Type = aabb.type;
	m_Damage = aabb.damage;
	m_NextHitTime = aabb.nextHitTime;
	m_Speed = 0.0f;
	m_AABB.SetPosition(m_Position);
	m_AABB.Size = m_Size;
	m_ShowFlg = true;
	m_CollideFlg = aabb.collideFlg;
	m_CollisionType = COLLISION_AABB;
	m_KnockBack = aabb.knockBack;
	m_Direction = aabb.direction;
	m_ArmorBreakLevel = aabb.armorBreakLevel;
	m_GetUltGauge = aabb.getUltGauge;
	m_ParentID = aabb.parentID;
}

void Sample::CShot::Update()
{
	if (!m_ShowFlg)
	{
		return;
	}

	m_Position.x += m_Speed * TimeScaleControllerInstance.GetTimeScale(m_Type);
	switch (m_CollisionType)
	{
	case COLLISION_SPHERE:
	{
		m_Collider->SetPosition(m_Position);
		break;
	}
	case COLLISION_AABB:
	{
		m_AABB.SetPosition(m_Position);
		break;
	}
	default:
	{
		break;
	}
	}
	UpdateTime();
	DeleteHitId();
}

void Sample::CShot::Render()
{
	if (!m_ShowFlg)
	{
		return;
	}
}


void Sample::CShot::UpdateTime()
{
	for (auto& id : m_HitIDs)
	{
		if (id.Time > 0.0f)
		{
			id.Time -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(m_Type);
		}
	}
}