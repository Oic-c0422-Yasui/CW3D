#pragma once

#include "AttackCollider.h"
#include "GameDefine.h"
#include	"KnockBack.h"
#include "TimeScaleController.h"

namespace ActionGame
{
	//ショットパラメーター
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
	//球体ショット
	struct ShotSphere : public ShotCreateParameter {
		float Radius;
	};
	//立方体ショット
	struct ShotAABB : public ShotCreateParameter{
		Vector3 size;
	};
	class CShot
	{
	protected:

		//ヒット判定用構造体
		struct Hit
		{
			unsigned int ID;
			float Time;
		};
		std::list<Hit>		m_HitIDs;

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
		float				m_NextHitTime;
		KnockBackPtr		m_Direction;
		BYTE				m_ArmorBreakLevel;
		float				m_GetUltGauge;
		unsigned int		m_ParentID;

	private:
		//削除時間までタイマーを進める
		void UpdateTime();
	public:
		CShot();
		~CShot();

		//球体の当たり判定作成
		void Create(Vector3 pos, ShotSphere sphire);
		
		//立方体の当たり判定作成
		void Create(Vector3 pos, ShotAABB aabb);
		
		void Update();

		void Render();

		//ヒットした相手のIDを追加
		void AddHit(unsigned int hitId)
		{
			Hit hit = { hitId, m_NextHitTime };
			m_HitIDs.push_back(hit);
		}

		//ヒット判定IDを削除
		void DeleteHitId()
		{
			auto removeIt = std::remove_if(m_HitIDs.begin(), m_HitIDs.end(), [&](const Hit& id) {
				return id.Time <= 0.0f; });
			m_HitIDs.erase(removeIt, m_HitIDs.end());
		}

		void AddDamage(int val) noexcept
		{
			m_Damage += val;
		}

		void AddPosition(const Vector3& pos) noexcept
		{
			m_Position += pos;
		}

		/**
		 * @brief		ゲッター
		 */
		bool IsShow() const noexcept {
			return m_ShowFlg;
		}

		bool GetCollideFlg() const noexcept {
			return m_CollideFlg;
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

		const KnockBackPtr& GetDirection() const noexcept
		{
			return m_Direction;
		}

		const Vector3& GetPosition() const noexcept 
		{
			return m_Position;
		}

		const Vector3& GetOffset() const noexcept 
		{
			return m_Offset;
		}

		float GetRadius() const noexcept 
		{
			return m_Radius;
		}

		const CSphere& GetColliderSphere() const noexcept 
		{
			return m_Collider->GetCollider();
		}

		const CAABB& GetColliderAABB() const noexcept 
		{
				return m_AABB;
		}
		int GetColliderType() const noexcept
		{
			return m_CollisionType;
		}

		const Vector3& GetKnockBack() const noexcept {
			return m_KnockBack;
		}

		float GetSpeed() const noexcept {
			return m_Speed;
		}

		int GetDamage() const noexcept {
			return m_Damage;
		}

		BYTE GetArmorBreakLevel() const noexcept{
			return m_ArmorBreakLevel;
		}

		bool IsHitId(unsigned int hitId) const noexcept
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

		/**
		 * @brief		セッター
		 */
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

		void SetKnockBack(const Vector3& val) noexcept
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

		void SetNextHitTime(float val) noexcept
		{
			m_NextHitTime = val;
		}

		void SetSpeed(float val) noexcept
		{
			m_Speed = val;
		}

		void SetPosition(const Vector3& pos) noexcept
		{
			m_Position = pos;
		}

		void SetOffset(const Vector3& offset) noexcept
		{
			m_Offset = offset;
		}

		void SetDirection(const KnockBackPtr& dir) noexcept
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

		
	};

	//ポインタ置き換え
	using ShotPtr = std::shared_ptr<CShot>;
}


