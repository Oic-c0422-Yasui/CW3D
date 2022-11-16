#pragma once
#include "Common.h"

namespace Sample
{
	//敵ステータス
	class EnemyStatus
	{
	public:
		int m_Hp;
		float m_UltGauge;
		float m_UltGaugeBoostMag;
		int m_Atk;
		std::string m_MeshName;
		Vector3 m_ColliderSize;
		float m_ColliderHeight;

		EnemyStatus(int hp, float ultGauge, float ultGaugeBoostMag, int atk,
			const std::string& meshName, const Vector3& colliderSize, float colliderHeight);

	};
	using EnemyStatusPtr = std::shared_ptr<EnemyStatus>;

	//敵ステータスの辞書
	class EnemyStatusDictionary
	{
	private:
		std::map<std::string, EnemyStatusPtr> map;
	public:
		EnemyStatusDictionary();

		void Add(const std::string& name, const EnemyStatusPtr& status);

		const std::map<std::string, EnemyStatusPtr> GetMap()
		{
			return map;
		}

		const EnemyStatusPtr& Get(const std::string& name);
		bool Delete(const std::string& name);

		bool IsContain(const std::string& name);
	};
}

