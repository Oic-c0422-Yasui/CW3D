#pragma once
#include "Singleton.h"
#include "CameraBase.h"


namespace ActionGame
{

	class CameraController : public Singleton<CameraController>
	{
		friend class Singleton<CameraController>;
	private:

		CameraPtr	m_Camera;
		CameraPtr	m_NextCamera;
		CameraPtr	m_DefaultCamera;
		bool		m_LeapFlg;
		bool		m_LeapStartFlg;
		float		m_LeapTime;
		bool		m_LeapEndFlg;
		float		m_TempLeapEndTime;
		MyUtilities::EASING_TYPE m_EndEaseType;
		float		m_Time;
		float		m_CurrentTime;
		bool		m_TimerStartFlg;

		float		m_QuakePower;
		float		m_QuakeFrequent;
		float		m_QuakeTime;
		float		m_QuakeCurrentTime;

		Vector3		m_TargetPos;
		Vector3		m_TargetLookPos;
		
		CameraController();
		void Reset();

	public:
		~CameraController();
		
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
		void SetCamera(const CameraPtr& camera, float tTime, MyUtilities::EASING_TYPE startEaseType, float leapStartTime, MyUtilities::EASING_TYPE endEaseType, float leapEndTime);
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
			return m_Camera->GetPos();
		}
		/*
		* @brief	�������W�擾
		* @return	�������W
		*/
		const Vector3& GetLookPosition() const noexcept
		{
			return m_Camera->GetLookPos();
		}
		/*
		* @brief	�ڕW���W�ݒ�
		* @param	pos �ڕW���W
		*/
		void SetTargetPos(const Vector3& pos) noexcept
		{
			m_Camera->SetPos(pos);
		}
		/*
		* @brief	�ڕW�������W�ݒ�
		* @param	pos �ڕW�������W
		*/
		void SetTargetLookPos(const Vector3& pos) noexcept
		{
			m_Camera->SetLookPos(pos);
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
			return m_Camera->GetCamera();
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

	};

}


//�ȈՃA�N�Z�X�p
#define CameraControllerInstance 	ActionGame::CameraController::GetInstance()

