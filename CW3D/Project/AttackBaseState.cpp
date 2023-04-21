#include "AttackBaseState.h"
#include "ParameterDefine.h"
#include "ActorObjectManager.h"
#include "AnimationUtilities.h"

using namespace ActionGame;

ActionGame::CAttackBaseState::CAttackBaseState()
	: CState()
	, currentTime_(0.0f)
	, isNextInput_(false)
	, moveCompentionParam_()
{
}


void ActionGame::CAttackBaseState::ReleaseShot()
{
	for (auto& shot : shots_)
	{
		shot->SetShow(false);
		shot.reset();
	}
	shots_.clear();
}

void ActionGame::CAttackBaseState::ReleaseEffect()
{
	for (auto& effect : effects_)
	{
		effect->SetStop(true);
		effect.reset();
	}
	effects_.clear();
}

const ShotAABB& ActionGame::CAttackBaseState::GetCreateShotStatusAABB()
{
	assert(false);
	static const ShotAABB box = {};
	return box;
}

const ShotOBB& ActionGame::CAttackBaseState::GetCreateShotStatusOBB()
{
	assert(false);
	static const ShotOBB box = {};
	return box;
}

const ShotSphere& ActionGame::CAttackBaseState::GetCreateShotStatusSphere()
{
	assert(false);
	static const ShotSphere sphere = {};
	return sphere;
}

const EffectCreateParameter& ActionGame::CAttackBaseState::GetCreateEffectStatus()
{
	assert(false);
	static const EffectCreateParameter param = {};
	return param;
}

void ActionGame::CAttackBaseState::CreateShotAABB()
{
	//攻撃力取得
	auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
	ShotAABB status = GetCreateShotStatusAABB();
	status.damage += attack;
	status.type = Actor()->GetType();
	status.parentID = Actor()->GetID();
	//アクターが反転状態なら向きを反転
	if (Actor()->IsReverse())
	{
		status.offset.x *= -1;
	}
	status.direction = GetKnockBack();

	shots_.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), status));
}

void ActionGame::CAttackBaseState::CreateShotOBB()
{
	//攻撃力取得
	auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
	ShotOBB status = GetCreateShotStatusOBB();
	status.damage += attack;
	status.type = Actor()->GetType();
	status.parentID = Actor()->GetID();
	//アクターが反転状態なら向きを反転
	if (Actor()->IsReverse())
	{
		status.offset.x *= -1;
		status.angle.z *= -1;
	}
	status.direction = GetKnockBack();

	shots_.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), status));
}

void ActionGame::CAttackBaseState::CreateShotSphere()
{
	auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
	ShotSphere status = GetCreateShotStatusSphere();
	status.damage += attack;
	status.type = Actor()->GetType();
	status.parentID = Actor()->GetID();
	//アクターが反転状態なら向きを反転
	if (Actor()->IsReverse())
	{
		status.offset.x *= -1;
	}
	status.direction = GetKnockBack();
	shots_.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), status));
}

void ActionGame::CAttackBaseState::CreateEffect()
{
	EffectCreateParameter status = GetCreateEffectStatus();

	//アクターが反転状態なら向きを反転
	if (Actor()->IsReverse())
	{
		status.offset.x *= -1;
		if (status.rotate.y == MOF_ToRadian(360))
		{
			status.rotate.y = MOF_ToRadian(180);
		}
		else
		{
			status.rotate.y *= -1;
		}
	}
	effects_.push_back(EffectControllerInstance.Play(status.name, Actor()->GetPosition(), status));
}

bool ActionGame::CAttackBaseState::IsActorInSight(TransformPtr& outPos,float& outMinDistance,float sightAngle,float maxDistance)
{

	const auto selfPos = Actor()->GetPosition();
	bool isContain = false;
	float minDistance = maxDistance;

	//回転アニメーションで向いている方向の回転値が取れない可能性があるので回転完了後の値設定
	auto rotate = Actor()->GetRotate();
	if (Actor()->IsReverse())
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
	auto actors = ActorObjectManagerInstance.GetHostilityActors(Actor()->GetType());
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
		outMinDistance = (actor.lock()->GetCollider().Size.x + Actor()->GetCollider().Size.x) * 1.0f;
		isContain = true;
	}

	return isContain;
}

bool ActionGame::CAttackBaseState::MoveCompensation(MoveCompensationParam& param)
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

void ActionGame::CAttackBaseState::SettingMoveCompensationParam(const BaseCompensationParam& param)
{
	auto& mParam = moveCompentionParam_;
	mParam.isEnable = param.isEnable;
	mParam.endTime = param.endTime;
	mParam.maxDistance = param.maxDistance;
	mParam.sightAngle = param.sightAngle;
	mParam.currentTime = 0.0f;
	mParam.isActorInSight = false;
	mParam.minDistance = 0.0f;
	if (mParam.targetPos) { mParam.targetPos.reset(); }
}



void ActionGame::CAttackBaseState::Start()
{
	currentTime_ = 0.0f;
	isNextInput_ = false;
	if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
	{
		Actor()->SetReverse(false);
	}
	else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
	{
		Actor()->SetReverse(true);
	}

	//移動補正が有効ならパラメータを設定
	auto& param = moveCompentionParam_;
	if (param.isEnable)
	{
		param.isActorInSight = IsActorInSight(param.targetPos, param.minDistance, param.sightAngle, param.maxDistance);
	}
	
}

void ActionGame::CAttackBaseState::Execution()
{
	//移動補正
	if(moveCompentionParam_.targetPos)
	MoveCompensation(moveCompentionParam_);

	currentTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
}

void ActionGame::CAttackBaseState::InputExecution() {

	float scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	
	//タイムスケールが0以下の場合、入力を受け付けない
	if (scale <= 0.0f)
	{
		return;
	}
	//対応したスキルのボタンが押されていたらそのスキルのステートに移動
	for (int i = 0; i < Actor()->GetSkillController()->GetCount(); i++)
	{
		SKillPtr skill = Actor()->GetSkillController()->GetSkill(i);
		if (!skill->CanUseSkill() || skill->GetState() == NULL || skill->GetFlyState() == NULL)
		{
			continue;
		}
		if (Input()->IsPush(skill->GetButton()))
		{

			skill->Start();
			if (Actor()->GetPositionY() > 0)
			{
				ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetFlyState());
			}
			else
			{
				ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetState());
			}
			break;
		}
	}

}

void ActionGame::CAttackBaseState::End() 
{
	ReleaseShot();
	ReleaseEffect();
	auto param = Actor()->GetParameterMap();
	auto& armorLevel =  param->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	armorLevel = param->Get<BYTE>(PARAMETER_KEY_DEFAULT_ARMORLEVEL);
	if (moveCompentionParam_.targetPos)
	{
		moveCompentionParam_.targetPos.reset();
	}
}
