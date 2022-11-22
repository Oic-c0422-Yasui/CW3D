#include "ClearTermEnemyAllDeadText.h"

Sample::ClearTermEnemyAllDeadText::ClearTermEnemyAllDeadText()
	: ClearTermText("敵をすべて倒せ")
	, m_EnemyCount(0)
	, m_EnemyMaxCount(0)
	, m_DescriptionPos(1800,600)
	, m_ClearTermPos(1800,700)
{
}

void Sample::ClearTermEnemyAllDeadText::Initialize()
{
	
}

void Sample::ClearTermEnemyAllDeadText::Render()
{
	
	CGraphicsUtilities::RenderString(m_DescriptionPos.x, m_DescriptionPos.y,MOF_XRGB(255,255,255), m_Description);
	CGraphicsUtilities::RenderString(m_ClearTermPos.x, m_ClearTermPos.y, MOF_XRGB(255, 255, 255), "残り%d/%d", m_EnemyCount, m_EnemyMaxCount);
}
