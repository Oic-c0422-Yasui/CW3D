#pragma once

#include	"Subject.h"

namespace ActionGame {

	template <typename T>
	class ReactiveParameter : public CSubject<T> {
	private:
		/** �p�����[�^�[ */
		T		value_;
	public:
		/**
		 * �R���X�g���N�^
		 */
		ReactiveParameter()
			: CSubject<T>()
			, value_()
		{
		}

		/**
		 * �R���X�g���N�^
		 */
		ReactiveParameter(const T& v)
			: CSubject<T>()
			, value_(v)
		{
		}
		/**
		 * �R���X�g���N�^
		 */
		ReactiveParameter(const ReactiveParameter< T >& v)
			: CSubject<T>()
			, value_(v.value_)
		{
		}
		/**
		 * �f�X�g���N�^
		 */
		virtual ~ReactiveParameter()
		{
		}

		/** �L���X�g */
		operator const T& () const {
			return value_;
		}
		/** ��� */
		ReactiveParameter< T >& operator = (const ReactiveParameter< T >& v) {
			value_ = v.value_;
			this->Notify(value_);
			return *this;
		}
		ReactiveParameter< T >& operator = (const T& v) {
			value_ = v;
			this->Notify(value_);
			return *this;
		}
		void Set(const T& v) {
			value_ = v;
			this->Notify(value_);
		}

		/** �Z�p���Z�q +�@-�@* /�@*/
		T operator + (const ReactiveParameter< T >& v) const {
			return value_ + v.value_;
		}
		T operator + (const T& v) const {
			return value_ + v;
		}
		T operator - (const ReactiveParameter< T >& v) const {
			return value_ - v.value_;
		}
		T operator - (const T& v) const {
			return value_ - v;
		}
		T operator * (const ReactiveParameter< T >& v) const {
			return value_ * v.value_;
		}
		T operator * (const T& v) const {
			return value_ * v;
		}
		T operator / (const ReactiveParameter< T >& v) const {
			return value_ / v.value_;
		}
		T operator / (const T& v) const {
			return value_ / v;
		}

		/** ����������Z�q +=�@-=�@*=�@/= */
		ReactiveParameter< T >& operator += (const ReactiveParameter< T >& v) {
			value_ += v.value_;
			this->Notify(value_);
			return *this;
		}
		ReactiveParameter< T >& operator += (const T& v) {
			value_ += v;
			this->Notify(value_);
			return *this;
		}
		ReactiveParameter< T >& operator -= (const ReactiveParameter< T >& v) {
			value_ -= v.value_;
			this->Notify(value_);
			return *this;
		}
		ReactiveParameter< T >& operator -= (const T& v) {
			value_ -= v;
			this->Notify(value_);
			return *this;
		}
		ReactiveParameter< T >& operator *= (const ReactiveParameter< T >& v) {
			value_ *= v.value_;
			this->Notify(value_);
			return *this;
		}
		ReactiveParameter< T >& operator *= (const T& v) {
			value_ *= v;
			this->Notify(value_);
			return *this;
		}
		ReactiveParameter< T >& operator /= (const ReactiveParameter< T >& v) {
			value_ /= v.value_;
			this->Notify(value_);
			return *this;
		}
		ReactiveParameter< T >& operator /= (const T& v) {
			value_ /= v;
			this->Notify(value_);
			return *this;
		}

		/** ��r���Z�q == != */
		bool operator == (const ReactiveParameter< T >& v) const {
			return value_ == v.value_;
		}
		bool operator == (const T& v) const {
			return value_ == v;
		}
		bool operator != (const ReactiveParameter< T >& v) const {
			return value_ != v.value_;
		}
		bool operator != (const T& v) const {
			return value_ != v;
		}
		bool operator <= (const ReactiveParameter< T >& v) const {
			return value_ <= v.value_;
		}
		bool operator <= (const T& v) const {
			return value_ <= v;
		}
		bool operator < (const ReactiveParameter< T >& v) const {
			return value_ < v.value_;
		}
		bool operator < (const T& v) const {
			return value_ < v;
		}
		bool operator >= (const ReactiveParameter< T >& v) const {
			return value_ >= v.value_;
		}
		bool operator >= (const T& v) const {
			return value_ >= v;
		}
		bool operator > (const ReactiveParameter< T >& v) const {
			return value_ > v.value_;
		}
		bool operator > (const T& v) const {
			return value_ > v;
		}
	};
}