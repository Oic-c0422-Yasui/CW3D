#include "Shot.h"

using namespace ActionGame;



ActionGame::CShot::CShot()
	: collider_(std::make_shared<CAttackCollider>())
	, position_(0, 0, 0)
	, AABB_()
	, radius_(0.0f)
	, isShow_(false)
	, isEnableCollider(false)
	, parentCharaType_(CHARA_TYPE::PLAYER)
	, speed_(0.0f)
	, knockBackPower_(0, 0, 0)
	, knockBackDirection_()
	, offset_(0, 0, 0)
	, damage_(0)
	, nextHitTime_(0.0f)
	, collisionType_(COLLISION_TYPE::AABB)
	, armorBreakLevel_(0)
	, recieveUltGauge_(0.0f)
	, parentID_(0)

{
}

ActionGame::CShot::~CShot()
{
}

void ActionGame::CShot::CreateBase(const Vector3& pos, const ShotCreateParameter& shot)
{
	position_ = pos;
	offset_ = shot.offset;
	parentCharaType_ = shot.type;
	damage_ = shot.damage;
	nextHitTime_ = shot.nextHitTime;
	speed_ = 0.0f;
	isShow_ = true;
	isEnableCollider = shot.collideFlg;
	knockBackPower_ = shot.knockBack;
	knockBackDirection_ = shot.direction;
	armorBreakLevel_ = shot.armorBreakLevel;
	recieveUltGauge_ = shot.recieveUltGauge;
	parentID_ = shot.parentID;
	damageEffect_ = shot.damageEffect;
}



void ActionGame::CShot::Create(const Vector3& pos, const ShotSphere& sphire)
{
	//ベースのパラメータ作成
	CreateBase(pos, sphire);

	//追加のパラメータ作成
	radius_ = sphire.Radius;
	collider_->SetPosition(position_);
	collider_->SetRadius(radius_);
	collisionType_ = COLLISION_TYPE::SPHERE;
}

void ActionGame::CShot::Create(const Vector3& pos, const ShotAABB& aabb)
{
	//ベースのパラメータ作成
	CreateBase(pos, aabb);

	//追加のパラメータ作成
	size_ = aabb.size;
	AABB_.Size = size_;
	AABB_.SetPosition(position_);
	collisionType_ = COLLISION_TYPE::AABB;
}

void ActionGame::CShot::Create(const Vector3& pos, const ShotOBB& obb)
{
	//ベースのパラメータ作成
	CreateBase(pos, obb);

	//追加のパラメータ作成
	size_ = obb.size;
	OBB_.Position = position_;
	OBB_.Size = size_;
	OBB_.Angle = obb.angle;
	OBB_.CalculateAxis();
	collisionType_ = COLLISION_TYPE::OBB;
}

void ActionGame::CShot::ApplyColliderPosition()
{
	switch (collisionType_)
	{
	case COLLISION_TYPE::SPHERE:
	{
		collider_->SetPosition(position_);
		break;
	}
	case COLLISION_TYPE::AABB:
	{
		AABB_.SetPosition(position_);
		break;
	}
	case COLLISION_TYPE::OBB:
	{
		OBB_.Position = position_;
		break;
	}
	default:
	{
		break;
	}
	}
}

void ActionGame::CShot::Update()
{
	if (!isShow_)
	{
		return;
	}

	position_.x += speed_ * TimeScaleControllerInstance.GetTimeScale(parentCharaType_);
	
	//コライダーの座標を現在の座標に合わせる
	ApplyColliderPosition();

	//タイマー更新
	UpdateTime();
	//ヒットID削除
	DeleteHitId();
}

void ActionGame::CShot::Render()
{
	if (!isShow_)
	{
		return;
	}
}


void ActionGame::CShot::UpdateTime()
{
	for (auto& id : hitIDs_)
	{
		if (id.Time > 0.0f)
		{
			id.Time -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(parentCharaType_);
		}
	}
}


