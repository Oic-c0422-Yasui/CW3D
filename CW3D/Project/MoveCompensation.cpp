#include "MoveCompensation.h"
#include "ActorObjectManager.h"

ActionGame::CMoveCompensationAction::CMoveCompensationAction(BaseParameter baseParam)
    : CAction()
    , param_()
	, type_(CHARA_TYPE::PLAYER)
{
	SettingMoveCompensationParam(baseParam);
}

bool ActionGame::CMoveCompensationAction::IsActorInSight(TransformPtr& outPos, float& outMinDistance, float sightAngle, float maxDistance)
{

	const auto selfPos = Transform()->GetPosition();
	bool isContain = false;
	float minDistance = maxDistance;

	//��]�A�j���[�V�����Ō����Ă�������̉�]�l�����Ȃ��\��������̂ŉ�]������̒l�ݒ�
	auto rotate = Transform()->GetRotate();
	if (Transform()->IsReverse())
	{
		rotate.y = MOF_ToRadian(90);
	}
	else
	{
		rotate.y = MOF_ToRadian(-90);
	}

	//�O���x�N�g��
	Vector3 fowardVec = MyUtil::ForwardVector(rotate);
	MyUtil::Normalize(fowardVec);



	//�G�΃A�N�^�[���擾
	auto actors = ActorObjectManagerInstance.GetHostilityActors(type_);
	for (auto actor : *actors)
	{
		//��\���Ȃ玟��
		if (!actor.lock()->IsShow())
		{
			continue;
		}

		//������ɃA�N�^�[�����邩�H
		const auto targetPos = actor.lock()->GetPosition();
		if (!MyUtil::IsRange(selfPos, fowardVec, targetPos,
			sightAngle, minDistance))
		{
			continue;
		}

		//�A�N�^�[�܂ł̋����v�Z
		float distance = MyUtil::Distance(selfPos, targetPos);
		minDistance = distance;
		outPos = actor.lock()->GetActor()->GetTransform();
		outMinDistance = (actor.lock()->GetCollider().Size.x +Collider()->GetCollider().Size.x);
		isContain = true;
	}

	return isContain;
}

bool ActionGame::CMoveCompensationAction::MoveCompensation(MoveCompensationParam& param)
{
	if (!param.isEnable)
	{
		return false;
	}
	if (!param.isActorInSight)
	{
		return false;
	}


	if (param.currentTime <= param.endTime)
	{
		const auto selfPos = Actor()->GetPosition();

		//�����v�Z
		const auto distance = MyUtil::DistanceSquare(selfPos, param.targetPos->GetPosition());
		const auto sqrMinDistance = std::pow(param.minDistance, 2);
		if (distance > sqrMinDistance)
		{
			//�ړ�
			auto movePos = MyUtil::Timer(selfPos, param.currentTime, param.targetPos->GetPosition(), param.endTime);
			Actor()->SetPosition(Vector3(movePos.x, selfPos.y, movePos.z));
		}
		else
		{
			//�ړ������������̂ŕ␳�I��
			param.isEnable = false;
			return false;
		}
	}
	else
	{
		//�ړ������������̂ŕ␳�I��
		param.isEnable = false;
		return true;
	}

	return false;
}

void ActionGame::CMoveCompensationAction::SettingMoveCompensationParam(const BaseParameter& param)
{
	param_.isEnable = param.isEnable;
	param_.isEnableYaxis = param.isEnableYaxis;
	param_.endTime = param.endTime;
	param_.maxDistance = param.maxDistance;
	param_.sightAngle = param.sightAngle;
	param_.currentTime = 0.0f;
	param_.isActorInSight = false;
	param_.minDistance = 0.0f;
	param_.se
	if (param_.targetPos) { param_.targetPos.reset(); }
}


void ActionGame::CMoveCompensationAction::Start()
{

}

void ActionGame::CMoveCompensationAction::Execution()
{
}

void ActionGame::CMoveCompensationAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::CMoveCompensationAction::GetKey() const
{
    return ActionKeyType();
}

void ActionGame::CMoveCompensationAction::SetType(CHARA_TYPE type) noexcept
{

}


bool ActionGame::CMoveCompensationAction::IsActorInSight(TransformPtr& outPos, float& offsetSize, float sightAngle, float maxDistance)
{
    return false;
}

bool ActionGame::CMoveCompensationAction::MoveCompensation(Parameter& param)
{
    return false;
}

void ActionGame::CMoveCompensationAction::SettingMoveCompensationParam(const BaseParameter& param)
{
}


