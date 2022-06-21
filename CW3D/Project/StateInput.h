#pragma once

#include	"IInput.h"
#include	<unordered_map>

namespace Sample {

	/**
	 * @brief		���̓N���X
	 */
	class StateInput : public IInput{
	protected:
		/** �L�[��� */
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
		 * @brief		�R���X�g���N�^
		 */
		StateInput()
			: m_KeyMap()
		{ }
		/**
		 * @brief		�f�X�g���N�^
		 */
		~StateInput() override = default;

		/**
		 * @brief		�X�V
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
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	kn				�o�^�L�[��
		 */
		void AddKey(const KeyType& kn) {
			m_KeyMap.emplace(kn, KeyData());
		}

		/**
		 * @brief		�L�[�̒l�ύX
		 * @param[in]	kn				�o�^�L�[��
		 * @param[in]	v				�l
		 */
		void SetKeyValue(const KeyType& kn, float v) {
			const auto& it = m_KeyMap.find(kn);
			if (it == m_KeyMap.end()) { return; }
			KeyData& kd = it->second;
			kd.m_NowValue = v;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�̓��͒l���擾
		 * @param[in]	kn		�o�^�L�[��
		 * @return		�L�[���͂̒l
		 */
		float GetAxis(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_NowValue;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɉ����ꂽ���ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ����ꂽ
		 *				false	���̃t���[���ł͉�����Ă��Ȃ�
		 */
		bool IsPush(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_NowValue > kd.m_InputValue && kd.m_PreviousValue < kd.m_InputValue;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɉ����ꂽ���ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ����ꂽ
		 *				false	���̃t���[���ł͉�����Ă��Ȃ�
		 */
		bool IsDoublePush(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_NowValue > kd.m_InputValue && kd.m_PreviousValue < kd.m_InputValue&&
				kd.m_PushTime < DOUBLE_PUSH_TIME;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɉ����ꂽ���ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ����ꂽ
		 *				false	���̃t���[���ł͉�����Ă��Ȃ�
		 */
		bool IsNegativePush(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_NowValue < -kd.m_InputValue && kd.m_PreviousValue > -kd.m_InputValue;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɉ����ꂽ���ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ����ꂽ
		 *				false	���̃t���[���ł͉�����Ă��Ȃ�
		 */
		bool IsNegativeDoublePush(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_NowValue < -kd.m_InputValue && kd.m_PreviousValue > -kd.m_InputValue &&
				kd.m_PushTime < DOUBLE_PUSH_TIME;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɗ����ꂽ���ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŗ����ꂽ
		 *				false	���̃t���[���ł͗�����Ă��Ȃ�
		 */
		bool IsPull(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_NowValue < kd.m_InputValue&& kd.m_PreviousValue > kd.m_InputValue;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɗ����ꂽ���ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŗ����ꂽ
		 *				false	���̃t���[���ł͗�����Ă��Ȃ�
		 */
		bool IsNegativePull(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_NowValue > kd.m_InputValue && kd.m_PreviousValue < -kd.m_InputValue;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[��������Ă��邩�ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ�����Ă���
		 *				false	���̃t���[���ŉ�����Ă��Ȃ�
		 */
		bool IsPress(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_NowValue > kd.m_InputValue;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����b������Ă��邩
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ�����Ă���
		 *				false	���̃t���[���ŉ�����Ă��Ȃ�
		 */
		float GetPressTime(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_HoldTime;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[��������Ă��邩�ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ�����Ă���
		 *				false	���̃t���[���ŉ�����Ă��Ȃ�
		 */
		float GetNegativePressTime(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_HoldTime;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[��������Ă��邩�ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ�����Ă���
		 *				false	���̃t���[���ŉ�����Ă��Ȃ�
		 */
		bool IsNegativePress(const KeyType& kn) const override {
			const auto& v = m_KeyMap.find(kn);
			if (v == m_KeyMap.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.m_NowValue < -kd.m_InputValue;
		}


		/**
		 * @brief		�o�^����Ă���L�[�z��
		 * @return		�L�[�̎��ʔz��
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