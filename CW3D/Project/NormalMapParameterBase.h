#pragma once

#include "Common.h"
#include <Graphics/SpriteStudio/sstypes.h>

namespace MyClass
{
	/*���̒u������*/
	//�m�[�}���}�b�v�p�V�F�[�_�[�|�C���^
	using NormalMapPtr = std::shared_ptr<Mof::CShader>;
	//�m�[�}���}�b�v�p�V�F�[�_�[�o�C���h�|�C���^
	using NormalMapBindPtr = std::shared_ptr<Mof::CShaderBindBase>;

	class CNormalMapParameterBase
	{
	protected:
		/*
		* @brief�@�ǂݍ��݁i�p����p�j
		*/
		bool Load(const std::string& fileName, const NormalMapPtr& shader,
			const NormalMapBindPtr& shaderBind);
		/*
		* @brief�@�V�F�[�_�[�ɃJ������ݒ�i�p����p�j
		*/
		void SetCamera(const NormalMapBindPtr& bind);
	public:
		CNormalMapParameterBase();
		virtual ~CNormalMapParameterBase() = default;

		/*
		* @brief�@�ǂݍ���
		* @param fileName�@�V�F�[�_�[�̃t�@�C����
		* @return true �Ȃ琬��
		*/
		virtual bool Load(const std::string& fileName) = 0;

		/*
		* @brief�@�V�F�[�_�[�擾
		*/
		virtual const NormalMapPtr& GetShader() const noexcept = 0;
		/*
		* @brief�@�V�F�[�_�[�o�C���h�擾
		*/
		virtual const NormalMapBindPtr& GetShaderBind() const noexcept = 0;
		/*
		* @brief�@�V�F�[�_�[�ɃJ������ݒ�
		*/
		virtual void SetCamera() = 0;
	};
}



