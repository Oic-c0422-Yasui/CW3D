#pragma once

#include	"Common.h"
#include	"Observer.h"

namespace Sample {

	/**
	 * @brief		HP
	 */
	template < typename T >
	class IHPShowFlg : public IObserver<T>
	{
	public:
		virtual void Set(const T& v) = 0;
		virtual const T Get() const = 0;
	};
	//ポインタ置き換え
	using HPShowFlgPtr = std::shared_ptr<IHPShowFlg<bool>>;

}