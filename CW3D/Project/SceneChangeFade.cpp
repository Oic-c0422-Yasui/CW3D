#include "SceneChangeFade.h"

ActionGame::SceneChangeFade::SceneChangeFade(float startTime, float durationTime, float endTime)
	: m_CurrentTime(0.0f)
	, m_StartTime(startTime)
	, m_DurationTime(durationTime)
	, m_EndTime(endTime)
	, m_HalfPointFlg(false)
	, m_Alpha(0)
{
	m_AllTime = m_StartTime + m_DurationTime + m_EndTime;
}

void ActionGame::SceneChangeFade::Update()
{
	m_CurrentTime += CUtilities::GetFrameSecond();
	if (!IsHalfPoint())
	{
		float rate = m_CurrentTime / m_StartTime;
		//フェードイン
		m_Alpha = (int)(255 * rate);
	}
	else if(m_CurrentTime >= m_StartTime + m_DurationTime)
	{
		float rate = m_CurrentTime / m_AllTime;
		//フェードアウト
		m_Alpha = (int)(255 * (1 - rate));
	}
}

void ActionGame::SceneChangeFade::Render(ScenePtr& prev, ScenePtr& current)
{
	CRectangle rect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight());
	CGraphicsUtilities::RenderFillRect(rect, MOF_ARGB(m_Alpha, 0, 0, 0));
}

bool ActionGame::SceneChangeFade::IsEnd() const noexcept
{
	return m_CurrentTime >= m_AllTime;
}

bool ActionGame::SceneChangeFade::IsHalfPoint() const noexcept
{
	return m_CurrentTime >= m_StartTime;
}
