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
	//���x�X�V
	velocity_->Update();
	//���x�ō��W�ړ�
	transform_->AddPosition(velocity_);
	//���x��Y����]
	transform_->SetRotateY(velocity_->GetRotateY());
	//�����蔻��̍��W�ړ�
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
