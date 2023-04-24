#pragma once


	/**
 * Singleton用テンプレート
 */
	template< typename T >
	class Singleton
	{
	private:
		Singleton(const Singleton& obj) = delete;
		Singleton(Singleton&& obj) = delete;

		static T* instance_;

	protected:

		Singleton() { }
		virtual ~Singleton() { }

		/**
		 * シングルトン用のインスタンスの生成
		 */
		static void Create()
		{

			if (instance_)
			{
				return;
			}
			instance_ = new T();
		}
	public:
		/**
		 * シングルトン用のアクセスポイントの定義
		 * この関数内でインスタンス化され、外部から参照できる
		 */
		static constexpr T& GetInstance()
		{
			if (instance_ == nullptr)
			{
				Create();
			}
			return *instance_;
		}

		/**
		 * シングルトン用のインスタンスの破棄
		 */
		static void Release()
		{
			//エラー確認
			assert(instance_);

			if (instance_)
			{
				delete instance_;
				instance_ = nullptr;
				return;
			}
		}
	};
	template< typename T > T* Singleton<T>::instance_ = nullptr;

