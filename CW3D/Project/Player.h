#pragma once
#include "GameDefine.h"
#include	"InputManager.h"
#include	"ResourceManager.h"
#include	"PlayerStatus.h"



class CPlayer : public CPlayerStatus
{
private:
	CVector3	m_Position;
	CVector3	m_Velocity;
	CVector3	m_Rotation;
	CVector3	m_Scale;
	CMeshContainer*		m_pMesh;
	bool		m_HorizontalMoveFlg;
	bool		m_VerticalMoveFlg;
	bool		m_ReverseFlg;

#define TEMP_SPEED 0.20f

	Sample::InputPtr		m_pInput;
	
	CMatrix44 matWorld;

	void UpdateKey();
	void UpdateMove();
	void SetReverse();

public:
	CPlayer();
	~CPlayer();
	bool Load(CMeshContainer* pMesh);
	void Initialize();
	void Update();
	void Render();
	void Release();

	void SetInput(const Sample::InputPtr& ptr)
	{
		m_pInput = ptr;
	}

	Vector3 GetPosition() { return m_Position; }
};

