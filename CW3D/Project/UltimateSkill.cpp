#include "UltimateSkill.h"
#include "ParameterDefine.h"

ActionGame::UltimateSkill::UltimateSkill(const ActorWeakPtr& actor)

	: Skill()
	, m_ActorRef(actor)
	, m_MaxGaugeFlg(false)
{
}

ActionGame::UltimateSkill::~UltimateSkill()
{
}

void ActionGame::UltimateSkill::Create(const std::string& key, const std::string& inputKey, const std::string& texName, char* state, char* flyState)
{
	Skill::Create(key, inputKey, texName, state, flyState);
	m_CanUseFlg = false;
}

void ActionGame::UltimateSkill::Start()
{
	Skill::Start();
	auto& currentGauge = m_ActorRef.lock()->GetParameterMap()->Get<CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	currentGauge -= m_UltSkillData->ExpendGauge.Get();
}

void ActionGame::UltimateSkill::Reset()
{
	Skill::Reset();
	m_CanUseFlg = false;
	m_MaxGaugeFlg = false;
}

void ActionGame::UltimateSkill::Update()

{
	if (!m_CanUseFlg.Get() && !isStart_)
	{
		auto& currentGauge = m_ActorRef.lock()->GetParameterMap()->Get<CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
		if (currentGauge >= m_UltSkillData->ExpendGauge.Get() && m_CT <= 0.0f)
		{
			m_CanUseFlg = true;
		}
	}
	if (!isStart_)
	{
		return;
	}
	Skill::AddTimer();
	auto& currentGauge = m_ActorRef.lock()->GetParameterMap()->Get<CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	if (currentGauge >= m_UltSkillData->ExpendGauge.Get() && m_CT <= 0.0f)
	{
		Skill::ResetFlg();
	}
}
