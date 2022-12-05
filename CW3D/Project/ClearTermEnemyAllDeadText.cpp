#include "ClearTermEnemyAllDeadText.h"

ActionGame::ClearTermEnemyAllDeadText::ClearTermEnemyAllDeadText()
	: ClearTermText("“G‚ð‚·‚×‚Ä“|‚¹")
	, m_EnemyCount(0)
	, m_EnemyMaxCount(0)
	, m_DescriptionPos(1800,600)
	, m_ClearTermPos(1800,700)
{
}

void ActionGame::ClearTermEnemyAllDeadText::Initialize()
{
	
}

void ActionGame::ClearTermEnemyAllDeadText::Render()
{
	
	CGraphicsUtilities::RenderString(m_DescriptionPos.x, m_DescriptionPos.y,MOF_XRGB(255,255,255), m_Description);
	CGraphicsUtilities::RenderString(m_ClearTermPos.x, m_ClearTermPos.y, MOF_XRGB(255, 255, 255), "Žc‚è%d/%d", m_EnemyCount, m_EnemyMaxCount);
}
