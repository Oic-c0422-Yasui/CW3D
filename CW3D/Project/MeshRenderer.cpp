#include "MeshRenderer.h"
#include "ResourceManager.h"


MyClass::CMeshRenderer::CMeshRenderer()
	: mesh_(nullptr)
	, normalMap_(nullptr)
	, isEnableNormalMap_(true)
{
}


MyClass::CMeshRenderer::~CMeshRenderer()
{
}

bool MyClass::CMeshRenderer::Load(const std::string& meshTag, const std::string& meshName, const std::string& shaderName)
{
	//���b�V�������݂��Ȃ��Ȃ�ǂݍ��ݎ��s
	if (!ResourcePtrManager<CMeshContainer>::GetInstance().IsContainResource(meshTag,meshName))
	{
		return false;
	}
	//���\�[�X�̒l���擾
	mesh_ = ResourcePtrManager<CMeshContainer>::GetInstance().GetResource(meshTag, meshName);

	//�V�F�[�_�[�̏ꍇ��
	if (ResourcePtrManager<CNormalMapParameter>::GetInstance().IsContainResource("Shader", shaderName))
	{
		normalMap_ = ResourcePtrManager<CNormalMapParameter>::GetInstance().GetResource("Shader", shaderName);
		isEnableNormalMap_ = false;
	}
	normalMap_->GetShader()->SetTechnique(0);
	
	return true;
}

void MyClass::CMeshRenderer::Render(const Matrix& mat, const MyClass::Color& color)
{
	mesh_->Render(mat, color, 
		normalMap_->GetShader().get(),
		normalMap_->GetShaderBind().get());
}



void MyClass::CMeshRenderer::Render(MotionPtr motion, const MyClass::Color& color)
{
	
	//mesh_->Render(motion, color,
	//	normalMap_->GetShader().get(),
	//	normalMap_->GetShaderBind().get());

	{
		mesh_->Render(motion, color);
	}
	
}

void MyClass::CMeshRenderer::Release()
{
	mesh_.reset();
	normalMap_.reset();
}

MyClass::MotionPtr MyClass::CMeshRenderer::CreateMotionController()
{
	return mesh_->CreateMotionController();
}


