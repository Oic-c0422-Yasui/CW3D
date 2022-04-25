#include	"MofInput.h"

#ifdef __MOFLIB
#include	<Mof.h>

using namespace Sample;

/**
 * @brief		�L�[�{�[�h�L�[�̎擾
 * @param[in]	positive		�{�����̃L�[
 * @param[in]	negative		�|�����̃L�[
 * @return		�L�[���͂̒l
 */
float MofInput::GetKeyboardKeyState(int positive, int negative) const {
	if (positive >= 0 && g_pInput->IsKeyHold(positive)) { return 1.0f; }
	if (negative >= 0 && g_pInput->IsKeyHold(negative)) { return -1.0f; }
	return 0;
}


/**
 * @brief		�}�E�X�L�[�̎擾
 * @param[in]	positive		�{�����̃L�[
 * @param[in]	negative		�|�����̃L�[
 * @return		�L�[���͂̒l
 */
float MofInput::GetMouseKeyState(int positive, int negative) const {
	if (positive >= 0 && g_pInput->IsMouseKeyHold(positive)) { return 1.0f; }
	if (negative >= 0 && g_pInput->IsMouseKeyHold(negative)) { return -1.0f; }
	return 0;
}

/**
 * @brief		�W���C�p�b�h�L�[�̎擾
 * @param[in]	padNo			�p�b�h�ԍ�
 * @param[in]	positive		�{�����̃L�[
 * @param[in]	negative		�|�����̃L�[
 * @return		�L�[���͂̒l
 */
float MofInput::GetJoypadKeyState(int padNo, int positive, int negative) const {
	LPGamePad pad = g_pInput->GetGamePad(padNo);
	if (pad == nullptr)
	{
		return 0;
	}
	if (positive >= 0 && pad->IsKeyHold(positive)) { return 1.0f; }
	if (negative >= 0 && pad->IsKeyHold(negative)) { return -1.0f; }
	return 0;
}

/**
 * @brief		�W���C�p�b�h�X�e�B�b�N�̎擾
 * @param[in]	padNo			�p�b�h�ԍ�
 * @return		�L�[���͂̒l
 */
float MofInput::GetJoypadStickHorizontal(int padNo) const {
	LPGamePad pad = g_pInput->GetGamePad(padNo);
	if (pad == nullptr)
	{
		return 0;
	}
	return pad->GetStickHorizontal();
}

/**
 * @brief		�W���C�p�b�h�X�e�B�b�N�̎擾
 * @param[in]	padNo			�p�b�h�ԍ�
 * @return		�L�[���͂̒l
 */
float MofInput::GetJoypadStickVertical(int padNo) const {
	LPGamePad pad = g_pInput->GetGamePad(padNo);
	if (pad == nullptr)
	{
		return 0;
	}
	return pad->GetStickVertical();
}

#endif