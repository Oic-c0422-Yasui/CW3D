#pragma once
#include "StateAI.h"


namespace ActionGame
{

    class CBaseStateAI : public CStateAI
    {
    protected:
		/*
		* @brief	範囲内にいるか
		*/
		bool IsInRange(const Vector3& size, const CAABB& target);
		/*
		* @brief	範囲内にいるか
		*/
		bool IsInRange(float distance, const Vector3& target);

		/*
		* @brief	移動入力
		*/
		void InputMove(float distance,const Vector3& target);

		float GetDistance(const Vector3& target);

    public:
        CBaseStateAI();

		/**
		 * @brief		利用キーの登録
		 */
		virtual void RegisterKey() override = 0;

		/**
		 * @brief		開始
		 */
		virtual void Start() override = 0;

		/**
		 * @brief		更新
		 */
		virtual void Update() override = 0;

		/**
		 * @brief		終了
		 */
		virtual void End() override = 0;
    };
}
