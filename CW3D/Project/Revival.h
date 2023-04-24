#pragma once
#include "RevivalCount.h"

namespace ActionGame
{

	/*
	* @brief	�����p�N���X
	*/
	class CRevival
	{
	private:
		RevivalCountPtr count_;
	public:
		CRevival();
		~CRevival();
		/*
		* @brief	�ǂݍ���
		* @param	revivalCount �����\��
		*/
		bool Load(uint32_t revivalCount);
		/*
		* @brief	������
		*/
		void Initialize();

		void SubCount() noexcept;
		uint32_t GetCount() const noexcept;

	};

	using RevivalPtr = std::shared_ptr<CRevival>;
}


