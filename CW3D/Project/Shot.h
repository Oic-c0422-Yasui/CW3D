#pragma once

#include "AttackCollider.h"
#include "GameDefine.h"
#include	"KnockBack.h"
#include "TimeController.h"

namespace Sample
{
	struct ShotCreateParameter {
		Vector3 offset;
		float	nextHitTime;
		int		damage;
		Vector3	knockBack;
		bool	collideFlg;
		CHARACTER_TYPE type;
		KnockBackPtr direction;
		BYTE armorBreakLevel;
		float getUltGauge;
		unsigned int parentID;
	};
	struct ShotSphere : public ShotCreateParameter {
		float Radius;
	};
	struct ShotAABB : public ShotCreateParameter{
		Vector3 size;
	};
	class CShot
	{
	protected:
		struct Hit
		{
			unsigned int ID;
			float Time;
		};

		AttackColliderPtr	m_Collider;
		CAABB				m_AABB;
		CVector3			m_Position;
		float				m_Radius;
		CVector3			m_Size;
		Vector3				m_Offset;
		bool				m_ShowFlg;
		bool				m_CollideFlg;
		CHARACTER_TYPE		m_Type;
		int					m_CollisionType;
		float				m_Speed;
		CVector3			m_KnockBack;
		int					m_Damage;
		std::list<Hit>		m_HitIDs;
		float				m_NextHitTime;
		KnockBackPtr		m_Direction;
		BYTE				m_ArmorBreakLevel;
		float				m_GetUltGauge;
		unsigned int		m_ParentID;


	public:
		CShot()
			:m_Collider(std::make_shared<CAttackCollider>())
			, m_Position(0,0,0)
			, m_AABB()
			, m_Radius(0.0f)
			, m_ShowFlg(false)
			, m_CollideFlg(false)
			, m_Type()
			, m_Speed(0.0f)
			, m_KnockBack(0,0,0)
			, m_Offset(0,0,0)
			, m_Damage(0)
			, m_NextHitTime(0.0f)
			, m_CollisionType(COLLITION_AABB)
			, m_ArmorBreakLevel(0)
			, m_GetUltGauge(0.0f)
			, m_ParentID(0)

		{
		}

		~CShot() {

		}

		void Create(Vector3 pos, ShotSphere sphire)
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
			m_CollisionType = COLLITION_SPHERE;
			m_KnockBack = sphire.knockBack;
			m_Direction = sphire.direction;
			m_ArmorBreakLevel = sphire.armorBreakLevel;
			m_GetUltGauge = sphire.getUltGauge;
			m_ParentID = sphire.parentID;
		}

		void Create(Vector3 pos, ShotAABB aabb)
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
			m_CollisionType = COLLITION_AABB;
			m_KnockBack = aabb.knockBack;
			m_Direction = aabb.direction;
			m_ArmorBreakLevel = aabb.armorBreakLevel;
			m_GetUltGauge = aabb.getUltGauge;
			m_ParentID = aabb.parentID;
		}

		void Update()
		{
			if (!m_ShowFlg)
			{
				return;
			}
			
			m_Position.x += m_Speed * TimeControllerInstance.GetTimeScale(m_Type);
			switch (m_CollisionType)
			{
				case COLLITION_SPHERE:
				{
					m_Collider->SetPosition(m_Position);
					break;
				}
				case COLLITION_AABB:
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

		void Render()
		{
			if (!m_ShowFlg)
			{
				return;
			}
		}


		bool IsShow() const noexcept {
			return m_ShowFlg;
		}

		bool GetCollideFlg() const noexcept {
			return m_CollideFlg;
		}

		int GetColliderType() const noexcept {
			return m_CollisionType;
		}

		float GetNextHitTime() const noexcept
		{
			return m_NextHitTime;
		}

		CHARACTER_TYPE GetCharaType() const noexcept
		{
			return m_Type;
		}

		float GetGetUltGauge() const noexcept
		{
			return m_GetUltGauge;
		}

		unsigned int GetParentID() const noexcept
		{
			return m_ParentID;
		}

		void SetCharaType(CHARACTER_TYPE type) noexcept
		{
			m_Type = type;
		}

		void SetShow(bool isShow) noexcept
		{
			m_ShowFlg = isShow;
		}

		void SetCollideFlg(bool flg) noexcept
		{
			m_CollideFlg = flg;
		}

		void SetKnockBack(Vector3 val) noexcept
		{
			m_KnockBack = val;
		}
		void SetKnockBackX(float val) noexcept
		{
			m_KnockBack.x = val;
		}
		void SetKnockBackY(float val) noexcept
		{
			m_KnockBack.y = val;
		}
		void SetKnockBackZ(float val) noexcept
		{
			m_KnockBack.z = val;
		}

		void SetDamage(int val) noexcept
		{
			m_Damage = val;
		}

		void AddDamage(int val) noexcept
		{
			m_Damage += val;
		}

		void SetNextHitTime(float val) noexcept
		{
			m_NextHitTime = val;
		}

		void SetSpeed(float val) noexcept
		{
			m_Speed = val;
		}

		void SetPosition(Vector3 pos) noexcept
		{
			m_Position = pos;
		}

		void SetOffset(Vector3 offset) noexcept
		{
			m_Offset = offset;
		}

		void SetDirection(KnockBackPtr dir) noexcept
		{
			m_Direction = dir;
		}

		void SetArmorBreakLevel(BYTE level) noexcept
		{
			m_ArmorBreakLevel = level;
		}

		void SetGetUltGauge(float gauge) noexcept
		{
			m_GetUltGauge = gauge;
		}

		void SetParentID(unsigned int id)noexcept
		{
			m_ParentID = id;
		}

		KnockBackPtr GetDirection() const noexcept
		{
			return m_Direction;
		}

		void AddPosition(Vector3 pos) noexcept
		{
			m_Position += pos;
		}

		Vector3 GetPosition() const noexcept {
			return m_Position;
		}

		Vector3 GetOffset() const noexcept {
			return m_Offset;
		}

		float GetRadius() const noexcept {
			return m_Radius;
		}

		CSphere GetColliderSphere() const noexcept {
			return m_Collider->GetCollider();
		}

		CAABB GetColliderAABB() const noexcept {
				return m_AABB;
		}


		Vector3 GetKnockBack() const noexcept {
			return m_KnockBack;
		}

		float GetSpeed() const noexcept {
			return m_Speed;
		}

		int GetDamage() const noexcept {
			return m_Damage;
		}

		const BYTE& GetArmorBreakLevel() const noexcept{
			return m_ArmorBreakLevel;
		}

		bool IsHitId(unsigned int hitId)
		{
			for (auto& id : m_HitIDs)
			{
				if (id.ID == hitId)
				{
					return true;
				}
			}
			return false;
		}

		void UpdateTime()
		{
			for (auto& id : m_HitIDs)
			{
				if (id.Time > 0.0f)
				{
					id.Time -= CUtilities::GetFrameSecond() * TimeControllerInstance.GetTimeScale(m_Type);
				}
			}
		}

		void AddHit(unsigned int hitId)
		{

			Hit hit = { hitId, m_NextHitTime };
			m_HitIDs.push_back(hit);
		}

		void DeleteHitId()
		{
			auto removeIt = std::remove_if(m_HitIDs.begin(), m_HitIDs.end(), [&](const Hit& id) {
				return id.Time <= 0.0f; });
			m_HitIDs.erase(removeIt, m_HitIDs.end());
		}

	};

	//ポインタ置き換え
	using ShotPtr = std::shared_ptr<CShot>;
}


