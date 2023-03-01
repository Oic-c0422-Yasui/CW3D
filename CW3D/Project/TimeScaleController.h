#pragma once

#include "Singleton.h"

#include "TimeScale.h"
#include "CharaTypeDefine.h"
#include <map>

namespace ActionGame
{
	/*
	* @brief　タイムスケール操作クラス
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
		* @brief	更新
		*/
		void Update();

		/*
		* @brief	指定したキャラのタイムスケールを取得
		* @param	type　キャラのタイプ
		* @return	指定したキャラのタイムスケール
		*/
		float GetTimeScale(CHARA_TYPE type) noexcept;
		/*
		* @brief	全体のタイムスケールを取得
		* @return	全体のタイムスケール
		*/
		float GetTimeScale()const noexcept
		{
			return timeScale_.GetScale();
		}
		/*
		* @brief	プレイヤーのタイムスケールを取得
		* @return	プレイヤーのタイムスケール
		*/
		float GetPlayerTimeScale() noexcept
		{
			return charaMap_[CHARA_TYPE::PLAYER].GetScale();
		}
		/*
		* @brief	敵のタイムスケールを取得
		* @return	敵のタイムスケール
		*/
		float GetEnemyTimeScale() noexcept
		{
			return charaMap_[CHARA_TYPE::ENEMY].GetScale();
		}
		/*
		* @brief	ボスのタイムスケールを取得
		* @return	ボスのタイムスケール
		*/
		float GetBossTimeScale() noexcept
		{
			return charaMap_[CHARA_TYPE::BOSS].GetScale();
		}


		/*
		* @brief	タイムスケールの値をリセット
		*/
		void Reset() noexcept;
		

		/*
		* @brief	全体のタイムスケールを設定
		* @param	scale	タイムスケール
		* @param	changeTime	タイムスケールの変化にかかる時間
		* @param	easeType	イージングタイプ
		*/
		void SetTimeScale(float scale, float changeTime, MyUtil::EASING_TYPE easeType ) noexcept
		{
			timeScale_.SetScale(scale,changeTime,easeType);
		}
		/*
		* @brief	全体のタイムスケールを設定
		* @param	anim アニメーションの構造体
		* @param	changeTime	タイムスケールの変化にかかる時間
		* @param	easeType	イージングタイプ
		*/
		void SetTimeScale(const MyUtil::ANIM_DATA_ARRAY& anim) noexcept
		{
			timeScale_.SetScale(anim);
		}

		void SetTimeScale(CHARA_TYPE id, float scale, float changeTime,
							MyUtil::EASING_TYPE easeType = MyUtil::EASING_TYPE::LINER) noexcept;

		void SetTimeScale(CHARA_TYPE id, const MyUtil::ANIM_DATA_ARRAY& anim) noexcept;
		


		//ID以外のタイムスケールを変える
		void SetOtherTimeScale(CHARA_TYPE id, float scale, float changeTime,
			MyUtil::EASING_TYPE easeType = MyUtil::EASING_TYPE::LINER) noexcept;
		


		void SetOtherTimeScale(CHARA_TYPE id, const MyUtil::ANIM_DATA_ARRAY& anim) noexcept;

	};
}
//簡易アクセス用
#define TimeScaleControllerInstance 	ActionGame::TimeScaleController::GetInstance()

