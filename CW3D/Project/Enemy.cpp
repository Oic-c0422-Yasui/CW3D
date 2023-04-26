#include "Enemy.h"
#include	"CameraController.h"
#include "ServiceLocator.h"
#include "ICombo.h"

using namespace ActionGame;


CEnemy::CEnemy()

	: ActionGame::CActorObject()
	, input_()
	, defaultPos_(0,0,0)
	, isBoss_(false)
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
	defaultPos_ = eneParam->GetParam().position_;

	//�{�X�����f
	isBoss_ = eneParam->GetParam().isBoss_;
	if (isBoss_)
	{
		actor_->SetType(CHARA_TYPE::BOSS);
	}

	//�C���v�b�g�L�[
	auto& stateInput = std::make_shared<Input::CStateInput>();
	input_ = stateInput;

	//���b�V���擾
	mesh_ = ResourcePtrManager<CMeshContainer>::GetInstance().GetResource("Enemy", eneParam->GetStatus()->MeshName);
	if (mesh_ == nullptr)
	{
		return false;
	}
	//�V�F�[�_�[�ǂݍ���
	normalMap_ = ResourcePtrManager<MyClass::CNormalMapSkinnedParameter>::GetInstance().GetResource("Shader", "NormalMapSkin");

	//���[�V�����쐬
	motion_ = mesh_->CreateMotionController();
	//���[�V������Ԑݒ�
	actor_->SetAnimationState(motion_);

	//�A�N�V�����쐬
	actionCreator->Create(actor_);
	//�X�e�[�g�쐬
	stateCreator->Create(stateMachine_, actor_, input_);
	//�p�����[�^�[�쐬
	auto& param = actor_->GetParameterMap();
	paramCreator->Create(param);

	//�p�����[�^�ݒ�
	SettingParameter(param, eneParam->GetStatus());


	//�����ʒu�ݒ�
	position_ = defaultPos_;

	//AI�쐬
	AI_ = aiCreator->Create(actor_, stateMachine_, stateInput);

	CActorObject::Load();

	return true;
}

void CEnemy::Initialize()
{
	//�p�����[�^������
	auto param = actor_->GetParameterMap();
	auto& gauge = param->Get<ActionGame::CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	gauge = 0.0f;
	auto& hp = param->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp = maxHP_.Get();
	HP_ = maxHP_.Get();
	auto& alpha = param->Get<float>(PARAMETER_KEY_ALPHA);
	alpha = 1.0f;
	auto& invincible = param->Get<float>(PARAMETER_KEY_INVINCIBLE_TIME);
	invincible = 0.0f;
	auto& isShowHP = param->Get<ActionGame::CReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP);
	isShowHP = false;
	auto& armorLevel = param->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	armorLevel = param->Get<BYTE>(PARAMETER_KEY_DEFAULT_ARMORLEVEL);


	ActionGame::CActorObject::Initialize();
	//���W������
	actor_->SetPosition(defaultPos_);
	actor_->SetReverse(true);

	stateMachine_->ChangeState(STATE_KEY_NPC_STARTPOSE);
	matWorld_ = actor_->GetMatrix();
	isShow_ = false;
	


}

void CEnemy::Update()
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
		//���S�ɓ����ɂȂ�����\�����Ȃ�
		auto& alpha = actor_->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
		if (alpha <= 0)
		{
			isShow_ = false;
		}
	}

	//��Ԃ̃C���v�b�g
	input_->Update();
	//AI�X�V
	AI_->Update();

	ActionGame::CActorObject::Update();

	position_ = actor_->GetPosition();
}

void CEnemy::Render()
{
	if (!isShow_)
	{
		return;
	}

	ActionGame::CActorObject::Render();
}

void CEnemy::RenderDebug()
{
	CGraphicsUtilities::RenderBox(GetCollider(), Vector4(0, 1, 0, 0.2f));
}

void CEnemy::Render2D()
{
	if (!isShow_)
	{
		return;
	}

	
}

void CEnemy::Render2DDebug()
{
}

void CEnemy::Release()
{
	ActionGame::CActorObject::Release();
}

void CEnemy::Damage(const Vector3& direction, const Vector3& power,int damage,BYTE armorBreakeLevel)
{

	//�_���[�W���󂯂������Ɍ���
	auto& transform = actor_->GetTransform();
	transform->SetReverse(direction.x > 0 ? true : false);

	//�_���[�W
	auto& hp = actor_->GetParameterMap()->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp -= damage;

	//�R���{���ǉ�
	CServiceLocator<ICombo>::GetService()->AddCount();

	//�J������h�炷
	CameraControllerInstance.Quake(0.25f, 40.0f, 0.2f);

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
		//HP���o�[��\��
		auto& isShowHP = actor_->GetParameterMap()->Get<ActionGame::CReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP);
		isShowHP = false;
	}
	HP_ = hp;

}

void ActionGame::CEnemy::Damage(const Vector3& direction, const Vector3& power, int damage, BYTE armorBrakeLevel, const EffectCreateParameterPtr& effect)
{
	if (effect != nullptr)
	{
		//�_���[�W�G�t�F�N�g����
		EffectControllerInstance.Play(effect->name, GetCollider().Position, effect);
	}

	Damage(direction,power,damage,armorBrakeLevel);
}

bool CEnemy::IsInvincible() const
{
	auto& invincible = actor_->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE_TIME);
	return invincible > 0.0f || stateMachine_->GetCurrentState()->GetKey() == STATE_KEY_DEAD || stateMachine_->GetCurrentState()->GetKey() == STATE_KEY_DOWN;
}

void ActionGame::CEnemy::SettingParameter(const AnyParameterMapPtr& param, const EnemyStatusPtr& eneStatus)
{
	//HP
	auto& maxHP = param->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_MAX_HP);
	maxHP = eneStatus->HP;
	auto& hp = param->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp = eneStatus->HP;
	HP_ = maxHP;
	maxHP_ = maxHP;
	//�U����
	auto& atk = param->Get<int>(PARAMETER_KEY_ATTACK);
	atk = eneStatus->Atk;
	//���O
	name_ = eneStatus->Name;
	//�K�E�Z�Q�[�W
	auto& maxUltGauge = param->Get<CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	maxUltGauge = eneStatus->UltGauge;
	//���肪�l������K�E�Z�Q�[�W�̔{��
	SetUltBoostMag(eneStatus->UltGaugeBoostMag);
	//�d��
	weight_ = eneStatus->Weight;
	//�A�[�}�[���x��
	auto& defaultArmorLevel = param->Get<BYTE>(PARAMETER_KEY_DEFAULT_ARMORLEVEL);
	defaultArmorLevel = eneStatus->ArmorLevel;
	auto& armorLevel = param->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	armorLevel = eneStatus->ArmorLevel;
	//�傫��
	actor_->SetScale(eneStatus->Scale);
	//�����蔻��
	colliderSize_ = eneStatus->ColliderSize;
	colliderOffset_ = Vector3(0.0f,eneStatus->ColliderHeight, 0.0f);

}

