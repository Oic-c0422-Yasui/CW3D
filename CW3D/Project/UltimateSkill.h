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

		bool isMaxGauge_;

		//���L�҂̃A�N�^�[�Q��
		ActorWeakPtr actorRef_;

		UltimateSkillDataPtr ultSkillData_;
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
			return ultSkillData_->ExpendGauge.Get();
		}

		/*
		* @brief	�X�L���f�[�^�ݒ�
		* @param	skill	�X�L���f�[�^
		*/
		void SetSkillData(const SkillDataPtr& skill) override
		{
			CSkill::SetSkillData(skill);
			ultSkillData_ = std::dynamic_pointer_cast<UltimateSkillData>(skillData_);
			if (ultSkillData_ == nullptr)
			{
				assert(ultSkillData_);
			}
		}

		/*
		* @brief	�g�p����K�E�Z�Q�[�W�ʒm
		*/
		ActionGame::IObservable<float>* GetSkillUltSubject(int id) { return &(ultSkillData_->ExpendGauge.Get()); }
	};

	//�|�C���^�u������
	using UltimateSkillPtr = std::shared_ptr<UltimateSkill>;
	using UltimateWeakSkillPtr = std::weak_ptr<UltimateSkill>;
}