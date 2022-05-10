#pragma once

#include "IAction.h"

#include "Mof.h"


namespace Sample {

	
	//アニメーション用のシェアポインタ
	using AnimationStatePtr = std::shared_ptr<CMeshMotionController>;

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

		///**
		// * @brief		パラメーターマップの生成
		// */
		//template< typename... Types >
		//void CreateParameterMap() {
		//	SetParameterMap(std::make_shared<ParameterMap<Types...>>());
		//}

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
		virtual void SetPosition(CVector3 position) = 0;

		/**
		 * @brief		回転設定
		 */
		virtual void SetRotate(CVector3 rotate) = 0;

		/**
		 * @brief		サイズ設定
		 */
		virtual void SetScale(CVector3 scale) = 0;

		///**
		// * @brief		アニメーション
		// */
		virtual void SetAnimationState(AnimationStatePtr animState) = 0;

		/**
		 * @brief		姿勢取得
		 */
		virtual TransformPtr GetTransform() const = 0;

		/**
		 * @brief		座標取得
		 */
		virtual CVector3 GetPosition() const = 0;

		/**
		 * @brief		マトリクス取得
		 */
		virtual CMatrix44 GetMatrix() const = 0;

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



		///**
		// * @brief		パラメーター
		// */
		//virtual ParameterMapPtr GetParameterMap() = 0;

		///**
		// * @brief		パラメーター
		// */
		//virtual const ParameterMapPtr& GetParameterMap() const = 0;

		///**
		// * @brief		登録パラメーターの設定
		// */
		//template <typename T>
		//void SetParameter(const ParameterKeyType& key, const T& value)
		//{
		//	return GetParameterMap()->Set<T>(key, value);
		//}

		///**
		// * @brief		登録パラメーターの取得
		// */
		//template <typename T>
		//ParameterHandle<T>& GetParameter(const ParameterKeyType& key)
		//{
		//	return GetParameterMap()->Get<T>(key);
		//}

		///**
		// * @brief		アニメーション
		// */
		virtual AnimationStatePtr GetAnimationState() const = 0;

	protected:
		///**
		// * @brief		パラメーター
		// */
		//virtual void SetParameterMap(ParameterMapPtr ptr) = 0;
	};
	//ポインタ置き換え
	using ActorPtr = std::shared_ptr<IActor>;
	using ActorWeakPtr = std::weak_ptr<IActor>;
}