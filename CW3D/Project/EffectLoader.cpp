#include "EffectLoader.h"
#include "ResourceManager.h"
#include "EffectRenderer.h"

bool ActionGame::EffectLoader::Load()
{
	//エフェクトマネージャー
	const auto& manager = EffectRendererInstance.GetManager();
	//リソース管理のインスタンス
	auto& instance = ResourceManager<Effekseer::EffectRef>::GetInstance();
	//リソースのタグ
	constexpr auto tag = "Effect";

	Effekseer::EffectRef effect = Effekseer::Effect::Create(manager, u"Effect/Laser01.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource(tag, "AttackEffect1", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/sword.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource(tag, "DamageEffect1", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/tuki.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource(tag, "AttackEffect2", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/sandStome.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource(tag, "SkillEffect1", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/Laser01.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource(tag, "SkillEffect2", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/tornade.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource(tag, "SkillEffect3", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/fire.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource(tag, "SkillEffect4", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/drill.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource(tag, "SkillEffect5", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/Track1.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource(tag, "ClosedEffect", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/Clow1.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource(tag, "AttackEffect3", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/A_Sylph2.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource(tag, "EscapeEffect", effect);

	effect = Effekseer::Effect::Create(manager, u"Effect/MonsterRoar.efk");
	if (effect == nullptr)
	{
		return false;
	}
	instance.AddResource(tag, "RoarEffect", effect);

    return true;
}
