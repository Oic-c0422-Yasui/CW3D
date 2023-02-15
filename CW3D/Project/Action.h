#pragma once

#include	"IAction.h"
#include	"AnimationDefine.h"
#include	"StateDefine.h"

namespace ActionGame {

	
	/**
	 * @brief		�A�N�V�������N���X
	 */
	class CAction : public IAction
	{
	private:
		/* �p���N���X */
		TransformPtr					m_Transform;

		/* ���x�N���X */
		VelocityPtr						m_Velocity;

		/* �A�j���[�V�����N���X */
		AnimationStatePtr				m_Animation;

		/* �p�����[�^�[���N���X */
		AnyParameterMapPtr				m_Parameters;

		/* �X�L������N���X */
		SkillControllerPtr				m_SkillController;
		

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

		/**
		 * @brief		�p�����[�^�[���o�^
		 */
		void SetParameterMap(const AnyParameterMapPtr& a) final { m_Parameters = a; }

		/**
		 * @brief		�X�L������o�^
		 */
		void SetSkillController(const SkillControllerPtr & a) final { m_SkillController = a; }

	protected:
		/** private�����o�擾��p */
		TransformPtr Transform() { return m_Transform; }
		VelocityPtr	 Velocity()	 { return m_Velocity; }
		AnimationStatePtr AnimationState() { return m_Animation; }
		AnyParameterMapPtr ParameterMap() { return m_Parameters; }
		SkillControllerPtr SkillController() { return m_SkillController; }
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CAction()
			: m_Transform()
			, m_Velocity()
			, m_Animation()
			, m_Parameters()
			, m_SkillController()
		{
		}

		/**
		 * @brief		�V�K�A�N�V�����̐���
		 * @return		���������A�N�V����
		 */
		template < typename T, typename... _Args >
		static std::shared_ptr< T > Create(_Args&& ... args) {
			if (!std::is_base_of<CAction, T >::value)
			{
				return std::shared_ptr<T>();
			}
			auto re = std::make_shared<T>(args...);
			return re;
		}
	};

}