#include "Actor.h"

ActionGame::Actor::Actor()
	: enable_shared_from_this()
	, transform_(std::make_shared<CTransform>())
	, velocity_(std::make_shared<CVelocity>())
	, actionMap_()
	, parameters_(std::make_shared<CAnyParameterMap>())
	, motion_()
	, skillController_(std::make_shared<CSkillController>())
	, myID_(IDManagerInstance.CreateID())
	, charaType_()
	, collider_(std::make_shared<CCollider>())
{
}

void ActionGame::Actor::Update()
{
	//速度更新
	velocity_->Update();
	//速度で座標移動
	transform_->AddPosition(velocity_);
	//速度でY軸回転
	transform_->SetRotateY(velocity_->GetRotateY());
	//当たり判定の座標移動
	collider_->SetPosition(transform_->GetPosition());

	skillController_->Update();
}

void ActionGame::Actor::AddAction(const ActionPtr& action)
{
	AddAction(action->GetKey(), action);
}

void ActionGame::Actor::AddAction(const ActionKeyType& key, const ActionPtr& action)
{
	actionMap_[key] = action;
	action->SetTransform(transform_);
	action->SetVelocity(velocity_);
	action->SetAnimation(motion_);
	action->SetParameterMap(parameters_);
	action->SetSkillController(skillController_);
	action->SetCollider(collider_);
}
