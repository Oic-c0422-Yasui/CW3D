#pragma once
#include "Common.h"

namespace MyClass
{

	/*���̒u������*/
	//�m�[�}���}�b�v�p�V�F�[�_�[�|�C���^
	using NormalMapSkinnedPtr = std::shared_ptr<Mof::CShader>;
	//�m�[�}���}�b�v�p�V�F�[�_�[�o�C���h�|�C���^
	using NormalMapSkinnedBindPtr = std::shared_ptr<Mof::CShaderBind_BumpMappingSkinned>;


	class CNormalMapSkinnedParameter
	{
	private:
		NormalMapSkinnedPtr normalMap_;
		NormalMapSkinnedBindPtr normalMapBind_;
	public:
		CNormalMapSkinnedParameter();
		~CNormalMapSkinnedParameter();
		/*
		* @brief�@�ǂݍ���
		* @param fileName�@�V�F�[�_�[�̃t�@�C����
		* @return true �Ȃ琬��
		*/
		bool Load(const std::string& fileName);

		/*
		* @brief�@�V�F�[�_�[�擾
		*/
		const NormalMapSkinnedPtr& GetShader();
		/*
		* @brief�@�V�F�[�_�[�o�C���h�擾
		*/
		const NormalMapSkinnedBindPtr& GetShaderBind();
		/*
		* @brief�@�V�F�[�_�[�ɃJ������ݒ�
		*/
		void SetCamera();
	};

	using NormalMapSkinnedParameterPtr = std::shared_ptr<CNormalMapSkinnedParameter>;

}


