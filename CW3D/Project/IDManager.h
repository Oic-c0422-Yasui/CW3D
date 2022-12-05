#pragma once

#include "Singleton.h"
#include "Common.h"


namespace ActionGame
{
	//アクターオブジェクトを識別するID
	class CMyID
	{
	private:
		unsigned int Id;
	public:
		CMyID(unsigned int id) : Id(id) {}
		unsigned int GetID()const noexcept { return Id; }
	};

	class CIDManager : public Singleton<CIDManager>
	{
		friend class Singleton<CIDManager>;
	private:

		unsigned int m_IDSeed;

		CIDManager()
			: Singleton<CIDManager>()
		{
			m_IDSeed = 0;
		}

	public:

		CMyID GetId()
		{
			return CMyID(m_IDSeed++);
		}

		void Reset()
		{
			m_IDSeed = 0;
		}
	};
}
//簡易アクセス用
#define IDManagerInstance 	ActionGame::CIDManager::GetInstance()

