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
		virtual ~CObject();
		virtual bool Load();
		virtual void Initialize();
		virtual void Update();
		virtual void Render();
		virtual void Release();

		CAABB GetCollider()
		{			
			return CAABB(m_Position + m_Offset, m_Size);
		}
		const Vector3& GetPosition()
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

