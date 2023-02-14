#pragma once

#include "Singleton.h"
#include "Common.h"


namespace ActionGame
{
	/*
	* @brief	アクターを識別するID
	*/
	class CMyID
	{
	private:
		size_t Id;
	public:
		CMyID(size_t id) : Id(id) {}
		size_t GetID()const noexcept { return Id; }
	};

	/*
	* @brief	アクターを識別するIDを生成するクラス
	*/
	class CIDManager : public Singleton<CIDManager>
	{
		friend class Singleton<CIDManager>;
	private:

		size_t m_IDSeed;

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

