#include "Player.h"
#include "AdditionalSkill.h"
#include "UltimateSkill.h"



CPlayer::CPlayer():
	Sample::CActorObject(),
	m_pInput()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Load()
{
	m_pMesh = Sample::ResourceManager<CMeshContainer>::GetInstance().GetResource("Player");

	if (m_pMesh == nullptr)
	{
		return false;
	}

	m_Motion = m_pMesh->CreateMotionController();
	m_Actor->SetAnimationState(m_Motion);

	m_StateMachine = std::make_shared<Sample::StateMachine>();


	m_ActionCreator.Create(m_Actor);
	m_StateCreator.Create(m_StateMachine, m_Actor, m_pInput);

	m_Actor->GetParameterMap()->Add<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP, 800);
	m_Actor->GetParameterMap()->Add<Sample::ReactiveParameter<int>>(PARAMETER_KEY_MAXHP, 800);
	m_Actor->GetParameterMap()->Add<int>(PARAMETER_KEY_DAMAGE, 0);
	m_Actor->GetParameterMap()->Add<int>(PARAMETER_KEY_ATTACK, 25);
	m_Actor->GetParameterMap()->Add<float>(PARAMETER_KEY_INVINCIBLE, 0.0f);

	m_HP = m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	m_MaxHP = m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_MAXHP);
	Sample::SKillPtr skill;

	

	Sample::SKillPtr additionalSkill = std::make_shared<Sample::CAdditionalSkill>();
	skill = m_Actor->GetSkillController()->Create(SKILL_KEY_1, INPUT_KEY_SKILL2, STATE_KEY_SKILL2_1, STATE_KEY_JUMPSKILL2_1, additionalSkill);
	Sample::CSkillData skillData;
	skillData.SetData(180, 3, 0.8f, 0);
	skill->SetSkillData(skillData);

	skill = m_Actor->GetSkillController()->Create(SKILL_KEY_2, INPUT_KEY_SKILL3, STATE_KEY_SKILL3_1, STATE_KEY_JUMPSKILL3_1);
	skill->SetSkillData(125, 5);

	Sample::SKillPtr ultSkill = std::make_shared<Sample::CUltimateSkill>();
	skill = m_Actor->GetSkillController()->Create(SKILL_KEY_3, INPUT_KEY_SKILL1, STATE_KEY_SKILL1_1, STATE_KEY_SKILL1_1);
	//skillData.SetData()
	skill->SetSkillData(550, 8);

	skill = m_Actor->GetSkillController()->Create(SKILL_KEY_ESCAPE, INPUT_KEY_ESCAPE, STATE_KEY_ESCAPE, STATE_KEY_ESCAPE);
	skill->SetCT(1);

	return true;
}

void CPlayer::Initialize()
{
	m_ShowFlg = true;
	m_Actor->SetPosition(Vector3(0, 0,0));
	m_Actor->SetRotate(Vector3(0, 0, 0));
	m_Actor->SetScale(Vector3(1, 1, 1));
	m_ColliderSize.x = 0.5f;
	m_ColliderSize.y = 0.8f;
	m_ColliderSize.z = 0.5f;
	m_ColliderOffset.y = 1.0f;

	m_StateMachine->ChangeState(STATE_KEY_IDLE);

	matWorld = m_Actor->GetMatrix();
	SetType(CHARA_PLAYER);
}

void CPlayer::Update()
{
	if (!m_ShowFlg)
	{
		return;
	}
	Sample::CActorObject::Update();
}

void CPlayer::Render()
{
	if (!m_ShowFlg)
	{
		return;
	}
	Sample::CActorObject::Render();
}

void CPlayer::Release()
{
	Sample::CActorObject::Release();
}

void CPlayer::Damage(const Vector3& direction, Vector3 power, int damage,BYTE level)
{
	Sample::EffectCreateParameter param = { "DamageEffect1", Vector3(0, 1.0f, 0) , Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f),1.0f };
	Sample::EffectPtr effect = EffectControllerInstance.Play(param.name, GetCollider().Position, param);

	auto& hp = m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	auto& knockBack = m_Actor->GetParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);

	auto& transform = m_Actor->GetTransform();
	transform->SetReverse(direction.x > 0 ? true : false);

	hp -= damage;
	if (hp <= 0)
	{
		hp = 0;

		m_DeadFlg = true;
	}
	m_HP = hp;
	if (m_Actor->GetArmorLevel() <= level)
	{
		knockBack = direction * power;

		m_StateMachine->ChangeState(STATE_KEY_DAMAGE);
	}

}
