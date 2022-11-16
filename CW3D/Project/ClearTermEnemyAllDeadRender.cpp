#include "ClearTermEnemyAllDeadRender.h"

Sample::ClearTermEnemyAllDeadRender::ClearTermEnemyAllDeadRender()
	: m_EnemyCount(0)
	, m_EnemyMaxCount(0)
{
}

void Sample::ClearTermEnemyAllDeadRender::Initialize()
{
	m_Description = "�G�̂����";
}

void Sample::ClearTermEnemyAllDeadRender::Render()
{
	CGraphicsUtilities::RenderString(1800, 500, MOF_XRGB(255, 255, 255), "�˔j����");
	CGraphicsUtilities::RenderString(1800, 600,MOF_XRGB(255,255,255), m_Description);
	CGraphicsUtilities::RenderString(1800, 700, MOF_XRGB(255, 255, 255), "�c��%d/%d", m_EnemyCount, m_EnemyMaxCount);
}
