#pragma once

#include	"Common.h"



namespace Input 
{
	constexpr float DOUBLE_PUSH_TIME = 0.25f;
	/**
	 * @brief		入力インターフェイス
	 */
	//用のない初期化をしない
	class __declspec(novtable) IInput
	{
	public:
		//キー
		using KeyType = std::string;

		/**
		 * @brief		デストラクタ
		 */
		virtual ~IInput() = default;

		/**
		 * @brief		更新
		 */
		virtual void Update() = 0;

		/**
		 * @brief		指定名称の登録キーの入力値を取得
		 * @param[in]	keyName		登録キー名
		 * @return		キー入力の値
		 */
		virtual float GetAxis(const KeyType& keyName) const = 0;

		/**
		 * @brief		指定名称の登録キーがこのフレームに押されたかどうか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		virtual bool IsPush(const KeyType& keyName) const = 0;

		/**
		 * @brief		指定名称の登録キーが指定のフレームに2回押されたかどうか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		virtual bool IsDoublePush(const KeyType& keyName) const = 0;

		/**
		 * @brief		指定名称の登録キーがこのフレームに押されたかどうか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		virtual bool IsNegativePush(const KeyType& keyName) const = 0;

		/**
		 * @brief		指定名称の登録キーが指定のフレームに2回押されたかどうか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		virtual bool IsNegativeDoublePush(const KeyType& keyName) const = 0;

		/**
		 * @brief		指定名称の登録キーがこのフレームに離されたかどうか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで離された
		 *				false	このフレームでは離されていない
		 */
		virtual bool IsPull(const KeyType& keyName) const = 0;

		/**
		 * @brief		指定名称の登録キーがこのフレームに離されたかどうか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで離された
		 *				false	このフレームでは離されていない
		 */
		virtual bool IsNegativePull(const KeyType& keyName) const = 0;

		/**
		 * @brief		指定名称の登録キーが押されているかどうか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		virtual bool IsPress(const KeyType& keyName) const = 0;

		/**
		 * @brief		指定名称の登録キーが押されているかどうか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		virtual bool IsNegativePress(const KeyType& keyName) const = 0;

		/**
		 * @brief		指定名称の登録キーが何秒押されているか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		virtual float GetNegativePressTime(const KeyType& keyName) const = 0;

		/**
		 * @brief		指定名称の登録キーが何秒押されているか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		virtual float GetPressTime(const KeyType& keyName) const = 0;


		/**
		 * @brief		登録されているキー配列
		 * @return		キーの識別配列
		 */
		virtual std::vector<KeyType> GetKeyList() const = 0;
	};
	//ポインタ置き換え
	using InputPtr = std::shared_ptr<IInput>;
	using InputList = std::vector<InputPtr>;

}