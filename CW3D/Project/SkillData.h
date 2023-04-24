#pragma once
#include	"ReactiveParameter.h"
#include	"ParameterHandle.h"

namespace ActionGame
{
	/*
	* �X�L���f�[�^���܂Ƃ߂��N���X
	*/

	/*
	* @brief	�X�L���f�[�^
	*/
	struct SkillData
	{
		//�_���[�W�ʁi���j
		uint32_t	DamagePercent;
		//�ő�̃N�[���^�C��
		ParameterHandle< CReactiveParameter<float>>	MaxCT;
		SkillData()
			: DamagePercent(0)
			, MaxCT(0.0f)

		{
		}

		SkillData(uint32_t dmg, float maxCT)
			: DamagePercent(dmg)
			, MaxCT(maxCT)

		{
		}

		virtual ~SkillData(){}
	};
	using SkillDataPtr = std::shared_ptr<SkillData>;

	/*
	* @brief	�ǉ��X�L���f�[�^
	*/
	struct AdditionalSkillData : public SkillData
	{
		//�ǉ��X�L���̍ő�̃N�[���^�C��
		ParameterHandle< CReactiveParameter<float>>	AddMaxCT;
		//�J�n����
		float StartTime;
		//�ǉ�����g�p�\��
		BYTE Count;
		AdditionalSkillData()
			: SkillData()
			, AddMaxCT(0)
			, StartTime(0)
			, Count(0)
		{
		}
		/*
		* @brief	�R���X�g���N�^
		* @param	dmg �_���[�W
		* @param	maxCT �ő�N�[���^�C��
		* @param	addMaxCT �ǉ����̓N�[���^�C��
		* @param	st	�J�n����
		* @param	cnt	�ǉ���
		*/
		AdditionalSkillData(uint32_t dmg, float maxCT,float addmaxCT,float st,int cnt)
			: SkillData(dmg, maxCT)
			, AddMaxCT(addmaxCT)
			, StartTime(st)
			, Count(cnt)
		{
		}
	};
	using AdditionalSkillDataPtr = std::shared_ptr<AdditionalSkillData>;

	/*
	* @brief	�K�E�Z�X�L���f�[�^
	*/
	struct UltimateSkillData : public SkillData
	{
		//�g�p����Q�[�W��
		ParameterHandle< CReactiveParameter<float>>	ExpendGauge;

		UltimateSkillData()
			: SkillData()
			, ExpendGauge(0)
		{
		}
		UltimateSkillData(uint32_t dmg, float maxCT,float gauge)
			: SkillData(dmg, maxCT)
			, ExpendGauge(gauge)
		{
		}
	};
	using UltimateSkillDataPtr = std::shared_ptr<UltimateSkillData>;

}

