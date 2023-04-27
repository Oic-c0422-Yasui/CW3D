#pragma once

#include	<vector>
#include	<algorithm>
#include	"Observable.h"

namespace ActionGame {

	template <class... Args>
	class CSubject : public IObservable<Args...> {
	private:
		/** �ʒm���󂯂�I�u�U�[�o�[���X�g */
		std::vector<std::shared_ptr< IObserver<Args...> >> observerList_;
	public:
		/**
		 * �R���X�g���N�^
		 */
		CSubject()
			: observerList_()
		{
		}
		/**
		 * �f�X�g���N�^
		 */
		virtual ~CSubject()
		{
		}

		/**
		 * @brief	�ʒm���󂯂�I�u�U�[�o�[�̓o�^
		 */
		void Subscribe(std::shared_ptr < IObserver<Args...> > pobs) override {
			observerList_.push_back(pobs);
		}

		/**
		 * @brief	�ʒm���󂯂�I�u�U�[�o�[�̓o�^
		 */
		std::shared_ptr < ObserverFunction<Args...> > Subscribe(std::function<void(Args...)> f) override {
			auto func = std::make_shared< ObserverFunction<Args...> >(f);
			observerList_.push_back(func);
			return func;
		}

		/**
		 * @brief	�ʒm���󂯂�I�u�U�[�o�[�̍폜
		 */
		void Dispose(std::shared_ptr < IObserver<Args...> > pobs) override {
			observerList_.erase(std::remove_if(
				observerList_.begin(), observerList_.end(),
				[&](const std::shared_ptr < IObserver<Args...> >& o) {return o == pobs; }),
				observerList_.end());
		}

		/**
		 * @brief	�ʒm���󂯂邷�ׂẴI�u�U�[�o�[�̍폜
		 */
		void Dispose() override {
			observerList_.clear();
		}

		/**
		 * @brief	�ʒm���\�b�h
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
		/** �ʒm���󂯂�I�u�U�[�o�[���X�g */
		std::vector<std::shared_ptr< IObserver<void> >> observerList_;
	public:
		/**
		 * �R���X�g���N�^
		 */
		CSubject()
			: observerList_()
		{
		}
		/**
		 * �f�X�g���N�^
		 */
		virtual ~CSubject()
		{
		}

		/**
		 * @brief	�ʒm���󂯂�I�u�U�[�o�[�̓o�^
		 */
		void Subscribe(std::shared_ptr < IObserver<void> > pobs) override {
			observerList_.push_back(pobs);
		}

		/**
		 * @brief	�ʒm���󂯂�I�u�U�[�o�[�̓o�^
		 */
		std::shared_ptr < ObserverFunction<void> > Subscribe(std::function<void()> f) override {
			auto func = std::make_shared< ObserverFunction<void> >(f);
			observerList_.push_back(func);
			return func;
		}

		/**
		 * @brief	�ʒm���󂯂�I�u�U�[�o�[�̍폜
		 */
		void Dispose(std::shared_ptr < IObserver<void> > pobs) override {
			observerList_.erase(std::remove_if(
				observerList_.begin(), observerList_.end(),
				[&](const std::shared_ptr < IObserver<void> >& o) {return o == pobs; }),
				observerList_.end());
		}

		/**
		 * @brief	�ʒm���󂯂邷�ׂẴI�u�U�[�o�[�̍폜
		 */
		void Dispose() override {
			observerList_.clear();
		}

		/**
		 * @brief	�ʒm���\�b�h
		 */
		void Notify() {
			for (auto& obj : observerList_) {
				obj->Notify();
			}
		}
	};
}