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
	//メッシュが存在しないなら読み込み失敗
	if (!ResourcePtrManager<CMeshContainer>::GetInstance().IsContainResource(meshTag,meshName))
	{
		return false;
	}
	//リソースの値を取得
	mesh_ = ResourcePtrManager<CMeshContainer>::GetInstance().GetResource(meshTag, meshName);

	//シェーダーの場合は
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


