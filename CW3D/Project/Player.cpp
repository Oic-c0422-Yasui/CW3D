#include "Player.h"
#include	"EffectController.h"



CPlayer::CPlayer()
	: ActionGame::ActorObject()
	, m_pInput()

{
	SetType(CHARA_TYPE::PLAYER);
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Load()
{
	//���b�V���擾
	m_pMesh = ActionGame::ResourcePtrManager<CMeshContainer>::GetInstance().GetResource("Player", "Player");

	if (m_pMesh == nullptr)
	{
		return false;
	}
	//���[�V�����ǂݍ���
	m_Motion = m_pMesh->CreateMotionController();
	m_Actor->SetAnimationState(m_Motion);
	
	m_StateMachine = std::make_shared<ActionGame::StateMachine>();
	//�A�N�V�����쐬
	m_ActionCreator.Create(m_Actor);
	//�X�e�[�g�쐬
	m_StateCreator.Create(m_StateMachine, m_Actor, m_pInput);
	
	//�p�����[�^�[�쐬
	auto& param = m_Actor->GetParameterMap();
	m_ParameterCreator.Create(param);
	//�p�����[�^�[�ݒ�
	m_MaxHP = param->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_MAX_HP);
	m_MaxUltGauge = param->Get<ActionGame::ReactiveParameter<float>>(PARAMETER_KEY_MAX_ULTGAUGE);
	//�X�L���ݒ�
	m_SkillCreator.Create(m_Actor);
	
	return true;
}

void CPlayer::Initialize()
{
	//���W�ݒ�
	m_Actor->SetPosition(Vector3(-30, 0,0));
	m_Actor->SetRotate(Vector3(0, 0, 0));
	m_Actor->SetScale(Vector3(1, 1, 1));
	m_ColliderSize = Vector3(0.5f, 0.8f, 0.5f);
	m_ColliderOffset.y = 1.0f;
	m_EscapeColliderSize = m_ColliderSize + Vector3(1.2f,0.5f,1.2f);
	m_Actor->SetReverse(false);

	//�����͑ҋ@���[�V����
	m_StateMachine->ChangeState(STATE_KEY_STARTPOSE);

	//���肪�l������K�E�Z�Q�[�W�̔{��
	SetUltBoostMag(1.0f);

	//�p�����[�^������
	auto param = m_Actor->GetParameterMap();
	auto& gauge = param->Get<ActionGame::ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	gauge = 0.0f;
	auto& hp = param->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp = m_MaxHP.Get();
	auto& alpha = param->Get<float>(PARAMETER_KEY_ALPHA);
	alpha = 1.0f;
	auto& invincible = param->Get<float>(PARAMETER_KEY_INVINCIBLE);
	invincible = 0.0f;
	auto& armorLevel = param->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	armorLevel = param->Get<BYTE>(PARAMETER_KEY_DEFAULT_ARMORLEVEL);

	//�X�L��������
	m_Actor->GetSkillController()->Reset();
	
	ActorObject::Initialize();
}

void CPlayer::Update()
{
	if (!m_ShowFlg)
	{
		return;
	}
	
	//���G���Ԓ��Ȃ玞�Ԃ����炷
	auto& invincible = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	if (invincible > 0.0f)
	{
		invincible -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}

	//���񂾂�
	if (m_DeadFlg)
	{
		//���S�ɓ����Ȃ�\�����Ȃ�
		auto& alpha = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
		if (alpha <= 0)
		{
			m_ShowFlg = false;
		}
	}
	ActionGame::ActorObject::Update();
}

void CPlayer::Render()
{
	if (!m_ShowFlg)
	{
		return;
	}
	ActionGame::ActorObject::Render();
}

void CPlayer::RenderDebug2D()
{

}

void CPlayer::Release()
{
	ActionGame::ActorObject::Release();
}

void CPlayer::Damage(const Vector3& direction, const Vector3& power, int damage,BYTE armorBrakeLevel)
{

	//�_���[�W�G�t�F�N�g����
	ActionGame::EffectCreateParameter param = { "DamageEffect1", Vector3(0, 1.0f, 0) , Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f),1.0f };
	ActionGame::EffectPtr effect = EffectControllerInstance.Play(param.name, GetCollider().Position, param);

	//�_���[�W���󂯂������Ɍ���
	auto& transform = m_Actor->GetTransform();
	transform->SetReverse(direction.x > 0 ? true : false);


	//�_���[�W
	auto& hp = m_Actor->GetParameterMap()->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp -= damage;

	//HP���O�ȉ��Ȃ玀�S
	if (hp <= 0)
	{
		hp = 0;

		m_DeadFlg = true;
	}

	//�K�E�Z�Q�[�W�l��
	AddUltGauge(1.0f);

	//���g�̃A�[�}�[���x����葊��̃A�[�}�[�j�󃌃x���̂ق��������Ƃ�
	auto& armorLevel = m_Actor->GetParameterMap()->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	if (armorLevel <= armorBrakeLevel)
	{
		//�m�b�N�o�b�N�ݒ�
		auto& knockBack = m_Actor->GetParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);
		knockBack = direction * power;

		//�_���[�W�X�e�[�g�֑J��
		m_StateMachine->ChangeState(STATE_KEY_DAMAGE);
	}

}

bool CPlayer::IsInvincible() const
{
	auto& invincible = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	return invincible > 0.0f || m_StateMachine->GetCurrentState()->GetKey() == STATE_KEY_DEAD || m_StateMachine->GetCurrentState()->GetKey() == STATE_KEY_DOWN
							|| m_StateMachine->GetCurrentState()->GetKey() == STATE_KEY_STARTPOSE;
}

void CPlayer::ClearPose()
{
	if (!m_StateMachine->IsState(STATE_KEY_CLEARPOSE))
	{
		m_StateMachine->ChangeState(STATE_KEY_CLEARPOSE);
	}
}
