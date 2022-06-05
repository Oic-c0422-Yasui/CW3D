#pragma once

#include	"Common.h"
#include	"Observer.h"

namespace Sample {

	/**
	 * @brief		CT
	 */
	template < typename T >
	class ICTGauge : public IObserver<T>
	{
	public:
		virtual void Set(const T& v) = 0;
		virtual const T Get() const = 0;
		virtual const float GetPercent() const = 0;
	};
	//�|�C���^�u������
	using CTGaugePtr = std::shared_ptr<ICTGauge<float>>;

}