#include "FlyHighSkillState.h"
#include "ParameterDefine.h"
#include "FollowFixedCamera.h"
#include "CameraController.h"

ActionGame::CFlyHighSkillState::CFlyHighSkillState(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, currenteEcapeTime_(0.0f)
	, isStartCollide_(false)
{
}

void ActionGame::CFlyHighSkillState::Start()
{
	isStartCollide_ = false;
	currenteEcapeTime_ = 0.0f;
	action_ = Actor()->GetAction<CJumpAction>(GetKey());
	action_->Start();
	CAttackBaseState::Start();

	CreateShotAABB();
	CreateEffect();

	for (auto& shot : shots_)
	{
		auto skillDamage = Actor()->GetSkillController()->GetSkill(SKILL_KEY_5)->GetDamage();
		auto damage = MyUtil::CalculateAtk(shot->GetDamage(), skillDamage);
		shot->SetDamage(damage);
	}


	Vector3 pos(0, 11, -18);
	Vector3 lookPos(0, -1, 0);
	
	//反転処理
	if (Actor()->IsReverse())
	{
		pos.x *= -1;
		lookPos.x *= -1;
	}
	CameraPtr camera;
	camera = std::make_shared<ActionGame::CFollowFixedCamera>(Actor()->GetPosition(), Actor()->GetPosition(), pos, lookPos);
	CameraControllerInstance.SetCamera(camera, 0.1f, MyUtil::EASING_TYPE::IN_SINE, 0.4f, MyUtil::EASING_TYPE::IN_SINE, 0.7f);
}

void ActionGame::CFlyHighSkillState::Execution()
{
	action_->Execution();
	for (auto& shot : shots_)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (currentTime_ >= parameter_.CollideStartFrameTime && !isStartCollide_)
		{
			shot->SetEnableCollider(true);
		}
		if (currentTime_ > parameter_.CollideEndFrameTime)
		{
			if (shot->IsEnableCollider())
			{
				shot->SetEnableCollider(false);
			}
		}

	}
	if (currentTime_ >= parameter_.CollideStartFrameTime && !isStartCollide_)
	{
		isStartCollide_ = true;
	}


	//ジャスト回避時間
	if (currentTime_ >= parameter_.EscapeStartTime)
	{

		if (currenteEcapeTime_ < parameter_.EscapeTime)
		{
			auto& isEscape_ = Actor()->GetParameterMap()->Get<bool>(PARAMETER_KEY_ESCAPE);
			if (!isEscape_)
			{
				isEscape_ = true;
			}
			currenteEcapeTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
			if (currenteEcapeTime_ >= parameter_.EscapeTime)
			{
				isEscape_ = false;
			}

		}
	}

	// 落下状態への移行
	if (Actor()->GetVelocity()->GetVelocityY() <= 0.0f)
	{
		ChangeState(STATE_KEY_FALL);
	}
	CAttackBaseState::Execution();
}

void ActionGame::CFlyHighSkillState::InputExecution()
{
	//タイムスケールが0以下の場合、入力を受け付けない
	if (IsTimeScaleZero())
	{
		return;
	}

	//左右で移動
	if (IsPressMoveKey())
	{
		action_->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL),
			-(Input()->GetAxis(INPUT_KEY_VERTICAL)));
	}


	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		ChangeState(STATE_KEY_JUMP_ATTACK1);
	}

	CAttackBaseState::InputExecution();
}

void ActionGame::CFlyHighSkillState::End()
{
	CAttackBaseState::End();
	action_->End();
	auto& isEscape_ = Actor()->GetParameterMap()->Get<bool>(PARAMETER_KEY_ESCAPE);
	isEscape_ = false;
}

void ActionGame::CFlyHighSkillState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CFlyHighSkillState::GetKey() const
{
	return STATE_KEY_FLYHIGH_SKILL;
}
