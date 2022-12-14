#pragma once

#include "Utilities.h"

namespace ActionGame
{
	class CameraBase
	{
	protected:
		CCamera		m_Camera;
		CVector3	m_OffsetPos;
		CVector3	m_OffsetLookPos;
		CVector3	m_LookPos;
		CVector3	m_Position;
		CVector3	m_TargetPos;
		CVector3	m_TargetLookPos;
		bool		m_AnimEndFlg;
		bool		m_ResetFlg;

		//�A�j���[�V�����p�\����
		struct animData
		{
			MyUtilities::ANIM_V3_DATA_ARRAY Pos;
			MyUtilities::ANIM_V3_DATA_ARRAY LookPos;

			bool		Flg;
			float		CurrentTime;
			int			Count;

			animData()
				: Pos()
				, LookPos()
				, Flg(false)
				, CurrentTime(0.0f)
				, Count(0)
			{
			}
			void Release()
			{
				Pos.clear();
				LookPos.clear();
			}
		};
		animData m_AnimData;

	public:
		CameraBase(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos);
		virtual ~CameraBase() {};
		/*
		* @brief	����
		*/
		virtual void Create();
		/*
		* @brief	�X�V
		* @param	pos	���W
		* @param	lookPos	�������W
		*/
		virtual void Update(const Vector3& pos, const Vector3& lookPos) = 0;
		/*
		* @brief	�J�����̍X�V
		*/
		virtual void UpdateCamera();
		/*
		* @brief	�f�o�b�O�QD�`��
		*/
		virtual void Render2DDebug();
		/*
		* @brief	�J�������W�X�V�K�p
		* @param	pos	���W
		* @param	lookPos	�������W
		*/
		virtual void Enable(const Vector3& pos, const Vector3& lookPos);
		/*
		* @brief	�A�j���[�V�����ݒ�
		* @param	offsetPos	�I�t�Z�b�g���W�A�j���[�V����
		* @param	offsetLookPos	�I�t�Z�b�g�������W�A�j���[�V����
		*/
		virtual void SetAnim(const MyUtilities::ANIM_V3_DATA_ARRAY& offsetPos, const MyUtilities::ANIM_V3_DATA_ARRAY& offsetLookPos);

		/*
		* @brief	���W�擾
		* @return	���W
		*/
		const CVector3& GetPos() const noexcept
		{
			return m_Position;
		}
		/*
		* @brief	�������W�擾
		* @return	�������W
		*/
		const CVector3& GetLookPos() const noexcept
		{
			return m_LookPos;
		}
		/*
		* @brief	�^�[�Q�b�g�̍��W�擾
		* @return	�^�[�Q�b�g�̍��W
		*/
		const CVector3& GetTargetPos() const noexcept
		{
			return m_TargetPos;
		}
		/*
		* @brief	�^�[�Q�b�g�̒������W�擾
		* @return	�^�[�Q�b�g�̒������W
		*/
		const CVector3& GetTargetLookPos() const noexcept
		{
			return m_TargetLookPos;
		}
		/*
		* @brief	�I�t�Z�b�g���W�擾
		* @return	�I�t�Z�b�g���W
		*/
		const CVector3& GetOffsetPos() const noexcept
		{
			return m_OffsetPos;
		}
		/*
		* @brief	�I�t�Z�b�g�������W�擾
		* @return	�I�t�Z�b�g�������W
		*/
		const CVector3& GetOffsetLookPos() const noexcept
		{
			return m_OffsetLookPos;
		}
		/*
		* @brief	�J�����擾
		* @return	�J����
		*/
		CCamera& GetCamera() noexcept
		{
			return m_Camera;
		}
		/*
		* @brief	�A�j���[�V�������I���������H
		* @return	true�@�Ȃ�I��
		*/
		bool IsEnd() const noexcept
		{
			return m_AnimEndFlg;
		}
		/*
		* @brief	���W�ݒ�
		* @param	pos�@���W
		*/
		void SetPos(const Vector3& pos) noexcept
		{
			m_Position = pos;
		}
		/*
		* @brief	�������W�ݒ�
		* @param	pos�@�������W
		*/
		void SetLookPos(const Vector3& pos) noexcept
		{
			m_LookPos = pos;
		}
		/*
		* @brief	�^�[�Q�b�g���W�ݒ�
		* @param	pos�@�^�[�Q�b�g���W
		*/
		void SetTargetPos(const Vector3& pos) noexcept
		{
			m_TargetPos = pos;
		}
		/*
		* @brief	�^�[�Q�b�g�������W�ݒ�
		* @param	pos�@�^�[�Q�b�g�������W
		*/
		void SetTargetLookPos(const Vector3& pos) noexcept
		{
			m_TargetLookPos = pos;
		}
		/*
		* @brief	�I�t�Z�b�g���W�ݒ�
		* @param	pos�@�I�t�Z�b�g���W
		*/
		void SetOffsetPos(const Vector3& pos) noexcept
		{
			m_OffsetPos = pos;
		}
		/*
		* @brief	�I�t�Z�b�g�������W�ݒ�
		* @param	pos�@�I�t�Z�b�g�������W
		*/
		void SetOffsetLookPos(const Vector3& pos) noexcept
		{
			m_OffsetLookPos = pos;
		}
		/*
		* @brief	�A�j���[�V�����I���ݒ�
		* @param	isEnd�@�A�j���[�V�����I���t���O
		*/
		void SetEndAnimFlg(bool isEnd) noexcept
		{
			m_AnimEndFlg = isEnd;
		}
		/*
		* @brief	���Z�b�g�ݒ�
		* @param	isReset�@���Z�b�g�t���O
		*/
		void SetResetFlg(bool isReset) noexcept
		{
			m_ResetFlg = isReset;
		}
	};

	using CameraPtr = std::shared_ptr<CameraBase>;
}


