#include "JsonCreatorUtilities.h"


Vector3 MyUtil::CreateVector3(nlohmann::json& os)
{
    Vector3 value;

    os["x"].get_to(value.x);
    os["y"].get_to(value.y);
    os["z"].get_to(value.z);

    return value;
}
