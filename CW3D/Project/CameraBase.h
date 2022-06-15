#pragma once
#include "GameDefine.h"
class CCameraBase
{
protected:
	CCamera m_Camera;
	CVector3 m_OffsetPos;
	CVector3 m_OffsetLookPos;
	CVector3 m_LookPos;
	CVector3 m_Position;
	CVector3 m_TargetPos;
	CVector3 m_TargetLookPos;

public:
	CCameraBase();
	virtual ~CCameraBase() {};
	virtual void Create();
	virtual void Update(const Vector3& pos, const Vector3& lookPos) = 0;
	virtual void UpdateCamera();
	virtual void Render2DDebug();

	const CVector3& GetPos() const noexcept
	{
		return m_Position;
	}
	const CVector3& GetLookPos() const noexcept
	{
		return m_LookPos;
	}
	const CVector3& GetTargetPos() const noexcept
	{
		return m_TargetPos;
	}
	const CVector3& GetTargetLookPos() const noexcept
	{
		return m_TargetLookPos;
	}
	const CVector3& GetOffsetPos() const noexcept
	{
		return m_OffsetPos;
	}
	const CVector3& GetOffsetLookPos() const noexcept
	{
		return m_OffsetLookPos;
	}
	CCamera& GetCamera()
	{
		return m_Camera;
	}

	void SetPos(const Vector3& pos) noexcept
	{
		m_Position = pos;
	}
	void SetLookPos(const Vector3& pos) noexcept
	{
		m_LookPos = pos;
	}
	void SetTargetPos(const Vector3& pos) noexcept
	{
		m_TargetPos = pos;
	}
	void SetTargetLookPos(const Vector3& pos) noexcept
	{
		m_TargetLookPos = pos;
	}
	void SetOffsetPos(const Vector3& pos) noexcept
	{
		m_OffsetPos = pos;
	}
	void SetOffsetLookPos(const Vector3& pos) noexcept
	{
		m_OffsetLookPos = pos;
	}

};

using CameraPtr = std::shared_ptr<CCameraBase>;
