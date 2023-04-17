#pragma once

#include	"IInput.h"
#include	"OperateDeviceState.h"

namespace Input {
	
	/**
	 * @brief		入力クラス
	 */
	class CInput : public IInput
	{
	protected:
		//名前置き換え
		using ArrayKey = std::vector<int>;
		using ArrayKeyType = std::vector<KeyType>;

		/** キー状態 */
		struct KeyData {
			enum class Type {
				Keyboard,
				Mouse,

				Left_JoyStick_Horizontal,
				Left_JoyStick_Vertical,

				Right_JoyStick_Horizontal,
				Right_JoyStick_Vertical,

				DPad_Left,
				DPad_Right,
				DPad_Up,
				DPad_Down,

				JoyPad,
			};
			struct Key {
				int					positiveNo_;
				int					negativeNo_;
				int					padNo_;
				Type				type_;
				ArrayKey			holdKeys_;
			};
			std::vector<Key>	inputKey_;
			ArrayKeyType		disableKeys_;
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
				, disableKeys_()
			{
			}
		};
		using KeyMap = std::unordered_map<KeyType, KeyData >;
		KeyMap					keyMap_;

		COperateDeviceState		operateDevice_;

	protected:

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
		 * @brief		ジョイパッド左スティックの取得
		 * @param[in]	padNo			パッド番号
		 * @return		キー入力の値
		 */
		virtual float GetLeftJoyStickHorizontal(int padNo) const = 0;

		/**
		 * @brief		ジョイパッド左スティックの取得
		 * @param[in]	padNo			パッド番号
		 * @return		キー入力の値
		 */
		virtual float GetLeftJoyStickVertical(int padNo) const = 0;

		/**
		 * @brief		ジョイパッド右スティックの取得
		 * @param[in]	padNo			パッド番号
		 * @return		キー入力の値
		 */
		virtual float GetRightJoyStickHorizontal(int padNo) const = 0;

		/**
		 * @brief		ジョイパッド右スティックの取得
		 * @param[in]	padNo			パッド番号
		 * @return		キー入力の値
		 */
		virtual float GetRightJoyStickVertical(int padNo) const = 0;

		/**
		 * @brief		ジョイパッド十字キーの左キー取得
		 * @param[in]	padNo			パッド番号
		 * @return		キー入力の値
		 */
		virtual float GetDPadLeftKeyState(int padNo) const = 0;

		/**
		 * @brief		ジョイパッド十字キーの右キー取得
		 * @param[in]	padNo			パッド番号
		 * @return		キー入力の値
		 */
		virtual float GetDPadRightKeyState(int padNo) const = 0;

		/**
		 * @brief		ジョイパッド十字キーの上キー取得
		 * @param[in]	padNo			パッド番号
		 * @return		キー入力の値
		 */
		virtual float GetDPadUpKeyState(int padNo) const = 0;

		/**
		 * @brief		ジョイパッド十字キーの下キー取得
		 * @param[in]	padNo			パッド番号
		 * @return		キー入力の値
		 */
		virtual float GetDPadDownKeyState(int padNo) const = 0;

	private:
		/*
		* @brief	操作しているデバイスを変更する
		*/
		void SetChangeDevice(KeyData::Type device,float currentVal);
		/*
		* @brief	ホールド状態の値を取得する
		*/
		float GetHoldValue(const KeyData::Key& key);
		/*
		* @brief	同時入力時、指定したキーの入力を除外する
		*/
		void DisableInputKey(const KeyData& data);

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
		 * @param[in]	positiveKey		+方向の登録キー
		 * @param[in]	negativeKey		-方向の登録キー
		 */
		void AddJoypadKey(const KeyType& keyName, int pad, int positiveKey, int negativeKey);

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 * @param[in]	pad				登録パッド
		 * @param[in]	key				登録キー
		 * @param[in]	holdKeys		登録キー配列
		 * @param[in]	disableKeys		入力を受け付けない登録されているキー名
		 */
		void AddJoypadKey(const KeyType& keyName, int pad, int key,
			const ArrayKey& holdKeys,const ArrayKeyType& disableKeys = ArrayKeyType());

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 * @param[in]	pad				登録パッド
		 */
		void AddLeftJoyStickHorizontal(const KeyType& keyName, int pad);

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 * @param[in]	pad				登録パッド
		 */
		void AddLeftJoyStickVertical(const KeyType& keyName, int pad);

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 * @param[in]	pad				登録パッド
		 */
		void AddRightJoyStickHorizontal(const KeyType& keyName, int pad);

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 * @param[in]	pad				登録パッド
		 */
		void AddRightJoyStickVertical(const KeyType& keyName, int pad);

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 * @param[in]	pad				登録パッド
		 */
		void AddDPadLeftKey(const KeyType& keyName, int pad);

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 * @param[in]	pad				登録パッド
		 * @param[in]	holdKeys		登録キー配列
		 * @param[in]	disableKeys		入力を受け付けない登録されているキー名
		 */
		void AddDPadLeftKey(const KeyType& keyName, int pad,
			const ArrayKey& holdKeys, const ArrayKeyType& disableKeys = ArrayKeyType());

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 * @param[in]	pad				登録パッド
		 */
		void AddDPadRightKey(const KeyType& keyName, int pad);

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 * @param[in]	pad				登録パッド
		 * @param[in]	holdKeys		登録キー配列
		 * @param[in]	disableKeys		入力を受け付けない登録されているキー名
		 */
		void AddDPadRightKey(const KeyType& keyName, int pad,
			const ArrayKey& holdKeys, const ArrayKeyType& disableKeys = ArrayKeyType());

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 * @param[in]	pad				登録パッド
		 */
		void AddDPadUpKey(const KeyType& keyName, int pad);

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 * @param[in]	pad				登録パッド
		 * @param[in]	holdKeys		登録キー配列
		 * @param[in]	disableKeys		入力を受け付けない登録されているキー名
		 */
		void AddDPadUpKey(const KeyType& keyName, int pad,
			const ArrayKey& holdKeys, const ArrayKeyType& disableKeys = ArrayKeyType());

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 * @param[in]	pad				登録パッド
		 */
		void AddDPadDownKey(const KeyType& keyName, int pad);

		/**
		 * @brief		登録キーの追加
		 * @param[in]	keyName				登録キー名
		 * @param[in]	pad				登録パッド
		 * @param[in]	holdKeys		登録キー配列
		 * @param[in]	disableKeys		入力を受け付けない登録されているキー名
		 */
		void AddDPadDownKey(const KeyType& keyName, int pad,
			const ArrayKey& holdKeys, const ArrayKeyType& disableKeys = ArrayKeyType());

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

		/**
		 * @brief		操作しているデバイスのタイプ取得
		 * @return		デバイスのタイプ
		 */
		GameDevice GetDeviceType() const noexcept override;
	};

}