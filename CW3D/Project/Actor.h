#pragma once
#include	"IActor.h"
#include	"IDManager.h"



namespace ActionGame {


	/**
	 * @brief		アクタークラス
	 */
	class Actor : public IActor, public std::enable_shared_from_this<IActor>
	{
	protected:
		/* 姿勢 */
		TransformPtr			transform_;

		/*　速度 */
		VelocityPtr				velocity_;

		/* アクションマップ */
		using ActionMap = std::unordered_map< ActionKeyType, ActionPtr >;
		ActionMap				actionMap_;

		/*パラメーター情報*/
		AnyParameterMapPtr		parameters_;

		/*スキル操作*/
		SkillControllerPtr		skillController_;

		/* モーション */
		AnimationStatePtr		motion_;

		/* アクターID　*/
		CMyID					myID_;

		/* キャラタイプ　*/
		CHARA_TYPE				charaType_;

		/* 当たり判定　*/
		ColliderPtr				collider_;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		Actor();
			

		/**
		 * @brief		アクターの更新処理
		 */
		void Update() override;


		/**
		 * @brief		アクションの追加
		 * @param[in]	key			アクションキー
		 * @param[in]	action		追加するアクション
		 */
		void AddAction(const ActionPtr& action) override;

		/**
		 * @brief		アクションの追加
		 * @param[in]	key			アクションキー
		 * @param[in]	action		追加するアクション
		 */
		void AddAction(const ActionKeyType& key, const ActionPtr& action) override;

		/**
		 * @brief		座標設定
		 */
		void SetPosition(const Vector3& position) override {
			transform_->SetPosition(position);
		}

		/**
		 * @brief		回転設定
		 */
		void SetRotate(const  Vector3& rotate) override{
			transform_->SetRotate(rotate);
		}

		/**
		 * @brief		サイズ設定
		 */
		void SetScale(const Vector3& scale) override {
			transform_->SetScale(scale);
		}

		void SetReverse(bool isReverse) override{
			transform_->SetReverse(isReverse);
		}

		/**
		 * @brief		アニメーション
		 */
		void SetAnimationState(AnimationStatePtr animState) override {
			motion_ = animState;
		}

		/**
		 * @brief		タイプ設定
		 */
		void SetType(CHARA_TYPE type) override {
			charaType_ = type;
			transform_->SetType(type);
			velocity_->SetType(type);
		}

		/**
		 * @brief		当たり判定設定
		 */
		void SetCollider(const ColliderPtr& collider) override {
			collider_ = collider;
		}

		/**
		 * @brief		アクションの取得
		 * @param[in]	key			アクションキー
		 * @retval		true アクション
		 * @retval		false nullptr
		 */
		ActionPtr GetAction(const ActionKeyType& key) override {
			auto& act = actionMap_.find(key);
			if (act == actionMap_.end())
			{
				return nullptr;
			}
			return act->second;
		}


		/**
		 * @brief		姿勢取得
		 */
		TransformPtr GetTransform() const override {
			return transform_;
		}

		/**
		 * @brief		速度取得
		 */
		VelocityPtr GetVelocity() const override {
			return velocity_;
		}

		/**
		 * @brief		座標取得
		 */
		const CVector3& GetPosition() const override {
			return transform_->GetPosition();
		}

		/**
		 * @brief		回転取得
		 */
		const CVector3& GetRotate() const override {
			return transform_->GetRotate();
		}

		/**
		 * @brief		マトリクス取得
		 */
		const CMatrix44& GetMatrix() const override {
			return transform_->GetWorld();
		}

		bool IsReverse() const{
			return transform_->IsReverse();
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
		 * @brief		ID取得
		 */
		uint32_t GetID() const override {
			return myID_.GetID();
		}

		CHARA_TYPE GetType() const override {
			return charaType_;
		}

		/**
		* @brief	当たり判定取得
		*/
		const ColliderPtr& GetCollider() const override {
			return collider_;
		}

		/**
		 * @brief		パラメーター
		 */
		const AnyParameterMapPtr& GetParameterMap() const override {
			return parameters_;
		}

		/**
		 * @brief		アニメーション
		 */
		const AnimationStatePtr& GetAnimationState() const override {
			return motion_;
		}

		/**
		 * @brief		スキル
		 */
		const SkillControllerPtr& GetSkillController() const override {
			return skillController_;
		}

	};
}