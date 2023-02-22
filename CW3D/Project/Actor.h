#pragma once
#include	"IActor.h"
#include	"IDManager.h"



namespace ActionGame {


	/**
	 * @brief		�A�N�^�[�N���X
	 */
	class Actor : public IActor, public std::enable_shared_from_this<IActor>
	{
	protected:
		/* �p�� */
		TransformPtr			m_Transform;

		/*�@���x */
		VelocityPtr				velocity_;

		/* �A�N�V�����}�b�v */
		using ActionMap = std::unordered_map< ActionKeyType, ActionPtr >;
		ActionMap				m_ActionMap;

		/*�p�����[�^�[���*/
		AnyParameterMapPtr		m_Parameters;

		/*�X�L������*/
		SkillControllerPtr		m_SkillController;

		/* ���[�V���� */
		AnimationStatePtr		m_Motion;

		/* �A�N�^�[ID�@*/
		CMyID					m_MyID;

		/* �L�����^�C�v�@*/
		CHARA_TYPE				m_CharaType;


	public:
		/**
		 * @brief		�R���X�g���N�^
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
		 * @brief		�A�N�^�[�̍X�V����
		 */
		void Update() override {
			//���x�X�V
			velocity_->Update();
			//���x�ō��W�ړ�
			m_Transform->AddPosition(velocity_);

			m_Transform->SetRotateY(velocity_->GetRotateY());

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
			m_ActionMap[key] = action;
			action->SetTransform(m_Transform);
			action->SetVelocity(velocity_);
			action->SetAnimation(m_Motion);
			action->SetParameterMap(m_Parameters);
			action->SetSkillController(m_SkillController);
		}

		/**
		 * @brief		���W�ݒ�
		 */
		void SetPosition(const Vector3& position) override {
			m_Transform->SetPosition(position);
		}

		/**
		 * @brief		��]�ݒ�
		 */
		void SetRotate(const  Vector3& rotate) override{
			m_Transform->SetRotate(rotate);
		}

		/**
		 * @brief		�T�C�Y�ݒ�
		 */
		void SetScale(const Vector3& scale) override {
			m_Transform->SetScale(scale);
		}

		void SetReverse(bool isReverse) override{
			m_Transform->SetReverse(isReverse);
		}

		/**
		 * @brief		�A�j���[�V����
		 */
		void SetAnimationState(AnimationStatePtr animState) override {
			m_Motion = animState;
		}

		/**
		 * @brief		�^�C�v�ݒ�
		 */
		void SetType(CHARA_TYPE type) override {
			m_CharaType = type;
			m_Transform->SetType(type);
			velocity_->SetType(type);
		}

		/**
		 * @brief		�A�N�V�����̎擾
		 * @param[in]	key			�A�N�V�����L�[
		 * @return		�A�N�V����
		 */
		ActionPtr GetAction(const ActionKeyType& key) override {
			auto& act = m_ActionMap.find(key);
			assert(act != m_ActionMap.end());
			return act->second;
		}


		/**
		 * @brief		�p���擾
		 */
		TransformPtr GetTransform() const override {
			return m_Transform;
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
			return m_Transform->GetPosition();
		}

		/**
		 * @brief		��]�擾
		 */
		const CVector3& GetRotate() const override {
			return m_Transform->GetRotate();
		}

		/**
		 * @brief		�}�g���N�X�擾
		 */
		const CMatrix44& GetMatrix() const override {
			return m_Transform->GetWorld();
		}

		bool IsReverse() const{
			return m_Transform->IsReverse();
		}

		/**
		 * @brief		���W�擾
		 */
		float GetPositionX() const override {
			return m_Transform->GetPositionX();
		}

		/**
		 * @brief		���W�擾
		 */
		float GetPositionY() const override {
			return m_Transform->GetPositionY();
		}

		/**
		 * @brief		���W�擾
		 */
		float GetPositionZ() const override {
			return m_Transform->GetPositionZ();
		}

		/**
		 * @brief		ID�擾
		 */
		size_t GetID() const override {
			return m_MyID.GetID();
		}

		CHARA_TYPE GetType() const override {
			return m_CharaType;
		}

		/**
		 * @brief		�p�����[�^�[
		 */
		const AnyParameterMapPtr& GetParameterMap() const override {
			return m_Parameters;
		}

		/**
		 * @brief		�A�j���[�V����
		 */
		const AnimationStatePtr& GetAnimationState() const override {
			return m_Motion;
		}

		/**
		 * @brief		�X�L��
		 */
		const SkillControllerPtr& GetSkillController() const override {
			return m_SkillController;
		}

	};
}