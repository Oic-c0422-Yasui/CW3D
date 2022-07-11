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
#include	"PlayerSkillCreater.h"
#include	"PlayerParameterCreator.h"

class CPlayer : public Sample::CActorObject
{
private:


#define TEMP_SPEED 0.20f

	Sample::InputPtr		m_pInput;

	Sample::ParameterHandle< Sample::ReactiveParameter<int> > m_MaxHP;

	Sample::ParameterHandle< Sample::ReactiveParameter<float> > m_MaxUltGauge;

	Sample::PlayerActionCreator m_ActionCreator;
	Sample::PlayerStateCreator m_StateCreator;
	Sample::PlayerSkillCreator m_SkillCreator;
	Sample::PlayerParameterCreator m_ParameterCreator;

	CVector3 m_EscapeColliderSize;

public:
	CPlayer();
	~CPlayer() override;
	bool Load();
	void Initialize();
	void Update() override;
	void Render() override;
	void RenderDebug2D();
	void Release()override;

	void SetInput(const Sample::InputPtr& ptr) noexcept
	{
		m_pInput = ptr;
	}

	void Damage(const Vector3& direction, Vector3 power, int damage, BYTE level);

	int GetHP()
	{
		return m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	}


	/**
	* @brief		HPïœâªí ím
	*/
	Sample::IObservable<int>& GetHPSubject() { return  m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP); }
	Sample::IObservable<int>* GetMaxHPSubject() { return &(m_MaxHP.Get()); }
	/**
	 * @brief		CTïœâªí ím
	 */
	Sample::IObservable<float>* GetCTSubject(int id) { return &(GetSkillController()->GetSkill(id)->GetCTParam().Get()); }
	Sample::IObservable<float>* GetMaxCTSubject(int id) { return &(GetSkillController()->GetSkill(id)->GetMaxCTParam().Get()); }
	Sample::IObservable<bool>* GetCanUseSubject(int id) { return &(GetSkillController()->GetSkill(id)->GetCanUseFlgParam().Get()); }
	Sample::IObservable<float>* GetAddCTSubject(int id) { return &(GetSkillController()->GetSkill(id)->GetAddCTParam().Get()); }
	Sample::IObservable<float>* GetAddMaxCTSubject(int id) { return &(GetSkillController()->GetSkill(id)->GetAddMaxCTParam().Get()); }

	//ïKéEãZÉQÅ[ÉW
	Sample::IObservable<float>* GetMaxUltSubject() { return &(m_MaxUltGauge.Get()); }
	Sample::IObservable<float>& GetUltSubject() { return m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE); }
	Sample::IObservable<float>* GetSkillUltSubject(int id) { return &(GetSkillController()->GetSkill(id)->GetUltGaugeParam().Get()); }

	float GetMaxUltGauge()
	{
		return m_MaxUltGauge.Get();
	}

	bool IsEscape()
	{
		return m_Actor->GetParameterMap()->Get<bool>(PARAMETER_KEY_ESCAPE);
	}

	Sample::SkillControllerPtr GetSkillController()
	{
		return m_Actor->GetSkillController();
	}

	bool IsInvincible() const;

	const CAABB& GetCollider() override
	{
		
		m_Collider.Size = m_ColliderSize;
		m_Collider.SetPosition(m_Actor->GetPosition() + m_ColliderOffset);

		return m_Collider;
	}
	
	const CAABB& GetEscapeCollider()
	{
		m_Collider.Size = m_EscapeColliderSize;
		m_Collider.SetPosition(m_Actor->GetPosition() + m_ColliderOffset);
		return m_Collider;
	}

	void SetClearPose();
};

using PlayerPtr = std::shared_ptr<CPlayer>;