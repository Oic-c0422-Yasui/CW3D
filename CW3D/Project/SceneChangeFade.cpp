#include "SceneChangeFade.h"

ActionGame::SceneChangeFade::SceneChangeFade(float endTime)
	: m_CurrentTime(0.0f)
	, m_EndTime(endTime)
{
}

void ActionGame::SceneChangeFade::Update()
{
	m_CurrentTime += CUtilities::GetFrameSecond();
	float rate = m_CurrentTime / m_EndTime;
	m_Alpha = (int)(255 * (1 - rate));
}

void ActionGame::SceneChangeFade::Render(ScenePtr& prev, ScenePtr& current)
{
	CRectangle rect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight());
	CGraphicsUtilities::RenderFillRect(rect, MOF_ARGB(m_Alpha, 0, 0, 0));
}

bool ActionGame::SceneChangeFade::IsEnd() const noexcept
{
	return m_CurrentTime >= m_EndTime;
}
