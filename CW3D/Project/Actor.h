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
		TransformPtr			m_Transform;

		/*　速度 */
		VelocityPtr				velocity_;

		/* アクションマップ */
		using ActionMap = std::unordered_map< ActionKeyType, ActionPtr >;
		ActionMap				m_ActionMap;

		/*パラメーター情報*/
		AnyParameterMapPtr		m_Parameters;

		/*スキル操作*/
		SkillControllerPtr		m_SkillController;

		/* モーション */
		AnimationStatePtr		m_Motion;

		/* アクターID　*/
		CMyID					m_MyID;

		/* キャラタイプ　*/
		CHARA_TYPE				m_CharaType;


	public:
		/**
		 * @brief		コンストラクタ
		 */
		Actor()
			: enable_shared_from_this()
			, m_Transform(std::make_shared<Transform>())
			, velocity_(std::make_shared<Velocity>())
			, m_ActionMap()
			, m_Parameters(std::make_shared<AnyParameterMap>())
			, m_Motion()
			, m_SkillController(std::make_shared<CSkillController>())
			, m_MyID(IDManagerInstance.GetId())
			, m_CharaType()
		{
		}

		/**
		 * @brief		アクターの更新処理
		 */
		void Update() override {
			//速度更新
			velocity_->Update();
			//速度で座標移動
			m_Transform->AddPosition(velocity_);

			m_Transform->SetRotateY(velocity_->GetRotateY());

			m_SkillController->Update();
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
			m_ActionMap[key] = action;
			action->SetTransform(m_Transform);
			action->SetVelocity(velocity_);
			action->SetAnimation(m_Motion);
			action->SetParameterMap(m_Parameters);
			action->SetSkillController(m_SkillController);
		}

		/**
		 * @brief		座標設定
		 */
		void SetPosition(const Vector3& position) override {
			m_Transform->SetPosition(position);
		}

		/**
		 * @brief		回転設定
		 */
		void SetRotate(const  Vector3& rotate) override{
			m_Transform->SetRotate(rotate);
		}

		/**
		 * @brief		サイズ設定
		 */
		void SetScale(const Vector3& scale) override {
			m_Transform->SetScale(scale);
		}

		void SetReverse(bool isReverse) override{
			m_Transform->SetReverse(isReverse);
		}

		/**
		 * @brief		アニメーション
		 */
		void SetAnimationState(AnimationStatePtr animState) override {
			m_Motion = animState;
		}

		/**
		 * @brief		タイプ設定
		 */
		void SetType(CHARA_TYPE type) override {
			m_CharaType = type;
			m_Transform->SetType(type);
			velocity_->SetType(type);
		}

		/**
		 * @brief		アクションの取得
		 * @param[in]	key			アクションキー
		 * @return		アクション
		 */
		ActionPtr GetAction(const ActionKeyType& key) override {
			auto& act = m_ActionMap.find(key);
			assert(act != m_ActionMap.end());
			return act->second;
		}


		/**
		 * @brief		姿勢取得
		 */
		TransformPtr GetTransform() const override {
			return m_Transform;
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
			return m_Transform->GetPosition();
		}

		/**
		 * @brief		回転取得
		 */
		const CVector3& GetRotate() const override {
			return m_Transform->GetRotate();
		}

		/**
		 * @brief		マトリクス取得
		 */
		const CMatrix44& GetMatrix() const override {
			return m_Transform->GetWorld();
		}

		bool IsReverse() const{
			return m_Transform->IsReverse();
		}

		/**
		 * @brief		座標取得
		 */
		float GetPositionX() const override {
			return m_Transform->GetPositionX();
		}

		/**
		 * @brief		座標取得
		 */
		float GetPositionY() const override {
			return m_Transform->GetPositionY();
		}

		/**
		 * @brief		座標取得
		 */
		float GetPositionZ() const override {
			return m_Transform->GetPositionZ();
		}

		/**
		 * @brief		ID取得
		 */
		size_t GetID() const override {
			return m_MyID.GetID();
		}

		CHARA_TYPE GetType() const override {
			return m_CharaType;
		}

		/**
		 * @brief		パラメーター
		 */
		const AnyParameterMapPtr& GetParameterMap() const override {
			return m_Parameters;
		}

		/**
		 * @brief		アニメーション
		 */
		const AnimationStatePtr& GetAnimationState() const override {
			return m_Motion;
		}

		/**
		 * @brief		スキル
		 */
		const SkillControllerPtr& GetSkillController() const override {
			return m_SkillController;
		}

	};
}