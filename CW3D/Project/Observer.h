#pragma once

#include	<functional>
#include	<memory>

namespace ActionGame {

	template <class... Args>
	class IObserver {
	private:
	public:
		/**
		 * @brief	�ʒm���\�b�h
		 */
		virtual void Notify(Args...) = 0;
	};
	template <>
	class IObserver<void> {
	private:
	public:
		/**
		 * @brief	�ʒm���\�b�h
		 */
		virtual void Notify() = 0;
	};

	/**
	 * �֐��P�̂ł̓o�^�p
	 */
	template <class... Args>
	class ObserverFunction : public IObserver<Args...> {
	private:
		/** �ʒm���Ɏ��s����֐� */
		std::function<void(Args...)>	func_;
	public:
		/**
		 * �R���X�g���N�^
		 */
		ObserverFunction(std::function<void(Args...)>& f)
			: func_(f) {
		}

		/**
		 * @brief	�ʒm���\�b�h
		 */
		void Notify(Args... args) override {
			func_(args...);
		}
	};


}