#pragma once
class CPlayerStatus
{
protected:
	
	float m_Speed;
public:
	CPlayerStatus() :
		m_Speed(0.0f)
	{
	}

	virtual ~CPlayerStatus() {};
};

