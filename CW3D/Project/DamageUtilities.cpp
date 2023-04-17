#include "DamageUtilities.h"

uint32_t MyUtil::CalculateAtk(uint32_t baseAtk, uint32_t skillAtk)
{
    uint32_t atk;
    atk = baseAtk * (skillAtk * 0.01f);
    return atk;
}
