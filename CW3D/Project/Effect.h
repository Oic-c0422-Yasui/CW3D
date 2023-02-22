#pragma once
#include "Common.h"
namespace ActionGame
{
	/*
	* @brief �G�t�F�N�g�̍쐬�p���[���[�^
	* @param	name	�G�t�F�N�g��
	* @param	offset	���W�I�t�Z�b�g
	* @param	scale	�傫��
	* @param	rotate	��]�l
	* @param	speed	���x
	*/
	struct EffectCreateParameter
	{
		std::string name;	
		Vector3 offset;
		Vector3 scale;
		Vector3 rotate;
		float speed;
	};
	/*
	* @brief	�G�t�F�N�g�Đ��N���X
	*/
	class Effect
	{
	private:

		Effekseer::EffectRef				effect_;
		Effekseer::Handle					handle_;
		CVector3							position_;
		Vector3								rotation_;
		bool								isStop_;
		Vector3								offset_;

	public:

		Effect(Effekseer::Handle handle);
		~Effect();

		/*
		* @brief	������
		* @param	offset	���W�̃I�t�Z�b�g
		*/
		void Initialize( const Vector3& offset);

		/*
		* @brief	�X�V
		*/
		void Update();

		/*
		* @brief	�Đ�����~����Ă��邩�H
		* @return	true�@�Ȃ��~����Ă���
		*/
		bool IsStop() const noexcept
		{
			return  isStop_;
		}

		/*
		* @brief	�Đ���~�ݒ�
		* @param	isStop	�Đ���~��
		*/
		void SetStop(bool isStop) noexcept
		{
			isStop_ = isStop;
		}

		/*
		* @brief	�Đ��n���h�����擾
		* @return	�Đ��n���h��
		*/
		Effekseer::Handle GetHandle() const noexcept
		{
			return handle_;
		}

		/*
		* @brief	���W�I�t�Z�b�g���擾
		* @return	���W�I�t�Z�b�g
		*/
		const Vector3& GetOffset() const noexcept
		{
			return offset_;
		}

	
	};

	//�|�C���^�u������
	using EffectPtr = std::shared_ptr<Effect>;
}

