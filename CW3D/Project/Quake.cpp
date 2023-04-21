#include "Quake.h"

ActionGame::CQuake::CQuake()
	: param_()
	, offset_(0,0)
	, currentTime_(0.0f)
	, isQuake_(false)
{
}

ActionGame::CQuake::~CQuake()
{
}

void ActionGame::CQuake::Initialize(float power, float frequent, float time)
{
	Quake(power, frequent, time);
	currentTime_ = 0.0f;
	isQuake_ = false;
}

void ActionGame::CQuake::StartQuake()
{
	currentTime_ = 0.0f;
	isQuake_ = true;
}

void ActionGame::CQuake::Quake(float power, float frequent, float time) noexcept
{
	param_.power = param_.power > power ? param_.power : power;
	param_.frequent = param_.frequent > frequent ? param_.frequent : frequent;
	param_.time = time;
}

void ActionGame::CQuake::EnableQuake(QaukeAxis axis)
{
	if (!isQuake_)
	{
		return;
	}
	if (currentTime_ > param_.time)
	{
		isQuake_ = false;
		currentTime_ = 0.0f;
		offset_ = Vector2(0, 0);
		return;
	}


	//êUìÆìKóp
	float value = sin(currentTime_ * param_.frequent)* param_.power;
	Vector2 offset(0, 0);
	switch (axis)
	{
	case ActionGame::QaukeAxis::X:
		offset.x = value;
		break;
	case ActionGame::QaukeAxis::Y:
		offset.y = value;
		break;
	case ActionGame::QaukeAxis::XY:
		offset.x = value;
		offset.y = value;
		break;
	default:
		break;
	}
	
	offset_ = offset;
	currentTime_ += CUtilities::GetFrameSecond();

	
}

const Vector2& ActionGame::CQuake::GetOffset() const noexcept
{
	return offset_;
}
