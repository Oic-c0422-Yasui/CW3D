#pragma once
#include	"IActor.h"
#include	"IDManager.h"


namespace Sample {


	/**
	 * @brief		�A�N�V�������N���X
	 */
	class Actor : public IActor, public std::enable_shared_from_this<IActor>
	{
	protected:
		/** �p�� */
		TransformPtr			transform_;

		VelocityPtr				velocity_;

		/** �A�N�V���� */
		using ActionMap = std::unordered_map< ActionKeyType, ActionPtr >;
		ActionMap				actionMap_;

		/*�p�����[�^�[���*/
		AnyParameterMapPtr		parameters;

		SkillControllerPtr		m_SkillController;

		/** ���[�V���� */
		AnimationStatePtr		motion_;

		CMyID					myId_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Actor()
			: enable_shared_from_this()
			, transform_(std::make_shared<Transform>())
			, velocity_(std::make_shared<Velocity>())
			, actionMap_()
			, parameters(std::make_shared<AnyParameterMap>())
			, motion_()
			, m_SkillController(std::make_shared<CSkillController>())
			, myId_(IDManagerInstance.GetId())
		{
		}

		/**
		 * @brief		�A�N�^�[�̍X�V����
		 */
		void Update() override {
			//���x�X�V
			velocity_->Update();
			//���x�ō��W�ړ�
			transform_->MovePosition(velocity_);

			transform_->SetRotateY(velocity_->GetRotateY());

			m_SkillController->Update();
		}


		/**
		 * @brief		�A�N�V�����̒ǉ�
		 * @param[in]	key			�A�N�V�����L�[
		 * @param[in]	action		�ǉ�����A�N�V����
		 */
		void AddAction(const ActionPtr& action) override {
			AddAction(action->GetKey(), action);
		}

		/**
		 * @brief		�A�N�V�����̒ǉ�
		 * @param[in]	key			�A�N�V�����L�[
		 * @param[in]	action		�ǉ�����A�N�V����
		 */
		void AddAction(const ActionKeyType& key, const ActionPtr& action) override {
			actionMap_[key] = action;
			action->SetTransform(transform_);
			action->SetVelocity(velocity_);
			action->SetAnimation(motion_);
			action->SetParameterMap(parameters);
			action->SetSkillController(m_SkillController);
		}

		/**
		 * @brief		���W�ݒ�
		 */
		void SetPosition(const Vector3& position) override {
			transform_->SetPosition(position);
		}

		/**
		 * @brief		��]�ݒ�
		 */
		void SetRotate(const  Vector3& rotate) override{
			transform_->SetRotate(rotate);
		}

		/**
		 * @brief		�T�C�Y�ݒ�
		 */
		void SetScale(const Vector3& scale) override {
			transform_->SetScale(scale);
		}

		void SetReverse(bool isReverse) override{
			transform_->SetReverse(isReverse);
		}

		/**
		 * @brief		�A�j���[�V����
		 */
		void SetAnimationState(AnimationStatePtr animState) override {
			motion_ = animState;
		}

		/**
		 * @brief		�A�N�V�����̎擾
		 * @param[in]	key			�A�N�V�����L�[
		 * @return		�A�N�V����
		 */
		ActionPtr GetAction(const ActionKeyType& key) override {
			auto& act = actionMap_.find(key);
			assert(act != actionMap_.end());
			return act->second;
		}


		/**
		 * @brief		�p���擾
		 */
		TransformPtr GetTransform() const override {
			return transform_;
		}

		/**
		 * @brief		���x�擾
		 */
		VelocityPtr GetVelocity() const override {
			return velocity_;
		}

		/**
		 * @brief		���W�擾
		 */
		const CVector3& GetPosition() const override {
			return transform_->GetPosition();
		}

		/**
		 * @brief		��]�擾
		 */
		const CVector3& GetRotate() const override {
			return transform_->GetRotate();
		}

		/**
		 * @brief		�}�g���N�X�擾
		 */
		const CMatrix44& GetMatrix() const override {
			return transform_->GetWorld();
		}

		bool IsReverse() const{
			return transform_->IsReverse();
		}

		/**
		 * @brief		���W�擾
		 */
		float GetPositionX() const override {
			return transform_->GetPositionX();
		}

		/**
		 * @brief		���W�擾
		 */
		float GetPositionY() const override {
			return transform_->GetPositionY();
		}

		/**
		 * @brief		���W�擾
		 */
		float GetPositionZ() const override {
			return transform_->GetPositionZ();
		}

		/**
		 * @brief		ID�擾
		 */
		unsigned int GetID() const override {
			return myId_.GetID();
		}

		/**
		 * @brief		�p�����[�^�[
		 */
		const AnyParameterMapPtr& GetParameterMap() const override {
			return parameters;
		}

		/**
		 * @brief		�A�j���[�V����
		 */
		AnimationStatePtr GetAnimationState() const override {
			return motion_;
		}

		/**
		 * @brief		�X�L��
		 */
		SkillControllerPtr GetSkillController() const override {
			return m_SkillController;
		}

	};
}