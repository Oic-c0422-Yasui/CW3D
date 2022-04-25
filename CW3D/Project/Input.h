#pragma once

#include	"IInput.h"

namespace Sample {

	/**
	 * @brief		���̓N���X
	 */
	class Input : public IInput
	{
	protected:
		/** �L�[��� */
		struct KeyData {
			enum class Type {
				Keyboard,
				Mouse,

				JoyStickHorizontal,

				JoyStickVertical,

				JoyPad,
			};
			struct Key {
				int				positiveNo;
				int				negativeNo;
				int				padNo;
				Type			type;
			};
			std::vector<Key>	key;
			float				prevValue;
			float				nowValue;
			float				inputValue;

			KeyData()
				: key()
				, prevValue(0)
				, nowValue(0)
				, inputValue(0.5f) {
			}
		};
		using KeyMap = std::unordered_map<KeyType, KeyData >;
		KeyMap					keyMap_;

		/**
		 * @brief		�L�[�{�[�h�L�[�̎擾
		 * @param[in]	positive		�{�����̃L�[
		 * @param[in]	negative		�|�����̃L�[
		 * @return		�L�[���͂̒l
		 */
		virtual float GetKeyboardKeyState(int positive, int negative) const = 0;

		/**
		 * @brief		�}�E�X�L�[�̎擾
		 * @param[in]	positive		�{�����̃L�[
		 * @param[in]	negative		�|�����̃L�[
		 * @return		�L�[���͂̒l
		 */
		virtual float GetMouseKeyState(int positive, int negative) const = 0;

		/**
		 * @brief		�W���C�p�b�h�L�[�̎擾
		 * @param[in]	padNo			�p�b�h�ԍ�
		 * @param[in]	positive		�{�����̃L�[
		 * @param[in]	negative		�|�����̃L�[
		 * @return		�L�[���͂̒l
		 */
		virtual float GetJoypadKeyState(int padNo, int positive, int negative) const = 0;

		/**
		 * @brief		�W���C�p�b�h�X�e�B�b�N�̎擾
		 * @param[in]	padNo			�p�b�h�ԍ�
		 * @return		�L�[���͂̒l
		 */
		virtual float GetJoypadStickHorizontal(int padNo) const = 0;

		/**
		 * @brief		�W���C�p�b�h�X�e�B�b�N�̎擾
		 * @param[in]	padNo			�p�b�h�ԍ�
		 * @return		�L�[���͂̒l
		 */
		virtual float GetJoypadStickVertical(int padNo) const = 0;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Input()
			: keyMap_()
		{ }
		/**
		 * @brief		�f�X�g���N�^
		 */
		~Input() override = default;

		/**
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	kn				�o�^�L�[��
		 * @param[in]	key				�o�^�L�[
		 */
		void AddKeyboardKey(const KeyType& kn, int key) {
			auto km = keyMap_.find(kn);
			if (km != keyMap_.end())
			{
				km->second.key.push_back({ key, -1, -1, KeyData::Type::Keyboard });
			}
			else
			{
				keyMap_[kn].key.push_back({ key, -1, -1, KeyData::Type::Keyboard });
			}
		}

		/**
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	kn				�o�^�L�[��
		 * @param[in]	positiveKey		+�����̓o�^�L�[
		 * @param[in]	negativeKey		-�����̓o�^�L�[
		 */
		void AddKeyboardKey(const KeyType& kn, int positiveKey, int negativeKey) {
			auto km = keyMap_.find(kn);
			if (km != keyMap_.end())
			{
				km->second.key.push_back({ positiveKey, negativeKey, -1, KeyData::Type::Keyboard });
			}
			else
			{
				keyMap_[kn].key.push_back({ positiveKey, negativeKey, -1, KeyData::Type::Keyboard });
			}
		}

		/**
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	kn		�o�^�L�[��
		 * @param[in]	Key		�o�^�L�[
		 */
		void AddMouseKey(const KeyType& kn, int Key) {
			auto km = keyMap_.find(kn);
			if (km != keyMap_.end())
			{
				km->second.key.push_back({ Key, -1, -1, KeyData::Type::Mouse });
			}
			else
			{
				keyMap_[kn].key.push_back({ Key, -1, -1, KeyData::Type::Mouse });
			}
		}

		/**
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	kn				�o�^�L�[��
		 * @param[in]	pad				�o�^�p�b�h
		 * @param[in]	key				�o�^�L�[
		 */
		void AddJoypadKey(const KeyType& kn, int pad, int key) {
			auto km = keyMap_.find(kn);
			if (km != keyMap_.end())
			{
				km->second.key.push_back({ key, -1, pad, KeyData::Type::JoyPad });
			}
			else
			{
				keyMap_[kn].key.push_back({ key, -1, pad, KeyData::Type::JoyPad });
			}
		}

		/**
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	kn				�o�^�L�[��
		 * @param[in]	pad				�o�^�p�b�h
		 */
		void AddJoyStickHorizontal(const KeyType& kn, int pad) {
			auto km = keyMap_.find(kn);
			if (km != keyMap_.end())
			{
				km->second.key.push_back({ -1, -1, pad, KeyData::Type::JoyStickHorizontal });
			}
			else
			{
				keyMap_[kn].key.push_back({ -1, -1, pad, KeyData::Type::JoyStickHorizontal });
			}
		}

		/**
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	kn				�o�^�L�[��
		 * @param[in]	pad				�o�^�p�b�h
		 */
		void AddJoyStickVertical(const KeyType& kn, int pad) {
			auto km = keyMap_.find(kn);
			if (km != keyMap_.end())
			{
				km->second.key.push_back({ -1, -1, pad, KeyData::Type::JoyStickVertical });
			}
			else
			{
				keyMap_[kn].key.push_back({ -1, -1, pad, KeyData::Type::JoyStickVertical });
			}
		}

		/**
		 * @brief		�X�V
		 */
		void Update() override;

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