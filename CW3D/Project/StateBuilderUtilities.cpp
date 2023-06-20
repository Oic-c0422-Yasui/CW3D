#include "StateBuilderUtilities.h"

using namespace ActionGame;



GravityScale ActionGame::CreateGravityScale(nlohmann::json& os)
{
    GravityScale value;

    os["isEnable"].get_to(value.isEnable);
    os["time"].get_to(value.time);
    os["startScale"].get_to(value.startScale);
    os["endScale"].get_to(value.endScale);

    return value;
}


EffectCreateParameter ActionGame::CreateEffectParam(nlohmann::json& os)
{
    EffectCreateParameter value;
    os["name"].get_to(value.name);
    os["speed"].get_to(value.speed);

    value.offset = MyUtil::CreateVector3(os["offset"]);
    value.scale = MyUtil::CreateVector3(os["scale"]);
    value.rotate = MyUtil::CreateVector3(os["rotate"]);


    return EffectCreateParameter();
}

void ActionGame::CreateShotBaseParam(nlohmann::json& os, ShotCreateParameter& value)
{
    os["damage"].get_to(value.damage);
    os["isEnableCollider"].get_to(value.isEnableCollider);
    os["armorBreakLevel"].get_to(value.armorBreakLevel);
    os["recieveUltGauge"].get_to(value.recieveUltGauge);

    value.offset = MyUtil::CreateVector3(os["offset"]);
    value.knockBack = MyUtil::CreateVector3(os["knockBack"]);
    value.damageEffect = std::make_shared<EffectCreateParameter>(
        CreateEffectParam(os["damageEffect"]));
    value.gravity = CreateGravityScale(os["gravityScale"]);
}

ShotAABB ActionGame::CreateAABBParam(nlohmann::json& os)
{
    ShotAABB value;

    CreateShotBaseParam(os, value);

    value.size = MyUtil::CreateVector3(os["size"]);

    return value;
}

ShotOBB ActionGame::CreateOBBParam(nlohmann::json& os)
{
    ShotOBB value;

    CreateShotBaseParam(os, value);

    value.size = MyUtil::CreateVector3(os["size"]);
    value.angle = MyUtil::CreateVector3(os["angle"]);

    return value;
}

ShotSphere ActionGame::CreateSphereParam(nlohmann::json& os)
{
    ShotSphere value;

    CreateShotBaseParam(os, value);

    os["radius"].get_to(value.Radius);

    return ShotSphere();
}


