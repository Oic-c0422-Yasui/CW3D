#pragma once

#include	<vector>
#include	<algorithm>
#include	"Observable.h"

namespace ActionGame {

	template <class... Args>
	class CSubject : public IObservable<Args...> {
	private:
		/** 通知を受けるオブザーバーリスト */
		std::vector<std::shared_ptr< IObserver<Args...> >> observerList_;
	public:
		/**
		 * コンストラクタ
		 */
		CSubject()
			: observerList_()
		{
		}
		/**
		 * デストラクタ
		 */
		virtual ~CSubject()
		{
		}

		/**
		 * @brief	通知を受けるオブザーバーの登録
		 */
		void Subscribe(std::shared_ptr < IObserver<Args...> > pobs) override {
			observerList_.push_back(pobs);
		}

		/**
		 * @brief	通知を受けるオブザーバーの登録
		 */
		std::shared_ptr < ObserverFunction<Args...> > Subscribe(std::function<void(Args...)> f) override {
			auto func = std::make_shared< ObserverFunction<Args...> >(f);
			observerList_.push_back(func);
			return func;
		}

		/**
		 * @brief	通知を受けるオブザーバーの削除
		 */
		void Dispose(std::shared_ptr < IObserver<Args...> > pobs) override {
			observerList_.erase(std::remove_if(
				observerList_.begin(), observerList_.end(),
				[&](const std::shared_ptr < IObserver<Args...> >& o) {return o == pobs; }),
				observerList_.end());
		}

		/**
		 * @brief	通知を受けるすべてのオブザーバーの削除
		 */
		void Dispose() override {
			observerList_.clear();
		}

		/**
		 * @brief	通知メソッド
		 */
		void Notify(Args... args) {
			for (auto& obj : observerList_) {
				obj->Notify(args...);
			}
		}
	};

	template <>
	class CSubject<void> : public IObservable<void> {
	private:
		/** 通知を受けるオブザーバーリスト */
		std::vector<std::shared_ptr< IObserver<void> >> observerList_;
	public:
		/**
		 * コンストラクタ
		 */
		CSubject()
			: observerList_()
		{
		}
		/**
		 * デストラクタ
		 */
		virtual ~CSubject()
		{
		}

		/**
		 * @brief	通知を受けるオブザーバーの登録
		 */
		void Subscribe(std::shared_ptr < IObserver<void> > pobs) override {
			observerList_.push_back(pobs);
		}

		/**
		 * @brief	通知を受けるオブザーバーの登録
		 */
		std::shared_ptr < ObserverFunction<void> > Subscribe(std::function<void()> f) override {
			auto func = std::make_shared< ObserverFunction<void> >(f);
			observerList_.push_back(func);
			return func;
		}

		/**
		 * @brief	通知を受けるオブザーバーの削除
		 */
		void Dispose(std::shared_ptr < IObserver<void> > pobs) override {
			observerList_.erase(std::remove_if(
				observerList_.begin(), observerList_.end(),
				[&](const std::shared_ptr < IObserver<void> >& o) {return o == pobs; }),
				observerList_.end());
		}

		/**
		 * @brief	通知を受けるすべてのオブザーバーの削除
		 */
		void Dispose() override {
			observerList_.clear();
		}

		/**
		 * @brief	通知メソッド
		 */
		void Notify() {
			for (auto& obj : observerList_) {
				obj->Notify();
			}
		}
	};
}