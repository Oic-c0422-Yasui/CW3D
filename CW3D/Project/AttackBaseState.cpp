#include "AttackBaseState.h"
#include "ParameterDefine.h"
#include "ActorObjectManager.h"
#include "AnimationUtilities.h"

using namespace ActionGame;

ActionGame::CAttackBaseState::CAttackBaseState()
	: CState()
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
	//�U���͎擾
	auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
	ShotAABB status = GetCreateShotStatusAABB();
	status.damage += attack;
	status.type = Actor()->GetType();
	status.parentID = Actor()->GetID();
	//�A�N�^�[�����]��ԂȂ�����𔽓]
	if (Actor()->IsReverse())
	{
		status.offset.x *= -1;
	}
	status.direction = GetKnockBack();

	shots_.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), status));
}

void ActionGame::CAttackBaseState::CreateShotOBB()
{
	//�U���͎擾
	auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
	ShotOBB status = GetCreateShotStatusOBB();
	status.damage += attack;
	status.type = Actor()->GetType();
	status.parentID = Actor()->GetID();
	//�A�N�^�[�����]��ԂȂ�����𔽓]
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
	status.type = Actor()->GetType();
	status.parentID = Actor()->GetID();
	//�A�N�^�[�����]��ԂȂ�����𔽓]
	if (Actor()->IsReverse())
	{
		status.offset.x *= -1;
	}
	status.direction = GetKnockBack();
	shots_.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), status));
}

void ActionGame::CAttackBaseState::CreateEffect()
{
	EffectCreateParameter status = GetCreateEffectStatus();
	status.type = Actor()->GetType();
	//�A�N�^�[�����]��ԂȂ�����𔽓]
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
	effects_.push_back(EffectControllerInstance.Play(status.name, Actor()->GetPosition(), status));
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

	//�ړ��␳�A�N�V�����擾
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

	float scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	
	//�^�C���X�P�[����0�ȉ��̏ꍇ�A���͂��󂯕t���Ȃ�
	if (scale <= 0.0f)
	{
		return;
	}
	//�Ή������X�L���̃{�^����������Ă����炻�̃X�L���̃X�e�[�g�Ɉړ�
	for (int i = 0; i < Actor()->GetSkillController()->GetCount(); i++)
	{
		SKillPtr skill = Actor()->GetSkillController()->GetSkill(i);
		if (!skill->CanUseSkill() || skill->GetState() == nullptr || skill->GetFlyState() == nullptr)
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
