#pragma once
#include	"Skill.h"


namespace ActionGame
{
	/*
	* @brief	�ǉ����͂��\�ȃX�L��
	*/
	class AdditionalSkill : public Skill
	{
	private:
		float m_AddStartTime;
		ActionGame::ParameterHandle< ActionGame::ReactiveParameter<float> >	m_AddCT;
		int		m_AddCount;
		bool	m_AddFlg;
		bool	m_DelayAddFlg;
		AdditionalSkillDataPtr m_AddSkillData;
	public:
		AdditionalSkill();
		~AdditionalSkill();

		/*
		* @brief	�J�n
		*/
		void Start() override;

		/*
		* @brief	���Z�b�g
		*/
		void Reset() override;

		/*
		* @brief	�X�V
		*/
		void Update() override;

		/*
		* @brief	�ǉ��N�[���^�C����ݒ�
		* @param	time �ǉ��N�[���^�C��(�b)
		*/
		void SetAddCT(float time) noexcept
		{
			m_AddCT = time;
		}

		/*
		* @brief	�ő�ǉ��N�[���^�C����ݒ�
		* @param	time �ő�ǉ��N�[���^�C��(�b)
		*/
		void SetAddMaxCT(float time) noexcept
		{
			m_AddSkillData->AddMaxCT = time;
		}

		/*
		* @brief	�g�p�񐔂�ݒ�
		*/
		void SetAddCount(float count) noexcept
		{
			m_AddCount = count;
		}

		/*
		* @brief	�ǉ�����
		*/
		void AddInput()
		{
			SetAddCT(0.0f);
			m_AddFlg = false;
		}

		/*
		* @brief	�ǉ�����
		*/
		bool IsAdditional() const noexcept
		{
			return m_AddFlg;
		}
		virtual bool IsDelayAdditional()
		{
			return m_DelayAddFlg;
		}

		float GetAddCT() const noexcept
		{
			return m_AddCT.Get();
		}
		float GetAddMaxCT() const noexcept
		{
			return m_AddSkillData->AddMaxCT.Get();
		}


		int GetAddCount() const noexcept
		{
			return m_AddCount;
		}

		/*
		* @brief	�g�p�\���H
		* @return	true�@�Ȃ�g�p�\
		*/
		bool IsCanUse() override
		{
			return m_AddFlg | m_CanUseFlg.Get();
		}

		/*
		* @brief	�X�L���f�[�^�ݒ�
		*/
		void SetSkillData(const SkillDataPtr& skill) override;
		

		ActionGame::IObservable<float>* GetAddCTSubject() { return &(m_AddCT.Get()); }
		ActionGame::IObservable<float>* GetAddMaxCTSubject() { return &(m_AddSkillData->MaxCT.Get()); }

	};

	//�|�C���^�u������
	using AdditionalSKillPtr = std::shared_ptr<AdditionalSkill>;
	using AdditionalWeakSKillPtr = std::weak_ptr<AdditionalSkill>;
}