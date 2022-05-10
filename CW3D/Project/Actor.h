#pragma once
#include	"IActor.h"

namespace Sample {

	/**
	 * @brief		アクション基底クラス
	 */
	class Actor : public IActor, public std::enable_shared_from_this<IActor>
	{
	protected:
		/** 姿勢 */
		TransformPtr			transform_;

		/** アクション */
		using ActionMap = std::unordered_map< ActionKeyType, ActionPtr >;
		ActionMap				actionMap_;

		/** パラメーター */
		//ParameterMapPtr			parameterMap_;

		/** モーション */
		AnimationStatePtr		motion_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		Actor()
			: enable_shared_from_this()
			, transform_(std::make_shared<Transform>())
			, actionMap_()
			//, parameterMap_()
			, motion_() {
		}

		/**
		 * @brief		アクションの追加
		 * @param[in]	key			アクションキー
		 * @param[in]	action		追加するアクション
		 */
		void AddAction(const ActionPtr& action) override {
			AddAction(action->GetKey(), action);
		}

		/**
		 * @brief		アクションの追加
		 * @param[in]	key			アクションキー
		 * @param[in]	action		追加するアクション
		 */
		void AddAction(const ActionKeyType& key, const ActionPtr& action) override {
			actionMap_[key] = action;
			action->SetTransform(transform_);
			//action->SetAnimation(motion_);
		}

		/**
		 * @brief		座標設定
		 */
		void SetPosition(CVector3 position) override {
			transform_->SetPosition(position);
		}

		/**
		 * @brief		回転設定
		 */
		void SetRotate(CVector3 rotate) override{
			transform_->SetRotate(rotate);
		}

		/**
		 * @brief		サイズ設定
		 */
		void SetScale(CVector3 scale) override {
			transform_->SetScale(scale);
		}

		/**
		 * @brief		アニメーション
		 */
		void SetAnimationState(AnimationStatePtr animState) override {
			motion_ = animState;
		}

		/**
		 * @brief		アクションの取得
		 * @param[in]	key			アクションキー
		 * @return		アクション
		 */
		ActionPtr GetAction(const ActionKeyType& key) override {
			auto& act = actionMap_.find(key);
			assert(act != actionMap_.end());
			return act->second;
		}


		/**
		 * @brief		姿勢取得
		 */
		TransformPtr GetTransform() const override {
			return transform_;
		}

		/**
		 * @brief		座標取得
		 */
		CVector3 GetPosition() const override {
			return transform_->GetPosition();
		}

		/**
		 * @brief		マトリクス取得
		 */
		CMatrix44 GetMatrix() const override {
			return transform_->GetWorld();
		}


		/**
		 * @brief		座標取得
		 */
		float GetPositionX() const override {
			return transform_->GetPositionX();
		}

		/**
		 * @brief		座標取得
		 */
		float GetPositionY() const override {
			return transform_->GetPositionY();
		}

		/**
		 * @brief		座標取得
		 */
		float GetPositionZ() const override {
			return transform_->GetPositionZ();
		}

		/**
		 * @brief		パラメーター
		 */
		/*ParameterMapPtr GetParameterMap() override {
			return parameterMap_;
		}*/

		/**
		 * @brief		パラメーター
		 */
		/*const ParameterMapPtr& GetParameterMap() const override {
			return parameterMap_;
		}*/

		/**
		 * @brief		アニメーション
		 */
		AnimationStatePtr GetAnimationState() const override {
			return motion_;
		}

	protected:
		/**
		 * @brief		パラメーター
		 */
		/*void SetParameterMap(ParameterMapPtr ptr) override {
			parameterMap_ = ptr;
		}*/
	};
}