#pragma once

#include "Singleton.h"

#include "TimeScale.h"
#include "CharaTypeDefine.h"


namespace ActionGame
{
	/*
	* @brief�@�^�C���X�P�[������N���X
	*/
	class TimeScaleController : public Singleton<TimeScaleController>
	{
		friend class Singleton<TimeScaleController>;
	private:

		TimeScale m_TimeScale;
		TimeScale m_PlayerTimeScale;
		TimeScale m_EnemyTimeScale;

		TimeScaleController()
			: Singleton<TimeScaleController>()
			, m_TimeScale()
			, m_PlayerTimeScale()
			, m_EnemyTimeScale()
		{
		}

	public:
		~TimeScaleController() {}

		/*
		* @brief	�X�V
		*/
		void Update();

		/*
		* @brief	�w�肵���L�����̃^�C���X�P�[�����擾
		* @param	type�@�L�����̃^�C�v
		* @return	�w�肵���L�����̃^�C���X�P�[��
		*/
		float GetTimeScale(CHARACTER_TYPE type) const noexcept;
		/*
		* @brief	�S�̂̃^�C���X�P�[�����擾
		* @return	�S�̂̃^�C���X�P�[��
		*/
		float GetTimeScale()const noexcept
		{
			return m_TimeScale.GetScale();
		}
		/*
		* @brief	�v���C���[�̃^�C���X�P�[�����擾
		* @return	�v���C���[�̃^�C���X�P�[��
		*/
		float GetPlayerTimeScale()const noexcept
		{
			return m_PlayerTimeScale.GetScale();
		}
		/*
		* @brief	�G�̃^�C���X�P�[�����擾
		* @return	�G�̃^�C���X�P�[��
		*/
		float GetEnemyTimeScale()const noexcept
		{
			return m_EnemyTimeScale.GetScale();
		}

		/*
		* @brief	���Z�b�g
		*/
		void Reset() noexcept
		{
			m_TimeScale.Reset();
			m_EnemyTimeScale.Reset();
			m_PlayerTimeScale.Reset();
		}

		/*
		* @brief	�S�̂̃^�C���X�P�[����ݒ�
		* @param	scale	�^�C���X�P�[��
		* @param	changeTime	�^�C���X�P�[���̕ω��ɂ����鎞��
		* @param	easeType	�C�[�W���O�^�C�v
		*/
		void SetTimeScale(float scale, float changeTime, MyUtilities::EASING_TYPE easeType ) noexcept
		{
			m_TimeScale.SetScale(scale,changeTime,easeType);
		}
		/*
		* @brief	�S�̂̃^�C���X�P�[����ݒ�
		* @param	anim �A�j���[�V�����̍\����
		* @param	changeTime	�^�C���X�P�[���̕ω��ɂ����鎞��
		* @param	easeType	�C�[�W���O�^�C�v
		*/
		void SetTimeScale(MyUtilities::ANIM_DATA* anim,int count) noexcept
		{
			m_TimeScale.SetScale(anim, count);
		}
		/*
		* @brief	�S�̂̃^�C���X�P�[����ݒ�
		* @param	anim �A�j���[�V�����̍\����
		* @param	changeTime	�^�C���X�P�[���̕ω��ɂ����鎞��
		* @param	easeType	�C�[�W���O�^�C�v
		*/
		void SetTimeScale(const MyUtilities::ANIM_DATA_ARRAY& anim) noexcept
		{
			m_TimeScale.SetScale(anim);
		}

		void SetTimeScale(CHARACTER_TYPE id,const float scale, const float changeTime, MyUtilities::EASING_TYPE easeType) noexcept
		{
			switch (id)
			{
			case CHARA_PLAYER:
			{
				m_PlayerTimeScale.SetScale(scale, changeTime, easeType);
				break;
			}
			case CHARA_ENEMY:
			{
				m_EnemyTimeScale.SetScale(scale, changeTime, easeType);
				break;
			}
			default:
				break;
			}
			
		}
		//animData,count
		void SetTimeScale(CHARACTER_TYPE id, MyUtilities::ANIM_DATA* anim, int count) noexcept
		{
			switch (id)
			{
			case CHARA_PLAYER:
			{
				m_PlayerTimeScale.SetScale(anim,count);
				break;
			}
			case CHARA_ENEMY:
			{
				m_EnemyTimeScale.SetScale(anim, count);
				break;
			}
			default:
				break;
			}
		}
		void SetTimeScale(CHARACTER_TYPE id,const MyUtilities::ANIM_DATA_ARRAY& anim) noexcept
		{
			switch (id)
			{
			case CHARA_PLAYER:
			{
				m_PlayerTimeScale.SetScale(anim);
				break;
			}
			case CHARA_ENEMY:
			{
				m_EnemyTimeScale.SetScale(anim);
				break;
			}
			default:
				break;
			}
		}


		//ID�ȊO�̃^�C���X�P�[����ς���
		void SetOtherTimeScale(CHARACTER_TYPE id,float scale,float changeTime, MyUtilities::EASING_TYPE easeType) noexcept
		{
			switch (id)
			{
			case CHARA_PLAYER:
			{
				m_EnemyTimeScale.SetScale(scale, changeTime, easeType);
				
				break;
			}
			case CHARA_ENEMY:
			{
				m_PlayerTimeScale.SetScale(scale, changeTime, easeType);
				break;
			}
			default:
				break;
			}

		}
		//animData,count
		void SetOtherTimeScale(CHARACTER_TYPE id, MyUtilities::ANIM_DATA* anim, int count) noexcept
		{
			switch (id)
			{
			case CHARA_PLAYER:
			{
				m_EnemyTimeScale.SetScale(anim, count);
				break;
			}
			case CHARA_ENEMY:
			{
				m_PlayerTimeScale.SetScale(anim, count);
				break;
			}
			default:
				break;
			}
		}

		void SetOtherTimeScale(CHARACTER_TYPE id,const MyUtilities::ANIM_DATA_ARRAY& anim) noexcept
		{
			switch (id)
			{
			case CHARA_PLAYER:
			{
				m_EnemyTimeScale.SetScale(anim);
				break;
			}
			case CHARA_ENEMY:
			{
				m_PlayerTimeScale.SetScale(anim);
				break;
			}
			default:
				break;
			}
		}

	};
}
//�ȈՃA�N�Z�X�p
#define TimeScaleControllerInstance 	ActionGame::TimeScaleController::GetInstance()

