#include "RunAttack1State.h"
#include "AnimationUtilities.h"

ActionGame::CRunAttack1State::CRunAttack1State(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isStartCollide_(false)
{
}

void ActionGame::CRunAttack1State::Start()
{
	action_ = Actor()->GetAction<CRunAttack1Action>(GetKey());

	isStartCollide_ = false;
	CAttackBaseState::Start();

	action_->Start();
	//当たり判定用の弾作成
	CreateShotAABB();
	isActorInSight_ = IsActorInSight(targetPos_, offsetSize_,270.0f,3.5f);

}

void ActionGame::CRunAttack1State::Execution()
{
	const auto pos = Actor()->GetPosition();

	if (isActorInSight_ && currentTime_ <= 0.1f)
	{
		auto distance = MyUtil::DistanceSquare(pos, targetPos_->GetPosition());
		auto mDist = std::pow(offsetSize_, 2);
		if (distance > mDist)
		{
			auto setPos = MyUtil::Timer(pos, currentTime_, targetPos_->GetPosition(), 0.1f);
			Actor()->SetPosition(Vector3(setPos.x, pos.y, setPos.z));
		}
		else
		{
			isActorInSight_ = false;
		}
	}
	else
	{
		if (targetPos_ != nullptr)
		{
			targetPos_.reset();
		}
	}
	

	for (auto& shot : shots_)
	{
		shot->SetPosition(pos + shot->GetOffset());
		if (currentTime_ >= parameter_.CollideStartFrameTime && !isStartCollide_)
		{
			shot->SetEnableCollider(true);
		}
		else if (shot->IsEnableCollider())
		{
			shot->SetEnableCollider(false);
		}
	}

	if (currentTime_ >= parameter_.CollideStartFrameTime && !isStartCollide_)
	{
		CreateEffect();
		isStartCollide_ = true;
	}


	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_IDLE);
	}

	CAttackBaseState::Execution();
}

void ActionGame::CRunAttack1State::InputExecution()
{
	float scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	//タイムスケールが0以下の場合、入力を受け付けない
	if (scale <= 0.0f)
	{
		return;
	}
	if (currentTime_ > parameter_.NextInputFrameTime)
	{
		if (Input()->IsPush(INPUT_KEY_ATTACK))
		{
			ChangeState(STATE_KEY_ATTACK1);
		}
	}

	CAttackBaseState::InputExecution();

}

void ActionGame::CRunAttack1State::End()
{
	CAttackBaseState::End();
	if (targetPos_ != nullptr)
	{
		targetPos_.reset();
	}
}

void ActionGame::CRunAttack1State::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CRunAttack1State::GetKey() const
{
	return STATE_KEY_RUN_ATTACK1;
}

