#pragma once
#include <memory>

namespace ActionGame
{
	/*
	* @brief	•œŠˆ‰ñ”
	*/
	class CRevivalCount
	{
	private:
		uint32_t currentCount_;
		uint32_t maxCount_;
	public:
		CRevivalCount(uint32_t maxCount);
		~CRevivalCount();

		uint32_t GetCurrentCount() const noexcept;
		uint32_t GetMaxCount() const noexcept;

		void SubCount() noexcept;

		void Reset();
	};
	using RevivalCountPtr = std::shared_ptr<CRevivalCount>;
}


