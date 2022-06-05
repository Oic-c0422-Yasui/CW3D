#pragma once
#include "GameDefine.h"
#include	"InputManager.h"
#include	"ResourceManager.h"

#include	"ActorObject.h"


class CPlayer : public Sample::CActorObject
{
private:


#define TEMP_SPEED 0.20f

	Sample::InputPtr		m_pInput;

public:
	CPlayer();
	~CPlayer() override;
	bool Load();
	void Initialize();
	void Update() override;
	void Render() override;
	void Release()override;

	void SetInput(const Sample::InputPtr& ptr)
	{
		m_pInput = ptr;
	}

	

	/*CAABB GetCollider{
		return m_Collider
	}*/
};

