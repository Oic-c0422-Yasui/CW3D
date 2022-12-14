#pragma once

#include "IAction.h"

#include "Common.h"
#include "ReactiveParameter.h"
#include "ParameterHandle.h"


namespace ActionGame {

	
	//アニメーション用のシェアポインタ
	using AnimationStatePtr = LPMeshMotionController;

	/**
	 * @brief		アクターインターフェイス
	 */
	class IActor
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~IActor() = default;

		/**
		 * @brief		アクターの更新処理
		 */
		virtual void Update() = 0;

		/**
		 * @brief		アクションの追加
		 * @param[in]	name		アクション名
		 * @param[in]	action		追加するアクション
		 */
		virtual void AddAction(const ActionPtr& action) = 0;

		/**
		 * @brief		アクションの追加
		 * @param[in]	key			アクションキー
		 * @param[in]	action		追加するアクション
		 */
		virtual void AddAction(const ActionKeyType& key, const ActionPtr& action) = 0;

		/**
		 * @brief		アクションの取得
		 * @param[in]	key			アクションキー
		 * @return		アクション
		 */
		virtual ActionPtr GetAction(const ActionKeyType& key) = 0;

		/**
		 * @brief		アクションの取得
		 * @param[in]	key			アクションキー
		 * @return		アクション
		 */
		template< typename T >
		std::shared_ptr< T > GetAction(const ActionKeyType& key) {
			return std::dynamic_pointer_cast<T>(GetAction(key));
		}

		/**
		 * @brief		座標設定
		 */
		virtual void SetPosition(const Vector3& position) = 0;

		/**
		 * @brief		回転設定
		 */
		virtual void SetRotate(const Vector3& rotate) = 0;

		/**
		 * @brief		サイズ設定
		 */
		virtual void SetScale(const Vector3& scale) = 0;

		/**
		 * @brief		反転設定
		 */
		virtual void SetReverse(bool isReverse) = 0;

		/**
		 * @brief		アニメーション設定
		 */
		virtual void SetAnimationState(AnimationStatePtr animState) = 0;

		/**
		 * @brief		キャラタイプ設定
		 */
		virtual void SetType(CHARACTER_TYPE type) = 0;

		/**
		 * @brief		姿勢取得
		 */
		virtual TransformPtr GetTransform() const = 0;

		/**
		 * @brief		速度取得
		 */
		virtual VelocityPtr GetVelocity() const = 0;

		/**
		 * @brief		座標取得
		 */
		virtual const CVector3& GetPosition() const = 0;

		/**
		 * @brief		回転取得
		 */
		virtual const CVector3& GetRotate() const = 0;

		/**
		 * @brief		マトリクス取得
		 */
		virtual const CMatrix44& GetMatrix() const = 0;

		/**
		 * @brief		反転取得
		 */
		virtual bool IsReverse() const = 0;

		/**
		 * @brief		座標取得
		 */
		virtual float GetPositionX() const = 0;

		/**
		 * @brief		座標取得
		 */
		virtual float GetPositionY() const = 0;

		/**
		 * @brief		座標取得
		 */
		virtual float GetPositionZ() const = 0;

		/**
		 * @brief		ID取得
		 */
		virtual unsigned int GetID() const = 0;

		/**
		 * @brief		タイプ取得
		 */
		virtual CHARACTER_TYPE GetType() const = 0;

		/**
		 * @brief		パラメーター
		 */
		virtual const AnyParameterMapPtr& GetParameterMap() const = 0;

		/**
		 * @brief		アニメーション
		 */
		virtual const AnimationStatePtr& GetAnimationState() const = 0;

		/**
		 * @brief		スキル
		 */
		virtual const SkillControllerPtr& GetSkillController() const = 0;

		/*
		* @brief	接触判定回避取得
		*/
		virtual bool IsThrough() const = 0;

		/*
		* @brief	接触判定回避設定
		*/
		virtual void SetThrough(bool isThrough) = 0;

		/*
		* @brief	アーマーレベル取得
		*/
		virtual BYTE GetArmorLevel() const = 0;

		/*
		* @brief	アーマーレベル設定
		*/
		virtual void SetArmorLevel(BYTE armor) = 0;

	};
	//ポインタ置き換え
	using ActorPtr = std::shared_ptr<IActor>;
	using ActorWeakPtr = std::weak_ptr<IActor>;
}