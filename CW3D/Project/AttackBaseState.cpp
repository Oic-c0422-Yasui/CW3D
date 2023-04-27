#include "AttackBaseState.h"
#include "ParameterDefine.h"
#include "ActorObjectManager.h"
#include "AnimationUtilities.h"

using namespace ActionGame;

ActionGame::CAttackBaseState::CAttackBaseState()
	: CBaseState()
	, currentTime_(0.0f)
	, isNextInput_(false)
	, moveCompensation_(nullptr)
{
}


void ActionGame::CAttackBaseState::ReleaseShot()
{
	for (auto& shot : shots_)
	{
		shot->SetShow(false);
		shot.reset();
	}
	shots_.clear();
}

void ActionGame::CAttackBaseState::ReleaseEffect()
{
	for (auto& effect : effects_)
	{
		effect->SetStop(true);
		effect.reset();
	}
	effects_.clear();
}

const ShotAABB& ActionGame::CAttackBaseState::GetCreateShotStatusAABB()
{
	assert(false);
	static const ShotAABB box = {};
	return box;
}

const ShotOBB& ActionGame::CAttackBaseState::GetCreateShotStatusOBB()
{
	assert(false);
	static const ShotOBB box = {};
	return box;
}

const ShotSphere& ActionGame::CAttackBaseState::GetCreateShotStatusSphere()
{
	assert(false);
	static const ShotSphere sphere = {};
	return sphere;
}

const EffectCreateParameter& ActionGame::CAttackBaseState::GetCreateEffectStatus()
{
	assert(false);
	static const EffectCreateParameter param = {};
	return param;
}

void ActionGame::CAttackBaseState::CreateShotAABB()
{
	//攻撃力取得
	auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
	ShotAABB status = GetCreateShotStatusAABB();
	status.damage += attack;
	status.parentType = Actor()->GetType();
	status.parentID = Actor()->GetID();
	//アクターが反転状態なら向きを反転
	if (Actor()->IsReverse())
	{
		status.offset.x *= -1;
	}
	status.direction = GetKnockBack();

	shots_.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), status));
}

void ActionGame::CAttackBaseState::CreateShotOBB()
{
	//攻撃力取得
	auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
	ShotOBB status = GetCreateShotStatusOBB();
	status.damage += attack;
	status.parentType = Actor()->GetType();
	status.parentID = Actor()->GetID();
	//アクターが反転状態なら向きを反転
	if (Actor()->IsReverse())
	{
		status.offset.x *= -1;
		status.angle.z *= -1;
	}
	status.direction = GetKnockBack();

	shots_.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), status));
}

void ActionGame::CAttackBaseState::CreateShotSphere()
{
	auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
	ShotSphere status = GetCreateShotStatusSphere();
	status.damage += attack;
	status.parentType = Actor()->GetType();
	status.parentID = Actor()->GetID();
	//アクターが反転状態なら向きを反転
	if (Actor()->IsReverse())
	{
		status.offset.x *= -1;
	}
	status.direction = GetKnockBack();
	shots_.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), status));
}

void ActionGame::CAttackBaseState::CreateEffect()
{
	CreateEffect(GetCreateEffectStatus());
}

void ActionGame::CAttackBaseState::CreateEffect(const EffectCreateParameter& effect)
{
	EffectCreateParameter param = effect;
	param.type = Actor()->GetType();
	//アクターが反転状態なら向きを反転
	if (Actor()->IsReverse())
	{
		param. offset.x *= -1;
		if (param.rotate.y == MOF_ToRadian(360))
		{
			param.rotate.y = MOF_ToRadian(180);
		}
		else
		{
			param.rotate.y *= -1;
		}
	}
	effects_.push_back(EffectControllerInstance.Play(param.name, Actor()->GetPosition(), param));
}

void ActionGame::CAttackBaseState::SetArmorLevel(BYTE level)
{
	auto& armorLevel = Actor()->GetParameterMap()->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	armorLevel = level;
}



void ActionGame::CAttackBaseState::Start()
{
	currentTime_ = 0.0f;
	isNextInput_ = false;

	if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
	{
		Actor()->SetReverse(false);
	}
	else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
	{
		Actor()->SetReverse(true);
	}

	//移動補正アクション取得
	moveCompensation_ = Actor()->GetAction<CMoveCompensationAction>(STATE_KEY_MOVECOMPENSATION + GetKey());
	if (moveCompensation_)
	{
		moveCompensation_->Start();
	}
	
}

void ActionGame::CAttackBaseState::Execution()
{
	if (moveCompensation_)
	{
		moveCompensation_->Execution();
	}

	currentTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
}

void ActionGame::CAttackBaseState::InputExecution() {
	
	//タイムスケールが0以下の場合、入力を受け付けない
	if (IsTimeScaleZero())
	{
		return;
	}
	//対応したスキルのボタンが押されていたらそのスキルのステートに移動
	ChangeSkillState();

}

void ActionGame::CAttackBaseState::End() 
{
	ReleaseShot();
	ReleaseEffect();
	auto param = Actor()->GetParameterMap();
	auto& armorLevel =  param->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	armorLevel = param->Get<BYTE>(PARAMETER_KEY_DEFAULT_ARMORLEVEL);
	if (moveCompensation_)
	{
		moveCompensation_->End();
	}
}
