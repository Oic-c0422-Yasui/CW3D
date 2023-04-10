#pragma once
#include "Common.h"
#include "NormalMapParameter.h"

namespace MyClass
{

	/*���̒u������*/
	//���b�V���|�C���^
	using MeshPtr = std::shared_ptr<Mof::CMeshContainer>;
	//�}�g���N�X(4�~4)
	using Matrix = Mof::CMatrix44;
	//���[�V����
	using MotionPtr = Mof::LPMeshMotionController;
	//�F(Vector4)
	using Color = Mof::Vector4;

	/*
	* @brief ���b�V���`����s���N���X
	*/
	class CMeshRenderer
	{
	private:
		MeshPtr mesh_;
		NormalMapParameterPtr normalMap_;
		bool isEnableNormalMap_;
	public:
		CMeshRenderer();
		~CMeshRenderer();
		/*
		* @brief	���\�[�X�}�l�[�W���[����ǂݍ��݁i���ɑf�ނ��ǂݍ��܂�Ă���ꍇ�̂݁j
		* @param	meshTag�@���b�V���^�O��
		* @param	meshName ���b�V����
		* @param	shaderName �V�F�[�_�[��
		* @return	true�@�Ȃ琬��
		*/
		bool Load(const std::string& meshTag,const std::string& meshName, const std::string& shaderName);

		/*
		* @brief ���b�V���`��
		* @param mat �}�g���N�X(�S�~�S)
		* @param color �F(Vector4)
		*/
		void Render(const Matrix& mat,const MyClass::Color& color);
		/*
		* @brief ���[�V�����K�p���b�V���`��
		* @param motion ���[�V����
		* @param color �F(Vector4)
		*/
		void Render(MotionPtr motion, const MyClass::Color& color);

		/*
		* @brief�@���
		*/
		void Release();

		/*
		* @brief ���[�V�����R���g���[���[����
		*/
		MotionPtr CreateMotionController();
	};
}



