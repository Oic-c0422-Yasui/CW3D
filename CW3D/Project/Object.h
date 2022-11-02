#pragma once
#include "GameDefine.h"

namespace Sample
{
	class CObject
	{
	protected:
		CVector3 m_Position;
		CVector3 m_Size;
		CVector3 m_Offset;
		bool	 m_ShowFlg;
	public:
		CObject(const Vector3& pos, const Vector3& size, const Vector3& offset);
		virtual ~CObject() = default;
		virtual void Initialize();

		CAABB GetCollider()
		{			
			return CAABB(m_Position + m_Offset, m_Size);
		}
		const Vector3& GetPosition() const noexcept
		{
			return m_Position;
		}

		bool IsShow() const noexcept
		{
			return m_ShowFlg;
		}

		void SetShow(bool isShow) noexcept
		{
			m_ShowFlg = isShow;
		}



	};
	using ObjectPtr = std::shared_ptr<CObject>;
}


