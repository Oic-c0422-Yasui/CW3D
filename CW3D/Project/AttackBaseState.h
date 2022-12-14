#pragma once


#include	"State.h"
#include	"FixedKnockBack.h"
#include	"EffectController.h"
#include	"ShotManager.h"
#include	"SkillDefine.h"

namespace ActionGame {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class AttackBaseState : public State
	{
	public:
		typedef struct BASEPARAM
		{
			BYTE armorLevel;
		}BaseParam;
	protected:
		
		float							m_CurrentTime;
		bool							m_NextInputFlg;

		std::vector<ShotPtr>			m_pShots;
		std::vector<EffectPtr>			m_pEffects;

	protected:
		/* �v���C�x�[�g�֐� */

		//�V���b�g���
		void ReleaseShot();
		//�G�t�F�N�g���
		void ReleaseEffect();
		//�m�b�N�o�b�N�擾
		virtual const KnockBackPtr GetKnockBack() { return std::make_shared<FixedKnockBack>(Actor()); }
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
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		AttackBaseState();

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