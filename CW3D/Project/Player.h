#pragma once
#include "GameDefine.h"
#include	"InputManager.h"
#include	"ResourceManager.h"
#include	"PlayerStatus.h"
#include	"StateMachine.h"
#include	"MoveAction.h"
#include	"Actor.h"


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

	Sample::StateMachinePtr m_StateMachine;
	Sample::AnimationStatePtr m_Motion;
	Sample::ActorPtr m_Actor;
	Sample::MoveActionPtr m_Move;
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


	Vector3 GetPosition() { return m_Actor->GetPosition(); }
};

