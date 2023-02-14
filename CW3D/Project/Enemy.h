#pragma once

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
	/*
	* @brief	�G�N���X
	*/
	class Enemy : public ActorObject
	{
	protected:
		InputPtr m_Input;

		ParameterHandle< ReactiveParameter<int> > m_HP;
		ParameterHandle< ReactiveParameter<int> > m_MaxHP;
		ParameterHandle< ReactiveParameter<Vector3> > m_Position;

		CharacterAIPtr	m_AI;

		CVector3 m_DefaultPos;
		std::string		m_Name;
		bool			m_BossFlg;
	protected:
		//�v���C�x�[�g�֐�

		/*
		* @brief	�G�̃p�����[�^�ݒ�
		*/
		virtual void SettingParameter(const AnyParameterMapPtr& param,
										const EnemyStatusPtr& eneStatus);
	public:
		Enemy();
		~Enemy() override;
		/*
		* @brief	�ǂݍ���
		* @param	eneParam �G�����Ɏg���p�����[�^
		* @param	actionCreator �A�N�V�����̐���
		* @param	stateCreator �X�e�[�g�̐���
		* @param	paramCreator �p�����[�^�̐���
		* @param	aiCreator AI�̐���
		*/
		virtual bool Load(const EnemyBuildParameterPtr& eneParam,
				const ActionCreatorPtr& actionCreator,
				const StateCreatorPtr& stateCreator,
				const ParameterCreatorPtr& paramCreator,
				const CharacterAICreatorPtr& aiCreator);
		/*
		* @brief	������
		*/
		virtual void Initialize();
		/*
		* @brief	�X�V
		*/
		virtual void Update() override;
		/*
		* @brief	�`��
		*/
		virtual void Render() override;
		/*
		* @brief	�f�o�b�O�`��
		*/
		virtual void RenderDebug();
		/*
		* @brief	�QD�`��
		*/
		virtual void Render2D();
		/*
		* @brief	�QD�f�o�b�O�`��
		*/
		virtual void Render2DDebug();
		/*
		* @brief	���
		*/
		virtual void Release() override;
		/*
		* @brief		�_���[�W����
		* @param direction	�m�b�N�o�b�N�̕���
		* @param power	�m�b�N�o�b�N�̗�
		* @param damage �_���[�W��
		* @param armorBrekeLevel	�A�[�}�[�j�󃌃x��
		*/
		virtual void Damage(const Vector3& direction, const Vector3& power, int damage,BYTE armorBrekeLevel);
		/*
		* @brief	���G��Ԃ��H
		* @return	true �Ȃ疳�G���
		*/
		virtual bool IsInvincible() const;

		/**
		 * @brief		HP�ω��ʒm
		 */
		ActionGame::IObservable<int>* GetHPSubject() 
		{ 
			return &(m_HP.Get());
		}

		/**
		 * @brief		�ő�HP�ω��ʒm
		 */
		ActionGame::IObservable<int>* GetMaxHPSubject() 
		{ 
			return &(m_MaxHP.Get()); 
		}

		/**
		 * @brief		���W�ω��ʒm
		 */
		ActionGame::IObservable<Vector3>* GetPositionSubject() 
		{ 
			return &(m_Position.Get()); 
		}
		/**
		 * @brief		HP�o�[�\����ԕω��ʒm
		 */
		ActionGame::IObservable<bool>& GetShowSubject() 
		{ 
			return  m_Actor->GetParameterMap()->Get<ActionGame::ReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP); 
		}

		/*
		* @brief	HP�擾
		* @return	HP
		*/
		int GetHP()
		{
			return m_HP.Get();
		}

		/*
		* @brief �\���p�̖��O�擾
		* @return �\���p�̖��O
		*/
		const std::string& GetName() const noexcept
		{
			return m_Name;
		}
		/*
		* @brief	�{�X�����f
		* @return	true�@�Ȃ�{�X
		*/
		bool IsBoss() const noexcept
		{
			return m_BossFlg;
		}

		/*
		* @brief	���W�ݒ�
		* @param	pos ���W
		*/
		void SetPosition(const Vector3& pos) noexcept override
		{
			m_Actor->SetPosition(pos);
			m_Position = m_Actor->GetPosition();
		}
		/*
		* @brief	�\���ݒ�
		* @param	isShow �\����
		*/
		void SetShow(bool isShow) noexcept override
		{
			if (!isShow)
			{
				auto& showFlg = m_Actor->GetParameterMap()->Get<ActionGame::ReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP);
				showFlg = isShow;
			}
			m_ShowFlg = isShow;
		}
		
	};

	//�|�C���^�u������
	using EnemyPtr = std::shared_ptr<Enemy>;
	using EnemyArray = std::vector<EnemyPtr>;
	using EnemyArrayPtr = std::shared_ptr<EnemyArray>;
}


