#pragma once

#include	"Subject.h"

namespace ActionGame {

	template <typename T>
	class CReactiveParameter : public CSubject<T> {
	private:
		/** パラメーター */
		T		value_;
	public:
		/**
		 * コンストラクタ
		 */
		CReactiveParameter()
			: CSubject<T>()
			, value_()
		{
		}

		/**
		 * コンストラクタ
		 */
		CReactiveParameter(const T& v)
			: CSubject<T>()
			, value_(v)
		{
		}
		/**
		 * コンストラクタ
		 */
		CReactiveParameter(const CReactiveParameter< T >& v)
			: CSubject<T>()
			, value_(v.value_)
		{
		}
		/**
		 * デストラクタ
		 */
		virtual ~CReactiveParameter()
		{
		}

		/** キャスト */
		operator const T& () const {
			return value_;
		}
		/** 代入 */
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

		/** 算術演算子 +　-　* /　*/
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

		/** 複合代入演算子 +=　-=　*=　/= */
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

		/** 比較演算子 == != */
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