#pragma once

#include	"SkillData.h"
#include	"TimeScaleController.h"



namespace ActionGame
{
	
	class CSkill
	{
	public:
	protected:
		std::string		skillName_;
		std::string		texureName_;
		std::string		inputKey_;
		char*			stateName_;
		char*			flyStateName_;
		bool			isStart_;
		SkillDataPtr	skillData_;
		
		ActionGame::ParameterHandle< ActionGame::CReactiveParameter<bool> >	canUse_;
		ActionGame::ParameterHandle< ActionGame::CReactiveParameter<float> > CT_;


	protected:
		/*		�v���C�x�[�g�֐�		*/
		
		//���Ԃ�i�߂�
		void AddTimer();

		//���Z�b�g����
		void ResetFlg();

		//���Ԃ�i�߂違���Z�b�g����
		void AddTimerAndResetFlg();

	public:
		CSkill();

		virtual ~CSkill() = default;
		
		/*
		* @brief	�X�L������
		* @param	name �X�L����
		* @param	inputKey �C���v�b�g�L�[��
		* @param	texName	�X�L���e�N�X�`���̖��O
		* @param	state	�X�e�[�g��
		* @param	state	�󒆃X�e�[�g��
		*/
		virtual void Create(const std::string& name, const std::string& inputKey, const std::string& texName, char* state, char* flyState);

		/*
		* @brief	�J�n
		*/
		virtual void Start();

		/*
		* @brief	���Z�b�g
		*/
		virtual void Reset();

		/*
		* @brief	�X�V
		*/
		virtual void Update();



		/////////////////////////////////////////////////////////////////////
		///			�Q�b�^�[
		////////////////////////////////////////////////////////////////////
		
		/**
		* @brief		�X�L�������擾
		*/
		const std::string& GetKey() const noexcept
		{
			return skillName_;
		}

		/*
		* @brief		�e�N�X�`�������擾
		*/
		const std::string& GetTexName() const noexcept
		{
			return texureName_;
		}

		/*
		* @brief		�C���v�b�g�L�[�����擾
		*/
		const std::string& GetButton() const noexcept
		{
			return inputKey_;
		}

		/*
		* @brief		�X�e�[�g�����擾
		*/
		char* GetState() const noexcept
		{
			return stateName_;
		}

		/*
		* @brief		�󒆃X�e�[�g�����擾
		*/
		char* GetFlyState() const noexcept
		{
			return flyStateName_;
		}

		/*
		* @brief		�ő�N�[���^�C�����擾
		*/
		float GetMaxCT() const noexcept
		{
			return skillData_->MaxCT.Get();
		}

		/*
		* @brief		���݂̃N�[���^�C�����擾
		*/
		float GetCT() const noexcept
		{
			return CT_.Get();
		}

		/*
		* @brief		�X�L���̃_���[�W�ʂ��擾
		* @return		�X�L���̃_���[�W��(%)
		*/
		int GetDamage() const noexcept
		{
			return skillData_->DamagePercent;
		}

		/*
		* @brief	�X�L�����g�p�ł��邩�H
		* @param	true�@�Ȃ�g�p�\
		*/
		virtual bool CanUseSkill()
		{
			return canUse_.Get();
		}


		/**
		* @brief		CT�ω��ʒm
		*/
		ActionGame::IObservable<float>* GetCTSubject()			{ return &(CT_.Get()); }
		ActionGame::IObservable<float>* GetMaxCTSubject()		{ return &(skillData_->MaxCT.Get()); }
		ActionGame::IObservable<bool>* GetCanUseSubject()		{ return &(canUse_.Get()); }


		/////////////////////////////////////////////////////////////////////
		///			�Z�b�^�[
		////////////////////////////////////////////////////////////////////

		/**
		* @brief		�X�L������ݒ�
		*/
		void SetKey(const std::string& key) noexcept
		{
			skillName_ = key;
			
		}

		/*
		* @brief		�X�e�[�g�����擾
		* @param		state		�X�e�[�g��
		* @param		flyState	�󒆃X�e�[�g��
		*/
		void SetState(char* state, char* flyState) noexcept
		{
			stateName_ = state;
			flyStateName_ = flyState;
		}

		/*
		* @brief		�C���v�b�g�L�[�����擾
		*/
		void SetButton(const std::string& button) noexcept
		{
			inputKey_ = button;
		}

		/*
		* @brief		���݂̃N�[���^�C�����擾
		* @param		�N�[���^�C��(�b)
		*/
		void SetCT(float ct) noexcept
		{
			CT_ = ct;
		}
		/*
		* @brief		���݂̃N�[���^�C��������
		* @param		����������N�[���^�C��(�b)
		*/
		void SubCT(float ct) noexcept
		{
			CT_ = max(CT_.Get() - ct, 0.0f);
		}

		/*
		* @brief		�ő�̃N�[���^�C����ݒ�
		* @param		�ő�N�[���^�C��(�b)
		*/
		void SetMaxCT(float ct) noexcept
		{
			skillData_->MaxCT = ct;
		}

		/*
		* @brief		�X�L���̃_���[�W�ʂ�ݒ�
		* @param		damage �X�L���̃_���[�W��(%)
		*/
		void SetDamage(float damage) noexcept
		{
			skillData_->DamagePercent = damage;
		}

		/*
		* @brief		�g�p�\�ۂ�ݒ�
		* @param		true�@�Ȃ�g�p�\
		*/
		void SetCanUse(bool isCanUse) noexcept
		{
			canUse_ = isCanUse;
		}

		/*
		* @brief		�X�L���f�[�^��ݒ�
		* @param		skill �X�L���f�[�^
		*/
		virtual void SetSkillData(const SkillDataPtr& skill)
		{
			skillData_ = skill;
		}

		/*
		* @brief		�X�L���f�[�^��ݒ�
		* @param		damage �_���[�W��(%)
		* @param		ct	�ő�N�[���^�C��(�b)
		*/
		void SetSkillData(float damage, float ct) noexcept
		{
			skillData_->MaxCT = ct;
			skillData_->DamagePercent = damage;
		}
		

	};

	//�|�C���^�u������
	using SKillPtr = std::shared_ptr<CSkill>;
	using SkillWeakPtr = std::weak_ptr<CSkill>;
}