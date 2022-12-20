#include "Enemy.h"
#include	"CameraController.h"
#include	"EffectController.h"

using namespace ActionGame;


CEnemy::CEnemy()

	: ActionGame::ActorObject()
	, m_Input()
	, m_DefaultPos(0,0,0)
{
	SetType(CHARA_TYPE::ENEMY);
}

CEnemy::~CEnemy()
{
	Release();
}

bool CEnemy::Load(const EnemyBuildParameterPtr& eneParam,
	const ActionCreatorPtr& actionCreator,
	const StateCreatorPtr& stateCreator,
	const ParameterCreatorPtr& paramCreator,
	const CharacterAICreatorPtr& aiCreator)
{
	//�����ʒu
	m_DefaultPos = eneParam->GetParam().m_Pos;

	//�C���v�b�g�L�[
	auto& stateInput = std::make_shared<ActionGame::StateInput>();
	m_Input = stateInput;

	//���b�V���擾
	m_pMesh = ActionGame::ResourcePtrManager<CMeshContainer>::GetInstance().GetResource("Enemy", eneParam->GetStatus()->m_MeshName);
	if (m_pMesh == nullptr)
	{
		return false;
	}

	//���[�V�����쐬
	m_Motion = m_pMesh->CreateMotionController();
	//���[�V������Ԑݒ�
	m_Actor->SetAnimationState(m_Motion);

	//�A�N�V�����쐬
	actionCreator->Create(m_Actor);
	//�X�e�[�g�쐬
	stateCreator->Create(m_StateMachine, m_Actor, m_Input);
	//�p�����[�^�[�쐬
	auto& param = m_Actor->GetParameterMap();
	paramCreator->Create(param);

	//�p�����[�^�ݒ�
	SettingParameter(param, eneParam->GetStatus());

	//�����ʒu�ݒ�
	m_Position = m_DefaultPos;
	m_HPShowFlg = true;

	//AI�쐬
	m_AI = aiCreator->Create(m_Actor, m_StateMachine, stateInput);

	return true;
}

void CEnemy::Initialize()
{
	//���W������
	m_Actor->SetPosition(m_DefaultPos);
	m_Actor->SetRotate(Vector3(0, MOF_ToDegree(90), 0));
	m_Actor->SetScale(Vector3(1, 1, 1));


	m_StateMachine->ChangeState(STATE_KEY_IDLE);
	matWorld = m_Actor->GetMatrix();
	m_ShowFlg = true;
	m_DeadFlg = false;
	m_HPShowFlg = true;


	//�p�����[�^������
	auto& gauge = m_Actor->GetParameterMap()->Get<ActionGame::ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	gauge = 0.0f;
	auto& hp = m_Actor->GetParameterMap()->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_HP);
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

	//���G���Ԓ��Ȃ玞�Ԃ����炷
	auto& invincible = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	if (invincible > 0.0f)
	{
		invincible -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}

	//���񂾂�
	if (m_DeadFlg)
	{
		//���S�ɓ����ɂȂ�����\�����Ȃ�
		auto& alpha = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
		if (alpha <= 0)
		{
			m_ShowFlg = false;
		}
	}

	//��Ԃ̃C���v�b�g
	m_Input->Update();
	//AI�X�V
	m_AI->Update();

	ActionGame::ActorObject::Update();

	m_Position = m_Actor->GetPosition();
}

void CEnemy::Render()
{
	if (!m_ShowFlg)
	{
		return;
	}

	ActionGame::ActorObject::Render();
}

void CEnemy::RenderDebug()
{
	CGraphicsUtilities::RenderBox(GetCollider(), Vector4(0, 1, 0, 0.2f));
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
	ActionGame::ActorObject::Release();
}

void CEnemy::Damage(const Vector3& direction, const Vector3& power,int damage,BYTE armorLevel)
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
		m_HPShowFlg = false;
	}
	m_HP = hp;

	//���g�̃A�[�}�[���x����葊��̃A�[�}�[�j�󃌃x���̂ق��������Ƃ�
	if (m_Actor->GetArmorLevel() <= armorLevel)
	{
		//�m�b�N�o�b�N�ݒ�
		auto& knockBack = m_Actor->GetParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);
		knockBack = direction * power;

		//�J������h�炷
		CameraControllerInstance.Quake(0.20f, 40.0f, 0.2f);

		//�_���[�W�X�e�[�g�֑J��
		m_StateMachine->ChangeState(STATE_KEY_DAMAGE);
	}
}

bool CEnemy::IsInvincible() const
{
	auto& invincible = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	return invincible > 0.0f || m_StateMachine->GetCurrentState()->GetKey() == STATE_KEY_DEAD || m_StateMachine->GetCurrentState()->GetKey() == STATE_KEY_DOWN;
}

void ActionGame::CEnemy::SettingParameter(const AnyParameterMapPtr& param, const EnemyStatusPtr& eneStatus)
{
	//HP
	auto& maxHP = param->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_MAXHP);
	maxHP = eneStatus->m_Hp;
	auto& hp = param->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp = eneStatus->m_Hp;
	m_HP = maxHP;
	m_MaxHP = maxHP;
	//�U����
	auto& atk = param->Get<int>(PARAMETER_KEY_ATTACK);
	atk = eneStatus->m_Atk;
	//�K�E�Z�Q�[�W
	auto& maxUltGauge = param->Get<ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	maxUltGauge = eneStatus->m_UltGauge;
	//���肪�l������K�E�Z�Q�[�W�̔{��
	SetUltBoostMag(eneStatus->m_UltGaugeBoostMag);
	//�����蔻��
	m_ColliderSize = eneStatus->m_ColliderSize;
	m_ColliderOffset = Vector3(0.0f,eneStatus->m_ColliderHeight, 0.0f);

}

