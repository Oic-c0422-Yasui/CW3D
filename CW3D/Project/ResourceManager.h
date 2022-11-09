#pragma once
#include "Common.h"
#include	"Singleton.h"

namespace Sample
{
	//なにかの型（入れるまで決まっていない）
	template<typename T>
	class ResourcePtrManager : public Singleton<ResourcePtrManager<T>>
	{
		friend class Singleton<ResourcePtrManager<T>>;
	private:
		//シェアポインタを使いやすいように名前を付ける
		using ResourcePtr = std::shared_ptr<T>;

		//辞書のようなもの
		using ResourceMap = std::unordered_map<std::string, ResourcePtr>;
		ResourceMap m_Resources;

		//タグ付き辞書
		std::unordered_map<std::string,ResourceMap> m_ResourcesMap;

		ResourcePtrManager() 
			: Singleton<ResourcePtrManager<T>>()
			, m_ResourcesMap()
		{

		}
	public:

		//リソースを追加する
		void AddResource(const std::string& key, const ResourcePtr& resource)
		{
			m_ResourcesMap["default"][key] = resource;
		}
		//リソースを追加する＆タグ付け
		void AddResource(const std::string& tag, const std::string& key, const ResourcePtr& resource)
		{
			m_ResourcesMap[tag][key] = resource;
		}

		//リソースを削除する
		bool DeleteResource(const std::string& key)
		{
			auto& map = m_ResourcesMap["default"];
			auto it = map.find(key);
			if (it != map.end())
			{
				map.erase(it);
				return true;
			}
			return false;
		}

		//タグ内のリソースを削除する
		bool DeleteResouce(const std::string& tag, const std::string& key)
		{
			auto& map = m_ResourcesMap[tag];
			auto it = map.find(key);
			if (it != map.end())
			{
				map.erase(it);
				return true;
			}
			return false;
		}

		//リソースを取得する
		ResourcePtr& GetResource(const std::string& key)
		{
			for (auto& map : m_ResourcesMap)
			{
				auto it = map.second.find(key);
				if (it != map.second.end())
				{
					return map.second[key];
				}
			}
			return nullptr;
		}
		//タグ内のリソースを取得する
		const ResourcePtr& GetResource(const std::string& tag, const std::string& key)
		{
			if (IsContainTag(tag))
			{
				return m_ResourcesMap[tag][key];
			}
			return nullptr;
		}

		//リソースが存在するか？
		bool IsContainResource(const std::string& key)
		{
			for (auto& map : m_ResourcesMap)
			{
				auto it = map.find(key);
				if (it != map.end())
				{
					return true;
				}
			}
			return false;
		}
		//リソースが存在するか？
		bool IsContainResource(const std::string& tag,const std::string& key)
		{
			for (auto& map : m_ResourcesMap[tag])
			{
				auto it = map.find(key);
				if (it != map.end())
				{
					return true;
				}
			}
			return false;
		}

		//タグが存在するか？
		bool IsContainTag(const std::string& tag)
		{
			auto it = m_ResourcesMap.find(tag);
			return it != m_ResourcesMap.end();
		}
	};

	//なにかの型（入れるまで決まっていない）
	template<typename T>
	class ResourceManager : public Singleton<ResourceManager<T>>
	{
		friend class Singleton<ResourceManager<T>>;
	private:
		//辞書のようなもの
		using ResourceMap = std::unordered_map<std::string, T>;
		ResourceMap m_Resources;

		//タグ付き辞書
		std::unordered_map<std::string, ResourceMap> m_ResourcesMap;

		ResourceManager()
			: Singleton<ResourceManager<T>>()
			, m_ResourcesMap()
		{

		}
	public:
		//リソースを追加する
		void AddResource(const std::string& key, const T& resource)
		{
			m_ResourcesMap["default"][key] = resource;
		}
		//リソースを追加する＆タグ付け
		void AddResource(const std::string& tag, const std::string& key, const T& resource)
		{
			m_ResourcesMap[tag][key] = resource;
		}

		//リソースを削除する
		bool DeleteResource(const std::string& key)
		{
			auto& map = m_ResourcesMap["default"];
			auto it = map.find(key);
			if (it != map.end())
			{
				map.erase(it);
				return true;
			}
			return false;
		}

		//タグ内のリソースを削除する
		bool DeleteResouce(const std::string& tag, const std::string& key)
		{
			auto& map = m_ResourcesMap[tag];
			auto it = map.find(key);
			if (it != map.end())
			{
				map.erase(it);
				return true;
			}
			return false;
		}

		//リソースを取得する
		const T& GetResource(const std::string& key)
		{
			for (auto& map : m_ResourcesMap)
			{
				auto it = map.second.find(key);
				if (it != map.second.end())
				{
					return map.second[key];
				}
			}
			return nullptr;
		}
		//リソースを取得する
		const T& GetResource(const std::string& tag, const std::string& key)
		{
			if (IsContainTag(tag))
			{
				return m_ResourcesMap[tag][key];
			}
			return nullptr;
		}

		//リソースが存在するか？
		bool IsContainResource(const std::string& key)
		{
			for (auto& map : m_ResourcesMap)
			{
				auto it = map.second.find(key);
				if (it != map.second.end())
				{
					return true;
				}
			}
			return false;
		}

		//タグが存在するか？
		bool IsContainTag(const std::string& tag)
		{
			auto it = m_ResourcesMap.find(tag);
			return it != m_ResourcesMap.end();
		}
	
	};
}
	



