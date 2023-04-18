#pragma once


#include	"State.h"
#include	"FixedKnockBack.h"
#include	"EffectController.h"
#include	"ShotManager.h"
#include	"SkillDefine.h"
#include	"DamageUtilities.h"
#include	"VectorUtilities.h"

namespace ActionGame {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class CAttackBaseState : public CState
	{
	public:
		typedef struct BASEPARAM
		{
			BYTE armorLevel;
		}BaseParam;
		/*
		* @brief	���ړ��␳�p�����[�^
		* @param	isEnable		�␳���L�����H
		* @param	endTime			�I������
		* @param	sightAngle		����p�i�x���@�j
		* @param	minDistance		�ŏ��␳����
		*/
		struct BaseCompensationParam
		{
			bool isEnable;
			float endTime;
			float sightAngle;
			float maxDistance;
		};
		/*
		* @brief	�ړ��␳�p�����[�^
		* @param	isEnable		�␳���L�����H
		* @param	endTime			�I������
		* @param	sightAngle		����p�i�x���@�j
		* @param	maxDistance		�ő�␳����
		* @param	isActorInSight	������ɖڕW�A�N�^�[�����邩�H
		* @param	currentTime		���ݎ���
		* @param	minDistance		�ŏ��␳����
		* @param	targetPos		�ڕW�A�N�^�[�̃g�����X�t�H�[��
		*/
		struct MoveCompensationParam : public BaseCompensationParam
		{

			bool isActorInSight;
			float currentTime;
			float minDistance;
			TransformPtr targetPos;
		};

	protected:
		
		float							currentTime_;
		
		//���X�e�[�g�̃C���v�b�g��������Ă��邩�H
		bool							isNextInput_;


		std::vector<ShotPtr>			shots_;
		std::vector<EffectPtr>			effects_;

		
		MoveCompensationParam moveCompentionParam_;

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
		
		/*
		* @brief	������ɃA�N�^�[�����邩�H
		* @param[out]	outPos			��ԋ߂��̃A�N�^�[���W���i�[����(���A�N�^�[�������ꍇ)
		* @param[out]	outMinDistance	�ŏ����m�������i�[����
		* @param		sightAngle		����p�i�x���@�j
		* @param		maxDistance		�ő匟�m����
		* @return		true�@�Ȃ瑶�݂���
		*/
		bool IsActorInSight(TransformPtr& outPos,float& offsetSize, float sightAngle, float maxDistance);

		/*
		* @brief	�߂��̃A�N�^�[�Ɍ����Ĉړ��␳��������
		* @param[in,out]	param		�ړ��␳�p�����[�^
		* @retval			true		�ړ�����
		* @retval			false		�ړ���
		*/
		bool MoveCompensation(MoveCompensationParam& param);

		void SettingMoveCompensationParam(const BaseCompensationParam& param);
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