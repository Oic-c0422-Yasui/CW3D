#pragma once

#include	"IInput.h"
#include	<unordered_map>

namespace Sample {

	/**
	 * @brief		入力クラス
	 */
	class StateInput : public IInput{
	protected:
		/** キー状態 */
		struct KeyData {
			float				m_PreviousValue;
			float				m_NowValue;
			float				m_InputValue;
			float				m_PushTime;
			float				m_HoldTime;

			KeyData()
				: m_PreviousValue(0)
				, m_NowValue(0)
				, m_InputValue(0.1f)
				, m_PushTime(0.0f)
				, m_HoldTime(0.0f)
			{
			}
		};
		using KeyMap = std::unordered_map<KeyType, KeyData >;
		KeyMap					m_KeyMap;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		StateInput()
			: m_KeyMap()
		{ }
		/**
		 * @brief		デストラクタ
		 */
		~StateInput() override = default;

		/**
		 * @brief		更新
		 */
		void Update() override
		{
			for (auto k = m_KeyMap.begin(); k != m_KeyMap.end(); ++k)
			{
				if (IsPress(k->first) || IsNegativePress(k->first))
				{
					k->second.m_HoldTime += CUtilities::GetFrameSecond();
				}
				else
				{
					k->second.m_HoldTime = 0;
				}
				if (IsPush(k->first) || IsNegativePush(k->first))
				{
					k->second.m_PushTime = 0;
				}
				else
				{
					k->second.m_PushTime += CUtilities::GetFrameSecond();
				}

				k->second.m_PreviousValue = k->second.m_NowValue;
				k->second.m_NowValue = 0;
			}
		}

		/**
		 * @brief		登録キーの追加
		 * @param[in]	kn				登録キー名
		 */
		void AddKey(const KeyType& kn) {
			m_KeyMap.emplace(kn, KeyData());
		}

		/**
		 * @brief		キーの値変更
		 * @param[in]	kn				登録キー名
		 * @param[in]	v				値
		 */
		void SetKeyValue(const KeyType& kn, float v) {
			const auto& it = m_KeyMap.find(kn);
			if (it == m_KeyMap.end()) { return; }
			KeyData& kd = it->second;
			kd.m_NowValue = v;
		}

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
			return kd.m_NowValue > kd.m_InputValue && kd.m_PreviousValue < kd.m_InputValue&&
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
			return kd.m_NowValue < kd.m_InputValue&& kd.m_PreviousValue > kd.m_InputValue;
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
	using StateInputPtr = std::shared_ptr<StateInput>;
}