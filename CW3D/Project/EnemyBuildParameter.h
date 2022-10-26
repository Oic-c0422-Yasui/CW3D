#pragma once
#include "GameDefine.h"


namespace Sample
{
	class EnemyStatus
	{
	public:
		int m_Hp;
		float m_UltGauge;
		int m_Atk;
		std::string m_MeshName;
		Vector3 m_ColliderSize;
		float m_ColliderHeight;

		EnemyStatus(int hp,float ultGauge,int atk,
			const std::string& meshName,const Vector3& colliderSize,float colliderHeight);

	};
	using EnemyStatusPtr = std::shared_ptr<EnemyStatus>;

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

	class EnemyParam
	{
	public:
		std::string m_Type;
		Vector3 m_Pos;

		EnemyParam(const std::string& type,const Vector3& pos);
	};

	class EnemyBuildParameter
	{
	private:
		EnemyParam m_Param;
		EnemyStatusPtr m_Status;
	public:
		EnemyBuildParameter(const EnemyParam& param,const EnemyStatusPtr& status);
		~EnemyBuildParameter();

		const EnemyStatusPtr& GetStatus() const noexcept
		{
			return m_Status;
		}

		const EnemyParam& GetParam() const noexcept
		{
			return m_Param;
		}

	};

}


