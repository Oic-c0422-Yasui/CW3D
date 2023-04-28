#include "BaseStateAI.h"
#include "Collision.h"
#include "VectorUtilities.h"

ActionGame::CBaseStateAI::CBaseStateAI()
	:CStateAI()
{
}


bool ActionGame::CBaseStateAI::IsInRange(const Vector3& size, const CAABB& target)
{
	//�A�N�^�[�擾
	const auto& pos = Actor()->GetPosition();
	//�x���{�b�N�X
	CAABB collider(pos, size);
     
    return CCollision::Collision(target, collider);
}

bool ActionGame::CBaseStateAI::IsInRange(float distance, const Vector3& target)
{
	
	return MyUtil::DistanceSquare(Actor()->GetPosition(), target) <= std::pow(distance,2);
}

void ActionGame::CBaseStateAI::InputMove(float distance, const Vector3& target)
{
	//�ړ�����
	float sx = Actor()->GetPosition().x - target.x;
	float sz = Actor()->GetPosition().z - target.z;
	sx /= distance;
	sz /= distance;
	sx = ((sx < -1.0f) ? -1.0f : ((sx > 1.0f) ? 1.0f : sx));
	sz = -((sz < -1.0f) ? -1.0f : ((sz > 1.0f) ? 1.0f : sz));
	Input()->SetKeyValue(INPUT_KEY_HORIZONTAL, sx);
	Input()->SetKeyValue(INPUT_KEY_VERTICAL, sz);
}

float ActionGame::CBaseStateAI::GetDistance(const Vector3& target)
{
	//�����v�Z
	return MyUtil::Distance(Actor()->GetPosition(), target);
}

