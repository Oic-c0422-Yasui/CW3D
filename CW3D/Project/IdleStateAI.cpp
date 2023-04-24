#include "IdleStateAI.h"

ActionGame::CIdleStateAI::CIdleStateAI(Vector3 vigilanceRange, Vector3 attackRange, int attackTiming)
	: CStateAI()
	, isAttack(false)
	, vigilangeRange_(vigilanceRange)
	, attackRange_(attackRange)
	, attackTiming_(attackTiming)
{
}

void ActionGame::CIdleStateAI::RegisterKey()
{
	Input()->AddKey(INPUT_KEY_HORIZONTAL);
	Input()->AddKey(INPUT_KEY_VERTICAL);
	Input()->AddKey(INPUT_KEY_ATTACK);
}

void ActionGame::CIdleStateAI::Start()
{
	isAttack = false;
}

void ActionGame::CIdleStateAI::Update()
{
	//�^�[�Q�b�g�擾
	const auto& target = CServiceLocator< CPlayer >::GetService();
	if (target->IsDead())
	{
		return;
	}

	//�A�N�^�[�擾
	const auto& transform = Actor()->GetTransform();
	//�x���{�b�N�X
	CAABB collider;
	collider.SetPosition(transform->GetPosition());
	collider.Size = vigilangeRange_;

	//�����v�Z
	const Vector2 vec(transform->GetPosition().x - target->GetPosition().x, transform->GetPosition().z - target->GetPosition().z);
	const float length = sqrt(vec.x * vec.x + vec.y * vec.y);

	//�x���͈͓��ɓ����Ă�����ړ�
	if (CCollision::Collision(target->GetCollider(), collider))
	{
		collider.Size = attackRange_;
		//�U���͈͓��ɓ����Ă�����U��
		if (CCollision::Collision(target->GetCollider(), collider))
		{
			if (!Input()->IsPush(INPUT_KEY_ATTACK) && CUtilities::Random(attackTiming_) == 0)
			{
				transform->SetReverse(target->GetPosition().x < transform->GetPosition().x ? true : false);
				Input()->SetKeyValue(INPUT_KEY_ATTACK, 1.0f);
				isAttack = true;
			}
		}
		else
		{
			if (!Input()->IsPush(INPUT_KEY_HORIZONTAL) && !Input()->IsNegativePush(INPUT_KEY_HORIZONTAL))
			{
				Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
					target->GetPosition().x < transform->GetPosition().x ? -CUtilities::RandomFloat() : CUtilities::RandomFloat());
			}
			if (!Input()->IsPush(INPUT_KEY_VERTICAL) && !Input()->IsNegativePush(INPUT_KEY_VERTICAL) && CUtilities::Random(10) == 0)
			{
				Input()->SetKeyValue(INPUT_KEY_VERTICAL,
					CUtilities::Random(10) < 4 ? -CUtilities::RandomFloat() : CUtilities::RandomFloat());
			}
		}
	}
	//��~���Ƀ����_���œK���ɋt��������
	else if (CUtilities::Random(50) == 0)
	{
		Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
			transform->IsReverse() ? 1.0f : -1.0f);

	}
	//��~���Ƀ����_���œK���Ƀv���C���[��������
	else if (CUtilities::Random(50) == 0)
	{
		Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
			target->GetPosition().x < transform->GetPosition().x ? -1.0f : 1.0f);
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

}

void ActionGame::CIdleStateAI::End()
{
}
