#pragma once
#include "GameDefine.h"
#include	"InputManager.h"
#include	"ResourceManager.h"
#include	"StateMachine.h"
#include	"MoveAction.h"
#include	"Actor.h"
#include	"AttackCollider.h"
#include	"EnemyHPUI.h"

class CEnemy
{
protected:

	std::shared_ptr<CMeshContainer> m_pMesh;

	

	Sample::StateMachinePtr m_StateMachine;
	Sample::AnimationStatePtr m_Motion;
	Sample::ActorPtr m_Actor;
	Sample::InputPtr m_Input;


	CMatrix44 matWorld;

	Sample::AttackColliderPtr m_Collider;

	bool	m_ShowFlg;

	bool	m_DeadFlg;

	Sample::EnemyHPUI m_HPUI;

public:
	CEnemy();
	~CEnemy();
	bool Load();
	void Initialize(CVector3 pos);
	void Update();
	void Render();
	void RenderDebug();
	void Render2D();
	void Render2DDebug();
	void Release();

	void Damage(const Vector3& direction,Vector3 power, int damage);

	bool IsInvincible() const;

	CSphere GetCollider() {
		m_Collider->SetPosition(m_Actor->GetPosition() + Vector3(0, 0.7f, 0));
		return m_Collider->GetCollider(); }

	float GetSize()
	{
		return m_Collider->GetRadius();
	}

	bool IsShow()
	{
		return m_ShowFlg;
	}

	void SetShow(bool isShow)
	{
		m_ShowFlg = isShow;
	}

	Vector3 GetPosition()
	{
		return m_Actor->GetPosition();
	}

	int GetHP()
	{
		return m_Actor->GetParameterMap()->Get<int>(PARAMETER_KEY_HP);
	}
	int GetMaxHP()
	{
		return m_Actor->GetParameterMap()->Get<int>(PARAMETER_KEY_MAXHP);
	}

	void SetPosition(Vector3 pos)
	{
		m_Actor->SetPosition(pos);
	}

	unsigned int GetID() const
	{
		return m_Actor->GetID();
	}
	

};

