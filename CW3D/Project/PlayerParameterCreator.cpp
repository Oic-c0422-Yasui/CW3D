#include "PlayerParameterCreator.h"
#include "ParameterDefine.h"

bool ActionGame::PlayerParameterCreator::Create(const AnyParameterMapPtr& param)
{

	param->Add<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_HP, 250);
	param->Add<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_MAX_HP, 250);
	param->Add<int>(PARAMETER_KEY_DAMAGE, 0);
	param->Add<int>(PARAMETER_KEY_ATTACK, 25);
	param->Add<float>(PARAMETER_KEY_INVINCIBLE_TIME, 0.0f);
	param->Add<ActionGame::CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE, 0);
	param->Add<ActionGame::CReactiveParameter<float>>(PARAMETER_KEY_MAX_ULTGAUGE, 100.0f);
	param->Add<bool>(PARAMETER_KEY_ESCAPE, false);
	param->Add<BYTE>(PARAMETER_KEY_ARMORLEVEL, 1);
	param->Add<BYTE>(PARAMETER_KEY_DEFAULT_ARMORLEVEL, 1);
	return true;
}