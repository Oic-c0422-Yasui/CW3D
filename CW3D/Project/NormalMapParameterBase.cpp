#include "NormalMapParameterBase.h"
#include "CameraController.h"



MyClass::CNormalMapParameterBase::CNormalMapParameterBase()
	: normalMap_(nullptr)
	//, normalMapBind_(nullptr)
{
}

bool MyClass::CNormalMapParameterBase::Load(const std::string& fileName)
{
	//シェーダーの読み込み
	if (!normalMap_->Load(fileName.c_str()))
	{
		return false;
	}
	/*if (!normalMapBind_->Create(normalMap_.get()))
	{
		return false;
	}*/

	return true;
}

const MyClass::NormalMapPtr& MyClass::CNormalMapParameterBase::GetShader() const noexcept
{
	return normalMap_;
}






bool MyClass::CNormalMapParameterBase::CreateShaderBind(const NormalMapBindPtr& bind)
{
	if (!bind->Create(normalMap_.get()))
	{
		return false;
	}
	return true;
}



void MyClass::CNormalMapParameterBase::SetCameraBind(const NormalMapBindPtr& bind)
{
	//カメラを設定
	auto camera = CameraControllerInstance.GetCamera();
	bind->SetCamera(&camera);
}
