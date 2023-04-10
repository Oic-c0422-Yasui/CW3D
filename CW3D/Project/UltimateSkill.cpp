#include "UltimateSkill.h"
#include "ParameterDefine.h"

ActionGame::UltimateSkill::UltimateSkill(const ActorWeakPtr& actor)

	: CSkill()
	, m_ActorRef(actor)
	, m_MaxGaugeFlg(false)
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
	auto& currentGauge = m_ActorRef.lock()->GetParameterMap()->Get<CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	currentGauge -= m_UltSkillData->ExpendGauge.Get();
}

void ActionGame::UltimateSkill::Reset()
{
	CSkill::Reset();
	canUse_ = false;
	m_MaxGaugeFlg = false;
}

void ActionGame::UltimateSkill::Update()

{
	if (!canUse_.Get() && !isStart_)
	{
		auto& currentGauge = m_ActorRef.lock()->GetParameterMap()->Get<CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
		if (currentGauge >= m_UltSkillData->ExpendGauge.Get() && CT_ <= 0.0f)
		{
			canUse_ = true;
		}
	}
	if (!isStart_)
	{
		return;
	}
	CSkill::AddTimer();
	auto& currentGauge = m_ActorRef.lock()->GetParameterMap()->Get<CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	if (currentGauge >= m_UltSkillData->ExpendGauge.Get() && CT_ <= 0.0f)
	{
		CSkill::ResetFlg();
	}
}
