#include "NormalMapParameterBase.h"
#include "CameraController.h"



MyClass::CNormalMapParameterBase::CNormalMapParameterBase()
{
}

bool MyClass::CNormalMapParameterBase::Load(const std::string& fileName, const NormalMapPtr& shader, 
											const NormalMapBindPtr& shaderBind)
{
	//�V�F�[�_�[�̓ǂݍ���
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
	//�J������ݒ�
	auto camera = CameraControllerInstance.GetCamera();
	bind->SetCamera(&camera);
}
