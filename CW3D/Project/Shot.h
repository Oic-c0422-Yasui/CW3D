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
		int					m_Type;

	public:
		CShot()
			:m_Collider(std::make_shared<CAttackCollider>())
			,m_Position(0,0,0)
			, m_Radius(0.0f)
			, m_ShowFlg(false)
			, m_Type(0)

		{
		}

		void Create(Vector3 pos, float radius, int type)
		{
			m_Position = pos;
			m_Radius = radius;
			m_Type = type;
			m_Collider->SetPosition(m_Position);
			m_Collider->SetRadius(m_Radius);
			m_ShowFlg = true;
		}

		void Update()
		{
			if (!m_ShowFlg)
			{
				return;
			}

		}


		bool IsShow() const noexcept {
			return m_ShowFlg;
		}


	};

	//ポインタ置き換え
	using ShotPtr = std::shared_ptr<CShot>;
}


