#pragma once

#include "AttackCollider.h"

namespace Sample
{
	class CShot
	{
	protected:
		AttackColliderPtr	m_Collider;
		CVector3			m_Position;
		float				m_Radius;
		bool				m_ShowFlg;
		bool				m_CollideFlg;
		int					m_Type;
		float				m_Speed;
		float				m_KnockBack;

	public:
		CShot()
			:m_Collider(std::make_shared<CAttackCollider>())
			,m_Position(0,0,0)
			, m_Radius(0.0f)
			, m_ShowFlg(false)
			, m_CollideFlg(false)
			, m_Type(0)
			, m_Speed(0.0f)
			, m_KnockBack(0.0f)

		{
		}

		void Create(Vector3 pos, float radius, int type)
		{
			m_Position = pos;
			m_Radius = radius;
			m_Type = type;
			m_Speed = 0.0f;
			m_Collider->SetPosition(m_Position);
			m_Collider->SetRadius(m_Radius);
			m_ShowFlg = true;
			m_CollideFlg = true;
			m_KnockBack = 0.0f;
		}

		void Update()
		{
			if (!m_ShowFlg)
			{
				return;
			}
			m_Position.x += m_Speed;
			m_Collider->SetPosition(m_Position);
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

		void SetShow(bool isShow) noexcept
		{
			m_ShowFlg = isShow;
		}

		void SetCollideFlg(bool flg) noexcept
		{
			m_CollideFlg = flg;
		}

		void SetKnockBack(float val) noexcept
		{
			m_KnockBack = val;
		}

		void SetSpeed(float val) noexcept
		{
			m_Speed = val;
		}

		void AddPosition(Vector3 pos) noexcept
		{
			m_Position += pos;
		}

		Vector3 GetPosition() const noexcept {
			return m_Position;
		}

		float GetRadius() const noexcept {
			return m_Radius;
		}

		CSphere GetCollider() const noexcept {
			return m_Collider->GetCollider(); 
		}

		float GetKnockBack() const noexcept {
			return m_KnockBack;
		}

		float GetSpeed() const noexcept {
			return m_Speed;
		}

	};

	//ポインタ置き換え
	using ShotPtr = std::shared_ptr<CShot>;
}


