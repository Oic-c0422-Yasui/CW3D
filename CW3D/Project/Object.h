#pragma once
#include "Common.h"

namespace ActionGame
{
	class CObject
	{
	protected:
		CVector3 position_;
		CVector3 m_Size;
		CVector3 offset_;
		bool	 m_ShowFlg;
	public:
		CObject(const Vector3& pos, const Vector3& size, const Vector3& offset);
		virtual ~CObject() = default;
		virtual void Initialize();
		virtual void Update() = 0;

		CAABB GetCollider()
		{			
			return CAABB(position_ + offset_, m_Size);
		}
		const Vector3& GetPosition() const noexcept
		{
			return position_;
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


