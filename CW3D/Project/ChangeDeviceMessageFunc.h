#pragma once
#include <functional>

namespace MyUtil
{
	//デバイス変更時に実行される関数
	using deviceMessageFunc = const std::function<void()>&;
	
	/*
	* @brief	デバイス変更時に実行する関数を実行する
	*/
	class CChangeDeviceMessageFunc
	{
	public:
		/*
		* @brief	読み込み
		* @brief	keyBoradFunc キーボード時に実行される関数
		* @brief	controllerFunc コントローラー時に実行される関数
		*/
		static bool Load(deviceMessageFunc keyBoradFunc,
						deviceMessageFunc controllerFunc);
	};
}

