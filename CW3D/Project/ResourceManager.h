#pragma once
#include "Common.h"
#include	"TemplateSingleton.h"

namespace Sample
{
	//なにかの型（入れるまで決まっていない）
	template<typename T>
	class ResourceManager
	{
	private:
		//シェアポインタを使いやすいように名前を付ける
		using ResourcePtr = std::shared_ptr<T>;
		//辞書のようなもの
		std::unordered_map<std::string, ResourcePtr> m_Resources;

		ResourceManager() :
			m_Resources()
		{

		}
	public:

		//リソースを追加する
		void AddResource(const std::string& key, const ResourcePtr& ptr)
		{
			m_Resources[key] = ptr;
		}

		//リソースを削除する
		bool DeleteResource(const std::string& key)
		{
			auto it = m_Resources.find(key);
			if (it != m_Resources.end())
			{
				m_Resources.erase(it);
				return true;
			}
			return false;
		}

		//リソースを取得する
		ResourcePtr& GetResource(const std::string& key)
		{
			return m_Resources[key];
		}

		//マネージャーのインスタンスを取得する
		static ResourceManager& GetInstance()
		{
			static ResourceManager instance;
			return instance;
		}

	};
}
	



