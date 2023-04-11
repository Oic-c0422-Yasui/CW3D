#pragma once

#include "Common.h"

namespace MyClass
{
	//���b�V���|�C���^
	using MeshPtr = std::shared_ptr<CMeshContainer>;
	//�e�N�X�`���|�C���^
	using TexturePtr = std::shared_ptr<CTexture>;

	/*
	* @brief	�e�N�X�`���ƃm�[�}���}�b�v�̂Ȃ��}�e���A���ɉ��̃e�N�X�`����t�^����
	*/
	class CGiveTextureToMaterial
	{
	private:
		TexturePtr meshTexture_;
		TexturePtr normalMapTexture_;
	public:
		CGiveTextureToMaterial();
		~CGiveTextureToMaterial();
		/*
		* @brief	���̃e�N�X�`���ǂݍ���
		*/
		bool Load();
		/*
		* @brief ���̃e�N�X�`����t�^����
		* @param mesh�@�t�^����Ώۂ̃��b�V��
		*/
		void Give(const MeshPtr& mesh);

	};

	using GiveTextureToMaterialPtr = std::shared_ptr<CGiveTextureToMaterial>;
}


