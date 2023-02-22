#pragma once

#include	"IInput.h"
#include	<unordered_map>

namespace Input {

	/**
	 * @brief		���̓N���X
	 */
	class CStateInput : public IInput{
	protected:
		/** �L�[��� */
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
		 * @brief		�R���X�g���N�^
		 */
		CStateInput()
			: keyMap_()
		{ }
		/**
		 * @brief		�f�X�g���N�^
		 */
		~CStateInput() override = default;

		/**
		 * @brief		�X�V
		 */
		void Update() override;
		

		/**
		 * @brief		�o�^�L�[�̒ǉ�
		 * @param[in]	keyName				�o�^�L�[��
		 */
		void AddKey(const KeyType& keyName);

		/**
		 * @brief		�L�[�̒l�ύX
		 * @param[in]	keyName				�o�^�L�[��
		 * @param[in]	value				�l
		 */
		void SetKeyValue(const KeyType& keyName, float value);

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�̓��͒l���擾
		 * @param[in]	keyName		�o�^�L�[��
		 * @return		�L�[���͂̒l
		 */
		float GetAxis(const KeyType& keyName) const override;

		/**
		 * @brief		�w�薼�̂̓o�^�L�[�����̃t���[���ɉ����ꂽ���ǂ���
		 * @param[in]	keyName		�o�^�L�[��
		 * @return		true	���̃t���[���ŉ����ꂽ
		 *				false	���̃t���[���ł͉�����Ă��Ȃ�
		 */
		bool IsPush(const KeyType& keyName) const override;

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
		float GetNegativePressTime(const KeyType & keyName) const override;

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
	using StateInputPtr = std::shared_ptr<CStateInput>;
}