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

	//インプットキー
	Sample::InputPtr		m_pInput;

	//オブザーバー最大HP
	Sample::ParameterHandle< Sample::ReactiveParameter<int> > m_MaxHP;

	//オブザーバー最大必殺技ゲージ
	Sample::ParameterHandle< Sample::ReactiveParameter<float> > m_MaxUltGauge;

	//アクション生成
	Sample::PlayerActionCreator m_ActionCreator;
	//状態生成
	Sample::PlayerStateCreator m_StateCreator;
	//スキル生成
	Sample::PlayerSkillCreator m_SkillCreator;
	//パラメータ生成
	Sample::PlayerParameterCreator m_ParameterCreator;

	//回避時の当たり判定サイズ
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

	/*
	* @bref ダメージ処理
	* 
	*/
	void Damage(const Vector3& direction, const Vector3& power, int damage, BYTE level);
	
	/*
	* @bref インプットキーの設定
	*
	*/
	void SetInput(const Sample::InputPtr& ptr) noexcept
	{
		m_pInput = ptr;
	}

	/*
	* @bref HPの取得
	* @return HP
	*
	*/
	int GetHP() const noexcept
	{
		return m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	}


	/**
	* @brief		HP変化通知
	*/
	Sample::IObservable<int>& GetHPSubject() { return  m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP); }
	Sample::IObservable<int>* GetMaxHPSubject() { return &(m_MaxHP.Get()); }

	//スキル取得

	
	const Sample::SKillPtr& GetSkill(int id) const noexcept {
		return GetSkillController()->GetSkill(id);
	}
	template< typename T >
	const std::shared_ptr<T> GetSkillT(int id) const noexcept {
		auto& skill = GetSkillController()->GetSkill(id);
		return  std::dynamic_pointer_cast<T>(skill);
	}
	//必殺技ゲージ
	Sample::IObservable<float>* GetMaxUltSubject() { return &(m_MaxUltGauge.Get()); }
	Sample::IObservable<float>& GetUltSubject() { return m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE); }

	

	float GetMaxUltGauge()
	{
		return m_MaxUltGauge.Get();
	}

	bool IsEscape()
	{
		return m_Actor->GetParameterMap()->Get<bool>(PARAMETER_KEY_ESCAPE);
	}

	const Sample::SkillControllerPtr& GetSkillController() const noexcept
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
	
	const CAABB& GetEscapeCollider() noexcept
	{
		m_Collider.Size = m_EscapeColliderSize;
		m_Collider.SetPosition(m_Actor->GetPosition() + m_ColliderOffset);
		return m_Collider;
	}

	void SetClearPose();
};

using PlayerPtr = std::shared_ptr<CPlayer>;