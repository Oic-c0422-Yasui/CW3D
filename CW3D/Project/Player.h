#pragma once
#include "GameDefine.h"
#include	"InputManager.h"
#include	"ResourceManager.h"
#include	"ReactiveParameter.h"
#include	"ParameterHandle.h"
#include	"ActorObject.h"
#include	"Observer.h"
#include	"PlayerActionCreator.h"
#include	"PlayerStateCreator.h"

class CPlayer : public Sample::CActorObject
{
private:


#define TEMP_SPEED 0.20f

	Sample::InputPtr		m_pInput;

	Sample::ParameterHandle< Sample::ReactiveParameter<int> > m_HP;
	Sample::ParameterHandle< Sample::ReactiveParameter<int> > m_MaxHP;
	Sample::ParameterHandle< Sample::ReactiveParameter<float> > m_UltGauge;
	Sample::ParameterHandle< Sample::ReactiveParameter<float> > m_UltMaxGauge;

	Sample::PlayerActionCreator m_ActionCreator;
	Sample::PlayerStateCreator m_StateCreator;

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

	void Damage(const Vector3& direction, Vector3 power, int damage, BYTE level);

	int GetHP()
	{
		return m_HP.Get();
	}

	/**
	* @brief		HPïœâªí ím
	*/
	Sample::IObservable<int>* GetHPSubject() { return &(m_HP.Get()); }
	Sample::IObservable<int>* GetMaxHPSubject() { return &(m_MaxHP.Get()); }
	/**
	 * @brief		CTïœâªí ím
	 */
	Sample::IObservable<float>* GetCTSubject(int id) { return &(GetSkillController()->GetSkill(id)->GetTimeParam().Get()); }
	Sample::IObservable<float>* GetMaxCTSubject(int id) { return &(GetSkillController()->GetSkill(id)->GetCTParam().Get()); }
	//ïKéEãZÉQÅ[ÉW
	Sample::IObservable<float>* GetMaxUltSubject() { return &(m_UltMaxGauge.Get()); }
	Sample::IObservable<float>* GetUltSubject() { return &(m_UltGauge.Get()); }

	Sample::SkillControllerPtr GetSkillController()
	{
		return m_Actor->GetSkillController();
	}
	/*CAABB GetCollider{
		return m_Collider
	}*/
};

using PlayerPtr = std::shared_ptr<CPlayer>;