#pragma once

#include "Transform.h"
#include "ParameterMap.h"
#include "SkillController.h"
#include "Collider.h"


namespace ActionGame {

	//�L�[
	using ActionKeyType = std::string;
	//�A�j���[�V�����p�̃V�F�A�|�C���^
	using AnimationStatePtr = LPMeshMotionController;
	/**
	 * @brief		�A�N�V�����C���^�[�t�F�C�X
	 */
	class IAction
	{
		//�A�N�^�[����̂ݓo�^���ł���l��friend�w��
		friend class Actor;
	private:
		/**
		 * @brief		�p���o�^
		 */
		virtual void SetTransform(TransformPtr transform) = 0;

		/**
		 * @brief		���x�o�^
		 */
		virtual void SetVelocity(VelocityPtr transform) = 0;

		/**
		 * @brief		�A�j���[�V�����o�^
		 */
		virtual void SetAnimation(AnimationStatePtr animation) = 0;

		/**
		 * @brief		�p�����[�^�[���o�^
		 */
		virtual void SetParameterMap(const AnyParameterMapPtr& parameter) = 0;

		/**
		 * @brief		�X�L������o�^
		 */
		virtual void SetSkillController(const SkillControllerPtr& skill) = 0;

		/**
		 * @brief		�����蔻��o�^
		 */
		virtual void SetCollider(const ColliderPtr& collider) = 0;

	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~IAction() = default;

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		virtual void Start() = 0;

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		virtual void Execution() = 0;

		/**
		 * @brief		�A�N�V�������̏I������
		 */
		virtual void End() = 0;

		/**
		 * @brief		�A�N�V�������̎擾
		 */
		virtual const ActionKeyType GetKey() const = 0;
	};
	//�|�C���^�u������
	using ActionPtr = std::shared_ptr<IAction>;

}
