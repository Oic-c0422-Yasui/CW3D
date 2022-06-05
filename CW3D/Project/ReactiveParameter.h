#pragma once

#include	"Subject.h"

namespace Sample {

	template <typename T>
	class ReactiveParameter : public Subject<T> {
	private:
		/** �p�����[�^�[ */
		T		value;
	public:
		/**
		 * �R���X�g���N�^
		 */
		ReactiveParameter()
			: Subject<T>()
			, value()
		{
		}

		/**
		 * �R���X�g���N�^
		 */
		ReactiveParameter(const T& v)
			: Subject<T>()
			, value(v)
		{
		}
		/**
		 * �R���X�g���N�^
		 */
		ReactiveParameter(const ReactiveParameter< T >& v)
			: Subject<T>()
			, value(v.value)
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
			return value;
		}
		/** ��� */
		ReactiveParameter< T >& operator = (const ReactiveParameter< T >& v) {
			value = v.value;
			this->Notify(value);
			return *this;
		}
		ReactiveParameter< T >& operator = (const T& v) {
			value = v;
			this->Notify(value);
			return *this;
		}

		/** �Z�p���Z�q +�@-�@* /�@*/
		T operator + (const ReactiveParameter< T >& v) const {
			return value + v.value;
		}
		T operator + (const T& v) const {
			return value + v;
		}
		T operator - (const ReactiveParameter< T >& v) const {
			return value - v.value;
		}
		T operator - (const T& v) const {
			return value - v;
		}
		T operator * (const ReactiveParameter< T >& v) const {
			return value * v.value;
		}
		T operator * (const T& v) const {
			return value * v;
		}
		T operator / (const ReactiveParameter< T >& v) const {
			return value / v.value;
		}
		T operator / (const T& v) const {
			return value / v;
		}

		/** ����������Z�q +=�@-=�@*=�@/= */
		ReactiveParameter< T >& operator += (const ReactiveParameter< T >& v) {
			value += v.value;
			this->Notify(value);
			return *this;
		}
		ReactiveParameter< T >& operator += (const T& v) {
			value += v;
			this->Notify(value);
			return *this;
		}
		ReactiveParameter< T >& operator -= (const ReactiveParameter< T >& v) {
			value -= v.value;
			this->Notify(value);
			return *this;
		}
		ReactiveParameter< T >& operator -= (const T& v) {
			value -= v;
			this->Notify(value);
			return *this;
		}
		ReactiveParameter< T >& operator *= (const ReactiveParameter< T >& v) {
			value *= v.value;
			this->Notify(value);
			return *this;
		}
		ReactiveParameter< T >& operator *= (const T& v) {
			value *= v;
			this->Notify(value);
			return *this;
		}
		ReactiveParameter< T >& operator /= (const ReactiveParameter< T >& v) {
			value /= v.value;
			this->Notify(value);
			return *this;
		}
		ReactiveParameter< T >& operator /= (const T& v) {
			value /= v;
			this->Notify(value);
			return *this;
		}

		/** ��r���Z�q == != */
		bool operator == (const ReactiveParameter< T >& v) const {
			return value == v.value;
		}
		bool operator == (const T& v) const {
			return value == v;
		}
		bool operator != (const ReactiveParameter< T >& v) const {
			return value != v.value;
		}
		bool operator != (const T& v) const {
			return value != v;
		}
		bool operator <= (const ReactiveParameter< T >& v) const {
			return value <= v.value;
		}
		bool operator <= (const T& v) const {
			return value <= v;
		}
		bool operator < (const ReactiveParameter< T >& v) const {
			return value < v.value;
		}
		bool operator < (const T& v) const {
			return value < v;
		}
		bool operator >= (const ReactiveParameter< T >& v) const {
			return value >= v.value;
		}
		bool operator >= (const T& v) const {
			return value >= v;
		}
		bool operator > (const ReactiveParameter< T >& v) const {
			return value > v.value;
		}
		bool operator > (const T& v) const {
			return value > v;
		}
	};
}