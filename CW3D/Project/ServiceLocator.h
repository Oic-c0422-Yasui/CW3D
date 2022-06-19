#pragma once

#include	<memory>
#include	"Singleton.h"

namespace Sample {

	/**
	 * @brief		�T�[�r�X���P�[�^�[
	 */
	template <typename T>
	class ServiceLocator : public Singleton< ServiceLocator< T > >
	{
		friend class Singleton<ServiceLocator< T >>;
		using Service = std::shared_ptr< T >;
	protected:
		//�T�[�r�X�̋��L�|�C���^
		Service			service_;

		/**
		 * @brief		�R���X�g���N�^
		 */
		ServiceLocator()
			: service_() {
		}
	public:
		/**
		 * @brief		�T�[�r�X�̐ݒ�
		 */
		static void SetService(const Service& obj) noexcept {
			Singleton< ServiceLocator< T > >::GetInstance().service_ = obj;
		}

		/**
		 * @brief		�T�[�r�X�̎擾
		 */
		static Service& GetService() noexcept {
			return Singleton< ServiceLocator< T > >::GetInstance().service_;
		}
	};
}

