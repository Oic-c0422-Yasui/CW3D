#pragma once

#include	"Subject.h"

namespace ActionGame {

	template <typename T>
	class CReactiveParameter : public CSubject<T> {
	private:
		/** �p�����[�^�[ */
		T		value_;
	public:
		/**
		 * �R���X�g���N�^
		 */
		CReactiveParameter()
			: CSubject<T>()
			, value_()
		{
		}

		/**
		 * �R���X�g���N�^
		 */
		CReactiveParameter(const T& v)
			: CSubject<T>()
			, value_(v)
		{
		}
		/**
		 * �R���X�g���N�^
		 */
		CReactiveParameter(const CReactiveParameter< T >& v)
			: CSubject<T>()
			, value_(v.value_)
		{
		}
		/**
		 * �f�X�g���N�^
		 */
		virtual ~CReactiveParameter()
		{
		}

		/** �L���X�g */
		operator const T& () const {
			return value_;
		}
		/** ��� */
		CReactiveParameter< T >& operator = (const CReactiveParameter< T >& v) {
			value_ = v.value_;
			this->Notify(value_);
			return *this;
		}
		CReactiveParameter< T >& operator = (const T& v) {
			value_ = v;
			this->Notify(value_);
			return *this;
		}
		void Set(const T& v) {
			value_ = v;
			this->Notify(value_);
		}

		/** �Z�p���Z�q +�@-�@* /�@*/
		T operator + (const CReactiveParameter< T >& v) const {
			return value_ + v.value_;
		}
		T operator + (const T& v) const {
			return value_ + v;
		}
		T operator - (const CReactiveParameter< T >& v) const {
			return value_ - v.value_;
		}
		T operator - (const T& v) const {
			return value_ - v;
		}
		T operator * (const CReactiveParameter< T >& v) const {
			return value_ * v.value_;
		}
		T operator * (const T& v) const {
			return value_ * v;
		}
		T operator / (const CReactiveParameter< T >& v) const {
			return value_ / v.value_;
		}
		T operator / (const T& v) const {
			return value_ / v;
		}

		/** ����������Z�q +=�@-=�@*=�@/= */
		CReactiveParameter< T >& operator += (const CReactiveParameter< T >& v) {
			value_ += v.value_;
			this->Notify(value_);
			return *this;
		}
		CReactiveParameter< T >& operator += (const T& v) {
			value_ += v;
			this->Notify(value_);
			return *this;
		}
		CReactiveParameter< T >& operator -= (const CReactiveParameter< T >& v) {
			value_ -= v.value_;
			this->Notify(value_);
			return *this;
		}
		CReactiveParameter< T >& operator -= (const T& v) {
			value_ -= v;
			this->Notify(value_);
			return *this;
		}
		CReactiveParameter< T >& operator *= (const CReactiveParameter< T >& v) {
			value_ *= v.value_;
			this->Notify(value_);
			return *this;
		}
		CReactiveParameter< T >& operator *= (const T& v) {
			value_ *= v;
			this->Notify(value_);
			return *this;
		}
		CReactiveParameter< T >& operator /= (const CReactiveParameter< T >& v) {
			value_ /= v.value_;
			this->Notify(value_);
			return *this;
		}
		CReactiveParameter< T >& operator /= (const T& v) {
			value_ /= v;
			this->Notify(value_);
			return *this;
		}

		/** ��r���Z�q == != */
		bool operator == (const CReactiveParameter< T >& v) const {
			return value_ == v.value_;
		}
		bool operator == (const T& v) const {
			return value_ == v;
		}
		bool operator != (const CReactiveParameter< T >& v) const {
			return value_ != v.value_;
		}
		bool operator != (const T& v) const {
			return value_ != v;
		}
		bool operator <= (const CReactiveParameter< T >& v) const {
			return value_ <= v.value_;
		}
		bool operator <= (const T& v) const {
			return value_ <= v;
		}
		bool operator < (const CReactiveParameter< T >& v) const {
			return value_ < v.value_;
		}
		bool operator < (const T& v) const {
			return value_ < v;
		}
		bool operator >= (const CReactiveParameter< T >& v) const {
			return value_ >= v.value_;
		}
		bool operator >= (const T& v) const {
			return value_ >= v;
		}
		bool operator > (const CReactiveParameter< T >& v) const {
			return value_ > v.value_;
		}
		bool operator > (const T& v) const {
			return value_ > v;
		}
	};
}