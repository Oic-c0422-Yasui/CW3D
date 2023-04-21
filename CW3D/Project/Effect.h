#pragma once
#include "Common.h"
#include "CharaTypeDefine.h"
namespace ActionGame
{
	/*
	* @brief �G�t�F�N�g�̍쐬�p���[���[�^
	* @param	name	�G�t�F�N�g��
	* @param	offset	���W�I�t�Z�b�g
	* @param	scale	�傫��
	* @param	rotate	��]�l
	* @param	speed	���x
	* @param	type	�L�����̃^�C�v
	*/
	struct EffectCreateParameter
	{
		std::string name;	
		Vector3 offset;
		Vector3 scale;
		Vector3 rotate;
		float speed;
		CHARA_TYPE type;
	};
	using EffectCreateParameterPtr = std::shared_ptr<EffectCreateParameter>;

	/*
	* @brief	�G�t�F�N�g�Đ��N���X
	*/
	class CEffect
	{
	private:
		Effekseer::Handle					handle_;
		bool								isStop_;
		Vector3								offset_;
		float								speed_;
		CHARA_TYPE							type_;
	public:

		CEffect(Effekseer::Handle handle);
		~CEffect();

		/*
		* @brief	������
		* @param	offset	���W�̃I�t�Z�b�g
		*/
		void Initialize( const Vector3& offset,float speed,CHARA_TYPE type);

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

		float GetSpeed() const noexcept
		{
			return speed_;
		}
	
	};

	//�|�C���^�u������
	using EffectPtr = std::shared_ptr<CEffect>;
}

