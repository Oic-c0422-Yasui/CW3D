#pragma once
#include "GameDefine.h"
#include	"InputManager.h"
#include	"ResourceManager.h"

#include	"ActorObject.h"
#include	"Observer.h"


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
	/**
	 * @brief		CT•Ï‰»’Ê’m
	 */
	Sample::IObservable<float>* GetCT1Subject() { return &(GetSkillController()->GetSkill(SKILL_KEY_1)->GetTimeParam().Get()); }
	Sample::IObservable<float>* GetCT2Subject() { return &(GetSkillController()->GetSkill(SKILL_KEY_2)->GetTimeParam().Get()); }
	Sample::IObservable<float>* GetCT3Subject() { return &(GetSkillController()->GetSkill(SKILL_KEY_3)->GetTimeParam().Get()); }

	Sample::SkillControllerPtr GetSkillController()
	{
		return m_Actor->GetSkillController();
	}
	/*CAABB GetCollider{
		return m_Collider
	}*/
};

