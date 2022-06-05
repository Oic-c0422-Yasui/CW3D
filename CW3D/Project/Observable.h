#pragma once

#include	"Observer.h"

namespace Sample {

	template <class... Args>
	class IObservable {
	private:
	public:
		/**
		 * @brief	�ʒm���󂯂�I�u�U�[�o�[�̓o�^
		 */
		virtual void Subscribe(std::shared_ptr < IObserver<Args...> > pobs) = 0;
		/**
		 * @brief	�ʒm���󂯂�I�u�U�[�o�[�̓o�^
		 */
		virtual std::shared_ptr < ObserverFunction<Args...> > Subscribe(std::function<void(Args...)> f) = 0;

		/**
		 * @brief	�ʒm���󂯂�I�u�U�[�o�[�̍폜
		 */
		virtual void Dispose(std::shared_ptr < IObserver<Args...> > pobs) = 0;
	};
}