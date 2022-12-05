#pragma once
#include	"GameDefine.h"
#include	"InputManager.h"
#include	"ResourceManager.h"
#include	"ParameterHandle.h"
#include	"Observer.h"
#include	"IActionCreator.h"
#include	"IStateCreator.h"
#include	"IParameterCreator.h"
#include	"ICharacterAICreator.h"
#include	"EnemyBuildParameter.h"

#include	"ActorObject.h"

namespace ActionGame
{
	class CEnemy : public ActorObject
	{
	protected:
		InputPtr m_Input;

		ParameterHandle< ReactiveParameter<int> > m_HP;
		ParameterHandle< ReactiveParameter<int> > m_MaxHP;
		ParameterHandle< ReactiveParameter<Vector3> > m_Position;
		ParameterHandle< ReactiveParameter<bool> > m_HPShowFlg;

		CharacterAIPtr	m_AI;

		CVector3 m_DefaultPos;

	private:
		//�v���C�x�[�g�֐�
		/*
		* @brief	�G�̃p�����[�^�ݒ�
		*/
		void SettingParameter(const AnyParameterMapPtr& param,
								const EnemyStatusPtr& eneStatus);
	public:
		CEnemy();
		~CEnemy() override;
		/*
		* @brief	�ǂݍ���
		* @param	eneParam �G�����Ɏg���p�����[�^
		* @param	actionCreator �A�N�V�����̐���
		* @param	stateCreator �X�e�[�g�̐���
		* @param	paramCreator �p�����[�^�̐���
		* @param	aiCreator AI�̐���
		*/
		bool Load(const EnemyBuildParameterPtr& eneParam,
			const ActionCreatorPtr& actionCreator,
			const StateCreatorPtr& stateCreator,
			const ParameterCreatorPtr& paramCreator,
			const CharacterAICreatorPtr& aiCreator);
		/*
		* @brief	������
		*/
		void Initialize();
		/*
		* @brief	�X�V
		*/
		void Update() override;
		/*
		* @brief	�`��
		*/
		void Render() override;
		/*
		* @brief	�f�o�b�O�`��
		*/
		void RenderDebug();
		/*
		* @brief	�QD�`��
		*/
		void Render2D();
		/*
		* @brief	�QD�f�o�b�O�`��
		*/
		void Render2DDebug();
		/*
		* @brief	���
		*/
		void Release() override;
		/*
		* @brief		�_���[�W����
		* @param direction	�m�b�N�o�b�N�̕���
		* @param power	�m�b�N�o�b�N�̗�
		* @param damage �_���[�W��
		* @param level	�A�[�}�[�j�󃌃x��
		*/
		void Damage(const Vector3& direction, const Vector3& power, int damage,BYTE level);
		/*
		* @brief	���G��Ԃ��H
		* @return	true �Ȃ疳�G���
		*/
		bool IsInvincible() const;

		/*const Vector3& GetPosition() const noexcept
		{
			return m_Position.Get();
		}*/

		/**
		 * @brief		HP�ω��ʒm
		 */
		ActionGame::IObservable<int>* GetHPSubject() { return &(m_HP.Get()); }

		/**
		 * @brief		HP�ω��ʒm
		 */
		ActionGame::IObservable<int>* GetMaxHPSubject() { return &(m_MaxHP.Get()); }

		/**
		 * @brief		���W�ω��ʒm
		 */
		ActionGame::IObservable<Vector3>* GetPositionSubject() { return &(m_Position.Get()); }

		/**
		 * @brief		�\���ω��ʒm
		 */
		ActionGame::IObservable<bool>* GetShowSubject() { return &(m_HPShowFlg.Get()); }

		int GetHP()
		{
			return m_HP.Get();
		}

		void SetPosition(const Vector3& pos) noexcept override
		{
			m_Actor->SetPosition(pos);
			m_Position = m_Actor->GetPosition();
		}

		void SetShow(bool isShow) noexcept override
		{
			m_HPShowFlg = isShow;
			m_ShowFlg = isShow;
		}

	};

	//�|�C���^�u������
	using EnemyPtr = std::shared_ptr<CEnemy>;
	using EnemyArray = std::vector<EnemyPtr>;
	using EnemyArrayPtr = std::shared_ptr<EnemyArray>;
}


