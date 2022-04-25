#pragma once

#include	"IInput.h"

namespace Sample {

	/**
	 * @brief		���̓N���X
	 */
	class ReplayInput : public IInput
	{
	protected:
		/** �L�[��� */
		struct KeyData {
			float				prevValue;
			float				nowValue;
			float				inputValue;

			KeyData()
				: prevValue(0)
				, nowValue(0)
				, inputValue(0.5f) {
			}
		};
		using KeyMap = std::unordered_map<KeyType, KeyData >;
		KeyMap					keyMap_;

		/** �t�@�C���X�g���[�� */
		std::ifstream			file_;

		/**
		 * @brief		�t�@�C������̃L�[�ǂݍ���
		 */
		template < typename T = KeyType >
		T ReadKey(unsigned char size) {
			T key;
			file_.read((char*)&key, sizeof(T));
			return key;
		}

		/**
		 * @brief		�t�@�C������̃L�[�ǂݍ���
		 */
		template < >
		std::string ReadKey<std::string>(unsigned char size) {
			std::string key(size, '\0');
			file_.read(&key[0], size);
			return key;
		}

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		ReplayInput(const std::string& name)
			: keyMap_()
			, file_()
		{
			file_.open(name, std::ios::in | std::ios::binary);
		}
		/**
		 * @brief		�f�X�g���N�^
		 */
		~ReplayInput() {
			file_.close();
		}

		/**
		 * @brief		�X�V
		 */
		void Update() override {
			for (auto& key : keyMap_)
			{
				key.second.prevValue = key.second.nowValue;
				key.second.nowValue = 0;
			}
			while (!file_.eof())
			{
				unsigned char size = 0;
				file_.read((char*)&size, 1);
				if (size == 0xFF)
				{
					break;
				}
				KeyType key = ReadKey(size);
				float v = 0;
				file_.read((char*)&v, sizeof(v));
				keyMap_[key].nowValue = v;
			}
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�̓��͒l���擾
		 * @param[in]	kn		�o�^�L�[��
		 * @return		�L�[���͂̒l
		 */
		float GetAxis(const KeyType& kn) const override {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɉ����ꂽ���ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ����ꂽ
		 *				false	���̃t���[���ł͉�����Ă��Ȃ�
		 */
		bool IsPush(const KeyType& kn) const override {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue > kd.inputValue && kd.prevValue < kd.inputValue;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɉ����ꂽ���ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ����ꂽ
		 *				false	���̃t���[���ł͉�����Ă��Ȃ�
		 */
		bool IsNegativePush(const KeyType& kn) const override {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue < -kd.inputValue && kd.prevValue > -kd.inputValue;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɗ����ꂽ���ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŗ����ꂽ
		 *				false	���̃t���[���ł͗�����Ă��Ȃ�
		 */
		bool IsPull(const KeyType& kn) const override {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue < kd.inputValue && kd.prevValue > kd.inputValue;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɗ����ꂽ���ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŗ����ꂽ
		 *				false	���̃t���[���ł͗�����Ă��Ȃ�
		 */
		bool IsNegativePull(const KeyType& kn) const override {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue > kd.inputValue && kd.prevValue < -kd.inputValue;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[��������Ă��邩�ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ�����Ă���
		 *				false	���̃t���[���ŉ�����Ă��Ȃ�
		 */
		bool IsPress(const KeyType& kn) const override {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue > kd.inputValue;
		}

		/**
		 * @brief		�w�薼�̂̓o�^�L�[��������Ă��邩�ǂ���
		 * @param[in]	kn		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ�����Ă���
		 *				false	���̃t���[���ŉ�����Ă��Ȃ�
		 */
		bool IsNegativePress(const KeyType& kn) const override {
			const auto& v = keyMap_.find(kn);
			if (v == keyMap_.end()) { return 0; }
			const KeyData& kd = v->second;
			return kd.nowValue < -kd.inputValue;
		}

		/**
		 * @brief		�o�^����Ă���L�[�z��
		 * @return		�L�[�̎��ʔz��
		 */
		std::vector<KeyType> GetKeyList() const override {
			std::vector<KeyType> keys;
			for (auto& key : keyMap_)
			{
				keys.push_back(key.first);
			}
			return keys;
		}
	};

}