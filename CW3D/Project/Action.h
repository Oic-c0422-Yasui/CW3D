#pragma once

#include	"IAction.h"
#include	"GameDefine.h"

namespace Sample {

	//�A�j���[�V�����p�̃V�F�A�|�C���^
	using AnimationStatePtr = std::shared_ptr<CMeshMotionController>;
	/**
	 * @brief		�A�N�V�������N���X
	 */
	class Action : public IAction
	{
	private:
		/** �p���N���X */
		TransformPtr					m_Transform;

		///** �A�j���[�V�����N���X */
		AnimationStatePtr				m_Animation;

		/**
		 * @brief		�p���o�^
		 */
		void SetTransform(TransformPtr t) final { m_Transform = t; }

		///**
		// * @brief		�A�j���[�V�����o�^
		// */
		void SetAnimation(AnimationStatePtr a)  { m_Animation = a; }
	protected:
		/** private�����o�擾��p */
		TransformPtr Transform() { return m_Transform; }
		AnimationStatePtr AnimationState() { return m_Animation; }
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Action()
			: m_Transform()
			, m_Animation() {
		}

		/**
		 * @brief		�V�K�A�N�V�����̐���
		 * @return		���������A�N�V����
		 */
		template < typename T >
		static std::shared_ptr< T > Create() {
			if (!std::is_base_of<Action, T >::value)
			{
				return std::shared_ptr<T>();
			}
			auto re = std::make_shared<T>();
			return re;
		}
	};

}