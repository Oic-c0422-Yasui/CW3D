#pragma once

#include	"SkillData.h"
#include	"TimeScaleController.h"



namespace ActionGame
{
	
	class Skill
	{
	public:
	protected:
		std::string		m_Key;
		std::string		m_TexName;
		std::string		m_InputKey;
		char*			m_State;
		char*			m_FlyState;
		bool			m_StartFlg;
		SkillDataPtr	m_SkillData;
		
		ActionGame::ParameterHandle< ActionGame::ReactiveParameter<bool> >	m_CanUseFlg;
		ActionGame::ParameterHandle< ActionGame::ReactiveParameter<float> > m_CT;


	protected:
		/*		�v���C�x�[�g�֐�		*/
		
		//���Ԃ�i�߂�
		void AddTimer();

		//���Z�b�g����
		void ResetFlg();

		//���Ԃ�i�߂違���Z�b�g����
		void AddTimerAndResetFlg();

	public:
		Skill();

		virtual ~Skill() = default;
		
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
			return m_Key;
		}

		/*
		* @brief		�e�N�X�`�������擾
		*/
		const std::string& GetTexName() const noexcept
		{
			return m_TexName;
		}

		/*
		* @brief		�C���v�b�g�L�[�����擾
		*/
		const std::string& GetButton() const noexcept
		{
			return m_InputKey;
		}

		/*
		* @brief		�X�e�[�g�����擾
		*/
		char* GetState() const noexcept
		{
			return m_State;
		}

		/*
		* @brief		�󒆃X�e�[�g�����擾
		*/
		char* GetFlyState() const noexcept
		{
			return m_FlyState;
		}

		/*
		* @brief		�ő�N�[���^�C�����擾
		*/
		float GetMaxCT() const noexcept
		{
			return m_SkillData->MaxCT.Get();
		}

		/*
		* @brief		���݂̃N�[���^�C�����擾
		*/
		float GetCT() const noexcept
		{
			return m_CT.Get();
		}

		/*
		* @brief		�X�L���̃_���[�W�ʂ��擾
		* @return		�X�L���̃_���[�W��(%)
		*/
		int GetDamage() const noexcept
		{
			return m_SkillData->DamagePercent;
		}

		/*
		* @brief	�X�L�����g�p�ł��邩�H
		* @param	true�@�Ȃ�g�p�\
		*/
		virtual bool IsCanUse()
		{
			return m_CanUseFlg.Get();
		}


		/**
		* @brief		CT�ω��ʒm
		*/
		ActionGame::IObservable<float>* GetCTSubject()			{ return &(m_CT.Get()); }
		ActionGame::IObservable<float>* GetMaxCTSubject()		{ return &(m_SkillData->MaxCT.Get()); }
		ActionGame::IObservable<bool>* GetCanUseSubject()		{ return &(m_CanUseFlg.Get()); }


		/////////////////////////////////////////////////////////////////////
		///			�Z�b�^�[
		////////////////////////////////////////////////////////////////////

		/**
		* @brief		�X�L������ݒ�
		*/
		void SetKey(const std::string& key) noexcept
		{
			m_Key = key;
			
		}

		/*
		* @brief		�X�e�[�g�����擾
		* @param		state		�X�e�[�g��
		* @param		flyState	�󒆃X�e�[�g��
		*/
		void SetState(char* state, char* flyState) noexcept
		{
			m_State = state;
			m_FlyState = flyState;
		}

		/*
		* @brief		�C���v�b�g�L�[�����擾
		*/
		void SetButton(const std::string& button) noexcept
		{
			m_InputKey = button;
		}

		/*
		* @brief		���݂̃N�[���^�C�����擾
		* @param		�N�[���^�C��(�b)
		*/
		void SetCT(float ct) noexcept
		{
			m_CT = ct;
		}
		/*
		* @brief		���݂̃N�[���^�C��������
		* @param		����������N�[���^�C��(�b)
		*/
		void SubCT(float ct) noexcept
		{
			m_CT = max(m_CT.Get() - ct, 0.0f);
		}

		/*
		* @brief		�ő�̃N�[���^�C����ݒ�
		* @param		�ő�N�[���^�C��(�b)
		*/
		void SetMaxCT(float ct) noexcept
		{
			m_SkillData->MaxCT = ct;
		}

		/*
		* @brief		�X�L���̃_���[�W�ʂ�ݒ�
		* @param		damage �X�L���̃_���[�W��(%)
		*/
		void SetDamage(float damage) noexcept
		{
			m_SkillData->DamagePercent = damage;
		}

		/*
		* @brief		�g�p�\�ۂ�ݒ�
		* @param		true�@�Ȃ�g�p�\
		*/
		void SetCanUseFlg(bool isCanUse) noexcept
		{
			m_CanUseFlg = isCanUse;
		}

		/*
		* @brief		�X�L���f�[�^��ݒ�
		* @param		skill �X�L���f�[�^
		*/
		virtual void SetSkillData(const SkillDataPtr& skill)
		{
			m_SkillData = skill;
		}

		/*
		* @brief		�X�L���f�[�^��ݒ�
		* @param		damage �_���[�W��(%)
		* @param		ct	�ő�N�[���^�C��(�b)
		*/
		void SetSkillData(float damage, float ct) noexcept
		{
			m_SkillData->MaxCT = ct;
			m_SkillData->DamagePercent = damage;
		}
		

	};

	//�|�C���^�u������
	using SKillPtr = std::shared_ptr<Skill>;
	using SkillWeakPtr = std::weak_ptr<Skill>;
}