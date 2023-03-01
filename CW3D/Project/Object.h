#pragma once
#include "Common.h"

namespace ActionGame
{
	class CObject
	{
	protected:
		CVector3 position_;
		CVector3 size_;
		CVector3 offset_;
		bool	 isShow_;
	public:
		CObject(const Vector3& pos, const Vector3& size, const Vector3& offset);
		virtual ~CObject() = default;
		virtual void Initialize();
		virtual void Update() = 0;

		CAABB GetCollider()
		{			
			return CAABB(position_ + offset_, size_);
		}
		const Vector3& GetPosition() const noexcept
		{
			return position_;
		}

		bool IsShow() const noexcept
		{
			return isShow_;
		}

		void SetShow(bool isShow) noexcept
		{
			isShow_ = isShow;
		}



	};
	using ObjectPtr = std::shared_ptr<CObject>;
}


