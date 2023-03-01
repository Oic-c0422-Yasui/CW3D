#include "ZombieParameterCreator.h"

bool ActionGame::ZombieParameterCreator::Create(const AnyParameterMapPtr& param)
{
	param->Add<CReactiveParameter<int>>(PARAMETER_KEY_HP, 800);
	param->Add<CReactiveParameter<int>>(PARAMETER_KEY_MAX_HP, 800);
	param->Add<int>(PARAMETER_KEY_DAMAGE, 0);
	param->Add<int>(PARAMETER_KEY_ATTACK, 10);
	param->Add<float>(PARAMETER_KEY_INVINCIBLE, 0.0f);
	param->Add<CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE, 0);
	param->Add<CReactiveParameter<float>>(PARAMETER_KEY_MAX_ULTGAUGE, 100.0f);
	param->Add<bool>(PARAMETER_KEY_ESCAPE, false);
	param->Add<CReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP, false);
	param->Add<BYTE>(PARAMETER_KEY_ARMORLEVEL, 1);
	param->Add<BYTE>(PARAMETER_KEY_DEFAULT_ARMORLEVEL, 1);

	return true;
}
