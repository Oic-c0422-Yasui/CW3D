#pragma once

#include	"Observer.h"

namespace ActionGame {

	template <class... Args>
	class IObservable 
	{
	private:
	public:
		/**
		 * @brief	通知を受けるオブザーバーの登録
		 */
		virtual void Subscribe(std::shared_ptr < IObserver<Args...> > pobs) = 0;
		/**
		 * @brief	通知を受けるオブザーバーの登録
		 */
		virtual std::shared_ptr < ObserverFunction<Args...> > Subscribe(std::function<void(Args...)> f) = 0;

		/**
		 * @brief	通知を受けるオブザーバーの削除
		 */
		virtual void Dispose(std::shared_ptr < IObserver<Args...> > pobs) = 0;
	};

	template< >
	class IObservable<void>
	{
	public:
		using NotifyFunc = std::function<void()>;
		/**
		 * @brief	通知を受けるオブザーバーの登録
		 */
		virtual void Subscribe(std::shared_ptr < IObserver<void> > pobs) = 0;

		/**
		 * @brief	通知を受けるオブザーバーの削除
		 */
		virtual void Dispose(std::shared_ptr < IObserver<void> > pobs) = 0;
	};
}