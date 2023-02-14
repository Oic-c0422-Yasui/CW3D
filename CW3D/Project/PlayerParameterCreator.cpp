#include "PlayerParameterCreator.h"
#include "ParameterDefine.h"

bool ActionGame::PlayerParameterCreator::Create(const AnyParameterMapPtr& param)
{

	param->Add<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_HP, 120);
	param->Add<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_MAX_HP, 120);
	param->Add<int>(PARAMETER_KEY_DAMAGE, 0);
	param->Add<int>(PARAMETER_KEY_ATTACK, 25);
	param->Add<float>(PARAMETER_KEY_INVINCIBLE, 0.0f);
	param->Add<ActionGame::ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE, 0);
	param->Add<ActionGame::ReactiveParameter<float>>(PARAMETER_KEY_MAX_ULTGAUGE, 100.0f);
	param->Add<bool>(PARAMETER_KEY_ESCAPE, false);
	param->Add<bool>(PARAMETER_KEY_THROUGH_COLLISION, false);
	param->Add<BYTE>(PARAMETER_KEY_ARMORLEVEL, 1);
	param->Add<BYTE>(PARAMETER_KEY_DEFAULT_ARMORLEVEL, 1);
	return true;
}
