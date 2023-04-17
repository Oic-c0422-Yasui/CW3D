#include "Shadow.h"
#include "ResourceManager.h"
#include "AnimationUtilities.h"

ActionGame::CShadow::CShadow()
	: mesh_(nullptr)
	, matrix_()
	, attenuationRate_(0.0f)
{
}

ActionGame::CShadow::~CShadow()
{
}

bool ActionGame::CShadow::Load()
{
	mesh_ = ResourcePtrManager<CMeshContainer>::GetInstance().GetResource("Chara", "Shadow");
	if (mesh_ == nullptr)
	{
		return false;
	}

	return true;
}

void ActionGame::CShadow::Initialize(const BoneState& bone, const Vector3& scale)
{
	Initialize(bone, scale, 3.0f);
}

void ActionGame::CShadow::Initialize(const BoneState& bone, const Vector3& scale, float attenuationDistance)
{
	matrix_ = bone->BoneMatrix;
	matrix_.Scaling(scale);
	attenuationRate_ = 1.0f;
	attenuationDistance_ = attenuationDistance;
}

void ActionGame::CShadow::Update(const BoneState& bone, const Vector3& pos)
{
	Vector3 bonePos;
	bone->BoneMatrix.GetTranslation(bonePos);
	if (pos.y >= attenuationDistance_)
	{
		attenuationRate_ = 0.0f;
	}
	else
	{
		attenuationRate_ = MyUtil::Timer(1.0f, pos.y,0.0f, attenuationDistance_);
	}
	

	matrix_.SetTranslation(bonePos.x,0.0f, bonePos.z);
}

void ActionGame::CShadow::Render(const Vector4& color)
{
	auto resultColor = color;
	resultColor.a *= attenuationRate_;

	g_pGraphics->SetBlending(BLEND_SUB);
	mesh_->Render(matrix_, resultColor);
	g_pGraphics->SetBlending(BLEND_NORMAL);
}

void ActionGame::CShadow::Release()
{
	mesh_.reset();
}
