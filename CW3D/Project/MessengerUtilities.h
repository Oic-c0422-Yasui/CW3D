#pragma once
#include <functional>
#include <string>

namespace MyUtil
{
	//デバイス変更時に実行される関数
	using MessageFunc = std::function<void()>;
	using MessageName = std::string;

	/*
	* @brief	デバイス変更時に実行する関数を実行する
	*/
	class CChangeDeviceMessageFunc
	{
	public:

		/*
		* @brief	読み込み
		* @param	name			メッセージの名前
		* @param	keyBoradFunc キーボード時に実行される関数
		* @param	controllerFunc コントローラー時に実行される関数
		*/
		static bool Load(const MessageName& name,
			MessageFunc keyBoradFunc,
			MessageFunc controllerFunc);

		/*
		* @brief	登録した関数を削除する
		* @param	name	メッセージの名前
		*/
		static bool Delete(const MessageName& name);
	};

	/*
	* @brief	UI表示・非表示時に実行する関数を登録する
	*/
	class CUIMessageFunc
	{
	public:

		/*
		* @brief	読み込み
		* @param	name			メッセージの名前
		* @param	visibleFunc UI表示時に実行される関数
		* @param	disableFunc UI非表示時に実行される関数
		*/
		static bool Load(const MessageName& name,
			MessageFunc visibleFunc,
			MessageFunc disableFunc);

		/*
		* @brief	登録した関数を削除する
		* @param	name	メッセージの名前
		*/
		static bool Delete(const MessageName& name);
	};
}

