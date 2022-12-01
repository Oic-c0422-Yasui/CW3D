#pragma once
#include "Common.h"
namespace Sample
{
	/*
	* �G�t�F�N�g�̍쐬�p���[���[�^
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

		Effekseer::EffectRef				m_Effect;
		Effekseer::Handle					m_Handle;
		CVector3							m_Position;
		Vector3								m_Rotation;
		bool								m_StopFlg;
		Vector3								m_Offset;

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
			return  m_StopFlg;
		}

		/*
		* @brief	�Đ���~�ݒ�
		* @param	isStop	�Đ���~��
		*/
		void SetStop(bool isStop) noexcept
		{
			m_StopFlg = isStop;
		}

		/*
		* @brief	�Đ��n���h�����擾
		* @return	�Đ��n���h��
		*/
		Effekseer::Handle GetHandle() const noexcept
		{
			return m_Handle;
		}

		/*
		* @brief	���W�I�t�Z�b�g���擾
		* @return	���W�I�t�Z�b�g
		*/
		const Vector3& GetOffset() const noexcept
		{
			return m_Offset;
		}
	
	};

	//�|�C���^�u������
	using EffectPtr = std::shared_ptr<Effect>;
}

