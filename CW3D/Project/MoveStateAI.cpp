#include "MoveStateAI.h"

ActionGame::CMoveStateAI::CMoveStateAI(Vector3 vigilangeRange, Vector3 attackRange, int timing)
	: CBaseStateAI()
	, currentLostTime_(0)
	, isAttack_(false)
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
	currentLostTime_ = 0;
	isAttack_ = false;
}

void ActionGame::CMoveStateAI::Update()
{
	//�^�[�Q�b�g�擾
	const auto& target = CServiceLocator< CPlayer >::GetService();
	if (target->IsDead())
	{
		return;
	}

	//�A�N�^�[�擾
	const auto& transform = Actor()->GetTransform();

	//�x���͈͓��Ƀv���C���[�����Ȃ��Ȃ�ƃJ�E���g���Ĉ���ɒ�~
	if (!IsInRange(vigilangeRange_, target->GetCollider()))
	{

		currentLostTime_++;
		if (currentLostTime_ < 5)
		{
			Input()->SetKeyValue(INPUT_KEY_HORIZONTAL, transform->IsReverse() ? -1.0f : 1.0f);
		}
		//�v���C���[��5���ȏ㗣��Ă���ꍇ
		else if (!IsInRange(5.0f, target->GetPosition()))
		{
			//�ړ�����
			InputMove(-5.0f, target->GetPosition());
		}
		return;
	}
	else
	{
		currentLostTime_ = 0;
	}
	

	//�U���{�b�N�X
	if (IsInRange(attackRange_, target->GetCollider()))
	{
		if (CUtilities::Random(attackTiming_) == 0)
		{
			Input()->SetKeyValue(INPUT_KEY_ATTACK, 1.0f);
			isAttack_ = true;
		}
	}
	else
	{
		//�ړ�����
		InputMove(-5.0f, target->GetPosition());
	}

}
