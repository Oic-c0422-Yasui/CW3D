#pragma once

#include	"Common.h"
#include	"Observer.h"

namespace Sample {

	/**
	 * @brief		HP
	 */
	template < typename T >
	class IHPPosition : public IObserver<T>
	{
	public:
		virtual void Set(const T& v) = 0;
		virtual const T Get() const = 0;
	};
	//�|�C���^�u������
	using HPPositionPtr = std::shared_ptr<IHPPosition<Vector3>>;

}