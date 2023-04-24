#pragma once
#include "State.h"

namespace ActionGame
{
    /**
     * @brief		ベースのステートクラス
     */
    class CBaseState : public CState
    {
	protected:
		/* プライベート関数 */

		/*
		* @brief	左右キーが押されているか？
		*/
		bool IsPressHorizontalKey();
		/*
		* @brief	上下キーが押されているか？
		*/
		bool IsPressVirticalKey();
		/*
		* @brief	いずれかの移動キーが押されているか？
		*/
		bool IsPressMoveKey();

		/*
		* @brief	空中にいるか？
		*/
		bool IsFly();

		/*
		* @brief	押されているキーに合わせたスキルに変更する
		*/
		void ChangeSkillState();

		/*
		* @brief	タイムスケールが０以下か？
		*/
		bool IsTimeScaleZero();

		/*
		* @brief	空中状態かで状態変更を切り替える
		* @param	state	地上ステート
		* @param	flyState	空中ステート
		*/
		void SwitchFlyChangeState(const StateKeyType& state, const StateKeyType& flyState);

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CBaseState();

		/**
		 * @brief		ステート内の開始処理
		 */
		virtual void Start() override = 0;

		/**
		 * @brief		ステート内の実行処理
		 */
		virtual void Execution() override = 0;

		/**
		 * @brief		ステート内の入力処理
		 */
		virtual void InputExecution() override = 0;

		/**
		 * @brief		ステート内の終了処理
		 */
		virtual void End() override = 0;

    };

}

