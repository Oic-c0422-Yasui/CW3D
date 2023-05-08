#include "SpearAttackState.h"
#include "ParameterDefine.h"

ActionGame::CSpearAttackState::CSpearAttackState(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isStartCollide_(false)
{
}

void ActionGame::CSpearAttackState::Start()
{
	action_ = Actor()->GetAction<CAttack1Action>(GetKey());
	isStartCollide_ = false;

	SetArmorLevel(parameter_.armorLevel);
	CAttackBaseState::Start();

	action_->Start();
	auto& param = Actor()->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE_TIME);
	param = parameter_.CollideStartTime;
	//“–‚½‚è”»’è—p‚Ì’eì¬
	CreateShotAABB();
	CreateEffect();
}

void ActionGame::CSpearAttackState::Execution()
{
	for (auto& shot : shots_)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (currentTime_ >= parameter_.CollideStartTime && !isStartCollide_)
		{
			shot->SetEnableCollider(true);

		}
		if (currentTime_ > parameter_.ColliderEndTime)
		{
			if (shot->IsEnableCollider())
			{
				shot->SetEnableCollider(false);
			}
		}
	}
	for (auto& effect : effects_)
	{
		EffectControllerInstance.SetPosition(effect->GetHandle(), Actor()->GetPosition() + effect->GetOffset());
	}

	if (currentTime_ >= parameter_.CollideStartTime && !isStartCollide_)
	{
		
		isStartCollide_ = true;
	}
	if (currentTime_ >= parameter_.EndTime)
	{
		ChangeState(STATE_KEY_TIRED);
	}

	CAttackBaseState::Execution();
}

void ActionGame::CSpearAttackState::InputExecution()
{

	CAttackBaseState::InputExecution();
}

void ActionGame::CSpearAttackState::End()
{
	CAttackBaseState::End();
}

void ActionGame::CSpearAttackState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CSpearAttackState::GetKey() const
{
	return STATE_KEY_SPEAR_ATTACK;
}
