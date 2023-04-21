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

	//回転アニメーションで向いている方向の回転値が取れない可能性があるので回転完了後の値設定
	auto rotate = Transform()->GetRotate();
	if (Transform()->IsReverse())
	{
		rotate.y = MOF_ToRadian(90);
	}
	else
	{
		rotate.y = MOF_ToRadian(-90);
	}

	//前方ベクトル
	Vector3 fowardVec = MyUtil::ForwardVector(rotate);
	MyUtil::Normalize(fowardVec);



	//敵対アクターを取得
	auto actors = ActorObjectManagerInstance.GetHostilityActors(type_);
	for (auto actor : *actors)
	{
		//非表示なら次へ
		if (!actor.lock()->IsShow())
		{
			continue;
		}

		//視野内にアクターがいるか？
		const auto targetPos = actor.lock()->GetPosition();
		if (!MyUtil::IsRange(selfPos, fowardVec, targetPos,
			sightAngle, minDistance))
		{
			continue;
		}

		//アクターまでの距離計算
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

		//距離計算
		const auto distance = MyUtil::DistanceSquare(selfPos, param.targetPos->GetPosition());
		const auto sqrMinDistance = std::pow(param.minDistance, 2);
		if (distance > sqrMinDistance)
		{
			//移動
			auto movePos = MyUtil::Timer(selfPos, param.currentTime, param.targetPos->GetPosition(), param.endTime);
			Actor()->SetPosition(Vector3(movePos.x, selfPos.y, movePos.z));
		}
		else
		{
			//移動が完了したので補正終了
			param.isEnable = false;
			return false;
		}
	}
	else
	{
		//移動が完了したので補正終了
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


