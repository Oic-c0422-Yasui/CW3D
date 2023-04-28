#include "IdleStateAI.h"

ActionGame::CIdleStateAI::CIdleStateAI(Vector3 vigilanceRange, Vector3 attackRange, int attackTiming)
	: CBaseStateAI()
	, isAttack_(false)
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
	isAttack_ = false;
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


	//�x���͈͓��ɓ����Ă�����ړ�
	if (IsInRange(vigilangeRange_, target->GetCollider()))
	{

		//�U���͈͓��ɓ����Ă�����U��
		if (IsInRange(attackRange_, target->GetCollider()))
		{
			if (!Input()->IsPush(INPUT_KEY_ATTACK) && CUtilities::Random(attackTiming_) == 0)
			{
				transform->SetReverse(target->GetPosition().x < transform->GetPosition().x ? true : false);
				Input()->SetKeyValue(INPUT_KEY_ATTACK, 1.0f);
				isAttack_ = true;
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
	else if (!IsInRange(5.0f,target->GetPosition()))
	{
		//�ړ�����
		InputMove(5.0f, target->GetPosition());
	}

}

void ActionGame::CIdleStateAI::End()
{
}
