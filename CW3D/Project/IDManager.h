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
		uint32_t ID_;
	public:
		CMyID(uint32_t id) : ID_(id) {}
		uint32_t GetID()const noexcept { return ID_; }
	};

	/*
	* @brief	アクターを識別するIDを生成するクラス
	*/
	class CIDManager : public Singleton<CIDManager>
	{
		friend class Singleton<CIDManager>;
	private:

		uint32_t IDSeed_;

		CIDManager()
			: Singleton<CIDManager>()
		{
			IDSeed_ = 0;
		}

	public:
		/*
		* @brief　一意のIDを生成する
		*/
		CMyID CreateID()
		{
			return CMyID(IDSeed_++);
		}

		/*
		* @brief	生成IDをリセットする
		*/
		void Reset()
		{
			IDSeed_ = 0;
		}
	};
}
//簡易アクセス用
#define IDManagerInstance 	ActionGame::CIDManager::GetInstance()

