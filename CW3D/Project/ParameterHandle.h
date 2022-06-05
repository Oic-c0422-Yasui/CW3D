#pragma once

#include	"Common.h"

namespace Sample {

	/**
	 * @brief		�p�����[�^�[�ێ�
	 */
	template < typename T >
	class ParameterHandle
	{
	protected:
		/** �p�����[�^�[ */
		std::shared_ptr< T >			value_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		ParameterHandle() : value_(std::make_shared<T>()) { }
		ParameterHandle(const ParameterHandle& param) : value_(param) {}
		ParameterHandle(const T& initValue) : value_(std::make_shared<T>(initValue)) {}

		/**
		 * @brief		�擾
		 */
		T& Get() { return *value_; }
		const T& Get() const { return *value_; }
		operator T& () { return *value_; }
		operator const T& () const { return *value_; }

		/**
		 * @brief		�ݒ�
		 */
		void Set(const T& v) { *value_ = v; }
		ParameterHandle< T >& operator = (const ParameterHandle< T >& v) {
			value_ = v.value_;
			return *this;
		}
		const T& operator = (const T& v) {
			*value_ = v;
			return *value_;
		}
		const T& operator * () {
			return *value_;
		}

		/** �Z�p���Z�q +�@-�@* /�@*/
		T operator + (const ParameterHandle< T >& v) const {
			return *value_ + *v.value;
		}
		T operator + (const T& v) const {
			return *value_ + v;
		}
		T operator - (const ParameterHandle< T >& v) const {
			return *value_ - *v.value;
		}
		T operator - (const T& v) const {
			return *value_ - v;
		}
		T operator * (const ParameterHandle< T >& v) const {
			return *value_ * *v.value;
		}
		T operator * (const T& v) const {
			return *value_ * v;
		}
		T operator / (const ParameterHandle< T >& v) const {
			return *value_ / *v.value;
		}
		T operator / (const T& v) const {
			return *value_ / v;
		}

		/** ����������Z�q +=�@-=�@*=�@/= */
		ParameterHandle< T >& operator += (const ParameterHandle< T >& v) {
			*value_ += *v.value;
			return *this;
		}
		ParameterHandle< T >& operator += (const T& v) {
			*value_ += v;
			return *this;
		}
		ParameterHandle< T >& operator -= (const ParameterHandle< T >& v) {
			*value_ -= *v.value;
			return *this;
		}
		ParameterHandle< T >& operator -= (const T& v) {
			*value_ -= v;
			return *this;
		}
		ParameterHandle< T >& operator *= (const ParameterHandle< T >& v) {
			*value_ *= *v.value;
			return *this;
		}
		ParameterHandle< T >& operator *= (const T& v) {
			*value_ *= v;
			return *this;
		}
		ParameterHandle< T >& operator /= (const ParameterHandle< T >& v) {
			*value_ /= *v.value;
			return *this;
		}
		ParameterHandle< T >& operator /= (const T& v) {
			*value_ /= v;
			return *this;
		}

		/** ��r���Z�q == != <= < >= > */
		bool operator == (const ParameterHandle< T >& v) const {
			return *value_ == *v.value;
		}
		bool operator == (const T& v) const {
			return *value_ == v;
		}
		bool operator != (const ParameterHandle< T >& v) const {
			return *value_ != *v.value;
		}
		bool operator != (const T& v) const {
			return *value_ != v;
		}
		bool operator <= (const ParameterHandle< T >& v) const {
			return *value_ <= *v.value;
		}
		bool operator <= (const T& v) const {
			return *value_ <= v;
		}
		bool operator < (const ParameterHandle< T >& v) const {
			return *value_ < *v.value;
		}
		bool operator < (const T& v) const {
			return *value_ < v;
		}
		bool operator >= (const ParameterHandle< T >& v) const {
			return *value_ >= *v.value;
		}
		bool operator >= (const T& v) const {
			return *value_ >= v;
		}
		bool operator > (const ParameterHandle< T >& v) const {
			return *value_ > *v.value;
		}
		bool operator > (const T& v) const {
			return *value_ > v;
		}
	};

}