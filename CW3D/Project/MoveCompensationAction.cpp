#include "MoveCompensationAction.h"
#include "ActorObjectManager.h"

ActionGame::CMoveCompensationAction::CMoveCompensationAction(BaseParameter baseParam)
    : CAction()
    , param_()
	, saveParam_()
	, currentTime_(0.0f)
{
	SettingMoveCompensationParam(baseParam);
}

void ActionGame::CMoveCompensationAction::Start()
{
	param_ = saveParam_;

	//移動補正が有効ならパラメータを設定
	if (param_.isEnable)
	{
		param_.isActorInSight = IsActorInSight(param_.targetPos, param_.minDistance,
			param_.type, param_.sightAngle, param_.maxDistance);
	}
}

void ActionGame::CMoveCompensationAction::Execution()
{
	if (!param_.targetPos)
	{
		return;
	}
	param_.currentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(param_.type);

	//移動補正
	MoveCompensation(param_);
}

void ActionGame::CMoveCompensationAction::End()
{
	if (param_.targetPos)
	{
		param_.targetPos.reset();
	}
}

const ActionGame::ActionKeyType ActionGame::CMoveCompensationAction::GetKey() const
{
	return STATE_KEY_MOVECOMPENSATION;
}



void ActionGame::CMoveCompensationAction::Move(Vector3 pos)
{
	Transform()->SetPosition(pos);
}

bool ActionGame::CMoveCompensationAction::IsActorInSight(TransformPtr& outPos, float& outMinDistance,CHARA_TYPE type, float sightAngle, float maxDistance)
{

	const auto selfPos = Transform()->GetPosition();
	bool isContain = false;
	float minDistance = maxDistance;

	//回転アニメーションで向いている方向の回転値が取れない可能性があるので回転完了後の値設定
	auto rotate = Transform()->GetRotate();
	rotate.y = MOF_ToRadian(90);
	if (!Transform()->IsReverse())
	{
		rotate.y *= -1;
	}

	//前方ベクトル
	Vector3 fowardVec = MyUtil::ForwardVector(rotate);
	MyUtil::Normalize(fowardVec);



	//敵対アクターを取得
	auto actors = ActorObjectManagerInstance.GetHostilityActors(type);
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
		param_.targetPos = actor.lock()->GetActor()->GetTransform();

		auto size = actor.lock()->GetCollider().Size.x + Collider()->GetSize().x;
		param_.minDistance = size;
		isContain = true;
	}

	if (isContain)
	{
		param_.fixedTargetPos = param_.targetPos->GetPosition();
	}

	return isContain;
}

bool ActionGame::CMoveCompensationAction::MoveCompensation(Parameter& param)
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

		//距離計算
		const auto selfPos = Transform()->GetPosition();

		const auto distance = param.isFixedPos ? MyUtil::DistanceSquare(selfPos, param.fixedTargetPos)
											   : MyUtil::DistanceSquare(selfPos, param.targetPos->GetPosition());
		const int square = 2;
		const auto sqrMinDistance = std::pow(param.minDistance, square);
		if (distance > sqrMinDistance)
		{
			//移動
			auto movePos = MyUtil::Timer(selfPos, param.currentTime, param.targetPos->GetPosition(), param.endTime);
			//Y軸も移動するか？
			if (param.isEnableYaxis)
			{
				Move(Vector3(movePos.x, movePos.y, movePos.z));
			}
			else
			{
				Move(Vector3(movePos.x, selfPos.y, movePos.z));
			}
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
	saveParam_.isEnable		 = param.isEnable;
	saveParam_.isEnableYaxis = param.isEnableYaxis;
	saveParam_.isFixedPos	 = param.isFixedPos;
	saveParam_.endTime		 = param.endTime;
	saveParam_.maxDistance	 = param.maxDistance;
	saveParam_.sightAngle	 = param.sightAngle;
	saveParam_.type			 = param.type;
	saveParam_.currentTime   = 0.0f;
	saveParam_.minDistance   = 0.0f;
	saveParam_.fixedTargetPos = Vector3(0, 0, 0);
	saveParam_.isActorInSight = false;
	if (saveParam_.targetPos) { saveParam_.targetPos.reset(); }
}






