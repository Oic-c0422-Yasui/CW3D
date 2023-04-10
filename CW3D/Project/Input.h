#pragma once

#include	"IInput.h"

namespace Input {
	
	/**
	 * @brief		入力クラス
	 */
	class CInput : public IInput
	{
	protected:
		/** キー状態 */
		struct KeyData {
			enum class Type {
				Keyboard,
				Mouse,

				JoyStickHorizontal,

				JoyStickVertical,

				JoyPad,
			};
			struct Key {
				int				positiveNo_;
				int				negativeNo_;
				int				padNo_;
				Type			type_;
			};
			std::vector<Key>	inputKey_;
			float				previousValue_;
			float				currentValue_;
			float				inputValue_;
			float				holdTime_;
			float				pushTime_;
			int					pushCount_;
			KeyData()
				: inputKey_()
				, previousValue_(0)
				, currentValue_(0)
				, inputValue_(0.5f)
				, holdTime_(0.0f)
				, pushTime_(0.0f)
				, pushCount_(0.0f)
			{
			}
		};
		using KeyMap = std::unordered_map<KeyType, KeyData >;
		KeyMap					keyMap_;

		/**
		 * @brief		キーボードキーの取得
		 * @param[in]	positive		＋方向のキー
		 * @param[in]	negative		－方向のキー
		 * @return		キー入力の値
		 */
		virtual float GetKeyboardKeyState(int positive, int negative) const = 0;

		/**
		 * @brief		マウスキーの取得
		 * @param[in]	positive		＋方向のキー
		 * @param[in]	negative		－方向のキー
		 * @return		キー入力の値
		 */
		virtual float GetMouseKeyState(int positive, int negative) const = 0;

		/**
		 * @brief		ジョイパッドキーの取得
		 * @param[in]	padNo			パッド番号
		 * @param[in]	positive		＋方向のキー
		 * @param[in]	negative		－方向のキー
		 * @return		キー入力の値
		 */
		virtual float GetJoypadKeyState(int padNo, int positive, int negative) const = 0;

		/**
		 * @brief		ジョイパッドスティックの取得
		 * @param[in]	padNo			パッド番号
		 * @return		キー入力の値
		 */
		virtual float GetJoypadStickHorizontal(int padNo) const = 0;

		/**
		 * @brief		ジョイパッドスティックの取得
		 * @param[in]	padNo			パッド番号
		 * @return		キー入力の値
		 */
		virtual float GetJoypadStickVertical(int padNo) const = 0;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CInput();
		/**
		 * @brief		デストラクタ
		 */
		~CInput() override = default;


		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 * @param[in]	key				登録キー
		 */
		void AddKeyboardKey(const KeyType& keyName, int key);

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 * @param[in]	positiveKey		+方向の登録キー
		 * @param[in]	negativeKey		-方向の登録キー
		 */
		void AddKeyboardKey(const KeyType& keyName, int positiveKey, int negativeKey);

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName		登録キー名
		 * @param[in]	Key		登録キー
		 */
		void AddMouseKey(const KeyType& keyName, int Key);

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 * @param[in]	pad				登録パッド
		 * @param[in]	key				登録キー
		 */
		void AddJoypadKey(const KeyType& keyName, int pad, int key);

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 * @param[in]	pad				登録パッド
		 */
		void AddJoyStickHorizontal(const KeyType& keyName, int pad);

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 * @param[in]	pad				登録パッド
		 */
		void AddJoyStickVertical(const KeyType& keyName, int pad);

		/**
		 * @brief		更新
		 */
		void Update() override;

		/**
		 * @brief		指定名称の登録キーの入力値を取得
		 * @param[in]	keyName		登録キー名
		 * @return		キー入力の値
		 */
		float GetAxis(const KeyType & keyName) const override;

		/**
		 * @brief		指定名称の登録キーがこのフレームに押されたかどうか
		 * @param[in]	keyName		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		bool IsPush(const KeyType & keyName) const override;

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
		float GetNegativePressTime(const KeyType& keyName) const override;

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

}