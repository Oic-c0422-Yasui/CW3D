#pragma once
#include "Action.h"
#include "VectorUtilities.h"


namespace ActionGame
{
	/*
	* @brief	�ړ��␳�A�N�V����
	*/
	class CMoveCompensationAction : public CAction
	{
	public:

		/*
		* @brief	���ړ��␳�p�����[�^
		* @param	isEnable		�␳���L�����H
		* @param	isEnableYaxis	Y���ɂ��␳�������邩�H
		* @param	endTime			�I������
		* @param	sightAngle		����p�i�x���@�j
		* @param	minDistance		�ŏ��␳����
		* @param	parentType			�L�����^�C�v
		*/
		struct BaseParameter
		{
			bool isEnable;
			bool isEnableYaxis;
			float endTime;
			float sightAngle;
			float maxDistance;
			CHARA_TYPE type;
		};
		/*
		* @brief	�ړ��␳�p�����[�^
		* @param	isEnable		�␳���L�����H
		* @param	isEnableYaxis	Y���ɂ��␳�������邩�H
		* @param	endTime			�I������
		* @param	sightAngle		����p�i�x���@�j
		* @param	maxDistance		�ő�␳����
		* @param	parentType			�L�����^�C�v
		* @param	isActorInSight	������ɖڕW�A�N�^�[�����邩�H
		* @param	currentTime		���ݎ���
		* @param	minDistance		�ŏ��␳����
		* @param	targetPos		�ڕW�A�N�^�[�̃g�����X�t�H�[��
		*/
		struct Parameter : public BaseParameter
		{

			bool isActorInSight;
			float currentTime;
			float minDistance;
			TransformPtr targetPos;
		};

	protected:

		Parameter param_;
		Parameter saveParam_;
		float	 currentTime_;

	protected:
		/* �v���C�x�[�g�֐� */

		/*
		* @brief	������ɃA�N�^�[�����邩�H
		* @param[out]	outPos			��ԋ߂��̃A�N�^�[���W���i�[����(���A�N�^�[�������ꍇ)
		* @param[out]	outMinDistance	�ŏ����m�������i�[����
		* @param		parentType			�L�����^�C�v
		* @param		sightAngle		����p�i�x���@�j
		* @param		maxDistance		�ő匟�m����
		* @return		true�@�Ȃ瑶�݂���
		*/
		bool IsActorInSight(TransformPtr& outPos, float& offsetSize, CHARA_TYPE type, float sightAngle, float maxDistance);

		/*
		* @brief	�߂��̃A�N�^�[�Ɍ����Ĉړ��␳��������
		* @param[in,out]	param		�ړ��␳�p�����[�^
		* @retval			true		�ړ�����
		* @retval			false		�ړ���
		*/
		bool MoveCompensation(Parameter& param);

		void Move(Vector3 pos);

		void SettingMoveCompensationParam(const BaseParameter& param);

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CMoveCompensationAction(BaseParameter baseParam);

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		virtual void Start() override;

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		virtual void Execution() override;

		/**
		 * @brief		�A�N�V�������̏I������
		 */
		virtual  void End() override;

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		virtual  const ActionKeyType GetKey() const override;
		
	};

	using MoveCompensationActionPtr = std::shared_ptr<CMoveCompensationAction>;
}


