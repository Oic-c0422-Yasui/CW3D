#pragma once

#include	"IInput.h"
#include	<unordered_map>

namespace Input {

	/**
	 * @brief		入力クラス
	 */
	class CStateInput : public IInput{
	protected:
		/** キー状態 */
		struct KeyData {
			float				previousValue_;
			float				currentValue_;
			float				inputValue_;
			float				pushTime_;
			float				holdTime_;

			KeyData()
				: previousValue_(0)
				, currentValue_(0)
				, inputValue_(0.1f)
				, pushTime_(0.0f)
				, holdTime_(0.0f)
			{
			}
		};
		using KeyMap = std::unordered_map<KeyType, KeyData >;
		KeyMap					keyMap_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CStateInput()
			: keyMap_()
		{ }
		/**
		 * @brief		デストラクタ
		 */
		~CStateInput() override = default;

		/**
		 * @brief		更新
		 */
		void Update() override;
		

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 */
		void AddKey(const KeyType& keyName);

		/**
		 * @brief		キーの値変更
		 * @param[in]	keyName				登録キー名
		 * @param[in]	value				値
		 */
		void SetKeyValue(const KeyType& keyName, float value);

		/**
		 * @brief		指定名称の登録キーの入力値を取得
		 * @param[in]	keyName		登録キー名
		 * @return		キー入力の値
		 */
		float GetAxis(const KeyType& keyName) const override;

		/**
		 * @brief		指定名称の登録キーがこのフレームに押されたかどうか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		bool IsPush(const KeyType& keyName) const override;

		/**
		 * @brief		指定名称の登録キーがこのフレームに押されたかどうか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		bool IsDoublePush(const KeyType& keyName) const override;

		/**
		 * @brief		指定名称の登録キーがこのフレームに押されたかどうか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		bool IsNegativePush(const KeyType& keyName) const override;

		/**
		 * @brief		指定名称の登録キーがこのフレームに押されたかどうか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		bool IsNegativeDoublePush(const KeyType& keyName) const override;

		/**
		 * @brief		指定名称の登録キーがこのフレームに離されたかどうか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで離された
		 *				false	このフレームでは離されていない
		 */
		bool IsPull(const KeyType& keyName) const override;

		/**
		 * @brief		指定名称の登録キーがこのフレームに離されたかどうか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで離された
		 *				false	このフレームでは離されていない
		 */
		bool IsNegativePull(const KeyType& keyName) const override;

		/**
		 * @brief		指定名称の登録キーが押されているかどうか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		bool IsPress(const KeyType& keyName) const override;

		/**
		 * @brief		指定名称の登録キーが何秒押されているか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		float GetPressTime(const KeyType& keyName) const override;

		/**
		 * @brief		指定名称の登録キーが押されているかどうか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		float GetNegativePressTime(const KeyType & keyName) const override;

		/**
		 * @brief		指定名称の登録キーが押されているかどうか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		bool IsNegativePress(const KeyType& keyName) const override;


		/**
		 * @brief		登録されているキー配列
		 * @return		キーの識別配列
		 */
		std::vector<KeyType> GetKeyList() const override;
	};
	using StateInputPtr = std::shared_ptr<CStateInput>;
}