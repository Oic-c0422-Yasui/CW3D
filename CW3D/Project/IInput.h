#pragma once

#include	"Common.h"



namespace Sample {
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
		 * @param[in]	kn		登録キー名
		 * @return		キー入力の値
		 */
		virtual float GetAxis(const KeyType& kn) const = 0;

		/**
		 * @brief		指定名称の登録キーがこのフレームに押されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		virtual bool IsPush(const KeyType& kn) const = 0;

		/**
		 * @brief		指定名称の登録キーが指定のフレームに2回押されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		virtual bool IsDoublePush(const KeyType& kn) const = 0;

		/**
		 * @brief		指定名称の登録キーがこのフレームに押されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		virtual bool IsNegativePush(const KeyType& kn) const = 0;

		/**
		 * @brief		指定名称の登録キーが指定のフレームに2回押されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		virtual bool IsNegativeDoublePush(const KeyType& kn) const = 0;

		/**
		 * @brief		指定名称の登録キーがこのフレームに離されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで離された
		 *				false	このフレームでは離されていない
		 */
		virtual bool IsPull(const KeyType& kn) const = 0;

		/**
		 * @brief		指定名称の登録キーがこのフレームに離されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで離された
		 *				false	このフレームでは離されていない
		 */
		virtual bool IsNegativePull(const KeyType& kn) const = 0;

		/**
		 * @brief		指定名称の登録キーが押されているかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		virtual bool IsPress(const KeyType& kn) const = 0;

		/**
		 * @brief		指定名称の登録キーが押されているかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		virtual bool IsNegativePress(const KeyType& kn) const = 0;

		/**
		 * @brief		指定名称の登録キーが何秒押されているか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		virtual float GetNegativePressTime(const KeyType& kn) const = 0;

		/**
		 * @brief		指定名称の登録キーが何秒押されているか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		virtual float GetPressTime(const KeyType& kn) const = 0;


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