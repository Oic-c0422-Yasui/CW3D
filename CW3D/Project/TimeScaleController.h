#pragma once

#include "Singleton.h"

#include "TimeScale.h"
#include "CharaTypeDefine.h"
#include <map>

namespace ActionGame
{
	/*
	* @brief�@�^�C���X�P�[������N���X
	*/
	class TimeScaleController : public Singleton<TimeScaleController>
	{
		friend class Singleton<TimeScaleController>;
	private:
		CTimeScale timeScale_;
		std::map<CHARA_TYPE, CTimeScale> charaMap_;

		TimeScaleController()
			: Singleton<TimeScaleController>()
			, timeScale_()
		{
			charaMap_[CHARA_TYPE::PLAYER] = CTimeScale();
			charaMap_[CHARA_TYPE::ENEMY] = CTimeScale();
			charaMap_[CHARA_TYPE::BOSS] = CTimeScale();
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
		float GetTimeScale(CHARA_TYPE type) noexcept;
		/*
		* @brief	�S�̂̃^�C���X�P�[�����擾
		* @return	�S�̂̃^�C���X�P�[��
		*/
		float GetTimeScale()const noexcept
		{
			return timeScale_.GetScale();
		}
		/*
		* @brief	�v���C���[�̃^�C���X�P�[�����擾
		* @return	�v���C���[�̃^�C���X�P�[��
		*/
		float GetPlayerTimeScale() noexcept
		{
			return charaMap_[CHARA_TYPE::PLAYER].GetScale();
		}
		/*
		* @brief	�G�̃^�C���X�P�[�����擾
		* @return	�G�̃^�C���X�P�[��
		*/
		float GetEnemyTimeScale() noexcept
		{
			return charaMap_[CHARA_TYPE::ENEMY].GetScale();
		}
		/*
		* @brief	�{�X�̃^�C���X�P�[�����擾
		* @return	�{�X�̃^�C���X�P�[��
		*/
		float GetBossTimeScale() noexcept
		{
			return charaMap_[CHARA_TYPE::BOSS].GetScale();
		}


		/*
		* @brief	�^�C���X�P�[���̒l�����Z�b�g
		*/
		void Reset() noexcept;
		

		/*
		* @brief	�S�̂̃^�C���X�P�[����ݒ�
		* @param	scale	�^�C���X�P�[��
		* @param	changeTime	�^�C���X�P�[���̕ω��ɂ����鎞��
		* @param	easeType	�C�[�W���O�^�C�v
		*/
		void SetTimeScale(float scale, float changeTime, MyUtil::EASING_TYPE easeType ) noexcept
		{
			timeScale_.SetScale(scale,changeTime,easeType);
		}
		/*
		* @brief	�S�̂̃^�C���X�P�[����ݒ�
		* @param	anim �A�j���[�V�����̍\����
		* @param	changeTime	�^�C���X�P�[���̕ω��ɂ����鎞��
		* @param	easeType	�C�[�W���O�^�C�v
		*/
		void SetTimeScale(const MyUtil::ANIM_DATA_ARRAY& anim) noexcept
		{
			timeScale_.SetScale(anim);
		}

		void SetTimeScale(CHARA_TYPE id, float scale, float changeTime,
							MyUtil::EASING_TYPE easeType = MyUtil::EASING_TYPE::LINER) noexcept;

		void SetTimeScale(CHARA_TYPE id, const MyUtil::ANIM_DATA_ARRAY& anim) noexcept;
		


		//ID�ȊO�̃^�C���X�P�[����ς���
		void SetOtherTimeScale(CHARA_TYPE id, float scale, float changeTime,
			MyUtil::EASING_TYPE easeType = MyUtil::EASING_TYPE::LINER) noexcept;
		


		void SetOtherTimeScale(CHARA_TYPE id, const MyUtil::ANIM_DATA_ARRAY& anim) noexcept;

	};
}
//�ȈՃA�N�Z�X�p
#define TimeScaleControllerInstance 	ActionGame::TimeScaleController::GetInstance()

