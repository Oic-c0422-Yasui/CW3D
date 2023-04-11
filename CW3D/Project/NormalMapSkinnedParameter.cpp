#include "NormalMapSkinnedParameter.h"
#include "CameraController.h"

MyClass::CNormalMapSkinnedParameter::CNormalMapSkinnedParameter()
	: normalMap_(std::make_shared<CShader>())
	, normalMapBind_(std::make_shared<CShaderBind_BumpMappingSkinned>())
{
}

MyClass::CNormalMapSkinnedParameter::~CNormalMapSkinnedParameter()
{
	normalMapBind_.reset();
	normalMap_.reset();
}

bool MyClass::CNormalMapSkinnedParameter::Load(const std::string& fileName)
{
	//シェーダーの読み込み
	if (!normalMap_->Load(fileName.c_str()))
	{
		return false;
	}
	if (!normalMapBind_->Create(normalMap_.get()))
	{
		return false;
	}
	return true;
}

const MyClass::NormalMapSkinnedPtr& MyClass::CNormalMapSkinnedParameter::GetShader()
{
	return normalMap_;
}

const MyClass::NormalMapSkinnedBindPtr& MyClass::CNormalMapSkinnedParameter::GetShaderBind()
{
	return normalMapBind_;
}

void MyClass::CNormalMapSkinnedParameter::SetCamera()
{
	//カメラを設定
	auto camera = CameraControllerInstance.GetCamera();
	normalMapBind_->SetCamera(&camera);
}
