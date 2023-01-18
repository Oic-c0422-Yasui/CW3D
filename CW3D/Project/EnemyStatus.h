#pragma once
#include "Common.h"

namespace ActionGame
{
	/*
	* @brief	�G�X�e�[�^�X
	* @param HP		�̗�
	* @param UltGauge�@�K�E�Z�Q�[�W
	* @param UltGaugeBoostMag�@�K�E�Z�Q�[�W�u�[�X�g�{��
	* @param Atk�@�K�E�Z�Q�[�W�u�[�X�g�{��
	* @param MeshName�@�K�E�Z�Q�[�W�u�[�X�g�{��
	* @param Name�@���O
	* @param Weight�@�d��
	* @param ArmorLevel�@�A�[�}�[���x��
	* @param Scale�@�傫��
	* @param ColliderSize�@�����蔻��̃T�C�Y
	* @param ColliderHeight�@�����蔻��̒��S�_�̍���
	*/
	struct EnemyStatus
	{
		int HP;
		float UltGauge;
		float UltGaugeBoostMag;
		int Atk;
		std::string MeshName;
		std::string Name;
		float Weight;
		BYTE ArmorLevel;
		Vector3	Scale;
		Vector3 ColliderSize;
		float ColliderHeight;
	};
	using EnemyStatusPtr = std::shared_ptr<EnemyStatus>;



	//�G�X�e�[�^�X�̎���
	class EnemyStatusDictionary
	{
	private:
		std::map<std::string, EnemyStatusPtr> m_Map;
	public:
		EnemyStatusDictionary();

		void Add(const std::string& name, const EnemyStatusPtr& status);

		const std::map<std::string, EnemyStatusPtr> GetMap()
		{
			return m_Map;
		}

		const EnemyStatusPtr& Get(const std::string& name);
		bool Delete(const std::string& name);

		bool IsContain(const std::string& name);
	};
}

