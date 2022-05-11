#pragma once

#include "IAction.h"

#include "Mof.h"


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

		///**
		// * @brief		�p�����[�^�[�}�b�v�̐���
		// */
		//template< typename... Types >
		//void CreateParameterMap() {
		//	SetParameterMap(std::make_shared<ParameterMap<Types...>>());
		//}

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

		///**
		// * @brief		�A�j���[�V����
		// */
		virtual void SetAnimationState(AnimationStatePtr animState) = 0;

		/**
		 * @brief		�p���擾
		 */
		virtual TransformPtr GetTransform() const = 0;

		/**
		 * @brief		���W�擾
		 */
		virtual CVector3 GetPosition() const = 0;

		/**
		 * @brief		�}�g���N�X�擾
		 */
		virtual CMatrix44 GetMatrix() const = 0;

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



		///**
		// * @brief		�p�����[�^�[
		// */
		//virtual ParameterMapPtr GetParameterMap() = 0;

		///**
		// * @brief		�p�����[�^�[
		// */
		//virtual const ParameterMapPtr& GetParameterMap() const = 0;

		///**
		// * @brief		�o�^�p�����[�^�[�̐ݒ�
		// */
		//template <typename T>
		//void SetParameter(const ParameterKeyType& key, const T& value)
		//{
		//	return GetParameterMap()->Set<T>(key, value);
		//}

		///**
		// * @brief		�o�^�p�����[�^�[�̎擾
		// */
		//template <typename T>
		//ParameterHandle<T>& GetParameter(const ParameterKeyType& key)
		//{
		//	return GetParameterMap()->Get<T>(key);
		//}

		///**
		// * @brief		�A�j���[�V����
		// */
		virtual AnimationStatePtr GetAnimationState() const = 0;

	protected:
		///**
		// * @brief		�p�����[�^�[
		// */
		//virtual void SetParameterMap(ParameterMapPtr ptr) = 0;
	};
	//�|�C���^�u������
	using ActorPtr = std::shared_ptr<IActor>;
	using ActorWeakPtr = std::weak_ptr<IActor>;
}