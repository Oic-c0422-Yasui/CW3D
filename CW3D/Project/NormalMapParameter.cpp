#include "NormalMapParameter.h"
#include "CameraController.h"

MyClass::CNormalMapParameter::CNormalMapParameter()
	: normalMap_(std::make_shared<CShader>())
	, normalMapBind_(std::make_shared<CShaderBind_BumpMapping>())
{
}

MyClass::CNormalMapParameter::~CNormalMapParameter()
{
	normalMapBind_.reset();
	normalMap_.reset();
}

bool MyClass::CNormalMapParameter::Load(const std::string& fileName)
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

const MyClass::NormalMapPtr& MyClass::CNormalMapParameter::GetShader()
{
	return normalMap_;
}

const MyClass::NormalMapBindPtr& MyClass::CNormalMapParameter::GetShaderBind()
{
	return normalMapBind_;
}


void MyClass::CNormalMapParameter::SetCamera()
{
	//カメラを設定
	auto camera = CameraControllerInstance.GetCamera();
	normalMapBind_->SetCamera(&camera);
}