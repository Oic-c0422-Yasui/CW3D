#include "BaseAction.h"



ActionGame::CBaseAction::CBaseAction(BaseParameter baseParam)
	: CAction()
	, baseParam_(baseParam)
{
}

void ActionGame::CBaseAction::Start()
{
	PlayAnimation();
}

void ActionGame::CBaseAction::Execution()
{
}

void ActionGame::CBaseAction::End()
{
}

void ActionGame::CBaseAction::PlayAnimation()
{
	//メッシュのアニメーション変更
	AnimationState()->ChangeMotionByName(baseParam_.anim.name, baseParam_.anim.startTime, baseParam_.anim.speed,
		baseParam_.anim.tTime, baseParam_.anim.isLoop, MOTIONLOCK_OFF, TRUE);
}

void ActionGame::CBaseAction::PlayAnimation(char* name, float startTime, float speed, float tTime, bool isLoop)
{
	//メッシュのアニメーション変更
	AnimationState()->ChangeMotionByName(name, startTime, speed,
		tTime, isLoop, MOTIONLOCK_OFF, TRUE);
}

void ActionGame::CBaseAction::SetRotation(float rotateTime)
{
	auto& vel = Velocity();
	float rotateY = Transform()->GetRotateY();
	//反転方向に回転させる
	if (Transform()->IsReverse())
	{
		vel->SetRotateY(rotateY, MOF_ToRadian(90), rotateTime);
	}
	else
	{
		vel->SetRotateY(rotateY, MOF_ToRadian(-90), rotateTime);
	}
}