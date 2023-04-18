#pragma once

#include	"Input.h"

#ifdef __MOFLIB

namespace Input {

	/**
	 * @brief		入力クラス
	 */
	class CMofInput : public CInput
	{
	protected:
		//最小入力値
		const float MIN_INPUT = 0.3f;
		//スティック最大入力量
		const float MAX_INPUTSTICK = 1000.0f;
		//十字キー入力値
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
		 * @brief		キーボードキーの取得
		 * @param[in]	positive		＋方向のキー
		 * @param[in]	negative		－方向のキー
		 * @return		キー入力の値
		 */
		float GetKeyboardKeyState(int positive, int negative) const override;

		/**
		 * @brief		マウスキーの取得
		 * @param[in]	positive		＋方向のキー
		 * @param[in]	negative		－方向のキー
		 * @return		キー入力の値
		 */
		float GetMouseKeyState(int positive, int negative) const override;

		/**
		 * @brief		ジョイパッドキーの取得
		 * @param[in]	padNo			パッド番号
		 * @param[in]	positive		＋方向のキー
		 * @param[in]	negative		－方向のキー
		 * @return		キー入力の値
		 */
		float GetJoypadKeyState(int padNo, int positive, int negative) const override;

		/**
		 * @brief		左ジョイパッドスティックの取得
		 * @param[in]	padNo			パッド番号
		 * @return		キー入力の値
		 */
		float GetLeftJoyStickHorizontal(int padNo) const override;

		/**
		 * @brief		左ジョイパッドスティックの取得
		 * @param[in]	padNo			パッド番号
		 * @return		キー入力の値
		 */
		float GetLeftJoyStickVertical(int padNo) const override;

		/**
		 * @brief		右ジョイパッドスティックの取得
		 * @param[in]	padNo			パッド番号
		 * @return		キー入力の値
		 */
		float GetRightJoyStickHorizontal(int padNo) const override;

		/**
		 * @brief		右ジョイパッドスティックの取得
		 * @param[in]	padNo			パッド番号
		 * @return		キー入力の値
		 */
		float GetRightJoyStickVertical(int padNo) const override;

		/**
		 * @brief		ジョイパッド十字キーのキー取得
		 * @param[in]	padNo			パッド番号
		 * @param[in]	direction		キーの方向
		 * @return		キー入力の値
		 */
		float GetDPadKeyState(int padNo,DPad_Direction direction) const override;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CMofInput();
	};

}

#endif