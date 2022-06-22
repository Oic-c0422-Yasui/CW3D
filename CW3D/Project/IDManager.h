#pragma once

#include "Singleton.h"
#include "Common.h"


namespace Sample
{

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

	};
}
//�ȈՃA�N�Z�X�p
#define IDManagerInstance 	Sample::CIDManager::GetInstance()
