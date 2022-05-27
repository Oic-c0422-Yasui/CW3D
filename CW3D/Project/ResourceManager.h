#pragma once
#include "Common.h"
#include	"Singleton.h"

namespace Sample
{
	//なにかの型（入れるまで決まっていない）
	template<typename T>
	class ResourceManager : public Singleton<ResourceManager<T>>
	{
		friend class Singleton<ResourceManager<T>>;
	private:
		//シェアポインタを使いやすいように名前を付ける
		using ResourcePtr = std::shared_ptr<T>;
		//辞書のようなもの
		std::unordered_map<std::string, ResourcePtr> m_Resources;

		std::unordered_map<std::string, T> m_ResourcesT;

		ResourceManager() :
			Singleton<ResourceManager<T>>(),
			m_Resources(),
			m_ResourcesT()
		{

		}
	public:

		//リソースを追加する
		void AddResource(const std::string& key, const ResourcePtr& ptr)
		{
			m_Resources[key] = ptr;
		}

		//リソースを追加する
		void AddResourceT(const std::string& key, const T& ptr)
		{
			m_ResourcesT[key] = ptr;
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

		//リソースを削除する
		bool DeleteResourceT(const std::string& key)
		{
			auto it = m_ResourcesT.find(key);
			if (it != m_ResourcesT.end())
			{
				m_ResourcesT.erase(it);
				return true;
			}
			return false;
		}

		//リソースを取得する
		ResourcePtr& GetResource(const std::string& key)
		{
			return m_Resources[key];
		}

		T& GetResourceT(const std::string& key)
		{
			return m_ResourcesT[key];
		}

		////マネージャーのインスタンスを取得する
		//static ResourceManager& GetInstance()
		//{
		//	static ResourceManager instance;
		//	return instance;
		//}

	};
}
	



