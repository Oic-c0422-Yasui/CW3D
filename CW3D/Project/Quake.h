#pragma once
#include "Common.h"

namespace ActionGame
{
	/*
	* @brief	揺らす軸
	*/
	enum class QaukeAxis
	{
		X,
		Y,
		XY
	};

	/*
	* @brief	振動パラメータ
	*/
	struct QuakeParam
	{
		float power;	//揺れ幅
		float frequent;	//揺れ間隔
		float time;		//揺れ時間
	};
	/*
	* @brief	UIなどを揺らすためのオフセットを作成する
	*/
	class CQuake
	{
	private:
		Vector2		offset_;
		QuakeParam	param_;
		float		currentTime_;
		bool		isQuake_;
	private:
		/*
		* @brief	振動値を決める
		* @param	power 揺れ幅
		* @param	frequent 揺れ間隔
		* @param	time 揺れ時間
		*/
		void Quake(float power, float frequent, float time) noexcept;
	public:
		CQuake();
		~CQuake();
		/*
		* @brief	初期化
		* @param	power 揺れ幅
		* @param	frequent 揺れ間隔
		* @param	time 揺れ時間
		*/
		void Initialize(float power, float frequent, float time);
		/*
		* @brief	揺れ開始
		*/
		void StartQuake();
		
		/*
		* @brief	振動値を適用する
		* @param	axis 揺らす軸
		*/
		void EnableQuake(QaukeAxis axis);

		/*
		* @brief	揺れ座標オフセット
		*/
		const Vector2& GetOffset() const noexcept;
	};
}


