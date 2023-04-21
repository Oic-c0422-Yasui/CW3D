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
		// �p���Ǘ��N���X
		TransformPtr					transform_;

		// ���x�Ǘ��N���X 
		VelocityPtr						velocity_;

		// �A�j���[�V�����N���X 
		AnimationStatePtr				animation_;

		// �p�����[�^���N���X
		AnyParameterMapPtr				parameters_;

		// �X�L������N���X
		SkillControllerPtr				skillController_;
		
		//�@�����蔻��N���X
		ColliderPtr						collider_;

		/**
		 * @brief		�p���o�^
		 */
		void SetTransform(TransformPtr transform) final 
		{ 
			transform_ = transform;
		}

		/**
		 * @brief		�p���o�^
		 */
		void SetVelocity(VelocityPtr velocity) final 
		{ 
			velocity_ = velocity;
		}

		///**
		// * @brief		�A�j���[�V�����o�^
		// */
		void SetAnimation(AnimationStatePtr animation)  
		{ 
			animation_ = animation; 
		}

		/**
		 * @brief		�p�����[�^�[���o�^
		 */
		void SetParameterMap(const AnyParameterMapPtr& parameter) final 
		{ 
			parameters_ = parameter; 
		}

		/**
		 * @brief		�X�L������o�^
		 */
		void SetSkillController(const SkillControllerPtr & skill) final 
		{ 
			skillController_ = skill; 
		}

		/**
		 * @brief		�����蔻��o�^
		 */
		void SetCollider(const ColliderPtr& collider) final
		{
			collider_ = collider;
		}

	protected:
		/** private�����o�擾��p */
		//�p���N���X
		TransformPtr Transform() { return transform_; }
		//���x�N���X
		VelocityPtr	 Velocity()	 { return velocity_; }
		//�A�j���[�V�����N���X
		AnimationStatePtr AnimationState() { return animation_; }
		//�p�����[�^���N���X
		AnyParameterMapPtr ParameterMap() { return parameters_; }
		//�X�L������N���X
		SkillControllerPtr SkillController() { return skillController_; }
		//�����蔻��
		ColliderPtr		Collider() { return collider_; }
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CAction()
			: transform_()
			, velocity_()
			, animation_()
			, parameters_()
			, skillController_()
			, collider_()
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