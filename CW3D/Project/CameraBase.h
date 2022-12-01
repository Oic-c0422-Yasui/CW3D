#pragma once
#include "GameDefine.h"
class CCameraBase
{
protected:
	CCamera		m_Camera;
	CVector3	m_OffsetPos;
	CVector3	m_OffsetLookPos;
	CVector3	m_LookPos;
	CVector3	m_Position;
	CVector3	m_TargetPos;
	CVector3	m_TargetLookPos;
	bool		m_AnimEndFlg;
	bool		m_ResetFlg;

	//アニメーション用構造体
	struct animData
	{
		MyUtilities::ANIM_V3_DATA_ARRAY Pos;
		MyUtilities::ANIM_V3_DATA_ARRAY LookPos;

		bool		Flg;
		float		CurrentTime;
		int			Count;

		animData()
			: Pos()
			, LookPos()
			, Flg(false)
			, CurrentTime(0.0f)
			, Count(0)
		{
		}
		void Release()
		{
			Pos.clear();
			LookPos.clear();
		}
	};
	animData m_AnimData;

public:
	CCameraBase(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos);
	virtual ~CCameraBase() {};
	virtual void Create();
	virtual void Update(const Vector3& pos, const Vector3& lookPos) = 0;
	virtual void UpdateCamera();
	virtual void Render2DDebug();
	virtual void Enable(const Vector3& pos, const Vector3& lookPos);
	virtual void SetAnim(const MyUtilities::ANIM_V3_DATA_ARRAY& offsetPos, const MyUtilities::ANIM_V3_DATA_ARRAY& offsetLookPos);

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
	CCamera& GetCamera() noexcept
	{
		return m_Camera;
	}
	bool IsEnd() const noexcept
	{
		return m_AnimEndFlg;
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
	void SetEndAnimFlg(bool isEnd) noexcept
	{
		m_AnimEndFlg = isEnd;
	}
	void SetResetFlg(bool isReset) noexcept
	{
		m_ResetFlg = isReset; 
	}
};

using CameraPtr = std::shared_ptr<CCameraBase>;
