#include "CameraBase.h"


using namespace ActionGame;

CameraBase::CameraBase(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
	: camera_()
	, lookPos_(0,0,0)
	, position_(0,0,0)
	, targetPos_(pos)
	, targetLookPos_(lookPos)
	, offsetPos_(offsetPos)
	, offsetLookPos_(offsetLookPos)
	, isEndAnimation_(false)
	, isReset_(false)
	, animationData_()
{
	Create();
}

void CameraBase::Create()
{
	camera_.SetViewPort();
	position_ = targetPos_ + offsetPos_;
	lookPos_ = targetLookPos_ + offsetLookPos_;
	camera_.LookAt(position_, lookPos_, Vector3(0, 1, 0));
	perspectiveParam_ = { MOF_ToRadian(30) ,
						(float)g_pGraphics->GetTargetWidth() / (float)g_pGraphics->GetTargetHeight(), 
						0.01f, 
						250.0f };
	auto& param = perspectiveParam_;
	camera_.PerspectiveFov(param.Fov,
		param.Aspect,
		param.Near,
		param.Far);
	camera_.Update();

}

void CameraBase::UpdateCamera()
{
	camera_.LookAt(position_, lookPos_, Vector3(0, 1, 0));
	camera_.Update();
}


void CameraBase::Render2DDebug()
{
}

void CameraBase::Enable(const Vector3& pos, const Vector3& lookPos)
{
	position_ = pos;
	lookPos_ = lookPos;
	UpdateCamera();
}


void CameraBase::SetAnimation(const MyUtil::ANIM_V3_DATA_ARRAY& posAnim, const MyUtil::ANIM_V3_DATA_ARRAY& lookPosAnim)
{
	animationData_.posAnim = posAnim;
	animationData_.lookPosAnim = lookPosAnim;

	animationData_.isAnimation = true;
	animationData_.currentTime = 0.0f;
	animationData_.count = lookPosAnim.size();
}
