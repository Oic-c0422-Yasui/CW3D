#pragma once
#include "Common.h"

namespace ActionGame
{
	/*
	* @brief	敵ステータス
	* @param HP		体力
	* @param UltGauge　必殺技ゲージ
	* @param UltGaugeBoostMag　必殺技ゲージブースト倍率
	* @param Atk　必殺技ゲージブースト倍率
	* @param MeshName　必殺技ゲージブースト倍率
	* @param Name　名前
	* @param Weight　重さ
	* @param ArmorLevel　アーマーレベル
	* @param Scale　大きさ
	* @param ColliderSize　当たり判定のサイズ
	* @param ColliderHeight　当たり判定の中心点の高さ
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



	//敵ステータスの辞書
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

