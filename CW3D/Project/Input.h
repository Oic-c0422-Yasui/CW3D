#pragma once

#include	"IInput.h"

namespace ActionGame {
	
	/**
	 * @brief		入力クラス
	 */
	class Input : public IInput
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
				int				m_PositiveNo;
				int				m_NegativeNo;
				int				m_PadNo;
				Type			m_Type;
			};
			std::vector<Key>	m_Key;
			float				m_PreviousValue;
			float				m_NowValue;
			float				m_InputValue;
			float				m_HoldTime;
			float				m_PushTime;
			int					m_PushCount;
			KeyData()
				: m_Key()
				, m_PreviousValue(0)
				, m_NowValue(0)
				, m_InputValue(0.5f)
				, m_HoldTime(0.0f)
				, m_PushTime(0.0f)
				, m_PushCount(0.0f)
			{
			}
		};
		using KeyMap = std::unordered_map<KeyType, KeyData >;
		KeyMap					m_KeyMap;

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
		Input()
			: m_KeyMap()
		{ }
		/**
		 * @brief		デストラクタ
		 */
		~Input() override = default;

		/**
		 * @brief		登録キーの追加
		 * @param[in]	kn				登録キー名
		 * @param[in]	key				登録キー
		 */
		void AddKeyboardKey(const KeyType& kn, int key) {
			auto km = m_KeyMap.find(kn);
			if (km != m_KeyMap.end())
			{
				km->second.m_Key.push_back({ key, -1, -1, KeyData::Type::Keyboard });
			}
			else
			{
				m_KeyMap[kn].m_Key.push_back({ key, -1, -1, KeyData::Type::Keyboard });
			}
		}

		/**
		 * @brief		登録キーの追加
		 * @param[in]	kn				登録キー名
		 * @param[in]	positiveKey		+方向の登録キー
		 * @param[in]	negativeKey		-方向の登録キー
		 */
		void AddKeyboardKey(const KeyType& kn, int positiveKey, int negativeKey) {
			auto km = m_KeyMap.find(kn);
			if (km != m_KeyMap.end())
			{
				km->second.m_Key.push_back({ positiveKey, negativeKey, -1, KeyData::Type::Keyboard });
			}
			else
			{
				m_KeyMap[kn].m_Key.push_back({ positiveKey, negativeKey, -1, KeyData::Type::Keyboard });
			}
		}

		/**
		 * @brief		登録キーの追加
		 * @param[in]	kn		登録キー名
		 * @param[in]	Key		登録キー
		 */
		void AddMouseKey(const KeyType& kn, int Key) {
			auto km = m_KeyMap.find(kn);
			if (km != m_KeyMap.end())
			{
				km->second.m_Key.push_back({ Key, -1, -1, KeyData::Type::Mouse });
			}
			else
			{
				m_KeyMap[kn].m_Key.push_back({ Key, -1, -1, KeyData::Type::Mouse });
			}
		}

		/**
		 * @brief		登録キーの追加
		 * @param[in]	kn				登録キー名
		 * @param[in]	pad				登録パッド
		 * @param[in]	key				登録キー
		 */
		void AddJoypadKey(const KeyType& kn, int pad, int key) {
			auto km = m_KeyMap.find(kn);
			if (km != m_KeyMap.end())
			{
				km->second.m_Key.push_back({ key, -1, pad, KeyData::Type::JoyPad });
			}
			else
			{
				m_KeyMap[kn].m_Key.push_back({ key, -1, pad, KeyData::Type::JoyPad });
			}
		}

		/**
		 * @brief		登録キーの追加
		 * @param[in]	kn				登録キー名
		 * @param[in]	pad				登録パッド
		 */
		void AddJoyStickHorizontal(const KeyType& kn, int pad) {
			auto km = m_KeyMap.find(kn);
			if (km != m_KeyMap.end())
			{
				km->second.m_Key.push_back({ -1, -1, pad, KeyData::Type::JoyStickHorizontal });
			}
			else
			{
				m_KeyMap[kn].m_Key.push_back({ -1, -1, pad, KeyData::Type::JoyStickHorizontal });
			}
		}

		/**
		 * @brief		登録キーの追加
		 * @param[in]	kn				登録キー名
		 * @param[in]	pad				登録パッド
		 */
		void AddJoyStickVertical(const KeyType& kn, int pad) {
			auto km = m_KeyMap.find(kn);
			if (km != m_KeyMap.end())
			{
				km->second.m_Key.push_back({ -1, -1, pad, KeyData::Type::JoyStickVertical });
			}
			else
			{
				m_KeyMap[kn].m_Key.push_back({ -1, -1, pad, KeyData::Type::JoyStickVertical });
			}
		}

		/**
		 * @brief		更新
		 */
		void Update() override;

		/**
		 * @brief		指定名称の登録キーの入力値を取得
		 * @param[in]	kn		登録キー名
		 * @return		キー入力の値
		 */
		float GetAxis(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_NowValue;
		}

		/**
		 * @brief		指定名称の登録キーがこのフレームに押されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		bool IsPush(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_NowValue > kd.m_InputValue && kd.m_PreviousValue < kd.m_InputValue;
		}

		/**
		 * @brief		指定名称の登録キーがこのフレームに押されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		bool IsDoublePush(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_NowValue > kd.m_InputValue && kd.m_PreviousValue < kd.m_InputValue &&
				kd.m_PushTime < DOUBLE_PUSH_TIME;
		}

		/**
		 * @brief		指定名称の登録キーがこのフレームに押されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		bool IsNegativePush(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_NowValue < -kd.m_InputValue && kd.m_PreviousValue > -kd.m_InputValue;
		}

		/**
		 * @brief		指定名称の登録キーがこのフレームに押されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押された
		 *				false	このフレームでは押されていない
		 */
		bool IsNegativeDoublePush(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_NowValue < -kd.m_InputValue && kd.m_PreviousValue > -kd.m_InputValue &&
				kd.m_PushTime < DOUBLE_PUSH_TIME;
		}

		/**
		 * @brief		指定名称の登録キーがこのフレームに離されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで離された
		 *				false	このフレームでは離されていない
		 */
		bool IsPull(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_NowValue < kd.m_InputValue && kd.m_PreviousValue > kd.m_InputValue;
		}

		/**
		 * @brief		指定名称の登録キーがこのフレームに離されたかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで離された
		 *				false	このフレームでは離されていない
		 */
		bool IsNegativePull(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_NowValue > kd.m_InputValue && kd.m_PreviousValue < -kd.m_InputValue;
		}

		/**
		 * @brief		指定名称の登録キーが押されているかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		bool IsPress(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_NowValue > kd.m_InputValue;
		}

		/**
		 * @brief		指定名称の登録キーが何秒押されているか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		float GetPressTime(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_HoldTime;
		}
		/**
		 * @brief		指定名称の登録キーが押されているかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		float GetNegativePressTime(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_HoldTime;
		}

		/**
		 * @brief		指定名称の登録キーが押されているかどうか
		 * @param[in]	kn		登録キー名
		 * @return		true	このフレームで押されている
		 *				false	このフレームで押されていない
		 */
		bool IsNegativePress(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_NowValue < -kd.m_InputValue;
		}

		/**
		 * @brief		登録されているキー配列
		 * @return		キーの識別配列
		 */
		std::vector<KeyType> GetKeyList() const override {
			std::vector<KeyType> keys;
			for (auto& key : m_KeyMap)
			{
				keys.push_back(key.first);
			}
			return keys;
		}
	};

}