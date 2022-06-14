#include "Enemy.h"


#include "IdleState.h"
#include "MoveState.h"
#include "RunState.h"
#include "IdleMotionState.h"
#include "Attack1State.h"
#include "DamageState.h"
#include "FlyDamageState.h"
#include "DownState.h"
#include "DeadState.h"
#include "StateInput.h"

using namespace Sample;

CEnemy::CEnemy()
	: Sample::CActorObject()
	,m_Input()
{
}

CEnemy::~CEnemy()
{
	Release();
}

bool CEnemy::Load()
{
	m_Input = std::make_shared<Sample::StateInput>();
	m_Collider = std::make_shared<Sample::CAttackCollider>();
	m_pMesh = Sample::ResourceManager<CMeshContainer>::GetInstance().GetResource("Zombie");

	if (m_pMesh == nullptr)
	{
		return false;
	}

	m_Motion = m_pMesh->CreateMotionController();
	m_Actor->SetAnimationState(m_Motion);

	m_StateMachine = std::make_shared<Sample::StateMachine>();
	m_StateMachine->AddState(Sample::State::Create<Sample::IdleState>(m_Actor, m_Input));
	m_StateMachine->AddState(Sample::State::Create<Sample::MoveState>(m_Actor, m_Input));
	m_StateMachine->AddState(Sample::State::Create<Sample::RunState>(m_Actor, m_Input));
	m_StateMachine->AddState(Sample::State::Create<Sample::Attack1State>(m_Actor, m_Input));
	m_StateMachine->AddState(Sample::State::Create<Sample::DamageState>(m_Actor, m_Input));
	m_StateMachine->AddState(Sample::State::Create<Sample::FlyDamageState>(m_Actor, m_Input));
	m_StateMachine->AddState(Sample::State::Create<Sample::DownState>(m_Actor, m_Input));
	m_StateMachine->AddState(Sample::State::Create<Sample::DeadState>(m_Actor, m_Input));

	m_Actor->AddAction(Sample::Action::Create<Sample::IdleAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::MoveAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::RunAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::Attack1Action>());
	m_Actor->AddAction(Sample::Action::Create<Sample::DamageAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::FlyDamageAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::DownAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::DeadAction>());

	m_Actor->GetParameterMap()->Add<Vector3>(PARAMETER_KEY_KNOCKBACK, Vector3(0, 0, 0));
	m_Actor->GetParameterMap()->Add<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP, 500);
	m_Actor->GetParameterMap()->Add<Sample::ReactiveParameter<int>>(PARAMETER_KEY_MAXHP, 500);
	m_Actor->GetParameterMap()->Add<int>(PARAMETER_KEY_DAMAGE, 0);
	m_Actor->GetParameterMap()->Add<float>(PARAMETER_KEY_ALPHA, 1.0f);
	m_Actor->GetParameterMap()->Add<float>(PARAMETER_KEY_INVINCIBLE, 0.0f);

	m_HP = m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	m_MaxHP = m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_MAXHP);
	m_Position = m_Actor->GetPosition();
	m_HPShowFlg = true;
	return true;
}

void CEnemy::Initialize(CVector3 pos)
{
	m_Actor->SetPosition(pos);
	m_Actor->SetRotate(Vector3(0, 0, 0));
	m_Actor->SetScale(Vector3(1, 1, 1));
	m_ColliderSize.x = 0.5f;
	m_ColliderSize.y = 0.8f;
	m_ColliderSize.z = 0.5f;
	m_ColliderOffset.y = 1.0f;

	m_Collider->SetPosition(pos + Vector3(0, 5.0f, 0));
	m_Collider->SetRadius(0.6f);
	m_StateMachine->ChangeState(STATE_KEY_IDLE);
	matWorld = m_Actor->GetMatrix();
	m_ShowFlg = true;
	m_DeadFlg = false;

}

void CEnemy::Update()
{
	if (!m_ShowFlg)
	{
		return;
	}
	
	

	auto& invincible = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	if (invincible > 0.0f)
	{
		invincible -= CUtilities::GetFrameSecond();
	}
	if (m_DeadFlg)
	{
		auto& alpha = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
		if (alpha <= 0)
		{
			m_ShowFlg = false;
		}
	}
	Sample::CActorObject::Update();
	m_Position = m_Actor->GetPosition();
}

void CEnemy::Render()
{
	if (!m_ShowFlg)
	{
		return;
	}

	auto& alpha = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
	m_Motion->RefreshBoneMatrix(matWorld);
	m_pMesh->Render(m_Motion, Vector4(1.0f, 1.0f, 1.0f, alpha));
}

void CEnemy::RenderDebug()
{
}

void CEnemy::Render2D()
{
	if (!m_ShowFlg)
	{
		return;
	}
	if (!m_DeadFlg)
	{

	}
	
}

void CEnemy::Render2DDebug()
{
}

void CEnemy::Release()
{
	Sample::CActorObject::Release();
	m_Collider.reset();
}

void CEnemy::Damage(const Vector3& direction,Vector3 power,int damage)
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
		m_HPShowFlg = false;
	}
	m_HP = hp;

	knockBack = direction * power;



	m_StateMachine->ChangeState(STATE_KEY_DAMAGE);
}

bool CEnemy::IsInvincible() const
{
	auto& invincible = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	return invincible > 0.0f || m_StateMachine->GetCurrentState()->GetKey() == STATE_KEY_DEAD || m_StateMachine->GetCurrentState()->GetKey() == STATE_KEY_DOWN;
}
