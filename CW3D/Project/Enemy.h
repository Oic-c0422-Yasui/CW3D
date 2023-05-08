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
#include	"ISkillCreator.h"

#include	"ActorObject.h"
#include	"EffectController.h"

namespace ActionGame
{
	/*
	* @brief	�G�N���X
	*/
	class CEnemy : public CActorObject
	{
	protected:
		Input::InputPtr input_;

		ParameterHandle< CReactiveParameter<int> > HP_;
		ParameterHandle< CReactiveParameter<int> > maxHP_;
		ParameterHandle< CReactiveParameter<Vector3> > position_;

		CharacterAIPtr	AI_;

		Vector3			defaultPos_;
		std::string		name_;
		bool			isBoss_;
	protected:
		//�v���C�x�[�g�֐�

		/*
		* @brief	�G�̃p�����[�^�ݒ�
		*/
		virtual void SettingParameter(const AnyParameterMapPtr& param,
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
		* @param	aiCreator	�@AI�̐���
		* @param	skillCreator�@�X�L���̐���
		*/
		virtual bool Load(const EnemyBuildParameterPtr& eneParam,
				const ActionCreatorPtr& actionCreator,
				const StateCreatorPtr& stateCreator,
				const ParameterCreatorPtr& paramCreator,
				const CharacterAICreatorPtr& aiCreator,
				const SkillCreatorPtr& skillCreator);
		/*
		* @brief	������
		*/
		virtual void Initialize() override;
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
		* @param armorBrakeLevel �A�[�}�[�j�󃌃x��
		*/
		void Damage(const Vector3& direction,
					const Vector3& power,
					int damage,
					BYTE armorBrakeLevel);
		/*
		* @brief		�_���[�W����(�G�t�F�N�g�𔭐�������)
		* @param direction	�m�b�N�o�b�N�̕���
		* @param power	�m�b�N�o�b�N�̗�
		* @param damage �_���[�W��
		* @param armorBrakeLevel �A�[�}�[�j�󃌃x��
		* @param effect	�_���[�W�G�t�F�N�g
		*/
		void Damage(const Vector3& direction,
					const Vector3& power,
					int damage,
					BYTE armorBrakeLevel,
					const EffectCreateParameterPtr& effect);
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
			return &(HP_.Get());
		}

		/**
		 * @brief		�ő�HP�ω��ʒm
		 */
		ActionGame::IObservable<int>* GetMaxHPSubject() 
		{ 
			return &(maxHP_.Get()); 
		}

		/**
		 * @brief		���W�ω��ʒm
		 */
		ActionGame::IObservable<Vector3>* GetPositionSubject() 
		{ 
			return &(position_.Get()); 
		}
		/**
		 * @brief		HP�o�[�\����ԕω��ʒm
		 */
		ActionGame::IObservable<bool>& GetShowSubject() 
		{ 
			return  actor_->GetParameterMap()->Get<ActionGame::CReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP); 
		}

		/*
		* @brief	HP�擾
		* @return	HP
		*/
		int GetHP()
		{
			return HP_.Get();
		}

		/*
		* @brief �\���p�̖��O�擾
		* @return �\���p�̖��O
		*/
		const std::string& GetName() const noexcept
		{
			return name_;
		}
		/*
		* @brief	�{�X�����f
		* @return	true�@�Ȃ�{�X
		*/
		bool IsBoss() const noexcept
		{
			return isBoss_;
		}

		/*
		* @brief	���W�ݒ�
		* @param	pos ���W
		*/
		void SetPosition(const Vector3& pos) noexcept override
		{
			actor_->SetPosition(pos);
			position_ = actor_->GetPosition();
		}
		/*
		* @brief	�\���ݒ�
		* @param	isShow �\����
		*/
		void SetShow(bool isShow) noexcept override
		{
			if (!isShow)
			{
				auto& showFlg = actor_->GetParameterMap()->Get<ActionGame::CReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP);
				showFlg = isShow;
			}
			isShow_ = isShow;
		}
		
	};

	//�|�C���^�u������
	using EnemyPtr = std::shared_ptr<CEnemy>;
	using EnemyArray = std::vector<EnemyPtr>;
	using EnemyArrayPtr = std::shared_ptr<EnemyArray>;
}


