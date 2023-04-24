#include "VectorUtilities.h"


float MyUtil::LengthSquare(const Vector3& vec)
{
    return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float MyUtil::Length(const Vector3& vec)
{
    return std::sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float MyUtil::Dot(const Vector3& vec1, const Vector3& vec2)
{
    return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

void MyUtil::Normalize(Vector3& outVec)
{
    float distance = Length(outVec);
    if (distance > 0)
    {
        distance = 1 / distance;
    }
    else
    {
        distance = 0;
    }
    outVec.x = outVec.x * distance;
    outVec.y = outVec.y * distance;
    outVec.z = outVec.z * distance;

}



bool MyUtil::IsRange(const Vector3& selfPos, const Vector3& selfDir, const Vector3& targetPos,float sightAngle,float maxDistance)
{
    //ターゲットまでの向き
    auto targetDir = targetPos - selfPos;
    //ターゲットまでの距離
    float targetDistance = LengthSquare(targetDir);
    float distance = std::pow(maxDistance, 2);

    //ターゲットの方向正規化
    Normalize(targetDir);

    //ハーフコサイン
    float cosHarf = std::cos(MOF_ToHarfRadian(sightAngle));
    
    float innerProduct = Dot(selfDir, targetDir);

    return innerProduct > cosHarf && targetDistance < distance;
}

float MyUtil::Distance(const Vector3& vec1, const Vector3& vec2)
{
    return Length(vec1 - vec2);
}

float MyUtil::DistanceSquare(const Vector3& vec1, const Vector3& vec2)
{
    return LengthSquare(vec1 - vec2);
}

Vector3 MyUtil::ForwardVector(const Vector3& angle)
{
    auto vec = -VectorDirection::Forward();
    //角度から前方のベクトルを求める
    CMatrix33 mat;
    mat.RotationZXY(angle);
    vec *= mat;

    return vec;
}