#pragma once

#include "Transform.h"
#include "ShotManager.h"
#include "EffectController.h"
#include "ParameterMap.h"
#include "SkillController.h"

namespace Sample {

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
		virtual void SetTransform(TransformPtr t) = 0;

		/**
		 * @brief		���x�o�^
		 */
		virtual void SetVelocity(VelocityPtr t) = 0;

		/**
		 * @brief		�A�j���[�V�����o�^
		 */
		virtual void SetAnimation(AnimationStatePtr a) = 0;

		/**
		 * @brief		�p�����[�^�[���o�^
		 */
		virtual void SetParameterMap(const AnyParameterMapPtr& a) = 0;

		/**
		 * @brief		�p�����[�^�[���o�^
		 */
		virtual void SetSkillController(const SkillControllerPtr& a) = 0;

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
