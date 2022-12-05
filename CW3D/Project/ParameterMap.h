#pragma once
#include	"Common.h"

namespace ActionGame {

	/**
	 * @brief		パラメーター保存
	 */
	class AnyParameterMap {
	private:
		//型置き換え
		using Key = std::string;
		using Map = std::unordered_map<Key, std::any>;

		//マップ
		Map parameters_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		AnyParameterMap()
			: parameters_()
		{
		}

		/**
		 * @brief		パラメーターの追加
		 * @param[in]	key			キー
		 * @param[in]	param		パラメーター
		 */
		template< typename T >
		void Add(const Key& key, const T& param)
		{
			parameters_[key] = param;
		}

		/**
		 * @brief		パラメーターの取得
		 * @param[in]	key			キー
		 * @return		取得したパラメーター
		 */
		template< typename T >
		T& Get(const Key& key)
		{
			const auto& it = parameters_.find(key);
			assert(it != parameters_.end());
			return std::any_cast<T&>(it->second);
		}

		/**
		 * @brief		パラメーターの取得
		 * @param[in]	key			キー
		 * @return		取得したパラメーター
		 */
		template< typename T >
		const T& Get(const Key& key) const
		{
			const auto& it = parameters_.find(key);
			assert(it != parameters_.end());
			return std::any_cast<const T&>(it->second);
		}

		/**
		 * @brief		パラメーターの存在判定
		 * @param[in]	key			キー
		 * @return		trueならある
		 */
		const bool IsContain(const Key& key) const
		{
			return parameters_.find(key) != parameters_.end();
		}
	};
	//ポインタ置き換え
	using AnyParameterMapPtr = std::shared_ptr<AnyParameterMap>;
}