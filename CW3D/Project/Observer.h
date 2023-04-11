#pragma once

#include	<functional>
#include	<memory>

namespace ActionGame {

	template <class... Args>
	class IObserver {
	private:
	public:
		/**
		 * @brief	通知メソッド
		 */
		virtual void Notify(Args...) = 0;
	};
	template <>
	class IObserver<void> {
	private:
	public:
		/**
		 * @brief	通知メソッド
		 */
		virtual void Notify() = 0;
	};

	/**
	 * 関数単体での登録用
	 */
	template <class... Args>
	class ObserverFunction : public IObserver<Args...> {
	private:
		/** 通知時に実行する関数 */
		std::function<void(Args...)>	func_;
	public:
		/**
		 * コンストラクタ
		 */
		ObserverFunction(std::function<void(Args...)>& f)
			: func_(f) {
		}

		/**
		 * @brief	通知メソッド
		 */
		void Notify(Args... args) override {
			func_(args...);
		}
	};


}