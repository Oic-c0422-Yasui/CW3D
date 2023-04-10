#pragma once
#include "Common.h"
#include "CameraBase.h"

namespace MyClass
{
	/*���̒u������*/
	//�m�[�}���}�b�v�p�V�F�[�_�[�|�C���^
	using NormalMapPtr = std::shared_ptr<Mof::CShader>;
	//�m�[�}���}�b�v�p�V�F�[�_�[�o�C���h�|�C���^
	using NormalMapBindPtr = std::shared_ptr<Mof::CShaderBind_BumpMapping>;


	class CNormalMapParameter
	{
	private:
		NormalMapPtr normalMap_;
		NormalMapBindPtr normalMapBind_;
	public:
		CNormalMapParameter();
		~CNormalMapParameter();
		/*
		* @brief�@�ǂݍ���
		* @param fileName�@�V�F�[�_�[�̃t�@�C����
		* @return true �Ȃ琬��
		*/
		bool Load(const std::string& fileName);

		/*
		* @brief�@�V�F�[�_�[�擾
		*/
		const NormalMapPtr& GetShader();
		/*
		* @brief�@�V�F�[�_�[�o�C���h�擾
		*/
		const NormalMapBindPtr& GetShaderBind();
		/*
		* @brief�@�V�F�[�_�[�ɃJ������ݒ�
		*/
		void SetCamera();
	};

	using NormalMapParameterPtr = std::shared_ptr<CNormalMapParameter>;
}



