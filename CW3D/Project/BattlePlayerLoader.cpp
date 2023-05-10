#include "BattlePlayerLoader.h"
#include "PlayerActionCreator.h"
#include "PlayerStateCreator.h"
#include "PlayerParameterCreator.h"
#include "PlayerSkillCreator.h"


bool ActionGame::BattlePlayerLoader::Load(const PlayerPtr& player, const Input::InputPtr& input)
{
    auto action = std::make_shared<PlayerActionCreator>();
    auto state = std::make_shared<PlayerStateCreator>();
    auto param = std::make_shared<PlayerParameterCreator>();
    auto skill = std::make_shared<PlayerSkillCreator>();

    if (!player->Load(action, state, param,
                      input, skill, STATE_KEY_STARTPOSE))
    {
        return false;
    }

    return true;
}
