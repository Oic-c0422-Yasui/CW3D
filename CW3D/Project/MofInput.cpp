#include	"MofInput.h"

#ifdef __MOFLIB
#include	<Mof.h>

using namespace Input;

/**
 * @brief		�L�[�{�[�h�L�[�̎擾
 * @param[in]	positive		�{�����̃L�[
 * @param[in]	negative		�|�����̃L�[
 * @return		�L�[���͂̒l
 */
float CMofInput::GetKeyboardKeyState(int positive, int negative) const {
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
float CMofInput::GetMouseKeyState(int positive, int negative) const {
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
float CMofInput::GetJoypadKeyState(int padNo, int positive, int negative) const {
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
float CMofInput::GetLeftJoyStickHorizontal(int padNo) const {
	LPGamePad pad = g_pInput->GetGamePad(padNo);
	if (pad == nullptr)
	{
		return 0;
	}
	float horizontal = pad->GetStickHorizontal();
	if (horizontal >= MIN_INPUT) { return horizontal; }
	if (horizontal <= -MIN_INPUT) { return horizontal; }
	return 0;
}


/**
 * @brief		�W���C�p�b�h�X�e�B�b�N�̎擾
 * @param[in]	padNo			�p�b�h�ԍ�
 * @return		�L�[���͂̒l
 */
float CMofInput::GetLeftJoyStickVertical(int padNo) const {
	LPGamePad pad = g_pInput->GetGamePad(padNo);
	if (pad == nullptr)
	{
		return 0;
	}
	float vertical = pad->GetStickVertical();
	if (vertical >= MIN_INPUT) { return vertical; }
	if (vertical <= -MIN_INPUT) { return vertical; }
	return 0;
}


/**
 * @brief		�E�W���C�p�b�h�X�e�B�b�N�̎擾
 * @param[in]	padNo			�p�b�h�ԍ�
 * @return		�L�[���͂̒l
 */
float Input::CMofInput::GetRightJoyStickHorizontal(int padNo) const
{
	LPGamePad pad = g_pInput->GetGamePad(padNo);
	if (pad == nullptr)
	{
		return 0;
	}
	float horizontal = (float)pad->GetPadState()->lZ / MAX_INPUTSTICK;
	if (horizontal >= MIN_INPUT) { return horizontal; }
	if (horizontal <= -MIN_INPUT) { return horizontal; }
	return 0;
}


/**
 * @brief		�E�W���C�p�b�h�X�e�B�b�N�̎擾
 * @param[in]	padNo			�p�b�h�ԍ�
 * @return		�L�[���͂̒l
 */
float Input::CMofInput::GetRightJoyStickVertical(int padNo) const
{
	LPGamePad pad = g_pInput->GetGamePad(padNo);
	if (pad == nullptr)
	{
		return 0;
	}
	float vertical = (float)pad->GetPadState()->lRz / MAX_INPUTSTICK;
	if (vertical >= MIN_INPUT) { return vertical; }
	if (vertical <= -MIN_INPUT) { return vertical; }
	return 0;
}


/**
 * @brief		�W���C�p�b�h�\���L�[�̍��L�[�擾
 * @param[in]	padNo			�p�b�h�ԍ�
 * @return		�L�[���͂̒l
 */
float Input::CMofInput::GetDPadLeftKeyState(int padNo) const
{
	LPGamePad pad = g_pInput->GetGamePad(padNo);
	if (pad == nullptr)
	{
		return 0;
	}
	if (pad->GetPadState()->rgdwPOV[0] == DIRECTION.LEFT)
	{
		return 1.0f;
	}

	return 0;
}


/**
 * @brief		�W���C�p�b�h�\���L�[�̉E�L�[�擾
 * @param[in]	padNo			�p�b�h�ԍ�
 * @return		�L�[���͂̒l
 */
float Input::CMofInput::GetDPadRightKeyState(int padNo) const
{
	LPGamePad pad = g_pInput->GetGamePad(padNo);
	if (pad == nullptr)
	{
		return 0;
	}
	if (pad->GetPadState()->rgdwPOV[0] == DIRECTION.RIGHT)
	{
		return 1.0f;
	}

	return 0;
}


/**
 * @brief		�W���C�p�b�h�\���L�[�̏�L�[�擾
 * @param[in]	padNo			�p�b�h�ԍ�
 * @return		�L�[���͂̒l
 */
float Input::CMofInput::GetDPadUpKeyState(int padNo) const
{
	LPGamePad pad = g_pInput->GetGamePad(padNo);
	if (pad == nullptr)
	{
		return 0;
	}
	if (pad->GetPadState()->rgdwPOV[0] == DIRECTION.UP)
	{
		return 1.0f;
	}

	return 0;
}


/**
 * @brief		�W���C�p�b�h�\���L�[�̉��L�[�擾
 * @param[in]	padNo			�p�b�h�ԍ�
 * @return		�L�[���͂̒l
 */
float Input::CMofInput::GetDPadDownKeyState(int padNo) const
{
	LPGamePad pad = g_pInput->GetGamePad(padNo);
	if (pad == nullptr)
	{
		return 0;
	}
	if (pad->GetPadState()->rgdwPOV[0] == DIRECTION.DOWN)
	{
		return 1.0f;
	}

	return 0;
}

#endif