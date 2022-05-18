#pragma once
#include "GameDefine.h"
#include	"InputManager.h"
#include	"ResourceManager.h"
#include	"StateMachine.h"
#include	"MoveAction.h"
#include	"Actor.h"

class CEnemy
{
protected:

	std::shared_ptr<CMeshContainer> m_pMesh;

	

	Sample::StateMachinePtr m_StateMachine;
	Sample::AnimationStatePtr m_Motion;
	Sample::ActorPtr m_Actor;
	Sample::InputPtr m_Input;

	CMatrix44 matWorld;

public:
	CEnemy();
	~CEnemy();
	bool Load();
	void Initialize(CVector3 pos);
	void Update();
	void Render();
	void RenderDebug();
	void Release();

};

