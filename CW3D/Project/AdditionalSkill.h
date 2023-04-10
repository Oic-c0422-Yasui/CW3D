#pragma once
#include	"Skill.h"


namespace ActionGame
{
	/*
	* @brief	�ǉ����͂��\�ȃX�L��
	*/
	class CAdditionalSkill : public CSkill
	{
	private:
		float addStartTime_;
		ActionGame::ParameterHandle< ActionGame::CReactiveParameter<float> >	addCT_;
		int		addCount_;
		bool	isAdd_;
		bool	isDelayAdd_;
		AdditionalSkillDataPtr addSkillData_;
	public:
		CAdditionalSkill();
		~CAdditionalSkill();

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
			addCT_ = time;
		}

		/*
		* @brief	�ő�ǉ��N�[���^�C����ݒ�
		* @param	time �ő�ǉ��N�[���^�C��(�b)
		*/
		void SetAddMaxCT(float time) noexcept
		{
			addSkillData_->AddMaxCT = time;
		}

		/*
		* @brief	�g�p�񐔂�ݒ�
		*/
		void SetAddCount(float count) noexcept
		{
			addCount_ = count;
		}

		/*
		* @brief	�ǉ�����
		*/
		void AddInput()
		{
			SetAddCT(0.0f);
			isAdd_ = false;
		}

		/*
		* @brief	�ǉ�����
		*/
		bool IsAdditional() const noexcept
		{
			return isAdd_;
		}
		virtual bool IsDelayAdditional()
		{
			return isDelayAdd_;
		}

		float GetAddCT() const noexcept
		{
			return addCT_.Get();
		}
		float GetAddMaxCT() const noexcept
		{
			return addSkillData_->AddMaxCT.Get();
		}


		int GetAddCount() const noexcept
		{
			return addCount_;
		}

		/*
		* @brief	�g�p�\���H
		* @return	true�@�Ȃ�g�p�\
		*/
		bool CanUseSkill() override
		{
			return isAdd_ | canUse_.Get();
		}

		/*
		* @brief	�X�L���f�[�^�ݒ�
		*/
		void SetSkillData(const SkillDataPtr& skill) override;
		

		ActionGame::IObservable<float>* GetAddCTSubject() { return &(addCT_.Get()); }
		ActionGame::IObservable<float>* GetAddMaxCTSubject() { return &(addSkillData_->MaxCT.Get()); }

	};

	//�|�C���^�u������
	using AdditionalSKillPtr = std::shared_ptr<CAdditionalSkill>;
	using AdditionalWeakSKillPtr = std::weak_ptr<CAdditionalSkill>;
}