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
	std::shared_ptr<CMeshContainer>		m_pMesh;

	


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

	CAABB m_Collider;



public:
	CPlayer();
	~CPlayer();
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void Release();

	void SetInput(const Sample::InputPtr& ptr)
	{
		m_pInput = ptr;
	}

	

	/*CAABB GetCollider{
		return m_Collider
	}*/

	Vector3 GetPosition() { return m_Actor->GetPosition(); }
	Vector3 GetVelocity() { return m_Actor->GetVelocity()->GetVelocity(); }
	bool IsReverse() { return m_Actor->IsReverse(); }
	Vector3 GetRotate() { return m_Actor->GetRotate(); }
};

