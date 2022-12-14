#pragma once

#include "IAction.h"

#include "Common.h"
#include "ReactiveParameter.h"
#include "ParameterHandle.h"


namespace ActionGame {

	
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
		virtual void SetPosition(const Vector3& position) = 0;

		/**
		 * @brief		��]�ݒ�
		 */
		virtual void SetRotate(const Vector3& rotate) = 0;

		/**
		 * @brief		�T�C�Y�ݒ�
		 */
		virtual void SetScale(const Vector3& scale) = 0;

		/**
		 * @brief		���]�ݒ�
		 */
		virtual void SetReverse(bool isReverse) = 0;

		/**
		 * @brief		�A�j���[�V�����ݒ�
		 */
		virtual void SetAnimationState(AnimationStatePtr animState) = 0;

		/**
		 * @brief		�L�����^�C�v�ݒ�
		 */
		virtual void SetType(CHARACTER_TYPE type) = 0;

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
		virtual const CVector3& GetPosition() const = 0;

		/**
		 * @brief		��]�擾
		 */
		virtual const CVector3& GetRotate() const = 0;

		/**
		 * @brief		�}�g���N�X�擾
		 */
		virtual const CMatrix44& GetMatrix() const = 0;

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
		 * @brief		ID�擾
		 */
		virtual unsigned int GetID() const = 0;

		/**
		 * @brief		�^�C�v�擾
		 */
		virtual CHARACTER_TYPE GetType() const = 0;

		/**
		 * @brief		�p�����[�^�[
		 */
		virtual const AnyParameterMapPtr& GetParameterMap() const = 0;

		/**
		 * @brief		�A�j���[�V����
		 */
		virtual const AnimationStatePtr& GetAnimationState() const = 0;

		/**
		 * @brief		�X�L��
		 */
		virtual const SkillControllerPtr& GetSkillController() const = 0;

		/*
		* @brief	�ڐG�������擾
		*/
		virtual bool IsThrough() const = 0;

		/*
		* @brief	�ڐG������ݒ�
		*/
		virtual void SetThrough(bool isThrough) = 0;

		/*
		* @brief	�A�[�}�[���x���擾
		*/
		virtual BYTE GetArmorLevel() const = 0;

		/*
		* @brief	�A�[�}�[���x���ݒ�
		*/
		virtual void SetArmorLevel(BYTE armor) = 0;

	};
	//�|�C���^�u������
	using ActorPtr = std::shared_ptr<IActor>;
	using ActorWeakPtr = std::weak_ptr<IActor>;
}