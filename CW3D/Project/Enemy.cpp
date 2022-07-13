#include "Enemy.h"


#include	"CameraController.h"
#include "CharacterAICreator.h"


using namespace Sample;

CEnemy::CEnemy(const Vector3& pos)
	: Sample::CActorObject()
	,m_Input()
	,m_AI()
	, m_DefaultPos(pos)
{
	SetType(CHARA_ENEMY);
}

CEnemy::~CEnemy()
{
	Release();
}

bool CEnemy::Load()
{
	auto& stateInput = std::make_shared<Sample::StateInput>();
	m_Input = stateInput;
	m_pMesh = Sample::ResourceManager<CMeshContainer>::GetInstance().GetResource("Zombie");

	if (m_pMesh == nullptr)
	{
		return false;
	}

	m_Motion = m_pMesh->CreateMotionController();
	m_Actor->SetAnimationState(m_Motion);

	m_StateMachine = std::make_shared<Sample::StateMachine>();

	m_ActionCreator.Create(m_Actor);
	m_StateCreator.Create(m_StateMachine, m_Actor, m_Input);

	m_Actor->GetParameterMap()->Add<Vector3>(PARAMETER_KEY_KNOCKBACK, Vector3(0, 0, 0));
	m_Actor->GetParameterMap()->Add<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP, 800);
	m_Actor->GetParameterMap()->Add<Sample::ReactiveParameter<int>>(PARAMETER_KEY_MAXHP, 800);
	m_Actor->GetParameterMap()->Add<int>(PARAMETER_KEY_DAMAGE, 0);
	m_Actor->GetParameterMap()->Add<int>(PARAMETER_KEY_ATTACK, 10);
	m_Actor->GetParameterMap()->Add<float>(PARAMETER_KEY_ALPHA, 1.0f);
	m_Actor->GetParameterMap()->Add<float>(PARAMETER_KEY_INVINCIBLE, 0.0f);
	m_Actor->GetParameterMap()->Add<Sample::ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE, 0.0f);
	m_Actor->GetParameterMap()->Add<Sample::ReactiveParameter<float>>(PARAMETER_KEY_MAXULTGAUGE, 100.0f);

	m_HP = m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	m_MaxHP = m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_MAXHP);
	m_Position = m_Actor->GetPosition();
	m_HPShowFlg = true;


	CharacterAICreatorPtr aiCreator = std::make_shared<CharacterAICreator>();

	m_AI = aiCreator->Create(m_Actor, m_StateMachine, stateInput);

	return true;
}

void CEnemy::Initialize()
{
	m_Actor->SetPosition(m_DefaultPos);
	m_Actor->SetRotate(Vector3(0, MOF_ToDegree(90), 0));
	m_Actor->SetScale(Vector3(1, 1, 1));
	m_ColliderSize.x = 0.5f;
	m_ColliderSize.y = 0.8f;
	m_ColliderSize.z = 0.5f;
	m_ColliderOffset.y = 1.0f;

	m_StateMachine->ChangeState(STATE_KEY_IDLE);
	matWorld = m_Actor->GetMatrix();
	m_ShowFlg = true;
	m_DeadFlg = false;
	m_HPShowFlg = true;

	//‘ŠŽè‚ªŠl“¾‚·‚é•KŽE‹ZƒQ[ƒW‚Ì”{—¦
	SetUltBoostMag(1.0f);
	auto& gauge = m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	gauge = 0.0f;
	auto& hp = m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp = m_MaxHP.Get();
	m_HP = m_MaxHP.Get();
	auto& alpha = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
	alpha = 1.0f;
	auto& invincible = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	invincible = 0.0f;
}

void CEnemy::Update()
{
	if (!m_ShowFlg)
	{
		return;
	}
	
	m_Input->Update();

	auto& invincible = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	if (invincible > 0.0f)
	{
		invincible -= CUtilities::GetFrameSecond() * TimeControllerInstance.GetTimeScale();
	}
	if (m_DeadFlg)
	{
		auto& alpha = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
		if (alpha <= 0)
		{
			m_ShowFlg = false;
		}
	}
	m_AI->Update();
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

	
}

void CEnemy::Render2DDebug()
{
}

void CEnemy::Release()
{
	Sample::CActorObject::Release();
}

void CEnemy::Damage(const Vector3& direction, const Vector3& power,int damage,BYTE level)
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

	if (m_Actor->GetArmorLevel() <= level)
	{
		knockBack = direction * power;

		CameraControllerInstance.Quake(0.20f, 40.0f, 0.2f);

		m_StateMachine->ChangeState(STATE_KEY_DAMAGE);
	}
}

bool CEnemy::IsInvincible() const
{
	auto& invincible = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	return invincible > 0.0f || m_StateMachine->GetCurrentState()->GetKey() == STATE_KEY_DEAD || m_StateMachine->GetCurrentState()->GetKey() == STATE_KEY_DOWN;
}


