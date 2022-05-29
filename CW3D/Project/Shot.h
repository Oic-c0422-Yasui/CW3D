#pragma once

#include "AttackCollider.h"
#include "GameDefine.h"

namespace Sample
{
	class CShot
	{
	protected:
		AttackColliderPtr	m_Collider;
		CAABB				m_AABB;
		CVector3			m_Position;
		float				m_Radius;
		CVector3			m_Size;
		Vector3				m_Offset;
		bool				m_ShowFlg;
		bool				m_CollideFlg;
		BYTE				m_Type;
		int					m_CollisionType;
		float				m_Speed;
		CVector3			m_KnockBack;

	public:
		CShot()
			:m_Collider(std::make_shared<CAttackCollider>())
			, m_Position(0,0,0)
			, m_AABB()
			, m_Radius(0.0f)
			, m_ShowFlg(false)
			, m_CollideFlg(false)
			, m_Type(0)
			, m_Speed(0.0f)
			, m_KnockBack(0,0,0)
			, m_Offset(0,0,0)

		{
		}

		~CShot() {

		}

		void Create(Vector3 pos,Vector3 offset, float radius, int type)
		{
			m_Position = pos;
			m_Offset = offset;
			m_Radius = radius;
			m_Type = type;
			m_Speed = 0.0f;
			m_Collider->SetPosition(m_Position);
			m_Collider->SetRadius(m_Radius);
			m_ShowFlg = true;
			m_CollideFlg = true;
			m_CollisionType = COLLITION_SPHERE;
			m_KnockBack = Vector3(0, 0, 0);
		}

		void Create(Vector3 pos, Vector3 offset, Vector3 size, int type)
		{
			m_Size = size;
			m_Position = pos;
			m_Offset = offset;
			m_Type = type;
			m_Speed = 0.0f;
			m_AABB.SetPosition(m_Position);
			m_AABB.Size = size;
			m_ShowFlg = true;
			m_CollideFlg = true;
			m_CollisionType = COLLITION_AABB;
			m_KnockBack = Vector3(0, 0, 0);
		}

		void Update()
		{
			if (!m_ShowFlg)
			{
				return;
			}
			m_Position.x += m_Speed;
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

	};

	//ポインタ置き換え
	using ShotPtr = std::shared_ptr<CShot>;
}


