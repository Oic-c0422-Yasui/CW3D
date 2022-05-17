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

		/** ���x�N���X */
		VelocityPtr						m_Velocity;

		///** �A�j���[�V�����N���X */
		AnimationStatePtr				m_Animation;

		

		/**
		 * @brief		�p���o�^
		 */
		void SetTransform(TransformPtr t) final { m_Transform = t; }

		/**
		 * @brief		�p���o�^
		 */
		void SetVelocity(VelocityPtr v) final { m_Velocity = v; }

		///**
		// * @brief		�A�j���[�V�����o�^
		// */
		void SetAnimation(AnimationStatePtr a)  { m_Animation = a; }
	protected:
		/** private�����o�擾��p */
		TransformPtr Transform() { return m_Transform; }
		VelocityPtr	 Velocity()	 { return m_Velocity; }
		AnimationStatePtr AnimationState() { return m_Animation; }
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Action()
			: m_Transform()
			, m_Velocity()
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