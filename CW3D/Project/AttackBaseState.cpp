#include "AttackBaseState.h"
#include "ParameterDefine.h"

using namespace ActionGame;

ActionGame::AttackBaseState::AttackBaseState()
	: State()
	, m_CurrentTime(0.0f)
	, m_NextInputFlg(false)
{
}


void ActionGame::AttackBaseState::ReleaseShot()
{
	for (auto& shot : m_pShots)
	{
		shot->SetShow(false);
		shot.reset();
	}
	m_pShots.clear();
}

void ActionGame::AttackBaseState::ReleaseEffect()
{
	for (auto& effect : m_pEffects)
	{
		effect->SetStop(true);
		effect.reset();
	}
	m_pEffects.clear();
}

const ShotAABB& ActionGame::AttackBaseState::GetCreateShotStatusAABB()
{
	assert(false);
	static const ShotAABB box = {};
	return box;
}

const ShotOBB& ActionGame::AttackBaseState::GetCreateShotStatusOBB()
{
	assert(false);
	static const ShotOBB box = {};
	return box;
}

const ShotSphere& ActionGame::AttackBaseState::GetCreateShotStatusSphere()
{
	assert(false);
	static const ShotSphere sphere = {};
	return sphere;
}

const EffectCreateParameter& ActionGame::AttackBaseState::GetCreateEffectStatus()
{
	assert(false);
	static const EffectCreateParameter param = {};
	return param;
}

void ActionGame::AttackBaseState::CreateShotAABB()
{
	//攻撃力取得
	auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
	ShotAABB status = GetCreateShotStatusAABB();
	status.damage += attack;
	status.type = Actor()->GetType();
	status.parentID = Actor()->GetID();
	//アクターが反転状態なら向きを反転
	if (Actor()->IsReverse())
	{
		status.offset.x *= -1;
	}
	status.direction = GetKnockBack();

	m_pShots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), status));
}

void ActionGame::AttackBaseState::CreateShotOBB()
{
	//攻撃力取得
	auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
	ShotOBB status = GetCreateShotStatusOBB();
	status.damage += attack;
	status.type = Actor()->GetType();
	status.parentID = Actor()->GetID();
	//アクターが反転状態なら向きを反転
	if (Actor()->IsReverse())
	{
		status.offset.x *= -1;
		status.angle.z *= -1;
	}
	status.direction = GetKnockBack();

	m_pShots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), status));
}

void ActionGame::AttackBaseState::CreateShotSphere()
{
	auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
	ShotSphere status = GetCreateShotStatusSphere();
	status.damage += attack;
	status.type = Actor()->GetType();
	status.parentID = Actor()->GetID();
	//アクターが反転状態なら向きを反転
	if (Actor()->IsReverse())
	{
		status.offset.x *= -1;
	}
	status.direction = GetKnockBack();
	m_pShots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), status));
}

void ActionGame::AttackBaseState::CreateEffect()
{
	EffectCreateParameter status = GetCreateEffectStatus();

	//アクターが反転状態なら向きを反転
	if (Actor()->IsReverse())
	{
		status.offset.x *= -1;
		if (status.rotate.y == MOF_ToRadian(360))
		{
			status.rotate.y = MOF_ToRadian(180);
		}
		else
		{
			status.rotate.y *= -1;
		}
	}
	m_pEffects.push_back(EffectControllerInstance.Play(status.name, Actor()->GetPosition(), status));
}



void ActionGame::AttackBaseState::Start()
{
	m_CurrentTime = 0.0f;
	m_NextInputFlg = false;
	if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
	{
		Actor()->SetReverse(false);
	}
	else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
	{
		Actor()->SetReverse(true);
	}
}

void ActionGame::AttackBaseState::Execution()
{
	m_CurrentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
}

void ActionGame::AttackBaseState::InputExecution() {

	float scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	
	//タイムスケールが0以下の場合、入力を受け付けない
	if (scale <= 0.0f)
	{
		return;
	}
	//対応したスキルのボタンが押されていたらそのスキルのステートに移動
	for (int i = 0; i < Actor()->GetSkillController()->GetCount(); i++)
	{
		SKillPtr skill = Actor()->GetSkillController()->GetSkill(i);
		if (!skill->IsCanUse() || skill->GetState() == NULL || skill->GetFlyState() == NULL)
		{
			continue;
		}
		if (Input()->IsPush(skill->GetButton()))
		{

			skill->Start();
			if (Actor()->GetPositionY() > 0)
			{
				ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetFlyState());
			}
			else
			{
				ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetState());
			}
			break;
		}
	}

}

void ActionGame::AttackBaseState::End() 
{
	ReleaseShot();
	ReleaseEffect();
	auto param = Actor()->GetParameterMap();
	auto& armorLevel =  param->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	armorLevel = param->Get<BYTE>(PARAMETER_KEY_DEFAULT_ARMORLEVEL);
}
