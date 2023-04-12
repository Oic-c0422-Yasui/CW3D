#include "NormalMapParameterBase.h"
#include "CameraController.h"



MyClass::CNormalMapParameterBase::CNormalMapParameterBase()
{
}

bool MyClass::CNormalMapParameterBase::Load(const std::string& fileName, const NormalMapPtr& shader, 
											const NormalMapBindPtr& shaderBind)
{
	//シェーダーの読み込み
	if (!shader->Load(fileName.c_str()))
	{
		return false;
	}
	if (!shaderBind->Create(shader.get()))
	{
		return false;
	}

	return true;
}


void MyClass::CNormalMapParameterBase::SetCamera(const NormalMapBindPtr& bind)
{
	//カメラを設定
	auto camera = CameraControllerInstance.GetCamera();
	bind->SetCamera(&camera);
}
