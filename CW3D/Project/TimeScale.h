#pragma once
#include "Utilities.h"



namespace ActionGame
{

	/*
	* @brief	タイムスケールクラス
	*/
	class TimeScale
	{
	private:
		float	m_Time;
		MyUtilities::ANIM_DATA_ARRAY m_AnimDataArray;
		float	m_ChangeTime;
		bool	m_ChangeFlg;
		float	m_CurrentTime;
		int		m_Count;

	public:
		TimeScale();
		~TimeScale() {
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
			return m_Time;
		}
		/*
		* @brief	タイムスケール設定
		* @param	scale		タイムスケール
		* @param	changeTime	変化にかかる時間
		* @param	easeType	イージングタイプ
		*/
		void SetScale(float scale, float changeTime, MyUtilities::EASING_TYPE easeType) noexcept;


		void SetScale(const MyUtilities::ANIM_DATA_ARRAY& anim);

		void Reset() noexcept;

	};
}