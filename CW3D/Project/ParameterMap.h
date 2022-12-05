#pragma once
#include	"Common.h"

namespace ActionGame {

	/**
	 * @brief		�p�����[�^�[�ۑ�
	 */
	class AnyParameterMap {
	private:
		//�^�u������
		using Key = std::string;
		using Map = std::unordered_map<Key, std::any>;

		//�}�b�v
		Map parameters_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		AnyParameterMap()
			: parameters_()
		{
		}

		/**
		 * @brief		�p�����[�^�[�̒ǉ�
		 * @param[in]	key			�L�[
		 * @param[in]	param		�p�����[�^�[
		 */
		template< typename T >
		void Add(const Key& key, const T& param)
		{
			parameters_[key] = param;
		}

		/**
		 * @brief		�p�����[�^�[�̎擾
		 * @param[in]	key			�L�[
		 * @return		�擾�����p�����[�^�[
		 */
		template< typename T >
		T& Get(const Key& key)
		{
			const auto& it = parameters_.find(key);
			assert(it != parameters_.end());
			return std::any_cast<T&>(it->second);
		}

		/**
		 * @brief		�p�����[�^�[�̎擾
		 * @param[in]	key			�L�[
		 * @return		�擾�����p�����[�^�[
		 */
		template< typename T >
		const T& Get(const Key& key) const
		{
			const auto& it = parameters_.find(key);
			assert(it != parameters_.end());
			return std::any_cast<const T&>(it->second);
		}

		/**
		 * @brief		�p�����[�^�[�̑��ݔ���
		 * @param[in]	key			�L�[
		 * @return		true�Ȃ炠��
		 */
		const bool IsContain(const Key& key) const
		{
			return parameters_.find(key) != parameters_.end();
		}
	};
	//�|�C���^�u������
	using AnyParameterMapPtr = std::shared_ptr<AnyParameterMap>;
}