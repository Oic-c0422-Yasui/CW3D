#pragma once

#include	<memory>
#include	"Singleton.h"

namespace Sample {

	/**
	 * @brief		サービスロケーター
	 */
	template <typename T>
	class ServiceLocator : public Singleton< ServiceLocator< T > >
	{
		friend class Singleton<ServiceLocator< T >>;
		using Service = std::shared_ptr< T >;
	protected:
		//サービスの共有ポインタ
		Service			service_;

		/**
		 * @brief		コンストラクタ
		 */
		ServiceLocator()
			: service_() {
		}
	public:
		/**
		 * @brief		サービスの設定
		 */
		static void SetService(const Service& obj) noexcept {
			Singleton< ServiceLocator< T > >::GetInstance().service_ = obj;
		}

		/**
		 * @brief		サービスの取得
		 */
		static Service& GetService() noexcept {
			return Singleton< ServiceLocator< T > >::GetInstance().service_;
		}
	};
}

