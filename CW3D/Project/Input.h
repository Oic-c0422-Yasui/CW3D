#pragma once

#include	"IInput.h"

namespace Input {
	
	/**
	 * @brief		���̓N���X
	 */
	class CInput : public IInput
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
		CInput();
		/**
		 * @brief		�f�X�g���N�^
		 */
		~CInput() override = default;


		/**
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	keyName				�o�^�L�[��
		 * @param[in]	key				�o�^�L�[
		 */
		void AddKeyboardKey(const KeyType& keyName, int key);

		/**
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	keyName				�o�^�L�[��
		 * @param[in]	positiveKey		+�����̓o�^�L�[
		 * @param[in]	negativeKey		-�����̓o�^�L�[
		 */
		void AddKeyboardKey(const KeyType& keyName, int positiveKey, int negativeKey);

		/**
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	keyName		�o�^�L�[��
		 * @param[in]	Key		�o�^�L�[
		 */
		void AddMouseKey(const KeyType& keyName, int Key);

		/**
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	keyName				�o�^�L�[��
		 * @param[in]	pad				�o�^�p�b�h
		 * @param[in]	key				�o�^�L�[
		 */
		void AddJoypadKey(const KeyType& keyName, int pad, int key);

		/**
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	keyName				�o�^�L�[��
		 * @param[in]	pad				�o�^�p�b�h
		 */
		void AddJoyStickHorizontal(const KeyType& keyName, int pad);

		/**
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	keyName				�o�^�L�[��
		 * @param[in]	pad				�o�^�p�b�h
		 */
		void AddJoyStickVertical(const KeyType& keyName, int pad);

		/**
		 * @brief		�X�V
		 */
		void Update() override;

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�̓��͒l���擾
		 * @param[in]	keyName		�o�^�L�[��
		 * @return		�L�[���͂̒l
		 */
		float GetAxis(const KeyType & keyName) const override;

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɉ����ꂽ���ǂ���
		 * @param[in]	keyName		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ����ꂽ
		 *				false	���̃t���[���ł͉�����Ă��Ȃ�
		 */
		bool IsPush(const KeyType & keyName) const override;

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɉ����ꂽ���ǂ���
		 * @param[in]	keyName		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ����ꂽ
		 *				false	���̃t���[���ł͉�����Ă��Ȃ�
		 */
		bool IsDoublePush(const KeyType& keyName) const override;

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɉ����ꂽ���ǂ���
		 * @param[in]	keyName		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ����ꂽ
		 *				false	���̃t���[���ł͉�����Ă��Ȃ�
		 */
		bool IsNegativePush(const KeyType& keyName) const override;

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɉ����ꂽ���ǂ���
		 * @param[in]	keyName		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ����ꂽ
		 *				false	���̃t���[���ł͉�����Ă��Ȃ�
		 */
		bool IsNegativeDoublePush(const KeyType& keyName) const override;

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɗ����ꂽ���ǂ���
		 * @param[in]	keyName		�o�^�L�[��
		 * @return		true	���̃t���[���ŗ����ꂽ
		 *				false	���̃t���[���ł͗�����Ă��Ȃ�
		 */
		bool IsPull(const KeyType& keyName) const override;

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɗ����ꂽ���ǂ���
		 * @param[in]	keyName		�o�^�L�[��
		 * @return		true	���̃t���[���ŗ����ꂽ
		 *				false	���̃t���[���ł͗�����Ă��Ȃ�
		 */
		bool IsNegativePull(const KeyType& keyName) const override;

		/**
		 * @brief		�w�薼�̂̓o�^�L�[��������Ă��邩�ǂ���
		 * @param[in]	keyName		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ�����Ă���
		 *				false	���̃t���[���ŉ�����Ă��Ȃ�
		 */
		bool IsPress(const KeyType& keyName) const override;

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����b������Ă��邩
		 * @param[in]	keyName		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ�����Ă���
		 *				false	���̃t���[���ŉ�����Ă��Ȃ�
		 */
		float GetPressTime(const KeyType& keyName) const override;

		/**
		 * @brief		�w�薼�̂̓o�^�L�[��������Ă��邩�ǂ���
		 * @param[in]	keyName		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ�����Ă���
		 *				false	���̃t���[���ŉ�����Ă��Ȃ�
		 */
		float GetNegativePressTime(const KeyType& keyName) const override;

		/**
		 * @brief		�w�薼�̂̓o�^�L�[��������Ă��邩�ǂ���
		 * @param[in]	keyName		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ�����Ă���
		 *				false	���̃t���[���ŉ�����Ă��Ȃ�
		 */
		bool IsNegativePress(const KeyType& keyName) const override;

		/**
		 * @brief		�o�^����Ă���L�[�z��
		 * @return		�L�[�̎��ʔz��
		 */
		std::vector<KeyType> GetKeyList() const override;
	};

}