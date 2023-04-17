#include "UltimateSkill.h"
#include "ParameterDefine.h"

ActionGame::UltimateSkill::UltimateSkill(const ActorWeakPtr& actor)

	: CSkill()
	, actorRef_(actor)
	, isMaxGauge_(false)
{
}

ActionGame::UltimateSkill::~UltimateSkill()
{
}

void ActionGame::UltimateSkill::Create(const std::string& key, const std::string& inputKey, const std::string& texName, char* state, char* flyState)
{
	CSkill::Create(key, inputKey, texName, state, flyState);
	canUse_ = false;
}

void ActionGame::UltimateSkill::Start()
{
	CSkill::Start();
	auto& currentGauge = actorRef_.lock()->GetParameterMap()->Get<CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	currentGauge -= ultSkillData_->ExpendGauge.Get();
}

void ActionGame::UltimateSkill::Reset()
{
	CSkill::Reset();
	canUse_ = false;
	isMaxGauge_ = false;
}

void ActionGame::UltimateSkill::Update()

{
	if (!canUse_.Get() && !isStart_)
	{
		auto& currentGauge = actorRef_.lock()->GetParameterMap()->Get<CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
		if (currentGauge >= ultSkillData_->ExpendGauge.Get() && CT_ <= 0.0f)
		{
			canUse_ = true;
		}
	}
	if (!isStart_)
	{
		return;
	}
	CSkill::AddTimer();
	auto& currentGauge = actorRef_.lock()->GetParameterMap()->Get<CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	if (currentGauge >= ultSkillData_->ExpendGauge.Get() && CT_ <= 0.0f)
	{
		CSkill::ResetFlg();
	}
}
