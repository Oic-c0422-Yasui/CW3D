#include "ClearTermEnemyAllDeadText.h"

ClearTerm::CEnemyAllDeadText::CEnemyAllDeadText()
	: CClearTermText("“G‚ð‚·‚×‚Ä“|‚¹")
	, enemyCount_(0)
	, enemyMaxCount_(0)
	, descriptionPos_(1800,600)
	, clearTermPos_(1800,700)
{
}

void ClearTerm::CEnemyAllDeadText::Initialize()
{
	
}

void ClearTerm::CEnemyAllDeadText::Render()
{
	
	CGraphicsUtilities::RenderString(descriptionPos_.x, descriptionPos_.y,MOF_XRGB(255,255,255), description_);
	CGraphicsUtilities::RenderString(clearTermPos_.x, clearTermPos_.y, MOF_XRGB(255, 255, 255), "Žc‚è%d/%d", enemyCount_, enemyMaxCount_);
}
