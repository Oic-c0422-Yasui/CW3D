#pragma once

#include	"Input.h"

#ifdef __MOFLIB

namespace Input {

	/**
	 * @brief		���̓N���X
	 */
	class CMofInput : public CInput
	{
	protected:
		//�ŏ����͒l
		const float MIN_INPUT = 0.3f;
		//�X�e�B�b�N�ő���͗�
		const float MAX_INPUTSTICK = 1000.0f;
		//�\���L�[���͒l
		struct Direction
		{
			const int LEFT = 27000;
			const int RIGHT = 9000;
			const int UP = 0;
			const int DOWN = 18000;
		};
		const Direction DIRECTION_VALUE;
		int direction_[Dpad_Count];

	protected:
		/**
		 * @brief		�L�[�{�[�h�L�[�̎擾
		 * @param[in]	positive		�{�����̃L�[
		 * @param[in]	negative		�|�����̃L�[
		 * @return		�L�[���͂̒l
		 */
		float GetKeyboardKeyState(int positive, int negative) const override;

		/**
		 * @brief		�}�E�X�L�[�̎擾
		 * @param[in]	positive		�{�����̃L�[
		 * @param[in]	negative		�|�����̃L�[
		 * @return		�L�[���͂̒l
		 */
		float GetMouseKeyState(int positive, int negative) const override;

		/**
		 * @brief		�W���C�p�b�h�L�[�̎擾
		 * @param[in]	padNo			�p�b�h�ԍ�
		 * @param[in]	positive		�{�����̃L�[
		 * @param[in]	negative		�|�����̃L�[
		 * @return		�L�[���͂̒l
		 */
		float GetJoypadKeyState(int padNo, int positive, int negative) const override;

		/**
		 * @brief		���W���C�p�b�h�X�e�B�b�N�̎擾
		 * @param[in]	padNo			�p�b�h�ԍ�
		 * @return		�L�[���͂̒l
		 */
		float GetLeftJoyStickHorizontal(int padNo) const override;

		/**
		 * @brief		���W���C�p�b�h�X�e�B�b�N�̎擾
		 * @param[in]	padNo			�p�b�h�ԍ�
		 * @return		�L�[���͂̒l
		 */
		float GetLeftJoyStickVertical(int padNo) const override;

		/**
		 * @brief		�E�W���C�p�b�h�X�e�B�b�N�̎擾
		 * @param[in]	padNo			�p�b�h�ԍ�
		 * @return		�L�[���͂̒l
		 */
		float GetRightJoyStickHorizontal(int padNo) const override;

		/**
		 * @brief		�E�W���C�p�b�h�X�e�B�b�N�̎擾
		 * @param[in]	padNo			�p�b�h�ԍ�
		 * @return		�L�[���͂̒l
		 */
		float GetRightJoyStickVertical(int padNo) const override;

		/**
		 * @brief		�W���C�p�b�h�\���L�[�̃L�[�擾
		 * @param[in]	padNo			�p�b�h�ԍ�
		 * @param[in]	direction		�L�[�̕���
		 * @return		�L�[���͂̒l
		 */
		float GetDPadKeyState(int padNo,DPad_Direction direction) const override;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CMofInput();
	};

}

#endif