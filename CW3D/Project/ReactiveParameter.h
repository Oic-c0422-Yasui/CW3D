#pragma once

#include	"Subject.h"

namespace ActionGame {

	template <typename T>
	class ReactiveParameter : public CSubject<T> {
	private:
		/** パラメーター */
		T		value_;
	public:
		/**
		 * コンストラクタ
		 */
		ReactiveParameter()
			: CSubject<T>()
			, value_()
		{
		}

		/**
		 * コンストラクタ
		 */
		ReactiveParameter(const T& v)
			: CSubject<T>()
			, value_(v)
		{
		}
		/**
		 * コンストラクタ
		 */
		ReactiveParameter(const ReactiveParameter< T >& v)
			: CSubject<T>()
			, value_(v.value_)
		{
		}
		/**
		 * デストラクタ
		 */
		virtual ~ReactiveParameter()
		{
		}

		/** キャスト */
		operator const T& () const {
			return value_;
		}
		/** 代入 */
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

		/** 算術演算子 +　-　* /　*/
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

		/** 複合代入演算子 +=　-=　*=　/= */
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

		/** 比較演算子 == != */
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