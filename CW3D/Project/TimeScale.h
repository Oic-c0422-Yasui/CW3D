#pragma once
#include "AnimationUtilities.h"



namespace ActionGame
{

	/*
	* @brief	タイムスケールクラス
	*/
	class CTimeScale
	{
	private:
		float	timeScale_;
		MyUtil::ANIM_DATA_ARRAY animDataArray_;
		float	changeTime_;
		bool	isChange_;
		float	currentTime_;

	public:
		CTimeScale();
		~CTimeScale() {
		}
		/*
		* @brief	更新
		*/
		void Update();
		/*
		* @brief	タイムスケール取得
		* @return	タイムスケール
		*/
		float GetScale() const noexcept
		{
			return timeScale_;
		}
		/*
		* @brief	タイムスケール設定
		* @param	scale		タイムスケール
		* @param	changeTime	変化にかかる時間
		* @param	easeType	イージングタイプ
		*/
		void SetScale(float scale, float changeTime, MyUtil::EASING_TYPE easeType) noexcept;


		void SetScale(const MyUtil::ANIM_DATA_ARRAY& anim);

		void Reset() noexcept;

	};
}