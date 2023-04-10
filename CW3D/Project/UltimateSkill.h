#pragma once
#include	"Skill.h"
#include	"IActor.h"


namespace ActionGame
{
	/*
	* @brief	�K�E�Z�X�L��
	*/
	class UltimateSkill : public CSkill
	{
	private:

		bool m_MaxGaugeFlg;

		//���L�҂̃A�N�^�[�Q��
		ActorWeakPtr m_ActorRef;

		UltimateSkillDataPtr m_UltSkillData;
	public:
		/*
		* @brief	�R���X�g���N�^
		* @param	actor	���L�҂̃A�N�^�[
		*/
		UltimateSkill(const ActorWeakPtr& actor);
		
		~UltimateSkill();

		/*
		* @brief	�X�L������
		* @param	key �X�L����
		* @param	inputKey �C���v�b�g�L�[��
		* @param	texName	�X�L���e�N�X�`���̖��O
		* @param	state	�X�e�[�g��
		* @param	state	�󒆃X�e�[�g��
		*/
		void Create(const std::string& key, const std::string& inputKey, const std::string& texName, char* state, char* flyState) override;

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
		* @brief	�g�p����K�E�Z�Q�[�W�擾
		*/
		float GetExpendGauge() const noexcept
		{
			return m_UltSkillData->ExpendGauge.Get();
		}

		///*
		//* @brief	�g�p����K�E�Z�Q�[�W�擾�i�ʒm�p�j
		//*/
		//ActionGame::ParameterHandle< ActionGame::CReactiveParameter<float> >& GettExpendGaugeParam()
		//{
		//	return m_UltSkillData->ExpendGauge;
		//}

		/*
		* @brief	�X�L���f�[�^�ݒ�
		* @param	skill	�X�L���f�[�^
		*/
		void SetSkillData(const SkillDataPtr& skill) override
		{
			CSkill::SetSkillData(skill);
			m_UltSkillData = std::dynamic_pointer_cast<UltimateSkillData>(skillData_);
			if (m_UltSkillData == nullptr)
			{
				assert(m_UltSkillData);
			}
		}

		/*
		* @brief	�g�p����K�E�Z�Q�[�W�ʒm
		*/
		ActionGame::IObservable<float>* GetSkillUltSubject(int id) { return &(m_UltSkillData->ExpendGauge.Get()); }
	};

	//�|�C���^�u������
	using UltimateSkillPtr = std::shared_ptr<UltimateSkill>;
	using UltimateWeakSkillPtr = std::weak_ptr<UltimateSkill>;
}