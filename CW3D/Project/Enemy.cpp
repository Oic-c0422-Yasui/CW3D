#include "Enemy.h"
#include	"CameraController.h"
#include	"EffectController.h"

using namespace ActionGame;


Enemy::Enemy()

	: ActionGame::ActorObject()
	, m_Input()
	, m_DefaultPos(0,0,0)
	, m_BossFlg(false)
{
	SetType(CHARA_TYPE::ENEMY);
}

Enemy::~Enemy()
{
	Release();
}

bool Enemy::Load(const EnemyBuildParameterPtr& eneParam,
	const ActionCreatorPtr& actionCreator,
	const StateCreatorPtr& stateCreator,
	const ParameterCreatorPtr& paramCreator,
	const CharacterAICreatorPtr& aiCreator)
{
	//�����ʒu
	m_DefaultPos = eneParam->GetParam().m_Pos;

	//�{�X�����f
	m_BossFlg = eneParam->GetParam().m_IsBoss;

	//�C���v�b�g�L�[
	auto& stateInput = std::make_shared<ActionGame::CStateInput>();
	m_Input = stateInput;

	//���b�V���擾
	m_pMesh = ActionGame::ResourcePtrManager<CMeshContainer>::GetInstance().GetResource("Enemy", eneParam->GetStatus()->MeshName);
	if (m_pMesh == nullptr)
	{
		return false;
	}

	//���[�V�����쐬
	m_Motion = m_pMesh->CreateMotionController();
	//���[�V������Ԑݒ�
	actor_->SetAnimationState(m_Motion);

	//�A�N�V�����쐬
	actionCreator->Create(actor_);
	//�X�e�[�g�쐬
	stateCreator->Create(m_StateMachine, actor_, m_Input);
	//�p�����[�^�[�쐬
	auto& param = actor_->GetParameterMap();
	paramCreator->Create(param);

	//�p�����[�^�ݒ�
	SettingParameter(param, eneParam->GetStatus());


	//�����ʒu�ݒ�
	position_ = m_DefaultPos;

	//AI�쐬
	m_AI = aiCreator->Create(actor_, m_StateMachine, stateInput);

	return true;
}

void Enemy::Initialize()
{
	//�p�����[�^������
	auto param = actor_->GetParameterMap();
	auto& gauge = param->Get<ActionGame::ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	gauge = 0.0f;
	auto& hp = param->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp = m_MaxHP.Get();
	m_HP = m_MaxHP.Get();
	auto& alpha = param->Get<float>(PARAMETER_KEY_ALPHA);
	alpha = 1.0f;
	auto& invincible = param->Get<float>(PARAMETER_KEY_INVINCIBLE);
	invincible = 0.0f;
	auto& HPShowFlg = param->Get<ActionGame::ReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP);
	HPShowFlg = false;
	auto& armorLevel = param->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	armorLevel = param->Get<BYTE>(PARAMETER_KEY_DEFAULT_ARMORLEVEL);


	ActionGame::ActorObject::Initialize();
	//���W������
	actor_->SetPosition(m_DefaultPos);
	actor_->SetReverse(true);

	m_StateMachine->ChangeState(STATE_KEY_NPC_STARTPOSE);
	m_MatWorld = actor_->GetMatrix();
	m_ShowFlg = false;
	


}

void Enemy::Update()
{
	if (!m_ShowFlg)
	{
		return;
	}


	//���G���Ԓ��Ȃ玞�Ԃ����炷
	auto& invincible = actor_->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	if (invincible > 0.0f)
	{
		invincible -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}

	//���񂾂�
	if (m_DeadFlg)
	{
		//���S�ɓ����ɂȂ�����\�����Ȃ�
		auto& alpha = actor_->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
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

	position_ = actor_->GetPosition();
}

void Enemy::Render()
{
	if (!m_ShowFlg)
	{
		return;
	}

	ActionGame::ActorObject::Render();
}

void Enemy::RenderDebug()
{
	CGraphicsUtilities::RenderBox(GetCollider(), Vector4(0, 1, 0, 0.2f));
}

void Enemy::Render2D()
{
	if (!m_ShowFlg)
	{
		return;
	}

	
}

void Enemy::Render2DDebug()
{
}

void Enemy::Release()
{
	ActionGame::ActorObject::Release();
}

void Enemy::Damage(const Vector3& direction, const Vector3& power,int damage,BYTE armorBrekeLevel)
{

	//�_���[�W�G�t�F�N�g����
	ActionGame::EffectCreateParameter param = { "DamageEffect1", Vector3(0, 1.0f, 0) , Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f),1.0f };
	ActionGame::EffectPtr effect = EffectControllerInstance.Play(param.name, GetCollider().Position, param);

	//�_���[�W���󂯂������Ɍ���
	auto& transform = actor_->GetTransform();
	transform->SetReverse(direction.x > 0 ? true : false);

	//�_���[�W
	auto& hp = actor_->GetParameterMap()->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp -= damage;

	//HP���O�ȉ��Ȃ玀�S
	if (hp <= 0)
	{
		hp = 0;

		m_DeadFlg = true;
		auto& HPShowFlg = actor_->GetParameterMap()->Get<ActionGame::ReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP);
		HPShowFlg = false;
	}
	m_HP = hp;

	//���g�̃A�[�}�[���x����葊��̃A�[�}�[�j�󃌃x���̂ق��������Ƃ�

	auto& armorLevel = actor_->GetParameterMap()->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	if (armorLevel <= armorBrekeLevel)
	{
		//�m�b�N�o�b�N�ݒ�
		auto& knockBack = actor_->GetParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);
		knockBack = direction * power;

		//�J������h�炷
		CameraControllerInstance.Quake(0.20f, 40.0f, 0.2f);

		//�_���[�W�X�e�[�g�֑J��
		m_StateMachine->ChangeState(STATE_KEY_DAMAGE);
	}
}

bool Enemy::IsInvincible() const
{
	auto& invincible = actor_->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	return invincible > 0.0f || m_StateMachine->GetCurrentState()->GetKey() == STATE_KEY_DEAD || m_StateMachine->GetCurrentState()->GetKey() == STATE_KEY_DOWN;
}

void ActionGame::Enemy::SettingParameter(const AnyParameterMapPtr& param, const EnemyStatusPtr& eneStatus)
{
	//HP
	auto& maxHP = param->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_MAX_HP);
	maxHP = eneStatus->HP;
	auto& hp = param->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp = eneStatus->HP;
	m_HP = maxHP;
	m_MaxHP = maxHP;
	//�U����
	auto& atk = param->Get<int>(PARAMETER_KEY_ATTACK);
	atk = eneStatus->Atk;
	//���O
	m_Name = eneStatus->Name;
	//�K�E�Z�Q�[�W
	auto& maxUltGauge = param->Get<ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	maxUltGauge = eneStatus->UltGauge;
	//���肪�l������K�E�Z�Q�[�W�̔{��
	SetUltBoostMag(eneStatus->UltGaugeBoostMag);
	//�d��
	m_Weight = eneStatus->Weight;
	//�A�[�}�[���x��
	auto& defaultArmorLevel = param->Get<BYTE>(PARAMETER_KEY_DEFAULT_ARMORLEVEL);
	defaultArmorLevel = eneStatus->ArmorLevel;
	auto& armorLevel = param->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	armorLevel = eneStatus->ArmorLevel;
	//�傫��
	actor_->SetScale(eneStatus->Scale);
	//�����蔻��
	m_ColliderSize = eneStatus->ColliderSize;
	m_ColliderOffset = Vector3(0.0f,eneStatus->ColliderHeight, 0.0f);

}

