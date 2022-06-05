#pragma once

#include	"Common.h"
#include	"Observer.h"

namespace Sample {

	/**
	 * @brief		HP
	 */
	template < typename T >
	class IHPGauge : public IObserver<T>
	{
	public:
		virtual void Set(const T& v) = 0;
		virtual const T Get() const = 0;
		virtual const float GetPercent() const = 0;
	};
	//�|�C���^�u������
	using HPGaugePtr = std::shared_ptr<IHPGauge<int>>;

}