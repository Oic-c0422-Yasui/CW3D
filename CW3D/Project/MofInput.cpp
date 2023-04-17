#include	"MofInput.h"

#ifdef __MOFLIB
#include	<Mof.h>

using namespace Input;

/**
 * @brief		キーボードキーの取得
 * @param[in]	positive		＋方向のキー
 * @param[in]	negative		－方向のキー
 * @return		キー入力の値
 */
float CMofInput::GetKeyboardKeyState(int positive, int negative) const {
	if (positive >= 0 && g_pInput->IsKeyHold(positive)) { return 1.0f; }
	if (negative >= 0 && g_pInput->IsKeyHold(negative)) { return -1.0f; }
	return 0;
}


/**
 * @brief		マウスキーの取得
 * @param[in]	positive		＋方向のキー
 * @param[in]	negative		－方向のキー
 * @return		キー入力の値
 */
float CMofInput::GetMouseKeyState(int positive, int negative) const {
	if (positive >= 0 && g_pInput->IsMouseKeyHold(positive)) { return 1.0f; }
	if (negative >= 0 && g_pInput->IsMouseKeyHold(negative)) { return -1.0f; }
	return 0;
}

/**
 * @brief		ジョイパッドキーの取得
 * @param[in]	padNo			パッド番号
 * @param[in]	positive		＋方向のキー
 * @param[in]	negative		－方向のキー
 * @return		キー入力の値
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
 * @brief		ジョイパッドスティックの取得
 * @param[in]	padNo			パッド番号
 * @return		キー入力の値
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
 * @brief		ジョイパッドスティックの取得
 * @param[in]	padNo			パッド番号
 * @return		キー入力の値
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
 * @brief		右ジョイパッドスティックの取得
 * @param[in]	padNo			パッド番号
 * @return		キー入力の値
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
 * @brief		右ジョイパッドスティックの取得
 * @param[in]	padNo			パッド番号
 * @return		キー入力の値
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
 * @brief		ジョイパッド十字キーの左キー取得
 * @param[in]	padNo			パッド番号
 * @return		キー入力の値
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
 * @brief		ジョイパッド十字キーの右キー取得
 * @param[in]	padNo			パッド番号
 * @return		キー入力の値
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
 * @brief		ジョイパッド十字キーの上キー取得
 * @param[in]	padNo			パッド番号
 * @return		キー入力の値
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
 * @brief		ジョイパッド十字キーの下キー取得
 * @param[in]	padNo			パッド番号
 * @return		キー入力の値
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