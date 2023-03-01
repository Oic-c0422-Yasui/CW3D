#pragma once

#include "Singleton.h"
#include "Common.h"


namespace ActionGame
{
	/*
	* @brief	�A�N�^�[�����ʂ���ID
	*/
	class CMyID
	{
	private:
		size_t ID_;
	public:
		CMyID(size_t id) : ID_(id) {}
		size_t GetID()const noexcept { return ID_; }
	};

	/*
	* @brief	�A�N�^�[�����ʂ���ID�𐶐�����N���X
	*/
	class CIDManager : public Singleton<CIDManager>
	{
		friend class Singleton<CIDManager>;
	private:

		size_t IDSeed_;

		CIDManager()
			: Singleton<CIDManager>()
		{
			IDSeed_ = 0;
		}

	public:

		CMyID GetId()
		{
			return CMyID(IDSeed_++);
		}

		void Reset()
		{
			IDSeed_ = 0;
		}
	};
}
//�ȈՃA�N�Z�X�p
#define IDManagerInstance 	ActionGame::CIDManager::GetInstance()

