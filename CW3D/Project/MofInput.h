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
		 * @brief		�W���C�p�b�h�X�e�B�b�N�̎擾
		 * @param[in]	padNo			�p�b�h�ԍ�
		 * @return		�L�[���͂̒l
		 */
		float GetJoypadStickHorizontal(int padNo) const override;

		/**
		 * @brief		�W���C�p�b�h�X�e�B�b�N�̎擾
		 * @param[in]	padNo			�p�b�h�ԍ�
		 * @return		�L�[���͂̒l
		 */
		float GetJoypadStickVertical(int padNo) const override;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CMofInput()
			: CInput()
		{ }
	};

}

#endif