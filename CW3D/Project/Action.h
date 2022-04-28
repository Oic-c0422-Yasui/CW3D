#pragma once

#include	"IAction.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		�A�N�V�������N���X
	 */
	class Action : public IAction
	{
	private:
		/** �p���N���X */
		TransformPtr					m_Transform;

		///** �A�j���[�V�����N���X */
		//AnimationStatePtr				animation_;

		/**
		 * @brief		�p���o�^
		 */
		void SetTransform(TransformPtr t) final { m_Transform = t; }

		///**
		// * @brief		�A�j���[�V�����o�^
		// */
		//void SetAnimation(AnimationStatePtr a) final { m_Transform = a; }
	protected:
		/** private�����o�擾��p */
		TransformPtr Transform() { return m_Transform; }
		//AnimationStatePtr AnimationState() { return m_Transform; }
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Action()
			: m_Transform(){
			//, animation_() {
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