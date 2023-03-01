#include "EffectLoader.h"
#include "ResourceManager.h"
#include "EffectRenderer.h"

bool ActionGame::EffectLoader::Load()
{
	const auto& manager = EffectRendererInstance.GetManager();
	auto& instance = ResourceManager<Effekseer::EffectRef>::GetInstance();

	Effekseer::EffectRef effect = Effekseer::Effect::Create(manager, u"Effect/Laser01.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource("Effect", "AttackEffect1", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/sword.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource("Effect", "DamageEffect1", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/tuki.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource("Effect", "AttackEffect2", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/sandStome.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource("Effect", "SkillEffect1", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/Laser01.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource("Effect", "SkillEffect2", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/tornade.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource("Effect", "SkillEffect3", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/fire.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource("Effect", "SkillEffect4", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/drill.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource("Effect", "SkillEffect5", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/Track1.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource("Effect", "ClosedEffect", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/Clow1.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource("Effect", "AttackEffect3", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/A_Sylph2.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource("Effect", "EscapeEffect", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/MonsterRoar.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource("Effect", "RoarEffect", effect);

    return true;
}
