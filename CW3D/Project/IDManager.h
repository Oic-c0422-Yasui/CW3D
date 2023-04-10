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
		uint32_t ID_;
	public:
		CMyID(uint32_t id) : ID_(id) {}
		uint32_t GetID()const noexcept { return ID_; }
	};

	/*
	* @brief	�A�N�^�[�����ʂ���ID�𐶐�����N���X
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
		* @brief�@��ӂ�ID�𐶐�����
		*/
		CMyID CreateID()
		{
			return CMyID(IDSeed_++);
		}

		/*
		* @brief	����ID�����Z�b�g����
		*/
		void Reset()
		{
			IDSeed_ = 0;
		}
	};
}
//�ȈՃA�N�Z�X�p
#define IDManagerInstance 	ActionGame::CIDManager::GetInstance()

