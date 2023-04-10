#pragma once

#include	<memory>
#include	"Singleton.h"


/**
 * @brief		�T�[�r�X���P�[�^�[
 */
template <typename T>
class CServiceLocator : public Singleton< CServiceLocator< T > >
{
	friend class Singleton<CServiceLocator< T >>;
	using Service = std::shared_ptr< T >;
protected:
	//�T�[�r�X�̋��L�|�C���^
	Service			service_;

	/**
	 * @brief		�R���X�g���N�^
	 */
	CServiceLocator()
		: service_() {
	}
public:
	/**
	 * @brief		�T�[�r�X�̐ݒ�
	 */
	static void SetService(const Service& obj) noexcept {
		Singleton< CServiceLocator< T > >::GetInstance().service_ = obj;
	}

	/**
	 * @brief		�T�[�r�X�̎擾
	 */
	static Service& GetService() noexcept {
		return Singleton< CServiceLocator< T > >::GetInstance().service_;
	}
};

