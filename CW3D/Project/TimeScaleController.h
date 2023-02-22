#pragma once

#include "Singleton.h"

#include "TimeScale.h"
#include "CharaTypeDefine.h"


namespace ActionGame
{
	/*
	* @brief　タイムスケール操作クラス
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
		* @brief	更新
		*/
		void Update();

		/*
		* @brief	指定したキャラのタイムスケールを取得
		* @param	type　キャラのタイプ
		* @return	指定したキャラのタイムスケール
		*/
		float GetTimeScale(CHARA_TYPE type) const noexcept;
		/*
		* @brief	全体のタイムスケールを取得
		* @return	全体のタイムスケール
		*/
		float GetTimeScale()const noexcept
		{
			return m_TimeScale.GetScale();
		}
		/*
		* @brief	プレイヤーのタイムスケールを取得
		* @return	プレイヤーのタイムスケール
		*/
		float GetPlayerTimeScale()const noexcept
		{
			return m_PlayerTimeScale.GetScale();
		}
		/*
		* @brief	敵のタイムスケールを取得
		* @return	敵のタイムスケール
		*/
		float GetEnemyTimeScale()const noexcept
		{
			return m_EnemyTimeScale.GetScale();
		}

		/*
		* @brief	リセット
		*/
		void Reset() noexcept
		{
			m_TimeScale.Reset();
			m_EnemyTimeScale.Reset();
			m_PlayerTimeScale.Reset();
		}

		/*
		* @brief	全体のタイムスケールを設定
		* @param	scale	タイムスケール
		* @param	changeTime	タイムスケールの変化にかかる時間
		* @param	easeType	イージングタイプ
		*/
		void SetTimeScale(float scale, float changeTime, MyUtil::EASING_TYPE easeType ) noexcept
		{
			m_TimeScale.SetScale(scale,changeTime,easeType);
		}
		/*
		* @brief	全体のタイムスケールを設定
		* @param	anim アニメーションの構造体
		* @param	changeTime	タイムスケールの変化にかかる時間
		* @param	easeType	イージングタイプ
		*/
		void SetTimeScale(const MyUtil::ANIM_DATA_ARRAY& anim) noexcept
		{
			m_TimeScale.SetScale(anim);
		}

		void SetTimeScale(CHARA_TYPE id,float scale, float changeTime, MyUtil::EASING_TYPE easeType = MyUtil::EASING_TYPE::LINER) noexcept
		{
			switch (id)
			{
			case CHARA_TYPE::PLAYER:
			{
				m_PlayerTimeScale.SetScale(scale, changeTime, easeType);
				break;
			}
			case CHARA_TYPE::ENEMY:
			{
				m_EnemyTimeScale.SetScale(scale, changeTime, easeType);
				break;
			}
			default:
				break;
			}
			
		}

		void SetTimeScale(CHARA_TYPE id,const MyUtil::ANIM_DATA_ARRAY& anim) noexcept
		{
			switch (id)
			{
			case CHARA_TYPE::PLAYER:
			{
				m_PlayerTimeScale.SetScale(anim);
				break;
			}
			case CHARA_TYPE::ENEMY:
			{
				m_EnemyTimeScale.SetScale(anim);
				break;
			}
			default:
				break;
			}
		}


		//ID以外のタイムスケールを変える
		void SetOtherTimeScale(CHARA_TYPE id,float scale,float changeTime, MyUtil::EASING_TYPE easeType = MyUtil::EASING_TYPE::LINER) noexcept
		{
			switch (id)
			{
			case CHARA_TYPE::PLAYER:
			{
				m_EnemyTimeScale.SetScale(scale, changeTime, easeType);
				
				break;
			}
			case CHARA_TYPE::ENEMY:
			{
				m_PlayerTimeScale.SetScale(scale, changeTime, easeType);
				break;
			}
			default:
				break;
			}

		}


		void SetOtherTimeScale(CHARA_TYPE id,const MyUtil::ANIM_DATA_ARRAY& anim) noexcept
		{
			switch (id)
			{
			case CHARA_TYPE::PLAYER:
			{
				m_EnemyTimeScale.SetScale(anim);
				break;
			}
			case CHARA_TYPE::ENEMY:
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
//簡易アクセス用
#define TimeScaleControllerInstance 	ActionGame::TimeScaleController::GetInstance()

