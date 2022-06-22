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

	int						m_HP;


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

	void Damage(const Vector3& direction, Vector3 power, int damage);

	/**
	 * @brief		CT•Ï‰»’Ê’m
	 */
	Sample::IObservable<float>* GetCTSubject(int id) { return &(GetSkillController()->GetSkill(id)->GetTimeParam().Get()); }
	Sample::IObservable<float>* GetMaxCTSubject(int id) { return &(GetSkillController()->GetSkill(id)->GetCTParam().Get()); }

	Sample::SkillControllerPtr GetSkillController()
	{
		return m_Actor->GetSkillController();
	}
	/*CAABB GetCollider{
		return m_Collider
	}*/
};

using PlayerPtr = std::shared_ptr<CPlayer>;