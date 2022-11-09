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

	//�C���v�b�g�L�[
	Sample::InputPtr		m_pInput;

	//�I�u�U�[�o�[�ő�HP
	Sample::ParameterHandle< Sample::ReactiveParameter<int> > m_MaxHP;

	//�I�u�U�[�o�[�ő�K�E�Z�Q�[�W
	Sample::ParameterHandle< Sample::ReactiveParameter<float> > m_MaxUltGauge;

	//�A�N�V��������
	Sample::PlayerActionCreator m_ActionCreator;
	//��Ԑ���
	Sample::PlayerStateCreator m_StateCreator;
	//�X�L������
	Sample::PlayerSkillCreator m_SkillCreator;
	//�p�����[�^����
	Sample::PlayerParameterCreator m_ParameterCreator;

	//������̓����蔻��T�C�Y
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
	* @bref �_���[�W����
	* 
	*/
	void Damage(const Vector3& direction, const Vector3& power, int damage, BYTE level);
	
	/*
	* @bref �C���v�b�g�L�[�̐ݒ�
	*
	*/
	void SetInput(const Sample::InputPtr& ptr) noexcept
	{
		m_pInput = ptr;
	}

	/*
	* @bref HP�̎擾
	* @return HP
	*
	*/
	int GetHP() const noexcept
	{
		return m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	}


	/**
	* @brief		HP�ω��ʒm
	*/
	Sample::IObservable<int>& GetHPSubject() { return  m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP); }
	Sample::IObservable<int>* GetMaxHPSubject() { return &(m_MaxHP.Get()); }

	//�X�L���擾

	
	const Sample::SKillPtr& GetSkill(int id) const noexcept {
		return GetSkillController()->GetSkill(id);
	}
	template< typename T >
	const std::shared_ptr<T> GetSkillT(int id) const noexcept {
		auto& skill = GetSkillController()->GetSkill(id);
		return  std::dynamic_pointer_cast<T>(skill);
	}
	//�K�E�Z�Q�[�W
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