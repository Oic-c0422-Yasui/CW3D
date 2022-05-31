#pragma once

#include "IAction.h"

#include "Common.h"
#include "ShotManager.h"


namespace Sample {

	
	//�A�j���[�V�����p�̃V�F�A�|�C���^
	using AnimationStatePtr = LPMeshMotionController;

	/**
	 * @brief		�A�N�^�[�C���^�[�t�F�C�X
	 */
	class IActor
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~IActor() = default;

		/**
		 * @brief		�A�N�^�[�̍X�V����
		 */
		virtual void Update() = 0;

		/**
		 * @brief		�A�N�V�����̒ǉ�
		 * @param[in]	name		�A�N�V������
		 * @param[in]	action		�ǉ�����A�N�V����
		 */
		virtual void AddAction(const ActionPtr& action) = 0;

		/**
		 * @brief		�A�N�V�����̒ǉ�
		 * @param[in]	key			�A�N�V�����L�[
		 * @param[in]	action		�ǉ�����A�N�V����
		 */
		virtual void AddAction(const ActionKeyType& key, const ActionPtr& action) = 0;

		/**
		 * @brief		�A�N�V�����̎擾
		 * @param[in]	key			�A�N�V�����L�[
		 * @return		�A�N�V����
		 */
		virtual ActionPtr GetAction(const ActionKeyType& key) = 0;

		/**
		 * @brief		�A�N�V�����̎擾
		 * @param[in]	key			�A�N�V�����L�[
		 * @return		�A�N�V����
		 */
		template< typename T >
		std::shared_ptr< T > GetAction(const ActionKeyType& key) {
			return std::dynamic_pointer_cast<T>(GetAction(key));
		}

		/**
		 * @brief		���W�ݒ�
		 */
		virtual void SetPosition(CVector3 position) = 0;

		/**
		 * @brief		��]�ݒ�
		 */
		virtual void SetRotate(CVector3 rotate) = 0;

		/**
		 * @brief		�T�C�Y�ݒ�
		 */
		virtual void SetScale(CVector3 scale) = 0;


		virtual void SetReverse(bool isReverse) = 0;

		///**
		// * @brief		�A�j���[�V����
		// */
		virtual void SetAnimationState(AnimationStatePtr animState) = 0;

		/**
		 * @brief		�p���擾
		 */
		virtual TransformPtr GetTransform() const = 0;

		/**
		 * @brief		���x�擾
		 */
		virtual VelocityPtr GetVelocity() const = 0;

		/**
		 * @brief		���W�擾
		 */
		virtual CVector3 GetPosition() const = 0;

		/**
		 * @brief		��]�擾
		 */
		virtual CVector3 GetRotate() const = 0;

		/**
		 * @brief		�}�g���N�X�擾
		 */
		virtual CMatrix44 GetMatrix() const = 0;

		/**
		 * @brief		���]�擾
		 */
		virtual bool IsReverse() const = 0;

		/**
		 * @brief		���W�擾
		 */
		virtual float GetPositionX() const = 0;

		/**
		 * @brief		���W�擾
		 */
		virtual float GetPositionY() const = 0;

		/**
		 * @brief		���W�擾
		 */
		virtual float GetPositionZ() const = 0;


		/**
		 * @brief		�p�����[�^�[
		 */
		virtual const AnyParameterMapPtr& GetParameterMap() const = 0;

		///**
		// * @brief		�A�j���[�V����
		// */
		virtual AnimationStatePtr GetAnimationState() const = 0;

		///**
		// * @brief		�X�L��
		// */
		virtual SkillControllerPtr GetSkillController() const = 0;

	protected:

	};
	//�|�C���^�u������
	using ActorPtr = std::shared_ptr<IActor>;
	using ActorWeakPtr = std::weak_ptr<IActor>;
}