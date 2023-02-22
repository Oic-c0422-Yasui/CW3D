#pragma once

#include "Utilities.h"

namespace ActionGame
{
	class CameraBase
	{
	protected:
		CCamera		camera_;
		CVector3	offsetPos_;
		CVector3	offsetLookPos_;
		CVector3	lookPos_;
		CVector3	position_;
		CVector3	targetPos_;
		CVector3	targetLookPos_;
		bool		isEndAnimation_;
		bool		isReset_;

		//�A�j���[�V�����p�\����
		struct AnimationData
		{
			MyUtil::ANIM_V3_DATA_ARRAY posAnim;
			MyUtil::ANIM_V3_DATA_ARRAY lookPosAnim;

			bool		isAnimation;
			float		currentTime;
			int			count;

			AnimationData()
				: posAnim()
				, lookPosAnim()
				, isAnimation(false)
				, currentTime(0.0f)
				, count(0)
			{
			}
			void Release()
			{
				posAnim.clear();
				lookPosAnim.clear();
			}
		};
		AnimationData animationData_;

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
		* @param	posAnim	���W�̃A�j���[�V�����z��
		* @param	lookPosAnim	�������W�̃A�j���[�V�����z��
		*/
		virtual void SetAnimation(const MyUtil::ANIM_V3_DATA_ARRAY& posAnim, const MyUtil::ANIM_V3_DATA_ARRAY& lookPosAnim);

		/*
		* @brief	���W�擾
		* @return	���W
		*/
		const CVector3& GetPosition() const noexcept
		{
			return position_;
		}
		/*
		* @brief	�������W�擾
		* @return	�������W
		*/
		const CVector3& GetLookPos() const noexcept
		{
			return lookPos_;
		}
		/*
		* @brief	�^�[�Q�b�g�̍��W�擾
		* @return	�^�[�Q�b�g�̍��W
		*/
		const CVector3& GetTargetPos() const noexcept
		{
			return targetPos_;
		}
		/*
		* @brief	�^�[�Q�b�g�̒������W�擾
		* @return	�^�[�Q�b�g�̒������W
		*/
		const CVector3& GetTargetLookPos() const noexcept
		{
			return targetLookPos_;
		}
		/*
		* @brief	�I�t�Z�b�g���W�擾
		* @return	�I�t�Z�b�g���W
		*/
		const CVector3& GetOffsetPos() const noexcept
		{
			return offsetPos_;
		}
		/*
		* @brief	�I�t�Z�b�g�������W�擾
		* @return	�I�t�Z�b�g�������W
		*/
		const CVector3& GetOffsetLookPos() const noexcept
		{
			return offsetLookPos_;
		}
		/*
		* @brief	�J�����擾
		* @return	�J����
		*/
		CCamera& GetCamera() noexcept
		{
			return camera_;
		}
		/*
		* @brief	�A�j���[�V�������I���������H
		* @return	true�@�Ȃ�I��
		*/
		bool IsEnd() const noexcept
		{
			return isEndAnimation_;
		}
		/*
		* @brief	���W�ݒ�
		* @param	pos�@���W
		*/
		void SetPos(const Vector3& pos) noexcept
		{
			position_ = pos;
		}
		/*
		* @brief	�������W�ݒ�
		* @param	pos�@�������W
		*/
		void SetLookPos(const Vector3& pos) noexcept
		{
			lookPos_ = pos;
		}
		/*
		* @brief	�^�[�Q�b�g���W�ݒ�
		* @param	pos�@�^�[�Q�b�g���W
		*/
		void SetTargetPos(const Vector3& pos) noexcept
		{
			targetPos_ = pos;
		}
		/*
		* @brief	�^�[�Q�b�g�������W�ݒ�
		* @param	pos�@�^�[�Q�b�g�������W
		*/
		void SetTargetLookPos(const Vector3& pos) noexcept
		{
			targetLookPos_ = pos;
		}
		/*
		* @brief	�I�t�Z�b�g���W�ݒ�
		* @param	pos�@�I�t�Z�b�g���W
		*/
		void SetOffsetPos(const Vector3& pos) noexcept
		{
			offsetPos_ = pos;
		}
		/*
		* @brief	�I�t�Z�b�g�������W�ݒ�
		* @param	pos�@�I�t�Z�b�g�������W
		*/
		void SetOffsetLookPos(const Vector3& pos) noexcept
		{
			offsetLookPos_ = pos;
		}
		/*
		* @brief	�A�j���[�V�����I���ݒ�
		* @param	isEnd�@�A�j���[�V�����I���t���O
		*/
		void SetIsEndAnimation(bool isEnd) noexcept
		{
			isEndAnimation_ = isEnd;
		}
		/*
		* @brief	���Z�b�g�ݒ�
		* @param	isReset�@���Z�b�g�t���O
		*/
		void SetIsReset(bool isReset) noexcept
		{
			isReset_ = isReset;
		}
	};

	using CameraPtr = std::shared_ptr<CameraBase>;
}


