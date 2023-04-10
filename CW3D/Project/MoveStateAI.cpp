#include "MoveStateAI.h"

ActionGame::CMoveStateAI::CMoveStateAI(Vector3 vigilangeRange, Vector3 attackRange, int timing)
	: CStateAI()
	, currentLostTime(0)
	, isAttack(false)
	, attackRange_(attackRange)
	, vigilangeRange_(vigilangeRange)
	, attackTiming_(timing)
{
}

void ActionGame::CMoveStateAI::RegisterKey()
{
	Input()->AddKey(INPUT_KEY_HORIZONTAL);
	Input()->AddKey(INPUT_KEY_VERTICAL);
	Input()->AddKey(INPUT_KEY_ATTACK);
}

void ActionGame::CMoveStateAI::Start()
{
	currentLostTime = 0;
	isAttack = false;
}

void ActionGame::CMoveStateAI::Update()
{
	//�v���C���[�擾
	const auto& target = CServiceLocator< CPlayer >::GetService();
	const auto& transform = Actor()->GetTransform();
	//�x���{�b�N�X
	CAABB collider;
	collider.SetPosition(transform->GetPosition());
	collider.Size = vigilangeRange_;
	
	//�x���͈͓��Ƀv���C���[�����Ȃ��Ȃ�ƃJ�E���g���Ĉ���ɒ�~
	if (!CCollision::Collision(target->GetCollider(), collider))
	{
		//�����v�Z
		Vector2 vec(transform->GetPosition().x - target->GetPosition().x, transform->GetPosition().z - target->GetPosition().z);
		float length = sqrt(vec.x * vec.x + vec.y * vec.y);

		currentLostTime++;
		if (currentLostTime < 5)
		{
			Input()->SetKeyValue(INPUT_KEY_HORIZONTAL, transform->IsReverse() ? -1.0f : 1.0f);
		}
		//�v���C���[��5���ȏ㗣��Ă���ꍇ
		else if (length > 5.0f)
		{
			//�ړ�����
			float sx = target->GetPosition().x - transform->GetPosition().x;
			float sz = target->GetPosition().z - transform->GetPosition().z;
			sx /= 5.0f;
			sz /= 5.0f;
			sx = ((sx < -1.0f) ? -1.0f : ((sx > 1.0f) ? 1.0f : sx));
			sz = -((sz < -1.0f) ? -1.0f : ((sz > 1.0f) ? 1.0f : sz));
			Input()->SetKeyValue(INPUT_KEY_HORIZONTAL, sx);
			Input()->SetKeyValue(INPUT_KEY_VERTICAL, sz);
		}
		return;
	}
	else
	{
		currentLostTime = 0;
	}
	//�ړ�����
	float sx = target->GetPosition().x - transform->GetPosition().x;
	float sz = target->GetPosition().z - transform->GetPosition().z;
	sx /= 5.0f;
	sz /= 5.0f;
	sx = ((sx < -1.0f) ? -1.0f : ((sx > 1.0f) ? 1.0f : sx));
	sz = -((sz < -1.0f) ? -1.0f : ((sz > 1.0f) ? 1.0f : sz));

	//�U���{�b�N�X
	collider.Size = attackRange_;
	if (CCollision::Collision(target->GetCollider(), collider))
	{
		if (CUtilities::Random(attackTiming_) == 0)
		{
			Input()->SetKeyValue(INPUT_KEY_ATTACK, 1.0f);
			isAttack = true;
		}
	}
	else
	{
		Input()->SetKeyValue(INPUT_KEY_HORIZONTAL, sx);
		Input()->SetKeyValue(INPUT_KEY_VERTICAL, sz);
	}

}
