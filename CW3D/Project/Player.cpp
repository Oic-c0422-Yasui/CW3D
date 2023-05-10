#include "Player.h"
#include "ServiceLocator.h"

using namespace ActionGame;

ActionGame::CPlayer::CPlayer()
	: ActionGame::CActorObject()
	, combo_(std::make_shared<CCombo>(COMBO_SHOW_TIME))
	, initMotionName_()

{
	SetType(CHARA_TYPE::PLAYER);
}

ActionGame::CPlayer::~CPlayer()
{
	Release();
}

bool ActionGame::CPlayer::Load(const ActionCreatorPtr& actionCreator,
							   const StateCreatorPtr& stateCreator,
							   const ParameterCreatorPtr& paramCreator,
							   const Input::InputPtr& input,
							   const SkillCreatorPtr& skillCreator,
							   const std::string& initMotion)
{
	//���b�V���擾
	mesh_ = ResourcePtrManager<CMeshContainer>::GetInstance().GetResource("Player", "Player");

	if (mesh_ == nullptr)
	{
		return false;
	}
	CActorObject::Load();
	
	//�V�F�[�_�[�ǂݍ���
	normalMap_ = ResourcePtrManager<MyClass::CNormalMapSkinnedParameter>::GetInstance().GetResource("Shader", "NormalMapSkin");
	
	//�A�N�V�����쐬
	actionCreator->Create(actor_);
	//�X�e�[�g�쐬
	stateMachine_ = std::make_shared<ActionGame::StateMachine>();
	stateCreator->Create(stateMachine_, actor_, input);
	//�p�����[�^�[�쐬
	auto& param = actor_->GetParameterMap();
	paramCreator->Create(param);
	//�X�L���쐬
	skillCreator->Create(actor_);


	//�p�����[�^�[�ݒ�
	maxHP_ = param->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_MAX_HP);
	maxUltGauge_ = param->Get<ActionGame::CReactiveParameter<float>>(PARAMETER_KEY_MAX_ULTGAUGE);

	//�������[�V�������ݒ�
	initMotionName_ = initMotion;
	
	CServiceLocator<ICombo>::SetService(combo_);

	return true;
}

void ActionGame::CPlayer::Initialize()
{
	//���W�ݒ�
	actor_->SetPosition(Vector3(-30, 0,0));
	actor_->SetRotate(Vector3(0, MOF_ToRadian(-90), 0));
	actor_->SetScale(Vector3(1, 1, 1));
	colliderSize_ = Vector3(0.5f, 0.8f, 0.5f);
	colliderOffset_.y = 1.0f;
	escapeColliderSize_ = colliderSize_ + Vector3(1.2f,0.5f,1.2f);
	actor_->SetReverse(false);

	//�������[�V����
	stateMachine_->ChangeState(initMotionName_);

	//���肪�l������K�E�Z�Q�[�W�̔{��
	SetUltBoostMag(1.0f);

	//�p�����[�^������
	auto param = actor_->GetParameterMap();
	auto& gauge = param->Get<ActionGame::CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	gauge = 0.0f;
	auto& hp = param->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp = maxHP_.Get();
	auto& alpha = param->Get<float>(PARAMETER_KEY_ALPHA);
	alpha = 1.0f;
	auto& invincible = param->Get<float>(PARAMETER_KEY_INVINCIBLE_TIME);
	invincible = 0.0f;
	auto& armorLevel = param->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	armorLevel = param->Get<BYTE>(PARAMETER_KEY_DEFAULT_ARMORLEVEL);

	//�X�L��������
	actor_->GetSkillController()->Reset();
	
	//�R���{������
	combo_->Initialize();

	CActorObject::Initialize();
}

void ActionGame::CPlayer::Update()
{
	if (!isShow_)
	{
		return;
	}
	
	//���G���Ԓ��Ȃ玞�Ԃ����炷
	auto& invincible = actor_->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE_TIME);
	if (invincible > 0.0f)
	{
		invincible -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}

	//���񂾂�
	if (isDead_)
	{
		//���S�ɓ����Ȃ�\�����Ȃ�
		auto& alpha = actor_->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
		if (alpha <= 0)
		{
			isShow_ = false;
		}
	}

	//�R���{�X�V
	combo_->Update(GetType());

	ActionGame::CActorObject::Update();
}

void ActionGame::CPlayer::Render()
{
	if (!isShow_)
	{
		return;
	}
	ActionGame::CActorObject::Render();
}

void ActionGame::CPlayer::RenderDebug2D()
{

}

void ActionGame::CPlayer::Release()
{
	ActionGame::CActorObject::Release();
	combo_.reset();
	CServiceLocator<ICombo>::Release();
}

void ActionGame::CPlayer::Damage(const Vector3& direction, const Vector3& power, int damage,BYTE armorBreakeLevel)
{

	//�_���[�W���󂯂������Ɍ���
	auto& transform = actor_->GetTransform();
	transform->SetReverse(direction.x > 0 ? true : false);

	//�_���[�W
	auto& hp = actor_->GetParameterMap()->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp -= damage;

	//�K�E�Z�Q�[�W�l��
	AddUltGauge(1.0f);

	//���g�̃A�[�}�[���x����葊��̃A�[�}�[�j�󃌃x���̂ق��������Ƃ�
	auto& armorLevel = actor_->GetParameterMap()->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	if (armorLevel <= armorBreakeLevel)
	{
		//�m�b�N�o�b�N�ݒ�
		auto& knockBack = actor_->GetParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);
		knockBack = direction * power;

		//�_���[�W�X�e�[�g�֑J��
		stateMachine_->ChangeState(STATE_KEY_DAMAGE);
	}

	//HP���O�ȉ��Ȃ玀�S
	if (hp <= 0)
	{
		//���S���̂݁A�A�[�}�[���x���������荂���Ă��X�e�[�g��J��
		if (armorLevel > armorBreakeLevel)
		{
			//�_���[�W�X�e�[�g�֑J��
			stateMachine_->ChangeState(STATE_KEY_DAMAGE);
		}
		hp = 0;
		isDead_ = true;
	}

}

void ActionGame::CPlayer::Damage(const Vector3& direction, const Vector3& power, int damage, BYTE armorBrakeLevel, const EffectCreateParameterPtr& effect)
{
	if (effect != nullptr)
	{
		//�_���[�W�G�t�F�N�g����
		EffectControllerInstance.Play(effect->name, GetCollider().Position, effect);
	}

	Damage(direction, power, damage, armorBrakeLevel);
}

bool ActionGame::CPlayer::IsInvincible() const
{
	auto& invincible = actor_->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE_TIME);
	return invincible > 0.0f || stateMachine_->GetCurrentState()->GetKey() == STATE_KEY_DEAD || stateMachine_->GetCurrentState()->GetKey() == STATE_KEY_DOWN
							|| stateMachine_->GetCurrentState()->GetKey() == STATE_KEY_STARTPOSE;
}

void ActionGame::CPlayer::ClearPose()
{
	if (!stateMachine_->IsState(STATE_KEY_CLEARPOSE))
	{
		stateMachine_->ChangeState(STATE_KEY_CLEARPOSE);
	}
}
