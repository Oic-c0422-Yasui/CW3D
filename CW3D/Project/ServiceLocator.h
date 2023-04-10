#pragma once

#include	<memory>
#include	"Singleton.h"


/**
 * @brief		サービスロケーター
 */
template <typename T>
class CServiceLocator : public Singleton< CServiceLocator< T > >
{
	friend class Singleton<CServiceLocator< T >>;
	using Service = std::shared_ptr< T >;
protected:
	//サービスの共有ポインタ
	Service			service_;

	/**
	 * @brief		コンストラクタ
	 */
	CServiceLocator()
		: service_() {
	}
public:
	/**
	 * @brief		サービスの設定
	 */
	static void SetService(const Service& obj) noexcept {
		Singleton< CServiceLocator< T > >::GetInstance().service_ = obj;
	}

	/**
	 * @brief		サービスの取得
	 */
	static Service& GetService() noexcept {
		return Singleton< CServiceLocator< T > >::GetInstance().service_;
	}
};

