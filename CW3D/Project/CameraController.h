#pragma once
#include "Singleton.h"
#include "CameraBase.h"


namespace ActionGame
{
	/*
	* @brief	�J��������N���X
	*/
	class CCameraController : public Singleton<CCameraController>
	{
		friend class Singleton<CCameraController>;
	private:

		CameraPtr	camera_;
		CameraPtr	nextCamera_;
		CameraPtr	defaultCamera_;
		bool		isLeap_;
		bool		isLeapStart_;
		float		leapTime_;
		bool		isLeapEnd_;
		float		leapEndTime_;
		MyUtil::EASING_TYPE endEaseType_;
		float		timeScale_;
		float		currentTime_;
		bool		isTimerStart_;


		//�J�����h��
		struct QuakeState
		{
			float power;
			float frequent;
			float time;
			float currentTime;
		};
		QuakeState quakeState_;

		Vector3		targetPos_;
		Vector3		targetLookPos_;
		
		CCameraController();
		void Reset();

	public:
		~CCameraController();
		
		/*
		* @brief	�ǂݍ���
		* @param	camera	�f�t�H���g�ɂȂ�J����
		*/
		void Load(const CameraPtr& defaultCamera);
		/*
		* @brief	�J�����ݒ�
		* @param	camera	�g�p����J����
		*/
		void SetCamera(const CameraPtr& camera);
		/*
		* @brief	�J�����ݒ�
		* @param	camera	�g�p����J����
		* @param	tTime	�J�������f������
		*/
		void SetCamera(const CameraPtr& camera, float tTime);

		/*
		* @brief	�J�����ݒ�(���݂̃J�������g�p����J���� �ֈړ�����ۂɁA��ԃA�j���[�V�������s���j
		* @param	camera			�g�p����J����
		* @param	tTime			�J�������f������
		* @param	startEaseType	�J�ڊJ�n���̃C�[�W���O�^�C�v
		* @param	leapStartTime	�J�ڊJ�n�ɂ����鎞��
		* @param	endEaseType		�f�t�H���g�̃J�����֖߂鎞�̃C�[�W���O�^�C�v
		* @param	leapEndTime		�f�t�H���g�̃J�����֖߂�̂ɂ����鎞��
		*/
		void SetCamera(const CameraPtr& camera, float tTime, MyUtil::EASING_TYPE startEaseType, float leapStartTime, MyUtil::EASING_TYPE endEaseType, float leapEndTime);
		/*
		* @brief	�J�������f�t�H���g�ɂ���
		*/
		void SetDefault();
		/*
		* @brief	�X�V
		* @param pos	���W
		* @param lookPos	�������W 
		*/
		void Update(const Vector3& pos, const Vector3& lookPos);

		/*
		* @brief	�QD�f�o�b�O�`��
		*/
		void Render2DDebug();

		/*
		* @brief	���W�擾
		* @return	���W
		*/
		const Vector3& GetPosition() const noexcept
		{
			return camera_->GetPosition();
		}
		/*
		* @brief	�������W�擾
		* @return	�������W
		*/
		const Vector3& GetLookPosition() const noexcept
		{
			return camera_->GetLookPos();
		}
		/*
		* @brief	�ڕW���W�ݒ�
		* @param	pos �ڕW���W
		*/
		void SetTargetPos(const Vector3& pos) noexcept
		{
			camera_->SetPos(pos);
		}
		/*
		* @brief	�ڕW�������W�ݒ�
		* @param	pos �ڕW�������W
		*/
		void SetTargetLookPos(const Vector3& pos) noexcept
		{
			camera_->SetLookPos(pos);
		}
		/*
		* @brief	�^�[�Q�b�g�ݒ�
		* @param	pos �ڕW���W
		* @param	lookPos �ڕW�������W
		*/
		void SetTarget(const Vector3& pos, const Vector3& lookPos) noexcept
		{
			SetTargetPos(pos);
			SetTargetLookPos(lookPos);
		}
		/*
		* @brief	�J�����擾
		* @return	�J����
		*/
		const CCamera& GetCamera() const noexcept
		{
			return camera_->GetCamera();
		}

		/*
		* @brief	�J�����U��
		* @param	power	�U�����镝
		* @param	freq	�U������p�x
		* @param	time	�U�����鎞�� 
		*/
		void Quake(float power, float freq, float time);
		/*
		* @brief	�J�������W�K�p
		* @param	pos	���W
		* @param	lookPos	�������W
		*/
		void Enable(const Vector3& pos, const Vector3& lookPos);

		/*
		* @brief	�J�����̓��e�s��ݒ���擾����
		* @return	���e�s��ݒ�
		*/
		const PerspectiveParam& GetPerspectiveParam() const noexcept;
	};

}


//�ȈՃA�N�Z�X�p
#define CameraControllerInstance 	ActionGame::CCameraController::GetInstance()

