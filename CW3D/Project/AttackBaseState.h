#pragma once


#include	"BaseState.h"
#include	"FixedKnockBack.h"
#include	"EffectController.h"
#include	"ShotManager.h"
#include	"SkillDefine.h"
#include	"DamageUtilities.h"
#include	"MoveCompensationAction.h"

namespace ActionGame {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class CAttackBaseState : public CBaseState
	{
	public:
		typedef struct BASEPARAM
		{
			BYTE armorLevel;
		}BaseParam;
		

	protected:
		
		float							currentTime_;
		
		//���X�e�[�g�̃C���v�b�g��������Ă��邩�H
		bool							isNextInput_;


		std::vector<ShotPtr>			shots_;
		std::vector<EffectPtr>			effects_;

		//�ړ��␳�A�N�V����
		MoveCompensationActionPtr		moveCompensation_;

	protected:
		/* �v���C�x�[�g�֐� */

		//�V���b�g���
		void ReleaseShot();
		//�G�t�F�N�g���
		void ReleaseEffect();
		//�m�b�N�o�b�N�擾
		virtual const KnockBackPtr GetKnockBack() { return std::make_shared<CFixedKnockBack>(Actor()); }
		//�V���b�g�̃X�e�[�^�X�쐬�i���j
		virtual const ShotAABB& GetCreateShotStatusAABB();
		//�V���b�g�̃X�e�[�^�X�쐬�i��]���l���������j
		virtual const ShotOBB& GetCreateShotStatusOBB();
		//�V���b�g�̃X�e�[�^�X�쐬�i���́j
		virtual const ShotSphere& GetCreateShotStatusSphere();
		//�G�t�F�N�g�̃X�e�[�^�X�쐬
		virtual const EffectCreateParameter& GetCreateEffectStatus();
		//���̒e���쐬����
		virtual void CreateShotAABB();
		//��]���l���������̒e���쐬����
		virtual void CreateShotOBB();
		//���̂̒e���쐬����
		virtual void CreateShotSphere();
		//�G�t�F�N�g���쐬����
		virtual void CreateEffect();
		//�A�[�}�[���x����ݒ肷��
		virtual void SetArmorLevel(BYTE level);
		
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CAttackBaseState();

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		virtual void Start() override;

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		virtual void Execution() override;

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		virtual void InputExecution() override;

		/**
		 * @brief		�X�e�[�g���̏I������
		 */
		virtual void End() override;
		
	};

}