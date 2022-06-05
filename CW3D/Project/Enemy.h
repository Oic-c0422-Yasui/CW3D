#pragma once
#include "GameDefine.h"
#include	"InputManager.h"
#include	"ResourceManager.h"
#include	"AttackCollider.h"
#include	"ReactiveParameter.h"
#include	"ParameterHandle.h"
#include	"Observer.h"

#include	"ActorObject.h"

class CEnemy : public Sample::CActorObject
{
protected:


	Sample::InputPtr m_Input;


	Sample::AttackColliderPtr m_Collider;


	bool	m_DeadFlg;

	Sample::ParameterHandle< Sample::ReactiveParameter<int> > m_HP;
	Sample::ParameterHandle< Sample::ReactiveParameter<Vector3> > m_Position;
	Sample::ParameterHandle< Sample::ReactiveParameter<bool> > m_HPShowFlg;

public:
	CEnemy();
	~CEnemy() override;
	bool Load();
	void Initialize(CVector3 pos);
	void Update() override;
	void Render() override;
	void RenderDebug();
	void Render2D();
	void Render2DDebug();
	void Release() override;

	void Damage(const Vector3& direction,Vector3 power, int damage);

	bool IsInvincible() const;

	CSphere GetCollider() {
		m_Collider->SetPosition(m_Position.Get() + Vector3(0, 0.7f, 0));
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
		return m_Position.Get();
	}

	/**
	 * @brief		HP�ω��ʒm
	 */
	Sample::IObservable<int>* GetHPSubject() { return &(m_HP.Get()); }

	/**
	 * @brief		���W�ω��ʒm
	 */
	Sample::IObservable<Vector3>* GetPositionSubject() { return &(m_Position.Get()); }

	/**
	 * @brief		�\���ω��ʒm
	 */
	Sample::IObservable<bool>* GetShowSubject() { return &(m_HPShowFlg.Get()); }

	int GetHP()
	{
		return m_HP.Get();
	}

	void SetPosition(Vector3 pos)
	{
		m_Actor->SetPosition(pos);
		m_Position = m_Actor->GetPosition();
	}

	unsigned int GetID() const
	{
		return m_Actor->GetID();
	}
	

};

