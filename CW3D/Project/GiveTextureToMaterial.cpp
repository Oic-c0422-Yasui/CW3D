#include "GiveTextureToMaterial.h"
#include "ResourceManager.h"

MyClass::CGiveTextureToMaterial::CGiveTextureToMaterial()
	: meshTexture_(nullptr)
	, normalMapTexture_(nullptr)
{
}

MyClass::CGiveTextureToMaterial::~CGiveTextureToMaterial()
{
	meshTexture_.reset();
	normalMapTexture_.reset();
}

bool MyClass::CGiveTextureToMaterial::Load()
{

	const std::string tag = "Texture";
	const std::string meshTex = "TempMeshTex";

	//���b�V���e�N�X�`�������݂��Ă��Ȃ����H
	if (ResourcePtrManager<CTexture>::GetInstance().IsContainResource(tag, meshTex) == false)
	{
		//���݂��Ă��Ȃ��̂œǂݍ���
		auto tex = std::make_shared<CTexture>();
		if (!tex->Load("Shader/TempTexture/MeshTex.png"))
		{
			return false;
		}
		ResourcePtrManager<CTexture>::GetInstance().AddResource(tag,meshTex,tex);
	}
	meshTexture_ = ResourcePtrManager<CTexture>::GetInstance().GetResource(tag, meshTex);



	const std::string normalMapTex = "TempNormalMapTex";

	//�m�[�}���}�b�v�e�N�X�`�������݂��Ă��Ȃ����H
	if (ResourcePtrManager<CTexture>::GetInstance().IsContainResource(tag, normalMapTex) == false)
	{
		//���݂��Ă��Ȃ��̂œǂݍ���
		auto tex = std::make_shared<CTexture>();
		if (!tex->Load("Shader/TempTexture/NormalMapTex.png"))
		{
			return false;
		}
		ResourcePtrManager<CTexture>::GetInstance().AddResource(tag, normalMapTex, tex);
	}
	normalMapTexture_ = ResourcePtrManager<CTexture>::GetInstance().GetResource(tag, normalMapTex);

	return true;
}

void MyClass::CGiveTextureToMaterial::Give(const MeshPtr& mesh)
{
	//�e�N�X�`���ƃm�[�}���}�b�v���}�e���A���ɒǉ�
	for (uint32_t i = 0; i < mesh->GetGeometryCount(); i++)
	{
		auto texArray = mesh->GetGeometry(i)->GetMaterial()->GetTextureArray();
		//�e�N�X�`�����Ȃ��ꍇ
		if (texArray->GetArrayCount() <= 0)
		{
			texArray->Add(new CTexture(*meshTexture_.get()));
			texArray->Add(new CTexture(*normalMapTexture_.get()));
			continue;
		}
		//�m�[�}���}�b�v���Ȃ��ꍇ
		if (texArray->GetArrayCount() <= 1)
		{
			texArray->Add(new CTexture(*normalMapTexture_.get()));
		}
	}
}
